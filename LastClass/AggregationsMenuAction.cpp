#include "AggregationsMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "MouseLButton.h"
AggregationsMenuAction::AggregationsMenuAction() {
}
AggregationsMenuAction::~AggregationsMenuAction() {
}
void AggregationsMenuAction::MenuPress(LastClass* lastClass) {
	lastClass->classDiagramForm->mouseLButton->ChangeDrawingAggregationsState();
}