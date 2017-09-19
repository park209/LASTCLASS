#ifndef _SELECTION_H
#define _SELECTION_H
#include "FigureComposite.h"
#include "MovingVisitor.h"
#include "DrawingVisitor.h"
#include <afxwin.h>
using namespace std;
typedef signed long  int Long;
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
	void Accept(Visitor& visitor, Long distanceX, Long distanceY);
	void Accept(Visitor& visitor, CDC *cPaintDc);

	void SelectByArea(Diagram *diagram, CRect area);
	Long SelectByPoint(Diagram *diagram, Long x, Long y);

};

#endif // !_SELECTION_H
