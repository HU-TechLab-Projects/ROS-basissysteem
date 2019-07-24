#include "controllerpcside.hpp"

int controllerpcside (){

  auto comm = nanocom<>("/dev/ttyACM0", B115200);
  constexpr char hallo[] = "cont\0";


  while(comm.status){
    Controller controller_msg = Controller_init_zero;
    command command_msg       = command_init_zero;

    strncpy(command_msg.command, hallo, sizeof(command_msg.command));

    comm.send_message(&command_msg,command_fields);
    comm.receive_message(&controller_msg, Controller_fields);

    std::cout << "----------" << std::endl;
    std::cout << controller_msg.x << std::endl;
    std::cout << "----------" << std::endl;
    std::cout << controller_msg.y << std::endl;
    std::cout << "----------" << std::endl;
    std::cout << controller_msg.sw << std::endl;
    std::cout << "----------" << std::endl;
  }
  return -1;
}
