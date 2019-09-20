#include "ESPino32_GCP.h"
#include <Arduino.h>
#include <WiFiClient.h>

/* ------- This is for ESPino send image to GCP -------- */

String ESPino32_GCP::sendImage(String message, uint8_t *data_pic, size_t size_pic){

	String bodyTxt =  body("message",message);
	String bodyPic =  body("imageFile",message);
	String bodyEnd =  String("--") + BOUNDARY + String("--\r\n");
	size_t allLen = bodyTxt.length() + bodyPic.length() + size_pic+bodyEnd.length();
	String headerTxt =  header(allLen);

	WiFiClient client;

	 if (!client.connect(HOST,PORT)){
		return("connection failed");
	 }

	 client.print(headerTxt + bodyTxt + bodyPic);
	 client.write(data_pic, size_pic);
	 client.print("\r\n" + bodyEnd);

	 delay(20);
	 long tOut = millis() + TIMEOUT;
	 while(client.connected() && tOut > millis())
	 {
		if (client.available())
		{
			String serverRes = client.readStringUntil('\r');
			 if(serverRes.indexOf("\"status\"")!=-1)
			{
				return(serverRes);
			}
		}
	 }
	 return("TimeOut");
}

String ESPino32_GCP::header(size_t length){

	String  data;

			data =  F("POST /upload HTTP/1.1\r\n");
			data += F("Content-Type: multipart/form-data; boundary=");
			data += BOUNDARY;
			data += "\r\n";
			data += F("Host: ");
			data += HOST;
			data += F(":");
			data += PORT;
			data += F("\r\n");
			data += F("accept-encoding: gzip, deflate\r\n");
			data += F("Connection: keep-alive\r\n");
			data += F("content-length: ");
			data += String(length);
			data += "\r\n";
			data += "\r\n";

    Serial.println(data);

    return(data);
}

String ESPino32_GCP::body(String content , String message){

	String data;
	data = "--";
	data += BOUNDARY;
	data += F("\r\n");
	if(content=="imageFile")
	{
		data += F("Content-Disposition: form-data; name=\"image\"; filename=\"picture.jpg\"\r\n");
		data += F("Content-Type: image/jpg\r\n");
		data += F("\r\n");
	}
	else
	{
		data += "Content-Disposition: form-data; name=\"" + content +"\"\r\n";
		data += "\r\n";
		data += message;
		data += "\r\n";
	}

  Serial.println(data);

	 return(data);
}
