#include "DirectedAssociationMenuAction.h"
#include "ClassDiagramForm.h"
#include "MouseLButton.h"
DirectedAssociationMenuAction::DirectedAssociationMenuAction() {
}
DirectedAssociationMenuAction::~DirectedAssociationMenuAction() {
}
void DirectedAssociationMenuAction::MenuPress(ClassDiagramForm *classDiagramForm) {
	classDiagramForm->mouseLButton->ChangeState(54);
}