//GraphicCtrlCutMenuAction.cpp

#include "GraphicCtrlCutMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "GraphicCtrlCutKey.h"

GraphicCtrlCutMenuAction::GraphicCtrlCutMenuAction() {
}
GraphicCtrlCutMenuAction::GraphicCtrlCutMenuAction(const GraphicCtrlCutMenuAction& source) {
}
GraphicCtrlCutMenuAction::~GraphicCtrlCutMenuAction() {
}

void GraphicCtrlCutMenuAction::MenuPress(LastClass *lastClass) {
	GraphicCtrlCutKey *ctrlUndo = new GraphicCtrlCutKey;
	CClientDC dc(lastClass->classDiagramForm);
	ctrlUndo->KeyPress(lastClass->classDiagramForm, &dc);
	lastClass->classDiagramForm->Invalidate(false);
	if (ctrlUndo != 0) {
		delete ctrlUndo;
	}
}