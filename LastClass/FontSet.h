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
	FontSet(LOGFONT *lf);
	FontSet(const FontSet& source);
	~FontSet();

	LOGFONT& RelationFontSet();
private:
	LOGFONT lf;
};

#endif // _FONTSET_H