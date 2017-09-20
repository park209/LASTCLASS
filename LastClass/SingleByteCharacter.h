//SingleByteCharacter.h
#ifndef _SINGLEBYTECHARACTER_H
#define _SINGLEBYTECHARACTER_H

#include "Character.h"
#include <afxwin.h>

class SingleByteCharacter : public Character {
public:
	SingleByteCharacter();
	SingleByteCharacter(char character);
	SingleByteCharacter(const SingleByteCharacter& source);
	~SingleByteCharacter();

	CString MakeCString() const;

	virtual Character* Clone() const;

	SingleByteCharacter& operator=(const SingleByteCharacter& sourcce);

	char GetCharacter() const;
private:
	char character;
};

inline char SingleByteCharacter::GetCharacter() const {
	return this->character;
}

#endif // _SINGLEBYTECHARACTER_H

