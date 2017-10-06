#include "DependencyMenuAction.h"
#include "ClassDiagramForm.h"
#include "MouseLButton.h"
DependencyMenuAction::DependencyMenuAction() {
}
DependencyMenuAction::~DependencyMenuAction() {
}
void DependencyMenuAction::MenuPress(ClassDiagramForm *classDiagramForm) {
	classDiagramForm->mouseLButton->ChangeState(52);
}