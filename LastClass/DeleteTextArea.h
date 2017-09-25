//DeleteTextArea.h

#ifndef _DELETETEXTAREA_H
#define _DELETETEXTAREA_H

class TextEdit;
class DeleteTextArea {
public:
	DeleteTextArea();
	DeleteTextArea(const DeleteTextArea& source);
	~DeleteTextArea();
public:
	void DeleteArea(TextEdit *textEdit);
};

#endif _DELETETEXTAREA_H