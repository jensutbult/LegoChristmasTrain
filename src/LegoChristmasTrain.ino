#include <PowerFunctions.h>
#include <LegoTrain.h>
#include <CandleLED.h>


PowerFunctions pf(5, 0);
LegoTrain train(pf, 4);
CandleLED lampPostAndReindeer(6, CANDLE, 0.1);
CandleLED fire(9, FIRE, 1.0);
CandleLED twinLights(11, CANDLE, 0.1);
CandleLED upperFloorAndLight(10, CANDLE, 0.3);

void setup() {
}

void loop() {
  train.update();
  lampPostAndReindeer.update();
  fire.update();
  twinLights.update();
  upperFloorAndLight.update();
}
