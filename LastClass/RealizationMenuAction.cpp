#include "RealizationMenuAction.h"
#include "ClassDiagramForm.h"
#include "MouseLButton.h"
RealizationMenuAction::RealizationMenuAction() {
}
RealizationMenuAction::~RealizationMenuAction() {
}
void RealizationMenuAction::MenuPress(ClassDiagramForm *classDiagramForm) {
	classDiagramForm->mouseLButton->ChangeState(51);
}