//DKey.cpp

#include "DKey.h"
#include "ClassDiagramForm.h"
#include "Selection.h"
#include "Class.h"
#include "TextEdit.h"
#include "Diagram.h"

DKey::DKey() {
}

DKey::DKey(const DKey& source) {
}

DKey::~DKey() {
}

void DKey::KeyPress(ClassDiagramForm *classDiagramForm) {
	Class *object = static_cast<Class*>(classDiagramForm->selection->GetAt(0));
	if (object->GetReceptionPosition() == -1) {
		object->AddReception(classDiagramForm->diagram);
	}
}

void DKey::KeyPress(TextEdit *textEdit) {

}