/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "application.h"
#line 1 "/Users/yash/playground/meshed-led-test/src/meshed-led-test.ino"
/*
 * Project meshed-led-test
 * Description:
 * Author:
 * Date:
 */

void setup();
void loop();
int toggleLights(String command);
int setWait(String command);
#line 8 "/Users/yash/playground/meshed-led-test/src/meshed-led-test.ino"
uint8_t prevToggle = 0;
uint8_t toggle = 0;
uint16_t timer = 0;
uint8_t wait = 10;

LEDStatus breatheOrange(
    RGB_COLOR_ORANGE,
    LED_PATTERN_FADE,
    LED_SPEED_FAST,
    LED_PRIORITY_IMPORTANT);

// setup() runs once, when the device is first turned on.
void setup()
{
  Particle.function("toggleLights", toggleLights);
  Particle.function("setWait", setWait);
}

// loop() runs over and over again, as quickly as it can execute.
void loop()
{
  // The core of your code will likely live here.
  if (prevToggle != toggle)
  {
    breatheOrange.setActive(true);
    prevToggle = toggle;
    Particle.publish("meshed-led-test/lightshow", "started", PRIVATE);
  }

  if (breatheOrange.isActive())
  {
    timer++;
    delay(wait);
  }

  if (timer >= 100)
  {
    breatheOrange.setActive(false);
    timer = 0;
    Particle.publish("meshed-led-test/lightshow", "ended", PRIVATE);
  }
}

int toggleLights(String command)
{
  toggle = !toggle;
  return toggle;
}

int setWait(String command)
{
  char inputStr[10];
  command.toCharArray(inputStr, 10);
  int i = atoi(inputStr);

  if (i > 20)
  {
    wait = 20;
  }
  else if (i < 5)
  {
    wait = 5;
  }
  else
  {
    wait = i;
  }
  return wait;
}
