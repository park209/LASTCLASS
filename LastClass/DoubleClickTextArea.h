//DoubleClickTextArea.h

#ifndef _DOUBLECLICKTEXTAREA_H
#define _DOUBLECLICKTEXTAREA_H

class TextEdit;
class DoubleClickTextArea {
public:
	DoubleClickTextArea();
	DoubleClickTextArea(const DoubleClickTextArea& source);
	~DoubleClickTextArea();
public:
	void FindDoubleClickAreaIndex(TextEdit *textEdit);
};

#endif _DOUBLECLICKTEXTAREA_H