#pragma once
#include "vector2.h"
static const int SCREEN_WIDTH = 640;
static const int SCREEN_HEIGHT = 480;

struct coordinate {
	//À•W
	int x;
	int y;
	coordinate(int nx, int ny) {
		x = nx;
		y = ny;
	}
	coordinate(const coordinate* coord) {
		x = coord->x;
		y = coord->y;
	}
	coordinate() {
		x = 0;
		y = 0;
	}
	coordinate& operator=(const coordinate& coord) {
		x = coord.x;
		y = coord.y;

		return *this;
	}
	coordinate& operator+(const coordinate& coord) {
		coordinate result;
		result.x = coord.x + x;
		result.y = coord.y + y;

		return result;
	}
	coordinate& operator=(const vector2& v2) {
		x = v2.x;
		y = v2.y;

		return *this;
	}
	bool operator==(coordinate coord) {
		return x == coord.x && y == coord.y;
	}
	void operator+=(vector2 v2) {
		x += (int)v2.x;
		y += (int)v2.y;
	}
};