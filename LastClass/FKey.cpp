//FKey.cpp

#include "FKey.h"
#include "ClassDiagramForm.h"
#include "Selection.h"
#include "Class.h"
#include "TextEdit.h"

FKey::FKey() {
}

FKey::FKey(const FKey& source) {
}

FKey::~FKey() {
}

void FKey::KeyPress(ClassDiagramForm *classDiagramForm) {
	Class *object = static_cast<Class*>(classDiagramForm->selection->GetAt(0));
	if (object->GetReceptionPosition() != -1) {
		object->RemoveReception();
	}
}

void FKey::KeyPress(TextEdit *textEdit) {

}