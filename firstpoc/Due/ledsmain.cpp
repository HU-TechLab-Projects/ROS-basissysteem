#include "ledsmain.hpp"
int ledsmain(){
  hwlib::wait_ms(500);  
  auto comm = nanocom<>();


  while(true){
    command command_msg     = command_init_zero;
    ack_nak ack_nak_msg     = ack_nak_init_zero;
    sum_rpc sum_rpc_msg     = sum_rpc_init_zero;
    single_int rpc_response = single_int_init_zero;

    auto p1 = hwlib::target::pin_out(hwlib::target::pins::d53);
    auto p2 = hwlib::target::pin_out(hwlib::target::pins::d51);
    auto p3 = hwlib::target::pin_out(hwlib::target::pins::d49);
    auto p4 = hwlib::target::pin_out(hwlib::target::pins::d47);
    auto p5 = hwlib::target::pin_out(hwlib::target::pins::d45);
    auto port = hwlib::port_out_from(p1, p2, p3, p4, p5);

    comm.receive_message(&command_msg, command_fields);
    if(strcmp("sum", command_msg.command) == 0){
      ack_nak_msg.ack = true;
      comm.send_message(&ack_nak_msg, ack_nak_fields);
      comm.receive_message(&sum_rpc_msg, sum_rpc_fields);
      rpc_response.response = sum_rpc_msg.a + sum_rpc_msg.b;
      comm.send_message(&rpc_response, single_int_fields);
    } else if (strcmp("led", command_msg.command) == 0) {
      ack_nak_msg.ack = true;
      comm.send_message(&ack_nak_msg, ack_nak_fields);
      comm.receive_message(&rpc_response, single_int_fields);
      comm.send_message(&ack_nak_msg, ack_nak_fields);
      port.write(1 << (rpc_response.response));
    } else {
      // comm.send_message(&ack_nak_msg, ack_nak_fields);
    }
  }

  //
  // while(true){
  //   for(uint16_t i = 0; i < port.number_of_pins(); i++){
  //     port.write (1 << i);
  //     hwlib::wait_ms(100);
  //   }
  // }
  return 0;
}
