#include "EditResizerBlocker.h"
#include "EditResizer.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"
#include "Text.h"
#include "Figure.h"
#include "Selection.h"
#include "Class.h"
#include "Diagram.h"
#include "HistoryText.h"
#include "CtrlUndoTextKey.h"
#include "Relation.h"
#include "SelfRelation.h"
#include "Template.h"

EditResizerBlocker::EditResizerBlocker() {

}
EditResizerBlocker::EditResizerBlocker(const EditResizerBlocker& source) {

}
EditResizerBlocker::~EditResizerBlocker() {

}

void EditResizerBlocker::Block(TextEdit *textEdit, CDC *pDC) {
	EditResizer editResizer;
	CtrlUndoTextKey undo;
	RECT editRect;

	textEdit->GetClientRect(&editRect);


	if (!dynamic_cast<Relation*>(textEdit->figure) && !dynamic_cast<SelfRelation*>(textEdit->figure)) {

		FigureComposite *object = dynamic_cast<FigureComposite*>(textEdit->classDiagramForm->selection->GetAt(0));

		CRect rt(object->GetX(), object->GetY(), object->GetX() + object->GetWidth(), object->GetY() + object->GetHeight());

		if (textEdit->text->MaxWidth(pDC) + CaretWidth > editRect.right) {
			rt.right += textEdit->text->MaxWidth(pDC) + CaretWidth - editRect.right;
		}
		if (textEdit->GetRowHeight() * textEdit->text->GetLength() > editRect.bottom) {
			rt.bottom += textEdit->GetRowHeight() * textEdit->text->GetLength() - editRect.bottom;
		}

		if (!textEdit->classDiagramForm->diagram->CheckOverlap(rt, object)) {
			editResizer.ResizeEdit(textEdit, pDC);
			editResizer.ResizeClass(textEdit, pDC);
			textEdit->classDiagramForm->Invalidate(false);
		}
		else {
			undo.KeyPress(textEdit);
		}
	}
}