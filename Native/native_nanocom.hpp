#ifndef NATIVE_NANOCOM_H
#define NATIVE_NANOCOM_H
// C library headers
#include <stdio.h>
// #include <string.h>
#include <string>

// Linux headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()
#include <iostream>

//C++ headers
#include <chrono>


// Protobuff heders
#include <pb_encode.h>
#include <pb_decode.h>

inline std::chrono::microseconds time_now_us(){
  return std::chrono::duration_cast< std::chrono::microseconds >(
    std::chrono::system_clock::now().time_since_epoch()
  );
}

template<uint32_t waittime_us = 100000>
class nanocom {
private:

  static bool read_callback(pb_istream_t *stream, uint8_t * buf, size_t count){
    ssize_t counter;
    size_t bytesReceived = 0;
    int port = (intptr_t)stream->state;
    // std::cout << count << std::endl;
    std::chrono::microseconds timestamp = time_now_us();
    while(bytesReceived < count){
      counter = read(port, buf + bytesReceived, count - bytesReceived);
      if (counter < 0){
        perror("Read Failed: ");
        return false;
      } else if (counter > 0){
        timestamp = time_now_us();
      }
      if ((time_now_us() - timestamp) > std::chrono::microseconds(waittime_us)){
        return false;
      }
      bytesReceived += counter;
    }
    return bytesReceived == count;
  }

  static bool write_callback(pb_ostream_t* stream, const uint8_t * buf, size_t count) {
    ssize_t counter;
    size_t bytesSent = 0;
    int port = (intptr_t)stream->state;
    while(bytesSent < count){
      counter = write(port, buf + bytesSent, count - bytesSent);
      if (counter < 0){
        perror("Write Failed: ");
        return false;
      }
      bytesSent += counter;
    }
    // std::cout << "writing" << std::endl;
    return bytesSent == count;
  }
  struct termios tty;
  pb_ostream_t out;
  pb_istream_t in;

public:
  int serial_port;

  nanocom(const std::string & fd = "/dev/ttyACM0",
          speed_t baud = B2400){ // speed_t defined in termios.h
    serial_port = open(fd.c_str(), O_RDWR);
    if(serial_port < 0){
      perror("error creating serial port: ");
    }
    memset(&tty, 0, sizeof(tty));
    if(tcgetattr(serial_port, &tty) != 0) {
      printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
    }
    tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
    tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
    tty.c_cflag |=  CS8; // 8 bits per byte (most common)
    tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
    tty.c_cflag |=  CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)
    tty.c_cflag &= ~HUPCL; //Turn off hangup to prevent reset on read write switch

    tty.c_lflag &= ~ICANON;
    tty.c_lflag &= ~ECHO; // Disable echo
    tty.c_lflag &= ~ECHOE; // Disable erasure
    tty.c_lflag &= ~ECHONL; // Disable new-line echo
    tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
    tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes

    tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
    tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
    // tty.c_oflag &= ~OXTABS; // Prevent conversion of tabs to spaces (NOT PRESENT ON LINUX)
    // tty.c_oflag &= ~ONOEOT; // Prevent removal of C-d chars (0x004) in output (NOT PRESENT ON LINUX)

    tty.c_cc[VTIME] = 0;    // dont wait nanopb handles this.
    tty.c_cc[VMIN]  = 0;

    //Set in out baud rate to be 2400
    cfsetispeed(&tty, baud);
    cfsetospeed(&tty, baud);

    // Save tty settings, also checking for errora
    if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
        printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
    }

    out = pb_ostream_t {&write_callback, (void*)(intptr_t)serial_port, SIZE_MAX, 0};
    in  = pb_istream_t {&read_callback,  (void*)(intptr_t)serial_port, SIZE_MAX, 0};
  }
  ~nanocom(){
    close(serial_port);
  }
  template<typename T, typename Y>
  bool send_message(T* message, Y* message_fields){
    bool status = pb_encode_delimited(&out, message_fields, message);
    if (!status){
      std::cout << "error while sending: " << PB_GET_ERROR(&out) << std::endl;
    }
    return status;
  }

  template<typename T, typename Y>
  bool receive_message(T* message, Y* message_fields){
    bool status =  pb_decode_delimited(&in, message_fields, message);
    if (!status){
      std::cout << "error while receiving: " << PB_GET_ERROR(&in) << std::endl;
    }
    return status;
  }
};

#endif /* NATIVE_NANOCOM_H */
