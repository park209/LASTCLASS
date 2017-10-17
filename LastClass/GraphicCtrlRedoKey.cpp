//GraphicCtrlRedoKey.cpp

#include "GraphicCtrlRedoKey.h"
#include "ClassDiagramForm.h"
#include "HistoryGraphic.h"
#include "Diagram.h"
#include "Selection.h"
#include "LastClass.h"
#include "StatusBar.h"

GraphicCtrlRedoKey::GraphicCtrlRedoKey() {
}
GraphicCtrlRedoKey::GraphicCtrlRedoKey(const GraphicCtrlRedoKey& source) {
}
GraphicCtrlRedoKey::~GraphicCtrlRedoKey() {
}

void GraphicCtrlRedoKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
	if (classDiagramForm->historyGraphic->redoGraphicArray->GetLength() > 0) {
		Diagram *diagram_;
		Long zoomRate_;
		classDiagramForm->historyGraphic->PopRedoGraphic(&diagram_, &zoomRate_);

		Diagram *tempDiagram = new Diagram(*(classDiagramForm->diagram));
		classDiagramForm->historyGraphic->PushUndo(tempDiagram, zoomRate_);

		delete classDiagramForm->diagram;
		classDiagramForm->diagram = diagram_;
		classDiagramForm->zoomRate = zoomRate_;
		classDiagramForm->lastClass->statusBar->DestroyStatus();
		classDiagramForm->lastClass->statusBar->MakeStatusBar(classDiagramForm->lastClass, classDiagramForm->lastClass->GetSafeHwnd(), 0, 0, 5);
	}
	classDiagramForm->selection->DeleteAllItems();
}

void GraphicCtrlRedoKey::KeyPress(TextEdit *textEdit) {
}