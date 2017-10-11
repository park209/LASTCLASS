#include "AggregationMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "MouseLButton.h"
AggregationMenuAction::AggregationMenuAction() {
}
AggregationMenuAction::~AggregationMenuAction() {
}
void AggregationMenuAction::MenuPress(LastClass* lastClass) {
	lastClass->classDiagramForm->mouseLButton->ChangeDrawingAggregationState();
}