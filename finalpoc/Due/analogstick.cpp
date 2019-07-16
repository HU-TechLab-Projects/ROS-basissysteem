#include "analogstick.hpp"

int analogStick::getYValue(){
  return y.read();
}

int analogStick::getXValue(){
  return x.read();
}

bool analogStick::getSwValue(){
  return !sw.read();
}
