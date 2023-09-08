#ifndef ENCODER_H
#define ENCODER_H

#include "digital_in.h"
class Encoder {
  public:
    Encoder(int pin1, int pin2);
    void init();
    void update();
    int position();
  private:
    Digital_in c1, c2;
    int pos;
    bool last_c1;
    bool last_c2;
};

#endif // ENCODER_H