//SingleByteCharacter.cpp

#include "SingleByteCharacter.h"

SingleByteCharacter::SingleByteCharacter() {
	this->characters = "";

}
SingleByteCharacter::SingleByteCharacter(string characters) {
	 
	this->characters = characters;
	
}
SingleByteCharacter::SingleByteCharacter(const SingleByteCharacter& source) {
	this->characters= source.characters;

;
}
SingleByteCharacter::~SingleByteCharacter() {
}
Character* SingleByteCharacter::Clone() const {
	return new SingleByteCharacter(*this);
}
SingleByteCharacter& SingleByteCharacter::operator=(const SingleByteCharacter& source) {
	this->characters = source.characters;

	
	return *this;
}
 
 string SingleByteCharacter::GetCharacter() {
	return this->characters;
}
