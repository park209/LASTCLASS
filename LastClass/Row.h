//Row.h

#ifndef _ROW_H
#define _ROW_H

#include "TextComposite.h"
#include "Character.h"

typedef signed long int Long;

class Row : public TextComposite {
public:
	Row(Long capacity = 128);
	Row(const Row& source);
	virtual ~Row();

	Long Add(Character *character);
	Long Add(TextComponent *textComponent);
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