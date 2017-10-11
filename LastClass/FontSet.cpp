//FontSet.cpp

#include "FontSet.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"

FontSet::FontSet() {
	this->classDiagramForm = 0;
}

FontSet::FontSet(ClassDiagramForm *classDiagramForm) {
	this->classDiagramForm = classDiagramForm;
	this->lf.lfHeight = 25;										// 글꼴의 높이
	this->lf.lfWidth = 0;										// 글꼴의 너비
	this->lf.lfEscapement = 0;									// 방향
	this->lf.lfOrientation = 0;									// 회전각도
	this->lf.lfWeight = FW_NORMAL;								// 굵기
	this->lf.lfItalic = FALSE;									// 기울임꼴
	this->lf.lfUnderline = FALSE;								// 밑줄
	this->lf.lfStrikeOut = FALSE;								// 취소선
	this->lf.lfCharSet = DEFAULT_CHARSET;						// 문자 셋트
	this->lf.lfOutPrecision = OUT_CHARACTER_PRECIS;				//출력 정확도
	this->lf.lfClipPrecision = CLIP_CHARACTER_PRECIS;			// 클리핑 정확도
	this->lf.lfQuality = DEFAULT_QUALITY;						// 출력의 질
	this->lf.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;	// 자간
	strcpy(this->lf.lfFaceName, _T("맑은 고딕"));				//글꼴이름
	this->cFont.CreateFontIndirect(&this->lf);
	classDiagramForm->SetFont(&this->cFont, TRUE);
}

FontSet::FontSet(const FontSet& source) {
}

LOGFONT& FontSet::RelationFontSet() {
	this->lf.lfHeight = 13;										// 글꼴의 높이
	this->lf.lfWidth = 0;										// 글꼴의 너비
	this->lf.lfEscapement = 0;									// 방향
	this->lf.lfOrientation = 0;									// 회전각도
	this->lf.lfWeight = FW_NORMAL;								// 굵기
	this->lf.lfItalic = FALSE;									// 기울임꼴
	this->lf.lfUnderline = FALSE;								// 밑줄
	this->lf.lfStrikeOut = FALSE;								// 취소선
	this->lf.lfCharSet = DEFAULT_CHARSET;						// 문자 셋트
	this->lf.lfOutPrecision = OUT_CHARACTER_PRECIS;				//출력 정확도
	this->lf.lfClipPrecision = CLIP_CHARACTER_PRECIS;			// 클리핑 정확도
	this->lf.lfQuality = DEFAULT_QUALITY;						// 출력의 질
	this->lf.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;	// 자간
	strcpy(this->lf.lfFaceName, _T("굴림"));					//글꼴이름

	this->cFont.CreateFontIndirect(&this->lf);

	return this->lf;
}
LOGFONT& FontSet::ClassFontSet() {
	this->lf.lfHeight = 25;										// 글꼴의 높이
	this->lf.lfWidth = 0;										// 글꼴의 너비
	this->lf.lfEscapement = 0;									// 방향
	this->lf.lfOrientation = 0;									// 회전각도
	this->lf.lfWeight = FW_NORMAL;								// 굵기
	this->lf.lfItalic = FALSE;									// 기울임꼴
	this->lf.lfUnderline = FALSE;								// 밑줄
	this->lf.lfStrikeOut = FALSE;								// 취소선
	this->lf.lfCharSet = DEFAULT_CHARSET;						// 문자 셋트
	this->lf.lfOutPrecision = OUT_CHARACTER_PRECIS;				//출력 정확도
	this->lf.lfClipPrecision = CLIP_CHARACTER_PRECIS;			// 클리핑 정확도
	this->lf.lfQuality = DEFAULT_QUALITY;						// 출력의 질
	this->lf.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;	// 자간
	strcpy(this->lf.lfFaceName, _T("맑은 고딕"));				//글꼴이름

	this->cFont.CreateFontIndirect(&this->lf);

	return this->lf;
}

CFont& FontSet::SetFont(TextEdit *textEdit, CDC *pDC) {
	textEdit->SetFont(&this->cFont, TRUE);
	this->oldFont = pDC->SelectObject(&this->cFont);

	return static_cast<CFont&>(this->cFont);
}

FontSet::~FontSet() {
}