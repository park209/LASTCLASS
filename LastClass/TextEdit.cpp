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
	this->caret = NULL;
	this->rowIndex = 0;
	this->characterIndex = 0;
	this->startX = 0;
	this->startY = 0;
	this->currentX = 0;
	this->currentY = 0;
	this->rowHeight = 17; // 폰트 사이즈
	this->koreanEnglish = 0;
	this->flagBuffer = 0;
	this->flagInsert = 0;
	this->keyBoard = NULL;
	this->text = NULL;
	this->figure = figure;
}

int TextEdit::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CFrameWnd::OnCreate(lpCreateStruct); //override

	this->keyBoard = new KeyBoard;
	this->caret = new Caret(5, 5, this);
	this->text = new Text;

	ModifyStyle(WS_CAPTION, 0);
	//ModifyStyle(0, 0, SetWindowPos(&CWnd::wndTop, this->startY + 5, this->startY + 33, this->width - 5, this->height * 33, 0));

	this->text->SprayString(this->figure->GetContent()); // 넘겨받아온거 자료구조로 뿌려줌 ㅇㅇㅇㅇㅇ
	if (this->text->GetLength() > 0) {
		this->rowIndex = this->text->GetLength() - 1;
		if (this->text->GetAt(this->text->GetLength() - 1)->GetLength() > 0) {
			this->characterIndex = this->text->GetAt(this->text->GetLength() - 1)->GetLength();
		}
	}

	Invalidate();
	return 0;
}

void TextEdit::OnPaint() {
	CPaintDC dc(this);
	Long i = 0;
	WritingVisitor writingVisitor;

	CFont m_font;
	m_font.CreateFont(this->rowHeight, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "돋움체");
	SetFont(&m_font, TRUE);
	CFont *oldFont = dc.SelectObject(&m_font);

	this->text->Accept(writingVisitor, &dc);// 받았던거 출력

	this->caret->MoveToIndex(this->characterIndex, this->rowIndex);

	dc.SelectObject(oldFont);
	m_font.DeleteObject();
}

void TextEdit::OnKillFocus(CWnd *pNewWnd) {

	this->OnClose();
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

		this->text->GetAt(rowIndex)->Modify(this->characterIndex - 1, doubleByteCharacter.Clone());
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

			if (this->characterIndex == this->text->GetAt(rowIndex)->GetLength()) {
				this->text->GetAt(rowIndex)->Add(doubleByteCharacter.Clone());
			}
			else if (this->characterIndex < this->text->GetAt(rowIndex)->GetLength() && this->flagInsert == 0) {
				this->text->GetAt(rowIndex)->Insert(this->characterIndex, doubleByteCharacter.Clone());
			}
			else if (this->characterIndex < this->text->GetAt(rowIndex)->GetLength() && this->flagInsert == 1) {
				this->text->GetAt(rowIndex)->Modify(this->characterIndex, doubleByteCharacter.Clone());
			}
			this->characterIndex++;
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
				this->text->GetAt(rowIndex)->Modify(this->characterIndex - 1, doubleByteCharacter.Clone());
				delete[] tempChar;
			}
			else if (bufferLength == 0) {
				this->text->GetAt(rowIndex)->Remove(this->characterIndex - 1);
				this->characterIndex--;
				this->flagBuffer = 0;
			}
		}
	}
	ImmReleaseContext(GetSafeHwnd(), hIMC);
	Invalidate();

	return 0;
}

void TextEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (this->koreanEnglish == 0 && nChar != VK_BACK && nChar != VK_ESCAPE && nChar != VK_RETURN &&
		nChar != VK_SPACE && nChar != VK_TAB) {
		char nCharacter = nChar;

		SingleByteCharacter singleByteCharacter(nCharacter);

		if (this->characterIndex == this->text->GetAt(rowIndex)->GetLength()) {
			this->text->GetAt(rowIndex)->Add(singleByteCharacter.Clone());
		}
		else if (this->characterIndex < this->text->GetAt(rowIndex)->GetLength() && this->flagInsert == 0) {
			this->text->GetAt(rowIndex)->Insert(this->characterIndex, singleByteCharacter.Clone());
		}
		else if (this->characterIndex < this->text->GetAt(rowIndex)->GetLength() && this->flagInsert == 1) {
			this->text->GetAt(rowIndex)->Modify(this->characterIndex, singleByteCharacter.Clone());
		}
		this->characterIndex++;
	}
	Invalidate();
}

void TextEdit::OnLButtonDown(UINT nFlags, CPoint point) {
	CPaintDC dc(this);
	this->startX = point.x;
	this->startY = point.y;
	/*Long height = 5;
	Long width = 5;
	this->rowIndex = 0;
	this->characterIndex = 0;*/

	/*if (startX > 5 && startY > 5) {
	while (height < this->startY && this->rowIndex < this->count) {
	this->rowIndex++;
	height += rowHeight;
	}
	if (this->text->GetLength() > 0) {
	this->rowIndex--;
	}

	while (width < this->startX && this->characterIndex < this->text->GetAt(this->GetCurrentClassIndex())->GetLength()) {
	width += dc.GetTabbedTextExtent(this->text->GetAt(this->GetCurrentClassIndex())->GetAt(this->characterIndex)->MakeCString(), 0, 0).cx;
	this->characterIndex++;
	}
	if (this->characterIndex <= this->text->GetAt(this->GetCurrentClassIndex())->GetLength() && this->classDiagramForm->text->GetAt(this->classDiagramForm->GetCurrentClassIndex())->GetLength() > 0 &&
	width - dc.GetTabbedTextExtent(this->text->GetAt(this->GetCurrentClassIndex())->GetAt(this->characterIndex - 1)->MakeCString(), 0, 0).cx / 2 > this->startX) {
	this->characterIndex--;
	}
	}*/
	this->caret->MoveToIndex(this->characterIndex, this->rowIndex);
	Invalidate();
}

void TextEdit::OnLButtonUp(UINT nFlags, CPoint point) {
	this->currentX = point.x;
	this->currentY = point.y;

	Invalidate();
}

void TextEdit::OnMouseMove(UINT nFlags, CPoint point) {
	if (nFlags == MK_LBUTTON) {
		CPaintDC dc(this);
		this->currentX = point.x;
		this->currentY = point.y;
		Long height = 5;
		Long width = 5;

		/*this->rowIndex = 0;
		this->characterIndex = 0;
		if (currentX > 5 && currentY > 5) {
		while (height < this->currentY && this->rowIndex < this->count) {
		this->rowIndex++;
		height += rowHeight;
		}
		if (this->classDiagramForm->text->GetLength() > 0) {
		this->rowIndex--;
		}

		while (width < this->currentX && this->characterIndex < this->classDiagramForm->text->GetAt(this->classDiagramForm->GetCurrentClassIndex())->GetLength()) {
		width += dc.GetTabbedTextExtent(this->classDiagramForm->text->GetAt(this->classDiagramForm->GetCurrentClassIndex())->GetAt(this->characterIndex)->MakeCString(), 0, 0).cx;
		this->characterIndex++;
		}
		if (this->characterIndex <= this->classDiagramForm->text->GetAt(rowIndex)->GetLength() && this->classDiagramForm->text->GetAt(rowIndex)->GetLength() > 0 &&
		width - dc.GetTabbedTextExtent(this->classDiagramForm->text->GetAt(this->classDiagramForm->GetCurrentClassIndex())->GetAt(this->characterIndex - 1)->MakeCString(), 0, 0).cx / 2 > this->startX) {
		this->characterIndex--;
		}
		}*/
		//Invalidate();
	}
}

void TextEdit::OnLButtonDoubleClicked(UINT nFlags, CPoint point) {

}

void TextEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (nChar == VK_OEM_PLUS) {
		if (GetKeyState(VK_SHIFT) < 0) { //폰트 size
			this->rowHeight++;
		}
	}
	if (nChar == VK_OEM_MINUS) {
		if (GetKeyState(VK_SHIFT) < 0) {
			this->rowHeight--;
		}
	}

	this->keyBoard->KeyDown(this, nChar, nRepCnt, nFlags);

	this->koreanEnglish = 0;

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