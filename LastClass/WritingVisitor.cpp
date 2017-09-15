//WritingVIsitor.cpp

#include "WritingVisitor.h"
#include "Text.h"
#include "MemoBox.h"
#include "ClassName.h"
#include "Attribute.h"
#include "Method.h"
#include "Reception.h"

WritingVisitor::WritingVisitor() {
}
WritingVisitor::~WritingVisitor() {
}
void WritingVisitor::Visit(Class *object, CDC* cPaintDc) {
}
void WritingVisitor::Visit(MemoBox *memoBox, CDC *cPaintDc) {
	RECT rt = { memoBox->GetX() + 5 , memoBox->GetY() + 5, memoBox->GetX() + 5 + memoBox->GetWidth(), memoBox->GetY() + 5 + memoBox->GetHeight() };
	cPaintDc->DrawText((CString)memoBox->GetContent().c_str(), &rt, DT_EDITCONTROL | DT_EXPANDTABS);
}
void WritingVisitor::Visit(Selection *selection, CDC *cPaintDc) {
}
void WritingVisitor::Visit(Template *object, CDC *cPaintDc) {
}
void WritingVisitor::Visit(ClassName* className, CDC* cPaintDc) {
	RECT rt = { className->GetX() + 5 , className->GetY() + 5, className->GetX() + 5 + className->GetWidth(), className->GetY() + 5 + className->GetHeight() };
	cPaintDc->DrawText((CString)className->GetContent().c_str(), &rt, DT_EDITCONTROL | DT_EXPANDTABS);
}
void WritingVisitor::Visit(Attribute* attribute, CDC* cPaintDc) {
	RECT rt = { attribute->GetX() + 5 , attribute->GetY() + 5, attribute->GetX() + 5 + attribute->GetWidth(), attribute->GetY() + 5 + attribute->GetHeight() };
	cPaintDc->DrawText((CString)attribute->GetContent().c_str(), &rt, DT_EDITCONTROL | DT_EXPANDTABS);
}
void WritingVisitor::Visit(Method* method, CDC* cPaintDc) {
	RECT rt = { method->GetX() + 5 , method->GetY() + 5, method->GetX() + 5 + method->GetWidth(), method->GetY() + 5 + method->GetHeight() };
	cPaintDc->DrawText((CString)method->GetContent().c_str(), &rt, DT_EDITCONTROL | DT_EXPANDTABS);
}
void WritingVisitor::Visit(Reception* reception, CDC* cPaintDc) {
	RECT rt = { reception->GetX() + 5 , reception->GetY() + 5, reception->GetX() + 5 + reception->GetWidth(), reception->GetY() + 5 + reception->GetHeight() };
	cPaintDc->DrawText((CString)reception->GetContent().c_str(), &rt, DT_EDITCONTROL | DT_EXPANDTABS);
}
void WritingVisitor::Visit(Line *line, CDC* cPaintDc) {
}
void WritingVisitor::Visit(Generalization *generalization, CDC* cPaintDc){
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
void WritingVisitor::Visit(Text* text, CDC* cPaintDc) {
	Long fontWidth = cPaintDc->GetTextExtent("한").cx;
	Long fontHeight = cPaintDc->GetTextExtent("A").cy; // rowHeight 구하는방법
	Long textWidth = text->MaxWidth();
	// 맥스하이트 

	RECT rt = { 5 , 5, textWidth*fontWidth + 5, text->GetLength() * fontHeight + 5 };
	cPaintDc->DrawText((CString)text->MakeText().c_str(), &rt, DT_EDITCONTROL | DT_EXPANDTABS);
}