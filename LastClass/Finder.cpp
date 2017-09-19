//Finder.cpp

#include"Finder.h"

Finder::Finder() {

}

Finder::Finder(const Finder& source) {

}

Finder::~Finder() {

}

Finder& Finder::operator=(const Finder& source) {
	return const_cast<Finder&>(source);
}

bool Finder::FindRectangleByArea(CRect object, CRect area) {
	return  object.IntersectRect(object, area);
}

bool Finder::FindRectangleByPoint(CRect object, Long x, Long y) {
	bool ret = false;
	if (object.left <= x && object.right >= x && object.top <= y && object.bottom >= y) {
		ret = true;
	}
	return ret;
}

bool Finder::FindLineByArea(const CPoint& lineStart, const CPoint& lineEnd, CRect area) {
	bool ret = false;
	if (lineStart.x >= area.left && lineStart.y >= area.top && lineStart.x <= area.right && lineStart.y <= area.bottom
		&& lineEnd.x >= area.left && lineEnd.y >= area.top  &&
		lineEnd.x <= area.right && lineEnd.y <= area.bottom) {
		ret = true;
	}
	else {
		CPoint line2Start;
		CPoint line2End;
		if (ret == false) {//���� Ŭ�������� ���� �����ϴ� �� ã��
						   //���
			line2Start.x = area.left;
			line2Start.y = area.top;
			line2End.x = area.right;
			line2End.y = area.top;
			ret = IsLineCross(lineStart, lineEnd, line2Start, line2End);
		}
		if (ret == false) {
			//����
			line2Start.x = area.left;
			line2Start.y = area.top;
			line2End.x = area.left;
			line2End.y = area.bottom;
			ret = IsLineCross(lineStart, lineEnd, line2Start, line2End);
		}
		if (ret == false) {
			//����
			line2Start.x = area.right;
			line2Start.y = area.top;
			line2End.x = area.right;
			line2End.y = area.bottom;
			ret = IsLineCross(lineStart, lineEnd, line2Start, line2End);
		}
		if (ret == false) {
			//�ϴ�
			line2Start.x = area.left;
			line2Start.y = area.bottom;
			line2End.x = area.right;
			line2End.y = area.bottom;
			ret = IsLineCross(lineStart, lineEnd, line2Start, line2End);
		}
	}
	return ret;
}

bool Finder::FindLineByPoint(const CPoint& lineStart, const CPoint& lineEnd, Long x, Long y) {
	bool ret = false;
	CPoint line2Start;
	CPoint line2End;
	if (ret == false) {//���� Ŭ�������� ���� �����ϴ� �� ã��
					   //���
		line2Start.x = x - 5;
		line2Start.y = y - 5;
		line2End.x = x + 5;
		line2End.y = y - 5;
		ret = IsLineCross(lineStart, lineEnd, line2Start, line2End);
	}
	if (ret == false) {
		//����
		line2Start.x = x - 5;
		line2Start.y = y - 5;
		line2End.x = x - 5;
		line2End.y = y + 5;
		ret = IsLineCross(lineStart, lineEnd, line2Start, line2End);
	}
	if (ret == false) {
		//����
		line2Start.x = x + 5;
		line2Start.y = y - 5;
		line2End.x = x + 5;
		line2End.y = y + 5;
		ret = IsLineCross(lineStart, lineEnd, line2Start, line2End);
	}
	if (ret == false) {
		//�ϴ�
		line2Start.x = x - 5;
		line2Start.y = y + 5;
		line2End.x = x + 5;
		line2End.y = y + 5;
		ret = IsLineCross(lineStart, lineEnd, line2Start, line2End);
	}

	return ret;
}

CPoint& Finder::GetCrossPoint(const CPoint& lineStart, const CPoint& lineEnd, CRect object) {

	CPoint crossPoint;
	double t;
	double s;
	double under;
	double _t;
	double _s;

	CPoint line2Start;
	CPoint line2End;
	bool ret = false;

	if (ret == false) {
		line2Start.x = object.left;
		line2Start.y = object.top;
		line2End.x = object.right;
		line2End.y = object.top;
		ret = IsLineCross(lineStart, lineEnd, line2Start, line2End);
	}

	if (ret == false) {
		line2Start.x = object.right;
		line2Start.y = object.top;
		line2End.x = object.right;
		line2End.y = object.bottom;
		ret = IsLineCross(lineStart, lineEnd, line2Start, line2End);
	}
	
	if (ret == false) {
		line2Start.x = object.left;
		line2Start.y = object.top;
		line2End.x = object.left;
		line2End.y = object.bottom;
		ret = IsLineCross(lineStart, lineEnd, line2Start, line2End);
	}
	
	if (ret == false) {
		line2Start.x = object.left;
		line2Start.y = object.bottom;
		line2End.x = object.right;
		line2End.y = object.bottom;
		ret = IsLineCross(lineStart, lineEnd, line2Start, line2End);
	}
	
	under = (line2End.y - line2Start.y)*(lineEnd.x - lineStart.x) - (line2End.x - line2Start.x)*(lineEnd.y - lineStart.y);
	_t = (line2End.x - line2Start.x)*(lineStart.y - line2Start.y) - (line2End.y - line2Start.y)*(lineStart.x - line2Start.x);
	_s = (lineEnd.x - lineStart.x)*(lineStart.y - line2Start.y) - (lineEnd.y - lineStart.y)*(lineStart.x - line2Start.x);
	t = _t / under;
	s = _s / under;
	crossPoint.x = static_cast<LONG>(lineStart.x + t*(double)(lineEnd.x - lineStart.x));
	crossPoint.y = static_cast<LONG>(lineStart.y + t*(double)(lineEnd.y - lineStart.y));

	return crossPoint;
}

bool IsLineCross(const CPoint& line1Start, const CPoint& line1End, const CPoint& line2Start, const CPoint& line2End) {
	double t;
	double s;
	bool ret = false;
	double under = (line2End.y - line2Start.y)*(line1End.x - line1Start.x) - (line2End.x - line2Start.x)*(line1End.y - line1Start.y);
	if (under != 0) {
		double _t = (line2End.x - line2Start.x)*(line1Start.y - line2Start.y) - (line2End.y - line2Start.y)*(line1Start.x - line2Start.x);
		double _s = (line1End.x - line1Start.x)*(line1Start.y - line2Start.y) - (line1End.y - line1Start.y)*(line1Start.x - line2Start.x);
		t = _t / under;
		s = _s / under;
		if (t >= 0.0 && t <= 1.0 && s >= 0.0 && s <= 1.0 && _t != 0 && _s != 0) {
			ret = true;
		}
	}
	return ret;
}