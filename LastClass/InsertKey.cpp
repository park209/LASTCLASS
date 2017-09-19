//InsertKey.cpp

#include "InsertKey.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"

InsertKey::InsertKey() {
}

InsertKey::InsertKey(const InsertKey& source) {
}

InsertKey::~InsertKey() {
}

void InsertKey::KeyPress(TextEdit *textEdit) {
	if (textEdit->flagInsert == 1) {
		textEdit->flagInsert = 0;
	}
	else {
		textEdit->flagInsert = 1;
	}

}