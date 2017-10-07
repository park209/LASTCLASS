#include "SupportMenuAction.h"
#include "ClassDiagramForm.h"
#include "SupportMenu.h"

SupportMenuAction::SupportMenuAction() {
}
SupportMenuAction::~SupportMenuAction() {
}
void SupportMenuAction::MenuPress(ClassDiagramForm *classDiagramForm) {
	CRect rect;
	classDiagramForm->GetClientRect(&rect);
	SupportMenu *supportMenu = new SupportMenu();
	supportMenu->Create(NULL, "SupportMenu", WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, CRect(rect.CenterPoint().x - 450, rect.CenterPoint().y - 225 , rect.CenterPoint().x +450, rect.CenterPoint().y +225 ), classDiagramForm, 10001, NULL);
	supportMenu->SetFocus();
}