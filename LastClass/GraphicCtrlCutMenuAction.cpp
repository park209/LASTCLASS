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
	GraphicCtrlCutKey *ctrlCut = new GraphicCtrlCutKey;
	CClientDC dc(lastClass->classDiagramForm);
	ctrlCut->KeyPress(lastClass->classDiagramForm, &dc);
	lastClass->classDiagramForm->Invalidate(false);
	if (ctrlCut != 0) {
		delete ctrlCut;
	}
}