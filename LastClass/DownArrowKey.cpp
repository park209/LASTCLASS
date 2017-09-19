//DownArrowKey.cpp

#include "DownArrowKey.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"
#include "Character.h"

DownArrowKey::DownArrowKey() {
}

DownArrowKey::DownArrowKey(const DownArrowKey& source) {
}

DownArrowKey::~DownArrowKey() {
}

void DownArrowKey::KeyPress(TextEdit *textEdit) {
	CPaintDC dc(textEdit);

	CFont cFont;
	cFont.CreateFont(textEdit->GetRowHeight(), 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,      // �۲� ����
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "����ü");
	textEdit->SetFont(&cFont, TRUE);
	CFont *oldFont = dc.SelectObject(&cFont); // ��Ʈ ����


	Long x = textEdit->caret->GetCurrentCaretX();
	Long y = textEdit->caret->GetCurrentCaretY();

	Long rowIndex = y + textEdit->GetRowHeight();

	textEdit->caret->MoveToPoint(textEdit, &dc, CPoint(x, rowIndex));

	//Long rowDownWidth = 0;   //�Ʒ��ٱ���
	//Long rowCurrentWidth = 0;   //�����ٱ���
	//Long i = 0;
	//while (i < textEdit->characterIndex) { // �����ٿ��� ĳ�����ε������� �ʺ� ���Ѵ�
	//	rowCurrentWidth += dc.GetTextExtent(textEdit->text->GetAt(textEdit->rowIndex)->GetAt(i)->MakeCString()).cx;
	//	i++;
	//}
	//if (textEdit->rowIndex < textEdit->text->GetLength() - 1) { // 0 �ϼ� �����ϱ�
	//	textEdit->rowIndex++;
	//	textEdit->characterIndex = 0; // �Ʒ��ٿ��� ĳ�����ε��� ���Ѵ�(�ʺ��)
	//	while (rowDownWidth < rowCurrentWidth && textEdit->characterIndex < textEdit->text->GetAt(textEdit->rowIndex)->GetLength()) {
	//		rowDownWidth += dc.GetTextExtent(textEdit->text->GetAt(textEdit->rowIndex)->GetAt(textEdit->characterIndex)->MakeCString()).cx;
	//		textEdit->characterIndex++; // �Ѱ� ���ٵ�
	//	}
	//	if (rowCurrentWidth < rowDownWidth && textEdit->characterIndex > 0 &&
	//		rowCurrentWidth <= rowDownWidth - dc.GetTextExtent(textEdit->text->GetAt(textEdit->rowIndex)->GetAt(textEdit->characterIndex - 1)->MakeCString()).cx / 2) {
	//		textEdit->characterIndex--;
	//	}
	//}
	//else {
	//	textEdit->rowIndex = textEdit->text->GetLength() - 1;
	//}
	dc.SelectObject(oldFont);
	cFont.DeleteObject(); // ��Ʈ
}