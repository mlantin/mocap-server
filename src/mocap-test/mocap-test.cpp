#include "holojam_generated.h"
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

  std::string host = "127.0.0.1";
  std::string port = "9592";

  // Create IO service
  boost::asio::io_service clientIoService;
  // Create UDP client
  smallUDPClient client(clientIoService, host, port);

  const double PI = 2*acos(0.0);
  float angle;

  while(true) {

    for (int i = 0; i < 100; i++) {

      angle = 2*PI/100*i;

      // Create and init a FlatBufferBuilder
      flatbuffers::FlatBufferBuilder builder(1024);

      // Create Nugget fields and flake's label field:
      auto flakeLabel = builder.CreateString("vec3");
      auto scop = builder.CreateString("IAA");
      auto orig = builder.CreateString("mocap-test");

      // Create the Vector3 and Vector4 structs.
      auto v3 = Vector3(sin(angle)*3000, cos(angle)*3000, 0);
      auto v4 = Vector4(0.9961946980917455, 0.08715574274765817, 0, 0);

      // Build the vector of Vector3 structs:
      flatbuffers::Offset<flatbuffers::Vector<const Vector3 *>> vec3s_vector;
      std::vector<Vector3> array3;
      array3.reserve(1);
      array3.push_back(v3);
      auto vec3s = builder.CreateVectorOfStructs(array3);

      // // Build the vector of Vector4 structs:
      flatbuffers::Offset<flatbuffers::Vector<const Vector4 *>> vec4s_vector;
      std::vector<Vector4> array4;
      array4.reserve(1);
      array4.push_back(v4);
      auto vec4s = builder.CreateVectorOfStructs(array4);

      // Build a flake:
      FlakeBuilder flake_builder(builder);
      flake_builder.add_label(flakeLabel);
      flake_builder.add_vector3s(vec3s_vector);
      flake_builder.add_vector4s(vec4s_vector);
      auto flak = flake_builder.Finish();

      // Build the vector of flakes:
      std::vector<flatbuffers::Offset<Flake>> flake_vector;
      flake_vector.push_back(flak);
      auto flaks = builder.CreateVector(flake_vector);

      // Build the nugget and finish the serialization:
      NuggetBuilder nugget_builder(builder);
      nugget_builder.add_scope(scop);
      nugget_builder.add_origin(orig);
      nugget_builder.add_flakes(flaks);
      auto nug = nugget_builder.Finish();
      builder.Finish(nug);

      // Retrieve the Buffer and it's size:
      uint8_t *buf = builder.GetBufferPointer();
      int bufsz = builder.GetSize();

      // Get nugget data tht was made above:
      auto ngt = GetNugget(buf);
      auto le = ngt->flakes()->Length();

      // UDP Client
      // client.sendBinaryString(to_string(le));
      client.sendBinaryBuffer(buf, bufsz);

      // Prevents too much (?) data ... :
      std::this_thread::sleep_for(std::chrono::milliseconds(20));

    	}
    }
}
