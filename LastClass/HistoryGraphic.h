//HistoryGraphic.h

#ifndef _HISTORYGRAPHIC_H
#define _HISTORYGRAPHIC_H

#include "Array.h"

typedef signed long int Long;

class Diagram;

class HistoryGraphic {
public:
	static HistoryGraphic* Instance();

	HistoryGraphic();
	HistoryGraphic(const HistoryGraphic& source);
	~HistoryGraphic();

	void PushUndo(Diagram *diagram);
	Diagram* PopUndoGraphic();

	void PushRedo(Diagram *diagram);
	Diagram* PopRedoGraphic();

public:
	Array<Diagram*>*undoGraphicArray;
	Array<Diagram*>*redoGraphicArray;

	static HistoryGraphic* instance;
};


#endif //!_HISTORYGRAPHIC_H
