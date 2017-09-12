//Row.h

#ifndef _ROW_H
#define _ROW_H

#include "TextComposite.h"
#include "Character.h"
#include <string>

using namespace std;

typedef signed long int Long;

class Row : public TextComposite {
public:
	Row(Long capacity = 128);
	Row(Long x, Long y, Long rowHeight, Long capacity = 128);
	Row(const Row& source);
	virtual ~Row();

	Long Add(Character *character);
	Long Add(TextComponent *textComponent);
	Long Modify(Long index, TextComponent *textComponent);
	Long Remove(Long index);
	Long Insert(Long index, TextComponent *textComponent);
	Character* GetAt(Long index);

	TextComponent* Clone() const;
	void PrintCharacter(SmartPointer<TextComponent*>& index);
	string PrintRowString();
	void Accept(Visitor& visitor, CDC* cPaintDc);

	Row& operator = (const Row& source);
	Character* operator [] (Long index);

	Long GetCapacity() const;
	Long GetLength() const;
	Long GetX() const;
	Long GetY() const;
	Long GetRowHeight() const;
public:
	Long x;
	Long y;
	Long rowHeight;
};

inline Long Row::GetX() const {
	return this->x;
}
inline Long Row::GetY() const {
	return this->y;
}
inline Long Row::GetCapacity() const {
	return this->capacity;
}
inline Long Row::GetLength() const {
	return this->length;
}
inline Long Row::GetRowHeight() const {
	return this->rowHeight;
}

#endif // _ROW_H