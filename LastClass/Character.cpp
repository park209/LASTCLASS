//Character.cpp

#include "Character.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
Character::Character() {
}
Character::Character(const Character& source) {
}
Character::~Character() {
}
void Character::operator= (const Character& source) {
}

//#include <iostream>
//using namespace std;
//void Character::PrintText() {
//	if (dynamic_cast<SingleByteCharacter*>(this)) {
//		cout << dynamic_cast<SingleByteCharacter*>(this)->GetCharacter() << endl;
//	}
//	else if (dynamic_cast<DoubleByteCharacter*>(this)) {
//		cout << dynamic_cast<DoubleByteCharacter*>(this)->GetCharacters() << endl;
//	}
//}

//확인완료