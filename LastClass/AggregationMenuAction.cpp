#include "AggregationMenuAction.h"
#include "ClassDiagramForm.h"
#include "MouseLButton.h"
AggregationMenuAction::AggregationMenuAction() {
}
AggregationMenuAction::~AggregationMenuAction() {
}
void AggregationMenuAction::MenuPress(ClassDiagramForm *classDiagramForm) {
	classDiagramForm->mouseLButton->ChangeState(55);
}