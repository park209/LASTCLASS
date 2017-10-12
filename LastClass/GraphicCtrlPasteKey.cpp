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
		if (classDiagramForm->selection->GetLength() > 0) {
			isHave = 1;
		}if (classDiagramForm->copyBuffer->GetLength() == 1) {
			isOne = 1;
		}
		SmartPointer<Figure*>diagramSmartPointer(classDiagramForm->diagram->CreateIterator());
		for (diagramSmartPointer->First(); !diagramSmartPointer->IsDone(); diagramSmartPointer->Next()) {
			if (bigWidth == 0 || (diagramSmartPointer->Current()->GetX() + diagramSmartPointer->Current()->GetWidth()) > bigWidth) {
				bigWidth = diagramSmartPointer->Current()->GetX() + diagramSmartPointer->Current()->GetWidth();
			}
		}
		Figure *object_ = classDiagramForm->copyBuffer->GetAt(0);
		Long condition = 0;
		if (isOne == 1) {
			condition = (bigWidth + object_->GetWidth() + 10);
		}
		else {
			condition = bigWidth + (bigWidth - minX) + 20;
		}
		if (condition < 4000) {
			SmartPointer<Figure*>smartPointer(classDiagramForm->copyBuffer->CreateIterator());
			for (smartPointer->First(); !smartPointer->IsDone(); smartPointer->Next()) {
				if (dynamic_cast<Class*>(smartPointer->Current())) {
					Class *object = static_cast<Class*>(smartPointer->Current());
					Class *object2 = new Class(*object);
					SmartPointer<Figure*> smartPointer_(object2->CreateIterator());
					for (smartPointer_->First(); !smartPointer_->IsDone(); smartPointer_->Next()) {
						if (dynamic_cast<Relation*>(smartPointer_->Current())) {
							tmp++;
						}
						else {
							if (isOne == 1) {
								smartPointer_->Current()->Move((bigWidth + 10) - object->GetX(), 0);
							}
							else {
								smartPointer_->Current()->Move((bigWidth + 10) - minX, 0);
							}
						}
					}
					//if(isOne==1){
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
					//}
					if (isOne == 1) {
						object2->Move((bigWidth + 10) - object->GetX(), 0);
					}
					else {
						object2->Move((bigWidth + 10) - minX, 0);
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
					if (isOne == 1) {
						object2->Move((bigWidth + 10) - object->GetX(), 0);
					}
					else {
						object2->Move((bigWidth + 10) - minX, 0);
					}
					classDiagramForm->diagram->Add(static_cast<Figure*>(object2));
					if (isHave == 1) {
						classDiagramForm->selection->Correct(static_cast<Figure*>(object2), i);
					}
					else {
						classDiagramForm->selection->Add(static_cast<Figure*>(object2));
					}
				}
				i++;
			}
		}
	}
}



void GraphicCtrlPasteKey::KeyPress(TextEdit *textEdit) {

}