#include <Arduino.h>
#include <util/delay.h>
#include <avr/io.h>
#include "digital_in.h"
#include "digital_out.h"

// Declare the RotaryEncoder class 
class RotaryEncoder {
public:
  void init(Digital_in& c1_instance, Digital_in& c2_instance) {
    c1 = &c1_instance;
    c2 = &c2_instance;
    position_count = 0;
    last_c1_state = false;

  }

  void update() {
    bool current_c1_state = c1->is_hi();
    bool current_c2_state = c2->is_hi();

    if (current_c1_state != last_c1_state) {
      // C1 has changed
      if (current_c1_state != current_c2_state) {
        // Clockwise rotation
        position_count++;
      } else {
        // Counterclockwise rotation
        position_count--;
        //last_c1_state = current_c1_state;
      }
      
    }

    last_c1_state = current_c1_state;
    
  }

  int get_position_count() const {
    return position_count;
  }

private:
  Digital_in* c1;
  Digital_in* c2;
  int position_count;
  bool last_c1_state;
};

// Initialize the Digital_in and Digital_out objects
Digital_in c1(4);  // Connect to pin D4
Digital_in c2(3);  // Connect to pin D3
Digital_out led(5);  // Connect to built-in LED, usually D13 on most Arduino boards

RotaryEncoder encoder;  // Initialize encoder without input

void setup() {
  Serial.begin(9600);  // Initialize serial communication at 9600 baud

  // Initialize digital I/O
  c1.init(); 
  c2.init();
  led.init();

  // Initialize the encoder
  encoder.init(c1, c2);
}

void loop() {
  // Update the encoder state
  encoder.update();
  
  // Print the encoder position to the serial monitor
  Serial.println(encoder.get_position_count());
  
  // Turn on the LED for a short time for visualization (optional)
  //led.set_hi();
  //_delay_ms(0.2);  
  //led.set_lo();
  

}
