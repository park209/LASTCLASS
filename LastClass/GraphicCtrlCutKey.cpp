//GraphicCtrlCutKey.cpp

#include "GraphicCtrlCutKey.h"
#include "ClassDiagramForm.h"
#include "HistoryGraphic.h"
#include "Selection.h"
#include "Class.h"
#include "TextEdit.h"
#include "DrawingVisitor.h"
#include "WritingVisitor.h"
#include "SmartPointer.h"
#include "ArrayIterator.h"
#include "Line.h"
#include "ClassName.h"
#include "Attribute.h"
#include "Method.h"
#include "MemoBox.h"
#include "Template.h"
#include "Relation.h"
#include "Generalization.h"
#include "Realization.h"
#include "Dependency.h"
#include "Association.h"
#include "DirectedAssociation.h"
#include "Aggregation.h"
#include "Aggregations.h"
#include "Composition.h"
#include "Compositions.h"
#include "Template.h"
#include "SmartPointer.h"
#include "MemoLine.h"
#include "Finder.h"
#include "Diagram.h"
#include "LastClass.h"
#include "StatusBar.h"
#include "MouseLButton.h"
#include "DeleteGraphicKey.h"

GraphicCtrlCutKey::GraphicCtrlCutKey() {
}

GraphicCtrlCutKey::GraphicCtrlCutKey(const GraphicCtrlCutKey& source) {
}

GraphicCtrlCutKey::~GraphicCtrlCutKey() {
}

void GraphicCtrlCutKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
	if (classDiagramForm->copyBuffer != 0) {
		delete classDiagramForm->copyBuffer;
		classDiagramForm->copyBuffer = 0;
	}
	classDiagramForm->copyBuffer = new Selection(*classDiagramForm->selection);

	DeleteGraphicKey deleteGraphicKey;
	deleteGraphicKey.KeyPress(classDiagramForm, cdc);
}

void GraphicCtrlCutKey::KeyPress(TextEdit *textEdit) {

}