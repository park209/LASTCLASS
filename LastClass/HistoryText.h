//HistoryText.h

#ifndef _HISTORYTEXT_H
#define _HISTORYTEXT_H

//#include <afxwin.h>
#include "Array.h"

class Text;
class HistoryText {
public:
	HistoryText();
	HistoryText(const HistoryText& source);
	~HistoryText();

	void PushUndo(Text *text);
	Text* PopUndo();

	void PushRedo(Text *text);
	Text* PopRedo();

	Text* GetUndoArray() const;
	Text* GetRedoArray() const;
//private:
	Array<Text*>*undoArray;
	Array<Text*>*redoArray;
};

inline Text* HistoryText::GetUndoArray() const {
	// 필요하면 배열 전체 나중에
}
inline Text* HistoryText::GetRedoArray() const {
	// 필요하면 배열 전체 나중에
}

#endif // _HISTORYTEXT_H
