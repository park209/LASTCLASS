//Row.cpp

#include "Row.h"

Row::Row(Long capacity) : TextComposite(capacity) {
	this->capacity = capacity;
	this->length = 0;
}

Row::Row(const Row& source) {
	this->textComponents = source.textComponents;
	this->capacity = source.capacity;
	this->length = source.length;
	Long i = 0;
	while (i < source.length) {
		this->textComponents.Modify(i, (const_cast<Row&>(source)).textComponents[i]->Clone());
		i++;
	}
}

Row::~Row() {
}

Long Row::Add(TextComponent *textComponent) {
	Long index;
	if (this->length < this->capacity) {
		index = this->textComponents.Store(this->length, textComponent);
	}
	else {
		index = this->textComponents.AppendFromRear(textComponent);
		this->capacity++;
	}
	this->length++;
	return index;
}

Long Row::Add(Character *character) {
	Long index;
	if (this->length < this->capacity) {
		index = this->textComponents.Store(this->length, character->Clone());
	}
	else {
		index = this->textComponents.AppendFromRear(character->Clone());
		this->capacity++;
	}
	this->length++;
	return index;
}

Character* Row::GetAt(Long index) {
	return static_cast<Character*>( this->textComponents.GetAt(index));
}

TextComponent* Row::Clone() const {
	return new Row(*this);
}

Row& Row::operator = (const Row& source) {
	this->capacity = source.capacity;
	this->length = source.length;
	this->textComponents = source.textComponents;
	Long i = 0;
	while (i < source.length) {
		this->textComponents.Modify(i, (const_cast<Row&>(source)).textComponents.GetAt(i)->Clone());
		i++;
	}
	return *this;
}

Character* Row::operator [] (Long index) {
	return static_cast<Character*>(this->textComponents[index]);
}

#include <iostream>
#include "SingleByteCharacter.h"

using namespace std;

//int main(int argc, char* argv[]) {
//	Row object0(100);
//	cout << object0.GetCapacity() << " " << object0.GetLength() << endl;
//
//	Row object1;
//	cout << object1.GetCapacity() << " " << object1.GetLength() << endl;
//
//	Row object2(object1);
//	cout << object2.GetCapacity() << " " << object2.GetLength() << endl;
//	
//	SingleByteCharacter singleByteCharacter('a');
//
//	//object1.Add();
//
//	//cout << (static_cast<SingleByteCharacter*>(object1.GetAt(0)))->GetCharacter() << endl;
//
//	
//
//	return 0;
//}