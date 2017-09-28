//JKey.cpp

#include "JKey.h"
#include "ClassDiagramForm.h"
#include "Selection.h"
#include "Class.h"
#include "TextEdit.h"
#include "Diagram.h"

JKey::JKey() {
}

JKey::JKey(const JKey& source) {
}

JKey::~JKey() {
}

void JKey::KeyPress(ClassDiagramForm *classDiagramForm) {
	Class *object = static_cast<Class*>(classDiagramForm->selection->GetAt(0));
	if (object->GetMethodPosition() == -1) {
		object->AddMethod(classDiagramForm->diagram);
	}
}

void JKey::KeyPress(TextEdit *textEdit) {

}