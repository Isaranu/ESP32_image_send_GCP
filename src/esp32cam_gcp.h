#ifndef ESPino32_GCP_H
#define ESPino32_GCP_H

#include <WiFi.h>
#include <WiFiClient.h>

#define HOST 		        "server-ip"
#define PORT            port
#define BOUNDARY 		    "--------------------------133747188241686651551404"
#define TIMEOUT         30000

class ESPino32_GCP{

public:
  String sendImage(String message, uint8_t *data_pic,size_t size_pic);

private:
	String header(size_t length);
	String body(String content,String message);
	String sendData(String data);
};

#endif
