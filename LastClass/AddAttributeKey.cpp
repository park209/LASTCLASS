//AddAttributeKey.cpp

#include "AddAttributeKey.h"
#include "ClassDiagramForm.h"
#include "HistoryGraphic.h"
#include "Selection.h"
#include "Class.h"
#include "TextEdit.h"

AddAttributeKey::AddAttributeKey() {
}

AddAttributeKey::AddAttributeKey(const AddAttributeKey& source) {
}

AddAttributeKey::~AddAttributeKey() {
}

void AddAttributeKey::KeyPress(ClassDiagramForm *classDiagramForm) {
	if (classDiagramForm->selection->GetLength() > 0) {
		Class *object = static_cast<Class*>(classDiagramForm->selection->GetAt(0));
		if (object->GetAttributePosition() == -1) {
			classDiagramForm->historyGraphic->PushUndo(classDiagramForm->diagram);
			object->AddAttribute(classDiagramForm->diagram);
		}
	}
}

void AddAttributeKey::KeyPress(TextEdit *textEdit) {

}