//DeleteSelectedOne.cpp

#include "DeleteSelectedOne.h"
#include "ClassDiagramForm.h"
#include "Selection.h"
#include "Class.h"
#include "TextEdit.h"

DeleteSelectedOne::DeleteSelectedOne() {
}

DeleteSelectedOne::DeleteSelectedOne(const DeleteSelectedOne& source) {
}

DeleteSelectedOne::~DeleteSelectedOne() {
}

void DeleteSelectedOne::KeyPress(ClassDiagramForm *classDiagramForm) {
	while (classDiagramForm->selection->GetLength() != 0) {
		classDiagramForm->selection->Remove(classDiagramForm->diagram, classDiagramForm->selection->GetAt(classDiagramForm->selection->GetLength() - 1));
	}
}

void DeleteSelectedOne::KeyPress(TextEdit *textEdit) {

}