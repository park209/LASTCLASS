//Character.h

#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "TextComponent.h"
#include "Visitor.h"
#include "Iterator.h"
#include "SmartPointer.h"

class Character : public TextComponent {
public:
	Character() {};
	Character(const Character& source) {};
	virtual ~Character() {};

	virtual TextComponent* Clone() const = 0;
	virtual CString MakeCString() const = 0;
};

#endif // _CHARACTER_H
