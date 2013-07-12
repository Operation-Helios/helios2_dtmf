
// Helios 2 DTMF Test
// Operation Helios (operationhelios.com)

// PINS
const unsigned int DTMF_SIGNAL = 9;  // pin is high when receiving DTMF signal
const unsigned int DTMF0 = 2;  // LSB
const unsigned int DTMF1 = 4;
const unsigned int DTMF2 = 5;
const unsigned int DTMF3 = 7;  // MSB

// CONSTANTS
const unsigned int SERIAL_BAUD = 57600;

// VARIABLES
byte lastTone = 'a';

// FUNCTION PROTOTYPES
void setPinModes();
bool gotSignal();  // DTMF tone coming in?
byte getPinValue(unsigned int pin);  // digitalRead() a pin, returning 1 or 0
byte readDTMF();  // return the value of the received tone

void setup()
{
  // init serial for debugging
  Serial.begin(SERIAL_BAUD);
  
  setPinModes();
  
  Serial.println("LOG START");
}

void loop()
{
  // check if a DTMF tone is being received, then process it
  if (gotSignal())
  {
    byte toneValue = readDTMF();
    
    if (toneValue != lastTone)
    {
      lastTone = toneValue;
      Serial.println(toneValue);
    }
  }
}

void setPinModes()
{
  pinMode(DTMF_SIGNAL, INPUT);
  pinMode(DTMF0, INPUT);
  pinMode(DTMF1, INPUT);
  pinMode(DTMF2, INPUT);
  pinMode(DTMF3, INPUT);
}

bool gotSignal()
{
  return (digitalRead(DTMF_SIGNAL) == HIGH);
}

byte getPinValue(unsigned int pin)
{
  return ((digitalRead(pin) == HIGH)? 1 : 0);
}

byte readDTMF()
{
  byte pin0 = getPinValue(DTMF0) * B0001;
  byte pin1 = getPinValue(DTMF1) * B0010;
  byte pin2 = getPinValue(DTMF2) * B0100;
  byte pin3 = getPinValue(DTMF3) * B1000;
  return pin0 + pin1 + pin2 + pin3;
}

