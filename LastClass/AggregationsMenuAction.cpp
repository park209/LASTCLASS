#include "AggregationsMenuAction.h"
#include "ClassDiagramForm.h"
#include "MouseLButton.h"
AggregationsMenuAction::AggregationsMenuAction() {
}
AggregationsMenuAction::~AggregationsMenuAction() {
}
void AggregationsMenuAction::MenuPress(ClassDiagramForm *classDiagramForm) {
	classDiagramForm->mouseLButton->ChangeState(56);
}