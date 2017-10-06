//GraphicCtrlRedoKey.cpp

#include "GraphicCtrlRedoKey.h"
#include "ClassDiagramForm.h"
#include "HistoryGraphic.h"
#include "Diagram.h"

GraphicCtrlRedoKey::GraphicCtrlRedoKey() {
}
GraphicCtrlRedoKey::GraphicCtrlRedoKey(const GraphicCtrlRedoKey& source) {
}
GraphicCtrlRedoKey::~GraphicCtrlRedoKey() {
}

void GraphicCtrlRedoKey::KeyPress(ClassDiagramForm *classDiagramForm) {
	if (classDiagramForm->historyGraphic->redoGraphicArray->GetLength() > 0) {
		Diagram *diagram_ = classDiagramForm->historyGraphic->PopRedoGraphic();

		Diagram *tempDiagram = new Diagram(*(classDiagramForm->diagram));
		classDiagramForm->historyGraphic->PushUndo(tempDiagram);

		delete classDiagramForm->diagram;
		classDiagramForm->diagram = diagram_;
	}
}

void GraphicCtrlRedoKey::KeyPress(TextEdit *textEdit) {
}