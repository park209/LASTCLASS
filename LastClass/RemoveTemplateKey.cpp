//RemoveTemplateKey.cpp

#include "RemoveTemplateKey.h"
#include "ClassDiagramForm.h"
#include "HistoryGraphic.h"
#include "Selection.h"
#include "Class.h"
#include "TextEdit.h"

RemoveTemplateKey::RemoveTemplateKey() {
}

RemoveTemplateKey::RemoveTemplateKey(const RemoveTemplateKey& source) {
}

RemoveTemplateKey::~RemoveTemplateKey() {
}

void RemoveTemplateKey::KeyPress(ClassDiagramForm *classDiagramForm) {
	if (classDiagramForm->selection->GetLength() > 0) {
		Class *object = static_cast<Class*>(classDiagramForm->selection->GetAt(0));
		if (object->GetTempletePosition() != -1) {
			classDiagramForm->historyGraphic->PushUndo(classDiagramForm->diagram);
			object->RemoveTemplate();
		}
	}
}
void RemoveTemplateKey::KeyPress(TextEdit *textEdit) {

}