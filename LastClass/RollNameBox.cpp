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

CPoint RollNameBox::GetFirstRollNamePoint(CPoint startPoint, CPoint endPoint) {
	CPoint cPoint;


	return cPoint;
}

CPoint RollNameBox::GetSeocndRollNamePoint(CPoint startPoint, CPoint endPoint) {
	CPoint cPoint;


	return cPoint;
}
CPoint RollNameBox::GetThirdRollNamePoint(CPoint startPoint, CPoint endPoint) {
	CPoint cPoint;


	return cPoint;
}
CPoint RollNameBox::GetFourthRollNamePoint(CPoint startPoint, CPoint endPoint) {
	CPoint cPoint;


	return cPoint;
}
CPoint RollNameBox::GetFifthRollNamePoint(CPoint startPoint, CPoint endPoint) {
	CPoint cPoint;


	return cPoint;
}