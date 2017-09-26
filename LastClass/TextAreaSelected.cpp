//TextAreaSelected.cpp

#include "TextAreaSelected.h"
#include "TextEdit.h"
#include "Caret.h"
#include "Text.h"
#include "Row.h"
#include "Character.h"
#include "Figure.h"

TextAreaSelected::TextAreaSelected() {
}
TextAreaSelected::TextAreaSelected(const TextAreaSelected& source) {
}
TextAreaSelected::~TextAreaSelected() {
}

void TextAreaSelected::SelectTextArea(TextEdit *textEdit, CPaintDC *dc) {
	CRect rect;
	this->startCharacterIndex = 0;
	this->startRowIndex = 0;
	this->endCharacterIndex = 0;
	this->endRowIndex = 0;
	Long i;
	Long x;
	Long width = 0;
	CString str;

	CFont cFont;
	cFont.CreateFont(textEdit->GetRowHeight(), 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,// 글꼴 설정
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "맑은 고딕");
	textEdit->SetFont(&cFont, TRUE);
	CFont *oldFont = dc->SelectObject(&cFont);

	//CDC memDC;
	//CBitmap *pOldBitmap;
	//CBitmap bitmap;

	//memDC.CreateCompatibleDC(dc);
	//bitmap.CreateCompatibleBitmap(dc, textEdit->GetFigure()->GetWidth(), textEdit->GetFigure()->GetHeight());
	//pOldBitmap = memDC.SelectObject(&bitmap);

	//memDC.FillSolidRect(CRect(0, 0, textEdit->GetFigure()->GetWidth(), textEdit->GetFigure()->GetHeight()), RGB(255, 255, 255));
	//memDC.SelectObject(cFont);

	//memDC.SetTextColor(RGB(255, 255, 255));
	//memDC.SetBkColor(RGB(51, 153, 255));
	//memDC.SetBkMode(OPAQUE);//텍스트 배경을 SetBkColor 사용


	CString cString1;
	if (textEdit->selectedY == textEdit->caret->GetRowIndex()) { // 한줄에서 끝나는거면
		if (textEdit->selectedX < textEdit->caret->GetCharacterIndex()) {
			this->startCharacterIndex = textEdit->selectedX;
			this->startRowIndex = textEdit->selectedY;
			this->endCharacterIndex = textEdit->caret->GetCharacterIndex();
			this->endRowIndex = textEdit->caret->GetRowIndex();
		}
		else {
			this->startCharacterIndex = textEdit->caret->GetCharacterIndex();
			this->startRowIndex = textEdit->caret->GetRowIndex();
			this->endCharacterIndex = textEdit->selectedX;
			this->endRowIndex = textEdit->selectedY;
		}
		width = 0;
		i = startCharacterIndex;
		while (i < endCharacterIndex) { // 첫줄
			cString1 += textEdit->text->GetAt(startRowIndex)->GetAt(i)->MakeCString();
			str = textEdit->text->GetAt(startRowIndex)->GetAt(i)->MakeCString();
			if (str == "\t") {
				str = "        ";
			}
			width += dc->GetTextExtent(str).cx;
			i++;
		}
		x = 5;
		i = 0;
		while (i < startCharacterIndex) { // 현재줄에서 캐릭터인덱스까지 너비 구한다
			str = textEdit->text->GetAt(startRowIndex)->GetAt(i)->MakeCString();
			if (str == "\t") {
				str = "        ";
			}
			x += dc->GetTextExtent(str).cx;
			i++;
		}
		rect = { x, startRowIndex * textEdit->rowHeight + 5, x + width, startRowIndex * textEdit->rowHeight + textEdit->rowHeight + 5 };		 
		dc->DrawText(cString1, rect, DT_EXPANDTABS | DT_TABSTOP | 0x0800);
		//rect = { 0, 0, x + width, startRowIndex * textEdit->rowHeight + textEdit->rowHeight +5 };
		//memDC.DrawText(cString1, rect, DT_EXPANDTABS | DT_TABSTOP | 0x0800);
		//dc->BitBlt(x, startRowIndex * textEdit->rowHeight+5, x + width-32, startRowIndex * textEdit->rowHeight + textEdit->rowHeight+5, &memDC, 0, 0, SRCCOPY);

		textEdit->copyBuffer = cString1;
	}
	else { // 여러줄 선택이면
		if (textEdit->selectedY < textEdit->caret->GetRowIndex()) {
			this->startCharacterIndex = textEdit->selectedX;
			this->startRowIndex = textEdit->selectedY;
			this->endCharacterIndex = textEdit->caret->GetCharacterIndex();
			this->endRowIndex = textEdit->caret->GetRowIndex();
		}
		else {
			this->startCharacterIndex = textEdit->caret->GetCharacterIndex();
			this->startRowIndex = textEdit->caret->GetRowIndex();
			this->endCharacterIndex = textEdit->selectedX;
			this->endRowIndex = textEdit->selectedY;
		}
		width = 0;
		i = startCharacterIndex;
		while (i < textEdit->text->GetAt(this->startRowIndex)->GetLength()) { // 첫줄
			cString1 += textEdit->text->GetAt(this->startRowIndex)->GetAt(i)->MakeCString();
			str = textEdit->text->GetAt(this->startRowIndex)->GetAt(i)->MakeCString();
			if (str == "\t") {
				str = "        ";
			}
			width += dc->GetTextExtent(str).cx;
			i++;
		}
		cString1 += "\r\n";
		x = 5;
		i = 0;
		while (i < this->startCharacterIndex) { // 현재줄에서 캐릭터인덱스까지 너비 구한다
			str = textEdit->text->GetAt(this->startRowIndex)->GetAt(i)->MakeCString();
			if (str == "\t") {
				str = "        ";
			}
			x += dc->GetTextExtent(str).cx;
			i++;
		}
		rect = { x, this->startRowIndex * textEdit->rowHeight + 5, x + width, this->startRowIndex * textEdit->rowHeight + textEdit->rowHeight + 5 };		
		dc->DrawText(cString1, rect, DT_EXPANDTABS | DT_TABSTOP | 0x0800);
		//rect = { 0, 0, x + width, this->startRowIndex * textEdit->rowHeight + textEdit->rowHeight + 5 };
		//memDC.DrawText(cString1, rect, DT_EXPANDTABS | DT_TABSTOP | 0x0800);
		//dc->BitBlt(x, this->startRowIndex * textEdit->rowHeight + 5, x + width, this->startRowIndex * textEdit->rowHeight + textEdit->rowHeight + 5, &memDC, 0, 0, SRCCOPY);

		string string2; // 중간
		if (this->startRowIndex + 1 < this->endRowIndex) {
			i = this->startRowIndex + 1;
			while (i < this->endRowIndex) {
				string2 += textEdit->text->GetAt(i)->PrintRowString().c_str();
				string2 += "\r\n";
				i++;
			}
			x = 5;
			rect = { x, (this->startRowIndex + 1) * textEdit->rowHeight + 5, textEdit->GetFigure()->GetX() + textEdit->GetFigure()->GetWidth(),		 
			(this->endRowIndex - 1) * textEdit->rowHeight + textEdit->rowHeight + 5 };
			dc->DrawText(string2.c_str(), rect, DT_EXPANDTABS | DT_TABSTOP | 0x0800);
			//rect = { 0, 0, textEdit->GetFigure()->GetX()+ textEdit->GetFigure()->GetWidth(),
			//	(this->endRowIndex - 1) * textEdit->rowHeight + textEdit->rowHeight + 5 };
			//memDC.DrawText(string2.c_str(), rect, DT_EXPANDTABS | DT_TABSTOP | 0x0800);
			//dc->BitBlt(x, (this->startRowIndex + 1) * textEdit->rowHeight + 5, textEdit->GetFigure()->GetX() + textEdit->GetFigure()->GetWidth(),
			//	(this->endRowIndex - 1) * textEdit->rowHeight + textEdit->rowHeight + 5, &memDC, 0, 0, SRCCOPY);
		}
		CString cString3;
		width = 0;
		i = 0;
		while (i < this->endCharacterIndex) { // 끝줄
			cString3 += textEdit->text->GetAt(this->endRowIndex)->GetAt(i)->MakeCString();
			str = textEdit->text->GetAt(this->endRowIndex)->GetAt(i)->MakeCString();
			if (str == "\t") {
				str = "        ";
			}
			width += dc->GetTextExtent(str).cx;
			i++;
		}
		x = 5;
		i = 0;
		rect = { x, this->endRowIndex * textEdit->rowHeight + 5, x + width, this->endRowIndex * textEdit->rowHeight + textEdit->rowHeight + 5 };		
		dc->DrawText(cString3, rect, DT_EXPANDTABS | DT_TABSTOP | 0x0800);
		//rect = { 0, 0, x + width, this->endRowIndex * textEdit->rowHeight + textEdit->rowHeight + 5 };
		//memDC.DrawText(cString3, rect, DT_EXPANDTABS | DT_TABSTOP | 0x0800);
		//dc->BitBlt(x, this->endRowIndex * textEdit->rowHeight + 5, x + width, this->endRowIndex * textEdit->rowHeight + textEdit->rowHeight + 5, &memDC, 0, 0, SRCCOPY);

		textEdit->copyBuffer = cString1 + string2.c_str() + cString3; // 속성에 저장
	}
	//memDC.SelectObject(pOldBitmap);
	//bitmap.DeleteObject();
	//memDC.SelectObject(cFont);
	//dc->SelectObject(oldFont);
	//cFont.DeleteObject(); // 폰트
	//memDC.DeleteDC();
}