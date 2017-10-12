//FontSet.cpp

#include "FontSet.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"

FontSet::FontSet() {
	this->lf = { 0, };
}

FontSet::FontSet(LOGFONT *lf) { // ClassDiagramForm->OnCreate
	//Set Default
	lf->lfHeight = 25;										// 글꼴의 높이
	lf->lfWidth = 0;										// 글꼴의 너비
	lf->lfEscapement = 0;									// 방향
	lf->lfOrientation = 0;									// 회전각도
	lf->lfWeight = FW_NORMAL;								// 굵기
	lf->lfItalic = FALSE;									// 기울임꼴
	lf->lfUnderline = FALSE;								// 밑줄
	lf->lfStrikeOut = FALSE;								// 취소선
	lf->lfCharSet = DEFAULT_CHARSET;						// 문자 셋트
	lf->lfOutPrecision = OUT_CHARACTER_PRECIS;				//출력 정확도
	lf->lfClipPrecision = CLIP_CHARACTER_PRECIS;			// 클리핑 정확도
	lf->lfQuality = DEFAULT_QUALITY;						// 출력의 질
	lf->lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;		// 자간
	strcpy(lf->lfFaceName, _T("맑은 고딕"));				//글꼴이름
}

FontSet::FontSet(const FontSet& source) {
}

LOGFONT& FontSet::RelationFontSet() {
	//Set Default
	lf.lfHeight = 13;										// 글꼴의 높이
	lf.lfWidth = 0;											// 글꼴의 너비
	lf.lfEscapement = 0;									// 방향
	lf.lfOrientation = 0;									// 회전각도
	lf.lfWeight = FW_NORMAL;								// 굵기
	lf.lfItalic = FALSE;									// 기울임꼴
	lf.lfUnderline = FALSE;									// 밑줄
	lf.lfStrikeOut = FALSE;									// 취소선
	lf.lfCharSet = DEFAULT_CHARSET;							// 문자 셋트
	lf.lfOutPrecision = OUT_CHARACTER_PRECIS;				//출력 정확도
	lf.lfClipPrecision = CLIP_CHARACTER_PRECIS;				// 클리핑 정확도
	lf.lfQuality = DEFAULT_QUALITY;							// 출력의 질
	lf.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;		// 자간
	strcpy(lf.lfFaceName, _T("굴림"));					//글꼴이름

	return lf;
}

FontSet::~FontSet() {
}