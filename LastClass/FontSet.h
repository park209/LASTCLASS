//FontSet.h

#ifndef _FONTSET_H
#define _FONTSET_H

#include <string>
#include <afxwin.h>

using namespace std;

typedef signed long int Long;

class ClassDiagramForm;
class TextEdit;
class FontSet {
public:
	FontSet();
	FontSet(ClassDiagramForm *classDiagramForm);
	FontSet(const FontSet& source);
	~FontSet();

	LOGFONT& RelationFontSet();
	LOGFONT& ClassFontSet();
	CFont& SetFont(TextEdit* textEdit, CDC* pDC);
	
	CFont& GetCFont() const;
public:
private:
	ClassDiagramForm *classDiagramForm;
	CFont cFont;
	CFont *oldFont;
	LOGFONT lf;
};

inline CFont& FontSet::GetCFont() const {
	return const_cast<CFont&>(this->cFont);
}

#endif // _FONTSET_H