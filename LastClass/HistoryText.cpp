//HistoryText.cpp

#include "HistoryText.h"
#include "Text.h"
#include "Caret.h"

HistoryText::HistoryText() {
	this->undoTextArray = new Array<Text*>(0);
	this->redoTextArray = new Array<Text*>(0);
	this->undoCaretArray = new Array<Caret*>(0);
	this->redoCaretArray = new Array<Caret*>(0);
}

HistoryText::HistoryText(const HistoryText& source) {
	this->undoTextArray = source.undoTextArray;
	this->redoTextArray = source.redoTextArray;
	this->undoCaretArray = new Array<Caret*>(0);
	this->redoCaretArray = new Array<Caret*>(0);
}

HistoryText::~HistoryText() {
}

void HistoryText::PushUndo(Text *text, Caret *caret) {
	if (this->undoTextArray->GetCapacity() < 50) {
		this->undoTextArray->AppendFromFront(static_cast<Text*>(text->Clone()));
		Caret *tempCaret = new Caret(*caret);
		this->undoCaretArray->AppendFromFront(tempCaret);
	}
	else {
		this->undoTextArray->Insert(0, static_cast<Text*>(text->Clone()));
		this->undoTextArray->DeleteFromRear();
		Caret *tempCaret = new Caret(*caret);
		this->undoCaretArray->Insert(0, tempCaret);
		this->undoCaretArray->DeleteFromRear();
	}
}

Text* HistoryText::PopUndoText() {
	if (this->undoTextArray->GetLength() > 0) {
		Text *text = this->undoTextArray->GetAt(0);
		this->undoTextArray->Delete(0);

		return text;
	}
}

Caret* HistoryText::PopUndoCaret() {
	if (this->undoCaretArray->GetLength() > 0) {
		Caret *caret = this->undoCaretArray->GetAt(0);
		this->undoCaretArray->Delete(0);

		return caret;
	}
}

void HistoryText::PushRedo(Text *text, Caret *caret) {
	if (this->redoTextArray->GetCapacity() < 50) {
		this->redoTextArray->AppendFromFront(static_cast<Text*>(text->Clone()));
		Caret *tempCaret = new Caret(*caret);
		this->redoCaretArray->AppendFromFront(tempCaret);
	}
	else {
		this->redoTextArray->Insert(0, static_cast<Text*>(text->Clone()));
		this->redoTextArray->DeleteFromRear();
		Caret *tempCaret = new Caret(*caret);
		this->redoCaretArray->Insert(0, tempCaret);
		this->redoCaretArray->DeleteFromRear();
	}
}

Text* HistoryText::PopRedoText() {
	if (this->redoTextArray->GetLength() > 0) {
		Text *text = this->redoTextArray->GetAt(0);
		this->redoTextArray->Delete(0);

		return text;
	}
}

Caret* HistoryText::PopRedoCaret() {
	if (this->redoCaretArray->GetLength() > 0) {
		Caret *caret = this->redoCaretArray->GetAt(0);
		this->redoCaretArray->Delete(0);

		return caret;
	}
}

//#include <iostream>
//#include "SingleByteCharacter.h"
//#include "DoubleByteCharacter.h"
//#include "Row.h"
//#include "TextEdit.h"
//
//using namespace std;
//
//int main(int argc, char *argv[]) {
//	Figure *figure = 0;
//
//	TextEdit testTextEdit(figure);
//	HistoryText testHistoryText1;
//
//	Text testText1;
//	SingleByteCharacter testSingle1('1');
//	DoubleByteCharacter testDouble1("가");
//	Row testRow1;
//	testRow1.Add(testSingle1.Clone());
//	testRow1.Add(testDouble1.Clone());
//	testText1.Add(testRow1.Clone());
//
//	Text testText2;
//	SingleByteCharacter testSingle2('2');
//	DoubleByteCharacter testDouble2("나");
//	Row testRow2;
//	testRow2.Add(testSingle2.Clone());
//	testRow2.Add(testDouble2.Clone());
//	testText2.Add(testRow2.Clone());
//
//	Text testText3;
//	SingleByteCharacter testSingle3('3');
//	DoubleByteCharacter testDouble3("다");
//	Row testRow3;
//	testRow3.Add(testSingle3.Clone());
//	testRow3.Add(testDouble3.Clone());
//	testText3.Add(testRow3.Clone());
//
//	Text testText4;
//	SingleByteCharacter testSingle4('4');
//	DoubleByteCharacter testDouble4("라");
//	Row testRow4;
//	testRow4.Add(testSingle4.Clone());
//	testRow4.Add(testDouble4.Clone());
//	testText4.Add(testRow4.Clone());
//
//	Text testText5;
//	SingleByteCharacter testSingle5('5');
//	DoubleByteCharacter testDouble5("마");
//	Row testRow5;
//	testRow5.Add(testSingle5.Clone());
//	testRow5.Add(testDouble5.Clone());
//	testText5.Add(testRow5.Clone());
//
//	Text testText6;
//	SingleByteCharacter testSingle6('6');
//	DoubleByteCharacter testDouble6("바");
//	Row testRow6;
//	testRow6.Add(testSingle6.Clone());
//	testRow6.Add(testDouble6.Clone());
//	testText6.Add(testRow6.Clone());
//
//	cout << testText1.MakeText() << endl;
//	cout << testText2.MakeText() << endl;
//	cout << testText3.MakeText() << endl;
//	cout << testText4.MakeText() << endl;
//	cout << testText5.MakeText() << endl;
//	cout << testText6.MakeText() << endl << endl;
//
//	testHistoryText1.PushUndo(&testText1);
//	testHistoryText1.PushUndo(&testText2);
//	testHistoryText1.PushUndo(&testText3);
//	testHistoryText1.PushUndo(&testText4);
//	testHistoryText1.PushUndo(&testText5);
//	testHistoryText1.PushUndo(&testText6);
//
//	testHistoryText1.PushRedo(&testText1);
//	testHistoryText1.PushRedo(&testText2);
//	testHistoryText1.PushRedo(&testText3);
//	testHistoryText1.PushRedo(&testText4);
//	testHistoryText1.PushRedo(&testText5);
//	testHistoryText1.PushRedo(&testText6);
//
//	cout << testHistoryText1.undoTextArray->GetLength() << endl;
//	cout << testHistoryText1.undoTextArray->GetCapacity() << endl << endl;
//
//	int i = 0;
//	while (i < 5) {
//		//cout << testHistoryText1.undoTextArray->GetLength() << endl;
//		//cout << testHistoryText1.undoTextArray->GetCapacity() << endl;
//		testTextEdit.text = testHistoryText1.PopUndo();
//		cout << testTextEdit.text->MakeText() << endl;
//		cout << testHistoryText1.PopRedo()->MakeText() << endl;
//		i++;
//	}
//	cout << endl;
//
//	return 0;
//}
