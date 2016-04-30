#include "Vicon/Client.h"

#include "sioclient/include/sio_client.h"
#include <iostream>
#include <fstream>
#include <cassert>
#include <ctime>
#include <stdio.h>
#include <string>


using namespace ViconDataStreamSDK::CPP;

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

int main( int argc, char* argv[] )
{
  // Program options
  
  std::string HostName = "localhost:801";
  if( argc > 1 )
  {
    HostName = argv[1];
  }

  std::string LogFile = "";
  std::string MulticastAddress = "244.0.0.0:44801";
  bool ConnectToMultiCast = false;
  bool EnableMultiCast = false;
  for(int a=2; a < argc; ++a)
  {
    std::string arg = argv[a];
    if(arg == "--help")
    {
      std::cout << argv[0] << " <HostName>: allowed options include:\n  --log_file <LogFile> --enable_multicast <MulticastAddress:Port> --connect_to_multicast <MulticastAddress:Port> --help" << std::endl;
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
    else if (arg=="--enable_multicast")
    {
      EnableMultiCast = true;
      if(a < argc)
      {
        MulticastAddress = argv[a+1];
        std::cout << "Enabling multicast address <"<< MulticastAddress << "> ..." << std::endl;
        ++a;
      }
    }
    else if (arg=="--connect_to_multicast")
    {
      ConnectToMultiCast = true;
      if(a < argc)
      {
        MulticastAddress = argv[a+1];
        std::cout << "connecting to multicast address <"<< MulticastAddress << "> ..." << std::endl;
        ++a;
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
      if(ConnectToMultiCast)
      {
        // Multicast connection
        ok = ( MyClient.ConnectToMulticast( HostName, MulticastAddress ).Result == Result::Success );

      }
      else
      {
        ok =( MyClient.Connect( HostName ).Result == Result::Success );
      }
      if(!ok)
      {
        std::cout << "Warning - connect failed..." << std::endl;
      }

      std::cout << ".";
  #ifdef WIN32
      Sleep( 200 );
  #else
      sleep(1);
  #endif
    }

    // Connect to vr websocket server

    sio::client wsvr;
    wsvr.connect("ws://192.168.11.67:4567/socket.io/?EIO=4&transport=websocket");

    // set up the data structure for sending data to wsvr
    sio::message::ptr msg = sio::array_message::create();

    std::cout << std::endl;

    // Enable some different data types
    MyClient.EnableSegmentData();
    MyClient.EnableMarkerData();
    MyClient.EnableUnlabeledMarkerData();
    MyClient.EnableDeviceData();

    std::cout << "Segment Data Enabled: "          << Adapt( MyClient.IsSegmentDataEnabled().Enabled )         << std::endl;
    std::cout << "Marker Data Enabled: "           << Adapt( MyClient.IsMarkerDataEnabled().Enabled )          << std::endl;
    std::cout << "Unlabeled Marker Data Enabled: " << Adapt( MyClient.IsUnlabeledMarkerDataEnabled().Enabled ) << std::endl;
    std::cout << "Device Data Enabled: "           << Adapt( MyClient.IsDeviceDataEnabled().Enabled )          << std::endl;

    // Set the streaming mode
    //MyClient.SetStreamMode( ViconDataStreamSDK::CPP::StreamMode::ClientPull );
    // MyClient.SetStreamMode( ViconDataStreamSDK::CPP::StreamMode::ClientPullPreFetch );
    MyClient.SetStreamMode( ViconDataStreamSDK::CPP::StreamMode::ServerPush );

    // Set the global up axis
    MyClient.SetAxisMapping( Direction::Forward, 
                             Direction::Left, 
                             Direction::Up ); // Z-up
    // MyClient.SetGlobalUpAxis( Direction::Forward, 
    //                           Direction::Up, 
    //                           Direction::Right ); // Y-up

    Output_GetAxisMapping _Output_GetAxisMapping = MyClient.GetAxisMapping();
    std::cout << "Axis Mapping: X-" << Adapt( _Output_GetAxisMapping.XAxis ) 
                           << " Y-" << Adapt( _Output_GetAxisMapping.YAxis ) 
                           << " Z-" << Adapt( _Output_GetAxisMapping.ZAxis ) << std::endl;

    // Discover the version number
    Output_GetVersion _Output_GetVersion = MyClient.GetVersion();
    std::cout << "Version: " << _Output_GetVersion.Major << "." 
                             << _Output_GetVersion.Minor << "." 
                             << _Output_GetVersion.Point << std::endl;

    if( EnableMultiCast )
    {
      assert( MyClient.IsConnected().Connected );
      MyClient.StartTransmittingMulticast( HostName, MulticastAddress );
    }

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
      output_stream << "Waiting for new frame...";
      while( MyClient.GetFrame().Result != Result::Success )
      {
        // Sleep a little so that we don't lumber the CPU with a busy poll
        #ifdef WIN32
          Sleep( 200 );
        #else
          sleep(1);
        #endif

        output_stream << ".";
      }
      output_stream << std::endl;
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
      output_stream << "Frame Number: " << _Output_GetFrameNumber.FrameNumber << std::endl;

      Output_GetFrameRate Rate = MyClient.GetFrameRate();
      std::cout << "Frame rate: "           << Rate.FrameRateHz          << std::endl;
      // Get the timecode
      Output_GetTimecode _Output_GetTimecode  = MyClient.GetTimecode();

      output_stream << "Timecode: "
                << _Output_GetTimecode.Hours               << "h "
                << _Output_GetTimecode.Minutes             << "m " 
                << _Output_GetTimecode.Seconds             << "s "
                << _Output_GetTimecode.Frames              << "f "
                << _Output_GetTimecode.SubFrame            << "sf "
                << Adapt( _Output_GetTimecode.FieldFlag ) << " " 
                << _Output_GetTimecode.Standard            << " " 
                << _Output_GetTimecode.SubFramesPerFrame   << " " 
                << _Output_GetTimecode.UserBits            << std::endl << std::endl;

      // Get the latency
      output_stream << "Latency: " << MyClient.GetLatencyTotal().Total << "s" << std::endl;
      
      for( unsigned int LatencySampleIndex = 0 ; LatencySampleIndex < MyClient.GetLatencySampleCount().Count ; ++LatencySampleIndex )
      {
        std::string SampleName  = MyClient.GetLatencySampleName( LatencySampleIndex ).Name;
        double      SampleValue = MyClient.GetLatencySampleValue( SampleName ).Value;

        output_stream << "  " << SampleName << " " << SampleValue << "s" << std::endl;
      }
      output_stream << std::endl;

      // Count the number of subjects
      unsigned int SubjectCount = MyClient.GetSubjectCount().SubjectCount;
      output_stream << "Subjects (" << SubjectCount << "):" << std::endl;
      for( unsigned int SubjectIndex = 0 ; SubjectIndex < SubjectCount ; ++SubjectIndex )
      {
        output_stream << "  Subject #" << SubjectIndex << std::endl;

        // Get the subject name
        std::string SubjectName = MyClient.GetSubjectName( SubjectIndex ).SubjectName;
        output_stream << "    Name: " << SubjectName << std::endl;

        // Get the root segment
        std::string RootSegment = MyClient.GetSubjectRootSegmentName( SubjectName ).SegmentName;
        output_stream << "    Root Segment: " << RootSegment << std::endl;

        // // Count the number of segments
        // unsigned int SegmentCount = MyClient.GetSegmentCount( SubjectName ).SegmentCount;
        // output_stream << "    Segments (" << SegmentCount << "):" << std::endl;
        // for( unsigned int SegmentIndex = 0 ; SegmentIndex < SegmentCount ; ++SegmentIndex )
        // {
        //   output_stream << "      Segment #" << SegmentIndex << std::endl;

        //   // Get the segment name
        //   std::string SegmentName = MyClient.GetSegmentName( SubjectName, SegmentIndex ).SegmentName;
        //   output_stream << "        Name: " << SegmentName << std::endl;

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

          // Get the global segment translation
          Output_GetSegmentGlobalTranslation _Output_GetSegmentGlobalTranslation = 
            MyClient.GetSegmentGlobalTranslation( SubjectName, RootSegment );
          output_stream << "        Global Translation: (" << _Output_GetSegmentGlobalTranslation.Translation[ 0 ]  << ", " 
                                                       << _Output_GetSegmentGlobalTranslation.Translation[ 1 ]  << ", " 
                                                       << _Output_GetSegmentGlobalTranslation.Translation[ 2 ]  << ") " 
                                                       << Adapt( _Output_GetSegmentGlobalTranslation.Occluded ) << std::endl;

          
          // Get the global segment rotation in quaternion co-ordinates
          Output_GetSegmentGlobalRotationQuaternion _Output_GetSegmentGlobalRotationQuaternion = 
            MyClient.GetSegmentGlobalRotationQuaternion( SubjectName, RootSegment );
          output_stream << "        Global Rotation Quaternion: (" << _Output_GetSegmentGlobalRotationQuaternion.Rotation[ 0 ]     << ", " 
                                                               << _Output_GetSegmentGlobalRotationQuaternion.Rotation[ 1 ]     << ", " 
                                                               << _Output_GetSegmentGlobalRotationQuaternion.Rotation[ 2 ]     << ", " 
                                                               << _Output_GetSegmentGlobalRotationQuaternion.Rotation[ 3 ]     << ") " 
                                                               << Adapt( _Output_GetSegmentGlobalRotationQuaternion.Occluded ) << std::endl;

          
          std::vector<sio::message::ptr> vec = msg->get_vector();
          vec.clear();
          vec.push_back(sio::string_message::create(SubjectName));
          vec.push_back(sio::double_message::create(_Output_GetSegmentGlobalTranslation.Translation[ 0 ]));
          vec.push_back(sio::double_message::create(_Output_GetSegmentGlobalTranslation.Translation[ 1 ]));
          vec.push_back(sio::double_message::create(_Output_GetSegmentGlobalTranslation.Translation[ 2 ]));
          vec.push_back(sio::double_message::create(_Output_GetSegmentGlobalRotationQuaternion.Rotation[ 0 ]));
          vec.push_back(sio::double_message::create(_Output_GetSegmentGlobalRotationQuaternion.Rotation[ 1 ]));
          vec.push_back(sio::double_message::create(_Output_GetSegmentGlobalRotationQuaternion.Rotation[ 2 ]));
          vec.push_back(sio::double_message::create(_Output_GetSegmentGlobalRotationQuaternion.Rotation[ 3 ]));

          wsvr.socket()->emit("obj", msg);
        //}

        // Count the number of markers
        unsigned int MarkerCount = MyClient.GetMarkerCount( SubjectName ).MarkerCount;
        output_stream << "    Markers (" << MarkerCount << "):" << std::endl;
        for( unsigned int MarkerIndex = 0 ; MarkerIndex < MarkerCount ; ++MarkerIndex )
        {
          // Get the marker name
          std::string MarkerName = MyClient.GetMarkerName( SubjectName, MarkerIndex ).MarkerName;

          // Get the marker parent
          std::string MarkerParentName = MyClient.GetMarkerParentName( SubjectName, MarkerName ).SegmentName;

          // Get the global marker translation
          Output_GetMarkerGlobalTranslation _Output_GetMarkerGlobalTranslation =
            MyClient.GetMarkerGlobalTranslation( SubjectName, MarkerName );

          output_stream << "      Marker #" << MarkerIndex            << ": "
                                        << MarkerName             << " ("
                                        << _Output_GetMarkerGlobalTranslation.Translation[ 0 ]  << ", "
                                        << _Output_GetMarkerGlobalTranslation.Translation[ 1 ]  << ", "
                                        << _Output_GetMarkerGlobalTranslation.Translation[ 2 ]  << ") "
                                        << Adapt( _Output_GetMarkerGlobalTranslation.Occluded ) << std::endl;
        }
      }
    }
      
      
    if( EnableMultiCast )
    {
      MyClient.StopTransmittingMulticast();
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

    //wsvr.close();
  }
}