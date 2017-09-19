//Text.cpp 

#include "Text.h"
#include "Row.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include "Visitor.h"

Text::Text(Long capacity) : TextComposite(capacity) {
	this->capacity = capacity;
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

Long Text::Remove(Long index) {
	index = this->textComponents.Delete(index);
	this->length--;
	this->capacity--;
	return index;
}

Long Text::Insert(Long rowIndex) {
	return rowIndex;
}

string Text::MakeText() {
	SmartPointer<TextComponent*> smartPointer(this->CreateIterator());
	string text_;
	for (smartPointer->First(); !smartPointer->IsDone(); smartPointer->Next()) {
		text_.append(((Row*)smartPointer->Current())->PrintRowString());
		text_.append("\n");
	}
	Long i = text_.find_last_of('\n');
	text_.replace(i, 1, "\0");

	return text_;
}

Long Text::InsertRow(Long index) {

	Row row;
	this->textComponents.Insert(index, row.Clone());
	this->capacity++;
	this->length++;

	return index;
}

Long Text::InsertRow(Long index, TextComponent *textComponent) {
	this->textComponents.Insert(index, textComponent);

	this->capacity++;
	this->length++;

	return index;
}

void Text::SprayString(string str) {
	Long i = 0;
	char character[2] = { 0, };
	Long temp = 0;

	if (i == (Long)str.length()) {
		if (this->GetLength() == 0) {
			Row row;
			this->Add(row.Clone());
		}
	}
	while (str[i] != '\0') {
		Row *row = new Row;
		while (str[i] != '\n' && str[i] != '\0') {
			if (str[i] & 0x80) {
				character[0] = str[i];
				character[1] = str[i + 1];
				i++;
				DoubleByteCharacter doubleTemp(character);
				row->Add(doubleTemp.Clone());
			}
			else {
				SingleByteCharacter singleTemp(str[i]);
				row->Add(singleTemp.Clone());
			}
			i++;
		}
		this->Add(row->Clone());
		if (i < Long(str.length())) {
			i++;
		}

	}
}

Long Text::MaxWidth() {
	SmartPointer<TextComponent*> smartPointer(this->CreateIterator());
	Long width = 0;
	for (smartPointer->First(); !smartPointer->IsDone(); smartPointer->Next()) {
		if (width < Long(((Row*)smartPointer->Current())->PrintRowString().length())) {
			width = ((Row*)smartPointer->Current())->PrintRowString().length();
		}
	}
	return width;
}

Long Text::MaxHeight() {
	SmartPointer<TextComponent*> smartPointer(this->CreateIterator());
	Long width = 0;
	for (smartPointer->First(); !smartPointer->IsDone(); smartPointer->Next()) {
		if (width < Long(((Row*)smartPointer->Current())->PrintRowString().length())) {
			width = ((Row*)smartPointer->Current())->PrintRowString().length();
		}
	}
	return width;
}

Row* Text::GetAt(Long index) {
	return dynamic_cast<Row*>(this->textComponents[index]);
}

TextComponent* Text::Clone() const {
	return new Text(*this);
}

void Text::Accept(Visitor& visitor, CDC* cPaintDc) {
	visitor.Visit(this, cPaintDc);
}


Row* Text::operator [] (Long index) {
	return dynamic_cast<Row*>(this->textComponents[index]);
}

Text& Text::operator = (const Text& source) {
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