#ifndef DUE_NANOCOM_H
#define DUE_NANOCOM_H
#include <pb_encode.h>
#include <pb_decode.h>
#include <string.h>
#include "hwlib.hpp"

template<uint32_t waittime_us = 100000>
class nanocom {
private:

  static bool write_callback(pb_ostream_t *stream, const uint8_t *buf, size_t count){
    size_t counter = 0;
    while(counter < count){
      hwlib::cout << (char)buf[counter];
      counter++;
    }
    return (counter == count);
  }

  static bool read_callback(pb_istream_t *stream, uint8_t *buf, size_t count){
    size_t bytesReceived = 0;
    char tmp;
    uint32_t timestamp = hwlib::now_us();
    while (bytesReceived < count){
      tmp = '\0';
      if (hwlib::uart_char_available()){
        hwlib::cin >> tmp;
        *(buf+bytesReceived) = tmp;
        bytesReceived++;
        timestamp = hwlib::now_us();
      }
      else if((hwlib::now_us() - timestamp) > waittime_us){
        return false; // didnt receive a character for on time
      }
    }
    return bytesReceived == count;
  }

  pb_ostream_t out = {&write_callback, (void*)(intptr_t)NULL, SIZE_MAX, 0};
  pb_istream_t in  = {&read_callback, (void*)(intptr_t)NULL, SIZE_MAX, 0};

public:

  nanocom(){}

  template<typename T, typename Y>
  bool send_message(T* message, Y* message_fields){
    bool status = pb_encode_delimited(&out, message_fields, message);
    if (!status){
      //hwlib::cout << "error while sending: " << PB_GET_ERROR(&out) << hwlib::endl;
    }
    return status;
  }

  template<typename T, typename Y>
  bool receive_message(T* message, Y* message_fields){
    bool status =  pb_decode_delimited(&in, message_fields, message);
    if (!status){
      //hwlib::cout << "error while receiving: " << PB_GET_ERROR(&in) << hwlib::endl;
    }
    return status;
  }
};

#endif /* DUE_NANOCOM_H */
