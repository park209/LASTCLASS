//CtrlPasteKey.cpp

#include "CtrlPasteKey.h"
#include "TextEdit.h"
#include "Row.h"
#include "Caret.h"
#include "Text.h"
#include "DoubleByteCharacter.h"
#include "SingleByteCharacter.h"
CtrlPasteKey::CtrlPasteKey() {
}
CtrlPasteKey::CtrlPasteKey(const CtrlPasteKey& source) {
}
CtrlPasteKey::~CtrlPasteKey() {
}

void CtrlPasteKey::KeyPress(TextEdit *textEdit) {
	unsigned int priority_list = CF_TEXT;
	char *p_string = NULL;
	if (::GetPriorityClipboardFormat(&priority_list, 1) == CF_TEXT) {
		OpenClipboard(NULL);
		HANDLE h_clipboard_data = ::GetClipboardData(CF_TEXT);
		if (h_clipboard_data != NULL) {
			char *p_clipboard_data = (char *)::GlobalLock(h_clipboard_data);
			int string_len = strlen(p_clipboard_data) + 1;
			p_string = new char[string_len];
			memcpy(p_string, p_clipboard_data, string_len);
			::GlobalUnlock(h_clipboard_data);
		}
		::CloseClipboard();
		textEdit->copyBuffer = p_string;
		Long size = strlen(p_string);
		Long i = 0;
		char character[2] = { 0, };
		Long temp = 0;
		
			Row *row = textEdit->text->GetAt(textEdit->caret->GetRowIndex());
			if (textEdit->caret->GetCharacterIndex() < row->GetLength()) {
				while (i < size) {
					if (textEdit->copyBuffer[i] & 0x80) {
						character[0] = textEdit->copyBuffer[i];
						character[1] = textEdit->copyBuffer[i + 1];
						i++;
						DoubleByteCharacter doubleTemp(character);
						row->Insert(textEdit->caret->GetCharacterIndex(),doubleTemp.Clone());
					}
					else {
						SingleByteCharacter singleTemp(textEdit->copyBuffer[i]);
						row->Insert(textEdit->caret->GetCharacterIndex(),singleTemp.Clone());
					}
					textEdit->caret->characterIndex++;
					i++;
				}

			}
			else {
				while (i < size) {
					if (textEdit->copyBuffer[i] & 0x80) {
						character[0] = textEdit->copyBuffer[i];
						character[1] = textEdit->copyBuffer[i + 1];
						i++;
						DoubleByteCharacter doubleTemp(character);
						row->Add(doubleTemp.Clone());
					}
					else {
						SingleByteCharacter singleTemp(textEdit->copyBuffer[i]);
						row->Add(singleTemp.Clone());
					}
					textEdit->caret->characterIndex++;
					i++;
				}
			}
	}
}