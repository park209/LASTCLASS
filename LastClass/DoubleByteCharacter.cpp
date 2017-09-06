//DoubleByteCharacter.cpp

#include "DoubleByteCharacter.h"

DoubleByteCharacter::DoubleByteCharacter() {
	this->characters[0] = ' ';
	this->characters[1] = ' ';
}

DoubleByteCharacter::DoubleByteCharacter(char(*characters)) {
	this->characters[0] = characters[0];
	this->characters[1] = characters[1];
}

DoubleByteCharacter::DoubleByteCharacter(const DoubleByteCharacter& source) {
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

//
//#include <iostream>
//using namespace std; 
//int main(int argc, char *argv[]) {
//	Character* a = new DoubleByteCharacter("��");
//	cout << static_cast<DoubleByteCharacter*>(a)->GetCharacters() << endl;
//}