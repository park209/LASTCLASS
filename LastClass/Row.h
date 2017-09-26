//Row.h

#ifndef _ROW_H
#define _ROW_H

#include "TextComposite.h"
#include <afxwin.h>
#include <string>

typedef signed long int Long;

using namespace std;

class TextComponent;
class Row;
class Character;
class Visitor;
class Row : public TextComposite {
public:
	Row(Long capacity = 128);
	Row(const Row& source);
	virtual ~Row();

	Long Add(Character *character);
	virtual Long Add(TextComponent *textComponent);
	Long Modify(Long index, TextComponent *textComponent);
	virtual Long Remove(Long index);
	virtual Long Insert(Long index, TextComponent *textComponent);
	string PrintRowString();
	Long GetRowWidth(CDC* cPaintDc, Long to ,Long from = 0);
	Character* GetAt(Long index);

	virtual TextComponent* Clone() const;

	Row& operator = (const Row& source);
	Character* operator [] (Long index);
};

#endif // _ROW_H