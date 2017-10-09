//GraphicCtrlRedoMenuAction.cpp

#include "GraphicCtrlRedoMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "GraphicCtrlRedoKey.h"

GraphicCtrlRedoMenuAction::GraphicCtrlRedoMenuAction() {
}
GraphicCtrlRedoMenuAction::GraphicCtrlRedoMenuAction(const GraphicCtrlRedoMenuAction& source) {
}
GraphicCtrlRedoMenuAction::~GraphicCtrlRedoMenuAction() {
}

void GraphicCtrlRedoMenuAction::MenuPress(LastClass *lastClass) {
	GraphicCtrlRedoKey *ctrlRedo = new GraphicCtrlRedoKey;
	ctrlRedo->KeyPress(lastClass->classDiagramForm);
	lastClass->classDiagramForm->Invalidate(false);
}