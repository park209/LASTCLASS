//TextAreaSelected.cpp

#include "TextAreaSelected.h"
#include "TextAreaSelectedProcess.h"
#include "TextEdit.h"
#include "Caret.h"
#include "Text.h"
#include "Row.h"
#include "Character.h"
#include "Figure.h"

TextAreaSelected::TextAreaSelected() {
	this->selected = new TextAreaSelectedProcess;
}
TextAreaSelected::TextAreaSelected(const TextAreaSelected& source) {
}
TextAreaSelected::~TextAreaSelected() {
	if (this->selected != 0) {
		delete selected;
	}
}
void TextAreaSelected::SelectTextArea(TextEdit *textEdit, CPaintDC *dc) {
	//CFont cFont;
	//cFont.CreateFont(textEdit->GetRowHeight(), 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,// 글꼴 설정
	//   OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "맑은 고딕");
	//textEdit->SetFont(&cFont, TRUE);
	//CFont *oldFont = dc->SelectObject(&cFont);

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

	CString TopCstr;
	CString middleCstr;
	CString BottomCstr;
	RECT rt;

	selected->GetRange(textEdit);
	if (textEdit->selectedY == textEdit->caret->GetRowIndex()) {
		this->selected->SingleLineSelected(textEdit, dc, &TopCstr, &rt);
		dc->DrawText(TopCstr, &rt, DT_NOCLIP | DT_EXPANDTABS);
	}
	else {
		this->selected->FirstMultiLineSelected(textEdit, dc, &TopCstr, &rt);
		dc->DrawText(TopCstr, &rt, DT_NOCLIP | DT_EXPANDTABS);
		if (this->selected->GetStartRowIndex() + 1 < this->selected->GetEndRowIndex()) {
			this->selected->MiddleMultiLineSelected(textEdit, dc, &middleCstr, &rt);
			dc->DrawText(middleCstr, &rt, DT_NOCLIP | DT_EXPANDTABS);
		}

		this->selected->EndMultiLineSelected(textEdit, dc, &BottomCstr, &rt);
		dc->DrawText(BottomCstr, &rt, DT_NOCLIP | DT_EXPANDTABS);
	}
	//dc->BitBlt(rt.left+5,rt.top+5, rt.right+5,rt.bottom, &memDC, 0, 0, SRCCOPY);

	textEdit->copyBuffer = TopCstr + middleCstr + BottomCstr;

	//memDC.SelectObject(pOldBitmap);
	//bitmap.DeleteObject();
	//memDC.SelectObject(cFont);
	//dc->SelectObject(oldFont);
	//cFont.DeleteObject(); // 폰트
	//memDC.DeleteDC();
}