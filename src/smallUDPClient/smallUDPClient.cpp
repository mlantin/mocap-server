#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::udp;
using namespace std;

class smallUDPClient {

private:
  boost::asio::io_service& io_service_;
  udp::socket udp_socket_;
  udp::endpoint client_endpoint_;

public:
  // constructor creates the necessary boost objects for a udp client:
  smallUDPClient( boost::asio::io_service& io_service, const string& host, const string& port ) : io_service_(io_service), udp_socket_(io_service, udp::endpoint(udp::v4(), 0)) {
    udp::resolver resolver(io_service_);
    udp::resolver::query query(udp::v4(), host, port);
    udp::resolver::iterator iter = resolver.resolve(query);
    client_endpoint_ = *iter;
  }

  // destructor must take care of closing the socket:
  ~smallUDPClient() {
    udp_socket_.close();
  }

  void sendBinaryBuffer(uint8_t* buf, int size) {
    udp_socket_.send_to(boost::asio::buffer(buf, size), client_endpoint_);
  }

  void sendBinaryString(const string& s) {
    udp_socket_.send_to(boost::asio::buffer(s, s.size()), client_endpoint_);
  }

};
