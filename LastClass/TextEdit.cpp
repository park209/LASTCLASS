//TextEdit.cpp
#pragma comment(lib,"imm32")

#include "TextEdit.h"
#include "Text.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include "WritingVisitor.h"
#include "Caret.h"

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
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_KEYDOWN()
	ON_MESSAGE(WM_IME_NOTIFY, OnIMENotify)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

TextEdit::TextEdit(ClassDiagramForm *classDiagramForm, Long currentX, Long currentY, Long width, Long height) {
	this->classDiagramForm = classDiagramForm;
	this->caret = 0;
	this->width = width;
	this->height = height;
	this->rowIndex = 0;
	this->characterIndex = 0;
	this->currentX = currentX;
	this->currentY = currentY;
	this->indexes = NULL;
	this->count = 0;
	this->rowHeight = 20;
	this->koreanEnglish = 0;
	this->flagBuffer = 0;
	this->flagInsert = 0;
}

int TextEdit::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CFrameWnd::OnCreate(lpCreateStruct); //override
	this->caret = new Caret(5, 5, this);

	ModifyStyle(WS_CAPTION, 0);
	ModifyStyle(0, 0, SetWindowPos(&CWnd::wndTop, this->currentX + 3, this->currentY + 33, this->width - 5, this->height * 33, 0));

	CreateSolidCaret(3, 20); //rowHeight 가 오른쪽에 들어갈꺼임
	Long i = 0;
	CPaintDC dc(this);
	//this->classDiagramForm->text->Find(this->startX, this->startY, this->height, &(this->indexes), &(this->count));
	this->classDiagramForm->text->Find(this->currentX, this->currentY, this->startX, this->startY, this->height, this->rowHeight, &(this->indexes), &(this->count));

	if (this->count == 0) {
		Row row(this->currentX + 5, this->currentY + 5);
		i = this->classDiagramForm->text->Add(row.Clone());
	}

	/*while (i < count) {
		dc.TextOut(this->indexes[i]->GetX() + 5, this->indexes[i]->GetY() + 5, (CString)this->indexes[i]->PrintRowString().c_str());
		i++;
	}*/

	if (currentX > 5 && currentY > 5) {
		while (height < this->currentY && this->rowIndex < this->classDiagramForm->text->GetLength()) {
			this->rowIndex++;
			height += rowHeight;
		}
		if (this->classDiagramForm->text->GetLength() > 0) {
			this->rowIndex--;
		}

		while (width < this->currentX && this->characterIndex < this->classDiagramForm->text->GetAt(rowIndex)->GetLength()) {
			width += dc.GetTabbedTextExtent(this->classDiagramForm->text->GetAt(this->rowIndex)->GetAt(this->characterIndex)->MakeCString(), 0, 0).cx;
			this->characterIndex++;
		}
		if (this->characterIndex <= this->classDiagramForm->text->GetAt(rowIndex)->GetLength() && this->classDiagramForm->text->GetAt(rowIndex)->GetLength() > 0 &&
			width - dc.GetTabbedTextExtent(this->classDiagramForm->text->GetAt(this->rowIndex)->GetAt(this->characterIndex - 1)->MakeCString(), 0, 0).cx / 2 > this->currentX) {
			this->characterIndex--;
		}
	}
	this->caret->MoveToIndex(this->characterIndex, this->rowIndex);
	Invalidate();

	return 0;
}

void TextEdit::OnPaint() {
	CPaintDC dc(this);
	Long i = 0;
	Long j;
	Long caretX;

	//클래스 이름, 캐럿 출력
	if (this->classDiagramForm->text->GetLength() == 0) {
		Row newRow;
		this->classDiagramForm->text->Add(newRow.Clone());
	}

	/*while (i < this->classDiagramForm->text->GetLength() && this->classDiagramForm->text->GetLength() > 0) {
		j = 0;
		while (j < this->classDiagramForm->text->GetAt(i)->GetLength()) {
			dc.TextOut(5, 5 + i * dc.GetTabbedTextExtent((CString)this->classDiagramForm->text->GetAt(i)->PrintRowString().c_str(), 0, 0).cy,
				(CString)this->classDiagramForm->text->GetAt(i)->PrintRowString().c_str());
			j++;
		}
		i++;
	}*/

	while (i < count) {
	dc.TextOut(5, 5, (CString)this->indexes[i]->PrintRowString().c_str());
	i++;
	}

	this->caret->MoveToIndex(this->characterIndex, this->rowIndex);
}

void TextEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (this->koreanEnglish == 0 && nChar != VK_BACK && nChar != VK_ESCAPE && nChar != VK_RETURN && nChar != VK_SPACE && nChar != VK_TAB) {
		char nCharacter = nChar;

		if (this->classDiagramForm->text->GetLength() == 0) {
			Row newRow;
			this->classDiagramForm->text->Add(newRow.Clone());
		}
		SingleByteCharacter singleByteCharacter(nCharacter, 10, 5 + 10 * this->classDiagramForm->text->GetAt(rowIndex)->GetLength(), 5);
		
		if (this->characterIndex == this->classDiagramForm->text->GetAt(rowIndex)->GetLength()) {
			this->classDiagramForm->text->GetAt(rowIndex)->Add(singleByteCharacter.Clone());
		}
		else if (this->characterIndex < this->classDiagramForm->text->GetAt(rowIndex)->GetLength() && this->flagInsert == 0) {
			this->classDiagramForm->text->GetAt(rowIndex)->Insert(this->characterIndex, singleByteCharacter.Clone());
		}
		else if (this->characterIndex < this->classDiagramForm->text->GetAt(rowIndex)->GetLength() && this->flagInsert == 1) {
			this->classDiagramForm->text->GetAt(rowIndex)->Modify(this->characterIndex, singleByteCharacter.Clone());
		}
		this->characterIndex++;
	}
	Invalidate();
}

void TextEdit::OnKillFocus(CWnd *pNewWnd) {

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
		DoubleByteCharacter doubleByteCharacter(tempChar, 5 + 20 * this->classDiagramForm->text->GetAt(rowIndex)->GetLength(), 10);
		delete[] tempChar;

		this->classDiagramForm->text->GetAt(rowIndex)->Modify(this->characterIndex - 1, doubleByteCharacter.Clone());
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
			delete[] tempChar;
			
			if (this->characterIndex == this->classDiagramForm->text->GetAt(rowIndex)->GetLength()) {
				this->classDiagramForm->text->GetAt(rowIndex)->Add(doubleByteCharacter.Clone());
			}
			else if (this->characterIndex < this->classDiagramForm->text->GetAt(rowIndex)->GetLength() && this->flagInsert == 1) {
				this->classDiagramForm->text->GetAt(rowIndex)->Insert(this->characterIndex, doubleByteCharacter.Clone());
			}
			else if (this->characterIndex < this->classDiagramForm->text->GetAt(rowIndex)->GetLength() && this->flagInsert == 0) {
				this->classDiagramForm->text->GetAt(rowIndex)->Modify(this->characterIndex, doubleByteCharacter.Clone());
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
				delete[] tempChar;
			}
			else if (bufferLength == 0) {
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
	this->startX = point.x;
	this->startY = point.y;
}

void TextEdit::OnLButtonUp(UINT nFlags, CPoint point) {
	CPaintDC dc(this);
	this->currentX = point.x;
	this->currentY = point.y;
	Long height = 5;
	Long width = 5;
	this->rowIndex = 0;
	this->characterIndex = 0;

	if (currentX > 5 && currentY > 5) {
		while (height < this->currentY && this->rowIndex < this->classDiagramForm->text->GetLength()) {
			this->rowIndex++;
			height += rowHeight;
		}
		if (this->classDiagramForm->text->GetLength() > 0) {
			this->rowIndex--;
		}

		while (width < this->currentX && this->characterIndex < this->classDiagramForm->text->GetAt(rowIndex)->GetLength()) {
			width += dc.GetTabbedTextExtent(this->classDiagramForm->text->GetAt(this->rowIndex)->GetAt(this->characterIndex)->MakeCString(), 0, 0).cx;
			this->characterIndex++;
		}
		if (this->characterIndex <= this->classDiagramForm->text->GetAt(rowIndex)->GetLength() && this->classDiagramForm->text->GetAt(rowIndex)->GetLength() > 0 &&
			width - dc.GetTabbedTextExtent(this->classDiagramForm->text->GetAt(this->rowIndex)->GetAt(this->characterIndex - 1)->MakeCString(), 0, 0).cx / 2 > this->currentX) {
			this->characterIndex--;
		}
	}
	this->caret->MoveToIndex(this->characterIndex, this->rowIndex);
}

void OnLButtonDoubleClicked(UINT nFlags, CPoint point) {

}

void TextEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Row *row = NULL;

	this->koreanEnglish = 1;
	SingleByteCharacter spaceText(' ', 0, 0, 0);
	SingleByteCharacter tapText('\t', 0, 0, 0);

	if (this->classDiagramForm->text->GetLength() > 0) {
		row = this->classDiagramForm->text->GetAt(this->rowIndex);
	}

	switch (nChar) {
	case VK_BACK: // 백스페이스
		if (row != NULL&&this->characterIndex > 0) {
			row->Remove(this->characterIndex - 1);
			(this->characterIndex)--;
		}
		break;
	case VK_LEFT:
		this->characterIndex--;
		if (this->characterIndex < 0) {
			this->characterIndex = 0;
		}
		break;
	case VK_RIGHT:
		this->characterIndex++;
		if (this->characterIndex > this->classDiagramForm->text->GetAt(this->rowIndex)->GetLength()) {
			this->characterIndex--;
		}
		break;
	case VK_DELETE:
		if (row != NULL && this->characterIndex < row->GetLength()) {
			row->Remove(this->characterIndex);
		}
		break;
	case VK_SPACE:
		row->Insert(this->characterIndex, spaceText.Clone());
		this->characterIndex++;
		break;
	case VK_RETURN: // 컨트롤 엔터
		if (GetKeyState(VK_CONTROL) < 0) {
			this->rowIndex = this->classDiagramForm->text->InsertRow(rowIndex);
			while (this->classDiagramForm->text->GetAt(rowIndex - 1)->GetLength() > this->characterIndex) {
				Character *character = this->classDiagramForm->text->GetAt(rowIndex - 1)->GetAt(this->characterIndex);
				this->classDiagramForm->text->GetAt(rowIndex)->Add(character->Clone());
				this->classDiagramForm->text->GetAt(rowIndex - 1)->Remove(this->characterIndex);
			}
			this->characterIndex = 0;
		}
		break;
	case VK_HOME:
		this->characterIndex = 0; break;
	case VK_END:
		if (this->classDiagramForm->text->GetLength() > 0) {
			this->characterIndex = this->classDiagramForm->text->GetAt(this->rowIndex)->GetLength();
		}
		break;
	case VK_INSERT:
		if (flagInsert == 1) {
			this->flagInsert = 0;
		}
		else {
			this->flagInsert = 1;
		}
		break;
	case VK_TAB:
		if (this->characterIndex < this->classDiagramForm->text->GetAt(rowIndex)->GetLength()) {
			row->Insert(this->characterIndex, tapText.Clone());
		}
		else {
			row->Add(tapText.Clone());
		}
		this->characterIndex++;
		break;
	default: this->koreanEnglish = 0;
		break;
	}
	Invalidate();

	if (nChar == VK_ESCAPE) { // ESC 키
		CFrameWnd::OnClose();
	}
	if (nChar == VK_RETURN) { // 엔터
		if (GetKeyState(VK_CONTROL) >= 0) {
			CFrameWnd::OnClose();
		}
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

void TextEdit::OnClose() {
	//Save();
	if (this->classDiagramForm->textEdit != NULL) {
		delete this->classDiagramForm->textEdit;
	}
	CFrameWnd::OnClose();
}