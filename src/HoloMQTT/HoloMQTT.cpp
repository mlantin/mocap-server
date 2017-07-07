#include <iostream>
#include <cstdio>
#include <cstring>
#include <unistd.h>

#include "HoloMQTT.h"

HoloMQTT::HoloMQTT(const char *id, 
                   const char *host, 
                   int port ) : mosquittopp(id) {
    int keepalive = 60;

    connected = false; // Gets set in on_connected()

    connect(host, port, keepalive);

    loop_start();
};

HoloMQTT::~HoloMQTT() {
	loop_stop();            // Kill the thread
	mosqpp::lib_cleanup();    // Mosquitto library cleanup
}

void HoloMQTT::on_disconnect(int rc) {
	std::cout << ">> HoloMQTT - disconnection(" << rc << ")" << std::endl;
	connected = false;
}

void HoloMQTT::on_connect(int rc) {
	if ( rc == 0 ) {
		std::cout << ">> HoloMQTT - connected with server" << std::endl;
		connected = true;
 	} else {
 		std::cout << ">> HoloMQTT - Impossible to connect with server(" << rc << ")" << std::endl;
 	}
 }

void HoloMQTT::send(uint8_t *buf, int bufsize, std::string topic) {
	if (!connected)
		return;

	int rc = publish(NULL, topic.c_str(), bufsize, buf);
	if ( rc != MOSQ_ERR_SUCCESS ) {
		printf("PUBLISH Failed: ");
		outputError(rc);
	}
}

 void HoloMQTT::outputError(int rc) {
	switch ( rc ) {
	case MOSQ_ERR_INVAL:
		printf("ERROR: MOSQ_ERR_INVAL\n");
		break;
	case MOSQ_ERR_NOMEM:
		printf("ERROR: MOSQ_ERR_NOMEM\n");
		break;
	case MOSQ_ERR_NO_CONN:
		printf("ERROR: MOSQ_ERR_NO_CONN\n");
		break;
	case MOSQ_ERR_CONN_LOST:
		printf("ERROR: MOSQ_ERR_CONN_LOST\n");
		break;
	case MOSQ_ERR_PROTOCOL:
		printf("ERROR: MOSQ_ERR_PROTOCOL\n");
		break;
	case MOSQ_ERR_ERRNO:
		printf("ERROR: MOSQ_ERR_ERRNO: \n");
		break;
	default:
		printf("ERROR: %d \n", rc);
	}
}




