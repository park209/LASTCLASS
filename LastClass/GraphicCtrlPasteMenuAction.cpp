//GraphicCtrlPasteMenuAction.cpp

#include "GraphicCtrlPasteMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "GraphicCtrlPasteKey.h"

GraphicCtrlPasteMenuAction::GraphicCtrlPasteMenuAction() {
}
GraphicCtrlPasteMenuAction::GraphicCtrlPasteMenuAction(const GraphicCtrlPasteMenuAction& source) {
}
GraphicCtrlPasteMenuAction::~GraphicCtrlPasteMenuAction() {
}

void GraphicCtrlPasteMenuAction::MenuPress(LastClass *lastClass) {
	GraphicCtrlPasteKey *ctrlUndo = new GraphicCtrlPasteKey;
	CClientDC dc(lastClass->classDiagramForm);
	ctrlUndo->KeyPress(lastClass->classDiagramForm, &dc);
	lastClass->classDiagramForm->Invalidate(false);
	if (ctrlUndo != 0) {
		delete ctrlUndo;
	}
}