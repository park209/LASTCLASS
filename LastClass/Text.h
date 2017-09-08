#pragma once

//Text.h

#ifndef _TEXT_H
#define _TEXT_H

#include "Row.h"

typedef signed long int Long;

class Text : public TextComposite {
public:
	Text(Long capacity = 128);
	Text(const Text& source);
	virtual ~Text();

	Long Add(Row *row);
	Long Add(TextComponent *textComponent);
	Row* GetAt(Long index);

	TextComponent* Clone() const;
	void PrintRow(SmartPointer<TextComponent*>& index);
	void Accept(Visitor& visitor, CDC* cPaintDc);

	Long GetCapacity() const;
	Long GetLength() const;

	Text& operator = (const Text& source);
	Row* operator [] (Long index);

};

inline Long Text::GetCapacity() const {
	return this->capacity;
}
inline Long Text::GetLength() const {
	return this->length;
}



#endif // !_TEXT_H