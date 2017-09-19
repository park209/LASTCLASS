//Finder.h

#ifndef _FINDER_H
#define _FINDER_H

#include<afxwin.h>

typedef signed long int Long;

class Finder {
public:
	Finder();
	Finder(const Finder& source);
	~Finder();
	Finder& operator=(const Finder& source);

	
	bool FindRectangleByArea(CRect object, CRect area);
	bool FindRectangleByPoint(CRect object, Long x, Long y);
	bool FindLineByArea(const CPoint& lineStart, const CPoint& lineEnd, CRect area);
	bool FindLineByPoint(const CPoint& lineStart, const CPoint& lineEnd, Long x, Long y);
	CPoint& GetCrossPoint(const CPoint& lineStart, const CPoint& lineEnd, CRect object);
};

bool IsLineCross(const CPoint& line1Start, const CPoint& line1End, const CPoint& line2Start, const CPoint& line2End);

#endif //_FINDER_H