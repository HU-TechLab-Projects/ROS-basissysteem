#ifndef ANALOGSITCK_H
#define ANALOGSITCK_H
#include "hwlib.hpp"
#include "simple.pb.h"

class analogStick{
  hwlib::target::pin_adc &  x;
  hwlib::target::pin_adc &  y;
  hwlib::target::pin_in  & sw;
public:
  analogStick(hwlib::target::pin_adc &  x,
              hwlib::target::pin_adc &  y,
              hwlib::target::pin_in  & sw) : x(x), y(y), sw(sw){}

  int getXValue();
  int getYValue();
  bool getSwValue();
};

#endif /* ANALOGSITCK_H */
