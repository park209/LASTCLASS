#include "CompositionMenuAction.h"
#include "ClassDiagramForm.h"
#include "MouseLButton.h"
CompositionMenuAction::CompositionMenuAction() {
}
CompositionMenuAction::~CompositionMenuAction() {
}
void CompositionMenuAction::MenuPress(ClassDiagramForm *classDiagramForm) {
	classDiagramForm->mouseLButton->ChangeState(57);
}