#pragma once
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
	void operator=(coordinate coord) {
		x = coord.x;
		y = coord.y;
	}
	bool operator==(coordinate coord) {
		return x == coord.x && y == coord.y;
	}

};