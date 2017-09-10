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
	void Find(Long x, Long y, Long height, Row**(*indexes), Long *count);
	Long Remove(Long index);
	Row* GetAt(Long index);

	TextComponent* Clone() const;
	void PrintRow(SmartPointer<TextComponent*>& index);
	void Accept(Visitor& visitor, CDC* cPaintDc);
	Long InsertRow(Long index);

	Long GetCapacity() const;
	Long GetLength() const;

	Text& operator = (const Text& source);
	Row* operator [] (Long index);

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