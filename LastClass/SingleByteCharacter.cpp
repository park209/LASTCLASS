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
}
SingleByteCharacter::~SingleByteCharacter() {
}
TextComponent* SingleByteCharacter::Clone() {
	return new SingleByteCharacter(*this);
}
SingleByteCharacter& SingleByteCharacter::operator=(const SingleByteCharacter& source) {
	this->character = source.character;
	return *this;
}
 
//메인확인완료