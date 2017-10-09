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
}

HistoryGraphic::HistoryGraphic(const HistoryGraphic& source) {
	this->undoGraphicArray = source.undoGraphicArray;
	this->redoGraphicArray = source.redoGraphicArray;
}

HistoryGraphic::~HistoryGraphic() {
	delete this->undoGraphicArray;
	delete this->redoGraphicArray;
}

void HistoryGraphic::PushUndo(Diagram *diagram) {
	
	if (this->undoGraphicArray->GetCapacity() < 50) {
		this->undoGraphicArray->AppendFromFront(static_cast<Diagram*>(diagram->Clone()));
	}
	else {
		this->undoGraphicArray->Insert(0, static_cast<Diagram*>(diagram->Clone()));
		this->undoGraphicArray->DeleteFromRear();
	}
}

Diagram* HistoryGraphic::PopUndoGraphic(){
	Diagram *diagram=0;
	if (this->undoGraphicArray->GetLength() > 0) {
		diagram = this->undoGraphicArray->GetAt(0);
		this->undoGraphicArray->Delete(0);
	}
	return diagram;
}

void HistoryGraphic::PushRedo(Diagram *diagram){
	
	if (this->redoGraphicArray->GetCapacity() < 50) {
		this->redoGraphicArray->AppendFromFront(static_cast<Diagram*>(diagram->Clone()));
	}
	else {
		this->redoGraphicArray->Insert(0, static_cast<Diagram*>(diagram->Clone()));
		this->redoGraphicArray->DeleteFromRear();
	}
}

Diagram* HistoryGraphic::PopRedoGraphic(){
	Diagram *diagram = 0;
	if (this->redoGraphicArray->GetLength() > 0) {
		diagram = this->redoGraphicArray->GetAt(0);
		this->redoGraphicArray->Delete(0);
	}
	return diagram;
}
