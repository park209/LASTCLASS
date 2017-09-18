
//MemoBox.h
#ifndef _MEMOBOX_H
#define _MEMOBOX_H

#include "FigureComposite.h"
#include "DrawingVisitor.h"
typedef signed long int Long;

class MemoBox : public FigureComposite {
public:
	MemoBox(Long capacity = 10);
	MemoBox(Long x, Long y, Long width, Long height);
	MemoBox(const MemoBox& source);
	virtual ~MemoBox();	// 

	Long Add(Long x, Long y, Long width, Long height);	//
	virtual Long Add(Figure *figure);	//
	virtual Figure* GetAt(Long index);	//
	virtual Figure* Clone() const;	//
	virtual Long Remove(Long index);	//

	MemoBox& operator=(const MemoBox& source);
	Figure* operator[](Long index);


	void Accept(Visitor& visitor, CDC *cPaintDc);//CDC* CPointDc
};

#endif // !_MEMOBOX_H

