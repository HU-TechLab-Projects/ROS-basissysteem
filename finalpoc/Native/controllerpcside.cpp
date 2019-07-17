#include "controllerpcside.hpp"


bool sWrite(int fd, uint8_t * buf, size_t count) {
  ssize_t counter;
  size_t bytesSent = 0;
  while(bytesSent < count){
    counter = write(fd, buf + bytesSent, count - bytesSent);
    if (counter < 0){
      perror("Write Failed: ");
      return false;
    }
    bytesSent += counter;
  }
  return bytesSent == count;
}

int controllerpcside (){

  auto test = nanocom<>();
  bool status;
  while(true){
    Controller message = Controller_init_zero;
    constexpr char hallo[] = "h";
    std::cout << "writing\n";
    if (!sWrite(test.serial_port, (uint8_t *)hallo, 1)){
      usleep(1000);
      continue;
    }
    status = test.receive_message(&message, Controller_fields);
    if(!status){
      usleep(1000);
      continue;
    }

    std::cout << "----------" << std::endl;
    std::cout << message.x << std::endl;
    std::cout << "----------" << std::endl;
    std::cout << message.y << std::endl;
    std::cout << "----------" << std::endl;
    std::cout << message.sw << std::endl;
    std::cout << "----------" << std::endl;
  }
}
