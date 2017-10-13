//GraphicRightArrowKey.cpp

#include "GraphicRightArrowKey.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"
#include "OnHScrollLineRight.h"

GraphicRightArrowKey::GraphicRightArrowKey() {
}

GraphicRightArrowKey::GraphicRightArrowKey(const GraphicRightArrowKey& source) {
}

GraphicRightArrowKey::~GraphicRightArrowKey() {
}

void GraphicRightArrowKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
	OnHScrollLineRight onHScrollLineRight;
	onHScrollLineRight.Scrolling(classDiagramForm);
}

void GraphicRightArrowKey::KeyPress(TextEdit *textEdit) {
}