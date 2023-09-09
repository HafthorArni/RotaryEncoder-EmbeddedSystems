#include "digital_in.h"
#include "digital_out.h"
#include "encoder.h"
#include <util/delay.h>
#include <Arduino.h>

int main() {
  init();  // Initialize Arduino libraries
  Serial.begin(9600);  // Initialize Serial communication at 9600 baud rate
  
  Encoder encoder(3, 4);  // Assuming C1 is connected to pin 3 and C2 is connected to pin 4
  Digital_out led(5);  // Assuming LED is connected to pin 5
  
  encoder.init();
  led.init();
  
  while (1) {
    encoder.update();  // Update the encoder position
    
    // Print the current encoder position to the Serial monitor
    Serial.println(encoder.position());
  
    // Minimum sampling time to avoid missing an encoder pulse
    _delay_ms(0.286);  // 286 microseconds

    // Turn on the LED to signal that you have finished handling the state change
    led.toggle();
  }
  
  return 0;
}