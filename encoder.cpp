#include "encoder.h"

Encoder::Encoder(int pin1, int pin2) : c1(pin1), c2(pin2), pos(0), last_c1(false), last_c2(false) {}

void Encoder::init() {
  c1.init();
  c2.init();
}

  void Encoder::update() {
    bool current_c1 = c1.is_hi();
    bool current_c2 = c2.is_hi();

    if (current_c1 != last_c1) {
      // C1 has changed
      if (current_c1 !=  c2.is_hi()) {
        // Clockwise rotation
        pos++;
      } else {
        // Counterclockwise rotation
        pos--;
        //last_c1_state = current_c1_state;
      }
      
    }

    last_c1 = current_c1;
    
  }


int Encoder::position() {
  return pos;
}
