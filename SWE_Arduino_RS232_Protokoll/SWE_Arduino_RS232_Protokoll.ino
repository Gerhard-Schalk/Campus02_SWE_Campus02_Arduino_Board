#include "Arduino.h"
#include <U8g2lib.h>
#include <Wire.h>
#include "LM75_Temperature_Sensor.h"
#include "OLED_Display_Util.h"
#include "BitConverter.h"
#include "SerialCmd.h"

const int TIMER_START_VALUE = 49910; // 1s Sys Tick Timer

#define RGB_ON  LOW
#define RGB_OFF HIGH

const int LED_RED = 12;   // LED Red
const int LED_BLUE = 11;  // LED Blue
const int LED_GREEN = 10; // LED Green

void initSysTickTimer();
void oled_UpdateDisplay();
void sendSerialCmd();

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

int adcRawValuePoti = 0;
float voltValuePoti = 0.0f;
float tmpValue = 0.0f;
bool sysTickTimerFlag = false;

void setup() {
  // Port PC: LED7 .. LED0
  DDRC |= 0xFF; // Port PC Richtungsregister auf Ausgang setzten

  // RGB LEDs als Ausgänge konfigurieren
  pinMode(LED_RED, OUTPUT);  // Port 12 als Ausgang konfigurieren
  pinMode(LED_GREEN, OUTPUT); // Port 10 als Ausgang konfigurieren
  pinMode(LED_BLUE, OUTPUT);  // Port 11 als Ausgang konfigurieren

  // Alle RGB-LEDs ausschalten (negative Logik)
  digitalWrite( LED_RED, RGB_OFF );
  digitalWrite( LED_GREEN, RGB_OFF );
  digitalWrite( LED_BLUE, RGB_OFF );

  // OLED-Display
  u8g2.begin();
  u8g2.setFont(u8g2_font_profont22_mf);

  Serial.begin(9600);

  oled_UpdateDisplay();
  tmpValue = LM75_getTemperature();
  initSysTickTimer();
}

void loop() {

  // Poti einlesen
  adcRawValuePoti = analogRead( A0 );   // ADC einlesen

  // Spannungswert berechnen
  voltValuePoti = (5.0 * adcRawValuePoti) / 1023.0;

  if ( sysTickTimerFlag == true )
  {
    sysTickTimerFlag = false;

    // Temperatur Sensor LM75
    tmpValue = LM75_getTemperature();
  }

  // Update OLED-Display
  oled_UpdateDisplay();

  sendSerialCmd();

}

//  Timer Overflow ISR
ISR(TIMER3_OVF_vect)
{
  static uint8_t secCounter = 0;

  // Timer/Counter Zählregister Startwert setzen
  TCNT3 = TIMER_START_VALUE;

  secCounter++;

  if (secCounter >= 59)
  {
    secCounter = 0;
    sysTickTimerFlag = true;
  }
}


void serialEvent()
{
  if ( Serial.available() )
  {
    serialReceiveCmd();
  }
}



void ExecuteRecSerialCommand()
{
  uint8_t *pRespBuffer = gbaRxBuffer;

  switch (gbaRxBuffer[1]) {
    case 0x10: // CMD: LED Output
      if ( gbaRxBuffer[2] == 1 ) // LEN == 1 ?
      {
        PORTC = gbaRxBuffer[3];
      }
      break;

    case 0x12: // CMD: RGB-LED
      if ( gbaRxBuffer[2] == 3 ) // LEN == 3 ?
      {
        analogWrite(LED_RED, (int)(255 - gbaRxBuffer[3]));  // PWM ausgeben
        analogWrite(LED_GREEN, (int)(255 - gbaRxBuffer[4]));  // PWM ausgeben
        analogWrite(LED_BLUE, (int)(255 - gbaRxBuffer[5]));   // PWM ausgeben
      }
      break;
  }
}

void oled_UpdateDisplay()
{
  u8g2.clearBuffer(); // clear the internal memory

  oled_PrintIntValue(u8g2, 0, 16, "ADC: ", adcRawValuePoti, " ");
  oled_PrintFloatValue(u8g2, 0, 36, "Spg:", voltValuePoti, "V");
  oled_PrintFloatValue(u8g2, 0, 60, "Tmp:", tmpValue, "°C");

  u8g2.sendBuffer();  // transfer internal memory to the display
}

void sendSerialCmd()
{
  // ADC Ausgabe via serieller Schnittstelle
  byte baRawADCValue[2];
  intToBytes(adcRawValuePoti, baRawADCValue, true);
  serialSendCmd(0x02, baRawADCValue, 2);

  // mV Ausgabe via serieller Schnittstelle
  byte baVoltValue[4];
  floatToBytes(voltValuePoti * 1000.0, baVoltValue, true);
  serialSendCmd(0x04, baVoltValue, 4);

  // Temperature Ausgabe via serieller Schnittstelle
  byte baTmpValue[4];
  floatToBytes(tmpValue, baTmpValue, true);
  serialSendCmd(0x06, baTmpValue, 4);
}

void initSysTickTimer()
{
  // Alle Interrupts deaktivieren stellt sicher,
  // das während der Konfiguration ein Interrupt
  // ausgelöst wird.
  noInterrupts();

  // Timer/Counter 1 Control Register A/B
  // vor der Konfiguration auf 0 setzten
  TCCR3A = 0;
  TCCR3B = 0;

  // Timer/Counter 1 Zählregister = Startwert
  TCNT3 = TIMER_START_VALUE;

  // Timer/Counter 1 Prescaler = 1024
  TCCR3B |= (1 << CS10);
  TCCR3B |= (1 << CS12);

  // Timer/Counter 1 Overflow Interrupt aktivieren
  TIMSK3 |= (1 << TOIE3);

  interrupts(); // Alle Interrupts wieder aktivieren
}
