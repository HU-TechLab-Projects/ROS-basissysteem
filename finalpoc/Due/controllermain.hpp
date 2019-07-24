#ifndef CONTROLLERMAIN_H
#define CONTROLLERMAIN_H
#include "hwlib.hpp"
#include "due_nanocom.hpp"
#include "simple.pb.h"
#include "analogstick.hpp"

int controllerpoc(){
  hwlib::wait_ms(500);
  nanocom comm = nanocom<>();
  // PIOB->PIO_OER = { 0x1U << 27 };
  auto pinSW    = hwlib::target::pin_in (hwlib::target::pins::d41);
  auto pinXAdc  = hwlib::target::pin_adc(hwlib::target::ad_pins::a5);
  auto pinYAdc  = hwlib::target::pin_adc(hwlib::target::ad_pins::a4);
  auto stick = analogStick(pinXAdc, pinYAdc, pinSW);

  while(true){
    Controller controller_msg = Controller_init_zero;
    command command_msg       = command_init_zero;

    comm.receive_message(&command_msg,command_fields);
    if(strcmp("cont", command_msg.command) == 0){
      controller_msg.x = stick.getXValue();
      controller_msg.y = stick.getYValue();
      controller_msg.sw = stick.getSwValue();
      comm.send_message(&controller_msg, Controller_fields);
    }
  }
  return 1;
}

#endif /* CONTROLLERMAIN_H */
