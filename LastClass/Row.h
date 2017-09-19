//Row.h

#ifndef _ROW_H
#define _ROW_H

#include "TextComposite.h"
#include <afxwin.h>
#include <string>

typedef signed long int Long;

using namespace std;

class TextComponent;
class Row;
class Character;
class Visitor;
class Row : public TextComposite {
public:
	Row(Long capacity = 128);
	Row(const Row& source);
	virtual ~Row();

	Long Add(Character *character);
	Long Add(TextComponent *textComponent);
	Long Modify(Long index, TextComponent *textComponent);
	Long Remove(Long index);
	Long Insert(Long index, TextComponent *textComponent);
	string PrintRowString();
	string PrintRowString(Long count, Long offset=0);
	Character* GetAt(Long index);

	TextComponent* Clone() const;

	Row& operator = (const Row& source);
	Character* operator [] (Long index);

	Long GetCapacity() const;
	Long GetLength() const;
};

inline Long Row::GetCapacity() const {
	return this->capacity;
}
inline Long Row::GetLength() const {
	return this->length;
}

#endif // _ROW_H