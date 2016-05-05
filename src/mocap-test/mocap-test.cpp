#include "VRCom.pb.h"
#include "sioclient/include/sio_client.h"
#include <math.h>
#include <chrono>
#include <thread>
#include <iostream>
#include <sstream>

int main() {
	sio::client ws;
	ws.connect("ws://192.168.2.1:4567/socket.io/?EIO=4&transport=websocket");

	std::ostringstream bufstr;
	VRCom::Mocap* mocap = new VRCom::Mocap();
    VRCom::Position* pos = new VRCom::Position();
    VRCom::Rotation* rot = new VRCom::Rotation();
    mocap->set_allocated_rot(rot);
    mocap->set_allocated_pos(pos);

    const double PI = 2*acos(0.0); 
    float angle;
    while(true) {
    	for (int i = 0; i < 100; i++) {
    	  angle = 2*PI/100*i;
    	  pos->set_x(sin(angle)*3);
          pos->set_y(cos(angle)*3);
          pos->set_z(0);

          rot->set_x(0);
          rot->set_y(0);
          rot->set_z(0);
          rot->set_w(1);

          mocap->set_name("test");

          mocap->SerializeToOstream(&bufstr);

          ws.socket()->emit("mocap", std::make_shared<std::string>(bufstr.str()));
          std::ostringstream().swap(bufstr);
          bufstr.clear();

          std::this_thread::sleep_for(std::chrono::milliseconds(60));

    	}
    }
}