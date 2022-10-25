
#include "FastLED.h"
#define SIGNAL_PIN 2
#define LED 3
#define DATA_PIN 4
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS 30
#define BRIGHTNESS 96
#include "DFRobotDFPlayerMini.h"
#include "SoftwareSerial.h"

static const uint8_t PIN_MP3_TX = 6; // Connects to module's RX 
static const uint8_t PIN_MP3_RX = 7; // Connects to module's TX 
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);

// Create the Player object
DFRobotDFPlayerMini player;

CRGB leds[NUM_LEDS];

void setup()
{
  Serial.begin(9600);
  softwareSerial.begin(9600);
  pinMode(SIGNAL_PIN, INPUT);
  pinMode(LED, OUTPUT);
  delay(3000); // initial delay of a few seconds is recommended
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip); // initializes LED strip
  FastLED.setBrightness(BRIGHTNESS);// global brightness
  //player.begin(softwareSerial);
   //player.volume(30);
    // Play the first MP3 file on the SD card
    //player.play(1);
}

void showProgramCleanUp(long delayTime) {
  for (int i = 0; i < NUM_LEDS; ++i) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
  delay(delayTime);
}

void showProgramLight(long delayTime) {
  for (int i = 0; i < NUM_LEDS; ++i) {
    leds[i] = CRGB::White;
  }
  FastLED.show();
  delay(delayTime);
}

void play() {
  player.volume(30);
    // Play the first MP3 file on the SD card
  player.play(1);
}

void loop() {
  if(digitalRead(SIGNAL_PIN)==HIGH) {
    Serial.println("Movement detected.");
    digitalWrite(LED, HIGH);
     // put your setup code here, to run once:
    play;  
    showProgramLight(50);
    delay(600000); //10MN sur on
  } else {
    Serial.println("Did not detect movement.");
     digitalWrite(LED, LOW);
     showProgramCleanUp(2500);
  }
  //delay(1000);
}
