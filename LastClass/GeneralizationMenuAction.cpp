#include "GeneralizationMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "MouseLButton.h"
GeneralizationMenuAction::GeneralizationMenuAction() {
}
GeneralizationMenuAction::~GeneralizationMenuAction() {
}
void GeneralizationMenuAction::MenuPress(LastClass* lastClass) {
	lastClass->classDiagramForm->mouseLButton->ChangeDrawingGeneralizationState();
}