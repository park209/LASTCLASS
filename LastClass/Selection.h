#ifndef _SELECTION_H
#define _SELECTION_H
#include "FigureComposite.h"
#include <afxwin.h>
using namespace std;
class Diagram;
class Selection : public  FigureComposite{
public: 
	Selection(Long capacity = 256);
	Selection(const Selection& source);
	virtual ~Selection();
	Selection& operator = (const Selection& source);

	virtual Long Remove(Long index);
	virtual Long Add(Figure *figure);
	virtual Figure* GetAt(Long index);
	virtual Figure* Clone() const;
	void DeleteAllItems();

	void FindByArea(Diagram *diagram, CRect area);
	Long FindByPoint(Diagram *diagram, Long x, Long y);

	bool FindCrossPoints(const CPoint& line1Start, const CPoint& line1End, const CPoint& line2Start, const CPoint& line2End, CPoint *crossPoint);
};

#endif // !_SELECTION_H
