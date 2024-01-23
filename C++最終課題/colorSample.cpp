#include <DxLib.h>

#include "colorSample.h"
int colorSample::white = 0;
int colorSample::blue = 0;

void colorSample::MakeColors() {
	white = GetColor(255, 255, 255);
	blue = GetColor(0, 0, 255);
}