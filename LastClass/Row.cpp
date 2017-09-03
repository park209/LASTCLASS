//Row.cpp

#include "Row.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"

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
	return static_cast<Character*>(this->textComponents[index]);
}

TextComponent* Row::Clone() const {
	return new Row(*this);
}

#include <iostream>
using namespace std;

void Row::PrintCharacter(SmartPointer<TextComponent*>& index) {
	for (index->First(); !index->IsDone(); index->Next()) {
		if (dynamic_cast<SingleByteCharacter*>(index->Current())) {
			cout << "PrintCharacter Single 확인" << endl;
		}
		else if (dynamic_cast<DoubleByteCharacter*>(index->Current())) {
			cout << "PrintCharacter Double 확인" << endl;
		}
	}
}

void Row::Accept(Visitor& visitor, CDC* cPaintDc) {
	cout << "Row Accept" << endl;
	SmartPointer<TextComponent*> smartPointer(this->CreateIterator());
	while (!smartPointer->IsDone()) {
		if (dynamic_cast<SingleByteCharacter*>(smartPointer->Current())) {
			(static_cast<SingleByteCharacter*>(smartPointer->Current()))->Accept(visitor, cPaintDc);
		}
		else if (dynamic_cast<DoubleByteCharacter*>(smartPointer->Current())) {
			(static_cast<DoubleByteCharacter*>(smartPointer->Current()))->Accept(visitor, cPaintDc);
		}
		smartPointer->Next();
	}
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

//#include <iostream>
//#include "SingleByteCharacter.h"
//#include "DoubleByteCharacter.h"
//
//using namespace std;
//
//int main(int argc, char* argv[]) {
//	Row object0(100);
//cout << object0.GetCapacity() << " " << object0.GetLength() << endl;
//
//Row object1;
//cout << object1.GetCapacity() << " " << object1.GetLength() << endl;
//
//Row object2(object1);
//cout << object2.GetCapacity() << " " << object2.GetLength() << endl;
//
//SingleByteCharacter singleByteCharacter('a');
//
//object1.Add(static_cast<Character*>(&singleByteCharacter));
//
//cout << (static_cast<SingleByteCharacter*>(object1.GetAt(0)))->GetCharacter() << endl;
//
//DoubleByteCharacter doubleByteCharacter("가");
//
//object2.Add(static_cast<Character*>(&doubleByteCharacter));
//object2.Add(static_cast<Character*>(&doubleByteCharacter));
//object2.Add(static_cast<Character*>(&doubleByteCharacter));
//object2.Add(static_cast<Character*>(&doubleByteCharacter));
//
//cout << (static_cast<DoubleByteCharacter*>(object2.GetAt(0)))->GetCharacters() << endl;
//cout << (static_cast<DoubleByteCharacter*>(object2.GetAt(1)))->GetCharacters() << endl;
//cout << (static_cast<DoubleByteCharacter*>(object2.GetAt(2)))->GetCharacters() << endl;
//cout << (static_cast<DoubleByteCharacter*>(object2.GetAt(3)))->GetCharacters() << endl;
//
//
//
//	return 0;
//}