#!/usr/bin/env bash
FILE=~/variables.sh



sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'

sudo apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654


sudo apt update
yes | sudo apt install ros-melodic-desktop-full
sudo rosdep init
rosdep update
yes | sudo apt install python-rosinstall python-rosinstall-generator python-wstool build-essential mdns-scan
sudo systemctl enable avahi-daemon.service
sudo systemctl restart avahi-daemon.service
sudo usermod -a -G dialout $USER
if test -f "$FILE"; then
 echo "$FILE already exists"
 read -p "do you wish to overwrite it [y/n]? " -r
 echo
 if [[ $REPLY =~ ^[Yy]$ ]]; then
  echo "overwriting $FILE"
  rm $FILE
  touch $FILE
  echo "export ROS_MASTER_HOSTNAME=rosmaster" >> $FILE
  echo "export ROS_PORT=11311" >> $FILE
  chmod +x $FILE
 fi
else 
 echo "creating $FILE"
 touch $FILE
 echo "export ROS_MASTER_HOSTNAME=rosmaster" >> $FILE
 echo "export ROS_PORT=11311" >> $FILE
 chmod +x $FILE
fi


if ! cat ~/.bashrc | grep -q ros_sysvar_config ; then
 echo -e "#ros_sysvar_config\n" >> ~/.bashrc
 echo "source ~/variables.sh" >> ~/.bashrc
 echo "export ROS_MASTER_URI=http://\$ROS_MASTER_HOSTNAME.local:\$ROS_PORT" >> ~/.bashrc
 echo "export ROS_IP=\$HOSTNAME.local" >> ~/.bashrc
 echo "source /opt/ros/melodic/setup.bash" >> ~/.bashrc
 echo "echo ROS master uri: \$ROS_MASTER_URI" >> ~/.bashrc
 echo "echo Machine Adress: \$ROS_IP" >> ~/.bashrc
else
 echo "ros sysvars already in .bashrc"
fi
echo -e "\n\n\nTo complete update to the enviroment please run \"source ~/.bashrc\" or close this terminal and start a new one\n"
