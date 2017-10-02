//AddReceptionKey.cpp

#include "AddReceptionKey.h"
#include "ClassDiagramForm.h"
#include "Selection.h"
#include "Class.h"
#include "TextEdit.h"
#include "Diagram.h"
#include "HistoryGraphic.h"

AddReceptionKey::AddReceptionKey() {
}

AddReceptionKey::AddReceptionKey(const AddReceptionKey& source) {
}

AddReceptionKey::~AddReceptionKey() {
}

void AddReceptionKey::KeyPress(ClassDiagramForm *classDiagramForm) {
	//if (classDiagramForm->selection->GetLength() > 0) {
	//	Class *object = static_cast<Class*>(classDiagramForm->selection->GetAt(0));
	/////////////////
	Diagram *diagram_ = classDiagramForm->historyGraphic->PopUndoGraphic();
	if (diagram_ != 0) {
		delete classDiagramForm->diagram;
		classDiagramForm->diagram = diagram_;
	}
	///////////////////
		/*if (object->GetReceptionPosition() == -1) {
			classDiagramForm->historyGraphic->PushUndo(classDiagramForm->diagram);
			object->AddReception(classDiagramForm->diagram);
		}
	}*/

}

void AddReceptionKey::KeyPress(TextEdit *textEdit) {

}