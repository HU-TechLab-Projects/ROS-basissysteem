#include "ledsmainpcside.hpp"

int ledsmainpcside(){
  auto comm = nanocom<>();

  command command_msg = command_init_zero;
  ack_nak ack_nak_msg = ack_nak_init_zero;
  sum_rpc sum_rpc_msg = sum_rpc_init_zero;
  single_int rpc_response = single_int_init_zero;
  char msg [] = "sum\0";
  strncpy(command_msg.command, msg, sizeof(command_msg.command));

  for(uint32_t i = 0; i < sizeof(command_msg.command); i++){
    std::cout << command_msg.command[i];
  }
  std::cout << std::endl;

  comm.send_message(&command_msg, command_fields);
  while(!comm.receive_message(&ack_nak_msg, ack_nak_fields));

  sum_rpc_msg.a = 5;
  sum_rpc_msg.b = 4;

  std::cout << "sending sum of numbers: "
            << sum_rpc_msg.a
            << " and "
            << sum_rpc_msg.b
            << std::endl;

  comm.send_message(&sum_rpc_msg, sum_rpc_fields);
  while(!comm.receive_message(&rpc_response, single_int_fields));

  std::cout << "the answer is "
            << rpc_response.response
            << std::endl;




  return 0;
}
