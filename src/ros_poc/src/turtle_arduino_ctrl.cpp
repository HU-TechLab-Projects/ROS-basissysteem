#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "native_nanocom.hpp"
#include "simple.pb.h"
#include <sstream>

float controllertoturtle(int controllervalue, float speedscale = 1.f){
    // project the value that the controller gives (range 0 to 4096) to a value that turtlesim can use (range 1 to -1 times the speedscale)
    float newval = (((static_cast<float>(controllervalue) - 0.f) * (1.f  - -1.f )) / (4096.f - 0.f)) + -1.f;

    // deadzone check. limit the values given to the turtle so it doesnt move while the controller is not touched.
    // deadzone values are specific to the controller i used obtained by looking at the values returned while the controller was in neutral.
        float deadzone_max = 0.001;
        float deadzone_min = -0.003;
        
        if((newval < deadzone_max) && (newval > deadzone_min)){
            return 0.f;        
        }

        return newval * speedscale;

}

int main(int argc, char **argv){
    
    auto comm = nanocom<>("/dev/ttyACM0", B115200);
    constexpr char hallo[] = "cont\0";
    ros::init(argc,argv,"arduino_turtle_ctl");
    ros::NodeHandle n;

    ros::Publisher chatter_pub = n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);

    ros::Rate loop_rate(10);
    
    while(ros::ok()&&comm.status){
        geometry_msgs::Twist msg;
        
          
        Controller controller_msg = Controller_init_zero;
        command command_msg       = command_init_zero;

        strncpy(command_msg.command, hallo, sizeof(command_msg.command));

        comm.send_message(&command_msg,command_fields);
        comm.receive_message(&controller_msg, Controller_fields);

        msg.linear.x = controllertoturtle(controller_msg.x, 2.f);
        msg.angular.z = controllertoturtle(controller_msg.y,2.f) * -1;


        chatter_pub.publish(msg);
        loop_rate.sleep();
  
    }
    return 0;
}
