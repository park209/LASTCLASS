#pragma once
#ifndef _SINGLEBYTECHARACTER_H
#define _SINGLEBYTECHARACTER_H
#include "Character.h"
class SingleByteCharacter :public Character {
public:
	SingleByteCharacter();
	SingleByteCharacter(char character);
	SingleByteCharacter(const SingleByteCharacter& source);
	 ~SingleByteCharacter();
	virtual TextComponent* Clone();
	SingleByteCharacter& operator=(const SingleByteCharacter& sourcce);
	char GetCharacter()const;
private:
	char character;
};
inline char SingleByteCharacter::GetCharacter()const {
	return this->character;
}
#endif // !_SINGLEBYTECHARACTER_H

