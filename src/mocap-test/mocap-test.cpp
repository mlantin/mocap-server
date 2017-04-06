#include "VRCom.pb.h"
// UDP CLIENT WILL REPLACE "easywsclient.hpp"
#include "holojam_generated.h"
#include "easywsclient.hpp"
#include "smallUDPClient.hpp"
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <math.h>
#include <chrono>
#include <thread>
#include <string>
#include <iostream>
#include <sstream>
#include <cassert>

using namespace Holojam::Protocol;

int main(int argc, char* argv[]) {

	// UDP CLIENT REPLACES WebSocket easywsclient SETUP
  std::string host = "localhost";
  std::string port = "4567";

  // Create IO service
  boost::asio::io_service clientIoService;
  // Create UDP client
  smallUDPClient client(clientIoService, host, port);

  // This while loop prepares the test data and then sends it over the relay.
  const double PI = 2*acos(0.0);
  float angle;

  while(true) {

    for (int i = 0; i < 100; i++) {

      angle = 2*PI/100*i;

      // Create and init a FlatBufferBuilder
      flatbuffers::FlatBufferBuilder builder(1024);

      // Nugget Label
      auto flakeLabel = builder.CreateString("vec3");
      auto scop = builder.CreateString("IAA");
      auto orig = builder.CreateString("mocap-test");

      auto v3 = Vector3(sin(angle)*3000, cos(angle)*3000, 0);
      auto v4 = Vector4(0.9961946980917455, 0.08715574274765817, 0, 0);

      flatbuffers::Offset<flatbuffers::Vector<const Vector3 *>> vec3s_vector;
      std::vector<Vector3> array3;
      array3.reserve(1);
      array3.push_back(v3);
      auto vec3s = builder.CreateVectorOfStructs(array3);

      flatbuffers::Offset<flatbuffers::Vector<const Vector4 *>> vec4s_vector;
      std::vector<Vector4> array4;
      array4.reserve(1);
      array4.push_back(v4);
      auto vec4s = builder.CreateVectorOfStructs(array4);

      // create a flake:
      FlakeBuilder flake_builder(builder);
      flake_builder.add_label(flakeLabel);
      flake_builder.add_vector3s(vec3s_vector);
      flake_builder.add_vector4s(vec4s_vector);
      auto flak = flake_builder.Finish();

      std::vector<flatbuffers::Offset<Flake>> flake_vector;
      flake_vector.push_back(flak);
      auto flaks = builder.CreateVector(flake_vector);

      // create the nugget and finish the serialization:
      NuggetBuilder nugget_builder(builder);
      nugget_builder.add_scope(scop);
      nugget_builder.add_origin(orig);
      nugget_builder.add_flakes(flaks);
      auto nug = nugget_builder.Finish();
      builder.Finish(nug);

      //Buffer and it's size:
      uint8_t *buf = builder.GetBufferPointer();
      int bufsz = builder.GetSize();

      // Get nugget data tht was made above:
      auto ngt = GetNugget(buf);
      auto le = ngt->flakes()->Length();

      // UDP Client
      client.sendBinary(to_string(le));

       // MIRKO IS UNCERTAIN OF THE UTILITY OF THIS DELAY MECHANISM:
       std::this_thread::sleep_for(std::chrono::milliseconds(20));

    	}
    }
}
