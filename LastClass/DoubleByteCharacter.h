#pragma once
//DoubleByteCharacter.h

#ifndef _DOUBLEBYTECHARACTER_H
#define _DOUBLEBYTECHARACTER_H
#include "Character.h"
#include <string>
using namespace std;
class DoubleByteCharacter : public Character {
public:
	DoubleByteCharacter();
	DoubleByteCharacter(string characters);
	DoubleByteCharacter(const DoubleByteCharacter& source);
	virtual ~DoubleByteCharacter();
	virtual TextComponent* Clone() const;
	DoubleByteCharacter& operator = (const DoubleByteCharacter& source);
    string GetCharacter();
private:
	string characters;
};

#endif // !_DOUBLEBYTECHARACTER_H

