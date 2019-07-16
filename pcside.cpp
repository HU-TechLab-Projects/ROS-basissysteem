#include "native_nanocom.hpp"
#include "simple.pb.h"
//Open the serial port. Change device path as needed (currently set to an standard FTDI USB-UART cable type device)

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
  // std::cout << "writing" << std::endl;
  return bytesSent == count;
}
//
// bool read_callback(pb_istream_t *stream, uint8_t *buf, size_t count){
//     return sRead(stream, buf, count);
//
// }
//
// bool halloArduino(int fd){
//   constexpr char hallo[] = "h";
//   constexpr char ard[]   = "arduino";
//   // constexpr int size = sizeof(ard);
//   // char randombuff[1000] = {0};
//   char response [8];
//   if (!sWrite(fd, (uint8_t *)hallo, 1)){
//     return false;
//   }
//   if (!sRead(fd, (uint8_t *)response, 8)){
//     return false;
//   }
//   std::cout << "hier" << std::endl;
//   for(size_t i = 0; i < sizeof(ard); i++){
//     std::cout << response[i];
//   }
//   return strcmp(ard, response) == 0;
// }

// pb_istream_t pb_istream_from_uart(int port){
//   pb_istream_t stream = {&read_callback, (void*)(intptr_t)port, SIZE_MAX};
//   return stream;
// }

int main (){
  // int serial_port = open("/dev/ttyACM0", O_RDWR);
  // if (serial_port < 0){
  //   perror("yeeter de yote: ");
  //   return 1;
  // }
  // struct termios tty;
  // // std::cout << serial_port << std::endl;
  // memset(&tty, 0, sizeof (tty));
  // // Read in existing settings, and handle any error
  // if(tcgetattr(serial_port, &tty) != 0) {
  /*     printf("Error %i from tcgetattr: %s\n", errno, strerror(errno)); */
  // }
  //
  // tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
  // tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
  // tty.c_cflag |=  CS8; // 8 bits per byte (most common)
  // tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
  // tty.c_cflag |=  CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)
  // tty.c_cflag &= ~HUPCL; //Turn off hangup to prevent reset on read write switch
  //
  // tty.c_lflag &= ~ICANON;
  // tty.c_lflag &= ~ECHO; // Disable echo
  // tty.c_lflag &= ~ECHOE; // Disable erasure
  // tty.c_lflag &= ~ECHONL; // Disable new-line echo
  // tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
  // tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
  // tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes
  //
  // tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
  // tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
  // // tty.c_oflag &= ~OXTABS; // Prevent conversion of tabs to spaces (NOT PRESENT ON LINUX)
  // // tty.c_oflag &= ~ONOEOT; // Prevent removal of C-d chars (0x004) in output (NOT PRESENT ON LINUX)
  //
  // tty.c_cc[VTIME] = 0;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
  // tty.c_cc[VMIN]  = 0;
  // //
  // // // Set in/out baud rate to be 9600
  // cfsetispeed(&tty, B2400);
  // cfsetospeed(&tty, B2400);
  //
  // // Save tty settings, also checking for errora
  // if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
      /* printf("Error %i from tcsetattr: %s\n", errno, strerror(errno)); */
  // }

  // Write to serial port
  // write(serial_port, "Hello, world!", sizeof(msg));

  // Allocate memory for read buffer, set size according to your needs
  //uint8_t read_buf [128] = {0};

  // Read bytes. The behaviour of read() (e.g. does it block?,
  // how long does it block for?) depends on the configuration
  // settings above, specifically VMIN and VTIME
  // int num_bytes = read(serial_port, &read_buf, sizeof(read_buf));

  // n is the number of bytes read. n may be 0 if no bytes were received, and can also be -1 to signal an error.
  // if (num_bytes < 0) {
  //     printf("Error reading: %s", strerror(errno));
  // }

  //printf("Read %i bytes. Received message: %s n", num_bytes, read_buf);

  auto test = nanocom<>();
  while(true){
  // usleep(10);
  Controller message = Controller_init_zero;
  /* Create a stream that reads from the buffer. */
  constexpr char hallo[] = "h";
  // pb_istream_t stream = pb_istream_from_uart(serial_port);
  std::cout << "writing\n";
  if (!sWrite(test.serial_port, (uint8_t *)hallo, 1)){
    return 1;
  }
  while(!test.receive_message(&message, Controller_fields))

  // bool status = pb_decode_delimited(&stream, Controller_fields, &message);
  // pb_read(&stream, read_buf, MyMessage_size);
  // pb_istream_t stream2 = pb_istream_from_buffer(read_buf, MyMessage_size);
  /* Now we are ready to decode the message. */
  // size_t x = 0;
  // while((char)read_buf[x] != '0'){
  //   std::cout << (char)read_buf[x];
  //   x++;
  // }
  // std::cout << std::endl;

  /* Check for errors... */

  std::cout << "----------" << std::endl;
  std::cout << message.x << std::endl;
  std::cout << "----------" << std::endl;
  std::cout << message.y << std::endl;
  std::cout << "----------" << std::endl;
  std::cout << message.sw << std::endl;
  std::cout << "----------" << std::endl;
//   // Here we assume we received ASCII data, but you might be sending raw bytes (in that case, don't try and
//   // print it to the screen like this!)

  // halloArduino(serial_port);
 }
  // close(serial_port);
}
