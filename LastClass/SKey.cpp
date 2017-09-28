//SKey.cpp

#include "SKey.h"
#include "ClassDiagramForm.h"
#include "Selection.h"
#include "Class.h"
#include "TextEdit.h"

SKey::SKey() {
}

SKey::SKey(const SKey& source) {
}

SKey::~SKey() {
}

void SKey::KeyPress(ClassDiagramForm *classDiagramForm) {
	Class *object = static_cast<Class*>(classDiagramForm->selection->GetAt(0));
	if (object->GetTempletePosition() != -1) {
		object->RemoveTemplate();
	}
}
void SKey::KeyPress(TextEdit *textEdit) {

}