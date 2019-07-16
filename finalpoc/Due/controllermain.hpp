#ifndef CONTROLLERMAIN_H
#define CONTROLLERMAIN_H
#include "hwlib.hpp"
#include "due_nanocom.hpp"
#include "simple.pb.h"
#include "analogstick.hpp"

template<typename T>
bool sendControllerMsg(T & comm, Controller * message, analogStick & stick){
  message->x = stick.getXValue();
  message->y = stick.getYValue();
  message->sw = stick.getSwValue();

  return comm.send_message(message, Controller_fields);
}

template<typename T>
int controllerpoc(T & comm){
  hwlib::wait_ms(500);
  PIOB->PIO_OER = { 0x1U << 27 };
  auto pinSW    = hwlib::target::pin_in (hwlib::target::pins::d41);
  auto pinXAdc  = hwlib::target::pin_adc(hwlib::target::ad_pins::a5);
  auto pinYAdc  = hwlib::target::pin_adc(hwlib::target::ad_pins::a4);
  auto testDing = analogStick(pinXAdc, pinYAdc, pinSW);

  while(true){
    Controller message = Controller_init_zero;

      if (hwlib::uart_char_available()){
        PIOB->PIO_SODR = 0x01 << 27;
        if(hwlib::uart_getc() == 'h'){
            sendControllerMsg(comm, &message, testDing);
      }
    }
  }
  return 1;
}

#endif /* CONTROLLERMAIN_H */
