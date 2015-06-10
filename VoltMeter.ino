#include <MicroView.h>

unsigned long time;
int sensorValue;
long incremental;
float volts;
float timearr[120];
// array of voltage readings
//  timearr[0:60] = reading of last minute in seconds
//  timearr[60:120] = reading of last hour in minutes

int secs = 0;
int mins = 0;

#define inputPin A0

void setup()
{
  uView.begin();						// start MicroView
  uView.clear(PAGE);						// clear page
  uView.display();
  uView.setFontType(7);
  for (int i = 0; i < 120; i++){
    timearr[i] = 0.0;
  }
  time = millis()+1000;
}

void loop()
{
  incremental = 0;
  for (int i = 0; i < 5000; i++) {
    sensorValue = analogRead(inputPin);
    incremental += sensorValue; // 1024.0 * 5.0 / 4.7 * 14.7 ;
  }
  volts = incremental * 0.0002;
  volts *= 0.0153432;

  printVolts(volts);

  uView.display();  
  // wait till 1 second has passed
  while (millis() < time) {}
  time += 1000;
  
  storeVolts(volts);
}

void printVolts(float volts) {
  uView.clear(PAGE);
  uView.setCursor(0,0);
  uView.print(volts,3);
  uView.print("/");
}


void storeVolts(float volts) {
  // Store the latest reading in the seconds array
  timearr[secs] = volts;

  // Calculate the minute average and store it in the minute array
  if (++secs == 60) {
    volts = 0;
    for (int i=0; i<60; i++) {
      volts += timearr[i];
    }
    timearr[60 + mins] = volts / 60.0;
    if (++mins == 60) {
      mins = 0;
    }
    secs = 0;
  }
}

