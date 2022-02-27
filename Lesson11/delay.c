#include "delay.h"

void delay(int volatile loopCount){
  //int loopCount = 1000000;
  while (loopCount--){
    ;
  }
}