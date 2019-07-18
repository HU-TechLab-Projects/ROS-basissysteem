#include "ledsmainpcside.hpp"
#include <random>
int ledsmainpcside(){
  auto comm = nanocom<>();
  char msg [] = "sum\0";
  char led [] = "led\0";
  while(true){
    std::random_device generator;
    std::uniform_int_distribution<int> distribution(1,1000);

    command command_msg = command_init_zero;
    ack_nak ack_nak_msg = ack_nak_init_zero;
    sum_rpc sum_rpc_msg = sum_rpc_init_zero;
    single_int rpc_response = single_int_init_zero;


    strncpy(command_msg.command, msg, sizeof(command_msg.command));

    // for(uint32_t i = 0; i < sizeof(command_msg.command); i++){
    //   std::cout << command_msg.command[i];
    // }
    // std::cout << std::endl;

    comm.send_message(&command_msg, command_fields);
    comm.receive_message(&ack_nak_msg, ack_nak_fields);
    if(!ack_nak_msg.ack){
      std::cout << "sum command did not get an ack" << std::endl;
      continue;
    }
    sum_rpc_msg.a = distribution(generator);
    sum_rpc_msg.b = distribution(generator);

    // std::cout << "sending sum of numbers: "
    //           << sum_rpc_msg.a
    //           << " and "
    //           << sum_rpc_msg.b
    //           << std::endl;

    comm.send_message(&sum_rpc_msg, sum_rpc_fields);
    comm.receive_message(&rpc_response, single_int_fields);

    // std::cout << "the answer is "
    //           << rpc_response.response
    //           << std::endl;

    rpc_response.response = rpc_response.response % 5;
    strncpy(command_msg.command, led, sizeof(command_msg.command));

    comm.send_message(&command_msg, command_fields);
    comm.receive_message(&ack_nak_msg, ack_nak_fields);
    if(!ack_nak_msg.ack){
      std::cout << "led command did not get an ack" << std::endl;
      continue;
    }

    comm.send_message(&rpc_response, single_int_fields);
    comm.receive_message(&ack_nak_msg, ack_nak_fields);
    if(!ack_nak_msg.ack){
      std::cout << "set led command did not get an ack" << std::endl;
      continue;
    }

    // std::cout << "led: " << (rpc_response.response +1) << " should be on now" << std::endl;
    // usleep(1000000);
  }
  return 0;
}
