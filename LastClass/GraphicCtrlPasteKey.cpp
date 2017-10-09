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
		Long tmp = 0;
		Long isHave = 0;
		Long isOne = 0;
		Long bigWidth = 0;
		Long minX = 0;
		Long isCut = 0;
		Long lineLength = 0;
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
			if (minX == 0 || diagramSmartPointer->Current()->GetX() < minX) {
				minX = diagramSmartPointer->Current()->GetX();
			}
			if (bigWidth == 0 || (diagramSmartPointer->Current()->GetX() + diagramSmartPointer->Current()->GetWidth()) > bigWidth) {
				bigWidth = diagramSmartPointer->Current()->GetX() + diagramSmartPointer->Current()->GetWidth();
				lastObject = diagramSmartPointer->Current();
			}
		}
		SmartPointer<Figure*>CopyBufferSmartPointer(classDiagramForm->copyBuffer->CreateIterator());
		for (CopyBufferSmartPointer->First();!CopyBufferSmartPointer->IsDone();CopyBufferSmartPointer->Next()) {
			if (minX == 0 || CopyBufferSmartPointer->Current()->GetX() < minX) {
				minX = CopyBufferSmartPointer->Current()->GetX();
			}
			if (bigWidth == 0 || (CopyBufferSmartPointer->Current()->GetX() + CopyBufferSmartPointer->Current()->GetWidth()) > bigWidth) {
				bigWidth = CopyBufferSmartPointer->Current()->GetX() + CopyBufferSmartPointer->Current()->GetWidth();
				lastObject = CopyBufferSmartPointer->Current();
			}
		}
		if (lastObject != 0 && dynamic_cast<Class*>(lastObject)) {
			SmartPointer<Figure*>lastObjectSmartPointer(dynamic_cast<Class*>(lastObject)->CreateIterator());
			for (lastObjectSmartPointer->First();!lastObjectSmartPointer->IsDone();lastObjectSmartPointer->Next()) {
				if (dynamic_cast<Relation*>(lastObjectSmartPointer->Current())) {
					if (lineLength == 0 || lastObjectSmartPointer->Current()->GetWidth() > lineLength) {
						lineLength = lastObjectSmartPointer->Current()->GetWidth();
					}
				}
			}
		}
		Figure *object_ = classDiagramForm->copyBuffer->GetAt(0);
		Long condition = 0;
		if (isOne == 1) {
			condition = (bigWidth + object_->GetWidth() +lineLength+ 10);
		}
		else {
			condition = bigWidth + (bigWidth - minX)+lineLength + 20;
		}
		if (condition < 4000) {//비트맵의 너비로 조정
			SmartPointer<Figure*>smartPointer(classDiagramForm->copyBuffer->CreateIterator());
			for (smartPointer->First();!smartPointer->IsDone();smartPointer->Next()) {
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
					if (isOne == 1) {
						object2->Move((bigWidth + 10) + lineLength - object->GetX(), 0);
					}
					else {
						object2->Move((bigWidth + 10) + lineLength - minX, 0);
					}
					classDiagramForm->diagram->Add(static_cast<Figure*>(object2));
					if (isHave == 1) {
						classDiagramForm->selection->Correct(static_cast<Figure*>(object2), i);
					}
					else {
						classDiagramForm->selection->Add(static_cast<Figure*>(object2));
					}
				}
				else if (dynamic_cast<MemoBox*>(smartPointer->Current())) {
					MemoBox *object = static_cast<MemoBox*>(smartPointer->Current());
					MemoBox *object2 = new MemoBox(*object);
					if (isOne == 1 ) {
						object2->Move((bigWidth + 10) + lineLength - object->GetX(), 0);
					}
					else {
						object2->Move((bigWidth + 10) + lineLength - minX, 0);
					}
					classDiagramForm->diagram->Add(static_cast<Figure*>(object2));
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
									point_.y += 30;
									object2->Correct(z, point_);
									z++;
								}
							}
							static_cast<Class*>(parent)->Add(object2->Clone());
							temp = static_cast<Class*>(parent)->GetAt(parent->GetLength() - 1);
						}
						else {
							SmartPointer<Figure*> ResmartPointer(classDiagramForm->selection->CreateIterator());
							for (ResmartPointer->First();!ResmartPointer->IsDone();ResmartPointer->Next()) {
								if (dynamic_cast<Class*>(ResmartPointer->Current())) {
									if (isCut == 1) {
										if (ResmartPointer->Current()->GetX() == parent->GetX()
											&& ResmartPointer->Current()->GetY() == parent->GetY()) {
											while (static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetX() != object->GetX()) {
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
												point_.x += 50;
												point_.y += 50;
												object2->Correct(z, point_);
												z++;
											}
											static_cast<Class*>(ResmartPointer->Current())->Correct(object2->Clone(), f);
											temp = static_cast<Class*>(ResmartPointer->Current())->GetAt(f);
										}
									}
									else {
										Long condition_ = 0;
										if (isOne == 1) {
											condition_ = (bigWidth + 10) + lineLength - object->GetX();
										}
										else {
											condition_ = (bigWidth + 10) + lineLength - minX;
										}

										if (ResmartPointer->Current()->GetX() - condition_ == parent->GetX()) {
											while (static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetX() != object->GetX()) {
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
												point_.x += 50;
												point_.y += 50;
												object2->Correct(z, point_);
												z++;
											}
											static_cast<Class*>(ResmartPointer->Current())->Correct(object2->Clone(), f);
											temp = static_cast<Class*>(ResmartPointer->Current())->GetAt(f);
										}
									}
								}
							}
						}
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
									point_.y += 30;
									object2->Correct(z, point_);
									z++;
								}
							}
							static_cast<Class*>(parent)->Add(object2->Clone());
							temp = static_cast<Class*>(parent)->GetAt(parent->GetLength() - 1);
						}
						else {
							SmartPointer<Figure*> ResmartPointer(classDiagramForm->selection->CreateIterator());
							for (ResmartPointer->First();!ResmartPointer->IsDone();ResmartPointer->Next()) {
								if (dynamic_cast<Class*>(ResmartPointer->Current())) {
									if (isCut == 1) {
										if (ResmartPointer->Current()->GetX() == parent->GetX()
											&& ResmartPointer->Current()->GetY() == parent->GetY()) {
											while (static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetX() != object->GetX()) {
												f++;
											}
											if (isOne == 1) {
												object2->MovePaste((bigWidth + 10) - object->GetX(), 0);
											}
											else {
												object2->MovePaste((bigWidth + 10) - minX, 0);
											}
											z = 0;
											while (z < object2->GetLength()) {
												point_.x = object2->GetAt(z).x;
												point_.y = object2->GetAt(z).y;
												point_.x += 50;
												point_.y += 50;
												object2->Correct(z, point_);
												z++;
											}
											static_cast<Class*>(ResmartPointer->Current())->Correct(object2->Clone(), f);
											temp = static_cast<Class*>(ResmartPointer->Current())->GetAt(f);
										}
									}
									else {
										Long condition_ = 0;
										if (isOne == 1) {
											condition_ = (bigWidth + 10) - object->GetX();
										}
										else {
											condition_ = (bigWidth + 10) - minX;
										}

										if (ResmartPointer->Current()->GetX() - condition_ == parent->GetX()) {
											while (static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetX() != object->GetX()) {
												f++;
											}
											if (isOne == 1) {
												object2->MovePaste((bigWidth + 10) - object->GetX(), 0);
											}
											else {
												object2->MovePaste((bigWidth + 10) - minX, 0);
											}
											z = 0;
											while (z < object2->GetLength()) {
												point_.x = object2->GetAt(z).x;
												point_.y = object2->GetAt(z).y;
												point_.x += 50;
												point_.y += 50;
												object2->Correct(z, point_);
												z++;
											}
											static_cast<Class*>(ResmartPointer->Current())->Correct(object2->Clone(), f);
											temp = static_cast<Class*>(ResmartPointer->Current())->GetAt(f);
										}
									}
								}
							}
						}
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
									point_.y += 30;
									object2->Correct(z, point_);
									z++;
								}
							}
							static_cast<Class*>(parent)->Add(object2->Clone());
							temp = static_cast<Class*>(parent)->GetAt(parent->GetLength() - 1);
						}
						else {
							SmartPointer<Figure*> ResmartPointer(classDiagramForm->selection->CreateIterator());
							for (ResmartPointer->First();!ResmartPointer->IsDone();ResmartPointer->Next()) {
								if (dynamic_cast<Class*>(ResmartPointer->Current())) {
									if (isCut == 1) {
										if (ResmartPointer->Current()->GetX() == parent->GetX()
											&& ResmartPointer->Current()->GetY() == parent->GetY()) {
											while (static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetX() != object->GetX()) {
												f++;
											}
											if (isOne == 1) {
												object2->MovePaste((bigWidth + 10) - object->GetX(), 0);
											}
											else {
												object2->MovePaste((bigWidth + 10) - minX, 0);
											}
											z = 0;
											while (z < object2->GetLength()) {
												point_.x = object2->GetAt(z).x;
												point_.y = object2->GetAt(z).y;
												point_.x += 50;
												point_.y += 50;
												object2->Correct(z, point_);
												z++;
											}
											static_cast<Class*>(ResmartPointer->Current())->Correct(object2->Clone(), f);
											temp = static_cast<Class*>(ResmartPointer->Current())->GetAt(f);
										}
									}
									else {
										Long condition_ = 0;
										if (isOne == 1) {
											condition_ = (bigWidth + 10) - object->GetX();
										}
										else {
											condition_ = (bigWidth + 10) - minX;
										}

										if (ResmartPointer->Current()->GetX() - condition_ == parent->GetX()) {
											while (static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetX() != object->GetX()) {
												f++;
											}
											if (isOne == 1) {
												object2->MovePaste((bigWidth + 10) - object->GetX(), 0);
											}
											else {
												object2->MovePaste((bigWidth + 10) - minX, 0);
											}
											z = 0;
											while (z < object2->GetLength()) {
												point_.x = object2->GetAt(z).x;
												point_.y = object2->GetAt(z).y;
												point_.x += 50;
												point_.y += 50;
												object2->Correct(z, point_);
												z++;
											}
											static_cast<Class*>(ResmartPointer->Current())->Correct(object2->Clone(), f);
											temp = static_cast<Class*>(ResmartPointer->Current())->GetAt(f);
										}
									}
								}
							}
						}
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
									point_.y += 30;
									object2->Correct(z, point_);
									z++;
								}
							}
							static_cast<Class*>(parent)->Add(object2->Clone());
							temp = static_cast<Class*>(parent)->GetAt(parent->GetLength() - 1);
						}
						else {
							SmartPointer<Figure*> ResmartPointer(classDiagramForm->selection->CreateIterator());
							for (ResmartPointer->First();!ResmartPointer->IsDone();ResmartPointer->Next()) {
								if (dynamic_cast<Class*>(ResmartPointer->Current())) {
									if (isCut == 1) {
										if (ResmartPointer->Current()->GetX() == parent->GetX()
											&& ResmartPointer->Current()->GetY() == parent->GetY()) {
											while (static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetX() != object->GetX()) {
												f++;
											}
											if (isOne == 1) {
												object2->MovePaste((bigWidth + 10) - object->GetX(), 0);
											}
											else {
												object2->MovePaste((bigWidth + 10) - minX, 0);
											}
											z = 0;
											while (z < object2->GetLength()) {
												point_.x = object2->GetAt(z).x;
												point_.y = object2->GetAt(z).y;
												point_.x += 50;
												point_.y += 50;
												object2->Correct(z, point_);
												z++;
											}
											static_cast<Class*>(ResmartPointer->Current())->Correct(object2->Clone(), f);
											temp = static_cast<Class*>(ResmartPointer->Current())->GetAt(f);
										}
									}
									else {
										Long condition_ = 0;
										if (isOne == 1) {
											condition_ = (bigWidth + 10) - object->GetX();
										}
										else {
											condition_ = (bigWidth + 10) - minX;
										}

										if (ResmartPointer->Current()->GetX() - condition_ == parent->GetX()) {
											while (static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetX() != object->GetX()) {
												f++;
											}
											if (isOne == 1) {
												object2->MovePaste((bigWidth + 10) - object->GetX(), 0);
											}
											else {
												object2->MovePaste((bigWidth + 10) - minX, 0);
											}
											z = 0;
											while (z < object2->GetLength()) {
												point_.x = object2->GetAt(z).x;
												point_.y = object2->GetAt(z).y;
												point_.x += 50;
												point_.y += 50;
												object2->Correct(z, point_);
												z++;
											}
											static_cast<Class*>(ResmartPointer->Current())->Correct(object2->Clone(), f);
											temp = static_cast<Class*>(ResmartPointer->Current())->GetAt(f);
										}
									}
								}
							}
						}
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
									point_.y += 30;
									object2->Correct(z, point_);
									z++;
								}
							}
							static_cast<Class*>(parent)->Add(object2->Clone());
							temp = static_cast<Class*>(parent)->GetAt(parent->GetLength() - 1);
						}
						else {
							SmartPointer<Figure*> ResmartPointer(classDiagramForm->selection->CreateIterator());
							for (ResmartPointer->First();!ResmartPointer->IsDone();ResmartPointer->Next()) {
								if (dynamic_cast<Class*>(ResmartPointer->Current())) {
									if (isCut == 1) {
										if (ResmartPointer->Current()->GetX() == parent->GetX()
											&& ResmartPointer->Current()->GetY() == parent->GetY()) {
											while (static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetX() != object->GetX()) {
												f++;
											}
											if (isOne == 1) {
												object2->MovePaste((bigWidth + 10) - object->GetX(), 0);
											}
											else {
												object2->MovePaste((bigWidth + 10) - minX, 0);
											}
											z = 0;
											while (z < object2->GetLength()) {
												point_.x = object2->GetAt(z).x;
												point_.y = object2->GetAt(z).y;
												point_.x += 50;
												point_.y += 50;
												object2->Correct(z, point_);
												z++;
											}
											static_cast<Class*>(ResmartPointer->Current())->Correct(object2->Clone(), f);
											temp = static_cast<Class*>(ResmartPointer->Current())->GetAt(f);
										}
									}
									else {
										Long condition_ = 0;
										if (isOne == 1) {
											condition_ = (bigWidth + 10) - object->GetX();
										}
										else {
											condition_ = (bigWidth + 10) - minX;
										}

										if (ResmartPointer->Current()->GetX() - condition_ == parent->GetX()) {
											while (static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetX() != object->GetX()) {
												f++;
											}
											if (isOne == 1) {
												object2->MovePaste((bigWidth + 10) - object->GetX(), 0);
											}
											else {
												object2->MovePaste((bigWidth + 10) - minX, 0);
											}
											z = 0;
											while (z < object2->GetLength()) {
												point_.x = object2->GetAt(z).x;
												point_.y = object2->GetAt(z).y;
												point_.x += 50;
												point_.y += 50;
												object2->Correct(z, point_);
												z++;
											}
											static_cast<Class*>(ResmartPointer->Current())->Correct(object2->Clone(), f);
											temp = static_cast<Class*>(ResmartPointer->Current())->GetAt(f);
										}
									}
								}
							}
						}
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
									point_.y += 30;
									object2->Correct(z, point_);
									z++;
								}
							}
							static_cast<Class*>(parent)->Add(object2->Clone());
							temp = static_cast<Class*>(parent)->GetAt(parent->GetLength() - 1);
						}
						else {
							SmartPointer<Figure*> ResmartPointer(classDiagramForm->selection->CreateIterator());
							for (ResmartPointer->First();!ResmartPointer->IsDone();ResmartPointer->Next()) {
								if (dynamic_cast<Class*>(ResmartPointer->Current())) {
									if (isCut == 1) {
										if (ResmartPointer->Current()->GetX() == parent->GetX()
											&& ResmartPointer->Current()->GetY() == parent->GetY()) {
											while (static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetX() != object->GetX()) {
												f++;
											}
											if (isOne == 1) {
												object2->MovePaste((bigWidth + 10) - object->GetX(), 0);
											}
											else {
												object2->MovePaste((bigWidth + 10) - minX, 0);
											}
											z = 0;
											while (z < object2->GetLength()) {
												point_.x = object2->GetAt(z).x;
												point_.y = object2->GetAt(z).y;
												point_.x += 50;
												point_.y += 50;
												object2->Correct(z, point_);
												z++;
											}
											static_cast<Class*>(ResmartPointer->Current())->Correct(object2->Clone(), f);
											temp = static_cast<Class*>(ResmartPointer->Current())->GetAt(f);
										}
									}
									else {
										Long condition_ = 0;
										if (isOne == 1) {
											condition_ = (bigWidth + 10) - object->GetX();
										}
										else {
											condition_ = (bigWidth + 10) - minX;
										}

										if (ResmartPointer->Current()->GetX() - condition_ == parent->GetX()) {
											while (static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetX() != object->GetX()) {
												f++;
											}
											if (isOne == 1) {
												object2->MovePaste((bigWidth + 10) - object->GetX(), 0);
											}
											else {
												object2->MovePaste((bigWidth + 10) - minX, 0);
											}
											z = 0;
											while (z < object2->GetLength()) {
												point_.x = object2->GetAt(z).x;
												point_.y = object2->GetAt(z).y;
												point_.x += 50;
												point_.y += 50;
												object2->Correct(z, point_);
												z++;
											}
											static_cast<Class*>(ResmartPointer->Current())->Correct(object2->Clone(), f);
											temp = static_cast<Class*>(ResmartPointer->Current())->GetAt(f);
										}
									}
								}
							}
						}
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
									point_.y += 30;
									object2->Correct(z, point_);
									z++;
								}
							}
							static_cast<Class*>(parent)->Add(object2->Clone());
							temp = static_cast<Class*>(parent)->GetAt(parent->GetLength() - 1);
						}
						else {
							SmartPointer<Figure*> ResmartPointer(classDiagramForm->selection->CreateIterator());
							for (ResmartPointer->First();!ResmartPointer->IsDone();ResmartPointer->Next()) {
								if (dynamic_cast<Class*>(ResmartPointer->Current())) {
									if (isCut == 1) {
										if (ResmartPointer->Current()->GetX() == parent->GetX()
											&& ResmartPointer->Current()->GetY() == parent->GetY()) {
											while (static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetX() != object->GetX()) {
												f++;
											}
											if (isOne == 1) {
												object2->MovePaste((bigWidth + 10) - object->GetX(), 0);
											}
											else {
												object2->MovePaste((bigWidth + 10) - minX, 0);
											}
											z = 0;
											while (z < object2->GetLength()) {
												point_.x = object2->GetAt(z).x;
												point_.y = object2->GetAt(z).y;
												point_.x += 50;
												point_.y += 50;
												object2->Correct(z, point_);
												z++;
											}
											static_cast<Class*>(ResmartPointer->Current())->Correct(object2->Clone(), f);
											temp = static_cast<Class*>(ResmartPointer->Current())->GetAt(f);
										}
									}
									else {
										Long condition_ = 0;
										if (isOne == 1) {
											condition_ = (bigWidth + 10) - object->GetX();
										}
										else {
											condition_ = (bigWidth + 10) - minX;
										}

										if (ResmartPointer->Current()->GetX() - condition_ == parent->GetX()) {
											while (static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetX() != object->GetX()) {
												f++;
											}
											if (isOne == 1) {
												object2->MovePaste((bigWidth + 10) - object->GetX(), 0);
											}
											else {
												object2->MovePaste((bigWidth + 10) - minX, 0);
											}
											z = 0;
											while (z < object2->GetLength()) {
												point_.x = object2->GetAt(z).x;
												point_.y = object2->GetAt(z).y;
												point_.x += 50;
												point_.y += 50;
												object2->Correct(z, point_);
												z++;
											}
											static_cast<Class*>(ResmartPointer->Current())->Correct(object2->Clone(), f);
											temp = static_cast<Class*>(ResmartPointer->Current())->GetAt(f);
										}
									}
								}
							}
						}
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
									point_.y += 30;
									object2->Correct(z, point_);
									z++;
								}
							}
							static_cast<Class*>(parent)->Add(object2->Clone());
							temp = static_cast<Class*>(parent)->GetAt(parent->GetLength() - 1);
						}
						else {
							SmartPointer<Figure*> ResmartPointer(classDiagramForm->selection->CreateIterator());
							for (ResmartPointer->First();!ResmartPointer->IsDone();ResmartPointer->Next()) {
								if (dynamic_cast<Class*>(ResmartPointer->Current())) {
									if (isCut == 1) {
										if (ResmartPointer->Current()->GetX() == parent->GetX()
											&& ResmartPointer->Current()->GetY() == parent->GetY()) {
											while (static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetX() != object->GetX()) {
												f++;
											}
											if (isOne == 1) {
												object2->MovePaste((bigWidth + 10) - object->GetX(), 0);
											}
											else {
												object2->MovePaste((bigWidth + 10) - minX, 0);
											}
											z = 0;
											while (z < object2->GetLength()) {
												point_.x = object2->GetAt(z).x;
												point_.y = object2->GetAt(z).y;
												point_.x += 50;
												point_.y += 50;
												object2->Correct(z, point_);
												z++;
											}
											static_cast<Class*>(ResmartPointer->Current())->Correct(object2->Clone(), f);
											temp = static_cast<Class*>(ResmartPointer->Current())->GetAt(f);
										}
									}
									else {
										Long condition_ = 0;
										if (isOne == 1) {
											condition_ = (bigWidth + 10) - object->GetX();
										}
										else {
											condition_ = (bigWidth + 10) - minX;
										}

										if (ResmartPointer->Current()->GetX() - condition_ == parent->GetX()) {
											while (static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetX() != object->GetX()) {
												f++;
											}
											if (isOne == 1) {
												object2->MovePaste((bigWidth + 10) - object->GetX(), 0);
											}
											else {
												object2->MovePaste((bigWidth + 10) - minX, 0);
											}
											z = 0;
											while (z < object2->GetLength()) {
												point_.x = object2->GetAt(z).x;
												point_.y = object2->GetAt(z).y;
												point_.x += 50;
												point_.y += 50;
												object2->Correct(z, point_);
												z++;
											}
											static_cast<Class*>(ResmartPointer->Current())->Correct(object2->Clone(), f);
											temp = static_cast<Class*>(ResmartPointer->Current())->GetAt(f);
										}
									}
								}
							}
						}
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
									point_.y += 30;
									object2->Correct(z, point_);
									z++;
								}
							}
							static_cast<Class*>(parent)->Add(object2->Clone());
							temp = static_cast<Class*>(parent)->GetAt(parent->GetLength() - 1);
						}
						else {
							SmartPointer<Figure*> ResmartPointer(classDiagramForm->selection->CreateIterator());
							for (ResmartPointer->First();!ResmartPointer->IsDone();ResmartPointer->Next()) {
								if (dynamic_cast<Class*>(ResmartPointer->Current())) {
									if (isCut == 1) {
										if (ResmartPointer->Current()->GetX() == parent->GetX()
											&& ResmartPointer->Current()->GetY() == parent->GetY()) {
											while (static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetX() != object->GetX()) {
												f++;
											}
											if (isOne == 1) {
												object2->MovePaste((bigWidth + 10) - object->GetX(), 0);
											}
											else {
												object2->MovePaste((bigWidth + 10) - minX, 0);
											}
											z = 0;
											while (z < object2->GetLength()) {
												point_.x = object2->GetAt(z).x;
												point_.y = object2->GetAt(z).y;
												point_.x += 50;
												point_.y += 50;
												object2->Correct(z, point_);
												z++;
											}
											static_cast<Class*>(ResmartPointer->Current())->Correct(object2->Clone(), f);
											temp = static_cast<Class*>(ResmartPointer->Current())->GetAt(f);
										}
									}
									else {
										Long condition_ = 0;
										if (isOne == 1) {
											condition_ = (bigWidth + 10) - object->GetX();
										}
										else {
											condition_ = (bigWidth + 10) - minX;
										}

										if (ResmartPointer->Current()->GetX() - condition_ == parent->GetX()) {
											while (static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetX() != object->GetX()) {
												f++;
											}
											if (isOne == 1) {
												object2->MovePaste((bigWidth + 10) - object->GetX(), 0);
											}
											else {
												object2->MovePaste((bigWidth + 10) - minX, 0);
											}
											z = 0;
											while (z < object2->GetLength()) {
												point_.x = object2->GetAt(z).x;
												point_.y = object2->GetAt(z).y;
												point_.x += 50;
												point_.y += 50;
												object2->Correct(z, point_);
												z++;
											}
											static_cast<Class*>(ResmartPointer->Current())->Correct(object2->Clone(), f);
											temp = static_cast<Class*>(ResmartPointer->Current())->GetAt(f);
										}
									}
								}
							}
						}
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
						parent = static_cast<Class*>(finder.GetParents(classDiagramForm->diagram, object));
						if (isOne == 1) {
							if (object2->GetY() < parent->GetY() + parent->GetHeight() - 10) {
								static_cast<Figure*>(object2)->Move(0, 30);
								z = 0;
								while (z < object2->GetLength()) {
									point_.x = object2->GetAt(z).x;
									point_.y = object2->GetAt(z).y;
									point_.y += 30;
									object2->Correct(z, point_);
									z++;
								}
							}
							static_cast<Class*>(parent)->Add(object2->Clone());
							temp = static_cast<Class*>(parent)->GetAt(parent->GetLength() - 1);
						}
						else {
							SmartPointer<Figure*> ResmartPointer(classDiagramForm->selection->CreateIterator());
							for (ResmartPointer->First();!ResmartPointer->IsDone();ResmartPointer->Next()) {
								if (dynamic_cast<Class*>(ResmartPointer->Current())) {
									if (isCut == 1) {
										if (ResmartPointer->Current()->GetX() == parent->GetX()
											&& ResmartPointer->Current()->GetY() == parent->GetY()) {
											while (static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetX() != object->GetX()) {
												f++;
											}
											if (isOne == 1) {
												object2->MovePaste((bigWidth + 10) - object->GetX(), 0);
											}
											else {
												object2->MovePaste((bigWidth + 10) - minX, 0);
											}
											z = 0;
											while (z < object2->GetLength()) {
												point_.x = object2->GetAt(z).x;
												point_.y = object2->GetAt(z).y;
												point_.x += 50;
												point_.y += 50;
												object2->Correct(z, point_);
												z++;
											}
											static_cast<Class*>(ResmartPointer->Current())->Correct(object2->Clone(), f);
											temp = static_cast<Class*>(ResmartPointer->Current())->GetAt(f);
										}
									}
									else {
										Long condition_ = 0;
										if (isOne == 1) {
											condition_ = (bigWidth + 10) - object->GetX();
										}
										else {
											condition_ = (bigWidth + 10) - minX;
										}

										if (ResmartPointer->Current()->GetX() - condition_ == parent->GetX()) {
											while (static_cast<Class*>(ResmartPointer->Current())->GetAt(f)->GetX() != object->GetX()) {
												f++;
											}
											if (isOne == 1) {
												object2->MovePaste((bigWidth + 10) - object->GetX(), 0);
											}
											else {
												object2->MovePaste((bigWidth + 10) - minX, 0);
											}
											z = 0;
											while (z < object2->GetLength()) {
												point_.x = object2->GetAt(z).x;
												point_.y = object2->GetAt(z).y;
												point_.x += 50;
												point_.y += 50;
												object2->Correct(z, point_);
												z++;
											}
											static_cast<Class*>(ResmartPointer->Current())->Correct(object2->Clone(), f);
											temp = static_cast<Class*>(ResmartPointer->Current())->GetAt(f);
										}
									}
								}
							}
						}
						if (isHave == 1) {
							classDiagramForm->selection->Correct(temp, i);
						}
						else {
							classDiagramForm->selection->Add(temp);
						}
					}
				}
				i++;
			}
		}
		if (classDiagramForm->isCut == 1) {
			classDiagramForm->isCut = 0;
		}
	}
}



void GraphicCtrlPasteKey::KeyPress(TextEdit *textEdit) {

}