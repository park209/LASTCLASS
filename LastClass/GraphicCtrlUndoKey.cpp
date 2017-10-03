//GraphicCtrlUndoKey.cpp

#include "GraphicCtrlUndoKey.h"
#include "ClassDiagramForm.h"
#include "HistoryGraphic.h"
#include "Diagram.h"

GraphicCtrlUndoKey::GraphicCtrlUndoKey() {
}
GraphicCtrlUndoKey::GraphicCtrlUndoKey(const GraphicCtrlUndoKey& source) {
}
GraphicCtrlUndoKey::~GraphicCtrlUndoKey() {
}

void GraphicCtrlUndoKey::KeyPress(ClassDiagramForm *classDiagramForm) {
	if (classDiagramForm->historyGraphic->undoGraphicArray->GetLength() > 0) {
		Diagram *diagram_ = classDiagramForm->historyGraphic->PopUndoGraphic();

		Diagram *tempDiagram = new Diagram(*(classDiagramForm->diagram));
		classDiagramForm->historyGraphic->PushRedo(tempDiagram);

		delete classDiagramForm->diagram;
		classDiagramForm->diagram = diagram_;
	}
}

void GraphicCtrlUndoKey::KeyPress(TextEdit *textEdit) {
}