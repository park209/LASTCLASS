#pragma once
#ifndef _SINGLEBYTECHARACTER_H
#define _SINGLEBYTECHARACTER_H

#include "Character.h"

typedef signed long int Long;

class SingleByteCharacter :public Character {
public:
	SingleByteCharacter();
	SingleByteCharacter(char character, Long characterIndex, Long x, Long y);
	SingleByteCharacter(const SingleByteCharacter& source);
	 ~SingleByteCharacter();

	virtual Character* Clone() const;
	virtual void Accept(Visitor& visitor, CDC* cPaintDc);
	virtual CString MakeCString() const;

	SingleByteCharacter& operator=(const SingleByteCharacter& sourcce);

	char GetCharacter() const;
	Long GetCharacterIndex() const;
	Long GetX() const;
	Long GetY() const;
private:
	char character;
	Long characterIndex;
	Long x;
	Long y;
};

inline char SingleByteCharacter::GetCharacter() const {
	return this->character;
}
inline Long SingleByteCharacter::GetCharacterIndex() const {
	return this->characterIndex;
}
inline Long SingleByteCharacter::GetX() const {
	return this->x;
}
inline Long SingleByteCharacter::GetY() const {
	return this->y;
}

#endif // _SINGLEBYTECHARACTER_H

