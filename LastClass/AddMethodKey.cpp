//AddMethodKey.cpp

#include "AddMethodKey.h"
#include "ClassDiagramForm.h"
#include "HistoryGraphic.h"
#include "Selection.h"
#include "Class.h"
#include "TextEdit.h"
#include "Diagram.h"

AddMethodKey::AddMethodKey() {
}

AddMethodKey::AddMethodKey(const AddMethodKey& source) {
}

AddMethodKey::~AddMethodKey() {
}

void AddMethodKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
	if (classDiagramForm->selection->GetLength() > 0) {
		Class *object = static_cast<Class*>(classDiagramForm->selection->GetAt(0));
		if (object->GetMethodPosition() == -1) {
			classDiagramForm->historyGraphic->PushUndo(classDiagramForm->diagram, classDiagramForm->zoomRate);
			object->AddMethod(classDiagramForm->diagram);
		}
	}
}

void AddMethodKey::KeyPress(TextEdit *textEdit) {

}