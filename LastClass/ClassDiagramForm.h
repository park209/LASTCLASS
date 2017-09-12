
//ClassDiagramForm.h

#ifndef _CLASSDIAGRAM_H
#define _CLASSDIAGRAM_H

#include <afxwin.h>

typedef signed long int Long;

class Diagram; //���漱��
class Text;
class TextEdit;
class Selection;
class DrawingController;
class ClassDiagramForm : public CFrameWnd { //CFrameWnd �� ��Ӱ��� ǥ��
public:
	Diagram *diagram;
	Text *text;
	TextEdit *textEdit;
	Selection *selection;
	Long currentClassIndex;
	DrawingController *drawingController;
public:
	ClassDiagramForm();
public:
	Long Save();
	Long Load();
	Long TextSave();
	Long TextLoad();
	//void FindLinePoints(Long firstClass, Long secondClass ,Long startX, Long startY, Long currentX, Long currentY, Long  *lineStartX, Long *lineStartY, Long *lineEndX, Long *lineEndY);
	bool FindCrossPoint(const CPoint& line1Start, const CPoint& line1End, const CPoint& line2Start, const CPoint& line2End, CPoint *crossPoint);
public:
	Long GetRowIndex() const;
	Long GetCharacterIndex() const;
	Long GetCurrentClassIndex()const;
private:
	Long startX;
	Long startY;
	Long currentX;
	Long currentY;
	Long rowIndex;
	Long characterIndex;
	//Long selected;
	bool classButton;	//�ӽù�ư
	bool relationButton;	//�ӽù�ư
	bool generalizationButton; //�Ϲ�ȭ
	bool realizationButton; //��üȭ
	bool dependencyButton; //����
	bool associationButton; //����ȭ
	bool directedAssociationButton; //��������
	bool aggregationButton; // ����
	bool aggregationSButton; // ���տ���
	bool compositionButton; // �ռ�
	bool compositionSBtton; // ���տ���
	bool templateButton; //���ø���ȣ
	bool memoBoxButton; //�޸�ڽ�
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDoubleClicked(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
};

inline Long ClassDiagramForm::GetRowIndex() const {
	return this->rowIndex;
}
inline Long ClassDiagramForm::GetCharacterIndex() const {
	return this->characterIndex;
}
inline Long ClassDiagramForm::GetCurrentClassIndex()const {
	return this->currentClassIndex;
}

#endif // _CLASSDIAGRAM_H
