#include <TridentTD_LineNotify.h>
#include <OV2640.h>     // ติดตั้ง library กล้องให้เรียบร้อย https://github.com/LilyGO/ESP32-Camera

#define SSID        "--------------------"
#define PASSWORD    "--------------------"
#define LINE_TOKEN  "--------------------"

// เลือก ESP32 + Camera Module อย่างใดอย่างหนึ่ง
#define ESP32CAM            1      // CAMERA_MODEL_AI_THINKER
//#define TTGO_T_JOURNAL      1

OV2640 cam;

bool CameraLineNotify();

void setup() {
  Serial.begin(115200); Serial.println();

  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting to %s\n",  SSID);
  while(WiFi.status() != WL_CONNECTED) { Serial.print("."); delay(400); }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());  

  LINE.setToken(LINE_TOKEN);

  camera_config_t camera_config;
  
#if ESP32CAM

      camera_config.ledc_channel  = LEDC_CHANNEL_0;
      camera_config.ledc_timer    = LEDC_TIMER_0;
      camera_config.pin_d0        = 5;
      camera_config.pin_d1        = 18;
      camera_config.pin_d2        = 19;
      camera_config.pin_d3        = 21;
      camera_config.pin_d4        = 36;
      camera_config.pin_d5        = 39;
      camera_config.pin_d6        = 34;
      camera_config.pin_d7        = 35;
      camera_config.pin_xclk      = 0;
      camera_config.pin_pclk      = 22;
      camera_config.pin_vsync     = 25;
      camera_config.pin_href      = 23;
      camera_config.pin_sscb_sda  = 26;
      camera_config.pin_sscb_scl  = 27;
      camera_config.pin_reset     = -1;
      camera_config.xclk_freq_hz  = 20000000;
      camera_config.pixel_format  = CAMERA_PF_JPEG;
      camera_config.frame_size    = CAMERA_FS_QQVGA; // CAMERA_FS_QVGA CAMERA_FS_QQVGA  CAMERA_FS_VGA  CAMERA_FS_SVGA;

#elif TTGO_T_JOURNAL

      camera_config.ledc_channel  = LEDC_CHANNEL_0;
      camera_config.ledc_timer    = LEDC_TIMER_0;
      camera_config.pin_d0        = 17;
      camera_config.pin_d1        = 35;
      camera_config.pin_d2        = 34;
      camera_config.pin_d3        = 5;
      camera_config.pin_d4        = 39;
      camera_config.pin_d5        = 18;
      camera_config.pin_d6        = 36;
      camera_config.pin_d7        = 19;
      camera_config.pin_xclk      = 27;
      camera_config.pin_pclk      = 21;
      camera_config.pin_vsync     = 22;
      camera_config.pin_href      = 26;
      camera_config.pin_sscb_sda  = 25;
      camera_config.pin_sscb_scl  = 23;
      camera_config.pin_reset     = 15;
      camera_config.xclk_freq_hz  = 20000000;
      camera_config.pixel_format  = CAMERA_PF_JPEG;
      camera_config.frame_size    = CAMERA_FS_SVGA; // CAMERA_FS_QVGA CAMERA_FS_QQVGA  CAMERA_FS_VGA  CAMERA_FS_SVGA;
#endif

  cam.init(camera_config);

  delay(1000);  // wait a while for camera inner-setting

  CameraLineNotify();
}

void loop() {
}

bool CameraLineNotify(){
  cam.run();
  uint8_t *image_data = cam.getfb();
  size_t   image_size = cam.getSize();

  return LINE.notifyPicture( "Camera Capture", image_data, image_size);
}
