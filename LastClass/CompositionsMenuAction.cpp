#include "CompositionsMenuAction.h"
#include "ClassDiagramForm.h"
#include "MouseLButton.h"
CompositionsMenuAction::CompositionsMenuAction() {
}
CompositionsMenuAction::~CompositionsMenuAction() {
}
void CompositionsMenuAction::MenuPress(ClassDiagramForm *classDiagramForm) {
	classDiagramForm->mouseLButton->ChangeState(48);
}