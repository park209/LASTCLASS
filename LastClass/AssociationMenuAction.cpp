#include "AssociationMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "MouseLButton.h"
AssociationMenuAction::AssociationMenuAction() {
}
AssociationMenuAction::~AssociationMenuAction() {
}
void AssociationMenuAction::MenuPress(LastClass* lastClass) {
	lastClass->classDiagramForm->mouseLButton->ChangeDrawingAssociationState();
}