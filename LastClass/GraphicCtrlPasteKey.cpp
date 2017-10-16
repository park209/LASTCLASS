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
		Finder finder;
		Figure *temp = 0;
		Long j = 0;
		Long tmp;
		Long isHave = 0;
		Long isOne = 0;
		Long bigWidth = 0;
		Long minX = 0;
		Long isCut = 0;
		Long lineLength = 0;
		Long c;
		Long diagramMinX = 0;
		Long copyBufferMinX = 0;
		if (classDiagramForm->selection != 0) {
			delete classDiagramForm->selection;
			classDiagramForm->selection = 0;
		}
		classDiagramForm->selection = new Selection(*classDiagramForm->copyBuffer);
		if (classDiagramForm->selection->GetLength() > 0) {
			isHave = 1;
		}if (classDiagramForm->copyBuffer->GetLength() == 1) {
			isOne = 1;
		}
		if (classDiagramForm->isCut == 1) {
			isCut = 1;
		}
	
		Figure * lastObject = 0;
		SmartPointer<Figure*>diagramSmartPointer(classDiagramForm->diagram->CreateIterator());
		for (diagramSmartPointer->First();!diagramSmartPointer->IsDone();diagramSmartPointer->Next()) {
			if (bigWidth == 0 || (diagramSmartPointer->Current()->GetX() + diagramSmartPointer->Current()->GetWidth()) > bigWidth) {
				bigWidth = diagramSmartPointer->Current()->GetX() + diagramSmartPointer->Current()->GetWidth();
				lastObject = diagramSmartPointer->Current();
			}
		}
		SmartPointer<Figure*>CopyBufferSmartPointer(classDiagramForm->copyBuffer->CreateIterator());
		for (CopyBufferSmartPointer->First();!CopyBufferSmartPointer->IsDone();CopyBufferSmartPointer->Next()) {
			if (dynamic_cast<FigureComposite*>(CopyBufferSmartPointer->Current())) {//or memobox
				if (minX == 0 || CopyBufferSmartPointer->Current()->GetX() < minX) {
					minX = CopyBufferSmartPointer->Current()->GetX();
					//isFirst = 1;
				}
			}
		}
		if (lastObject != 0 && dynamic_cast<FigureComposite*>(lastObject)) {
			SmartPointer<Figure*>lastObjectSmartPointer(dynamic_cast<FigureComposite*>(lastObject)->CreateIterator());
			for (lastObjectSmartPointer->First();!lastObjectSmartPointer->IsDone();lastObjectSmartPointer->Next()) {
				if (dynamic_cast<Relation*>(lastObjectSmartPointer->Current())) {
					if (lineLength == 0 || lastObjectSmartPointer->Current()->GetWidth() > lineLength) {
						lineLength = lastObjectSmartPointer->Current()->GetWidth();
					}
				}
			}
		}
		/*if (lineLength < 0) {
			lineLength = -lineLength;
		}*/
		lineLength = 0;
		Figure *object_ = classDiagramForm->copyBuffer->GetAt(0);
		Long condition = 0;
		if (isOne == 1) {
			condition = (bigWidth + object_->GetWidth() + lineLength + 10);
		}
		else {
			condition = bigWidth + (bigWidth - minX) + lineLength + 20;
		}
		if (condition < 4000) {//비트맵의 너비로 조정
			SmartPointer<Figure*>smartPointer(classDiagramForm->copyBuffer->CreateIterator());
			for (smartPointer->First();!smartPointer->IsDone();smartPointer->Next()) {
				tmp = 0;
				c = 0;
				if (dynamic_cast<Class*>(smartPointer->Current())) {
					Class *object = static_cast<Class*>(smartPointer->Current());
					Class *object2 = new Class(*object);
					SmartPointer<Figure*> smartPointer_(object2->CreateIterator());
					for (smartPointer_->First();!smartPointer_->IsDone();smartPointer_->Next()) {
						if (dynamic_cast<Relation*>(smartPointer_->Current())) {
							tmp++;
						}
						else {
							if (isOne == 1) {
								smartPointer_->Current()->Move((bigWidth + 10) + lineLength - object->GetX(), 0);
							}
							else {
								smartPointer_->Current()->Move((bigWidth + 10) + lineLength - minX, 0);
							}
						}
						if (tmp == 0) {
							c++;
						}
					}
					if (isOne == 1) {
						Long k = 0;
						Long e;
						while (k < tmp) {
							j = 0;
							e = 0;
							while (j < object2->GetLength() && e == 0) {
								if (dynamic_cast<Relation*>(object2->GetAt(j))) {
									object2->Remove(j);
									e = 1;
								}
								j++;
							}
							k++;
						}
					}
					else {
						Long s = 0;
						Relation * relation_ = 0;
						Long isRemove;
						while (s < tmp) {
							isRemove = 1;
							relation_ = static_cast<Relation*>(object->GetAt(c));
							for (CopyBufferSmartPointer->First();!CopyBufferSmartPointer->IsDone();CopyBufferSmartPointer->Next()) {
								if (dynamic_cast<Relation*>(CopyBufferSmartPointer->Current())) {
									if (relation_->GetX() == static_cast<Relation*>(CopyBufferSmartPointer->Current())->GetX() &&
										relation_->GetY() == static_cast<Relation*>(CopyBufferSmartPointer->Current())->GetY()) {
										isRemove = 0;
									}
								}
							}
							if (isRemove == 1) {
								object->Remove(c);
								object2->Remove(c);
							}
							else
							{
								c++;
							}
							s++;
						}
					}
					if (isOne == 1) {
						object2->Move((bigWidth + 10) + lineLength - object->GetX(), 0);
					}
					else {
						object2->Move((bigWidth + 10) + lineLength - minX, 0);
					}
					classDiagramForm->diagram->Add(static_cast<Figure*>(object2));
					classDiagramForm->copyBuffer->Correct(static_cast<Figure*>(object2), i);
					if (isHave == 1) {
						classDiagramForm->selection->Correct(static_cast<Figure*>(object2), i);
					}
					else {
						classDiagramForm->selection->Add(static_cast<Figure*>(object2));
					}
				}
				else if (dynamic_cast<MemoBox*>(smartPointer->Current())) {
					/*MemoBox *object = static_cast<MemoBox*>(smartPointer->Current());
					MemoBox *object2 = new MemoBox(*object);
					if (isOne == 1) {
						object2->Move((bigWidth + 10) + lineLength - object->GetX(), 0);
					}
					else {
						object2->Move((bigWidth + 10) + lineLength - minX, 0);
					}
					classDiagramForm->diagram->Add(static_cast<Figure*>(object2));
					classDiagramForm->copyBuffer->Correct(static_cast<Figure*>(object2), i);
					if (isHave == 1) {
						classDiagramForm->selection->Correct(static_cast<Figure*>(object2), i);
					}
					else {
						classDiagramForm->selection->Add(static_cast<Figure*>(object2));
					}
					*/
					MemoBox *object = static_cast<MemoBox*>(smartPointer->Current());
					MemoBox *object2 = new MemoBox(*object);
					tmp = object->GetLength();
					c = 0;
					if (isOne == 1) {
						Long k = 0;
						Long e;
						while (k < tmp) {
							j = 0;
							e = 0;
							while (j < object2->GetLength() && e == 0) {
								if (dynamic_cast<Relation*>(object2->GetAt(j))) {
									object2->Remove(j);
									e = 1;
								}
								j++;
							}
							k++;
						}
					}
					else {
						Long s = 0;
						Relation * relation_ = 0;
						Long isRemove;
						while (s < tmp) {
							isRemove = 1;
							relation_ = static_cast<Relation*>(object->GetAt(c));
							for (CopyBufferSmartPointer->First();!CopyBufferSmartPointer->IsDone();CopyBufferSmartPointer->Next()) {
								if (dynamic_cast<Relation*>(CopyBufferSmartPointer->Current())) {
									if (relation_->GetX() == static_cast<Relation*>(CopyBufferSmartPointer->Current())->GetX() &&
										relation_->GetY() == static_cast<Relation*>(CopyBufferSmartPointer->Current())->GetY()) {
										isRemove = 0;
									}
								}
							}
							if (isRemove == 1) {
								object->Remove(c);
								object2->Remove(c);
							}
							else
							{
								c++;
							}
							s++;
						}
					}
					if (isOne == 1) {
						object2->Move((bigWidth + 10) + lineLength - object->GetX(), 0);
					}
					else {
						object2->Move((bigWidth + 10) + lineLength - minX, 0);
					}
					classDiagramForm->diagram->Add(static_cast<Figure*>(object2));
					classDiagramForm->copyBuffer->Correct(static_cast<Figure*>(object2), i);
					if (isHave == 1) {
						classDiagramForm->selection->Correct(static_cast<Figure*>(object2), i);
					}
					else {
						classDiagramForm->selection->Add(static_cast<Figure*>(object2));
					}
				}
				else if (dynamic_cast<Relation*>(smartPointer->Current())) {
					Relation *objectRelation = static_cast<Relation*>(smartPointer->Current());
					Long f = 0;
					Class *parent = 0;
					Long z;
					CPoint point_;
					FigureComposite *parent_ = 0;
					Long canPaste = 0;
					parent_ = static_cast<FigureComposite*>(finder.GetParents(classDiagramForm->diagram, smartPointer->Current()));
					SmartPointer<Figure*>tempsmartPointer(classDiagramForm->copyBuffer->CreateIterator());
					for (tempsmartPointer->First();!tempsmartPointer->IsDone();tempsmartPointer->Next()) {
						if (dynamic_cast<FigureComposite*>(tempsmartPointer->Current())) {
							if(static_cast<FigureComposite*>(tempsmartPointer->Current())->GetX() == parent_->GetX()&&
							 static_cast<FigureComposite*>(tempsmartPointer->Current())->GetY() == parent_->GetY()){
								canPaste = 1;
								}
							if (static_cast<FigureComposite*>(tempsmartPointer->Current())->GetX() -(bigWidth + 10 + lineLength - minX) == parent_->GetX() &&
								static_cast<FigureComposite*>(tempsmartPointer->Current())->GetY() == parent_->GetY()) {
								canPaste = 1;
							}
						}
					}
					//if (canPaste == 0) {
					//	classDiagramForm->copyBuffer->Remove(i);
						//classDiagramForm->selection->Remove(i);
					//}
					
					if(canPaste==1){
					if (dynamic_cast<Generalization*>(objectRelation)) {
						Generalization* object = static_cast<Generalization*>(smartPointer->Current());
						Generalization* object2 = new Generalization(*object);
						parent = static_cast<Class*>(finder.GetParents(classDiagramForm->diagram, object));
						if (isOne == 1) {
							if (object2->GetY() < parent->GetY() + parent->GetHeight() - 10) {
								static_cast<Figure*>(object2)->Move(0, 30);
								z = 0;
								while (z < object2->GetLength()) {
									point_.x = object2->GetAt(z).x;
									point_.y = object2->GetAt(z).y;
									point_.y += 20;
									object2->Correct(z, point_);
									z++;
								}
							}
							CPoint pointR;
							Long h = 0;
							while (h<object2->rollNamePoints->GetLength()) {
								pointR.x = object2->rollNamePoints->GetAt(h).x;
								pointR.y = object2->rollNamePoints->GetAt(h).y;
								pointR.y += 20;
								object2->rollNamePoints->Modify(h, pointR);
								h++;
							}
							static_cast<Class*>(parent)->Add(object2->Clone());
							temp = static_cast<Class*>(parent)->GetAt(parent->GetLength() - 1);
						}
						else {
							SmartPointer<Figure*> ResmartPointer(classDiagramForm->copyBuffer->CreateIterator());
							for (ResmartPointer->First();!ResmartPointer->IsDone();ResmartPointer->Next()) {
								if (dynamic_cast<Class*>(ResmartPointer->Current())) {
										Long condition_ = 0;
										if (isOne == 1) {
											condition_ = (bigWidth + 10) + lineLength - object->GetX();
										}
										else {
											condition_ = (bigWidth + 10) + lineLength - minX;
										}
										if (ResmartPointer->Current()->GetX() - condition_ == parent->GetX()&&//새로붙여넣기할때 너비만바뀜
											ResmartPointer->Current()->GetY() == parent->GetY()) {
											while (static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetX() != object->GetX()
												|| static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetY() != object->GetY()) {
												f++;//xy 다 같을때만 빠져나옴
											}
											//if (isOne == 1) {isOne이 1일때는 클래스일땐 선다지우고 선한개일떈위에서 처리해줌
												//object2->MovePaste((bigWidth + 10) + lineLength - object->GetX(), 0);
											//}
											//else {
												object2->MovePaste((bigWidth + 10) + lineLength - minX, 0);
											//static_cast<Figure*>(object2)->Move((bigWidth + 10) + lineLength - minX-parent->GetWidth(), 0);
											//}
											z = 0;
											while (z < object2->GetLength()) {
												point_.x = object2->GetAt(z).x;
												point_.y = object2->GetAt(z).y;
												point_.x += (bigWidth + 10) + lineLength - minX;
												point_.y += 0;
												object2->Correct(z, point_);
												z++;
											}
											CPoint pointR;
											Long h = 0;
											while (h<object2->rollNamePoints->GetLength())	{
												pointR.x = object2->rollNamePoints->GetAt(h).x;
												pointR.y = object2->rollNamePoints->GetAt(h).y;
												pointR.x+= (bigWidth + 10) + lineLength - minX;
												object2->rollNamePoints->Modify(h, pointR);
												h++;
											}
											static_cast<Class*>(ResmartPointer->Current())->Correct(object2->Clone(), f);
											temp = static_cast<Class*>(ResmartPointer->Current())->GetAt(f);
										}
									//if (isCut == 1) {
										else if(ResmartPointer->Current()->GetX() == parent->GetX()
										&& ResmartPointer->Current()->GetY() == parent->GetY()) {
										while (static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetX() != object->GetX()
											|| static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetY() != object->GetY()) {
											f++;
										}
										//if (isOne == 1) {
										//	object2->MovePaste((bigWidth + 10) + lineLength - object->GetX(), 0);
										//}
										//else {
											object2->MovePaste((bigWidth + 10) + lineLength - minX, 0);
										//static_cast<Figure*>(object2)->Move((bigWidth + 10) + lineLength - minX-parent->GetWidth(), 0);
										//}
										z = 0;
										while (z < object2->GetLength()) {
											point_.x = object2->GetAt(z).x;
											point_.y = object2->GetAt(z).y;
											point_.x += (bigWidth + 10) + lineLength - minX;
											point_.y += 0;
											object2->Correct(z, point_);
											z++;
										}
										CPoint pointR;
										Long h = 0;
										while (h<object2->rollNamePoints->GetLength()) {
											pointR.x = object2->rollNamePoints->GetAt(h).x;
											pointR.y = object2->rollNamePoints->GetAt(h).y;
											pointR.x += (bigWidth + 10) + lineLength - minX;
											object2->rollNamePoints->Modify(h, pointR);
											h++;
										}
										static_cast<Class*>(ResmartPointer->Current())->Correct(object2->Clone(), f);
										temp = static_cast<Class*>(ResmartPointer->Current())->GetAt(f);
									}
									//}
								}
							}
						}
						classDiagramForm->copyBuffer->Correct(temp, i);
						if (isHave == 1) {
							classDiagramForm->selection->Correct(temp, i);
						}
						else {
							classDiagramForm->selection->Add(temp);
						}
					}
					else if (dynamic_cast<Realization*>(objectRelation)) {
						Realization* object = static_cast<Realization*>(smartPointer->Current());
						Realization* object2 = new Realization(*object);
						parent = static_cast<Class*>(finder.GetParents(classDiagramForm->diagram, object));
						if (isOne == 1) {
							if (object2->GetY() < parent->GetY() + parent->GetHeight() - 10) {
								static_cast<Figure*>(object2)->Move(0, 30);
								z = 0;
								while (z < object2->GetLength()) {
									point_.x = object2->GetAt(z).x;
									point_.y = object2->GetAt(z).y;
									point_.y += 20;
									object2->Correct(z, point_);
									z++;
								}
							}
							CPoint pointR;
							Long h = 0;
							while (h<object2->rollNamePoints->GetLength()) {
								pointR.x = object2->rollNamePoints->GetAt(h).x;
								pointR.y = object2->rollNamePoints->GetAt(h).y;
								pointR.y += 20;
								object2->rollNamePoints->Modify(h, pointR);
								h++;
							}
							static_cast<Class*>(parent)->Add(object2->Clone());
							temp = static_cast<Class*>(parent)->GetAt(parent->GetLength() - 1);
						}
						else {
							SmartPointer<Figure*> ResmartPointer(classDiagramForm->copyBuffer->CreateIterator());
							for (ResmartPointer->First();!ResmartPointer->IsDone();ResmartPointer->Next()) {
								if (dynamic_cast<Class*>(ResmartPointer->Current())) {
									Long condition_ = 0;
									if (isOne == 1) {
										condition_ = (bigWidth + 10) + lineLength - object->GetX();
									}
									else {
										condition_ = (bigWidth + 10) + lineLength - minX;
									}
									if (ResmartPointer->Current()->GetX() - condition_ == parent->GetX() &&//새로붙여넣기할때 너비만바뀜
										ResmartPointer->Current()->GetY() == parent->GetY()) {
										while (static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetX() != object->GetX()
											|| static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetY() != object->GetY()) {
											f++;//xy 다 같을때만 빠져나옴
										}
										//if (isOne == 1) {isOne이 1일때는 클래스일땐 선다지우고 선한개일떈위에서 처리해줌
										//object2->MovePaste((bigWidth + 10) + lineLength - object->GetX(), 0);
										//}
										//else {
										object2->MovePaste((bigWidth + 10) + lineLength - minX, 0);
										//}
										z = 0;
										while (z < object2->GetLength()) {
											point_.x = object2->GetAt(z).x;
											point_.y = object2->GetAt(z).y;
											point_.x += (bigWidth + 10) + lineLength - minX;
											point_.y += 0;
											object2->Correct(z, point_);
											z++;
										}
										CPoint pointR;
										Long h = 0;
										while (h<object2->rollNamePoints->GetLength()) {
											pointR.x = object2->rollNamePoints->GetAt(h).x;
											pointR.y = object2->rollNamePoints->GetAt(h).y;
											pointR.x += (bigWidth + 10) + lineLength - minX;
											object2->rollNamePoints->Modify(h, pointR);
											h++;
										}
										static_cast<Class*>(ResmartPointer->Current())->Correct(object2->Clone(), f);
										temp = static_cast<Class*>(ResmartPointer->Current())->GetAt(f);
									}
									//if (isCut == 1) {
									else if (ResmartPointer->Current()->GetX() == parent->GetX()
										&& ResmartPointer->Current()->GetY() == parent->GetY()) {
										while (static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetX() != object->GetX()
											|| static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetY() != object->GetY()) {
											f++;
										}
										if (isOne == 1) {
											object2->MovePaste((bigWidth + 10) + lineLength - object->GetX(), 0);
										}
										else {
											object2->MovePaste((bigWidth + 10) + lineLength - minX, 0);
										}
										z = 0;
										while (z < object2->GetLength()) {
											point_.x = object2->GetAt(z).x;
											point_.y = object2->GetAt(z).y;
											point_.x += (bigWidth + 10) + lineLength - minX;
											point_.y += 0;
											object2->Correct(z, point_);
											z++;
										}
										CPoint pointR;
										Long h = 0;
										while (h<object2->rollNamePoints->GetLength()) {
											pointR.x = object2->rollNamePoints->GetAt(h).x;
											pointR.y = object2->rollNamePoints->GetAt(h).y;
											pointR.x += (bigWidth + 10) + lineLength - minX;
											object2->rollNamePoints->Modify(h, pointR);
											h++;
										}
										static_cast<Class*>(ResmartPointer->Current())->Correct(object2->Clone(), f);
										temp = static_cast<Class*>(ResmartPointer->Current())->GetAt(f);
									}
									//}
								}
							}
						}
						classDiagramForm->copyBuffer->Correct(temp, i);
						if (isHave == 1) {
							classDiagramForm->selection->Correct(temp, i);
						}
						else {
							classDiagramForm->selection->Add(temp);
						}
					}
					else if (dynamic_cast<Dependency*>(objectRelation)) {
						Dependency* object = static_cast<Dependency*>(smartPointer->Current());
						Dependency* object2 = new Dependency(*object);
						parent = static_cast<Class*>(finder.GetParents(classDiagramForm->diagram, object));
						if (isOne == 1) {
							if (object2->GetY() < parent->GetY() + parent->GetHeight() - 10) {
								static_cast<Figure*>(object2)->Move(0, 30);
								z = 0;
								while (z < object2->GetLength()) {
									point_.x = object2->GetAt(z).x;
									point_.y = object2->GetAt(z).y;
									point_.y += 20;
									object2->Correct(z, point_);
									z++;
								}
							}
							CPoint pointR;
							Long h = 0;
							while (h<object2->rollNamePoints->GetLength()) {
								pointR.x = object2->rollNamePoints->GetAt(h).x;
								pointR.y = object2->rollNamePoints->GetAt(h).y;
								pointR.y += 20;
								object2->rollNamePoints->Modify(h, pointR);
								h++;
							}
							static_cast<Class*>(parent)->Add(object2->Clone());
							temp = static_cast<Class*>(parent)->GetAt(parent->GetLength() - 1);
						}
						else {
							SmartPointer<Figure*> ResmartPointer(classDiagramForm->copyBuffer->CreateIterator());
							for (ResmartPointer->First();!ResmartPointer->IsDone();ResmartPointer->Next()) {
								if (dynamic_cast<Class*>(ResmartPointer->Current())) {
									Long condition_ = 0;
									if (isOne == 1) {
										condition_ = (bigWidth + 10) + lineLength - object->GetX();
									}
									else {
										condition_ = (bigWidth + 10) + lineLength - minX;
									}
									if (ResmartPointer->Current()->GetX() - condition_ == parent->GetX() &&//새로붙여넣기할때 너비만바뀜
										ResmartPointer->Current()->GetY() == parent->GetY()) {
										while (static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetX() != object->GetX()
											|| static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetY() != object->GetY()) {
											f++;//xy 다 같을때만 빠져나옴
										}
										//if (isOne == 1) {isOne이 1일때는 클래스일땐 선다지우고 선한개일떈위에서 처리해줌
										//object2->MovePaste((bigWidth + 10) + lineLength - object->GetX(), 0);
										//}
										//else {
										object2->MovePaste((bigWidth + 10) + lineLength - minX, 0);
										//}
										z = 0;
										while (z < object2->GetLength()) {
											point_.x = object2->GetAt(z).x;
											point_.y = object2->GetAt(z).y;
											point_.x += (bigWidth + 10) + lineLength - minX;
											point_.y += 0;
											object2->Correct(z, point_);
											z++;
										}
										CPoint pointR;
										Long h = 0;
										while (h<object2->rollNamePoints->GetLength()) {
											pointR.x = object2->rollNamePoints->GetAt(h).x;
											pointR.y = object2->rollNamePoints->GetAt(h).y;
											pointR.x += (bigWidth + 10) + lineLength - minX;
											object2->rollNamePoints->Modify(h, pointR);
											h++;
										}
										static_cast<Class*>(ResmartPointer->Current())->Correct(object2->Clone(), f);
										temp = static_cast<Class*>(ResmartPointer->Current())->GetAt(f);
									}
									//if (isCut == 1) {
									else if (ResmartPointer->Current()->GetX() == parent->GetX()
										&& ResmartPointer->Current()->GetY() == parent->GetY()) {
										while (static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetX() != object->GetX()
											|| static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetY() != object->GetY()) {
											f++;
										}
										if (isOne == 1) {
											object2->MovePaste((bigWidth + 10) + lineLength - object->GetX(), 0);
										}
										else {
											object2->MovePaste((bigWidth + 10) + lineLength - minX, 0);
										}
										z = 0;
										while (z < object2->GetLength()) {
											point_.x = object2->GetAt(z).x;
											point_.y = object2->GetAt(z).y;
											point_.x += (bigWidth + 10) + lineLength - minX;
											point_.y += 0;
											object2->Correct(z, point_);
											z++;
										}
										CPoint pointR;
										Long h = 0;
										while (h<object2->rollNamePoints->GetLength()) {
											pointR.x = object2->rollNamePoints->GetAt(h).x;
											pointR.y = object2->rollNamePoints->GetAt(h).y;
											pointR.x += (bigWidth + 10) + lineLength - minX;
											object2->rollNamePoints->Modify(h, pointR);
											h++;
										}
										static_cast<Class*>(ResmartPointer->Current())->Correct(object2->Clone(), f);
										temp = static_cast<Class*>(ResmartPointer->Current())->GetAt(f);
									}
									//}
								}
							}
						}
						classDiagramForm->copyBuffer->Correct(temp, i);
						if (isHave == 1) {
							classDiagramForm->selection->Correct(temp, i);
						}
						else {
							classDiagramForm->selection->Add(temp);
						}
					}
					else if (dynamic_cast<Association*>(objectRelation)) {
						Association* object = static_cast<Association*>(smartPointer->Current());
						Association* object2 = new Association(*object);
						parent = static_cast<Class*>(finder.GetParents(classDiagramForm->diagram, object));
						if (isOne == 1) {
							if (object2->GetY() < parent->GetY() + parent->GetHeight() - 10) {
								static_cast<Figure*>(object2)->Move(0, 30);
								z = 0;
								while (z < object2->GetLength()) {
									point_.x = object2->GetAt(z).x;
									point_.y = object2->GetAt(z).y;
									point_.y += 20;
									object2->Correct(z, point_);
									z++;
								}
							}
							CPoint pointR;
							Long h = 0;
							while (h<object2->rollNamePoints->GetLength()) {
								pointR.x = object2->rollNamePoints->GetAt(h).x;
								pointR.y = object2->rollNamePoints->GetAt(h).y;
								pointR.y += 20;
								object2->rollNamePoints->Modify(h, pointR);
								h++;
							}
							static_cast<Class*>(parent)->Add(object2->Clone());
							temp = static_cast<Class*>(parent)->GetAt(parent->GetLength() - 1);
						}
						else {
							SmartPointer<Figure*> ResmartPointer(classDiagramForm->copyBuffer->CreateIterator());
							for (ResmartPointer->First();!ResmartPointer->IsDone();ResmartPointer->Next()) {
								if (dynamic_cast<Class*>(ResmartPointer->Current())) {
									Long condition_ = 0;
									if (isOne == 1) {
										condition_ = (bigWidth + 10) + lineLength - object->GetX();
									}
									else {
										condition_ = (bigWidth + 10) + lineLength - minX;
									}
									if (ResmartPointer->Current()->GetX() - condition_ == parent->GetX() &&//새로붙여넣기할때 너비만바뀜
										ResmartPointer->Current()->GetY() == parent->GetY()) {
										while (static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetX() != object->GetX()
											|| static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetY() != object->GetY()) {
											f++;//xy 다 같을때만 빠져나옴
										}
										//if (isOne == 1) {isOne이 1일때는 클래스일땐 선다지우고 선한개일떈위에서 처리해줌
										//object2->MovePaste((bigWidth + 10) + lineLength - object->GetX(), 0);
										//}
										//else {
										object2->MovePaste((bigWidth + 10) + lineLength - minX, 0);
										//}
										z = 0;
										while (z < object2->GetLength()) {
											point_.x = object2->GetAt(z).x;
											point_.y = object2->GetAt(z).y;
											point_.x += (bigWidth + 10) + lineLength - minX;
											point_.y += 0;
											object2->Correct(z, point_);
											z++;
										}
										CPoint pointR;
										Long h = 0;
										while (h<object2->rollNamePoints->GetLength()) {
											pointR.x = object2->rollNamePoints->GetAt(h).x;
											pointR.y = object2->rollNamePoints->GetAt(h).y;
											pointR.x += (bigWidth + 10) + lineLength - minX;
											object2->rollNamePoints->Modify(h, pointR);
											h++;
										}
										static_cast<Class*>(ResmartPointer->Current())->Correct(object2->Clone(), f);
										temp = static_cast<Class*>(ResmartPointer->Current())->GetAt(f);
									}
									//if (isCut == 1) {
									else if (ResmartPointer->Current()->GetX() == parent->GetX()
										&& ResmartPointer->Current()->GetY() == parent->GetY()) {
										while (static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetX() != object->GetX()
											|| static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetY() != object->GetY()) {
											f++;
										}
										if (isOne == 1) {
											object2->MovePaste((bigWidth + 10) + lineLength - object->GetX(), 0);
										}
										else {
											object2->MovePaste((bigWidth + 10) + lineLength - minX, 0);
										}
										z = 0;
										while (z < object2->GetLength()) {
											point_.x = object2->GetAt(z).x;
											point_.y = object2->GetAt(z).y;
											point_.x += (bigWidth + 10) + lineLength - minX;
											point_.y += 0;
											object2->Correct(z, point_);
											z++;
										}
										CPoint pointR;
										Long h = 0;
										while (h<object2->rollNamePoints->GetLength()) {
											pointR.x = object2->rollNamePoints->GetAt(h).x;
											pointR.y = object2->rollNamePoints->GetAt(h).y;
											pointR.x += (bigWidth + 10) + lineLength - minX;
											object2->rollNamePoints->Modify(h, pointR);
											h++;
										}
										static_cast<Class*>(ResmartPointer->Current())->Correct(object2->Clone(), f);
										temp = static_cast<Class*>(ResmartPointer->Current())->GetAt(f);
									}
									//}
								}
							}
						}
						classDiagramForm->copyBuffer->Correct(temp, i);
						if (isHave == 1) {
							classDiagramForm->selection->Correct(temp, i);
						}
						else {
							classDiagramForm->selection->Add(temp);
						}
					}
					else if (dynamic_cast<DirectedAssociation*>(objectRelation)) {
						DirectedAssociation* object = static_cast<DirectedAssociation*>(smartPointer->Current());
						DirectedAssociation* object2 = new DirectedAssociation(*object);
						parent = static_cast<Class*>(finder.GetParents(classDiagramForm->diagram, object));
						if (isOne == 1) {
							if (object2->GetY() < parent->GetY() + parent->GetHeight() - 10) {
								static_cast<Figure*>(object2)->Move(0, 30);
								z = 0;
								while (z < object2->GetLength()) {
									point_.x = object2->GetAt(z).x;
									point_.y = object2->GetAt(z).y;
									point_.y += 20;
									object2->Correct(z, point_);
									z++;
								}
							}
							CPoint pointR;
							Long h = 0;
							while (h<object2->rollNamePoints->GetLength()) {
								pointR.x = object2->rollNamePoints->GetAt(h).x;
								pointR.y = object2->rollNamePoints->GetAt(h).y;
								pointR.y += 20;
								object2->rollNamePoints->Modify(h, pointR);
								h++;
							}
							static_cast<Class*>(parent)->Add(object2->Clone());
							temp = static_cast<Class*>(parent)->GetAt(parent->GetLength() - 1);
						}
						else {
							SmartPointer<Figure*> ResmartPointer(classDiagramForm->copyBuffer->CreateIterator());
							for (ResmartPointer->First();!ResmartPointer->IsDone();ResmartPointer->Next()) {
								if (dynamic_cast<Class*>(ResmartPointer->Current())) {
									Long condition_ = 0;
									if (isOne == 1) {
										condition_ = (bigWidth + 10) + lineLength - object->GetX();
									}
									else {
										condition_ = (bigWidth + 10) + lineLength - minX;
									}
									if (ResmartPointer->Current()->GetX() - condition_ == parent->GetX() &&//새로붙여넣기할때 너비만바뀜
										ResmartPointer->Current()->GetY() == parent->GetY()) {
										while (static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetX() != object->GetX()
											|| static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetY() != object->GetY()) {
											f++;//xy 다 같을때만 빠져나옴
										}
										//if (isOne == 1) {isOne이 1일때는 클래스일땐 선다지우고 선한개일떈위에서 처리해줌
										//object2->MovePaste((bigWidth + 10) + lineLength - object->GetX(), 0);
										//}
										//else {
										object2->MovePaste((bigWidth + 10) + lineLength - minX, 0);
										//}
										z = 0;
										while (z < object2->GetLength()) {
											point_.x = object2->GetAt(z).x;
											point_.y = object2->GetAt(z).y;
											point_.x += (bigWidth + 10) + lineLength - minX;
											point_.y += 0;
											object2->Correct(z, point_);
											z++;
										}
										CPoint pointR;
										Long h = 0;
										while (h<object2->rollNamePoints->GetLength()) {
											pointR.x = object2->rollNamePoints->GetAt(h).x;
											pointR.y = object2->rollNamePoints->GetAt(h).y;
											pointR.x += (bigWidth + 10) + lineLength - minX;
											object2->rollNamePoints->Modify(h, pointR);
											h++;
										}
										static_cast<Class*>(ResmartPointer->Current())->Correct(object2->Clone(), f);
										temp = static_cast<Class*>(ResmartPointer->Current())->GetAt(f);
									}
									//if (isCut == 1) {
									else if (ResmartPointer->Current()->GetX() == parent->GetX()
										&& ResmartPointer->Current()->GetY() == parent->GetY()) {
										while (static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetX() != object->GetX()
											|| static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetY() != object->GetY()) {
											f++;
										}
										if (isOne == 1) {
											object2->MovePaste((bigWidth + 10) + lineLength - object->GetX(), 0);
										}
										else {
											object2->MovePaste((bigWidth + 10) + lineLength - minX, 0);
										}
										z = 0;
										while (z < object2->GetLength()) {
											point_.x = object2->GetAt(z).x;
											point_.y = object2->GetAt(z).y;
											point_.x += (bigWidth + 10) + lineLength - minX;
											point_.y += 0;
											object2->Correct(z, point_);
											z++;
										}
										CPoint pointR;
										Long h = 0;
										while (h<object2->rollNamePoints->GetLength()) {
											pointR.x = object2->rollNamePoints->GetAt(h).x;
											pointR.y = object2->rollNamePoints->GetAt(h).y;
											pointR.x += (bigWidth + 10) + lineLength - minX;
											object2->rollNamePoints->Modify(h, pointR);
											h++;
										}
										static_cast<Class*>(ResmartPointer->Current())->Correct(object2->Clone(), f);
										temp = static_cast<Class*>(ResmartPointer->Current())->GetAt(f);
									}
									//}
								}
							}
						}
						classDiagramForm->copyBuffer->Correct(temp, i);
						if (isHave == 1) {
							classDiagramForm->selection->Correct(temp, i);
						}
						else {
							classDiagramForm->selection->Add(temp);
						}
					}
					else if (dynamic_cast<Aggregation*>(objectRelation)) {
						Aggregation* object = static_cast<Aggregation*>(smartPointer->Current());
						Aggregation* object2 = new Aggregation(*object);
						parent = static_cast<Class*>(finder.GetParents(classDiagramForm->diagram, object));
						if (isOne == 1) {
							if (object2->GetY() < parent->GetY() + parent->GetHeight() - 10) {
								static_cast<Figure*>(object2)->Move(0, 30);
								z = 0;
								while (z < object2->GetLength()) {
									point_.x = object2->GetAt(z).x;
									point_.y = object2->GetAt(z).y;
									point_.y += 20;
									object2->Correct(z, point_);
									z++;
								}
							}
							CPoint pointR;
							Long h = 0;
							while (h<object2->rollNamePoints->GetLength()) {
								pointR.x = object2->rollNamePoints->GetAt(h).x;
								pointR.y = object2->rollNamePoints->GetAt(h).y;
								pointR.y += 20;
								object2->rollNamePoints->Modify(h, pointR);
								h++;
							}
							static_cast<Class*>(parent)->Add(object2->Clone());
							temp = static_cast<Class*>(parent)->GetAt(parent->GetLength() - 1);
						}
						else {
							SmartPointer<Figure*> ResmartPointer(classDiagramForm->copyBuffer->CreateIterator());
							for (ResmartPointer->First();!ResmartPointer->IsDone();ResmartPointer->Next()) {
								if (dynamic_cast<Class*>(ResmartPointer->Current())) {
									Long condition_ = 0;
									if (isOne == 1) {
										condition_ = (bigWidth + 10) + lineLength - object->GetX();
									}
									else {
										condition_ = (bigWidth + 10) + lineLength - minX;
									}
									if (ResmartPointer->Current()->GetX() - condition_ == parent->GetX() &&//새로붙여넣기할때 너비만바뀜
										ResmartPointer->Current()->GetY() == parent->GetY()) {
										while (static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetX() != object->GetX()
											|| static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetY() != object->GetY()) {
											f++;//xy 다 같을때만 빠져나옴
										}
										//if (isOne == 1) {isOne이 1일때는 클래스일땐 선다지우고 선한개일떈위에서 처리해줌
										//object2->MovePaste((bigWidth + 10) + lineLength - object->GetX(), 0);
										//}
										//else {
										object2->MovePaste((bigWidth + 10) + lineLength - minX, 0);
										//}
										z = 0;
										while (z < object2->GetLength()) {
											point_.x = object2->GetAt(z).x;
											point_.y = object2->GetAt(z).y;
											point_.x += (bigWidth + 10) + lineLength - minX;
											point_.y += 0;
											object2->Correct(z, point_);
											z++;
										}
										CPoint pointR;
										Long h = 0;
										while (h<object2->rollNamePoints->GetLength()) {
											pointR.x = object2->rollNamePoints->GetAt(h).x;
											pointR.y = object2->rollNamePoints->GetAt(h).y;
											pointR.x += (bigWidth + 10) + lineLength - minX;
											object2->rollNamePoints->Modify(h, pointR);
											h++;
										}
										static_cast<Class*>(ResmartPointer->Current())->Correct(object2->Clone(), f);
										temp = static_cast<Class*>(ResmartPointer->Current())->GetAt(f);
									}
									//if (isCut == 1) {
									else if (ResmartPointer->Current()->GetX() == parent->GetX()
										&& ResmartPointer->Current()->GetY() == parent->GetY()) {
										while (static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetX() != object->GetX()
											|| static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetY() != object->GetY()) {
											f++;
										}
										if (isOne == 1) {
											object2->MovePaste((bigWidth + 10) + lineLength - object->GetX(), 0);
										}
										else {
											object2->MovePaste((bigWidth + 10) + lineLength - minX, 0);
										}
										z = 0;
										while (z < object2->GetLength()) {
											point_.x = object2->GetAt(z).x;
											point_.y = object2->GetAt(z).y;
											point_.x += (bigWidth + 10) + lineLength - minX;
											point_.y += 0;
											object2->Correct(z, point_);
											z++;
										}
										CPoint pointR;
										Long h = 0;
										while (h<object2->rollNamePoints->GetLength()) {
											pointR.x = object2->rollNamePoints->GetAt(h).x;
											pointR.y = object2->rollNamePoints->GetAt(h).y;
											pointR.x += (bigWidth + 10) + lineLength - minX;
											object2->rollNamePoints->Modify(h, pointR);
											h++;
										}
										static_cast<Class*>(ResmartPointer->Current())->Correct(object2->Clone(), f);
										temp = static_cast<Class*>(ResmartPointer->Current())->GetAt(f);
									}
									//}
								}
							}
						}
						classDiagramForm->copyBuffer->Correct(temp, i);
						if (isHave == 1) {
							classDiagramForm->selection->Correct(temp, i);
						}
						else {
							classDiagramForm->selection->Add(temp);
						}
					}
					else if (dynamic_cast<Aggregations*>(objectRelation)) {
						Aggregations* object = static_cast<Aggregations*>(smartPointer->Current());
						Aggregations* object2 = new Aggregations(*object);
						parent = static_cast<Class*>(finder.GetParents(classDiagramForm->diagram, object));
						if (isOne == 1) {
							if (object2->GetY() < parent->GetY() + parent->GetHeight() - 10) {
								static_cast<Figure*>(object2)->Move(0, 30);
								z = 0;
								while (z < object2->GetLength()) {
									point_.x = object2->GetAt(z).x;
									point_.y = object2->GetAt(z).y;
									point_.y += 20;
									object2->Correct(z, point_);
									z++;
								}
							}
							CPoint pointR;
							Long h = 0;
							while (h<object2->rollNamePoints->GetLength()) {
								pointR.x = object2->rollNamePoints->GetAt(h).x;
								pointR.y = object2->rollNamePoints->GetAt(h).y;
								pointR.y += 20;
								object2->rollNamePoints->Modify(h, pointR);
								h++;
							}
							static_cast<Class*>(parent)->Add(object2->Clone());
							temp = static_cast<Class*>(parent)->GetAt(parent->GetLength() - 1);
						}
						else {
							SmartPointer<Figure*> ResmartPointer(classDiagramForm->copyBuffer->CreateIterator());
							for (ResmartPointer->First();!ResmartPointer->IsDone();ResmartPointer->Next()) {
								if (dynamic_cast<Class*>(ResmartPointer->Current())) {
									Long condition_ = 0;
									if (isOne == 1) {
										condition_ = (bigWidth + 10) + lineLength - object->GetX();
									}
									else {
										condition_ = (bigWidth + 10) + lineLength - minX;
									}
									if (ResmartPointer->Current()->GetX() - condition_ == parent->GetX() &&//새로붙여넣기할때 너비만바뀜
										ResmartPointer->Current()->GetY() == parent->GetY()) {
										while (static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetX() != object->GetX()
											|| static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetY() != object->GetY()) {
											f++;//xy 다 같을때만 빠져나옴
										}
										//if (isOne == 1) {isOne이 1일때는 클래스일땐 선다지우고 선한개일떈위에서 처리해줌
										//object2->MovePaste((bigWidth + 10) + lineLength - object->GetX(), 0);
										//}
										//else {
										object2->MovePaste((bigWidth + 10) + lineLength - minX, 0);
										//}
										z = 0;
										while (z < object2->GetLength()) {
											point_.x = object2->GetAt(z).x;
											point_.y = object2->GetAt(z).y;
											point_.x += (bigWidth + 10) + lineLength - minX;
											point_.y += 0;
											object2->Correct(z, point_);
											z++;
										}
										CPoint pointR;
										Long h = 0;
										while (h<object2->rollNamePoints->GetLength()) {
											pointR.x = object2->rollNamePoints->GetAt(h).x;
											pointR.y = object2->rollNamePoints->GetAt(h).y;
											pointR.x += (bigWidth + 10) + lineLength - minX;
											object2->rollNamePoints->Modify(h, pointR);
											h++;
										}
										static_cast<Class*>(ResmartPointer->Current())->Correct(object2->Clone(), f);
										temp = static_cast<Class*>(ResmartPointer->Current())->GetAt(f);
									}
									//if (isCut == 1) {
									else if (ResmartPointer->Current()->GetX() == parent->GetX()
										&& ResmartPointer->Current()->GetY() == parent->GetY()) {
										while (static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetX() != object->GetX()
											|| static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetY() != object->GetY()) {
											f++;
										}
										if (isOne == 1) {
											object2->MovePaste((bigWidth + 10) + lineLength - object->GetX(), 0);
										}
										else {
											object2->MovePaste((bigWidth + 10) + lineLength - minX, 0);
										}
										z = 0;
										while (z < object2->GetLength()) {
											point_.x = object2->GetAt(z).x;
											point_.y = object2->GetAt(z).y;
											point_.x += (bigWidth + 10) + lineLength - minX;
											point_.y += 0;
											object2->Correct(z, point_);
											z++;
										}
										CPoint pointR;
										Long h = 0;
										while (h<object2->rollNamePoints->GetLength()) {
											pointR.x = object2->rollNamePoints->GetAt(h).x;
											pointR.y = object2->rollNamePoints->GetAt(h).y;
											pointR.x += (bigWidth + 10) + lineLength - minX;
											object2->rollNamePoints->Modify(h, pointR);
											h++;
										}
										static_cast<Class*>(ResmartPointer->Current())->Correct(object2->Clone(), f);
										temp = static_cast<Class*>(ResmartPointer->Current())->GetAt(f);
									}
									//}
								}
							}
						}
						classDiagramForm->copyBuffer->Correct(temp, i);
						if (isHave == 1) {
							classDiagramForm->selection->Correct(temp, i);
						}
						else {
							classDiagramForm->selection->Add(temp);
						}
					}
					else if (dynamic_cast<Composition*>(objectRelation)) {
						Composition* object = static_cast<Composition*>(smartPointer->Current());
						Composition* object2 = new Composition(*object);
						parent = static_cast<Class*>(finder.GetParents(classDiagramForm->diagram, object));
						if (isOne == 1) {
							if (object2->GetY() < parent->GetY() + parent->GetHeight() - 10) {
								static_cast<Figure*>(object2)->Move(0, 30);
								z = 0;
								while (z < object2->GetLength()) {
									point_.x = object2->GetAt(z).x;
									point_.y = object2->GetAt(z).y;
									point_.y += 20;
									object2->Correct(z, point_);
									z++;
								}
							}
							CPoint pointR;
							Long h = 0;
							while (h<object2->rollNamePoints->GetLength()) {
								pointR.x = object2->rollNamePoints->GetAt(h).x;
								pointR.y = object2->rollNamePoints->GetAt(h).y;
								pointR.y += 20;
								object2->rollNamePoints->Modify(h, pointR);
								h++;
							}
							static_cast<Class*>(parent)->Add(object2->Clone());
							temp = static_cast<Class*>(parent)->GetAt(parent->GetLength() - 1);
						}
						else {
							SmartPointer<Figure*> ResmartPointer(classDiagramForm->copyBuffer->CreateIterator());
							for (ResmartPointer->First();!ResmartPointer->IsDone();ResmartPointer->Next()) {
								if (dynamic_cast<Class*>(ResmartPointer->Current())) {
									Long condition_ = 0;
									if (isOne == 1) {
										condition_ = (bigWidth + 10) + lineLength - object->GetX();
									}
									else {
										condition_ = (bigWidth + 10) + lineLength - minX;
									}
									if (ResmartPointer->Current()->GetX() - condition_ == parent->GetX() &&//새로붙여넣기할때 너비만바뀜
										ResmartPointer->Current()->GetY() == parent->GetY()) {
										while (static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetX() != object->GetX()
											|| static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetY() != object->GetY()) {
											f++;//xy 다 같을때만 빠져나옴
										}
										//if (isOne == 1) {isOne이 1일때는 클래스일땐 선다지우고 선한개일떈위에서 처리해줌
										//object2->MovePaste((bigWidth + 10) + lineLength - object->GetX(), 0);
										//}
										//else {
										object2->MovePaste((bigWidth + 10) + lineLength - minX, 0);
										//}
										z = 0;
										while (z < object2->GetLength()) {
											point_.x = object2->GetAt(z).x;
											point_.y = object2->GetAt(z).y;
											point_.x += (bigWidth + 10) + lineLength - minX;
											point_.y += 0;
											object2->Correct(z, point_);
											z++;
										}
										CPoint pointR;
										Long h = 0;
										while (h<object2->rollNamePoints->GetLength()) {
											pointR.x = object2->rollNamePoints->GetAt(h).x;
											pointR.y = object2->rollNamePoints->GetAt(h).y;
											pointR.x += (bigWidth + 10) + lineLength - minX;
											object2->rollNamePoints->Modify(h, pointR);
											h++;
										}
										static_cast<Class*>(ResmartPointer->Current())->Correct(object2->Clone(), f);
										temp = static_cast<Class*>(ResmartPointer->Current())->GetAt(f);
									}
									//if (isCut == 1) {
									else if (ResmartPointer->Current()->GetX() == parent->GetX()
										&& ResmartPointer->Current()->GetY() == parent->GetY()) {
										while (static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetX() != object->GetX()
											|| static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetY() != object->GetY()) {
											f++;
										}
										if (isOne == 1) {
											object2->MovePaste((bigWidth + 10) + lineLength - object->GetX(), 0);
										}
										else {
											object2->MovePaste((bigWidth + 10) + lineLength - minX, 0);
										}
										z = 0;
										while (z < object2->GetLength()) {
											point_.x = object2->GetAt(z).x;
											point_.y = object2->GetAt(z).y;
											point_.x += (bigWidth + 10) + lineLength - minX;
											point_.y += 0;
											object2->Correct(z, point_);
											z++;
										}
										CPoint pointR;
										Long h = 0;
										while (h<object2->rollNamePoints->GetLength()) {
											pointR.x = object2->rollNamePoints->GetAt(h).x;
											pointR.y = object2->rollNamePoints->GetAt(h).y;
											pointR.x += (bigWidth + 10) + lineLength - minX;
											object2->rollNamePoints->Modify(h, pointR);
											h++;
										}
										static_cast<Class*>(ResmartPointer->Current())->Correct(object2->Clone(), f);
										temp = static_cast<Class*>(ResmartPointer->Current())->GetAt(f);
									}
									//}
								}
							}
						}
						classDiagramForm->copyBuffer->Correct(temp, i);
						if (isHave == 1) {
							classDiagramForm->selection->Correct(temp, i);
						}
						else {
							classDiagramForm->selection->Add(temp);
						}
					}
					else if (dynamic_cast<Compositions*>(objectRelation)) {
						Compositions* object = static_cast<Compositions*>(smartPointer->Current());
						Compositions* object2 = new Compositions(*object);
						parent = static_cast<Class*>(finder.GetParents(classDiagramForm->diagram, object));
						if (isOne == 1) {
							if (object2->GetY() < parent->GetY() + parent->GetHeight() - 10) {
								static_cast<Figure*>(object2)->Move(0, 30);
								z = 0;
								while (z < object2->GetLength()) {
									point_.x = object2->GetAt(z).x;
									point_.y = object2->GetAt(z).y;
									point_.y += 20;
									object2->Correct(z, point_);
									z++;
								}
							}
							CPoint pointR;
							Long h = 0;
							while (h<object2->rollNamePoints->GetLength()) {
								pointR.x = object2->rollNamePoints->GetAt(h).x;
								pointR.y = object2->rollNamePoints->GetAt(h).y;
								pointR.y += 20;
								object2->rollNamePoints->Modify(h, pointR);
								h++;
							}
							static_cast<Class*>(parent)->Add(object2->Clone());
							temp = static_cast<Class*>(parent)->GetAt(parent->GetLength() - 1);
						}
						else {
							SmartPointer<Figure*> ResmartPointer(classDiagramForm->copyBuffer->CreateIterator());
							for (ResmartPointer->First();!ResmartPointer->IsDone();ResmartPointer->Next()) {
								if (dynamic_cast<Class*>(ResmartPointer->Current())) {
									Long condition_ = 0;
									if (isOne == 1) {
										condition_ = (bigWidth + 10) + lineLength - object->GetX();
									}
									else {
										condition_ = (bigWidth + 10) + lineLength - minX;
									}
									if (ResmartPointer->Current()->GetX() - condition_ == parent->GetX() &&//새로붙여넣기할때 너비만바뀜
										ResmartPointer->Current()->GetY() == parent->GetY()) {
										while (static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetX() != object->GetX()
											|| static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetY() != object->GetY()) {
											f++;//xy 다 같을때만 빠져나옴
										}
										//if (isOne == 1) {isOne이 1일때는 클래스일땐 선다지우고 선한개일떈위에서 처리해줌
										//object2->MovePaste((bigWidth + 10) + lineLength - object->GetX(), 0);
										//}
										//else {
										object2->MovePaste((bigWidth + 10) + lineLength - minX, 0);
										//}
										z = 0;
										while (z < object2->GetLength()) {
											point_.x = object2->GetAt(z).x;
											point_.y = object2->GetAt(z).y;
											point_.x += (bigWidth + 10) + lineLength - minX;
											point_.y += 0;
											object2->Correct(z, point_);
											z++;
										}
										CPoint pointR;
										Long h = 0;
										while (h<object2->rollNamePoints->GetLength()) {
											pointR.x = object2->rollNamePoints->GetAt(h).x;
											pointR.y = object2->rollNamePoints->GetAt(h).y;
											pointR.x += (bigWidth + 10) + lineLength - minX;
											object2->rollNamePoints->Modify(h, pointR);
											h++;
										}
										static_cast<Class*>(ResmartPointer->Current())->Correct(object2->Clone(), f);
										temp = static_cast<Class*>(ResmartPointer->Current())->GetAt(f);
									}
									//if (isCut == 1) {
									else if (ResmartPointer->Current()->GetX() == parent->GetX()
										&& ResmartPointer->Current()->GetY() == parent->GetY()) {
										while (static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetX() != object->GetX()
											|| static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetY() != object->GetY()) {
											f++;
										}
										if (isOne == 1) {
											object2->MovePaste((bigWidth + 10) + lineLength - object->GetX(), 0);
										}
										else {
											object2->MovePaste((bigWidth + 10) + lineLength - minX, 0);
										}
										z = 0;
										while (z < object2->GetLength()) {
											point_.x = object2->GetAt(z).x;
											point_.y = object2->GetAt(z).y;
											point_.x += (bigWidth + 10) + lineLength - minX;
											point_.y += 0;
											object2->Correct(z, point_);
											z++;
										}
										CPoint pointR;
										Long h = 0;
										while (h<object2->rollNamePoints->GetLength()) {
											pointR.x = object2->rollNamePoints->GetAt(h).x;
											pointR.y = object2->rollNamePoints->GetAt(h).y;
											pointR.x += (bigWidth + 10) + lineLength - minX;
											object2->rollNamePoints->Modify(h, pointR);
											h++;
										}
										static_cast<Class*>(ResmartPointer->Current())->Correct(object2->Clone(), f);
										temp = static_cast<Class*>(ResmartPointer->Current())->GetAt(f);
									}
									//}
								}
							}
						}
						classDiagramForm->copyBuffer->Correct(temp, i);
						if (isHave == 1) {
							classDiagramForm->selection->Correct(temp, i);
						}
						else {
							classDiagramForm->selection->Add(temp);
						}
					}
					else if (dynamic_cast<MemoLine*>(objectRelation)) {
							MemoLine* object = static_cast<MemoLine*>(smartPointer->Current());
							MemoLine* object2 = new MemoLine(*object);
					parent_ = static_cast<FigureComposite*>(finder.GetParents(classDiagramForm->diagram, object));
					if (isOne == 1) {
						if (object2->GetY() < parent_->GetY() + parent_->GetHeight() - 10) {
							static_cast<Figure*>(object2)->Move(0, 30);
							z = 0;
							while (z < object2->GetLength()) {
								point_.x = object2->GetAt(z).x;
								point_.y = object2->GetAt(z).y;
								point_.y += 20;
								object2->Correct(z, point_);
								z++;
							}
						}
						CPoint pointR;
						Long h = 0;
						while (h<object2->rollNamePoints->GetLength()) {
							pointR.x = object2->rollNamePoints->GetAt(h).x;
							pointR.y = object2->rollNamePoints->GetAt(h).y;
							pointR.y += 20;
							object2->rollNamePoints->Modify(h, pointR);
							h++;
						}
						static_cast<FigureComposite*>(parent_)->Add(object2->Clone());
						temp = static_cast<FigureComposite*>(parent_)->GetAt(parent->GetLength() - 1);
					}
					else {
						SmartPointer<Figure*> ResmartPointer(classDiagramForm->copyBuffer->CreateIterator());
						for (ResmartPointer->First();!ResmartPointer->IsDone();ResmartPointer->Next()) {
							if (dynamic_cast<FigureComposite*>(ResmartPointer->Current())) {
								Long condition_ = 0;
								if (isOne == 1) {
									condition_ = (bigWidth + 10) + lineLength - object->GetX();
								}
								else {
									condition_ = (bigWidth + 10) + lineLength - minX;
								}
								if (ResmartPointer->Current()->GetX() - condition_ == parent_->GetX() &&//새로붙여넣기할때 너비만바뀜
									ResmartPointer->Current()->GetY() == parent_->GetY()) {
									while (static_cast<FigureComposite*>(ResmartPointer->Current())->GetAt(f)->GetX() != object->GetX()
										|| static_cast<FigureComposite*>(ResmartPointer->Current())->GetAt(f)->GetY() != object->GetY()) {
										f++;//xy 다 같을때만 빠져나옴
									}
									//if (isOne == 1) {isOne이 1일때는 클래스일땐 선다지우고 선한개일떈위에서 처리해줌
									//object2->MovePaste((bigWidth + 10) + lineLength - object->GetX(), 0);
									//}
									//else {
									object2->MovePaste((bigWidth + 10) + lineLength - minX, 0);
									//}
									z = 0;
									while (z < object2->GetLength()) {
										point_.x = object2->GetAt(z).x;
										point_.y = object2->GetAt(z).y;
										point_.x += (bigWidth + 10) + lineLength - minX;
										point_.y += 0;
										object2->Correct(z, point_);
										z++;
									}
									CPoint pointR;
									Long h = 0;
									while (h<object2->rollNamePoints->GetLength()) {
										pointR.x = object2->rollNamePoints->GetAt(h).x;
										pointR.y = object2->rollNamePoints->GetAt(h).y;
										pointR.x += (bigWidth + 10) + lineLength - minX;
										object2->rollNamePoints->Modify(h, pointR);
										h++;
									}
									static_cast<FigureComposite*>(ResmartPointer->Current())->Correct(f,object2->Clone());
									temp = static_cast<FigureComposite*>(ResmartPointer->Current())->GetAt(f);
								}
								//if (isCut == 1) {
								else if (ResmartPointer->Current()->GetX() == parent_->GetX()
									&& ResmartPointer->Current()->GetY() == parent_->GetY()) {
									while (static_cast<FigureComposite*>(ResmartPointer->Current())->GetAt(f)->GetX() != object->GetX()
										|| static_cast<FigureComposite*>(ResmartPointer->Current())->GetAt(f)->GetY() != object->GetY()) {
										f++;
									}
									if (isOne == 1) {
										object2->MovePaste((bigWidth + 10) + lineLength - object->GetX(), 0);
									}
									else {
										object2->MovePaste((bigWidth + 10) + lineLength - minX, 0);
									}
									z = 0;
									while (z < object2->GetLength()) {
										point_.x = object2->GetAt(z).x;
										point_.y = object2->GetAt(z).y;
										point_.x += (bigWidth + 10) + lineLength - minX;
										point_.y += 0;
										object2->Correct(z, point_);
										z++;
									}
									CPoint pointR;
									Long h = 0;
									while (h<object2->rollNamePoints->GetLength()) {
										pointR.x = object2->rollNamePoints->GetAt(h).x;
										pointR.y = object2->rollNamePoints->GetAt(h).y;
										pointR.x += (bigWidth + 10) + lineLength - minX;
										object2->rollNamePoints->Modify(h, pointR);
										h++;
									}
									static_cast<FigureComposite*>(ResmartPointer->Current())->Correct(f, object2->Clone());
									temp = static_cast<FigureComposite*>(ResmartPointer->Current())->GetAt(f);
								}
								//}
							}
						}
					}
					classDiagramForm->copyBuffer->Correct(temp, i);
					if (isHave == 1) {
						classDiagramForm->selection->Correct(temp, i);
					}
					else {
						classDiagramForm->selection->Add(temp);
					}
		          }//memoline
				}//copypaste가 1일때
			  }//relation
			  i++;
			}//for
			if (isCut == 1) {
				classDiagramForm->isCut = 0;
			}
			if (classDiagramForm->copyBuffer != 0) {
				delete classDiagramForm->copyBuffer;
				classDiagramForm->copyBuffer = 0;
			}
			classDiagramForm->copyBuffer = new Selection(*classDiagramForm->selection);
		}//condition
	}//copybuffer가 null이 아닐떄
}//끝

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