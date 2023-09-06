#include <Arduino.h>
#include <util/delay.h>
#include <avr/io.h>
#include "digital_in.h"
#include "digital_out.h"

// Declare the RotaryEncoder class
class RotaryEncoder {
public:
  RotaryEncoder(Digital_in& c1) : c1(c1), position_count(0), last_c1_state(false) {}
  void update() {
    bool current_c1_state = c1.is_hi();
    bool current_c2_state = c2.is_hi();
    
    if (current_c1_state != last_c1_state) {
      if (current_c2_state != current_c1_state){
        position_count++;
      }
      else {
        position_count--;
      }
    }
    
      last_c1_state = current_c1_state;
    }
  
  int position() {
    return position_count;
  }

private:
  Digital_in& c1;
  int position_count;
  bool last_c1_state;
};

// Initialize the Digital_in and Digital_out objects and the RotaryEncoder
Digital_in c1(4);  // Connect to pin D4
Digital_in c2(3);  // Connect to pin D3
Digital_out led(5);  // Connect to built-in LED, usually D13 on most Arduino boards

RotaryEncoder encoder(c1);  // Initialize encoder with c1 as input

void setup() {
  Serial.begin(9600);  // Initialize serial communication at 9600 baud

  // Initialize digital I/O
  c1.init(); 
  c2.init();
  led.init();
}

void loop() {
  // Update the encoder state
  encoder.update();
  
  // Print the encoder position to the serial monitor
  Serial.println(encoder.position());
  
  // Turn on the LED for a short time for visualization (optional)
  led.set_hi();
  _delay_ms(1);  
  led.set_lo();
  
  // You can add delay here based on the calculated minimum sampling time
  // _delay_ms(YOUR_MINIMUM_SAMPLING_TIME_IN_MS);
}
