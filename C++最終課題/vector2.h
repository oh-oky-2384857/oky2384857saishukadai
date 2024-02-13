#pragma once
#include "gameCommon.h"

struct vector2 {
	//coordinate‚Ìfloat”Å;
	//Žå‚Éshot‚ÌˆÚ“®ˆ—‚È‚Ç‚ÅŽg‚¤;
	float x;
	float y;
	vector2(float nx, float ny) {
		x = nx;
		y = ny;
	}
	vector2(int nx, int ny) {
		x = (float)nx;
		y = (float)ny;
	}
	vector2(const vector2* v2) {
		x = v2->x;
		y = v2->y;
	}
	vector2() {
		x = 0;
		y = 0;
	}
	vector2& operator=(const vector2& v2) {
		x = v2.x;
		y = v2.y;

		return *this;
	}
	bool operator==(vector2 v2) {
		return x == v2.x && y == v2.y;
	}
	vector2& operator*(const float f) {
		x *= f;
		y *= f;
		return *this;
	}
	vector2& operator+=(const vector2& v2) {
		x += v2.x;
		y += v2.y;
		return *this;
	}
};