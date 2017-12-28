#include <CandleLED.h>
#include <LegoTrain.h>

CandleLED lights(13, LIGHTBULB, 0.2);
LegoTrain train(5, 6, 10, 11);

void setup() {}

void loop() {

  float vbat = analogRead(9);
  vbat *= 2;    // divided by 2, so multiply back
  vbat *= 3.3;  // multiply by 3.3V (reference voltage)
  vbat /= 1024; // convert to voltage

  lights.update();

  if (vbat < 3.7) {
    train.enabled(false);
    lights.flash(true);
    return;
  }

  train.update();
}
