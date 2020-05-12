#include <Arduino.h>
#include <ShiftIn.h>
#include <Shifty.h>
ShiftIn<1> sIn;
Shifty sOut;

// Input Shift Register
#define PL A5           //pLoadPin
#define CE 0            //clockEnablePin
#define DS 3            //dataPin
#define CP 1            //clockPin

// Output Shift Register
#define SETCHIP(x) sOut.setBitCount((x)*8)
#define SER 4            //serialInputPin
#define SRCLK 10         //shiftRegisterClockPin
#define RCLK 5           //RegistarClockPin Latch

class fnd {
  private :
    int SSU;
    int SSD;
    int startPinNum;
    int posPinNum;
    int endPinNum;       //     0           1         2         3         4          5            6          7           8         9         A         B          C           D           E          F          G        H
    byte truthTable[18] = {B11111100, B00110000, B11011010, B01111010, B11111110, B01101110, B11101110, B00111100, B11111110, B01111110, B10111110, B11100110, B11001100, B11110010, B11001110, B10001110, B11101100, B10110110};
    const int delayTime = 5;

  public :
		fnd(int sNum, int pDgt, char eTyp) {
	    startPinNum = sNum;
	    posPinNum = sNum + pDgt;
	    endPinNum = posPinNum + 7;
	    if(eTyp == 'A') {
	      SSU = 0;
	      SSD = 1;
	    } else if(eTyp == 'C') {
	      SSU = 1;
	      SSD = 0;
	    }
	  }

    void show(int pDigits, int showNum);
    void count(int startNum, int finishNum);
};


void fnd::show(int pDigits, int showNum) {
	int pDgts = startPinNum + pDigits - 1;
  for(int i = startPinNum; i < posPinNum; i++) {
    if(i == pDgts) {
      sOut.writeBit(i, SSD);
    } else {
      sOut.writeBit(i, SSU);
    }
  }

  for(int i = 0; i <= 7; i++) {
    byte segment = (truthTable[showNum] & (0x01 << i)) >> i;
    if(segment == 1) {
      sOut.writeBit(endPinNum - i, SSU);
//			delay(delayTime);
    } else {
      sOut.writeBit(endPinNum - i, SSD);
//			delay(delayTime);
    }
  }
}

 fnd fDgt(0, 4, 'A');

void setup() {
	SETCHIP(2);
//	sOut.setBitCount(16);
	sIn.begin(PL, CE, DS, CP);
  sOut.setPins(SER, SRCLK, RCLK);
}

void loop() {
	fDgt.show(2, 17);
/*
	sOut.writeBit(0, 1);
	sOut.writeBit(1, 1);
	sOut.writeBit(2, 1);
	sOut.writeBit(3, 1);
	sOut.writeBit(4, 0);
	sOut.writeBit(5, 0);
	sOut.writeBit(6, 0);
	sOut.writeBit(7, 0);
	sOut.writeBit(8, 0);
	sOut.writeBit(9, 0);
	sOut.writeBit(10, 0);
*/
}
