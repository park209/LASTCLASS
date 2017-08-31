//DoubleByteCharacter.cpp
#include "DoubleByteCharacter.h"
DoubleByteCharacter::DoubleByteCharacter() {
	this->characters = "";
}
DoubleByteCharacter::DoubleByteCharacter(string characters) {
	this->characters = characters;

}
DoubleByteCharacter::DoubleByteCharacter(const DoubleByteCharacter& source) {
	this->characters = source.characters;
}
DoubleByteCharacter::~DoubleByteCharacter() {
}
TextComponent* DoubleByteCharacter::Clone() const {
	return new DoubleByteCharacter(*this);
}
DoubleByteCharacter& DoubleByteCharacter::operator=(const DoubleByteCharacter& source) {
	this->characters = source.characters;
	
	return *this;
}
string DoubleByteCharacter::GetCharacter() {
	return this->characters;
}
//
//#include <iostream>
//using namespace std; 
//int main(int argc, char *argv[]) {
//	Character* a = new DoubleByteCharacter("±è");
//	cout << static_cast<DoubleByteCharacter*>(a)->GetCharacters() << endl;
//}