// constants defined

const int RED_PIN = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN = 11;
const int ANALOG_PIN = 3;
const int ESP_PIN = 7;

// This variable controls how fast we loop through the colors.
// (Try changing this to make the fading faster or slower.)

int DISPLAY_TIME = 10;  // In milliseconds


void setup()
{
  // Here we'll configure the Arduino pins we're using to
  // drive the LED to be outputs:
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(ANALOG_PIN, INPUT);
  pinMode(ESP_PIN, OUTPUT);
  Serial.begin(9600);
}


void loop()
{
 readPIRSensor();
}

// reads value from PIR Sensor 
void readPIRSensor()
{
  int x;  
  x = analogRead(ANALOG_PIN);
  showRGB(x);  
  // write value to digital so that ESP8266 can be read from it 
  if ( x > 10 )
  {
    digitalWrite(ESP_PIN,HIGH); // there is some movement 
  }
  else {
    digitalWrite(ESP_PIN,LOW); // there is no movement
  }
  // logs for debugging
  Serial.println("PIR value");
  Serial.println(x);
  Serial.println("ECS PIN");
  Serial.println(digitalRead(ESP_PIN)); 
  delay(1000);
}

// This function translates a number between 0 and 767 into a
// specific color on the RGB LED. If you have this number count
// through the whole range (0 to 767), the LED will smoothly
// change color through the entire spectrum.

// The "base" numbers are:
// 0   = pure red
// 255 = pure green
// 511 = pure blue
// 767 = pure red (again)

// Numbers between the above colors will create blends. For
// example, 640 is midway between 512 (pure blue) and 767
// (pure red). It will give you a 50/50 mix of blue and red,
// resulting in purple.

// If you count up from 0 to 767 and pass that number to this
// function, the LED will smoothly fade between all the colors.
// (Because it starts and ends on pure red, you can start over
// at 0 without any break in the spectrum).


void showRGB(int color)
{
int redIntensity;
int greenIntensity;
int blueIntensity;

// Here we'll use an "if / else" statement to determine which
// of the three (R,G,B) zones x falls into. Each of these zones
// spans 255 because analogWrite() wants a number from 0 to 255.

// In each of these zones, we'll calculate the brightness
// for each of the red, green, and blue LEDs within the RGB LED.

if (color <= 255)          // zone 1
{
redIntensity = 255 - color;    // red goes from on to off
greenIntensity = color;        // green goes from off to on
blueIntensity = 0;             // blue is always off
}
else if (color <= 511)     // zone 2
{
redIntensity = 0;                     // red is always off
greenIntensity = 255 - (color - 256); // green on to off
blueIntensity = (color - 256);        // blue off to on
}
else // color >= 512       // zone 3
{
redIntensity = (color - 512);         // red off to on
greenIntensity = 0;                   // green is always off
blueIntensity = 255 - (color - 512);  // blue on to off
}

// Now that the brightness values have been set, command the LED
// to those values

analogWrite(RED_PIN, redIntensity);
analogWrite(BLUE_PIN, blueIntensity);
analogWrite(GREEN_PIN, greenIntensity);
}
