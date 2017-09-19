//FlagSet.h
#ifndef _FLAGSET_H
#define _FLAGSET_H

typedef signed long int Long;

class textEdit;
class FlagSet {
public:
	bool ConvertKoreanEnglish();
	bool ConvertFlagInsert();
	bool Convert();
private:
	Long koreanEnglish;//flag
	Long flagInsert;//flag
	Long flagBuffer;//flag
};

#endif // !_FLAGSET_H
