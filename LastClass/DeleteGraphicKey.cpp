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

void DeleteGraphicKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
	//Long i = 0;
	//Long j;
	//while (i < classDiagramForm->selection->GetLength()) {
	//	if (dynamic_cast<FigureComposite*>(classDiagramForm->selection->GetAt(i))) {
	//		j = 0;
	//		while()
	//	}
	//}
	if (classDiagramForm->selection->GetLength() > 0) {
		classDiagramForm->historyGraphic->PushUndo(classDiagramForm->diagram);
		while (classDiagramForm->selection->GetLength() != 0) {
			classDiagramForm->selection->Remove(classDiagramForm->diagram, classDiagramForm->selection->GetAt(classDiagramForm->selection->GetLength() - 1));
		}
	}
}

void DeleteGraphicKey::KeyPress(TextEdit *textEdit) {

}