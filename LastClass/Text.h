//Text.h

#ifndef _TEXT_H
#define _TEXT_H

#include "TextComposite.h"
#include <afxwin.h>
#include <string>

typedef signed long int Long;

using namespace std;

class Row;
class TextComponent;
class Visitor;
class Text : public TextComposite {
public:
	Text(Long capacity = 128);
	Text(const Text& source);
	virtual ~Text();

	Long Add(Row *row);
	Long Add(TextComponent *textComponent);
	Long Remove(Long index);
	Long Insert(Long index);

	string MakeText();

	Long InsertRow(Long index);
	Long InsertRow(Long index, TextComponent *textComponent);
	void SprayString(string str);
	Long MaxWidth(CDC* cPaintDc);
	Row* GetAt(Long index);
	
	TextComponent* Clone() const;
	void Accept(Visitor& visitor, CDC* cPaintDc);

	Text& operator = (const Text& source);
	Row* operator [] (Long index);

	Long GetCapacity() const;
	Long GetLength() const;
	Long GetWidth() const;
	Long GetHeight() const;
private:
	Long width;
	Long height;
};

inline Long Text::GetCapacity() const {
	return this->capacity;
}
inline Long Text::GetLength() const {
	return this->length;
}
inline Long Text::GetWidth() const {
	return this->width;
}
inline Long Text::GetHeight() const {
	return this->height;
}

#endif // _TEXT_H