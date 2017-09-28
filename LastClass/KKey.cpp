//KKey.cpp

#include "KKey.h"
#include "ClassDiagramForm.h"
#include "Selection.h"
#include "Class.h"

KKey::KKey() {
}

KKey::KKey(const KKey& source) {
}

KKey::~KKey() {
}

void KKey::KeyPress(ClassDiagramForm *classDiagramForm) {
	Class *object = static_cast<Class*>(classDiagramForm->selection->GetAt(0));
	if (object->GetMethodPosition() != -1) {
		object->RemoveMethod();
	}
}

void KKey::KeyPress(TextEdit *textEdit) {

}