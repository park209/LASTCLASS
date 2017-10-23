//GraphicCtrlCopyKey.cpp

#include "GraphicCtrlCopyKey.h"
#include "ClassDiagramForm.h"
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

GraphicCtrlCopyKey::GraphicCtrlCopyKey() {
}

GraphicCtrlCopyKey::GraphicCtrlCopyKey(const GraphicCtrlCopyKey& source) {
}

GraphicCtrlCopyKey::~GraphicCtrlCopyKey() {
}

void GraphicCtrlCopyKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
	if (classDiagramForm->copyBuffer != 0) {
		delete classDiagramForm->copyBuffer;
		classDiagramForm->copyBuffer = 0;
	}
	classDiagramForm->copyBuffer = classDiagramForm->selection->MakeSelectionBuffer(*classDiagramForm->selection);
	//classDiagramForm->selection->DeleteOutSideRelation(*classDiagramForm->copyBuffer);
}

void GraphicCtrlCopyKey::KeyPress(TextEdit *textEdit) {

}