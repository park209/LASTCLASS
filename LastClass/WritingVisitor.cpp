//WritingVIsitor.cpp

#include "WritingVisitor.h"
#include "Text.h"
#include "MemoBox.h"
#include "ClassName.h"
#include "Attribute.h"
#include "Method.h"
#include "Reception.h"
#include "Template.h"
#include "ClassDiagramForm.h"
#include <afxwin.h>

WritingVisitor::WritingVisitor() {
}
WritingVisitor::~WritingVisitor() {
}
void WritingVisitor::Visit(Diagram *diagram, Selection *selection, Long distanceX, Long distanceY) {
}
void WritingVisitor::Visit(Class *object, CDC* cPaintDc) {
}
void WritingVisitor::Visit(Text* text, CDC* cPaintDc) {
	Long fontHeight = cPaintDc->GetTextExtent("아").cy; // rowHeight 구하는방법
	Long textWidth = text->MaxWidth(cPaintDc);
	CFont* cFont = cPaintDc->GetCurrentFont();

	CDC memDC;
	CBitmap *pOldBitmap;
	CBitmap bitmap;

	memDC.CreateCompatibleDC(cPaintDc); // memDC 호환되는걸 만듦
	bitmap.CreateCompatibleBitmap(cPaintDc, textWidth, text->GetLength() * fontHeight); // 호환되는 비트맵 만듦
	pOldBitmap = memDC.SelectObject(&bitmap); // memDC 에 bitmap 을 연결
	memDC.FillSolidRect(CRect(0, 0, textWidth, text->GetLength() * fontHeight), RGB(255, 255, 255));
	memDC.SelectObject(cFont);

	RECT rt = { 0 , 0, textWidth, text->GetLength() * fontHeight};
	memDC.DrawText((CString)text->MakeText().c_str(), &rt, DT_EXPANDTABS | DT_NOCLIP);

	cPaintDc->BitBlt(0, 0, textWidth, text->GetLength() * fontHeight, &memDC, 0, 0, SRCCOPY); // bitblt memDC 에 있는걸 dc로 뿌려준다

	memDC.SelectObject(pOldBitmap);
	bitmap.DeleteObject();
	memDC.DeleteDC();
	//memDC.SelectObject(cFont);
	//cFont->DeleteObject();
}
void WritingVisitor::Visit(MemoBox *memoBox, CDC *cPaintDc) { //접힌부분아래로 적히게
	RECT rt = { memoBox->GetX() + GabX , memoBox->GetY() + MemoGab, memoBox->GetX() + memoBox->GetWidth() - GabX, memoBox->GetY() + memoBox->GetHeight() - GabY };
	cPaintDc->DrawText((CString)memoBox->GetContent().c_str(), &rt, DT_EXPANDTABS | DT_NOCLIP);
}
void WritingVisitor::Visit(Selection *selection, CDC *cPaintDc) {
}
void WritingVisitor::Visit(Template *object, CDC *cPaintDc) {
	RECT rt = { object->GetX() + GabX , object->GetY() + GabY, object->GetX() + object->GetWidth() - GabX, object->GetY() + object->GetHeight() - GabY };
	cPaintDc->DrawText((CString)object->GetContent().c_str(), &rt, DT_EXPANDTABS | DT_NOCLIP);

}
void WritingVisitor::Visit(ClassName* className, CDC* cPaintDc) {
	RECT rt = { className->GetX() + GabX , className->GetY() + GabY, className->GetX() + className->GetWidth() - GabX, className->GetY() + className->GetHeight() - GabY };
	cPaintDc->DrawText((CString)className->GetContent().c_str(), &rt, DT_EXPANDTABS | DT_NOCLIP);
}
void WritingVisitor::Visit(Attribute* attribute, CDC* cPaintDc) {
	RECT rt = { attribute->GetX() + GabX , attribute->GetY() + GabY, attribute->GetX() + attribute->GetWidth() - GabX, attribute->GetY() + attribute->GetHeight() - GabY };
	cPaintDc->DrawText((CString)attribute->GetContent().c_str(), &rt, DT_EXPANDTABS | DT_NOCLIP);
}
void WritingVisitor::Visit(Method* method, CDC* cPaintDc) {
	RECT rt = { method->GetX() + GabX , method->GetY() + GabY, method->GetX() + method->GetWidth() - GabX, method->GetY() + method->GetHeight() - GabY };
	cPaintDc->DrawText((CString)method->GetContent().c_str(), &rt, DT_EXPANDTABS | DT_NOCLIP);
}
void WritingVisitor::Visit(Reception* reception, CDC* cPaintDc) {
	RECT rt = { reception->GetX() + GabX , reception->GetY() + GabY, reception->GetX() + reception->GetWidth() - GabX, reception->GetY() + reception->GetHeight() - GabX };
	cPaintDc->DrawText((CString)reception->GetContent().c_str(), &rt, DT_EXPANDTABS | DT_NOCLIP);
}
void WritingVisitor::Visit(Line *line, CDC* cPaintDc) {
}
void WritingVisitor::Visit(Generalization *generalization, CDC* cPaintDc) {
}
void WritingVisitor::Visit(Realization *realization, CDC* cPaintDc) {
}
void WritingVisitor::Visit(Dependency *dependency, CDC* cPaintDc) {
}
void WritingVisitor::Visit(Association *association, CDC* cPaintDc) {
}
void WritingVisitor::Visit(DirectedAssociation *directedAssociation, CDC* cPaintDc) {
}
void WritingVisitor::Visit(Aggregation *aggregation, CDC* cPaintDc) {
}
void WritingVisitor::Visit(Aggregations *aggregations, CDC* cPaintDc) {
}
void WritingVisitor::Visit(Composition *composition, CDC* cPaintDc) {
}
void WritingVisitor::Visit(Compositions *compositions, CDC* cPaintDc) {
}
void WritingVisitor::Visit(MemoLine *memoLine, CDC *cPaintDc) {
}
void WritingVisitor::Visit(SelfGeneralization *selfGeneralization, CDC *cPaintDc) {
}
void WritingVisitor::Visit(SelfDependency *selfDependency, CDC *cPaintDc) {
}
void WritingVisitor::Visit(SelfAggregation *selfAggregation, CDC *cPaintDc) {
}
void WritingVisitor::Visit(SelfAssociation *selfAssociation, CDC *cPaintDc) {
}
void WritingVisitor::Visit(SelfAggregations *selfAggregations, CDC *cPaintDc) {
}
void WritingVisitor::Visit(SelfDirectedAssociation *selfDirectedAssociation, CDC *cPaintDc) {
}
void WritingVisitor::Visit(SelfComposition *selfComposition, CDC *cPaintDc) {
}
void WritingVisitor::Visit(SelfCompositions *selfCompositions, CDC *cPaintDc) {
}
