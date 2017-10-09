//GraphicCtrlAllKey.cpp

#include "GraphicCtrlAllKey.h"
#include "ClassDiagramForm.h"
#include "Diagram.h"
#include "Selection.h"
#include "MouseLButton.h"
#include "MouseLButtonAction.h"
#include "SelectionState.h"
#include "MultipleSelectionState.h"

GraphicCtrlAllKey::GraphicCtrlAllKey() {
}

GraphicCtrlAllKey::GraphicCtrlAllKey(const GraphicCtrlAllKey& source) {
}

GraphicCtrlAllKey::~GraphicCtrlAllKey() {
}

void GraphicCtrlAllKey::KeyPress(ClassDiagramForm *classDiagramForm) {
	Long i = 0;
	classDiagramForm->selection->DeleteAllItems();
	while (i < classDiagramForm->diagram->GetLength()) {
		classDiagramForm->selection->Add(classDiagramForm->diagram->GetAt(i));
		//j = 0; // 전체선택 선까지 ㅁ 표시 나오게 하려면 클래스일때 내부에 선 전부 selection 배열에 넣어주는거 필요함 // 근데 필요없을듯
		//while (classDiagramForm->diagram->GetAt(i)->
		i++;
	}
	if (classDiagramForm->selection->GetLength() == 1) {
		classDiagramForm->mouseLButton->ChangeState(SelectionState::Instance());
	}
	if (classDiagramForm->selection->GetLength() > 1) {
		classDiagramForm->mouseLButton->ChangeState(MultipleSelectionState::Instance());
	}
}

void GraphicCtrlAllKey::KeyPress(TextEdit *textEdit) {
}