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



//
//void GraphicCtrlPasteKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
//	if (classDiagramForm->copyBuffer != NULL) {
//		Long i = 0;
//		Finder finder;
//		Figure *temp = 0;
//		Long j = 0;
//		Long tmp;
//		Long isHave = 0;
//		Long isOne = 0;
//		Long bigWidth = 0;
//		Long minX = 0;
//		Long isCut = 0;
//		Long lineLength = 0;
//		Long c;
//		Long diagramMinX = 0;
//		Long copyBufferMinX = 0;
//		if (classDiagramForm->selection->GetLength() > 0) {
//			isHave = 1;
//		}if (classDiagramForm->copyBuffer->GetLength() == 1) {
//			isOne = 1;
//		}
//		if (classDiagramForm->isCut == 1) {
//			isCut = 1;
//		}
//		CPoint point;
//		::GetCursorPos(&point); // 바탕화면 커서위치 Get
//		::ScreenToClient(classDiagramForm->GetSafeHwnd(), &point); // 폼영역의 좌표로 변환
//
//		CRect rt = { 0, };
//
//		SmartPointer<Figure*>CopyBufferSmartPointer(classDiagramForm->copyBuffer->CreateIterator());
//		for (CopyBufferSmartPointer->First(); !CopyBufferSmartPointer->IsDone(); CopyBufferSmartPointer->Next()) {
//			if (dynamic_cast<FigureComposite*>(CopyBufferSmartPointer->Current())) {
//				if (CopyBufferSmartPointer->Current() == 0 && CopyBufferSmartPointer->Current()->GetX() < rt.left) {//minimumX
//					rt.left = CopyBufferSmartPointer->Current()->GetX();
//				}
//				else if (CopyBufferSmartPointer->Current() == 0 && CopyBufferSmartPointer->Current()->GetX()            //maximumX
//					+ CopyBufferSmartPointer->Current()->GetWidth() > rt.right) {
//					rt.right = CopyBufferSmartPointer->Current()->GetX() + CopyBufferSmartPointer->Current()->GetWidth();
//				}
//				if (CopyBufferSmartPointer->Current() == 0 && CopyBufferSmartPointer->Current()->GetY() < rt.top) {   //minimumY
//					rt.top = CopyBufferSmartPointer->Current()->GetY();
//				}
//				else if (CopyBufferSmartPointer->Current() == 0 && CopyBufferSmartPointer->Current()->GetY()            //maximumY
//					+ CopyBufferSmartPointer->Current()->GetHeight() > rt.bottom) {
//					rt.bottom = CopyBufferSmartPointer->Current()->GetY() + CopyBufferSmartPointer->Current()->GetHeight();
//				}
//			}
//		}
//		CopyBufferSmartPointer->First();
//		i = 0;
//		while (!CopyBufferSmartPointer->IsDone()) {
//			if (dynamic_cast<Relation*>(CopyBufferSmartPointer->Current())) {
//				if (CopyBufferSmartPointer->Current()->GetX() >= rt.left && CopyBufferSmartPointer->Current()->GetX() <= rt.right &&
//					CopyBufferSmartPointer->Current()->GetY() >= rt.top && CopyBufferSmartPointer->Current()->GetY() <= rt.bottom &&
//					CopyBufferSmartPointer->Current()->GetX() + CopyBufferSmartPointer->Current()->GetWidth() >= rt.left &&
//					CopyBufferSmartPointer->Current()->GetX() + CopyBufferSmartPointer->Current()->GetWidth() <= rt.bottom &&
//					CopyBufferSmartPointer->Current()->GetY() + CopyBufferSmartPointer->Current()->GetHeight() >= rt.top &&
//					CopyBufferSmartPointer->Current()->GetY() + CopyBufferSmartPointer->Current()->GetHeight() <= rt.bottom) {
//					i++;
//				}
//				else {
//					static_cast<Selection*>(classDiagramForm->copyBuffer)->Remove(i);
//				}
//			}
//			CopyBufferSmartPointer->Next();
//		}
//		Long distanceX = point.x - rt.left;
//		Long distanceY = point.y - rt.top;
//		//현재 커서 위치에 해당 Rect가 곂치는 기호들이 있는지 판단
//		rt.left += point.x;
//		rt.top += point.y;
//		rt.right += point.x;
//		rt.bottom += point.y;
//		bool ret = classDiagramForm->diagram->CheckOverlap(rt, 0);
//		if (ret == false) {
//			i = 0;
//			Long j;
//			Long k = 0;
//			Long l = 0;
//			Figure *figure;
//			RollNameBox *rollNameBoxesPoint = RollNameBox::Instance();
//			CPoint cPoint1;
//			CPoint cPoint2;
//			CPoint cPoint3;
//			CPoint cPoint4;
//			CPoint cPoint5;
//			while (i < classDiagramForm->copyBuffer->GetLength()) {
//				figure = classDiagramForm->copyBuffer->GetAt(i);
//				if (dynamic_cast<FigureComposite*>(figure)) { //클래스나 메모면
//					Long startX = figure->GetX();
//					Long startY = figure->GetY();
//					Long endX = figure->GetX() + figure->GetWidth();
//					Long endY = figure->GetY() + figure->GetHeight();
//					figure->Move(distanceX, distanceY); // 해당 클래스나 메모 이동
//
//					classDiagramForm->diagram->Add(figure->Clone());
//
//					FigureComposite *figureComposite = static_cast<FigureComposite*>(classDiagramForm->diagram->GetAt(classDiagramForm->diagram->GetLength() - 1)); // 형변환
//					j = 0;
//					while (j < figureComposite->GetLength()) { // 형변환 한게 관리하면 배열 렝스까지
//						figure = figureComposite->GetAt(j);
//						figure->Move(distanceX, distanceY);
//						if (dynamic_cast<Relation*>(figureComposite->GetAt(j))) {
//							Relation *relation = static_cast<Relation*>(figureComposite->GetAt(j));
//							Long m = 0;
//							while (m < relation->GetLength()) {
//								CPoint point(relation->GetAt(m).x + distanceX, relation->GetAt(m).y + distanceY);
//								relation->Move(m, point);
//								m++;
//							}
//							if (relation->GetLength() == 0) {
//								CPoint startPoint{ relation->GetX(), relation->GetY() };
//								CPoint endPoint{ relation->GetX() + relation->GetWidth(), relation->GetY() + relation->GetHeight() };
//								cPoint1 = rollNameBoxesPoint->GetFirstRollNamePoint(startPoint, endPoint);
//								cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint, endPoint);
//								cPoint3 = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint, endPoint);
//								cPoint4 = rollNameBoxesPoint->GetFourthRollNamePoint(startPoint, endPoint);
//								cPoint5 = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint, endPoint);
//								relation->rollNamePoints->Modify(0, cPoint1);
//								relation->rollNamePoints->Modify(1, cPoint2);
//								relation->rollNamePoints->Modify(2, cPoint3);
//								relation->rollNamePoints->Modify(3, cPoint4);
//								relation->rollNamePoints->Modify(4, cPoint5);
//							}
//							else {
//								CPoint startPoint{ relation->GetX(), relation->GetY() };
//								CPoint endPoint{ relation->GetAt(0).x, relation->GetAt(0).y };
//								cPoint1 = rollNameBoxesPoint->GetFirstRollNamePoint(startPoint, endPoint);
//								cPoint4 = rollNameBoxesPoint->GetFourthRollNamePoint(startPoint, endPoint);
//								relation->rollNamePoints->Modify(0, cPoint1);
//								relation->rollNamePoints->Modify(3, cPoint4);
//
//								CPoint startPoint3{ relation->GetAt(relation->GetLength() - 1).x,
//									relation->GetAt(relation->GetLength() - 1).y };
//								CPoint endPoint3{ relation->GetX() + relation->GetWidth() , relation->GetY() + relation->GetHeight() };
//								cPoint3 = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint3, endPoint3);
//								cPoint5 = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint3, endPoint3);
//								relation->rollNamePoints->Modify(2, cPoint3);
//								relation->rollNamePoints->Modify(4, cPoint5);
//
//								if (relation->GetLength() % 2 == 0) {//짝수
//
//									CPoint startPoint2{ relation->GetAt((relation->GetLength() - 1) / 2).x,
//										relation->GetAt((relation->GetLength() - 1) / 2).y };
//									CPoint endPoint2{ relation->GetAt((relation->GetLength() - 1) / 2 + 1).x,
//										relation->GetAt((relation->GetLength() - 1) / 2 + 1).y };
//									cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, endPoint2);
//									relation->rollNamePoints->Modify(1, cPoint2);
//
//								}
//								else {//홀수
//
//									CPoint startPoint2{ relation->GetAt((relation->GetLength() - 1) / 2).x,
//										relation->GetAt((relation->GetLength() - 1) / 2).y };
//									cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, startPoint2);
//									relation->rollNamePoints->Modify(1, cPoint2);
//
//								}
//							}
//						}
//						if (dynamic_cast<SelfRelation*>(figureComposite->GetAt(j))) {
//							SelfRelation *selfRelation = static_cast<SelfRelation*>(figureComposite->GetAt(j));
//							CPoint startPoint1And4{ selfRelation->GetX(), selfRelation->GetY() };
//							CPoint endPoint1And4{ selfRelation->GetX() ,  selfRelation->GetY() - 40 };
//
//							CPoint startPoint2{ selfRelation->GetX(), selfRelation->GetY() - 40 };
//							CPoint endPoint2{ selfRelation->GetX() + 80,  selfRelation->GetY() - 40 };
//
//							CPoint startPoint3And5{ selfRelation->GetX() + 80, selfRelation->GetY() + 40 };
//							CPoint endPoint3And5{ selfRelation->GetX() + 30,  selfRelation->GetY() + 40 };
//							cPoint1 = rollNameBoxesPoint->GetSelfRelationFirstRollNamePoint(startPoint1And4, endPoint1And4);
//							cPoint2 = rollNameBoxesPoint->GetSelfRelationSecondRollNamePoint(startPoint2, endPoint2);
//							cPoint3 = rollNameBoxesPoint->GetSelfRelationThirdRollNamePoint(startPoint3And5, endPoint3And5);
//							cPoint4 = rollNameBoxesPoint->GetSelfRelationFourthRollNamePoint(startPoint1And4, endPoint1And4);
//							cPoint5 = rollNameBoxesPoint->GetSelfRelationFifthRollNamePoint(startPoint3And5, endPoint3And5);
//							selfRelation->rollNamePoints->Modify(0, cPoint1);
//							selfRelation->rollNamePoints->Modify(1, cPoint2);
//							selfRelation->rollNamePoints->Modify(2, cPoint3);
//							selfRelation->rollNamePoints->Modify(3, cPoint4);
//							selfRelation->rollNamePoints->Modify(4, cPoint5);
//						}
//
//						j++;
//					}
//					k = 0;
//					while (k < classDiagramForm->diagram->GetLength()) {
//						figureComposite = static_cast<FigureComposite*>(classDiagramForm->diagram->GetAt(k));
//						l = 0;
//						while (l < figureComposite->GetLength()) {
//							if (dynamic_cast<Relation*>(figureComposite->GetAt(l))) {
//								Relation *relation = static_cast<Relation*>(figureComposite->GetAt(l));
//								Long relationEndX = relation->GetX() + relation->GetWidth();
//								Long relationEndY = relation->GetY() + relation->GetHeight();
//								if ((startX <= relationEndX && relationEndX <= endX && (startY == relationEndY || endY == relationEndY)) ||
//									(startY <= relationEndY && relationEndY <= endY && (startX == relationEndX || endX == relationEndX))) {
//									relation->EndPointMove(distanceX, distanceY);
//									if (relation->GetLength() == 0) {
//										CPoint startPoint{ relation->GetX(), relation->GetY() };
//										CPoint endPoint{ relation->GetX() + relation->GetWidth(), relation->GetY() + relation->GetHeight() };
//										cPoint1 = rollNameBoxesPoint->GetFirstRollNamePoint(startPoint, endPoint);
//										cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint, endPoint);
//										cPoint3 = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint, endPoint);
//										cPoint4 = rollNameBoxesPoint->GetFourthRollNamePoint(startPoint, endPoint);
//										cPoint5 = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint, endPoint);
//										relation->rollNamePoints->Modify(0, cPoint1);
//										relation->rollNamePoints->Modify(1, cPoint2);
//										relation->rollNamePoints->Modify(2, cPoint3);
//										relation->rollNamePoints->Modify(3, cPoint4);
//										relation->rollNamePoints->Modify(4, cPoint5);
//									}
//									else {
//										CPoint startPoint{ relation->GetX(), relation->GetY() };
//										CPoint endPoint{ relation->GetAt(0).x, relation->GetAt(0).y };
//										cPoint1 = rollNameBoxesPoint->GetFirstRollNamePoint(startPoint, endPoint);
//										cPoint4 = rollNameBoxesPoint->GetFourthRollNamePoint(startPoint, endPoint);
//										relation->rollNamePoints->Modify(0, cPoint1);
//										relation->rollNamePoints->Modify(3, cPoint4);
//
//										CPoint startPoint3{ relation->GetAt(relation->GetLength() - 1).x,
//											relation->GetAt(relation->GetLength() - 1).y };
//										CPoint endPoint3{ relation->GetX() + relation->GetWidth() , relation->GetY() + relation->GetHeight() };
//										cPoint3 = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint3, endPoint3);
//										cPoint5 = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint3, endPoint3);
//										relation->rollNamePoints->Modify(2, cPoint3);
//										relation->rollNamePoints->Modify(4, cPoint5);
//
//										if (relation->GetLength() % 2 == 0) {//짝수
//
//											CPoint startPoint2{ relation->GetAt((relation->GetLength() - 1) / 2).x,
//												relation->GetAt((relation->GetLength() - 1) / 2).y };
//											CPoint endPoint2{ relation->GetAt((relation->GetLength() - 1) / 2 + 1).x,
//												relation->GetAt((relation->GetLength() - 1) / 2 + 1).y };
//											cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, endPoint2);
//											relation->rollNamePoints->Modify(1, cPoint2);
//
//										}
//										else {//홀수
//											CPoint startPoint2{ relation->GetAt((relation->GetLength() - 1) / 2).x,
//												relation->GetAt((relation->GetLength() - 1) / 2).y };
//											cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, startPoint2);
//											relation->rollNamePoints->Modify(1, cPoint2);
//										}
//									}
//								}
//							}
//							l++;
//						}
//						k++;
//					}
//				}
//				i++;
//			}
//		}
//	}
//}