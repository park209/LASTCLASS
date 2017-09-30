//HKey.cpp

#include "HKey.h"
#include "ClassDiagramForm.h"
#include "Selection.h"
#include "Class.h"
#include "TextEdit.h"

HKey::HKey() {
}

HKey::HKey(const HKey& source) {
}

HKey::~HKey() {
}

void HKey::KeyPress(ClassDiagramForm *classDiagramForm) {
	Class *object = static_cast<Class*>(classDiagramForm->selection->GetAt(0));
	if (object->GetAttributePosition() != 1) {
		object->RemoveAttribute();
	}
}

void HKey::KeyPress(TextEdit *textEdit) {
}