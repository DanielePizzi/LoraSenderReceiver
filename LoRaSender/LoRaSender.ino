/* Heltec Automation send communication test example
 *
 * Function:
 * 1. Send data from a CubeCell device over hardware 
 * 
 * 
 * this project also realess in GitHub:
 * https://github.com/HelTecAutomation/ASR650x-Arduino
 * */

#include "LoRaWan_APP.h"
#include "Arduino.h"

#include "GPS_Air530.h"
#include "GPS_Air530Z.h"

//if GPS module is Air530, use this
//Air530Class GPS;

//if GPS module is Air530Z, use this
Air530ZClass GPS;

/*
 * set LoraWan_RGB to 1,the RGB active in loraWan
 * RGB red means sending;
 * RGB green means received done;
 */
#ifndef LoraWan_RGB
#define LoraWan_RGB 0
#endif

#define RF_FREQUENCY                                915000000 // Hz

#define TX_OUTPUT_POWER                             14        // dBm

#define LORA_BANDWIDTH                              0         // [0: 125 kHz,
                                                              //  1: 250 kHz,
                                                              //  2: 500 kHz,
                                                              //  3: Reserved]
#define LORA_SPREADING_FACTOR                       7         // [SF7..SF12]
#define LORA_CODINGRATE                             1         // [1: 4/5,
                                                              //  2: 4/6,
                                                              //  3: 4/7,
                                                              //  4: 4/8]
#define LORA_PREAMBLE_LENGTH                        8         // Same for Tx and Rx
#define LORA_SYMBOL_TIMEOUT                         0         // Symbols
#define LORA_FIX_LENGTH_PAYLOAD_ON                  false
#define LORA_IQ_INVERSION_ON                        false


#define RX_TIMEOUT_VALUE                            1000
#define BUFFER_SIZE                                 30 // Define the payload size here

char txpacket[BUFFER_SIZE];
char rxpacket[BUFFER_SIZE];

static RadioEvents_t RadioEvents;

double txNumber;

int16_t rssi,rxSize;
void  DoubleToString( char *str, double double_num,unsigned int len);

void setup() {
    Serial.begin(115200);
    /*GPS uart baud: 
    * Air530Z support : 9600,19200,38400,57600,115200.
    * Air530  support : 9600,19200,38400,57600,115200,230400,460800
    * default is 9600
    */
    GPS.begin(9600);
    
    /*GPS mode set: 
    * GPS        :        MODE_GPS
    * BEIDOU     :        MODE_BEIDOU
    * GLONASS    :        MODE_GLONASS             //only Air530Z supported.
    * GPS+BEIDOU :        MODE_GPS_BEIDOU
    * GSP+GLONASS:        MODE_GPS_GLONASS
    * GPS+BEIDOU+GLONASS: MODE_GPS_BEIDOU_GLONASS  //only Air530Z supported.
    * For Air530, default mode is GPS+BEIDOU.
    * For Air530Z, default mode is GPS+BEIDOU+GLONASS.
    */
    GPS.setmode(MODE_GPS_GLONASS);
    
    /*supported nmea sentence :
    * GLL, RMC, VTG, GGA, GSA, GSV
    */
  //  GPS.setNMEA(NMEA_GSV);


    txNumber=0;
    rssi=0;

    Radio.Init( &RadioEvents );
    Radio.SetChannel( RF_FREQUENCY );
    Radio.SetTxConfig( MODEM_LORA, TX_OUTPUT_POWER, 0, LORA_BANDWIDTH,
                                   LORA_SPREADING_FACTOR, LORA_CODINGRATE,
                                   LORA_PREAMBLE_LENGTH, LORA_FIX_LENGTH_PAYLOAD_ON,
                                   true, 0, 0, LORA_IQ_INVERSION_ON, 3000 ); 
   }



void loop()
{
	delay(1000);

  // Lettura dati GPS
  while (GPS.available() > 0)
  {
    GPS.encode(GPS.read());
  }
  // fine dati gps

  
	txNumber += 0.01;
	sprintf(txpacket,"%s","Hello world number");  //start a package
//	sprintf(txpacket+strlen(txpacket),"%d",txNumber); //add to the end of package
	
	DoubleToString(txpacket,txNumber,3);	   //add to the end of package
	
	turnOnRGB(COLOR_SEND,0); //change rgb color

	Serial.printf("\r\nsending packet \"%s\" , length %d\r\n",txpacket, strlen(txpacket));

  Serial.print("Date/Time: ");
  if (GPS.date.isValid())
  {
    Serial.printf("%d/%02d/%02d",GPS.date.year(),GPS.date.day(),GPS.date.month());
  }
  else
  {
    Serial.print("INVALID");
  }

  if (GPS.time.isValid())
  {
    Serial.printf(" %02d:%02d:%02d.%02d",GPS.time.hour(),GPS.time.minute(),GPS.time.second(),GPS.time.centisecond());
  }
  else
  {
    Serial.print(" INVALID");
  }
  Serial.println();
  
  Serial.print("LAT: ");
  Serial.print(GPS.location.lat(),6);
  Serial.print(", LON: ");
  Serial.print(GPS.location.lng(),6);
  Serial.print(", ALT: ");
  Serial.print(GPS.altitude.meters());

  Serial.println(); 
  
  Serial.print("SATS: ");
  Serial.print(GPS.satellites.value());
  Serial.print(", HDOP: ");
  Serial.print(GPS.hdop.hdop());
  Serial.print(", AGE: ");
  Serial.print(GPS.location.age());
  Serial.print(", COURSE: ");
  Serial.print(GPS.course.deg());
  Serial.print(", SPEED: ");
  Serial.println(GPS.speed.kmph());
  Serial.println();

	Radio.Send( (uint8_t *)txpacket, strlen(txpacket) ); //send the package out	
}

/**
  * @brief  Double To String
  * @param  str: Array or pointer for storing strings
  * @param  double_num: Number to be converted
  * @param  len: Fractional length to keep
  * @retval None
  */
void  DoubleToString( char *str, double double_num,unsigned int len) { 
  double fractpart, intpart;
  fractpart = modf(double_num, &intpart);
  fractpart = fractpart * (pow(10,len));
  sprintf(str + strlen(str),"%d", (int)(intpart)); //Integer part
  sprintf(str + strlen(str), ".%d", (int)(fractpart)); //Decimal part
}
