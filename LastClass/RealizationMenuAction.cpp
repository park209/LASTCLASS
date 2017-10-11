#include "RealizationMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "MouseLButton.h"
RealizationMenuAction::RealizationMenuAction() {
}
RealizationMenuAction::~RealizationMenuAction() {
}
void RealizationMenuAction::MenuPress(LastClass* lastClass) {
	lastClass->classDiagramForm->mouseLButton->ChangeDrawingRealizationState();
}