#include <PowerFunctions.h>
#include <LegoTrain.h>
#include <CandleLED.h>


PowerFunctions pf(5, 0);
LegoTrain train(pf, 4);
CandleLED ledOne(6);

void setup() {
}

void loop() {
  train.update();
  ledOne.update();
}
