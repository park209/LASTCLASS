//TextEdit.cpp

#include "TextEdit.h"
#include "SingleByteCharacter.h"
#include "WritingVisitor.h"

#include <iostream>
//#include <fstream> //로드세이브할때

using namespace std;

BEGIN_MESSAGE_MAP(TextEdit, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_CHAR()
	ON_WM_LBUTTONDOWN()
	//ON_WM_LBUTTONUP()
	//ON_WM_KEYDOWN()
	ON_WM_KILLFOCUS()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

TextEdit::TextEdit(ClassDiagramForm *classDiagramForm, Long x, Long y, Long width, Long height) {
	this->classDiagramForm = classDiagramForm;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

int TextEdit::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CFrameWnd::OnCreate(lpCreateStruct); //코드재사용 오버라이딩 //상속에서
	
	ModifyStyle(WS_CAPTION, 0);
	//1.3. 윈도우를 갱신한다
	Invalidate();

	return 0;
}

void TextEdit::OnPaint() {
	CPaintDC dc(this);

	//클래스 이름, 캐럿 출력
	CreateSolidCaret(5, 20);
	if (this->classDiagramForm->text->GetLength() == 0) {
		SetCaretPos(CPoint(5, 5));
	}
	else {
		SetCaretPos(CPoint(this->classDiagramForm->text->GetAt(0)->GetLength()*10 + 5, 5));
	}
	ShowCaret();

	WritingVisitor writingVisitor;
	this->classDiagramForm->text->Accept(writingVisitor, &dc);
}

void TextEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
	char nCharacter = nChar;

	if (this->classDiagramForm->text->GetLength() ==  0) {
		Row newRow;
		this->classDiagramForm->text->Add(newRow.Clone());
	}
	SingleByteCharacter singleByteCharacter(nCharacter, this->classDiagramForm->text->GetAt(0)->GetLength(), 5+10*this->classDiagramForm->text->GetAt(0)->GetLength(), 5);
	this->classDiagramForm->text->GetAt(0)->Add(singleByteCharacter.Clone());

	Invalidate();
}

void TextEdit::OnLButtonDown(UINT nFlags, CPoint point) {
	if (point.x > this->GetWidth() || point.x < 0) {
		CFrameWnd::OnClose();
	}
}

void TextEdit::OnKillFocus(CWnd *pNewWnd) {

	CFrameWnd::OnClose();
}

void TextEdit::OnClose() {

	CFrameWnd::OnClose();
}