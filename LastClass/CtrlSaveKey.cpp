//CtrlSaveKey.cpp

#include "CtrlSaveKey.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"

CtrlSaveKey::CtrlSaveKey() {
}

CtrlSaveKey::CtrlSaveKey(const CtrlSaveKey& source) {
}

CtrlSaveKey::~CtrlSaveKey() {
}

void CtrlSaveKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
	classDiagramForm->Save();
}

void CtrlSaveKey::KeyPress(TextEdit *textEdit) {
	textEdit->classDiagramForm->Save();
}