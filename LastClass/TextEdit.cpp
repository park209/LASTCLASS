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
	this->rowHeight = 18; // ��Ʈ ������
	this->koreanEnglish = 0;
	this->flagBuffer = 0;
	this->flagInsert = 0;
	this->flagSelection = 0;
	this->currentX = 0;
}

int TextEdit::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CFrameWnd::OnCreate(lpCreateStruct); //override

	this->text = new Text;
	this->caret = new Caret;
	this->keyBoard = new KeyBoard;

	ModifyStyle(WS_CAPTION, 0);
	//ModifyStyle(0, 0, SetWindowPos(&CWnd::wndTop, this->selectedY + 5, this->selectedY + 33, this->width - 5, this->height * 33, 0));

	this->text->SprayString(this->figure->GetContent()); // �Ѱܹ޾ƿ°� �ڷᱸ���� �ѷ��� ����������

	Invalidate();
	return 0;
}

void TextEdit::OnPaint() {
	CPaintDC dc(this);
	WritingVisitor writingVisitor;

	CFont cFont;
	cFont.CreateFont(this->rowHeight, 0, 0, 0, FW_LIGHT, FALSE, FALSE, 0, DEFAULT_CHARSET,// �۲� ����
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "����ü");
	SetFont(&cFont, TRUE);
	CFont *oldFont = dc.SelectObject(&cFont); // ��Ʈ ����

	this->text->Accept(writingVisitor, &dc);//�޾Ҵ��� ���
	this->caret->MoveToIndex(this, &dc);

	dc.SetTextColor(RGB(255, 255, 255));
	dc.SetBkColor(RGB(0, 100, 255));
	//dc.SetBkMode(TRANSPARENT);//�ؽ�Ʈ ����� �����ϰ� ����
	dc.SetBkMode(OPAQUE);//�ؽ�Ʈ ����� SetBkColor ���

	if (this->flagSelection == 1) { // flagSelection�� ����������
		CRect rect;
		Long startCharacterIndex = 0;
		Long startRowIndex = 0;
		Long endCharacterIndex = 0;
		Long endRowIndex = 0;
		Long i;
		Long j;
		Long x;
		Long width = 0;
		CString copyBuffer;

		CString cString1;
		if (this->selectedY == this->caret->GetRowIndex()) {
			if (this->selectedX < this->caret->GetCharacterIndex()) {
				startCharacterIndex = this->selectedX;
				startRowIndex = this->selectedY;
				endCharacterIndex = this->caret->GetCharacterIndex();
				endRowIndex = this->caret->GetRowIndex();
			}
			else {
				startCharacterIndex = this->caret->GetCharacterIndex();
				startRowIndex = this->caret->GetRowIndex();
				endCharacterIndex = this->selectedX;
				endRowIndex = this->selectedY;
			}
			width = 0;
			i = startCharacterIndex;
			while (i < endCharacterIndex) { // ù��
				cString1 += this->text->GetAt(startRowIndex)->GetAt(i)->MakeCString();
				width += dc.GetTextExtent(this->text->GetAt(startRowIndex)->GetAt(i)->MakeCString()).cx;
				i++;
			}
			x = 5;
			i = 0;
			while (i < startCharacterIndex) { // �����ٿ��� ĳ�����ε������� �ʺ� ���Ѵ�
				x += dc.GetTextExtent(this->text->GetAt(startRowIndex)->GetAt(i)->MakeCString()).cx;
				i++;
			}
			rect = { x, startRowIndex * this->rowHeight + 5, x + width, startRowIndex * this->rowHeight + this->rowHeight + 5 };
			dc.DrawText(cString1, rect, DT_EDITCONTROL | DT_EXPANDTABS);

			copyBuffer = cString1;
		}
		else {
			if (this->selectedY < this->caret->GetRowIndex()) {
				startCharacterIndex = this->selectedX;
				startRowIndex = this->selectedY;
				endCharacterIndex = this->caret->GetCharacterIndex();
				endRowIndex = this->caret->GetRowIndex();
			}
			else {
				startCharacterIndex = this->caret->GetCharacterIndex();
				startRowIndex = this->caret->GetRowIndex();
				endCharacterIndex = this->selectedX;
				endRowIndex = this->selectedY;
			}
			width = 0;
			i = startCharacterIndex;
			while (i < this->text->GetAt(startRowIndex)->GetLength()) { // ù��
				cString1 += this->text->GetAt(startRowIndex)->GetAt(i)->MakeCString();
				width += dc.GetTextExtent(this->text->GetAt(startRowIndex)->GetAt(i)->MakeCString()).cx;
				i++;
			}
			cString1 += "\r\n";
			x = 5;
			i = 0;
			while (i < startCharacterIndex) { // �����ٿ��� ĳ�����ε������� �ʺ� ���Ѵ�
				x += dc.GetTextExtent(this->text->GetAt(startRowIndex)->GetAt(i)->MakeCString()).cx;
				i++;
			}
			rect = { x, startRowIndex * this->rowHeight + 5, x + width, startRowIndex * this->rowHeight + this->rowHeight + 5 };
			dc.DrawText(cString1, rect, DT_EDITCONTROL | DT_EXPANDTABS);

			string string2; // �߰�
			if (startRowIndex + 1 < endRowIndex) {
				i = startRowIndex + 1;
				while (i < endRowIndex) {
					string2 += this->text->GetAt(i)->PrintRowString().c_str();
					string2 += "\r\n";
					i++;
				}
				x = 5;
				rect = { x, (startRowIndex + 1) * this->rowHeight + 5, 1000, (endRowIndex - 1) * this->rowHeight + this->rowHeight + 5 };
				dc.DrawText(string2.c_str(), rect, DT_EDITCONTROL | DT_EXPANDTABS);
			}

			CString cString3;
			width = 0;
			i = 0;
			while (i < endCharacterIndex) { // ù��
				cString3 += this->text->GetAt(endRowIndex)->GetAt(i)->MakeCString();
				width += dc.GetTextExtent(this->text->GetAt(endRowIndex)->GetAt(i)->MakeCString()).cx;
				i++;
			}
			x = 5;
			i = 0;
			rect = { x, endRowIndex * this->rowHeight + 5, x + width, endRowIndex * this->rowHeight + this->rowHeight + 5 };
			dc.DrawText(cString3, rect, DT_EDITCONTROL | DT_EXPANDTABS);

			copyBuffer = cString1 + string2.c_str() + cString3; // Ŭ�����忡 ����
		}
		////////////////////
		//ctrl+c���
		//////////////////////
		OpenClipboard();
		EmptyClipboard();
		size_t cbstr = (copyBuffer.GetLength() + 1) * sizeof(TCHAR);
		HGLOBAL h = GlobalAlloc(GMEM_MOVEABLE, cbstr);
		memcpy_s(GlobalLock(h), cbstr, copyBuffer.LockBuffer(), cbstr);
		GlobalUnlock(h);
		copyBuffer.UnlockBuffer();
		UINT uniFormat = (sizeof(TCHAR) == sizeof(WCHAR)) ? CF_UNICODETEXT : CF_TEXT;
		if (::SetClipboardData(uniFormat, h) == NULL) {
		}
		CloseClipboard();
		///////////////////////////
		//
		//////////////////////////
	}
	dc.SelectObject(oldFont);
	cFont.DeleteObject(); // ��Ʈ
}

//void TextEdit::OnPaint() {
//	CPaintDC dc(this);
//	Long i = 0;
//	WritingVisitor writingVisitor;
//
//	CFont cFont;
//	cFont.CreateFont(this->rowHeight, 0, 0, 0, FW_LIGHT, FALSE, FALSE, 0, DEFAULT_CHARSET,// �۲� ����
//		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "����ü");
//	SetFont(&cFont, TRUE);
//	CFont *oldFont = dc.SelectObject(&cFont); // ��Ʈ ����
//
//	this->text->Accept(writingVisitor, &dc);//�޾Ҵ��� ���
//	this->caret->MoveToIndex(this, &dc);
//
//	if (this->flagSelection == 1) {
//		dc.SetTextColor(RGB(255, 255, 255));
//		dc.SetBkColor(RGB(0, 100, 255));
//		//dc.SetBkMode(TRANSPARENT);//�ؽ�Ʈ ����� �����ϰ� ����
//		dc.SetBkMode(OPAQUE);//�ؽ�Ʈ ����� SetBkColor ���
//		Long x = 0;
//		//   while (i < this->selectedX) { // �����ٿ��� ĳ�����ε������� �ʺ� ���Ѵ�
//		//      x += dc.GetTextExtent(this->text->GetAt(this->caret->GetRowIndex())->GetAt(i)->MakeCString()).cx;
//		//      i++;
//		//   }
//		Long y = 0;
//		CRect rt;
//		Long startCI = 0;
//		Long startRI = 0;
//		Long endCI = 0;
//		Long endRI = 0;
//		CString rows;
//		if (this->selectedY == this->caret->GetRowIndex()) {
//			if (this->selectedX < this->caret->GetCharacterIndex()) {
//				//   rt = { x + 5, y, this->caret->GetCurrentCaretX(), this->caret->GetCurrentCaretY() + this->rowHeight };
//				startCI = this->selectedX;
//				startRI = this->selectedY;
//				endCI = this->caret->GetCharacterIndex();
//				endRI = this->caret->GetRowIndex();
//			}
//			else {
//				//   rt = { this->caret->GetCurrentCaretX() , this->caret->GetCurrentCaretY(), x + 5, y + this->rowHeight };
//				startCI = this->caret->GetCharacterIndex();
//				startRI = this->caret->GetRowIndex();
//				endCI = this->selectedX;
//				endRI = this->selectedY;
//			}
//		}
//		else {
//			if (this->selectedY < this->caret->GetRowIndex()) {
//				//   rt = { x + 5, y, this->caret->GetCurrentCaretX(), this->caret->GetCurrentCaretY() + this->rowHeight };
//				startCI = this->selectedX;
//				startRI = this->selectedY;
//				endCI = this->caret->GetCharacterIndex();
//				endRI = this->caret->GetRowIndex();
//			}
//			else {
//				//   rt = { this->caret->GetCurrentCaretX() ,  this->caret->GetCurrentCaretY(), x + 5, y + this->rowHeight };
//				startCI = this->caret->GetCharacterIndex();
//				startRI = this->caret->GetRowIndex();
//				endCI = this->selectedX;
//				endRI = this->selectedY;
//			}
//		}
//		Long j = 0;
//		CString text;
//		while (startRI < endRI) {
//			while (startCI + j < this->text->GetAt(startRI)->GetLength()) {
//				rows.Append(this->text->GetAt(startRI)->GetAt(startCI + j)->MakeCString());
//				j++;
//			}
//			while (i < startCI) { // �����ٿ��� ĳ�����ε������� �ʺ� ���Ѵ�
//				x += dc.GetTextExtent(this->text->GetAt(startRI)->GetAt(i)->MakeCString()).cx;
//				i++;
//			}
//			y = this->rowHeight*startRI + 5;
//			rt = { x + 5,y,x + 5 + dc.GetTextExtent(rows).cx,y + this->rowHeight };
//			dc.DrawText(rows, &rt, DT_LEFT | DT_TOP | DT_EDITCONTROL | DT_EXPANDTABS);
//			text.Append(rows);
//			text.Append("\r\n");
//			rows = "";
//			startCI = 0;
//			j = 0;
//			x = 0;
//
//			startRI++;
//		}
//		while (startCI + j < endCI) {
//			while (startCI + j < endCI) {
//				rows.Append(this->text->GetAt(startRI)->GetAt(startCI + j)->MakeCString());
//				j++;
//			}
//			while (i < startCI) { // �����ٿ��� ĳ�����ε������� �ʺ� ���Ѵ�
//				x += dc.GetTextExtent(this->text->GetAt(startRI)->GetAt(i)->MakeCString()).cx;
//				i++;
//			}
//			y = this->rowHeight*startRI + 5;
//			rt = { x + 5,y,x + 5 + dc.GetTextExtent(rows).cx,y + this->rowHeight };
//			dc.DrawText(rows, &rt, DT_LEFT | DT_TOP | DT_EDITCONTROL | DT_EXPANDTABS);
//			text.Append(rows);
//		}
//		//////////////////////
//		//ctrl+c���
//		//////////////////////
//		OpenClipboard();
//		EmptyClipboard();
//		size_t cbstr = (text.GetLength() + 1) * sizeof(TCHAR);
//		HGLOBAL h = GlobalAlloc(GMEM_MOVEABLE, cbstr);
//		memcpy_s(GlobalLock(h), cbstr, text.LockBuffer(), cbstr);
//		GlobalUnlock(h);
//		text.UnlockBuffer();
//		UINT uniFormat = (sizeof(TCHAR) == sizeof(WCHAR)) ? CF_UNICODETEXT : CF_TEXT;
//		if (::SetClipboardData(uniFormat, h) == NULL) {
//		}
//		CloseClipboard();
//		///////////////////////////
//		//
//		//////////////////////////
//	}
//	//dc.DrawText((CString)text->MakeText().c_str(),&rt, DT_LEFT | DT_TOP | DT_EDITCONTROL | DT_EXPANDTABS);
//	dc.SelectObject(oldFont);
//	cFont.DeleteObject(); // ��Ʈ
//}

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
		if (this->flagBuffer == 0) { // �����߿��� �����ϋ�
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
		else { // �����߿��� �������϶�
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
	cFont.CreateFont(this->rowHeight, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,      // �۲� ����
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "����ü");
	SetFont(&cFont, TRUE);
	CFont *oldFont = dc.SelectObject(&cFont); // ��Ʈ ����

	if (GetKeyState(VK_SHIFT) < 0) { // Ŭ���ߴµ� ����Ʈ�� �������� ��
		if (this->flagSelection == 0) { // flag �� �ȴ���������
			this->flagSelection = 1; // flag �� �����ش�
			this->selectedX = this->caret->GetCharacterIndex(); // selectedX, Y �� ���� ��ġ ĳ�� ��� ��ǥ�� �����Ѵ�
			this->selectedY = this->caret->GetRowIndex();
		}
	}
	else {
		if (this->flagSelection == 1) { // ����Ʈ �ȴ����ִµ� flag �� ���������� flag ������ش�
			this->flagSelection = 0;
		}
	}
	this->caret->MoveToPoint(this, &dc, point); // �ű� ��ġ�� ĳ���� �̵������ش�

	dc.SelectObject(oldFont);
	cFont.DeleteObject(); // ��Ʈ ��

	Invalidate();
}

void TextEdit::OnLButtonUp(UINT nFlags, CPoint point) {

	Invalidate();
}

void TextEdit::OnMouseMove(UINT nFlags, CPoint point) {
	if (nFlags == MK_LBUTTON) {

		CFont cFont;
		CPaintDC dc(this);
		cFont.CreateFont(this->GetRowHeight(), 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,      // �۲� ����
			OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "����ü");
		this->SetFont(&cFont, TRUE);
		CFont *oldFont = dc.SelectObject(&cFont);// ��Ʈ ����

		if (this->flagSelection == 0 && this->currentX != 0) {// && this->) { // �޸��콺 �����ִµ� �̵��ÿ� flag ���������� Ȯ���ؼ�
			this->flagSelection = 1; // flag ������ �ƴϸ� ���������� �ٲٰ�
			this->selectedX = this->caret->GetCharacterIndex(); // ���� �ѹ� selectedX, Y ��
			this->selectedY = this->caret->GetRowIndex();
		}
		this->caret->MoveToPoint(this, &dc, point); // ���ο� ��ġ�� ĳ�� �̵��Ѵ�

		dc.SelectObject(oldFont);
		cFont.DeleteObject(); // ��Ʈ ��

		Invalidate();
	}
	this->currentX = point.x;
}

void TextEdit::OnLButtonDoubleClicked(UINT nFlags, CPoint point) {
	
}

void TextEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (nChar == VK_OEM_PLUS) {
		if (GetKeyState(VK_SHIFT) < 0) { //��Ʈ size
			this->rowHeight++;
		}
	}
	if (nChar == VK_OEM_MINUS) {
		if (GetKeyState(VK_SHIFT) < 0) {
			this->rowHeight--;
		}
	}

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

