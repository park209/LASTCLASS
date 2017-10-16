//GraphicCtrlPasteKey.cpp

#include "GraphicCtrlPasteKey.h"
#include "ClassDiagramForm.h"
#include "Selection.h"
#include "Class.h"
#include "TextEdit.h"
#include "Diagram.h"
#include "SmartPointer.h"
#include "ArrayIterator.h"
#include "Line.h"
#include "ClassName.h"
#include "Attribute.h"
#include "Method.h"
#include "MemoBox.h"
#include "Template.h"
#include "Relation.h"
#include "Generalization.h"
#include "Realization.h"
#include "Dependency.h"
#include "Association.h"
#include "DirectedAssociation.h"
#include "Aggregation.h"
#include "Aggregations.h"
#include "Composition.h"
#include "Compositions.h"
#include "Reception.h"
#include "MemoLine.h"
#include "Finder.h"
#include "RollNameBox.h"
#include "SelfRelation.h"

#include "RollNameBox.h"
#include "SelfRelation.h"

#include "HistoryGraphic.h"

GraphicCtrlPasteKey::GraphicCtrlPasteKey() {
}

GraphicCtrlPasteKey::GraphicCtrlPasteKey(const GraphicCtrlPasteKey& source) {
}

GraphicCtrlPasteKey::~GraphicCtrlPasteKey() {
}

void GraphicCtrlPasteKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
	if (classDiagramForm->copyBuffer != NULL) {
		Long i = 0;
		Long j = 0;
		Long k = 0;
		Finder finder;

		int vertCurPos = classDiagramForm->GetScrollPos(SB_VERT);
		int horzCurPos = classDiagramForm->GetScrollPos(SB_HORZ);

		CPoint point;
		::GetCursorPos(&point); // 바탕화면 커서위치 Get
		::ScreenToClient(classDiagramForm->GetSafeHwnd(), &point); // 폼영역의 좌표로 변환

		CRect rt = { 0, };

		i = 0;
		SmartPointer<Figure*>CopyBufferSmartPointer(classDiagramForm->copyBuffer->CreateIterator());
		for (CopyBufferSmartPointer->First();!CopyBufferSmartPointer->IsDone();CopyBufferSmartPointer->Next()) {
			if (dynamic_cast<FigureComposite*>(CopyBufferSmartPointer->Current())) {
				if (i == 0 || CopyBufferSmartPointer->Current()->GetX() < rt.left) {//minimumX
					rt.left = CopyBufferSmartPointer->Current()->GetX();
				}
				if (i == 0 || CopyBufferSmartPointer->Current()->GetX()            //maximumX
					+ CopyBufferSmartPointer->Current()->GetWidth() > rt.right) {
					rt.right = CopyBufferSmartPointer->Current()->GetX() + CopyBufferSmartPointer->Current()->GetWidth();
				}
				if (i == 0 || CopyBufferSmartPointer->Current()->GetY() < rt.top) {   //minimumY
					rt.top = CopyBufferSmartPointer->Current()->GetY();
				}
				if (i == 0 || CopyBufferSmartPointer->Current()->GetY()            //maximumY
					+ CopyBufferSmartPointer->Current()->GetHeight() > rt.bottom) {
					rt.bottom = CopyBufferSmartPointer->Current()->GetY() + CopyBufferSmartPointer->Current()->GetHeight();
				}
				i++;
			}
		}
		for (CopyBufferSmartPointer->First();!CopyBufferSmartPointer->IsDone();CopyBufferSmartPointer->Next()) {
			if (dynamic_cast<FigureComposite*>(CopyBufferSmartPointer->Current())) {
				SmartPointer<Figure*>compositeIterator(static_cast<FigureComposite*>(CopyBufferSmartPointer->Current())->CreateIterator());
				j = 0;
				while (!compositeIterator->IsDone()) {
					if (dynamic_cast<Relation*>(compositeIterator->Current())) {
						if (compositeIterator->Current()->GetX() >= rt.left && compositeIterator->Current()->GetX() <= rt.right &&
							compositeIterator->Current()->GetY() >= rt.top && compositeIterator->Current()->GetY() <= rt.bottom &&
							compositeIterator->Current()->GetX() + compositeIterator->Current()->GetWidth() >= rt.left &&
							compositeIterator->Current()->GetX() + compositeIterator->Current()->GetWidth() <= rt.right &&
							compositeIterator->Current()->GetY() + compositeIterator->Current()->GetHeight() >= rt.top &&
							compositeIterator->Current()->GetY() + compositeIterator->Current()->GetHeight() <= rt.bottom) {
							j++;
							compositeIterator->Next();
						}
						else {
							Figure *figure = compositeIterator->Current();
							k = 0;
							SmartPointer<Figure*>bufferIterator(classDiagramForm->copyBuffer->CreateIterator());
							while (!bufferIterator->IsDone()) {
								if (dynamic_cast<Relation*>(bufferIterator->Current())) {
									if (figure->GetX() == bufferIterator->Current()->GetX() &&
										figure->GetY() == bufferIterator->Current()->GetY() &&
										figure->GetX() + figure->GetWidth() == bufferIterator->Current()->GetX() + bufferIterator->Current()->GetWidth() &&
										figure->GetY() + figure->GetHeight() == bufferIterator->Current()->GetY() + bufferIterator->Current()->GetHeight()) {
										classDiagramForm->copyBuffer->Remove(k);
									}
									else {
										k++;
										bufferIterator->Next();
									}
								}
								else {
									k++;
									bufferIterator->Next();
								}
							}
							static_cast<FigureComposite*>(CopyBufferSmartPointer->Current())->Remove(j);
						}
					}
					else {
						j++;
						compositeIterator->Next();
					}
				}
			}
		}
		Long distanceX = point.x + horzCurPos - rt.left;
		Long distanceY = point.y + vertCurPos - rt.top;

		Long quadrant = finder.FindQuadrant(point.x + horzCurPos, point.y + vertCurPos, rt.left, rt.top);
		//현재 커서 위치에 해당 Rect가 곂치는 기호들이 있는지 판단
		if (quadrant == 1) {
			rt.left += abs(distanceX);
			rt.top -= abs(distanceY);
			rt.right += abs(distanceX);
			rt.bottom -= abs(distanceY);
		}
		else if (quadrant == 2) {
			rt.left += abs(distanceX);
			rt.top += abs(distanceY);
			rt.right += abs(distanceX);
			rt.bottom += abs(distanceY);
		}
		else if (quadrant == 3) {
			rt.left -= abs(distanceX);
			rt.top += abs(distanceY);
			rt.right -= abs(distanceX);
			rt.bottom += abs(distanceY);
		}
		else if (quadrant == 4) {
			rt.left -= abs(distanceX);
			rt.top -= abs(distanceY);
			rt.right -= abs(distanceX);
			rt.bottom -= abs(distanceY);
		}

		bool ret = classDiagramForm->diagram->CheckOverlap(rt, 0);
		//없으면 기호들을 이동시킨다
		if (ret == false) {
			Figure *figure;
			MovingVisitor movingVisitor;
			for (CopyBufferSmartPointer->First();!CopyBufferSmartPointer->IsDone();CopyBufferSmartPointer->Next()) {
				figure = CopyBufferSmartPointer->Current();
				if (dynamic_cast<Class*>(figure)) { //클래스나 메모면
					static_cast<Class*>(figure)->Accept(movingVisitor, distanceX, distanceY);
					classDiagramForm->diagram->Add(figure->Clone());
				}
				else if (dynamic_cast<MemoBox*>(figure)) {
					static_cast<MemoBox*>(figure)->Accept(movingVisitor, distanceX, distanceY);
					classDiagramForm->diagram->Add(figure->Clone());
				}
			}
		}
	}
}


void GraphicCtrlPasteKey::KeyPress(TextEdit *textEdit) {
}