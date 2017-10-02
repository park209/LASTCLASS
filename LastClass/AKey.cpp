//AKey.cpp

#include "AKey.h"
#include "ClassDiagramForm.h"
#include "Selection.h"
#include "Class.h"
#include "TextEdit.h"

AKey::AKey() {
}

AKey::AKey(const AKey& source) {
}

AKey::~AKey() {
}

void AKey::KeyPress(ClassDiagramForm *classDiagramForm) {
	Class *object = static_cast<Class*>(classDiagramForm->selection->GetAt(0));
	if (object->GetTempletePosition() == -1) {
		object->AddTemplate(object->GetX() + object->GetWidth()-17, object->GetY()-17, 34, 34);
	}
}

void AKey::KeyPress(TextEdit *textEdit) {

}