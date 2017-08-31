#pragma once
#ifndef _CHARACTER_H
#define _CHARACTER_H
#include "TextComponent.h"
#include <string>
using namespace std;
class Character : public TextComponent {
public:
	Character();
	Character(const Character& source);
	virtual ~Character() = 0;
	void operator = (const Character& source);
	virtual TextComponent* Clone() const = 0;
	//virtual string GetCharacter() const = 0;
	virtual string GetCharacter()=0 ;
};

#endif // !_CHARACTER_H
