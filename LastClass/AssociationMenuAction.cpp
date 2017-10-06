#include "AssociationMenuAction.h"
#include "ClassDiagramForm.h"
#include "MouseLButton.h"
AssociationMenuAction::AssociationMenuAction() {
}
AssociationMenuAction::~AssociationMenuAction() {
}
void AssociationMenuAction::MenuPress(ClassDiagramForm *classDiagramForm) {
	classDiagramForm->mouseLButton->ChangeState(53);
}