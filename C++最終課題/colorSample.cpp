#include <DxLib.h>

#include "colorSample.h"
int colorSample::white = 0;
int colorSample::blue = 0;
int colorSample::black = 0;
int colorSample::fireBrick = 0;
int colorSample::lawngreen = 0;

void colorSample::MakeColors() {
	white = GetColor(255, 255, 255);
	blue = GetColor(0, 0, 255);
	black = GetColor(0, 0, 0);
	fireBrick = GetColor(178, 34, 34);
	lawngreen = GetColor(124, 252, 0);
}