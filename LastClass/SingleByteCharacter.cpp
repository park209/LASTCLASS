//SingleByteCharacter.cpp

#include "SingleByteCharacter.h"

SingleByteCharacter::SingleByteCharacter() {
	this->character = ' ';
}

SingleByteCharacter::SingleByteCharacter(char character) {
	this->character = character;
}

SingleByteCharacter::SingleByteCharacter(const SingleByteCharacter& source) {
	this->character = source.character;
	this->characterIndex = source.characterIndex;
	this->x = source.x;
	this->y = source.y;
}

SingleByteCharacter::~SingleByteCharacter() {
}

Character* SingleByteCharacter::Clone() const {
	return new SingleByteCharacter(*this);
}

#include <iostream>
using namespace std;

void SingleByteCharacter::Accept(Visitor& visitor, CDC* cPaintDc) {
	cout << "SingleByte Accept" << endl;
	visitor.Visit(this, cPaintDc);
}

CString SingleByteCharacter::MakeCString() const {
	char tempChar[2];
	tempChar[0] = this->character;
	tempChar[1] = '\0';

	CString cs(tempChar);
	return cs;
}

SingleByteCharacter& SingleByteCharacter::operator = (const SingleByteCharacter& source) {
	this->character = source.character;
	this->characterIndex = source.characterIndex;
	this->x = source.x;
	this->y = source.y;
	
	return *this;
}
