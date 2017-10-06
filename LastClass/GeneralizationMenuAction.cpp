#include "GeneralizationMenuAction.h"
#include "ClassDiagramForm.h"
#include "MouseLButton.h"
GeneralizationMenuAction::GeneralizationMenuAction() {
}
GeneralizationMenuAction::~GeneralizationMenuAction() {
}
void GeneralizationMenuAction::MenuPress(ClassDiagramForm *classDiagramForm) {
	classDiagramForm->mouseLButton->ChangeState(50);
}