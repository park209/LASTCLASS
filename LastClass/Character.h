#pragma once
#ifndef _CHARACTER_H
#define _CHARACTER_H
#include "TextComponent.h"
class Character : public TextComponent {
public:
	Character();
	Character(const Character& source);
	virtual ~Character() = 0;
	void operator = (const Character& source);
	virtual TextComponent* Clone() = 0;
};

#endif // !_CHARACTER_H
