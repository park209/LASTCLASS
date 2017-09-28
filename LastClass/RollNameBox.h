//RollNameBox.h

#ifndef _ROLLNAMEBOX_H
#define _ROLLNAMEBOX_H

#include "Array.h"
#include "afxwin.h"

class RollNameBox {
public:
	static RollNameBox* Instance();
public:
	RollNameBox();
	RollNameBox(const RollNameBox& source);
	~RollNameBox();
public:
	Array<CPoint> GetRollNameBoxPoints(CPoint startPoint, CPoint endPoint);
private:
	static RollNameBox* instance;
};

#endif // _ROLLNAMEBOX_H