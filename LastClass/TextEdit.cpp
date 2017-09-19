//TextEdit.cpp

#pragma comment(lib,"imm32")

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
#include "WritingVisitor.h"   
#include <iostream>

BEGIN_MESSAGE_MAP(TextEdit, CFrameWnd)
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
	this->figure = figure;
	this->rowHeight = 18; // 폰트 사이즈
	this->koreanEnglish = 0;
	this->flagBuffer = 0;
	this->flagInsert = 0;
}

int TextEdit::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CFrameWnd::OnCreate(lpCreateStruct); //override

	this->text = new Text;
	this->caret = new Caret;
	this->keyBoard = new KeyBoard;

	ModifyStyle(WS_CAPTION, 0);
	//ModifyStyle(0, 0, SetWindowPos(&CWnd::wndTop, this->selectedY + 5, this->selectedY + 33, this->width - 5, this->height * 33, 0));

	this->text->SprayString(this->figure->GetContent()); // 넘겨받아온거 자료구조로 뿌려줌 ㅇㅇㅇㅇㅇ
	Invalidate();
	return 0;
}

//#include <gdiplus.h>
//using namespace Gdiplus;
void TextEdit::OnPaint() {
	CPaintDC dc(this);
	Long i = 0;
	WritingVisitor writingVisitor;

	CFont cFont;
	cFont.CreateFont(this->rowHeight, 0, 0, 0, FW_LIGHT, FALSE, FALSE, 0, DEFAULT_CHARSET,// 글꼴 설정
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "돋움체");
	SetFont(&cFont, TRUE);
	CFont *oldFont = dc.SelectObject(&cFont); // 폰트 시작

	this->text->Accept(writingVisitor, &dc);//받았던거 출력
	this->caret->MoveToIndex(this, &dc);
	
	if (this->flagInsert == 2) {
		dc.SetTextColor(RGB(255, 255, 255));
		dc.SetBkColor(RGB(0, 051, 255));
		//dc.SetBkMode(TRANSPARENT);//텍스트 배경을 투명하게 설정
		dc.SetBkMode(OPAQUE);//텍스트 배경을 SetBkColor 사용
		Long x = 0;
		while (i < this->selectedX) { // 현재줄에서 캐릭터인덱스까지 너비 구한다
			x += dc.GetTextExtent(this->text->GetAt(this->caret->GetRowIndex())->GetAt(i)->MakeCString()).cx;
			i++;
		}
		Long y = this->rowHeight*this->selectedY + 5;
		CRect rt;
		
		if (y == this->caret->GetCurrentCaretY()) {
			if (x < this->caret->GetCurrentCaretX()) {
				rt = { x + 5, y, this->caret->GetCurrentCaretX(), this->caret->GetCurrentCaretY() + this->rowHeight };
			}
			else {
				rt = { this->caret->GetCurrentCaretX() , this->caret->GetCurrentCaretY(), x + 5, y + this->rowHeight };
			}
		}
		else {
			if (y < this->caret->GetCurrentCaretY()) {
				rt = { x + 5, y, this->caret->GetCurrentCaretX(), this->caret->GetCurrentCaretY() + this->rowHeight };
			}
			else {
				rt = { this->caret->GetCurrentCaretX() ,  this->caret->GetCurrentCaretY(), x + 5, y + this->rowHeight };
			}
		}

		dc.DrawText((CString)text->MakeText().c_str(),&rt, DT_LEFT | DT_TOP | DT_EDITCONTROL | DT_EXPANDTABS);
	}
	dc.SelectObject(oldFont);
	cFont.DeleteObject(); // 폰트

}

void TextEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (this->koreanEnglish == 0 && nChar != VK_BACK && nChar != VK_ESCAPE && nChar != VK_RETURN &&
		nChar != VK_SPACE && nChar != VK_TAB && nChar != 10&&nChar!=VK_EXECUTE){
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
	Invalidate();
}

Long TextEdit::OnComposition(WPARAM wParam, LPARAM lParam) {
	HIMC hIMC = ImmGetContext(GetSafeHwnd());
	Long bufferLength;
	char buffer[8];
	Long i = 0;

	if (lParam & GCS_RESULTSTR) {
		bufferLength = ImmGetCompositionString(hIMC, GCS_RESULTSTR, NULL, 0);
		ImmGetCompositionString(hIMC, GCS_RESULTSTR, buffer, bufferLength);
		char(*tempChar) = new char[bufferLength];
		while (i < bufferLength) {
			tempChar[i] = buffer[i];
			i++;
		}
		DoubleByteCharacter doubleByteCharacter(tempChar);
		delete[] tempChar;

		this->text->GetAt(this->caret->GetRowIndex())->Modify(this->caret->GetCharacterIndex() - 1, doubleByteCharacter.Clone());
		this->flagBuffer = 0;
	}
	else if (lParam & GCS_COMPSTR) {
		bufferLength = ImmGetCompositionString(hIMC, GCS_COMPSTR, NULL, 0);
		ImmGetCompositionString(hIMC, GCS_COMPSTR, buffer, bufferLength);
		if (this->flagBuffer == 0) { // 조합중에서 시작일떄
			char(*tempChar) = new char[bufferLength];
			while (i < bufferLength) {
				tempChar[i] = buffer[i];
				i++;
			}
			DoubleByteCharacter doubleByteCharacter(tempChar);
			delete[] tempChar;

			if (this->caret->GetCharacterIndex() == this->text->GetAt(this->caret->GetRowIndex())->GetLength()) {
				this->text->GetAt(this->caret->GetRowIndex())->Add(doubleByteCharacter.Clone());
			}
			else if (this->caret->GetCharacterIndex() < this->text->GetAt(this->caret->GetRowIndex())->GetLength() && this->flagInsert == 0) {
				this->text->GetAt(this->caret->GetRowIndex())->Insert(this->caret->GetCharacterIndex(), doubleByteCharacter.Clone());
			}
			else if (this->caret->GetCharacterIndex() < this->text->GetAt(this->caret->GetRowIndex())->GetLength() && this->flagInsert == 1) {
				this->text->GetAt(this->caret->GetRowIndex())->Modify(this->caret->GetCharacterIndex(), doubleByteCharacter.Clone());
			}	
			this->caret->MoveForwardCharacterIndex();
			this->flagBuffer = 1;
		}
		else { // 조합중에서 조합중일때
			if (bufferLength > 0) {
				char(*tempChar) = new char[bufferLength];
				while (i < bufferLength) {
					tempChar[i] = buffer[i];
					i++;
				}
				DoubleByteCharacter doubleByteCharacter(tempChar);
				this->text->GetAt(this->caret->GetRowIndex())->Modify(this->caret->GetCharacterIndex() - 1, doubleByteCharacter.Clone());
				delete[] tempChar;
			}
			else if (bufferLength == 0) {
				this->text->GetAt(this->caret->GetRowIndex())->Remove(this->caret->GetCharacterIndex() - 1);
				this->caret->MoveBackwardCharacterIndex();
				this->flagBuffer = 0;
			}
		}
	}
	ImmReleaseContext(GetSafeHwnd(), hIMC);
	Invalidate();

	return 0;
}

void TextEdit::OnKillFocus(CWnd *pNewWnd) {

	this->OnClose();
}

void TextEdit::OnLButtonDown(UINT nFlags, CPoint point) {
	CPaintDC dc(this);

	CFont cFont;
	cFont.CreateFont(this->rowHeight, 0, 0, 0, FW_LIGHT, FALSE, FALSE, 0, DEFAULT_CHARSET,      // 글꼴 설정
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "돋움체");
	SetFont(&cFont, TRUE);
	CFont *oldFont = dc.SelectObject(&cFont); // 폰트 시작
	

	this->caret->MoveToPoint(this, &dc, point);

	dc.SelectObject(oldFont);
	cFont.DeleteObject(); // 폰트 끝

	Invalidate();
}


void TextEdit::OnLButtonUp(UINT nFlags, CPoint point) {

	Invalidate();
}

void TextEdit::OnMouseMove(UINT nFlags, CPoint point) {
	if (nFlags == MK_LBUTTON) {

		CFont cFont;
		CPaintDC dc(this);
		cFont.CreateFont(this->GetRowHeight(), 0, 0, 0, FW_LIGHT, FALSE, FALSE, 0, DEFAULT_CHARSET,      // 글꼴 설정
			OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "돋움체");
		this->SetFont(&cFont, TRUE);
		CFont *oldFont = dc.SelectObject(&cFont);// 폰트 시작

		this->caret->MoveToPoint(this, &dc, point);
	}
}

void TextEdit::OnLButtonDoubleClicked(UINT nFlags, CPoint point) {

}

void TextEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (nChar == VK_OEM_PLUS) {
		if (GetKeyState(VK_SHIFT) < 0) { //폰트 size
			this->rowHeight++;
			this->flagInsert = 2;
			this->selectedX = this->caret->GetCharacterIndex();
			this->selectedY = this->caret->GetRowIndex();
		}
	}
	if (nChar == VK_OEM_MINUS) {
		if (GetKeyState(VK_SHIFT) < 0) {
			this->rowHeight--;
			this->flagInsert = 0;
		}
	}
//	this->koreanEnglish = 0;
	this->keyBoard->KeyDown(this, nChar, nRepCnt, nFlags);
	Invalidate();
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

void TextEdit::OnClose() {
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

	CFrameWnd::OnClose();
}