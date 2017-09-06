//DoubleByteCharacter.cpp

#include "DoubleByteCharacter.h"

DoubleByteCharacter::DoubleByteCharacter() {
	this->x = 0;
	this->y = 0;
	this->characters[0] = ' ';
	this->characters[1] = ' ';
}

DoubleByteCharacter::DoubleByteCharacter(char(*characters), Long x, Long y) {
	this->x = x;
	this->y = y;
	this->characters[0] = characters[0];
	this->characters[1] = characters[1];
}

DoubleByteCharacter::DoubleByteCharacter(const DoubleByteCharacter& source) {
	this->x = source.x;
	this->y = source.y;
	this->characters[0] = source.characters[0];
	this->characters[1] = source.characters[1];
}

DoubleByteCharacter::~DoubleByteCharacter() {
}

TextComponent* DoubleByteCharacter::Clone() const {
	return new DoubleByteCharacter(*this);
}

#include <iostream>
using namespace std;

void DoubleByteCharacter::Accept(Visitor& visit, CDC* cPaintDc) {
	cout << "DoubleByte Accept" << endl;
	visit.Visit(this, cPaintDc);
}

DoubleByteCharacter& DoubleByteCharacter::operator=(const DoubleByteCharacter& source) {
	this->characters[0] = source.characters[0];
	this->characters[1] = source.characters[1];

	return *this;
}

CString DoubleByteCharacter::MakeCString() const {
	char newChar[3];
	newChar[0] = this->characters[0];
	newChar[1] = this->characters[1];
	newChar[2] = '\0';

	CString cs(newChar);

	return cs;
}

//
//#include <iostream>
//using namespace std; 
//int main(int argc, char *argv[]) {
//	Character* a = new DoubleByteCharacter("±è");
//	cout << static_cast<DoubleByteCharacter*>(a)->GetCharacters() << endl;
//}