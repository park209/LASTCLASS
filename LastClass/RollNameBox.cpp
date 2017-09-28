//RollNameBox.cpp

#include "RollNameBox.h"

RollNameBox* RollNameBox::instance = 0;

RollNameBox* RollNameBox::Instance() {
	if (instance == 0) {
		instance = new RollNameBox;
	}
	return instance;
}

RollNameBox::RollNameBox() {
}

RollNameBox::RollNameBox(const RollNameBox& source) {
}

RollNameBox::~RollNameBox() {
}

Array<CPoint> RollNameBox::GetRollNameBoxPoints(CPoint startPoint, CPoint endPoint) {
	Array<CPoint> cPoints;


	return cPoints;
}