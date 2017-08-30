//DoubleByteCharacter.cpp
#include "DoubleByteCharacter.h"
DoubleByteCharacter::DoubleByteCharacter() {
	this->characters[0] = ' ';
	this->characters[1] = ' ';
	this->characters[2] = ' ';
}
DoubleByteCharacter::DoubleByteCharacter(char(*characters)) {
	this->characters[0] = characters[0];
	this->characters[1] = characters[1];
	this->characters[2] = '\0';
}
DoubleByteCharacter::DoubleByteCharacter(const DoubleByteCharacter& source) {
	this->characters[0] = source.characters[0];
	this->characters[1] = source.characters[1];
	this->characters[2] = '\0';
}
DoubleByteCharacter::~DoubleByteCharacter() {
}
TextComponent* DoubleByteCharacter::Clone() {
	return new DoubleByteCharacter(*this);
}
DoubleByteCharacter& DoubleByteCharacter::operator=(const DoubleByteCharacter& source) {
	this->characters[0] = source.characters[0];
	this->characters[1] = source.characters[1];
	this->characters[2] = '\0';
	return *this;
}

#include <iostream>
using namespace std; 
int main(int argc, char *argv[]) {
	Character* a = new DoubleByteCharacter("±è");
	cout << static_cast<DoubleByteCharacter*>(a)->GetCharacters() << endl;
}