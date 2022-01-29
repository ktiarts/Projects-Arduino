/*
  Timer management code for the DMD library, includes implementation
  for AVR-based Arduino compatible (Eleven, Uno, etc.) and for Arduino Due

 Copyright (C) 2014 Freetronics, Inc. (info <at> freetronics <dot> com)

 Updated by Angus Gratton, based on DMD by Marc Alexander.

---

 This program is free software: you can redistribute it and/or modify it under the terms
 of the version 3 GNU General Public License as published by the Free Software Foundation.

 This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 See the GNU General Public License for more details.

 You should have received a copy of the GNU General Public License along with this program.
 If not, see <http://www.gnu.org/licenses/>.
*/
#include "DMD2.h"

// Uncomment the following line if you don't want DMD library to touch
// any timer functionality (ie if you want to use TimerOne library or
// similar, or other libraries that use timers.)

#define NO_TIMERS

#ifdef NO_TIMERS
// Timer-free stub code
void BaseDMD::begin() {
  beginNoTimer();
}

void BaseDMD::end() {
}

#else // Use timers

// Keep an array of pointers to all known DMDs so we can
// call them on timer interrupt.
//
// List uses realloc to grow, doesn't shrink on stop just NULLs out the
// entry (presuming there isn't a lot of growth/shrinkage of DMD arrays!)
static volatile BaseDMD **running_dmds = 0;
static volatile int running_dmd_len = 0;

// Add a running_dmd to the list (disable interrupts when running)
static void register_running_dmd(BaseDMD *dmd)
{
  int empty = -1;
  for(int i = 0; i < running_dmd_len; i++) {
    if(running_dmds[i] == dmd)
      return; // Already running and registered
    if(!running_dmds[i])
      empty = i; // Found an unused slot in the array
  }

  if(empty == -1) { // Grow array to fit new entry
    running_dmd_len++;
    BaseDMD **resized = (BaseDMD **)realloc(running_dmds, sizeof(BaseDMD *)*running_dmd_len);
    if(!resized) {
      // Allocation failed, bail out
      running_dmd_len--;
      return;
    }
    empty = running_dmd_len-1;
    running_dmds = (volatile BaseDMD **)resized;
  }
  running_dmds[empty] = dmd;
}

// Null out a running_dmd from the list (disable interrupts when running)
static bool unregister_running_dmd(BaseDMD *dmd)
{
  bool still_running = false;
  for(int i = 0; i < running_dmd_len; i++) {
    if(running_dmds[i] == dmd)
      running_dmds[i] = NULL;
    else if (running_dmds[i])
      still_running = true;
  }
  return still_running;
}

static void inline __attribute__((always_inline)) scan_running_dmds()
{
  for(int i = 0; i < running_dmd_len; i++) {
    BaseDMD *next = (BaseDMD*)running_dmds[i];
    if(next) {
      next->scanDisplay();
    }
  }
}

#ifdef __AVR__

/* This timer ISR uses the standard /64 timing used by Timer1 in the Arduino core,
   so none of those registers (or normal PWM timing) is changed. We do skip 50% of ISRs
   as 50% timer overflows is approximately every 4ms, which is fine for flicker-free
   updating.
*/
ISR(TIMER1_OVF_vect)
{
  static uint8_t skip_isrs = 0;
  skip_isrs = (skip_isrs + 1) % 2;
  if(skip_isrs)
    return;
  scan_running_dmds();
}

void BaseDMD::begin()
{
  beginNoTimer(); // Do any generic setup

  char oldSREG = SREG;
  cli();
  register_running_dmd(this);
  TIMSK1 = _BV(TOIE1); // set overflow interrupt
  SREG = oldSREG;
}

void BaseDMD::end()
{
  char oldSREG = SREG;
  cli();
  bool still_running = unregister_running_dmd(this);
  if(!still_running)
    TIMSK1 &= ~_BV(TOIE1); // disable timer interrupt, no more DMDs are running
  SREG = oldSREG;
  // One final (manual) scan to turn off all LEDs
  clearScreen();
  scanDisplay();
}

#else // __ARM__, Due assumed

void TC7_Handler(){
  TC_GetStatus(TC2, 1);
  scan_running_dmds();
}

void BaseDMD::begin()
{
  beginNoTimer(); // Do any generic setup

  NVIC_DisableIRQ(TC7_IRQn);
  register_running_dmd(this);
  pmc_set_writeprotect(false);
  pmc_enable_periph_clk(TC7_IRQn);
  // Timer 7 is TC2, channel 1
  TC_Configure(TC2, 1, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK4); // counter up, /128 divisor
  TC_SetRC(TC2, 1, 2500); // approx 4ms at /128 divisor
  TC2->TC_CHANNEL[1].TC_IER=TC_IER_CPCS;

  NVIC_ClearPendingIRQ(TC7_IRQn);
  NVIC_EnableIRQ(TC7_IRQn);
  TC_Start(TC2, 1);
}

void BaseDMD::end()
{
  NVIC_DisableIRQ(TC7_IRQn);
  bool still_running = unregister_running_dmd(this);
  if(still_running)
    NVIC_EnableIRQ(TC7_IRQn); // Still some DMDs running
  else
    TC_Stop(TC2, 1);
  clearScreen();
  scanDisplay();
}

#endif // ifdef __AVR__
#endif // ifdef NO_TIMERS