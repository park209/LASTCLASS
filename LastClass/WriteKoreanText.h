//WriteKoreanText.h

#pragma comment(lib,"imm32")

#include <afxwin.h>

#ifndef _WRITEKOREANTEXT_H
#define _WRITEKOREANTEXT_H

class TextEdit;
class WriteKoreanText {
public:
	WriteKoreanText();
	WriteKoreanText(const WriteKoreanText& source);
	~WriteKoreanText();
public:
	void WriteHanguel(WPARAM wParam, LPARAM lParam, HIMC hIMC, TextEdit *textEdit);
};

#endif //_WRITEKOREANTEXT_H