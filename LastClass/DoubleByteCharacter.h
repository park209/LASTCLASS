//DoubleByteCharacter.h

#ifndef _DOUBLEBYTECHARACTER_H
#define _DOUBLEBYTECHARACTER_H

#include "Character.h"

typedef signed long int Long;

class DoubleByteCharacter : public Character {
public:
	DoubleByteCharacter();
	DoubleByteCharacter(char(*characters), Long x, Long y);
	DoubleByteCharacter(const DoubleByteCharacter& source);
	virtual ~DoubleByteCharacter();

	virtual TextComponent* Clone() const;
	virtual void Accept(Visitor& visitor, CDC* cPaintDc);
	CString MakeCString() const;

	DoubleByteCharacter& operator = (const DoubleByteCharacter& source);

	Long GetX() const;
	Long GetY() const;
	char* GetCharacters() const;
private:
	Long x;
	Long y;
	char characters[2];
};

inline Long DoubleByteCharacter::GetX() const {
	return this->x;
}
inline Long DoubleByteCharacter::GetY() const {
	return this->y;
}
inline char* DoubleByteCharacter::GetCharacters() const {
	return const_cast<char*>(this->characters);
}
#endif // _DOUBLEBYTECHARACTER_H

