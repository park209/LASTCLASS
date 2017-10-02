//DeleteGraphicKey.cpp

#include "DeleteGraphicKey.h"
#include "ClassDiagramForm.h"
#include "HistoryGraphic.h"
#include "Selection.h"
#include "Class.h"
#include "TextEdit.h"

DeleteGraphicKey::DeleteGraphicKey() {
}

DeleteGraphicKey::DeleteGraphicKey(const DeleteGraphicKey& source) {
}

DeleteGraphicKey::~DeleteGraphicKey() {
}

void DeleteGraphicKey::KeyPress(ClassDiagramForm *classDiagramForm) {
	if (classDiagramForm->selection->GetLength() > 0) {
		classDiagramForm->historyGraphic->PushUndo(classDiagramForm->diagram);
		classDiagramForm->selection->Remove(classDiagramForm->diagram, classDiagramForm->selection->GetAt(classDiagramForm->selection->GetLength() - 1));
	}
}

void DeleteGraphicKey::KeyPress(TextEdit *textEdit) {

}