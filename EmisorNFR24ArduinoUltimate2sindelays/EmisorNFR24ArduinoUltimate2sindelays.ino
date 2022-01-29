/*
  // March 2014 - TMRh20 - Updated along with High Speed RF24 Library fork
  // Parts derived from examples by J. Coliz <maniacbug@ymail.com>
*/
/**
 * Example for efficient call-response using ack-payloads 
 *
 * This example continues to make use of all the normal functionality of the radios including
 * the auto-ack and auto-retry features, but allows ack-payloads to be written optionally as well.
 * This allows very fast call-response communication, with the responding radio never having to 
 * switch out of Primary Receiver mode to send back a payload, but having the option to if wanting
 * to initiate communication instead of respond to a commmunication.
 */
 

#include<avr/wdt.h> /* Header for watchdog timers in AVR */
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

// Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 
RF24 radio(9,10);

// Topology
const uint64_t pipes[2] = { 0xABCDABCD71LL, 0x544d52687CLL };              // Radio pipe addresses for the 2 nodes to communicate.

// Role management: Set up role.  This sketch uses the same software for all the nodes
// in this system.  Doing so greatly simplifies testing.  

typedef enum { role_ping_out = 1, role_pong_back } role_e;                 // The various roles supported by this sketch
const char* role_friendly_name[] = { "invalid", "Ping out", "Pong back"};  // The debug-friendly names of those roles
role_e role = role_pong_back;                                              // The role of the current running sketch

// A single byte to keep track of the data being sent back and forth
byte counter = 1;

void setup(){
wdt_disable();  
  Serial.begin(115200);
  printf_begin();
  radio.begin();
  radio.setAutoAck(1);                    // Ensure autoACK is enabled
  radio.enableAckPayload();               // Allow optional ack payloads
  radio.setRetries(0,15);                 // Smallest time between retries, max no. of retries
  radio.setPayloadSize(1);                // Here we are sending 1-byte payloads to test the call-response speed
  role = role_ping_out;                  // Become the primary transmitter (ping out)
  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1,pipes[1]);
  pinMode(6,INPUT);
  pinMode(7,INPUT);
  wdt_enable(WDTO_1S);
}

void loop(void) {

    radio.stopListening();                                  // First, stop listening so we can talk.
        
    printf("Now sending %d as payload. ",counter);
    byte gotByte;  
    unsigned long time = micros();                          // Take the time, and send it.  This will block until complete   
       wdt_reset();                                                     //Called when STANDBY-I mode is engaged (User is finished sending)

    Serial.println("");
    if(digitalRead(6) == 1){
      counter = 1;
      wdt_reset();
    }
    if (digitalRead(7) == 1){
      counter = 2;
      wdt_reset();
    }
    if ((digitalRead(7) == 0) && (digitalRead(6) == 0)){
      counter = 3;
      wdt_reset();
    }
 
   radio.write(&counter,1);
          
        }
  
