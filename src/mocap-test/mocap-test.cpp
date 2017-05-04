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


// These simulates multiple mocap subjects;
// these will be the strings bound to the "origin"
std::string FirstPlayerSim = "PIXEL1";
std::string SecondPlayerSim = "PlayerR";
std::string ThirdPlayerSim = "PlayerS";
std::string scope = "Vicon-Test";
std::string origin = "Update";

// UDP CLIENT REPLACES WebSocket easywsclient SETUP
std::string host = "0.0.0.0";
std::string port = "9592";

// Create IO service
boost::asio::io_service clientIoService;
// Create UDP client
smallUDPClient client(clientIoService, host, port);

const double PI = 2*acos(0.0);

void sendTranslationData(std::string scope, std::string subject) {

  float angle;

  for (int i = 0; i < 1000; i++) {

    angle = 2*PI/100*i;

    // Create and init a FlatBufferBuilder
    flatbuffers::FlatBufferBuilder builder(1024);

    // Create Nugget fields and flake's label field:
    auto flakeLabel = builder.CreateString(subject);
    auto scop = builder.CreateString(scope);
    auto orig = builder.CreateString(origin);

    float xa = sin(angle)*.5*1.0f;
    float ya = cos(angle)*.5*1.0f;

    // Create the Vector3 and Vector4 structs.
    auto v3 = Vector3(xa, ya, 2.0f);
    auto v4 = Vector4(0.9961946980917455, 0.08715574274765817, 0, 0);

    // Build the vector of Vector3 structs:
    std::vector<Vector3> array3;
    array3.reserve(1);
    array3.push_back(v3);
    auto vec3s = builder.CreateVectorOfStructs(array3);


    // // Build the vector of Vector4 structs:
    std::vector<Vector4> array4;
    array4.reserve(1);
    array4.push_back(v4);
    auto vec4s = builder.CreateVectorOfStructs(array4);

    // Build a flake:
    FlakeBuilder flake_builder(builder);
    flake_builder.add_label(flakeLabel);
    flake_builder.add_vector3s(vec3s);
    flake_builder.add_vector4s(vec4s);
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
    auto v3x = ngt->flakes()->Get(0)->vector3s()->Get(0)->x();
    auto v3y = ngt->flakes()->Get(0)->vector3s()->Get(0)->y();
    auto v3z = ngt->flakes()->Get(0)->vector3s()->Get(0)->z();

    printf("%f, %f, %f\n\n", v3x, v3y, v3z);

    // UDP Client
    // client.sendBinaryString(to_string(le));
    client.sendBinaryBuffer(buf, bufsz);

    // Prevents too much (?) data ... :
    std::this_thread::sleep_for(std::chrono::milliseconds(15));

    }
}

int main(int argc, char* argv[]) {

  while(true) {

    sendTranslationData(scope, FirstPlayerSim);

  }
  return 0;
}
