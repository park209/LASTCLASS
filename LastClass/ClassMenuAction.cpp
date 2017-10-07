#include "ClassMenuAction.h"
#include "ClassDiagramForm.h"
#include "MouseLButton.h"
ClassMenuAction::ClassMenuAction() {
}
ClassMenuAction::~ClassMenuAction() {
}
void ClassMenuAction::MenuPress(ClassDiagramForm *classDiagramForm) {
	classDiagramForm->mouseLButton->ChangeState(49);
}