#include "ClassMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "MouseLButton.h"
#include "DrawingClass.h"
ClassMenuAction::ClassMenuAction() {
}
ClassMenuAction::~ClassMenuAction() {
}
void ClassMenuAction::MenuPress(LastClass* lastClass) {

	lastClass->classDiagramForm->mouseLButton->ChangeDrawingClassState();

}