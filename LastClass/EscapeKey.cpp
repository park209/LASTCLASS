//EscapeKey.cpp

#include "EscapeKey.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "ClassDiagramForm.h"

EscapeKey::EscapeKey() {
}
EscapeKey::EscapeKey(const EscapeKey& source) {
}
EscapeKey::~EscapeKey() {
}
void EscapeKey::KeyPress(TextEdit *textEdit) {
	textEdit->OnClose();
}

void EscapeKey::KeyPress(ClassDiagramForm *classDiagramForm) {
}