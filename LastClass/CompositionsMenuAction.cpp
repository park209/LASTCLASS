#include "CompositionsMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "MouseLButton.h"
CompositionsMenuAction::CompositionsMenuAction() {
}
CompositionsMenuAction::~CompositionsMenuAction() {
}
void CompositionsMenuAction::MenuPress(LastClass* lastClass) {
	lastClass->classDiagramForm->mouseLButton->ChangeDrawingCompositionsState();
}