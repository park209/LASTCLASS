//GraphicUpArrowKey.cpp

#include "GraphicUpArrowKey.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"
#include "OnVScrollLineUp.h"
GraphicUpArrowKey::GraphicUpArrowKey() {
}

GraphicUpArrowKey::GraphicUpArrowKey(const GraphicUpArrowKey& source) {
}

GraphicUpArrowKey::~GraphicUpArrowKey() {
}

void GraphicUpArrowKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
	OnVScrollLineUp onVScrollLineUp;
	onVScrollLineUp.Scrolling(classDiagramForm);
}

void GraphicUpArrowKey::KeyPress(TextEdit *textEdit) {
}