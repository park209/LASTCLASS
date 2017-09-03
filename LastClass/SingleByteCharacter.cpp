//SingleByteCharacter.cpp

#include "SingleByteCharacter.h"

SingleByteCharacter::SingleByteCharacter() {
	this->character = ' ';
	this->characterIndex = 0;
	this->x = 0;
	this->y = 0;
}

SingleByteCharacter::SingleByteCharacter(char character, Long characterIndex, Long x, Long y) {
	this->character = character;
	this->characterIndex = characterIndex;
	this->x = x;
	this->y = y;
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

SingleByteCharacter& SingleByteCharacter::operator=(const SingleByteCharacter& source) {
	this->character = source.character;
	this->characterIndex = source.characterIndex;
	this->x = source.x;
	this->y = source.y;
	
	return *this;
}
 
//메인확인완료