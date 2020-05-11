#include <Arduino.h>
#include <ShiftIn.h>
#include <Shifty.h>
ShiftIn<1> si;
Shifty so;

void setup() {
	si.begin(8, 9, 11, 12);
  so.setBitCount(8);
  so.setPins(11, 12, 8);
}

void loop() {

}
