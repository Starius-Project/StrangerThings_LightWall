/***************************************************
  Adafruit MQTT Library ESP8266 Example

  Must use ESP8266 Arduino from:
    https://github.com/esp8266/Arduino

  Works great with Adafruit's Huzzah ESP board & Feather
  ----> https://www.adafruit.com/product/2471
  ----> https://www.adafruit.com/products/2821

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Tony DiCola for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
#include <ESP8266WiFi.h>
#include <Adafruit_NeoPixel.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "SFR_51F8"
#define WLAN_PASS       "43bzsu6hva92fhvr7uzr"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "Electro_Guy"
#define AIO_KEY         "2e81c6d2c7d3a6cd22f49961de5ed0931665b620"

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

// Setup a feed called 'photocell' for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Publish photocell = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/photocell");

// Setup a feed called 'onoff' for subscribing to changes.
Adafruit_MQTT_Subscribe StrangerThings = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/strangerthings");

/*************************** Sketch Code ************************************/

// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).
void MQTT_connect();

//////////LED
#define LED_PIN    D2
// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 50
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

long randNumber;  //Pixel random number variable
long randNumberR;  //RED random number variable
long randNumberG;  //GREEN random number variable
long randNumberB;  //BLUE random number variable

int A = 48;
int B = 46;
int C = 44;
int D = 43;
int E = 41;
int F = 40;
int G = 38;
int H = 36;
int Q = 29;
int P = 26;
int O = 25;
int N = 24;
int M = 22;
int L = 20;
int K = 19;
int J = 18;
int I = 16;
int R = 12;
int S = 11;
int T  = 10;
int U = 8;
int V = 7;
int W = 5;
int X = 4;
int Y = 2;
int Z = 0;

int LEDARRAY[26] = {A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z};


void setup() {
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
  for (int i = 0; i < LED_COUNT; i++)
  {
    strip.setPixelColor(i,0, 0, 0);    //turn random pixel off
    strip.show();
  }
  randomSeed(analogRead(3));
  Serial.begin(115200);
  delay(10);

  Serial.println(F("Adafruit MQTT demo"));

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  // Setup MQTT subscription for onoff feed.
  mqtt.subscribe(&StrangerThings);
  strip.setBrightness(255);
  
  
}

uint32_t x=45;

void loop() {
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();

  // this is our 'wait for incoming subscription packets' busy subloop
  // try to spend your time here

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
    if (subscription == &StrangerThings) {
      Serial.print(F("Got: "));
      Serial.println((char *)StrangerThings.lastread);
      if (strcmp((char *)StrangerThings.lastread, "ON") == 0){

        randomPixel(S);
        delay(1000);
        randomPixel(K);
        delay(1000);
        randomPixel(U);
        delay(1000);
        randomPixel(L);
        delay(1000);
        randomPixel(L);
        delay(1000);
        rainbow(3);
        for (int i = 0; i < LED_COUNT; i++)
        {
           strip.setPixelColor(i,0, 0, 0);    //turn random pixel off
           strip.show();
         }
        Serial.println("Upside down");
        /*if (! photocell.publish(x)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK!"));
  }*/
      }

    if (strcmp((char *)StrangerThings.lastread, "RAINBOW") == 0){
      rainbow(3);
    }


    if (strcmp((char *)StrangerThings.lastread, "DEATH") == 0){
      randomPixel(D);
        delay(1000);
        randomPixel(E);
        delay(1000);
        randomPixel(A);
        delay(1000);
        randomPixel(T);
        delay(1000);
        randomPixel(H);
        delay(1000);
    }

    if (strcmp((char *)StrangerThings.lastread, "HELP") == 0){
      randomPixel(H);
        delay(1000);
        randomPixel(E);
        delay(1000);
        randomPixel(L);
        delay(1000);
        randomPixel(P);
        delay(1000);
    }

        if (strcmp((char *)StrangerThings.lastread, "4JULY") == 0){
      randomPixel(T);
        delay(1000);
        randomPixel(O);
        delay(1000);
        randomPixel(D);
        delay(1000);
        randomPixel(A);
        delay(1000);
        randomPixel(Y);
        delay(1000);
    }
    
  }

  

  // ping the server to keep the mqtt connection alive
  // NOT required if you are publishing once every KEEPALIVE seconds
  /*
  if(! mqtt.ping()) {
    mqtt.disconnect();
  }
  */
}
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
  randomPixel(C);
  delay(1000);
  for (int i = 0; i < LED_COUNT; i++)
  {
    strip.setPixelColor(i,0, 0, 0);    //turn random pixel off
    strip.show();
  }
}


//Random pixel with random color.
void randomPixel(int c)
{
  randNumberR = random(0, 255);   //Random RED value
  randNumberG = random(0, 255);   //Random GREEN value
  randNumberB = random(0, 255);   //Random BLUE value
  for (int i = 0; i < LED_COUNT; i++)
  {
    strip.setPixelColor(i,0, 0, 0);    //turn random pixel off
    strip.show();
  }
  

 


     strip.setPixelColor(c,randNumberR, randNumberG, randNumberB);        //turn pixel on
     strip.show();

 
}

// Some functions of our own for creating animated effects -----------------

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la strip.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }
}

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this outer loop:
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<30; a++) {  // Repeat 30 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}
