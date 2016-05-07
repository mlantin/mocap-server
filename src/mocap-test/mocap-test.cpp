#include "VRCom.pb.h"
#include "easywsclient.hpp"
#include <math.h>
#include <chrono>
#include <thread>
#include <iostream>
#include <sstream>
#include <cassert>

int main() {
	
  using easywsclient::WebSocket;
  WebSocket::pointer ws = WebSocket::from_url("ws://192.168.2.1:4567");
  assert(ws);

	std::ostringstream bufstr;
  VRCom::Update* msg = new VRCom::Update();
	VRCom::Mocap* mocap = new VRCom::Mocap();
  msg->set_allocated_mocap(mocap);
  VRCom::Mocap::Subject* subj = mocap->add_subjects();
  VRCom::Position* pos = new VRCom::Position();
  VRCom::Rotation* rot = new VRCom::Rotation();
  subj->set_name("test");
  subj->set_allocated_rot(rot);
  subj->set_allocated_pos(pos);

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

       msg->SerializeToOstream(&bufstr);

       ws->sendBinary(bufstr.str());
       ws->poll();

       std::ostringstream().swap(bufstr);
       bufstr.clear();

       std::this_thread::sleep_for(std::chrono::milliseconds(20));

    	}
    }
}