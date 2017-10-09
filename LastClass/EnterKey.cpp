//EnterKey.cpp

#include "EnterKey.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "ClassDiagramForm.h"
#include "Figure.h"

EnterKey::EnterKey() {
}
EnterKey::EnterKey(const EnterKey& source) {
}
EnterKey::~EnterKey() {
}

void EnterKey::KeyPress(TextEdit *textEdit) {
	textEdit->OnClose();
}

void EnterKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
}