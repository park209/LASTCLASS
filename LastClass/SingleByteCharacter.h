#pragma once
#ifndef _SINGLEBYTECHARACTER_H
#define _SINGLEBYTECHARACTER_H
#include "Character.h"
#include <string>
using namespace std;

class SingleByteCharacter :public Character {
public:
	SingleByteCharacter();
	SingleByteCharacter(string characters);
	SingleByteCharacter(const SingleByteCharacter& source);
	 ~SingleByteCharacter();
	virtual Character* Clone() const ;
	SingleByteCharacter& operator=(const SingleByteCharacter& sourcce);
	//string GetCharacter()const;
	string GetCharacter();
private:
	string characters;
};

//	return const_cast<string>(this->character);
//}
#endif // !_SINGLEBYTECHARACTER_H

