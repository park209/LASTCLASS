//TextEdit.cpp

#include "TextEdit.h"
#include "ClassDiagramForm.h"
#include "Text.h"
#include "Row.h"
#include "Character.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include "Figure.h"
#include "Caret.h"
#include "KeyBoard.h"
#include "KeyAction.h"
#include "EndKey.h"
#include "TextAreaSelected.h"
#include "HistoryText.h"
#include "WritingVisitor.h"   
#include "DeleteTextArea.h"
#include "WriteKoreanText.h"
#include "DoubleClickTextArea.h"
#include "FontSet.h"

//#include <iostream>

BEGIN_MESSAGE_MAP(TextEdit, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_CHAR()
	ON_MESSAGE(WM_IME_COMPOSITION, OnComposition)
	ON_WM_KILLFOCUS()

	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()

	ON_WM_KEYDOWN()
	ON_MESSAGE(WM_IME_NOTIFY, OnIMENotify)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

TextEdit::TextEdit(Figure *figure) {
	this->text = NULL;
	this->caret = NULL;
	this->keyBoard = NULL;
	this->historyText = NULL;
	this->textAreaSelected = NULL;
	this->fontSet = NULL;
	this->figure = figure;
	this->rowHeight = 25; // 폰트 사이즈
	this->koreanEnglish = 0;
	this->flagBuffer = 0;
	this->flagInsert = 0;
	this->flagSelection = 0;
	this->currentX = 0;
	this->copyBuffer = "";
}

int TextEdit::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CWnd::OnCreate(lpCreateStruct); //override
	CWnd::SetFocus();
	this->text = new Text;
	this->caret = new Caret;
	this->keyBoard = new KeyBoard;
	this->historyText = new HistoryText;
	this->textAreaSelected = new TextAreaSelected;
	this->fontSet = new FontSet;

	this->text->SprayString(this->figure->GetContent()); // 넘겨받아온거 자료구조로 뿌려줌 ㅇㅇㅇㅇㅇ

	CWnd::HideCaret();
	::DestroyCaret();

	Invalidate();
	return 0;
}

void TextEdit::OnPaint() {
	CPaintDC dc(this);
	WritingVisitor writingVisitor;

	CFont cFont;
	cFont.CreateFont(this->rowHeight, 0, 0, 0, this->fontSet->GetFontWeight(), FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, this->fontSet->GetFaceName().c_str());
	SetFont(&cFont, TRUE);
	CFont *oldFont = dc.SelectObject(&cFont); // 폰트 시작

	if (this->flagSelection == 0) {
		dc.FillSolidRect(CRect(5, 5, figure->GetWidth() - 5, figure->GetHeight() - 5), RGB(255, 255, 255));

		this->text->Accept(writingVisitor, &dc);//받았던거 출력
		this->caret->MoveToIndex(this, &dc);
	}
	else if (this->flagSelection == 1) { // flagSelection이 눌려있으면
		this->textAreaSelected->SelectTextArea(this, &dc);
	}

	dc.SelectObject(oldFont);
	cFont.DeleteObject(); // 폰트
}

void TextEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (this->koreanEnglish == 0 && nChar != VK_BACK && nChar != VK_ESCAPE && nChar != VK_RETURN &&
		nChar != VK_SPACE && nChar != VK_TAB && nChar != 10  && GetKeyState(VK_CONTROL) >= 0) {

		if (flagSelection == 1) {
			DeleteTextArea *deleteArea = new DeleteTextArea();
			deleteArea->DeleteArea(this);
			if (deleteArea != 0) {
				delete deleteArea;
			}
		}
		char nCharacter = nChar;
		SingleByteCharacter singleByteCharacter(nCharacter);
		if (this->caret->GetCharacterIndex() == this->text->GetAt(this->caret->GetRowIndex())->GetLength()) {
			this->text->GetAt(this->caret->GetRowIndex())->Add(singleByteCharacter.Clone());
		}
		else if (this->caret->GetCharacterIndex() < this->text->GetAt(this->caret->GetRowIndex())->GetLength() && this->flagInsert == 0) {
			this->text->GetAt(this->caret->GetRowIndex())->Insert(this->caret->GetCharacterIndex(), singleByteCharacter.Clone());
		}
		else if (this->caret->GetCharacterIndex() < this->text->GetAt(this->caret->GetRowIndex())->GetLength() && this->flagInsert == 1) {
			this->text->GetAt(this->caret->GetRowIndex())->Modify(this->caret->GetCharacterIndex(), singleByteCharacter.Clone());
		}
		this->caret->MoveForwardCharacterIndex();
	}

	CWnd::HideCaret();
	::DestroyCaret();

	Invalidate();
}

Long TextEdit::OnComposition(WPARAM wParam, LPARAM lParam) {
	HIMC hIMC = ImmGetContext(GetSafeHwnd());

	if (flagSelection == 1) {
		DeleteTextArea *deleteArea = new DeleteTextArea();
		deleteArea->DeleteArea(this);
		if (deleteArea != 0) {
			delete deleteArea;
		}
	}
	WriteKoreanText *writeHanguel = new WriteKoreanText();
	writeHanguel->WriteHanguel(wParam, lParam, hIMC, this);
	if (writeHanguel != 0) {
		delete writeHanguel;
	}
	ImmReleaseContext(GetSafeHwnd(), hIMC);
	
	CWnd::HideCaret();
	::DestroyCaret();

	Invalidate();
	return 0;
}

void TextEdit::OnLButtonDown(UINT nFlags, CPoint point) {

	CPaintDC dc(this);
	MSG msg;
	UINT dblclkTime = GetDoubleClickTime();
	UINT elapseTime = 0;

	SetTimer(1, 1, NULL);
	while (elapseTime < dblclkTime) {
		PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
		if (msg.message == WM_LBUTTONDBLCLK || msg.message == WM_RBUTTONDBLCLK) {
			KillTimer(1);
		}
		elapseTime++;
	}

	CFont cFont;
	cFont.CreateFont(this->rowHeight, 0, 0, 0, this->fontSet->GetFontWeight(), FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, this->fontSet->GetFaceName().c_str());
	SetFont(&cFont, TRUE);
	CFont *oldFont = dc.SelectObject(&cFont); // 폰트 시작

	if (GetKeyState(VK_SHIFT) < 0) { // 클릭했는데 쉬프트가 눌려있을 때
		if (this->flagSelection == 0) { // flag 가 안눌려있으면
			this->flagSelection = 1; // flag 를 눌러준다
			this->selectedX = this->caret->GetCharacterIndex(); // selectedX, Y 를 기존 위치 캐럿 상단 좌표로 고정한다
			this->selectedY = this->caret->GetRowIndex();
		}
	}
	else {
		if (this->flagSelection == 1) { // 쉬프트 안눌려있는데 flag 가 눌려있으면 flag 취소해준다
			this->flagSelection = 0;
		}
	}
	this->caret->MoveToPoint(this, &dc, point); // 옮긴 위치로 캐럿을 이동시켜준다

	dc.SelectObject(oldFont);
	cFont.DeleteObject(); // 폰트 끝

	CWnd::HideCaret();
	::DestroyCaret();

	
	SetCapture();


	KillTimer(1);
	Invalidate();
}

void TextEdit::OnLButtonUp(UINT nFlags, CPoint point) {

	MSG msg;
	UINT dblclkTime = GetDoubleClickTime();
	UINT elapseTime = 0;
	PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
	if (msg.message == WM_LBUTTONDBLCLK || msg.message == WM_RBUTTONDBLCLK) {
		return;
	}

	CWnd::HideCaret();
	::DestroyCaret();

	KillTimer(1);
		ReleaseCapture();
		Invalidate();
	
}

void TextEdit::OnMouseMove(UINT nFlags, CPoint point) {
	//bool ret = IsOntheText(this, point);
	//SetCursor(LoadCursor(NULL, IDC_IBEAM));

	if (nFlags == MK_LBUTTON) {
		
		SetCursor(LoadCursor(NULL, IDC_IBEAM));
		CFont cFont;
		CPaintDC dc(this);
		cFont.CreateFont(this->rowHeight, 0, 0, 0, this->fontSet->GetFontWeight(), FALSE, FALSE, 0, DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, this->fontSet->GetFaceName().c_str());
		this->SetFont(&cFont, TRUE);
		CFont *oldFont = dc.SelectObject(&cFont);// 폰트 시작

		if (this->flagSelection == 0 && this->currentX != 0) {// && this->) { // 왼마우스 눌려있는데 이동시에 flag 진행중인지 확인해서
			this->flagSelection = 1; // flag 진행중 아니면 진행중으로 바꾸고
			this->selectedX = this->caret->GetCharacterIndex(); // 최초 한번 selectedX, Y 를
			this->selectedY = this->caret->GetRowIndex();
		}
			this->caret->MoveToPoint(this, &dc, point); // 새로운 위치로 캐럿 이동한다
	
		dc.SelectObject(oldFont);
		cFont.DeleteObject(); // 폰트 끝

		::DestroyCaret();
		Invalidate();
	}
	this->currentX = point.x;
}

void TextEdit::OnLButtonDblClk(UINT nFlags, CPoint point) {
	CPaintDC dc(this);

	DoubleClickTextArea *DoubleClick = new DoubleClickTextArea();
	DoubleClick->FindDoubleClickAreaIndex(this);
	if (DoubleClick != 0) {
		delete DoubleClick;
	}
	
	::DestroyCaret();
	Invalidate();
}

void TextEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	this->koreanEnglish = 1;

	KeyAction *keyAction = this->keyBoard->KeyDown(this, nChar, nRepCnt, nFlags);
	if (keyAction != 0) {
		keyAction->KeyPress(this);
	}
	this->koreanEnglish = 0;

	if (nChar != VK_RETURN && nChar != VK_ESCAPE) {
		CWnd::HideCaret();
		::DestroyCaret();

		CWnd::Invalidate();
	}
}

LRESULT TextEdit::OnIMENotify(WPARAM wParam, LPARAM lParam) {
	if (wParam == IMN_SETCONVERSIONMODE) {
		if (this->koreanEnglish == 0) {
			this->koreanEnglish = 1;
		}
		else {
			this->koreanEnglish = 0;
		}
	}
	return 0;
}

void TextEdit::OnKillFocus(CWnd *pNewWnd) {
	CWnd::OnKillFocus(pNewWnd);

	CWnd::HideCaret();
	::DestroyCaret();
	string content(this->text->MakeText());
	this->figure->ReplaceString(content);

	if (this->caret != NULL) {
		delete this->caret;
	}
	if (this->keyBoard != NULL) {
		delete this->keyBoard;
	}
	if (this->text != NULL) {
		delete this->text;
	}
	if (this->historyText != NULL) {
		delete this->historyText;
	}
	if (this->textAreaSelected != NULL) {
		delete this->textAreaSelected;
	}

	if (this != NULL) {
		delete this;
	}
}

void TextEdit::OnClose() {
	CWnd::HideCaret();
	::DestroyCaret();

	string content(this->text->MakeText());
	this->figure->ReplaceString(content);

	if (this->caret != NULL) {
		delete this->caret;
	}
	if (this->keyBoard != NULL) {
		delete this->keyBoard;
	}
	if (this->text != NULL) {
		delete this->text;
	}
	if (this->historyText != NULL) {
		delete this->historyText;
	}
	if (this->textAreaSelected != NULL) {
		delete this->textAreaSelected;
	}
	if (this != NULL) {
		delete this;
	}
}
	
