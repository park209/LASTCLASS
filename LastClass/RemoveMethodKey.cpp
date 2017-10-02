//RemoveMethodKey.cpp

#include "RemoveMethodKey.h"
#include "ClassDiagramForm.h"
#include "HistoryGraphic.h"
#include "Selection.h"
#include "Class.h"

RemoveMethodKey::RemoveMethodKey() {
}

RemoveMethodKey::RemoveMethodKey(const RemoveMethodKey& source) {
}

RemoveMethodKey::~RemoveMethodKey() {
}

void RemoveMethodKey::KeyPress(ClassDiagramForm *classDiagramForm) {
	if (classDiagramForm->selection->GetLength() > 0) {
		Class *object = static_cast<Class*>(classDiagramForm->selection->GetAt(0));
		if (object->GetMethodPosition() != -1) {
			classDiagramForm->historyGraphic->PushUndo(classDiagramForm->diagram);
			object->RemoveMethod();
		}
	}
}

void RemoveMethodKey::KeyPress(TextEdit *textEdit) {

}