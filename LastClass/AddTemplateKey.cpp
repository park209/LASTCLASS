//AddTemplateKey.cpp

#include "AddTemplateKey.h"
#include "ClassDiagramForm.h"
#include "Selection.h"
#include "Class.h"
#include "TextEdit.h"
#include "HistoryGraphic.h"

AddTemplateKey::AddTemplateKey() {
}

AddTemplateKey::AddTemplateKey(const AddTemplateKey& source) {
}

AddTemplateKey::~AddTemplateKey() {
}

void AddTemplateKey::KeyPress(ClassDiagramForm *classDiagramForm) {
	if (classDiagramForm->selection->GetLength() > 0) {
		Class *object = static_cast<Class*>(classDiagramForm->selection->GetAt(0));
		if (object->GetTempletePosition() == -1) {
			classDiagramForm->historyGraphic->PushUndo(classDiagramForm->diagram);
			object->AddTemplate(object->GetX() + object->GetWidth() - 17, object->GetY() - 17, 34, 34);
		}
	}
}

void AddTemplateKey::KeyPress(TextEdit *textEdit) {

}