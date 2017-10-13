//GraphicDownArrowKey.cpp

#include "GraphicDownArrowKey.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"
#include "OnVScrollLineDown.h"

GraphicDownArrowKey::GraphicDownArrowKey() {
}

GraphicDownArrowKey::GraphicDownArrowKey(const GraphicDownArrowKey& source) {
}

GraphicDownArrowKey::~GraphicDownArrowKey() {
}

void GraphicDownArrowKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
	OnVScrollLineDown onVScrollLineDown;
	onVScrollLineDown.Scrolling(classDiagramForm);
}

void GraphicDownArrowKey::KeyPress(TextEdit *textEdit) {
}