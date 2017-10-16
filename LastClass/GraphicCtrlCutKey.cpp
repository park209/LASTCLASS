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

GraphicCtrlCutKey::GraphicCtrlCutKey() {
}

GraphicCtrlCutKey::GraphicCtrlCutKey(const GraphicCtrlCutKey& source) {
}

GraphicCtrlCutKey::~GraphicCtrlCutKey() {
}

void GraphicCtrlCutKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
	Long i = 0;
	Long j;
	Long k;
	FigureComposite *selectedComposite;
	FigureComposite *composite;
	Figure *relation;
	Long relationEndX;
	Long relationEndY;

	if (classDiagramForm->copyBuffer != 0) {
		delete classDiagramForm->copyBuffer;
		classDiagramForm->copyBuffer = 0;
	}
	classDiagramForm->copyBuffer = new Selection(*classDiagramForm->selection);
	while (i < classDiagramForm->selection->GetLength()) {
		if (dynamic_cast<FigureComposite*>(classDiagramForm->selection->GetAt(i))) {
			selectedComposite = static_cast<FigureComposite*>(classDiagramForm->selection->GetAt(i));
			j = 0;
			while (j < classDiagramForm->diagram->GetLength()) {
				composite = static_cast<FigureComposite*>(classDiagramForm->diagram->GetAt(j));
				k = 0;
				while (k < composite->GetLength()) {
					if (dynamic_cast<Relation*>(composite->GetAt(k))) {
						relation = composite->GetAt(k);
						relationEndX = relation->GetX() + relation->GetWidth();
						relationEndY = relation->GetY() + relation->GetHeight();
						if (selectedComposite->GetX() <= relationEndX
							&& relationEndX <= selectedComposite->GetX() + selectedComposite->GetWidth()
							&& selectedComposite->GetY() <= relationEndY
							&& relationEndY <= selectedComposite->GetY() + selectedComposite->GetHeight()) {
							classDiagramForm->selection->Add(relation);
						}
					}
					k++;
				}
				j++;
			}
		}
		i++;
	}

	if (classDiagramForm->selection->GetLength() > 0) {
		classDiagramForm->historyGraphic->PushUndo(classDiagramForm->diagram);
		while (classDiagramForm->selection->GetLength() != 0) {
			classDiagramForm->selection->Remove(classDiagramForm->diagram, classDiagramForm->selection->GetAt(classDiagramForm->selection->GetLength() - 1));
		}
	}
}

void GraphicCtrlCutKey::KeyPress(TextEdit *textEdit) {

}