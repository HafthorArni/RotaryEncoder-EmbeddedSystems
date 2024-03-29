#include "digital_in.h"
#include "digital_out.h"
#include "encoder.h"
#include <util/delay.h>
#include <Arduino.h>
#include "timer_msec.h"

Timer_msec timer;
Digital_out led(5);  // Assuming LED is connected to pin 5
Encoder encoder(3, 4);  // Assuming C1 is connected to pin 3 and C2 is connected to pin 4

int main() {
  init();  // Initialize Arduino libraries
  Serial.begin(9600);  // Initialize Serial communication at 9600 baud rate
  timer.init(0.1);
  sei();
  
  encoder.init();
  led.init();

  int revnumlast = 0;
  while (1) {
    //Serial.println(encoder.position());  // Print the encoder position continuously

    // calculationg the number of revolutions
    int revnum = encoder.position()/1400;
    if (revnum!= revnumlast){
      Serial.print("Revolution number:");
      Serial.println(revnum);
    }
    revnumlast = revnum;
  }
  
  return 0;
}

ISR(TIMER1_COMPA_vect){
    encoder.update();  // Update the encoder position
    
    led.toggle();

}
