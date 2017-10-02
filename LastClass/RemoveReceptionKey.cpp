//RemoveReceptionKey.cpp

#include "RemoveReceptionKey.h"
#include "ClassDiagramForm.h"
#include "HistoryGraphic.h"
#include "Selection.h"
#include "Class.h"
#include "TextEdit.h"

RemoveReceptionKey::RemoveReceptionKey() {
}

RemoveReceptionKey::RemoveReceptionKey(const RemoveReceptionKey& source) {
}

RemoveReceptionKey::~RemoveReceptionKey() {
}

void RemoveReceptionKey::KeyPress(ClassDiagramForm *classDiagramForm) {
	if (classDiagramForm->selection->GetLength() > 0) {
		Class *object = static_cast<Class*>(classDiagramForm->selection->GetAt(0));
		if (object->GetReceptionPosition() != -1) {
			classDiagramForm->historyGraphic->PushUndo(classDiagramForm->diagram);
			object->RemoveReception();
		}
	}
}

void RemoveReceptionKey::KeyPress(TextEdit *textEdit) {

}