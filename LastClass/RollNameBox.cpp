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
	double degree = atan2(endPoint.x - startPoint.x, startPoint.y - endPoint.y); // 기울기
	double distance = sqrt(pow(endPoint.x - startPoint.x, 2) + pow(startPoint.y - endPoint.y, 2));

	double dX = (startPoint.x) + (40 * (endPoint.x - startPoint.x) / distance); //뒤로 온 기준점 x
	double dY = (startPoint.y) - (40 * (startPoint.y - endPoint.y) / distance);

	cPoint.x = static_cast<LONG>(dX - 20 * cos(degree));
	cPoint.y = static_cast<LONG>(dY - 20 * sin(degree));

	return cPoint;
}

CPoint RollNameBox::GetSecondRollNamePoint(CPoint startPoint, CPoint endPoint) {
	CPoint cPoint;
	double degree = atan2(endPoint.x - startPoint.x, startPoint.y - endPoint.y); // 기울기
	double distance = sqrt(pow(endPoint.x - startPoint.x, 2) + pow(startPoint.y - endPoint.y, 2));

	double dX = (startPoint.x+(endPoint.x-startPoint.x)/2) + ((endPoint.x - startPoint.x) / distance); //뒤로 온 기준점 x
	double dY = (startPoint.y +(endPoint.y - startPoint.y) / 2) - ((startPoint.y - endPoint.y) / distance);

	cPoint.x = static_cast<LONG>(dX - 20 * cos(degree));
	cPoint.y = static_cast<LONG>(dY - 20 * sin(degree));

	return cPoint;
}
CPoint RollNameBox::GetThirdRollNamePoint(CPoint startPoint, CPoint endPoint) {
	CPoint cPoint;
	double degree = atan2(endPoint.x - startPoint.x, startPoint.y - endPoint.y); // 기울기

	double distance = sqrt(pow(endPoint.x - startPoint.x,2) + pow(startPoint.y - endPoint.y, 2));
	// 루트안에 = 루트(제곱(
	double dX = (endPoint.x)-(40 * (endPoint.x - startPoint.x) / distance); //뒤로 온 기준점 x
	double dY = (endPoint.y)+(40 * (startPoint.y - endPoint.y) / distance); //뒤로 온 기준점 y
	
	cPoint.x = static_cast<LONG>(dX - 20 * cos(degree));
	cPoint.y = static_cast<LONG>(dY - 20 * sin(degree));

	return cPoint;
}
CPoint RollNameBox::GetFourthRollNamePoint(CPoint startPoint, CPoint endPoint) {
	CPoint cPoint;
	double degree = atan2(endPoint.x - startPoint.x, startPoint.y - endPoint.y); // 기울기
	double distance = sqrt(pow(endPoint.x - startPoint.x, 2) + pow(startPoint.y - endPoint.y, 2));

	double dX = (startPoint.x) + (40 * (endPoint.x - startPoint.x) / distance); //뒤로 온 기준점 x
	double dY = (startPoint.y) - (40 * (startPoint.y - endPoint.y) / distance);

	cPoint.x = static_cast<LONG>(dX + 20 * cos(degree));
	cPoint.y = static_cast<LONG>(dY + 20 * sin(degree));

	return cPoint;
}
CPoint RollNameBox::GetFifthRollNamePoint(CPoint startPoint, CPoint endPoint) {

	CPoint cPoint;
	double degree = atan2(endPoint.x - startPoint.x, startPoint.y - endPoint.y); // 기울기

	double distance = sqrt(pow(endPoint.x - startPoint.x, 2) + pow(startPoint.y - endPoint.y, 2));
	// 루트안에 = 루트(제곱(
	double dX = (endPoint.x) - (40 * (endPoint.x - startPoint.x) / distance); //뒤로 온 기준점 x
	double dY = (endPoint.y) + (40 * (startPoint.y - endPoint.y) / distance); //뒤로 온 기준점 y

	cPoint.x = static_cast<LONG>(dX + 20 * cos(degree));
	cPoint.y = static_cast<LONG>(dY + 20 * sin(degree));

	

	return cPoint;
}

CPoint RollNameBox::GetFirstSelfRollNamePoint(CPoint startPoint, CPoint endPoint) {
	CPoint cPoint;

	return cPoint;
}
CPoint RollNameBox::GetSecondSelfRollNamePoint(CPoint startPoint, CPoint endPoint) {
	CPoint cPoint;

	return cPoint;
}
CPoint RollNameBox::GetThirdSelfRollNamePoint(CPoint startPoint, CPoint endPoint) {
	CPoint cPoint;

	return cPoint;
}
CPoint RollNameBox::GetFourthSelfRollNamePoint(CPoint startPoint, CPoint endPoint) {
	CPoint cPoint;

	return cPoint;
}
CPoint RollNameBox::GetFifthSelfRollNamePoint(CPoint startPoint, CPoint endPoint) {
	CPoint cPoint;
	
	return cPoint;
}