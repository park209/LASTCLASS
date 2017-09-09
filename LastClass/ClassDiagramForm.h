
//ClassDiagramForm.h

#ifndef _CLASSDIAGRAM_H
#define _CLASSDIAGRAM_H

#include <afxwin.h>

typedef signed long int Long;

class Diagram; //전방선언
class Text;
class ClassDiagramForm : public CFrameWnd { //CFrameWnd 에 상속관계 표기
public:
	Diagram *diagram;
	Text *text;
public:
	ClassDiagramForm(); // 이건 생성자????
public:
	Long Save();
	Long Load();
	//void FindLinePoints(Long firstClass, Long secondClass ,Long startX, Long startY, Long currentX, Long currentY, Long  *lineStartX, Long *lineStartY, Long *lineEndX, Long *lineEndY);

	bool FindCrossPoint(const CPoint& line1Start, const CPoint& line1End, const CPoint& line2Start, const CPoint& line2End, CPoint *crossPoint);

private:
	Long startX;
	Long startY;
	Long currentX;
	Long currentY;
	Long rowIndex;
	Long characterIndex;
	Long selected;
	bool classButton;	//임시버튼
	bool relationButton;	//임시버튼
	bool generalizationButton; //일반화
	bool realizationButton; //실체화
	bool dependencyButton; //의존
	bool associationButton; //연관화
	bool directedAssociationButton; //직접연관
	bool aggregationButton; // 집합
	bool aggregationSButton; // 집합연관
	bool compositionButton; // 합성
	bool compositionSBtton; // 복합연관
	bool templateButton; //템플릿기호
	bool memoBoxButton; //메모박스

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
};

#endif // _CLASSDIAGRAM_H
