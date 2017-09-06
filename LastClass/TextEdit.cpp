//TextEdit.cpp
#pragma comment(lib,"imm32")

#include "TextEdit.h"
#include "Text.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include "WritingVisitor.h"

#include <iostream>
#include <fstream> //로드세이브할때


using namespace std;

BEGIN_MESSAGE_MAP(TextEdit, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_CHAR()
	ON_WM_KILLFOCUS()
	ON_MESSAGE(WM_IME_COMPOSITION, OnComposition)
	ON_WM_LBUTTONDOWN()
	//ON_WM_LBUTTONUP()
	ON_WM_KEYDOWN()
	ON_MESSAGE(WM_IME_NOTIFY, OnIMENotify)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

TextEdit::TextEdit(ClassDiagramForm *classDiagramForm, Long x, Long y, Long width, Long height) {
	this->classDiagramForm = classDiagramForm;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->rowIndex = 0;
	this->characterIndex = 0;
	this->koreanEnglish = 0;
	this->flagBuffer = 0;
}

int TextEdit::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CFrameWnd::OnCreate(lpCreateStruct); //override
	
	ModifyStyle(WS_CAPTION, 0);
	
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
		SetCaretPos(CPoint(dc.GetTabbedTextExtent((CString)this->classDiagramForm->text->GetAt(this->rowIndex)->PrintRowString().c_str(), 0, 0).cx + 5, 5));
	}
	ShowCaret();
	if (this->classDiagramForm->text->GetLength() > 0) {
		dc.TextOut(5, 5, (CString)this->classDiagramForm->text->GetAt(this->rowIndex)->PrintRowString().c_str());
	}
}

void TextEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (this->koreanEnglish == 0 && nChar != VK_BACK && nChar != VK_ESCAPE && nChar != VK_RETURN && nChar != VK_SPACE) {
		char nCharacter = nChar;

		if (this->classDiagramForm->text->GetLength() == 0) {
			Row newRow;
			this->classDiagramForm->text->Add(newRow.Clone());
		}
		SingleByteCharacter singleByteCharacter(nCharacter, 10, 5 + 10 * this->classDiagramForm->text->GetAt(0)->GetLength(), 5);
		if (this->characterIndex == this->classDiagramForm->text->GetAt(rowIndex)->GetLength()) {
			this->classDiagramForm->text->GetAt(rowIndex)->Add(singleByteCharacter.Clone());
		}
		else if (this->characterIndex < this->classDiagramForm->text->GetAt(rowIndex)->GetLength()) {
			this->classDiagramForm->text->GetAt(rowIndex)->Insert(this->characterIndex, singleByteCharacter.Clone());
		}
		this->characterIndex++;
	}
	Invalidate();
}

void TextEdit::OnKillFocus(CWnd *pNewWnd) {
	this->classDiagramForm->Invalidate();
	CFrameWnd::OnClose();
}

Long TextEdit::OnComposition(WPARAM wParam, LPARAM lParam) {
	HIMC hIMC = ImmGetContext(GetSafeHwnd());
	Long bufferLength;
	char buffer[8];
	Long i = 0;

	if (this->classDiagramForm->text->GetLength() == 0) { /////////////////////////// 왜 1/
		Row newRow;
		this->rowIndex = this->classDiagramForm->text->Add(newRow.Clone());
	}

	if (lParam & GCS_RESULTSTR) {
		bufferLength = ImmGetCompositionString(hIMC, GCS_RESULTSTR, NULL, 0);
		ImmGetCompositionString(hIMC, GCS_RESULTSTR, buffer, bufferLength);
		char(*tempChar) = new char[bufferLength];
		while (i < bufferLength) {
			tempChar[i] = buffer[i];
			i++;
		}
		DoubleByteCharacter doubleByteCharacter(tempChar, 5 + 20 * this->classDiagramForm->text->GetAt(0)->GetLength(), 10);
		this->classDiagramForm->text->GetAt(rowIndex)->Modify(this->characterIndex - 1, doubleByteCharacter.Clone());

		SetCaretPos(CPoint(characterIndex * 5, rowIndex * 10));
		ShowCaret();
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
			DoubleByteCharacter doubleByteCharacter(tempChar, 5 + 20 * this->classDiagramForm->text->GetAt(0)->GetLength(), 10);
			if (this->characterIndex == this->classDiagramForm->text->GetAt(rowIndex)->GetLength()) {
				this->classDiagramForm->text->GetAt(rowIndex)->Add(doubleByteCharacter.Clone());
			}
			else if (this->characterIndex < this->classDiagramForm->text->GetAt(rowIndex)->GetLength()) {
				this->classDiagramForm->text->GetAt(rowIndex)->Insert(this->characterIndex, doubleByteCharacter.Clone());
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
				DoubleByteCharacter doubleByteCharacter(tempChar, 5 + 20 * this->classDiagramForm->text->GetAt(0)->GetLength(), 10);
				this->classDiagramForm->text->GetAt(rowIndex)->Modify(this->characterIndex - 1, doubleByteCharacter.Clone());
			}
			else if(bufferLength == 0){
				this->classDiagramForm->text->GetAt(rowIndex)->Remove(this->characterIndex - 1);
				this->characterIndex--;
				this->flagBuffer = 0;
			}
		}
	}
	ImmReleaseContext(GetSafeHwnd(), hIMC);
	Invalidate();

	return 0;
}

void TextEdit::OnLButtonDown(UINT nFlags, CPoint point) {

	CFrameWnd::OnClose();
}

void TextEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Row *row = NULL;
	SingleByteCharacter spaceText;

	switch (nChar) {
	case VK_BACK:
		if (this->classDiagramForm->text->GetLength() > 0) {
			row = this->classDiagramForm->text->GetAt(this->rowIndex);
		}
		if (row != NULL&&this->characterIndex>0) {
			row->Remove(this->characterIndex-1);
			(this->characterIndex)--;
		}
		break;
		case VK_LEFT:
			this->characterIndex--;
			if (this->characterIndex <0){
				this->characterIndex = 0;
			}

			break;
		case VK_RIGHT:
			this->characterIndex++;
			if (this->characterIndex >this->classDiagramForm->text->GetAt(this->rowIndex)->GetLength()){
				this->characterIndex--;
			}
			break;
		case VK_DELETE:
			if (this->classDiagramForm->text->GetLength() > 0) {
				row = this->classDiagramForm->text->GetAt(this->rowIndex);
			}
			if (row != NULL && this->characterIndex < row->GetLength()) {
				row->Remove(this->characterIndex);
			}
			break;
		case VK_SPACE:
			if (this->classDiagramForm->text->GetLength() > 0) {
				row = this->classDiagramForm->text->GetAt(this->rowIndex);
			}
			row->Insert(this->characterIndex, spaceText.Clone());
			this->characterIndex++;
			break;
		case VK_RETURN: // 엔터
			this->rowIndex = this->classDiagramForm->text->InsertRow(rowIndex);
			while (this->classDiagramForm->text->GetAt(rowIndex - 1)->GetLength() > this->characterIndex) {
				Character *character = this->classDiagramForm->text->GetAt(rowIndex - 1)->GetAt(this->characterIndex);
				this->classDiagramForm->text->GetAt(rowIndex)->Add(character->Clone());
				this->classDiagramForm->text->GetAt(rowIndex - 1)->Remove(this->characterIndex);
			}
			this->characterIndex = 0;
	default:
		break;
	}
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
	//Save();

	CFrameWnd::OnClose();
}