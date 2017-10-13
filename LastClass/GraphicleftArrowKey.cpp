//GraphicLeftArrowKey.cpp

#include "GraphicLeftArrowKey.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"
#include "OnHScrollLineLeft.h"

GraphicLeftArrowKey::GraphicLeftArrowKey() {
}

GraphicLeftArrowKey::GraphicLeftArrowKey(const GraphicLeftArrowKey& source) {
}

GraphicLeftArrowKey::~GraphicLeftArrowKey() {
}

void GraphicLeftArrowKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
	OnHScrollLineLeft onHScrollLineLeft;
		onHScrollLineLeft.Scrolling(classDiagramForm);
}

void GraphicLeftArrowKey::KeyPress(TextEdit *textEdit) {
}