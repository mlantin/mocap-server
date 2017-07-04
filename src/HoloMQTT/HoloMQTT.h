#include "mosquittopp.h"

class HoloMQTT : public mosqpp::mosquittopp {
  bool connected;

  public:
    HoloMQTT(const char* id, const char* host, int port);
    ~HoloMQTT();

 	bool isConnected() {return connected;}

    void on_connect(int rc);
    void on_disconnect(int rc);

    void send(uint8_t *buf, int bufsize); 

	void outputError(int rc);
};