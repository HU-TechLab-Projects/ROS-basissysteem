#include "ledsmain.hpp"

int ledsmain(){
  auto p1 = hwlib::target::pin_out(hwlib::target::pins::d53);
  auto p2 = hwlib::target::pin_out(hwlib::target::pins::d51);
  auto p3 = hwlib::target::pin_out(hwlib::target::pins::d49);
  auto p4 = hwlib::target::pin_out(hwlib::target::pins::d47);
  auto p5 = hwlib::target::pin_out(hwlib::target::pins::d45);
  auto port = hwlib::port_out_from(p1, p2, p3, p4, p5);

  while(true){
    for(uint16_t i = 0; i < port.number_of_pins(); i++){
      port.write (1 << i);
      hwlib::wait_ms(100);
    }
  }

}
