#include "SaveMenuAction.h"
#include "ClassDiagramForm.h"

SaveMenuAction::SaveMenuAction() {
}
SaveMenuAction::~SaveMenuAction() {
}
void SaveMenuAction::MenuPress(ClassDiagramForm *classDiagramForm) {

		classDiagramForm->Save();

}