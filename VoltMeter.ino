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
#define graphMax 4.970
#define graphMin 4.930

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
  printGraph();

  uView.display();  
  // wait till 1 second has passed
  while (millis() < time) {}
  time += 1000;
  
  storeVolts(volts);
}

void printVolts(float volts) {
  // Print the current voltage followed by the "V" symbol ("/" in this font)
  uView.clear(PAGE);
  uView.setCursor(0,0);
  if (volts < 10)
    uView.print(volts,3);
  else if (volts < 100)
    uView.print(volts,2);
  uView.print("/");
}

void printGraph() {
  int y;
  int i;
  for (int x=0; x<60; x++) {
    // in the 0th position we want the value of timearr[secs - 1] (this sec hasn't been recorded yet)
    // in the 1st position we want the value of timearr[secs - 2]
    // in the 2nd position we want the value of timearr[secs - 3], etc.    
    // when we underflow [secs - n] we want to wrap around to [59]
    i = secs - x - 1;
    if (i<0) {
      i += 60;
    }
    y = 24 * (timearr[i] - graphMin) / (graphMax - graphMin);
    // bound y between 0 <= y <= 24
    y = min(max(y,0),24);
    
    uView.pixel(x + 2, 47 - y);
  }
  // draw arrow if current reading is below min or above max
  if (timearr[secs-1] > graphMax) {
    uView.line(2,32,2,25);
    uView.line(2,25,5,28);
    uView.line(2,25,0,27);
  }
  if (timearr[secs-1] < graphMin) {
    uView.line(2,38,2,45);
    uView.line(2,45,5,42);
    uView.line(2,45,0,43);
  }
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

