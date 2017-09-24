//Row.cpp

#include "Row.h"
#include "Character.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include "Visitor.h"

#pragma warning(disable:4996)
#include <iostream>
#include <string>
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

Long Row::Modify(Long index, TextComponent *textComponent) {
	return this->textComponents.Modify(index, textComponent);
}

Long Row::Remove(Long index) {
	index = this->textComponents.Delete(index);
	this->length--;
	this->capacity--;

	return index;
}

Long Row::Insert(Long index, TextComponent *textComponent) {
	this->length++;
	this->capacity++;
	return this->textComponents.Insert(index, textComponent);
}

string Row::PrintRowString() {
	char tempChar[256] = { 0, };
	string tab;
	Long i = 0;
	Long j = 0;
	Long column = 0;
	Long tabWidth = 0;

	SmartPointer<TextComponent*> iterator = this->CreateIterator();
	for (iterator->First(); !iterator->IsDone(); iterator->Next()) {
		if (dynamic_cast<SingleByteCharacter*>(iterator->Current())) {
			tempChar[i] = static_cast<SingleByteCharacter*>(iterator->Current())->GetCharacter();
			if (tempChar[i] == '\t') {
				tabWidth = (column + 8) / 8 * 8 - column;
				column += tabWidth;
				j = 0;
				tab = "";
				while (j < tabWidth) { //구한 칸만큼 탭문자의 크기를 정함
					tab += " ";
					j++;
				}
				strcat(tempChar, tab.c_str());
			}
			column += 1;
		}
		else if (dynamic_cast<DoubleByteCharacter*>(iterator->Current())) {
			tempChar[i] = static_cast<DoubleByteCharacter*>(iterator->Current())->GetCharacters()[0];
			i++;
			tempChar[i] = static_cast<DoubleByteCharacter*>(iterator->Current())->GetCharacters()[1];
		}
		i++;
	}
	string tempString(tempChar, i);

	return tempString;
}

string Row::PrintRowString(Long startIndex, Long endIndex) {
	char tempChar[256] = { 0, };
	string tab;
	Long i = startIndex;
	Long j = 0;
	Long k = 0;
	Long column = 0;
	Long tabWidth = 0;
	while (i < endIndex) {
		if (dynamic_cast<SingleByteCharacter*>(this->GetAt(i))) {
			tempChar[j] = static_cast<SingleByteCharacter*>(this->GetAt(i))->GetCharacter();
			if (tempChar[j] == '\t') {
				tabWidth = (column + 8) / 8 * 8 - column;
				column += tabWidth;
				k = 0;
				tab = "";
				while (k < tabWidth) { //구한 칸만큼 탭문자의 크기를 정함
					tab += "#";
					k++;
				}
				char temp[8];
				strcpy(temp, tab.c_str());
				tempChar[j] = temp[0];
				//strcat(tempChar, tab.c_str());
			}
			column += 1;
		}
		else if (dynamic_cast<DoubleByteCharacter*>(this->GetAt(i))) {
			tempChar[j] = static_cast<DoubleByteCharacter*>(this->GetAt(i))->GetCharacters()[0];
			j++;
			tempChar[j] = static_cast<DoubleByteCharacter*>(this->GetAt(i))->GetCharacters()[1];
			column += 2;
		}
		j++;
		i++;
	}
	string tempString(tempChar, i);

	return tempString;
}

string Row::ReplaceTabString(string &str, const string& from, const string& to) {
	size_t index = 0; //string처음부터 검사
	while ((index = str.find(from, index)) != string::npos)  //from을 찾을 수 없을 때까지
	{
		str.replace(index, from.length(), to);
		index += to.length(); // 중복검사를 피하고 from.length() > to.length()인 경우를 위해서
	}
	return str;
}

Character* Row::GetAt(Long index) {
	return static_cast<Character*>(this->textComponents[index]);
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

int main(int argc, char* argv[]) {
	Row row;
	SingleByteCharacter single1('a');
	row.Add(single1.Clone());
	SingleByteCharacter single2('b');
	row.Add(single2.Clone());
	SingleByteCharacter single3('c');
	row.Add(single3.Clone());
	SingleByteCharacter single4('\t');
	row.Add(single4.Clone());
	SingleByteCharacter single5('d');
	row.Add(single5.Clone());
	
	string a= row.PrintRowString();

	cout << a << endl;
}