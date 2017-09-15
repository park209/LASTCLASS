//Caret.h

#ifndef _CARET_H
#define _CARET_H

typedef signed long int Long;
class TextEdit;
class Caret {
public:
	Caret();
	Caret(Long x, Long y, TextEdit *textEdit);
	Caret(const Caret& source);
	~Caret();

	void MoveToIndex(Long characterIndex, Long rowIndex);

	Caret& operator = (const Caret& source);

	Long GetX();
	Long GetY();
private:
	TextEdit *textEdit;
	Long x;
	Long y;
};

inline Long Caret::GetX() {
	return this->x;
}
inline Long Caret::GetY() {
	return this->y;
}

#endif // _CARET_H