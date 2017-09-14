//TextEdit.cpp
#pragma comment(lib,"imm32")

#include "TextEdit.h"
#include "Text.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include "WritingVisitor.h"
#include "Caret.h"
#include "KeyBoard.h"
#include "Diagram.h"
#include "Figure.h"

#include <iostream>
#include <fstream> //�ε弼�̺��Ҷ�

using namespace std;

BEGIN_MESSAGE_MAP(TextEdit, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_CHAR()
	ON_WM_KILLFOCUS()
	ON_MESSAGE(WM_IME_COMPOSITION, OnComposition)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_KEYDOWN()
	ON_MESSAGE(WM_IME_NOTIFY, OnIMENotify)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

TextEdit::TextEdit(Figure *content) {
	this->caret = 0;
	this->rowIndex = 0;
	this->characterIndex = 0;
	this->startX = 0;
	this->startY = 0;
	this->currentX = 0;
	this->currentY = 0;
	this->count = 0;
	this->rowHeight = 20;
	this->koreanEnglish = 0;
	this->flagBuffer = 0;
	this->flagInsert = 0;
	this->keyBoard = NULL;
	this->text = NULL;
	this->content = content;
}

int TextEdit::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CFrameWnd::OnCreate(lpCreateStruct); //override
	this->keyBoard = new KeyBoard;
	this->caret = new Caret(5, 5, this);
	this->text = new Text;
	CPaintDC dc(this);
	Long i = 0;

	ModifyStyle(WS_CAPTION, 0);
	//ModifyStyle(0, 0, SetWindowPos(&CWnd::wndTop, this->startY + 5, this->startY + 33, this->width - 5, this->height * 33, 0));

	this->text->SprayString(this->content->GetContent());

	Invalidate();

	return 0;
}

void TextEdit::OnPaint() {
	CPaintDC dc(this);
	Long i = 0;

	this->count = 0;

	WritingVisitor writingVisitor;
	this->text->Accept(writingVisitor, &dc);

	this->caret->MoveToIndex(this->characterIndex, this->rowIndex);
}

void TextEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (this->koreanEnglish == 0 && nChar != VK_BACK && nChar != VK_ESCAPE && nChar != VK_RETURN && nChar != VK_SPACE && nChar != VK_TAB) {
		char nCharacter = nChar;
		
		SingleByteCharacter singleByteCharacter(nCharacter);

		//ClassDiagramForm classDiagramForm = FindWindow(NULL, "classDiagram");
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

void TextEdit::OnKillFocus(CWnd *pNewWnd) {

	CFrameWnd::OnClose();
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
		if (this->flagBuffer == 0) { // �����߿��� �����ϋ�
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
		else { // �����߿��� �������϶�
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

void TextEdit::OnLButtonDown(UINT nFlags, CPoint point) {
	CPaintDC dc(this);
	this->startX = point.x;
	this->startY = point.y;
	Long height = 5;
	Long width = 5;
	this->rowIndex = 0;
	this->characterIndex = 0;

	if (startX > 5 && startY > 5) {
		while (height < this->startY && this->rowIndex < this->count) {
			this->rowIndex++;
			height += rowHeight;
		}
		if (this->text->GetLength() > 0) {
			this->rowIndex--;
		}

		/*while (width < this->startX && this->characterIndex < this->text->GetAt(this->GetCurrentClassIndex())->GetLength()) {
			width += dc.GetTabbedTextExtent(this->text->GetAt(this->GetCurrentClassIndex())->GetAt(this->characterIndex)->MakeCString(), 0, 0).cx;
			this->characterIndex++;
		}
		if (this->characterIndex <= this->text->GetAt(this->GetCurrentClassIndex())->GetLength() && this->classDiagramForm->text->GetAt(this->classDiagramForm->GetCurrentClassIndex())->GetLength() > 0 &&
			width - dc.GetTabbedTextExtent(this->text->GetAt(this->GetCurrentClassIndex())->GetAt(this->characterIndex - 1)->MakeCString(), 0, 0).cx / 2 > this->startX) {
			this->characterIndex--;
		}*/
	}
	//this->caret->MoveToIndex(this->characterIndex, this->rowIndex);
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
	this->koreanEnglish = 1;

	this->keyBoard->KeyDown(this, nChar, nRepCnt, nFlags);

	//Row *row = NULL;
	//this->koreanEnglish = 1;
	//SingleByteCharacter spaceText(' ', 0, 0, 0);
	//SingleByteCharacter tapText('\t', 0, 0, 0);

	//switch (nChar) {
	//case VK_TAB:
	//   if (this->characterIndex < this->classDiagramForm->text->GetAt(rowIndex)->GetLength()) {
	//      row->Insert(this->characterIndex, tapText.Clone());
	//   }
	//   else {
	//      row->Add(tapText.Clone());
	//   }
	//   this->characterIndex++;
	//   break;
	//default: this->koreanEnglish = 0;
	//   break;
	//}
	this->koreanEnglish = 0;

	Invalidate();

	//if (nChar == VK_ESCAPE) { // ESC Ű
	//   CFrameWnd::OnClose();
	//}
	//if (nChar == VK_RETURN) { // ����
	//   if (GetKeyState(VK_CONTROL) >= 0) {
	//      CFrameWnd::OnClose();
	//   }
	//}
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
	string content = this->text->MakeText();
	this->content->ReplaceString(content);

	if (this->caret != NULL) {
		delete this->caret;
	}
	if (this->keyBoard != NULL) {
		delete this->keyBoard;
	}

	CFrameWnd::OnClose();
}