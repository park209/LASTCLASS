//DoubleClickTextAreaProcess.h

#ifndef _DOUBLECLICKTEXTAREAPROCESS_H
#define _DOUBLECLICKTEXTAREAPROCESS_H

typedef signed long int Long;

class TextEdit;
class DoubleClickTextAreaProcess {
public:
	DoubleClickTextAreaProcess();
	DoubleClickTextAreaProcess(const DoubleClickTextAreaProcess& source);
	~DoubleClickTextAreaProcess();
public:
	Long DoubleClickKoreanStartIndex(TextEdit *textEdit);
	Long DoubleClickKoreanEndIndex(TextEdit *textEdit);
	Long DoubleClickEnglishStartIndex(TextEdit *textEdit);
	Long DoubleClickEnglishEndIndex(TextEdit *textEdit);
};

#endif _DOUBLECLICKTEXTAREAPROCESS_H