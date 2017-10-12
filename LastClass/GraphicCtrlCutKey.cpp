//GraphicCtrlCutKey.cpp

#include "GraphicCtrlCutKey.h"
#include "ClassDiagramForm.h"
#include "HistoryGraphic.h"
#include "Selection.h"
#include "Class.h"
#include "TextEdit.h"
#include "DrawingVisitor.h"
#include "WritingVisitor.h"
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
#include "Template.h"
#include "SmartPointer.h"
#include "MemoLine.h"
#include "Finder.h"
#include "Diagram.h"

GraphicCtrlCutKey::GraphicCtrlCutKey() {
}

GraphicCtrlCutKey::GraphicCtrlCutKey(const GraphicCtrlCutKey& source) {
}

GraphicCtrlCutKey::~GraphicCtrlCutKey() {
}

void GraphicCtrlCutKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
	classDiagramForm->historyGraphic->PushUndo(classDiagramForm->diagram);
	if (classDiagramForm->copyBuffer != 0) {
		delete classDiagramForm->copyBuffer;
	}
	Long d;
	Figure *object3;
	classDiagramForm->copyBuffer = new Selection(*classDiagramForm->selection);
	if (classDiagramForm->selection->GetLength() == 1) {
		//Figure *parent;
		Finder finder;
		CBitmap bitmap;
		CDC memDC;
		CFont* cFont = cdc->GetCurrentFont();
		Long x = 0;
		Long y = 0;
		Long k = 0;
		CBitmap *OldBitmap = 0;
		Figure *object = classDiagramForm->copyBuffer->GetAt(0);
		DrawingVisitor drawingVisitor;
		WritingVisitor writingVisitor;
		memDC.CreateCompatibleDC(cdc);
		memDC.SelectObject(cFont);
		Long tempsize = 0;
		Figure *previous = 0;
		SmartPointer<Figure*>smartPointer_(classDiagramForm->copyBuffer->CreateIterator());
		if (classDiagramForm->selection->GetLength() > 1) {
			Long minX = 0;
			//Long minY = 0;
			Long bigWidth = 0;
			Long maxX = 0;
			//Long maxY = 0;
			Long bigHeight = 0;
			for (smartPointer_->First();!smartPointer_->IsDone();smartPointer_->Next()) {
				if (dynamic_cast<Class*>(smartPointer_->Current()) || dynamic_cast<MemoBox*>(smartPointer_->Current())) {
					if (smartPointer_->Current()->GetX() > maxX || maxX == 0) {
						maxX = smartPointer_->Current()->GetX();
						bigWidth = smartPointer_->Current()->GetWidth();
					}
					if (minX == 0 || smartPointer_->Current()->GetX() < minX) {
						minX = smartPointer_->Current()->GetX();
					}
					/*if (smartPointer_->Current()->GetY() > maxY || maxY == 0) {
					maxY = smartPointer_->Current()->GetY();
					bigHeight = smartPointer_->Current()->GetHeight();
					}
					if (minY == 0 ||smartPointer_->Current()->GetY() < minY ) {
					minY = smartPointer_->Current()->GetY();
					}*/
					if (bigHeight == 0 || (smartPointer_->Current()->GetY() + smartPointer_->Current()->GetHeight()) > bigHeight) {
						bigHeight = smartPointer_->Current()->GetY() + smartPointer_->Current()->GetHeight();
					}
				}
			}
			bitmap.CreateCompatibleBitmap(&memDC, (maxX + bigWidth) - minX, bigHeight);
			OldBitmap = (CBitmap*)memDC.SelectObject(&bitmap);
			memDC.FillSolidRect(CRect(0, 0, (maxX + bigWidth) - minX, bigHeight), RGB(255, 255, 255));
		}
		for (smartPointer_->First();!smartPointer_->IsDone();smartPointer_->Next()) {
			if (dynamic_cast<Class*>(smartPointer_->Current())) {
				Class *objectClass = static_cast<Class*>(classDiagramForm->copyBuffer->GetAt(0));
				Template *objectTemplate = 0;
				SmartPointer<Figure*> smartPointer(objectClass->CreateIterator());
				for (smartPointer->First();!smartPointer->IsDone();smartPointer->Next()) {
					if (dynamic_cast<Template*>(smartPointer->Current())) {
						objectTemplate = static_cast<Template*>(smartPointer->Current());
						k = objectTemplate->GetY();
					}
				}
				if (objectTemplate == 0 && classDiagramForm->selection->GetLength() == 1) {
					//bitmap.CreateCompatibleBitmap(&memDC, objectClass->GetWidth(), objectClass->GetHeight());
					bitmap.CreateCompatibleBitmap(&memDC, objectClass->GetWidth(), objectClass->GetHeight());
					OldBitmap = (CBitmap*)memDC.SelectObject(&bitmap);
					memDC.FillSolidRect(CRect(0, 0, objectClass->GetX() + objectClass->GetWidth(), objectClass->GetY() + objectClass->GetHeight()), RGB(255, 255, 255));
				}
				else if (classDiagramForm->selection->GetLength() == 1) {
					bitmap.CreateCompatibleBitmap(&memDC, objectClass->GetWidth() + ((objectTemplate->GetX() + objectTemplate->GetWidth())
						- (objectClass->GetX() + objectClass->GetWidth())), objectClass->GetHeight() + (objectClass->GetY() - objectTemplate->GetY()));
					OldBitmap = (CBitmap*)memDC.SelectObject(&bitmap);
					memDC.FillSolidRect(CRect(0, 0, objectClass->GetX() + objectClass->GetWidth(), objectClass->GetY() + objectClass->GetHeight()), RGB(255, 255, 255));
				}
				x = objectClass->GetX();
				y = objectClass->GetY();
				for (smartPointer->First();!smartPointer->IsDone();smartPointer->Next()) {
					if (dynamic_cast<Line*>(smartPointer->Current())) {
						if (objectTemplate == 0) {
							static_cast<Line*>(smartPointer->Current())->Move(-x, -y);
						}
						else {
							static_cast<Line*>(smartPointer->Current())->Move(-x, -y + (y - objectTemplate->GetY()));
						}
					}
					if (dynamic_cast<ClassName*>(smartPointer->Current())) {
						if (objectTemplate == 0) {
							static_cast<ClassName*>(smartPointer->Current())->Move(-x, -y);
						}
						else {
							static_cast<ClassName*>(smartPointer->Current())->Move(-x, -y + (y - objectTemplate->GetY()));
						}
					}
					if (dynamic_cast<Attribute*>(smartPointer->Current())) {
						if (objectTemplate == 0) {
							static_cast<Attribute*>(smartPointer->Current())->Move(-x, -y);
						}
						else {
							static_cast<Attribute*>(smartPointer->Current())->Move(-x, -y + (y - objectTemplate->GetY()));
						}
					}
					if (dynamic_cast<Method*>(smartPointer->Current())) {
						if (objectTemplate == 0) {
							static_cast<Method*>(smartPointer->Current())->Move(-x, -y);
						}

						else {
							static_cast<Method*>(smartPointer->Current())->Move(-x, -y + (y - objectTemplate->GetY()));
						}
					}
					if (dynamic_cast<Template*>(smartPointer->Current())) {
						static_cast<Template*>(smartPointer->Current())->Move(-x, -y + (y - objectTemplate->GetY()));
					}
				}
				if (objectTemplate == 0) {
					objectClass->Move(-x, -y);
				}
				else {
					objectClass->Move(-x, -y + (y - k));
				}
				objectClass->Accept(drawingVisitor, &memDC);
				objectClass->Accept(writingVisitor, &memDC);
				SmartPointer<Figure*> smartPointer_(objectClass->CreateIterator());
				for (smartPointer_->First();!smartPointer_->IsDone();smartPointer_->Next()) {
					if (dynamic_cast<Line*>(smartPointer_->Current())) {
						if (objectTemplate == 0) {
							static_cast<Line*>(smartPointer_->Current())->Move(x, y);
						}
						else {
							static_cast<Line*>(smartPointer_->Current())->Move(x, y - (y - k));
						}
					}
					if (dynamic_cast<ClassName*>(smartPointer_->Current())) {
						if (objectTemplate == 0) {
							static_cast<ClassName*>(smartPointer_->Current())->Move(x, y);
						}
						else {
							static_cast<ClassName*>(smartPointer_->Current())->Move(x, y - (y - k));
						}
					}
					if (dynamic_cast<Attribute*>(smartPointer_->Current())) {
						if (objectTemplate == 0) {
							static_cast<Attribute*>(smartPointer_->Current())->Move(x, y);
						}
						else {
							static_cast<Attribute*>(smartPointer_->Current())->Move(x, y - (y - k));
						}
					}
					if (dynamic_cast<Method*>(smartPointer_->Current())) {
						if (objectTemplate == 0) {
							static_cast<Method*>(smartPointer_->Current())->Move(x, y);
						}
						else {
							static_cast<Method*>(smartPointer_->Current())->Move(x, y - (y - k));
						}
					}
					if (dynamic_cast<Template*>(smartPointer_->Current())) {
						static_cast<Template*>(smartPointer_->Current())->Move(x, y - (y - k));
					}
				}
				if (objectTemplate == 0) {
					objectClass->Move(x, y);
				}
				else {
					objectClass->Move(x, y - (y - k));
				}
				objectClass->Accept(drawingVisitor, cdc);
				objectClass->Accept(writingVisitor, cdc);
			}
			else if (dynamic_cast<MemoBox*>(smartPointer_->Current())) {
				MemoBox *objectMemoBox = static_cast<MemoBox*>(classDiagramForm->copyBuffer->GetAt(0));
				if (classDiagramForm->selection->GetLength() == 1) {
					bitmap.CreateCompatibleBitmap(&memDC, objectMemoBox->GetWidth() + 1, objectMemoBox->GetHeight() + 1);
					OldBitmap = (CBitmap*)memDC.SelectObject(&bitmap);
					memDC.FillSolidRect(CRect(0, 0, objectMemoBox->GetX() + objectMemoBox->GetWidth(), objectMemoBox->GetY() + objectMemoBox->GetHeight()), RGB(255, 255, 255));
				}
				/*if (previous != 0) {
				}
				else {*/
				x = objectMemoBox->GetX();
				y = objectMemoBox->GetY();
				//}
				objectMemoBox->Move(-x, -y);
				objectMemoBox->Accept(drawingVisitor, &memDC);
				objectMemoBox->Accept(writingVisitor, &memDC);
				objectMemoBox->Move(x, y);
				objectMemoBox->Accept(drawingVisitor, cdc);
				objectMemoBox->Accept(writingVisitor, cdc);

			}
			else if (dynamic_cast<Relation*>(smartPointer_->Current())) {
				Relation *objectRelation = static_cast<Relation*>(classDiagramForm->copyBuffer->GetAt(0));
				if (classDiagramForm->selection->GetLength() == 1) {
					bitmap.CreateCompatibleBitmap(&memDC, object->GetWidth() + 20, object->GetHeight() + 20);
					OldBitmap = (CBitmap*)memDC.SelectObject(&bitmap);
					memDC.FillSolidRect(CRect(0, 0, object->GetX() + object->GetWidth(), object->GetY() + object->GetHeight()), RGB(255, 255, 255));
				}
				x = objectRelation->GetX();
				y = objectRelation->GetY();
				//k = objectRelation->GetAt(1).y;
				//if (y > k) {
				objectRelation->SetX(0);
				objectRelation->SetY(0);
				//}
				/*if (classDiagramForm->selection->GetLength() >1) {
				parent = static_cast<Class*>(finder.GetParents(classDiagramForm->diagram, objectRelation));
				objectRelation->SetX(parent->GetWidth());
				objectRelation->SetY(objectRelation->GetY() - parent->GetY());
				}*/
				if (dynamic_cast<Generalization*>(objectRelation)) {
					static_cast<Generalization*>(objectRelation)->Accept(drawingVisitor, &memDC);
				}
				else if (dynamic_cast<Realization*>(objectRelation)) {
					static_cast<Realization*>(objectRelation)->Accept(drawingVisitor, &memDC);
				}
				else if (dynamic_cast<Dependency*>(objectRelation)) {
					static_cast<Dependency*>(objectRelation)->Accept(drawingVisitor, &memDC);
				}
				else if (dynamic_cast<Association*>(objectRelation)) {
					static_cast<Association*>(objectRelation)->Accept(drawingVisitor, &memDC); //, cPaintDc
				}
				else if (dynamic_cast<DirectedAssociation*>(objectRelation)) {
					static_cast<DirectedAssociation*>(objectRelation)->Accept(drawingVisitor, &memDC);
				}
				else if (dynamic_cast<Aggregation*>(objectRelation)) {
					static_cast<Aggregation*>(objectRelation)->Accept(drawingVisitor, &memDC);
				}
				else if (dynamic_cast<Aggregations*>(objectRelation)) {
					static_cast<Aggregations*>(objectRelation)->Accept(drawingVisitor, &memDC);
				}
				else if (dynamic_cast<Composition*>(objectRelation)) {
					static_cast<Composition*>(objectRelation)->Accept(drawingVisitor, &memDC);
				}
				else if (dynamic_cast<Compositions*>(objectRelation)) {
					static_cast<Compositions*>(objectRelation)->Accept(drawingVisitor, &memDC);
				}
				else if (dynamic_cast<MemoLine*>(objectRelation)) {
					static_cast<MemoLine*>(objectRelation)->Accept(drawingVisitor, &memDC);
				}
				objectRelation->SetX(x);
				objectRelation->SetY(y);
				if (dynamic_cast<Generalization*>(objectRelation)) {
					static_cast<Generalization*>(objectRelation)->Accept(drawingVisitor, cdc);
				}
				else if (dynamic_cast<Realization*>(objectRelation)) {
					static_cast<Realization*>(objectRelation)->Accept(drawingVisitor, cdc);
				}
				else if (dynamic_cast<Dependency*>(objectRelation)) {
					static_cast<Dependency*>(objectRelation)->Accept(drawingVisitor, cdc);
				}
				else if (dynamic_cast<Association*>(objectRelation)) {
					static_cast<Association*>(objectRelation)->Accept(drawingVisitor, cdc); //, cPaintDc
				}
				else if (dynamic_cast<DirectedAssociation*>(objectRelation)) {
					static_cast<DirectedAssociation*>(objectRelation)->Accept(drawingVisitor, cdc);
				}
				else if (dynamic_cast<Aggregation*>(objectRelation)) {
					static_cast<Aggregation*>(objectRelation)->Accept(drawingVisitor, cdc);
				}
				else if (dynamic_cast<Aggregations*>(objectRelation)) {
					static_cast<Aggregations*>(objectRelation)->Accept(drawingVisitor, cdc);
				}
				else if (dynamic_cast<Composition*>(objectRelation)) {
					static_cast<Composition*>(objectRelation)->Accept(drawingVisitor, cdc);
				}
				else if (dynamic_cast<Compositions*>(objectRelation)) {
					static_cast<Compositions*>(objectRelation)->Accept(drawingVisitor, cdc);
				}
				else if (dynamic_cast<MemoLine*>(objectRelation)) {
					static_cast<MemoLine*>(objectRelation)->Accept(drawingVisitor, cdc);
				}
			}
			/*if (dynamic_cast<MemoBox*>(smartPointer_->Current()) || dynamic_cast<Class*>(smartPointer_->Current())) {
			previous = smartPointer_->Current();
			}*/
		}
		OpenClipboard(NULL);
		EmptyClipboard();
		SetClipboardData(CF_BITMAP, bitmap.GetSafeHandle());
		CloseClipboard();
		memDC.SelectObject(cFont);
		memDC.SelectObject(OldBitmap);
		bitmap.DeleteObject();
		memDC.DeleteDC();

	}
	while (classDiagramForm->selection->GetLength() != 0) {
		d = 0;
		object3 = 0;
		if (classDiagramForm->diagram->GetLength() > 0) {
			while (d <= classDiagramForm->diagram->GetLength() && classDiagramForm->selection->GetAt(classDiagramForm->selection->GetLength() - 1) != object3) {
				object3 = classDiagramForm->diagram->GetAt(d);
				d++;
			}

			//classDiagramForm->selection->Remove(classDiagramForm->diagram, classDiagramForm->selection->GetAt(classDiagramForm->selection->GetLength() - 1));
			classDiagramForm->selection->Remove(classDiagramForm->selection->GetLength() - 1);
			if (d <= classDiagramForm->diagram->GetLength()) {
				classDiagramForm->diagram->Remove(d - 1);
			}
		}
		if (classDiagramForm->isCut == 0) {
			classDiagramForm->isCut = 1;
		}
	}
}

void GraphicCtrlCutKey::KeyPress(TextEdit *textEdit) {

}