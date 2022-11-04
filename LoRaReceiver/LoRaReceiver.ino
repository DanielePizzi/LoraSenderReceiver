// Libraries for LoRa
#include <SPI.h>
#include <LoRa.h>

// Libraries for OLED Display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// define the pins used by the LoRa transceiver module
#define LORA_SCK 5
#define LORA_MISO 19
#define LORA_MOSI 27
#define LORA_CS 18
#define LORA_RST 14
#define LORA_DIO0 26
#define LORA_DIO1 35
#define LORA_DIO2 34

// 433E6 for Asia
// 866E6 for Europe
// 915E6 for North America
#define LORA_BAND 866E6

// OLED pins
#define OLED_SDA 4
#define OLED_SCL 15
#define OLED_RST 16
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);

void onReceive(int packetSize)
{
  if (packetSize < 1)
    return;

  // received a packet
  Serial.print("Received packet '");

  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("LORA RECEIVER");
  display.setCursor(0, 20);
  display.print("Received packet:");

  // read packet
  String loRaData;
  loRaData.reserve(packetSize);
  for (int i = 0; i < packetSize; i++)
  {
    const char c = (char)LoRa.read();
    loRaData += c;
    Serial.print(c);
  }

  int rssi = LoRa.packetRssi();

  // Dsiplay information
  display.setCursor(0, 30);
  display.print(loRaData);
  display.setCursor(0, 50);
  display.print("RSSI:");
  display.setCursor(30, 50);
  String s (rssi);
  s += " dBm ";
  if (rssi > -30)
    s += "(++)";
  else if (rssi >= -60)
    s += "(+)";
  else if (rssi < -80)
    s += "(-)";
  else if (rssi < -110)
    s += "(--)";

  display.print(s);
  display.display();
}

void setup()
{
  // initialize Serial Monitor
  Serial.begin(115200);
  // Serial.begin(9600);
  while (!Serial)
    ;

  // reset OLED display via software
  pinMode(OLED_RST, OUTPUT);
  digitalWrite(OLED_RST, LOW);
  delay(20);
  digitalWrite(OLED_RST, HIGH);

  // initialize OLED
  Wire.begin(OLED_SDA, OLED_SCL);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3c, false, false))
  { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("LORA RECEIVER");
  display.display();

  Serial.println("LoRa Receiver Callback");

  // SPI LoRa pins
  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_CS);
  // setup LoRa transceiver module
  LoRa.setPins(LORA_CS, LORA_RST, LORA_DIO0);

  if (!LoRa.begin(LORA_BAND))
  {
    Serial.println("Starting LoRa failed!");
    display.clearDisplay();
    display.println("Starting LoRa failed!");
    display.display();
    while (1)
      ;
  }

  // Uncomment the next line to disable the default AGC and set LNA gain, values between 1 - 6 are supported
  // LoRa.setGain(6);

  Serial.println("LoRa Initializing OK!");
  display.setCursor(0, 10);
  display.println("LoRa Initializing OK!");
  display.display();

  // ----------------------------------
  // followed does not work
  // why?
  // ----------------------------------
  
  // register the receive callback
  //LoRa.onReceive(onReceive);
  // put the radio into receive mode
  //LoRa.receive();
}

void loop()
{
  onReceive(LoRa.parsePacket());
}
