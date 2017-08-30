//TextComposite.h

#ifndef _TEXTCOMPOSITE_H
#define _TEXTCOMPOSTIE_H

#include "TextComponent.h"
#include "Array.h"

typedef signed long int Long;

class Character;
class TextComposite : public TextComponent {
public:
	TextComposite(Long capacity = 128);
	TextComposite(const TextComposite& source);
	virtual Long Add(Character *character) = 0;
	//virtual Long Remove(Long index) = 0;
	virtual TextComponent* GetAt(Long index) = 0;
	virtual TextComponent* Clone() const = 0;
	virtual ~TextComposite() = 0;

	TextComposite& operator = (const TextComposite& source);
	Long GetCapacity() const;
	Long GetLength() const;
protected:
	Array<TextComponent*> textComponents;
	Long capacity;
	Long length;
};

inline Long TextComposite::GetCapacity() const {
	return this->capacity;
}

inline Long TextComposite::GetLength() const {
	return this->length;
}

#endif // _TEXTCOMPONENT_H