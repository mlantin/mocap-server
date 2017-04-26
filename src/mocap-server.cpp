#include "Vicon/Client.h"
#include "easywsclient.hpp"
#include "smallUDPClient.hpp"
#include "holojam_generated.h"
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include "VRCom.pb.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <ctime>
#include <stdio.h>
#include <string>
#include <chrono>
#include <thread>
#include <math.h>

using namespace ViconDataStreamSDK::CPP;
using namespace Holojam::Protocol;

#define output_stream if(!LogFile.empty()) ; else std::cout

namespace
{
  std::string Adapt( const bool i_Value )
  {
    return i_Value ? "True" : "False";
  }

  std::string Adapt( const Direction::Enum i_Direction )
  {
    switch( i_Direction )
    {
      case Direction::Forward:
        return "Forward";
      case Direction::Backward:
        return "Backward";
      case Direction::Left:
        return "Left";
      case Direction::Right:
        return "Right";
      case Direction::Up:
        return "Up";
      case Direction::Down:
        return "Down";
      default:
        return "Unknown";
    }
  }

  std::string Adapt( const DeviceType::Enum i_DeviceType )
  {
    switch( i_DeviceType )
    {
      case DeviceType::ForcePlate:
        return "ForcePlate";
      case DeviceType::Unknown:
      default:
        return "Unknown";
    }
  }

  std::string Adapt( const Unit::Enum i_Unit )
  {
    switch( i_Unit )
    {
      case Unit::Meter:
        return "Meter";
      case Unit::Volt:
        return "Volt";
      case Unit::NewtonMeter:
        return "NewtonMeter";
      case Unit::Newton:
        return "Newton";
      case Unit::Kilogram:
        return "Kilogram";
      case Unit::Second:
        return "Second";
      case Unit::Ampere:
        return "Ampere";
      case Unit::Kelvin:
        return "Kelvin";
      case Unit::Mole:
        return "Mole";
      case Unit::Candela:
        return "Candela";
      case Unit::Radian:
        return "Radian";
      case Unit::Steradian:
        return "Steradian";
      case Unit::MeterSquared:
        return "MeterSquared";
      case Unit::MeterCubed:
        return "MeterCubed";
      case Unit::MeterPerSecond:
        return "MeterPerSecond";
      case Unit::MeterPerSecondSquared:
        return "MeterPerSecondSquared";
      case Unit::RadianPerSecond:
        return "RadianPerSecond";
      case Unit::RadianPerSecondSquared:
        return "RadianPerSecondSquared";
      case Unit::Hertz:
        return "Hertz";
      case Unit::Joule:
        return "Joule";
      case Unit::Watt:
        return "Watt";
      case Unit::Pascal:
        return "Pascal";
      case Unit::Lumen:
        return "Lumen";
      case Unit::Lux:
        return "Lux";
      case Unit::Coulomb:
        return "Coulomb";
      case Unit::Ohm:
        return "Ohm";
      case Unit::Farad:
        return "Farad";
      case Unit::Weber:
        return "Weber";
      case Unit::Tesla:
        return "Tesla";
      case Unit::Henry:
        return "Henry";
      case Unit::Siemens:
        return "Siemens";
      case Unit::Becquerel:
        return "Becquerel";
      case Unit::Gray:
        return "Gray";
      case Unit::Sievert:
        return "Sievert";
      case Unit::Katal:
        return "Katal";

      case Unit::Unknown:
      default:
        return "Unknown";
    }
  }
}

const double PI = 2*acos(0.0);

enum AxisOrientation {
    YUP,
    ZUP,
  };

int main( int argc, char* argv[] )
{
  // Program options

  //Vicon is a right-handed coordinate system with ZUP by default.
  //The server will output Right-Handed with Y UP (the OpenGL convention)
  AxisOrientation axes = ZUP;

  std::string HostName = "localhost:801";
  std::string WebsocketAddr = "ws://localhost:4567";

  int a = 1;

  if( argc > 1 )
  {
    HostName = argv[1];
    a = 2;
  }
  if (argc > 2) {
    WebsocketAddr = argv[2];
    a = 3;
  }

  std::string LogFile = "";

  for(; a < argc; ++a)
  {
    std::string arg = argv[a];
    if(arg == "--help")
    {
      std::cout << argv[0] << " <HostName> <websocket addr>: allowed options include:\n  --log_file <LogFile> --orient <ZUP | YUP> --help" << std::endl;
      return 0;
    }
    else if (arg=="--log_file")
    {
      if(a < argc)
      {
        LogFile = argv[a+1];
        std::cout << "Using log file <"<< LogFile << "> ..." << std::endl;
        ++a;
      }
    }
    else if (arg == "--orient") {
      if (a < argc) {
        std::string orient = argv[a+1];
        if (orient == "YUP")
          axes = YUP;
        a++;
      }
    }
    else
    {
      std::cout << "Failed to understand argument <" << argv[a] << ">...exiting" << std::endl;
      return 1;
    }
  }

  std::ofstream ofs;
  if(!LogFile.empty())
  {
    ofs.open(LogFile.c_str());
    if(!ofs.is_open())
    {
      std::cout << "Could not open log file <" << LogFile << ">...exiting" << std::endl;
      return 1;
    }
  }

  Client MyClient;

  // try to connect
  for(int i=0; i != 3; ++i) // repeat to check disconnecting doesn't wreck next connect
  {
    // Connect to a server
    std::cout << "Connecting to " << HostName << " ..." << std::flush;
    while( !MyClient.IsConnected().Connected )
    {
      // Direct connection

      bool ok = false;
      ok =( MyClient.Connect( HostName ).Result == Result::Success );
      if(!ok)
      {
        std::cout << "Warning - connect failed..." << std::endl;
      }

      std::cout << ".";
  #ifdef WIN32
      Sleep( 200 );
  #else
      std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  #endif
    }

    std::string playerOne = "Player";
    std::string playerTwo = "playerTwo";
    std::string host = "127.0.0.1";
    std::string port = "9592";

    // Create IO service
    boost::asio::io_service clientIoService;
    // Create UDP client
    smallUDPClient client(clientIoService, host, port);

    int numSubjects = 0;

    std::ostringstream bufstr;

    // Enable some different data types
    MyClient.EnableSegmentData();

    std::cout << "Segment Data Enabled: "          << Adapt( MyClient.IsSegmentDataEnabled().Enabled )         << std::endl;
    std::cout << "Marker Data Enabled: "           << Adapt( MyClient.IsMarkerDataEnabled().Enabled )          << std::endl;
    std::cout << "Unlabeled Marker Data Enabled: " << Adapt( MyClient.IsUnlabeledMarkerDataEnabled().Enabled ) << std::endl;
    std::cout << "Device Data Enabled: "           << Adapt( MyClient.IsDeviceDataEnabled().Enabled )          << std::endl;

    // Set the streaming mode
    //MyClient.SetStreamMode( ViconDataStreamSDK::CPP::StreamMode::ClientPull );
    // MyClient.SetStreamMode( ViconDataStreamSDK::CPP::StreamMode::ClientPullPreFetch );
    MyClient.SetStreamMode( ViconDataStreamSDK::CPP::StreamMode::ServerPush );

    //Set the coordinate system to the OpenGL system (X right, Y UP, Z Backward
    //Note: There is something off with the way Blade outputs data. Somehow it needs to start with
    //its default coordinate system (X Forward, Y Left, Z Up) so that the axis mapping works correctly.
    Output_SetAxisMapping _Output_SetAxisMapping =
      MyClient.SetAxisMapping( Direction::Right,
                               Direction::Up,
                               Direction::Backward ); // OpenGL

    std::cout << "Axis mapping result: " << _Output_SetAxisMapping.Result << std::endl;

    Output_GetAxisMapping _Output_GetAxisMapping = MyClient.GetAxisMapping();
    std::cout << "Axis Mapping: X-" << Adapt( _Output_GetAxisMapping.XAxis )
                           << " Y-" << Adapt( _Output_GetAxisMapping.YAxis )
                           << " Z-" << Adapt( _Output_GetAxisMapping.ZAxis ) << std::endl;

    // Discover the version number
    Output_GetVersion _Output_GetVersion = MyClient.GetVersion();
    std::cout << "Version: " << _Output_GetVersion.Major << "."
                             << _Output_GetVersion.Minor << "."
                             << _Output_GetVersion.Point << std::endl;


    // get the number of subjects and allocate the map.
    // We are assuming that the number and set of subjects won't change.
    // This may not be a great assumption. The alternative is to reallocate
    // at each frame or check if there are differences at each frame.


    size_t FrameRateWindow = 1000; // frames
    size_t Counter = 0;
    clock_t LastTime = clock();
    // Loop until a key is pressed
  #ifdef WIN32
    while( !Hit() )
  #else
    while( true)
  #endif
    {
      // Get a frame
      //output_stream << "Waiting for new frame...";
      while( MyClient.GetFrame().Result != Result::Success )
      {
        // Sleep a little so that we don't lumber the CPU with a busy poll
        #ifdef WIN32
          Sleep( 200 );
        #else
          std::this_thread::sleep_for(std::chrono::milliseconds(200));;
        #endif

        //output_stream << ".";
      }
      //output_stream << std::endl;
      if(++Counter == FrameRateWindow)
      {
        clock_t Now = clock();
        double FrameRate = (double)(FrameRateWindow * CLOCKS_PER_SEC) / (double)(Now - LastTime);
        if(!LogFile.empty())
        {
          time_t rawtime;
          struct tm * timeinfo;
          time ( &rawtime );
          timeinfo = localtime ( &rawtime );

          ofs << "Frame rate = " << FrameRate << " at " <<  asctime (timeinfo)<< std::endl;
        }

        LastTime = Now;
        Counter = 0;
      }

      // Get the frame number
      Output_GetFrameNumber _Output_GetFrameNumber = MyClient.GetFrameNumber();
      //output_stream << "Frame Number: " << _Output_GetFrameNumber.FrameNumber << std::endl;

      Output_GetFrameRate Rate = MyClient.GetFrameRate();
      //std::cout << "Frame rate: "           << Rate.FrameRateHz          << std::endl;
      // Get the timecode
      Output_GetTimecode _Output_GetTimecode  = MyClient.GetTimecode();

      // output_stream << "Timecode: "
      //           << _Output_GetTimecode.Hours               << "h "
      //           << _Output_GetTimecode.Minutes             << "m "
      //           << _Output_GetTimecode.Seconds             << "s "
      //           << _Output_GetTimecode.Frames              << "f "
      //           << _Output_GetTimecode.SubFrame            << "sf "
      //           << Adapt( _Output_GetTimecode.FieldFlag ) << " "
      //           << _Output_GetTimecode.Standard            << " "
      //           << _Output_GetTimecode.SubFramesPerFrame   << " "
      //           << _Output_GetTimecode.UserBits            << std::endl << std::endl;

      // Get the latency
  //output_stream << "Latency: " << MyClient.GetLatencyTotal().Total << "s" << std::endl;

      for( unsigned int LatencySampleIndex = 0 ; LatencySampleIndex < MyClient.GetLatencySampleCount().Count ; ++LatencySampleIndex )
      {
        std::string SampleName  = MyClient.GetLatencySampleName( LatencySampleIndex ).Name;
        double      SampleValue = MyClient.GetLatencySampleValue( SampleName ).Value;

        //output_stream << "  " << SampleName << " " << SampleValue << "s" << std::endl;
      }
      //output_stream << std::endl;

      // Count the number of subjects
      unsigned int SubjectCount = MyClient.GetSubjectCount().SubjectCount;
      // if (numSubjects != SubjectCount) {
      //   allocateSubjects(mocap, SubjectCount);
      //   numSubjects = SubjectCount;
      // }

      //output_stream << "Subjects (" << SubjectCount << "):" << std::endl;
      for( unsigned int SubjectIndex = 0 ; SubjectIndex < SubjectCount; ++SubjectIndex )
      {
        //output_stream << "  Subject #" << SubjectIndex << std::endl;

        // Get the subject name
        std::string SubjectName = MyClient.GetSubjectName( SubjectIndex ).SubjectName;
        // output_stream << "    Name: " << SubjectName << std::endl;

        std::cout << SubjectName << '\n';

        // Get the root segment
        std::string RootSegment = MyClient.GetSubjectRootSegmentName( SubjectName ).SegmentName;
        //output_stream << "    Root Segment: " << RootSegment << std::endl;

        // // Count the number of segments
        // unsigned int SegmentCount = MyClient.GetSegmentCount( SubjectName ).SegmentCount;
        // output_stream << "    Segments (" << SegmentCount << "):" << std::endl;
        // for( unsigned int SegmentIndex = 0 ; SegmentIndex < SegmentCount ; ++SegmentIndex )
        // {
        //   output_stream << "      Segment #" << SegmentIndex << std::endl;

        //   // Get the segment name
        //   std::string SegmentName = MyClient.GetSegmentName( SubjectName, SegmentIndex ).SegmentName;
           //output_stream << "        Name: " << SegmentName << std::endl;

        //   // Get the segment parent
        //   std::string SegmentParentName = MyClient.GetSegmentParentName( SubjectName, SegmentName ).SegmentName;
        //   output_stream << "        Parent: " << SegmentParentName << std::endl;

        //   // Get the segment's children
        //   unsigned int ChildCount = MyClient.GetSegmentChildCount( SubjectName, SegmentName ).SegmentCount;
        //   output_stream << "     Children (" << ChildCount << "):" << std::endl;
        //   for( unsigned int ChildIndex = 0 ; ChildIndex < ChildCount ; ++ChildIndex )
        //   {
        //     std::string ChildName = MyClient.GetSegmentChildName( SubjectName, SegmentName, ChildIndex ).SegmentName;
        //     output_stream << "       " << ChildName << std::endl;
        //   }

          // Get the Local segment translation
          Output_GetSegmentLocalTranslation _Output_GetSegmentLocalTranslation =
            MyClient.GetSegmentLocalTranslation( SubjectName, RootSegment );
          // output_stream << "        Local Translation: (" << _Output_GetSegmentLocalTranslation.Translation[ 0 ]  << ", "
          //                                              << _Output_GetSegmentLocalTranslation.Translation[ 1 ]  << ", "
          //                                              << _Output_GetSegmentLocalTranslation.Translation[ 2 ]  << ") "
          //                                              << Adapt( _Output_GetSegmentLocalTranslation.Occluded ) << std::endl;


          // Get the Local segment rotation in quaternion co-ordinates
          Output_GetSegmentLocalRotationQuaternion _Output_GetSegmentLocalRotationQuaternion =
            MyClient.GetSegmentLocalRotationQuaternion( SubjectName, RootSegment );
          // output_stream << "        Local Rotation Quaternion: (" << _Output_GetSegmentLocalRotationQuaternion.Rotation[ 0 ]     << ", "
          //                                                      << _Output_GetSegmentLocalRotationQuaternion.Rotation[ 1 ]     << ", "
          //                                                      << _Output_GetSegmentLocalRotationQuaternion.Rotation[ 2 ]     << ", "
          //                                                      << _Output_GetSegmentLocalRotationQuaternion.Rotation[ 3 ]     << ") "
          //                                                      << Adapt( _Output_GetSegmentLocalRotationQuaternion.Occluded ) << std::endl;

          Output_GetSegmentLocalRotationEulerXYZ _Output_Euler =
            MyClient.GetSegmentLocalRotationEulerXYZ(SubjectName, RootSegment);

          // output_stream << "        Local Rotation Euler: (" << _Output_Euler.Rotation[ 0 ]     << ", "
          //                                                      << _Output_Euler.Rotation[ 1 ]     << ", "
          //                                                      << _Output_Euler.Rotation[ 2 ]     << ") " << std::endl;

          if ((SubjectName != "Wii") ){

            auto v3x = _Output_GetSegmentLocalTranslation.Translation[ 0 ];
            auto v3y = _Output_GetSegmentLocalTranslation.Translation[ 1 ];
            auto v3z = _Output_GetSegmentLocalTranslation.Translation[ 2 ];

            auto v4x = _Output_GetSegmentLocalRotationQuaternion.Rotation[ 0 ];
            auto v4y = _Output_GetSegmentLocalRotationQuaternion.Rotation[ 1 ];
            auto v4z = _Output_GetSegmentLocalRotationQuaternion.Rotation[ 2 ];
            auto v4w = _Output_GetSegmentLocalRotationQuaternion.Rotation[ 3 ];

            // Create and init a FlatBufferBuilder
            flatbuffers::FlatBufferBuilder builder(1024);

            // Create Nugget fields and flake's label field:
            auto flakeLabel = builder.CreateString("vec3");
            auto scop = builder.CreateString("IAA");

            auto orig = builder.CreateString(SubjectName);

            // if(SubjectName == "PIXEL1"){
            //   orig = builder.CreateString(playerTwo);
            // }

            // Create the Vector3 and Vector4 structs.
            auto v3 = Vector3(v3x, v3y, v3z);
            auto v4 = Vector4(v4x, v4y, v4z, v4w);

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
            auto vec3x = ngt->flakes()->Get(0)->vector3s()->Get(0)->x();
            auto vec3y = ngt->flakes()->Get(0)->vector3s()->Get(0)->y();
            auto vec3z = ngt->flakes()->Get(0)->vector3s()->Get(0)->z();

            // TODO: REMEMBER TO REMOVE DEBUG LOGGING BELOW WHEN NEEDED:
            printf("%f, %f, %f\n\n", vec3x, vec3y, vec3z);

            // UDP Client
            // client.sendBinaryString(to_string(le));
            client.sendBinaryBuffer(buf, bufsz);

            std::this_thread::sleep_for(std::chrono::milliseconds(5));

          }

      }

    }

    MyClient.DisableSegmentData();
    MyClient.DisableMarkerData();
    MyClient.DisableUnlabeledMarkerData();
    MyClient.DisableDeviceData();

    // Disconnect and dispose
    int t = clock();
    std::cout << " Disconnecting..." << std::endl;
    MyClient.Disconnect();
    int dt = clock() - t;
    double secs = (double) (dt)/(double)CLOCKS_PER_SEC;
    std::cout << " Disconnect time = " << secs << " secs" << std::endl;

    // The commented out version below is from the prior webosocket version
    // of the server that uses protobuffers
    // ws->close();
  }
}
