//GraphicCtrlUndoMenuAction.cpp

#include "GraphicCtrlUndoMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "GraphicCtrlUndoKey.h"

GraphicCtrlUndoMenuAction::GraphicCtrlUndoMenuAction() {
}
GraphicCtrlUndoMenuAction::GraphicCtrlUndoMenuAction(const GraphicCtrlUndoMenuAction& source) {
}
GraphicCtrlUndoMenuAction::~GraphicCtrlUndoMenuAction() {
}

void GraphicCtrlUndoMenuAction::MenuPress(LastClass *lastClass) {
	GraphicCtrlUndoKey *ctrlUndo = new GraphicCtrlUndoKey;
	CClientDC dc(lastClass->classDiagramForm);
	ctrlUndo->KeyPress(lastClass->classDiagramForm,&dc);
	lastClass->classDiagramForm->Invalidate(false);
}