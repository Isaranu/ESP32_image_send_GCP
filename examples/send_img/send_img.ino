#include "esp32cam_gcp.h"
#include "Camera_Exp.h"

CAMERA cam;

const char* ssid = "";    //  your network SSID (name)
const char* pass = "";   // your network password

ESPino32_GCP espino32;

void setup()
{
  Serial.begin(115200);
  Serial.println("\r\nHello ESPino32 capture image to GCP !");

  cam.setFrameSize(CAMERA_FS_QVGA);
  cam.setMirror(false);
  cam.setVflip(false);
  cam.setWhiteBalance(true);

  esp_err_t err = cam.init();
  if (err != ESP_OK)
  {
    Serial.println("Camera init failed with error =" + String( err));
    return;
  }

  WiFi.begin(ssid, pass);
  unsigned char led_cnt=0;
  while (WiFi.status() != WL_CONNECTED)
  {
     Serial.print(".");
     delay(200);
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop(){

      String res;

      Serial.println("Send Picture");
      esp_err_t err;
      err = cam.capture();
      if (err == ESP_OK)
      {
        res = espino32.sendImage("Take Picture",cam.getfb(),cam.getSize());
        Serial.println(res);
      }
      else
        Serial.println("Camera Error");

      delay(60000); 
}
