#define LED_PIN     31

class BuiltInLed
{
  public:
  BuiltInLed() 
  {
    pinMode(LED_BUILTIN, OUTPUT);
  }

public:
  void turnOn()
  {
    digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
  }

  void turnOff()
  {
    digitalWrite(LED_BUILTIN, LOW);
  }

} led;