#pragma once

//MemoBox.h
#ifndef _MEMOBOX_H
#define _MEMOBOX_H

#include "Iterator.h"
#include "SmartPointer.h"
#include "FigureComposite.h"
//#include "Visitor.h"
#include <fstream>

typedef signed long int Long;
class MemoBox : public FigureComposite {
public:
	MemoBox(Long capacity = 256);
	MemoBox(Long x, Long y, Long width, Long height);
	MemoBox(const MemoBox& source);
	virtual ~MemoBox();	// 

	Long Add(Long x, Long y, Long width, Long height);	//
	Long Add(Figure *figure);	//
	Figure* GetAt(Long index);	//
	Figure* Clone() const;	//
	Long Remove(Long index);	//
	MemoBox& operator=(const MemoBox& source);
	Figure* operator[](Long index);

	Long GetCapacity() const;
	Long GetLength() const;
	//void Accept(Visitor& visitor, CDC *cPaintDc);//CDC* CPointDc
		
		 
};
inline Long MemoBox::GetCapacity() const {
	return this->capacity;
}
inline Long MemoBox::GetLength() const {
	return this->length;
}
#endif // !_MEMOBOX_H

