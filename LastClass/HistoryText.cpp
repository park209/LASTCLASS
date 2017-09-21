//HistoryText.cpp

#include "HistoryText.h"
#include "Text.h"

HistoryText::HistoryText() {
	this->undoArray = new Array<Text*>(0);
	this->redoArray = new Array<Text*>(0);
}

HistoryText::HistoryText(const HistoryText& source) {
	this->undoArray = source.undoArray;
	this->redoArray = source.redoArray;
}

HistoryText::~HistoryText() {
}

void HistoryText::PushUndo(Text *text) {
	if (this->undoArray->GetCapacity() < 100) {
		this->undoArray->AppendFromFront(static_cast<Text*>(text->Clone()));
	}
	else {
		this->undoArray->Insert(0, static_cast<Text*>(text->Clone()));
		this->undoArray->DeleteFromRear();
	}
}

Text* HistoryText::PopUndo() {
	if (this->undoArray->GetLength() > 0) {
		Text *text = this->undoArray->GetAt(0);
		this->undoArray->Delete(0);

		return text;
	}
}

void HistoryText::PushRedo(Text *text) {
	if (this->redoArray->GetCapacity() < 100) {
		this->redoArray->AppendFromFront(static_cast<Text*>(text->Clone()));
	}
	else {
		this->redoArray->Insert(0, static_cast<Text*>(text->Clone()));
		this->redoArray->DeleteFromRear();
	}
}

Text* HistoryText::PopRedo() {
	if (this->redoArray->GetLength() > 0) {
		Text *text = this->redoArray->GetAt(0);
		this->redoArray->Delete(0);

		return text;
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
//	cout << testHistoryText1.undoArray->GetLength() << endl;
//	cout << testHistoryText1.undoArray->GetCapacity() << endl << endl;
//
//	int i = 0;
//	while (i < 5) {
//		//cout << testHistoryText1.undoArray->GetLength() << endl;
//		//cout << testHistoryText1.undoArray->GetCapacity() << endl;
//		testTextEdit.text = testHistoryText1.PopUndo();
//		cout << testTextEdit.text->MakeText() << endl;
//		cout << testHistoryText1.PopRedo()->MakeText() << endl;
//		i++;
//	}
//	cout << endl;
//
//	return 0;
//}
