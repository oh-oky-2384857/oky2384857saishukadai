#pragma once

struct  vector2 {
	//coordinate‚Ìfloat”Å;
	//Žå‚Éshot‚ÌˆÚ“®ˆ—‚È‚Ç‚ÅŽg‚¤;
	float x;
	float y;

	vector2(float nx, float ny) {
		x = nx;
		y = ny;
	}
	vector2(const vector2* v2) {
		x = v2->x;
		y = v2->y;
	}
	vector2() {
		x = 0;
		y = 0;
	}
	void operator=(vector2 v2) {
		x = v2.x;
		y = v2.y;
	}
	bool operator==(vector2 v2) {
		return x == v2.x && y == v2.y;
	}
};