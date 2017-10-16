//GraphicCtrlUndoKey.cpp

#include "GraphicCtrlUndoKey.h"
#include "ClassDiagramForm.h"
#include "HistoryGraphic.h"
#include "Diagram.h"
#include "Selection.h"

GraphicCtrlUndoKey::GraphicCtrlUndoKey() {
}
GraphicCtrlUndoKey::GraphicCtrlUndoKey(const GraphicCtrlUndoKey& source) {
}
GraphicCtrlUndoKey::~GraphicCtrlUndoKey() {
}

void GraphicCtrlUndoKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
	if (classDiagramForm->historyGraphic->undoGraphicArray->GetLength() > 0) {
		Diagram *diagram_;
		Long zoomRate_;
		classDiagramForm->historyGraphic->PopUndoGraphic(&diagram_, &zoomRate_);

		Diagram *tempDiagram = new Diagram(*(classDiagramForm->diagram));
		classDiagramForm->historyGraphic->PushRedo(tempDiagram, zoomRate_);

		delete classDiagramForm->diagram;
		classDiagramForm->diagram = diagram_;
		classDiagramForm->zoomRate = zoomRate_;
	}
	classDiagramForm->selection->DeleteAllItems();
}

void GraphicCtrlUndoKey::KeyPress(TextEdit *textEdit) {
}