//Text.cpp 
#include "Text.h"

Text::Text(Long cpacity) : TextComposite(cpacity) {
	this->capacity = cpacity;
	this->length = 0;
}
Text::~Text() {
}

Text::Text(const Text& source) {
	this->textComponents = source.textComponents;


	Long i = 0;
	while (i < source.length) {
		this->textComponents.Modify(i, (const_cast<Text&>(source)).textComponents[i]->Clone());
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
}
Long Text::Add(Row *row) {
	Long index;

	if (this->length < this->capacity) {
		index = this->textComponents.Store(this->length, row->Clone());
	}
	else {
		index = this->textComponents.AppendFromRear(row->Clone());
		this->capacity++;
	}
	this->length++;
	return index;
}

Long Text::Add(TextComponent *textComponent) {
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

Row* Text::GetAt(Long index) {
	return static_cast<Row*>(this->textComponents.GetAt(index));
}


TextComponent*  Text::Clone() const {
	return new Text(*this);
}

Row* Text::operator[] (Long index) {
	return dynamic_cast<Row*>(this->textComponents[index]);
}


Text& Text::operator= (const Text& source) {
	Long i = 0;
	this->textComponents = source.textComponents;

	while (i < source.length) {
		this->textComponents.Modify(i, (const_cast<Text&>(source)).textComponents.GetAt(i)->Clone());
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
	return *this;
}

#include <iostream>
using namespace std;
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include "Character.h"
int main(int argc, char* argv[]) {
	Text *text = new Text();
	Row *row = new Row();
	Row *row2 = new Row();
	Long index = text->Add(row);
	index = text->Add(row);
	cout << text->GetLength() << endl;
	cout << index << endl;
	DoubleByteCharacter *single = new DoubleByteCharacter("ȣ");
	cout << single->GetCharacter() << endl;
	index=row->Add(single);
	index = row->Add(single);
	cout << index << endl;
	cout << row->GetLength() << endl;
	row= text->GetAt(0);
	string dd= text->GetAt(0)->GetAt(0)->GetCharacter();
	cout <<  dd << endl;
	/*if (dynanamimic_cast<SingleByteCharacter*>(text->GetAt(0)->GetAt(0))) {
		cout << "single" << endl;
		cout << (dynamic_cast<SingleByteCharacter*>(text->GetAt(0)->GetAt(0)))->GetCharacter() << endl;
	}
	else if(dynamic_cast<DoubleByteCharacter*>(text->GetAt(0)->GetAt(0)) ){
		cout << "double" << endl;
		cout << (dynamic_cast<DoubleByteCharacter*>(text->GetAt(0)->GetAt(0)))->GetCharacter() << endl;
	}*/

	return 0;

}