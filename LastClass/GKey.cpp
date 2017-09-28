//GKey.cpp

#include "GKey.h"
#include "ClassDiagramForm.h"
#include "Selection.h"
#include "Class.h"
#include "TextEdit.h"

GKey::GKey() {
}

GKey::GKey(const GKey& source) {
}

GKey::~GKey() {
}

void GKey::KeyPress(ClassDiagramForm *classDiagramForm) {
	Class *object = static_cast<Class*>(classDiagramForm->selection->GetAt(0));
	if (object->GetAttributePosition() == -1) {
		object->AddAttribute(classDiagramForm->diagram);
	}

}

void GKey::KeyPress(TextEdit *textEdit) {

}