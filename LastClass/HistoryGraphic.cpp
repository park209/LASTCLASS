//HistoryGraphic.cpp

#include "HistoryGraphic.h"
#include "Diagram.h"
#include "Text.h"

HistoryGraphic* HistoryGraphic::instance = 0;

HistoryGraphic* HistoryGraphic::Instance() {
	if (instance == 0) {
		instance = new HistoryGraphic;
	}
	return instance;
}

HistoryGraphic::HistoryGraphic() {
	this->undoGraphicArray = new Array<Diagram*>(0);
	this->redoGraphicArray = new Array<Diagram*>(0);
	//this->undoGraphicTextArray = new Array<Text*>(0);
	//this->redoGraphicTextArray = new Array<Text*>(0);

}

HistoryGraphic::HistoryGraphic(const HistoryGraphic& source) {
	this->undoGraphicArray = source.undoGraphicArray;
	this->redoGraphicArray = source.redoGraphicArray;
	//this->undoGraphicTextArray = source.undoGraphicTextArray;
	//this->redoGraphicTextArray = source.redoGraphicTextArray;
}

HistoryGraphic::~HistoryGraphic() {
	delete this->undoGraphicArray;
	delete this->redoGraphicArray;
	//delete this->undoGraphicTextArray;
	//delete this->redoGraphicTextArray;
}

void HistoryGraphic::PushUndo(Diagram *diagram) {//, Text *text) {
	
	if (this->undoGraphicArray->GetCapacity() < 50) {
		this->undoGraphicArray->AppendFromFront(static_cast<Diagram*>(diagram->Clone()));
		//this->undoGraphicTextArray->AppendFromFront(static_cast<Text*>(text->Clone()));
	}
	else {
		this->undoGraphicArray->Insert(0, static_cast<Diagram*>(diagram->Clone()));
		this->undoGraphicArray->DeleteFromRear();
		//this->undoGraphicTextArray->Insert(0, static_cast<Text*>(text->Clone()));
		//this->undoGraphicTextArray->DeleteFromRear();
	}
}

Diagram* HistoryGraphic::PopUndoGraphic(){//Diagram *diagram, Text *text) {
	if (this->undoGraphicArray->GetLength() > 0) {
		Diagram *diagram;
		diagram = this->undoGraphicArray->GetAt(0);
		this->undoGraphicArray->Delete(0);
		//text = this->undoGraphicTextArray->GetAt(0);
		//this->undoGraphicTextArray->Delete(0);

		return diagram;
	}
}


void HistoryGraphic::PushRedo(Diagram *diagram){//, Text *text) {
	
	if (this->redoGraphicArray->GetCapacity() < 50) {
		this->redoGraphicArray->AppendFromFront(static_cast<Diagram*>(diagram->Clone()));
		//this->redoGraphicTextArray->AppendFromFront(static_cast<Text*>(text->Clone()));
	}
	else {
		this->redoGraphicArray->Insert(0, static_cast<Diagram*>(diagram->Clone()));
		this->redoGraphicArray->DeleteFromRear();
		//this->redoGraphicTextArray->Insert(0, static_cast<Text*>(text->Clone()));
		//this->redoGraphicTextArray->DeleteFromRear();
	}
}

Diagram* HistoryGraphic::PopRedoGraphic(){//Diagram *diagram, Text *text) {
	if (this->redoGraphicArray->GetLength() > 0) {
		Diagram *diagram;
		diagram = this->redoGraphicArray->GetAt(0);
		this->redoGraphicArray->Delete(0);
		//text = this->redoGraphicTextArray->GetAt(0);
		//this->redoGraphicTextArray->Delete(0);
		return diagram;
	}
}
