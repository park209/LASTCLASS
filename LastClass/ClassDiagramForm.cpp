//ClassDiagramForm.cpp

#include "ClassDiagramForm.h"
#include "TextEdit.h"
#include "Diagram.h"
#include "Class.h"
#include "MemoBox.h"
#include "Selection.h"
#include "Template.h"
#include "ClassName.h"
#include "Method.h"
#include "Attribute.h"
#include "Reception.h"
#include "Line.h"
#include "Generalization.h"
#include "Realization.h"
#include "Dependency.h"
#include "Association.h"
#include "DirectedAssociation.h"
#include "Aggregation.h"
#include "Aggregations.h"
#include "Composition.h"
#include "Compositions.h"
#include "MemoLine.h"
#include "SelfAggregation.h"
#include "SelfAggregations.h"
#include "SelfAssociation.h"
#include "SelfComposition.h"
#include "SelfCompositions.h"
#include "SelfDependency.h"
#include "SelfDirectedAssociation.h"
#include "SelfGeneralization.h"
#include "SelfRelation.h"
#include "Figure.h"
#include "FigureFactory.h"
#include "DrawingVisitor.h"
#include "WritingVisitor.h"
#include "MovingVisitor.h"
#include "MouseLButton.h"
#include "HistoryGraphic.h"
#include "Scroll.h"
#include "VerticalScrollBar.h"
#include "HorizontalScrollBar.h"
#include "KeyBoard.h"
#include "KeyAction.h"
#include "VScrollCreator.h"
#include "ScrollAction.h"
#include "HScrollCreator.h"
#include <math.h>
#include <iostream>
#include <fstream>
using namespace std;


BEGIN_MESSAGE_MAP(ClassDiagramForm, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
	ON_WM_SETFOCUS()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_CLOSE()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
END_MESSAGE_MAP()

ClassDiagramForm::ClassDiagramForm() { // ������ �´µ�
	this->diagram = NULL;
	this->textEdit = NULL;
	this->selection = NULL;
	this->mouseLButton = NULL;
	this->verticalScrollBar = NULL;
	this->horizontalScroll = NULL;
	this->keyBoard = NULL;
	this->historyGraphic = NULL;
	this->startX = 0;
	this->startY = 0;
	this->currentX = 0;
	this->currentY = 0;
}

Long ClassDiagramForm::Load() {
	Long position = -1;
	Long i;
	Long x;
	Long y;
	Long width;
	Long height;
	Long length;
	Long lineX;
	Long lineY;
	Long lineWidth;
	Long lineHeight;
	Long index;
	ifstream fClass;
	ifstream fLine;
	Long type;
	Long relationLength;
	Long relationEndX;
	Long relationEndY;
	FigureFactory factory;
	Figure *figure;

	fClass.open("ClassSave.txt");
	fLine.open("LineSave.txt");
	//���� ������ ���� ������ ĭ 
	// 0 = Class, 1 = MemoBox, 2 = Line, 3 = Template, 4 = Generalization(�Ϲ�ȭ), 5 = Realization(��üȭ), 6 = Dependency(����), 7 = Association(����ȭ),
	// 8 = DirectedAssociation(��������),  9 = Aggregation(����), 10 = Aggregations(���տ���), 11 =  Composition(�ռ�), 12 = Compositions(���տ���), 13 = MemoLine
	// 14 = ClassName , 15 = Attribute , 16 = Method , 17 = Reception

	if (fClass.is_open() && fLine.is_open()) {
		fClass >> length >> x >> y >> width >> height >> type;
		while (!fClass.eof()) {
			figure = factory.Create(x, y, width, height, type);
			position = this->diagram->Add(figure);

			FigureComposite *figureComposite = static_cast<FigureComposite*>(this->diagram->GetAt(position));
			i = 0;
			while (position != -1 && i < length) {
				fLine >> lineX >> lineY >> lineWidth >> lineHeight >> type >> relationLength;

				figure = factory.Create(lineX, lineY, lineWidth, lineHeight, type);
				index = figureComposite->Add(figure);
				if (dynamic_cast<Relation*>(figureComposite->GetAt(index))) {
					Relation *relation = static_cast<Relation*>(figureComposite->GetAt(index));
					CPoint startCPoint;
					CPoint currentCPoint;
					Long j = 0;
					while (j < relationLength) {
						fLine >> relationEndX >> relationEndY;
						startCPoint.x = x;
						startCPoint.y = y;
						currentCPoint.x = relationEndX;
						currentCPoint.y = relationEndY;
						relation->Add(startCPoint, currentCPoint);
						j++;
					}
				}
				i++;
			}
			fClass >> length >> x >> y >> width >> height >> type;
		}
		fClass.close();
		fLine.close();
	}
	return this->diagram->GetLength();
}

Long ClassDiagramForm::Save() {
	Long k;
	Long i = 0;
	Long j;
	Long rowLength;
	Long fontSize;
	ofstream fClass;
	ofstream fLine; // �������� ofstream

	fClass.open("ClassSave.txt");
	fLine.open("LineSave.txt");
	if (fClass.is_open() && fLine.is_open()) {
		while (i < this->diagram->GetLength()) {
			//���� ������ ���� ������ ĭ 
			// 0 = Class, 1 = MemoBox, 2 = Line, 3 = Template, 4 = Generalization(�Ϲ�ȭ), 5 = Realization(��üȭ), 
			//6 = Dependency(����), 7 = Association(����ȭ),
			// 8 = DirectedAssociation(��������),  9 = Aggregation(����), 10 = Aggregations(���տ���), 
			//11 =  Composition(�ռ�), 12 = Compositions(���տ���), 13 = MemoLine
			// 14 = ClassName , 15 = Attribute , 16 = Method , 17 = Reception , 18 =SelfGeneralization ,
			//19 = SelfDependency , 20 = SelfAssociation , 21 = SelfDirectedAssociation
			// 22 = SelfAggregation , 23 = SelfAggregations , 24 =SelfComposition , 25 = SelfCompositions
			FigureComposite *object = 0;
			if (dynamic_cast<Class*>(this->diagram->GetAt(i))) {
				object = static_cast<FigureComposite*>(this->diagram->GetAt(i));
				fClass << object->GetLength() << " " << object->GetX() << " " << object->GetY()
					<< " " << object->GetWidth() << " " << object->GetHeight() << " " << 0 << endl;
			}

			else if (dynamic_cast<MemoBox*>(this->diagram->GetAt(i))) {
				object = static_cast<FigureComposite*>(this->diagram->GetAt(i));
				fontSize = object->GetFontSize();
				rowLength = object->GetRowCount(object->GetContent());
				fClass << object->GetLength() << " " << object->GetX() << " " << object->GetY()
					<< " " << object->GetWidth() << " " << object->GetHeight() << " " << 1 << " " << fontSize << " " << rowLength << endl;
			}
			j = 0;
			while (j < object->GetLength()) {
				Figure *figure;
				CPoint cPoint;
				if (dynamic_cast<Line*>(object->GetAt(j))) {
					figure = object->GetAt(j);
					fLine << figure->GetX() << " " << figure->GetY() << " " <<
						figure->GetWidth() << " " << figure->GetHeight() << " " << 2 << " " << 0 << endl;
				}

				else if (dynamic_cast<Template*>(object->GetAt(j))) {
					figure = object->GetAt(j);
					fontSize = object->GetFontSize();
					rowLength = object->GetRowCount(object->GetContent());
					fLine << figure->GetX() << " " << figure->GetY() << " " <<
						figure->GetWidth() << " " << figure->GetHeight() << " " << 3 << " " << fontSize << " " << rowLength << endl;
					fLine << object->GetContent() << endl;
				}

				else if (dynamic_cast<Generalization*>(object->GetAt(j))) {
					Relation *relation = static_cast<Relation*>(object->GetAt(j));
					fontSize = object->GetFontSize();
					rowLength = object->GetRowCount(object->GetContent());
					fLine << relation->GetX() << " " << relation->GetY() << " " <<
						relation->GetWidth() << " " << relation->GetHeight() << " " << 4 << " " << relation->GetLength() << endl;
					k = 0;
					while (k < relation->GetLength()) {
						cPoint = relation->GetAt(k);
						fLine << cPoint.x << " " << cPoint.y << endl;
						k++;
					}
				}

				else if (dynamic_cast<Realization*>(object->GetAt(j))) {
					Relation *relation = static_cast<Relation*>(object->GetAt(j));
					fLine << relation->GetX() << " " << relation->GetY() << " " <<
						relation->GetWidth() << " " << relation->GetHeight() << " " << 5 << " " << relation->GetLength() << endl;
					k = 0;
					while (k < relation->GetLength()) {
						cPoint = relation->GetAt(k);
						fLine << cPoint.x << " " << cPoint.y << endl;
						k++;
					}
				}

				else if (dynamic_cast<Dependency*>(object->GetAt(j))) {
					Relation *relation = static_cast<Relation*>(object->GetAt(j));
					fLine << relation->GetX() << " " << relation->GetY() << " " <<
						relation->GetWidth() << " " << relation->GetHeight() << " " << 6 << " " << relation->GetLength() << endl;
					k = 0;
					while (k < relation->GetLength()) {
						cPoint = relation->GetAt(k);
						fLine << cPoint.x << " " << cPoint.y << endl;
						k++;
					}
				}

				else if (dynamic_cast<Association*>(object->GetAt(j))) {
					Relation *relation = static_cast<Relation*>(object->GetAt(j));
					fLine << relation->GetX() << " " << relation->GetY() << " " <<
						relation->GetWidth() << " " << relation->GetHeight() << " " << 7 << " " << relation->GetLength() << endl;
					k = 0;
					while (k < relation->GetLength()) {
						cPoint = relation->GetAt(k);
						fLine << cPoint.x << " " << cPoint.y << endl;
						k++;
					}
				}

				else if (dynamic_cast<DirectedAssociation*>(object->GetAt(j))) {
					Relation *relation = static_cast<Relation*>(object->GetAt(j));
					fLine << relation->GetX() << " " << relation->GetY() << " " <<
						relation->GetWidth() << " " << relation->GetHeight() << " " << 8 << " " << relation->GetLength() << endl;
					k = 0;
					while (k < relation->GetLength()) {
						cPoint = relation->GetAt(k);
						fLine << cPoint.x << " " << cPoint.y << endl;
						k++;
					}
				}

				else if (dynamic_cast<Aggregation*>(object->GetAt(j))) {
					Relation *relation = static_cast<Relation*>(object->GetAt(j));
					fLine << relation->GetX() << " " << relation->GetY() << " " <<
						relation->GetWidth() << " " << relation->GetHeight() << " " << 9 << " " << relation->GetLength() << endl;
					k = 0;
					while (k < relation->GetLength()) {
						cPoint = relation->GetAt(k);
						fLine << cPoint.x << " " << cPoint.y << endl;
						k++;
					}
				}

				else if (dynamic_cast<Aggregations*>(object->GetAt(j))) {
					Relation *relation = static_cast<Relation*>(object->GetAt(j));
					fLine << relation->GetX() << " " << relation->GetY() << " " <<
						relation->GetWidth() << " " << relation->GetHeight() << " " << 10 << " " << relation->GetLength() << endl;
					k = 0;
					while (k < relation->GetLength()) {
						cPoint = relation->GetAt(k);
						fLine << cPoint.x << " " << cPoint.y << endl;
						k++;
					}
				}

				else if (dynamic_cast<Composition*>(object->GetAt(j))) {
					Relation *relation = static_cast<Relation*>(object->GetAt(j));
					fLine << relation->GetX() << " " << relation->GetY() << " " <<
						relation->GetWidth() << " " << relation->GetHeight() << " " << 11 << " " << relation->GetLength() << endl;
					k = 0;
					while (k < relation->GetLength()) {
						cPoint = relation->GetAt(k);
						fLine << cPoint.x << " " << cPoint.y << endl;
						k++;
					}
				}
				else if (dynamic_cast<Compositions*>(object->GetAt(j))) {
					Relation *relation = static_cast<Relation*>(object->GetAt(j));
					fLine << relation->GetX() << " " << relation->GetY() << " " <<
						relation->GetWidth() << " " << relation->GetHeight() << " " << 12 << " " << relation->GetLength() << endl;
					k = 0;
					while (k < relation->GetLength()) {
						cPoint = relation->GetAt(k);
						fLine << cPoint.x << " " << cPoint.y << endl;
						k++;
					}
				}

				else if (dynamic_cast<MemoLine*>(object->GetAt(j))) {
					Relation *relation = static_cast<Relation*>(object->GetAt(j));
					fLine << relation->GetX() << " " << relation->GetY() << " " <<
						relation->GetWidth() << " " << relation->GetHeight() << " " << 13 << " " << relation->GetLength() << endl;
					k = 0;
					while (k < relation->GetLength()) {
						cPoint = relation->GetAt(k);
						fLine << cPoint.x << " " << cPoint.y << endl;
						k++;
					}
				}
				else if (dynamic_cast<ClassName*>(object->GetAt(j))) {
					figure = static_cast<ClassName*>(object->GetAt(j));
					fontSize = object->GetFontSize();
					rowLength = object->GetRowCount(object->GetContent());
					fLine << figure->GetX() << " " << figure->GetY() << " " << figure->GetWidth() << " "
						<< figure->GetHeight() << " " << 14 <<
						" " << fontSize << " " << rowLength << endl;
					fLine << object->GetContent() << endl;
				}
				else if (dynamic_cast<Attribute*>(object->GetAt(j))) {
					figure = static_cast<Attribute*>(object->GetAt(j));
					fontSize = object->GetFontSize();
					rowLength = object->GetRowCount(object->GetContent());
					fLine << figure->GetX() << " " << figure->GetY() << " " << figure->GetWidth() << " "
						<< figure->GetHeight() << " " << 15 <<
						" " << fontSize << " " << rowLength << endl;
					fLine << object->GetContent() << endl;
				}
				else if (dynamic_cast<Method*>(object->GetAt(j))) {
					figure = static_cast<Method*>(object->GetAt(j));
					fontSize = object->GetFontSize();
					rowLength = object->GetRowCount(object->GetContent());
					fLine << figure->GetX() << " " << figure->GetY() << " " << figure->GetWidth() << " "
						<< figure->GetHeight() << " " << 16 <<
						" " << fontSize << " " << rowLength << endl;
					fLine << object->GetContent() << endl;
				}
				else if (dynamic_cast<Reception*>(object->GetAt(j))) {
					figure = static_cast<Reception*>(object->GetAt(j));
					fontSize = object->GetFontSize();
					rowLength = object->GetRowCount(object->GetContent());
					fLine << figure->GetX() << " " << figure->GetY() << " " << figure->GetWidth() << " "
						<< figure->GetHeight() << " " << 17 <<
						" " << fontSize << " " << rowLength << endl;
					fLine << object->GetContent() << endl;
				}
				else if (dynamic_cast<SelfGeneralization*>(object->GetAt(j))) {
					figure = static_cast<SelfRelation*>(object->GetAt(j));
					fLine << figure->GetX() << " " << figure->GetY() << " " << figure->GetWidth() << " "
						<< figure->GetHeight() << " " << 18 <<
						" " << 0 << endl;

				}
				else if (dynamic_cast<SelfDependency*>(object->GetAt(j))) {
					figure = static_cast<SelfRelation*>(object->GetAt(j));
					fLine << figure->GetX() << " " << figure->GetY() << " " << figure->GetWidth() << " "
						<< figure->GetHeight() << " " << 19 <<
						" " << 0 << endl;

				}
				else if (dynamic_cast<SelfAssociation*>(object->GetAt(j))) {
					figure = static_cast<SelfRelation*>(object->GetAt(j));
					fLine << figure->GetX() << " " << figure->GetY() << " " << figure->GetWidth() << " "
						<< figure->GetHeight() << " " << 20 <<
						" " << 0 << endl;

				}
				else if (dynamic_cast<SelfDirectedAssociation*>(object->GetAt(j))) {
					figure = static_cast<SelfRelation*>(object->GetAt(j));
					fLine << figure->GetX() << " " << figure->GetY() << " " << figure->GetWidth() << " "
						<< figure->GetHeight() << " " << 21 <<
						" " << 0 << endl;

				}
				else if (dynamic_cast<SelfAggregation*>(object->GetAt(j))) {
					figure = static_cast<SelfRelation*>(object->GetAt(j));
					fLine << figure->GetX() << " " << figure->GetY() << " " << figure->GetWidth() << " "
						<< figure->GetHeight() << " " << 22 <<
						" " << 0 << endl;

				}
				else if (dynamic_cast<SelfAggregations*>(object->GetAt(j))) {
					figure = static_cast<SelfRelation*>(object->GetAt(j));
					fLine << figure->GetX() << " " << figure->GetY() << " " << figure->GetWidth() << " "
						<< figure->GetHeight() << " " << 23 <<
						" " << 0 << endl;

				}
				else if (dynamic_cast<SelfComposition*>(object->GetAt(j))) {
					figure = static_cast<SelfRelation*>(object->GetAt(j));
					fLine << figure->GetX() << " " << figure->GetY() << " " << figure->GetWidth() << " "
						<< figure->GetHeight() << " " << 24 <<
						" " << 0 << endl;

				}
				else if (dynamic_cast<SelfCompositions*>(object->GetAt(j))) {
					figure = static_cast<SelfRelation*>(object->GetAt(j));
					fLine << figure->GetX() << " " << figure->GetY() << " " << figure->GetWidth() << " "
						<< figure->GetHeight() << " " << 25 <<
						" " << 0 << endl;

				}
				j++;
			}
			i++;
		}
		fClass.close();
		fLine.close();
	}
	return this->diagram->GetLength();
}

int ClassDiagramForm::OnCreate(LPCREATESTRUCT lpCreateStruct) {

	CFrameWnd::OnCreate(lpCreateStruct); //�ڵ����� �������̵� //��ӿ���
										 //1.1. ���̾�׷��� �غ��Ѵ�
	this->diagram = new Diagram();
	this->selection = new Selection;
	this->mouseLButton = new MouseLButton;
	this->historyGraphic = new HistoryGraphic;

	this->verticalScrollBar = new VerticalScrollBar(this);
	this->horizontalScroll = new HorizontalScrollBar(this);
	this->keyBoard = new KeyBoard;

	//1.2. �����Ѵ�
	//this->Load();

	//1.3. �����츦 �����Ѵ�
	Invalidate();

	return 0;
}

void ClassDiagramForm::OnPaint() {
	CPaintDC dc(this);
	CRect rect;
	this->GetClientRect(&rect);
	CDC memDC;
	CBitmap *pOldBitmap;
	CBitmap bitmap;
	memDC.CreateCompatibleDC(&dc);
	bitmap.CreateCompatibleBitmap(&dc, rect.right, rect.bottom);
	pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.FillSolidRect(CRect(0, 0, rect.right, rect.bottom), RGB(255, 255, 255));
	CFont cFont;//CreateFont�� ��18�� textEdit�� rowHight�� �ٲ����
	cFont.CreateFont(25, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,// �۲� ����
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "���� ���");
	SetFont(&cFont, TRUE);
	CFont *oldFont = memDC.SelectObject(&cFont);

	DrawingVisitor drawingVisitor;
	this->diagram->Accept(drawingVisitor, &memDC);
	WritingVisitor writingVisitor;
	this->diagram->Accept(writingVisitor, &memDC);
	this->selection->Accept(drawingVisitor, &memDC); // selectionFlag �߰� Ȯ��
	if (this->startX != 0 && this->startY != 0 && this->currentX != 0 && this->currentY != 0) {
		this->mouseLButton->MouseLButtonDrag(this->mouseLButton, this->diagram, this->selection, this->startX, this->startY, this->currentX, this->currentY, &memDC);
	}

	memDC.SelectObject(oldFont);
	cFont.DeleteObject();

	dc.BitBlt(0, 0, rect.right, rect.bottom, &memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(pOldBitmap);
	bitmap.DeleteObject();
	memDC.DeleteDC();
}

void ClassDiagramForm::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	this->mouseLButton->ChangeState(nChar);
	KeyAction *keyAction = this->keyBoard->KeyDown(this, nChar, nRepCnt, nFlags);
	if (keyAction != 0) {
		keyAction->KeyPress(this);

		Invalidate(false);
	}
	if (nChar == VK_END) {
		this->verticalScrollBar->OnVScrollBottom();
	}
	if (nChar == VK_HOME) {
		this->verticalScrollBar->OnVScrollTop();
	}
	//Invalidate();
}

void ClassDiagramForm::OnSetFocus(CWnd* pOldWnd) {
	CFrameWnd::OnSetFocus(pOldWnd);
	CWnd::SetFocus();
	Invalidate(false);
}
void ClassDiagramForm::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	VScrollCreator vaction;
	ScrollAction *action = vaction.CreatorAction(nSBCode, nPos, pScrollBar);
	if (action != 0) {
		action->ScrollScreen(this->verticalScrollBar);
	}
	
}
void ClassDiagramForm::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	HScrollCreator haction;
	ScrollAction *action = haction.CreatorAction(nSBCode, nPos, pScrollBar);
	if (action != 0) {
		action->ScrollScreen(this->horizontalScroll);
	}

}
void ClassDiagramForm::OnLButtonDown(UINT nFlags, CPoint point) {
	MSG msg;
	UINT dblclkTime = GetDoubleClickTime();
	UINT elapseTime = 0;
	this->SetFocus();
	SetTimer(1, 1, NULL);
	while (elapseTime < dblclkTime) {
		PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
		if (msg.message == WM_LBUTTONDBLCLK || msg.message == WM_RBUTTONDBLCLK) {
			KillTimer(1);
		}
		elapseTime++;
	}

	this->startX = point.x;
	this->startY = point.y;
	this->currentX = point.x;
	this->currentY = point.y;


	this->mouseLButton->MouseLButtonDown(this->mouseLButton, this->diagram, this->selection, this->startX, this->startY, this->currentX, this->currentY);


	KillTimer(1);

	Invalidate(false);
}

void ClassDiagramForm::OnLButtonDblClk(UINT nFlags, CPoint point) {
	this->startX = point.x;
	this->startY = point.y;
	this->currentX = point.x;
	this->currentY = point.y;



	Figure* figure = this->diagram->FindItem(startX, startY);
	if (figure != NULL) {

		this->textEdit = new TextEdit(figure);

		if (dynamic_cast<MemoBox*>(figure)) {
			this->textEdit->Create(NULL, "textEdit", WS_CHILD | WS_VISIBLE, CRect(
				figure->GetX() + GabX,
				figure->GetY() + GabY + MemoGab,
				figure->GetX() + figure->GetWidth() - GabX,
				figure->GetY() + figure->GetHeight() - GabY), this, 10000, NULL);
			//OnKillFocus(NULL);
		}
		else {
			this->textEdit->Create(NULL, "textEdit", WS_CLIPCHILDREN | WS_VISIBLE, CRect(
				figure->GetX() + GabX,
				figure->GetY() + GabY,
				figure->GetX() + figure->GetWidth() - GabX,
				figure->GetY() + figure->GetHeight() - GabY), this, 10000, NULL);

			//OnKillFocus(NULL);
		}

		OnKillFocus(NULL);
	}

	//���õ� relationLine �� ������
	if (this->selection->GetLength() == 1 && dynamic_cast<Relation*>(this->selection->GetAt(0))) {
		// relationLine ���� rollNamePoints array ���鼭 points ���� �ڽ������� ����Ŭ������ Ȯ���Ѵ�
		Long i = 0;
		Long index = 0;
		Relation *relation = static_cast<Relation*>(this->selection->GetAt(0));
		Long right;
		Long left;
		Long top;
		Long bottom;
		while (i < 5 && index == 0) {
			if (i == 1) {
				right = relation->rollNamePoints->GetAt(i).x + 40;
				left = relation->rollNamePoints->GetAt(i).x - 40;
				top = relation->rollNamePoints->GetAt(i).y - 10;
				bottom = relation->rollNamePoints->GetAt(i).y + 10;
			}
			else {
				right = relation->rollNamePoints->GetAt(i).x + 20;
				left = relation->rollNamePoints->GetAt(i).x - 20;
				top = relation->rollNamePoints->GetAt(i).y - 10;
				bottom = relation->rollNamePoints->GetAt(i).y + 10;
			}
	
			if (startX < right && startX > left && startY > top && startY < bottom) {
				index++;
			}
			i++;
		}
		if (index > 0) {
			this->textEdit = new TextEdit(relation, i - 1);
			this->textEdit->Create(NULL, "textEdit", WS_CHILD | WS_VISIBLE, CRect(
				left + 1,
				top + 1,
				right - 1,
				bottom - 1), this, 10000, NULL);
			OnKillFocus(NULL);
		}
	}
	if (this->selection->GetLength() == 1 && dynamic_cast<SelfRelation*>(this->selection->GetAt(0))) {
		// relationLine ���� rollNamePoints array ���鼭 points ���� �ڽ������� ����Ŭ������ Ȯ���Ѵ�
		Long i = 0;
		Long index = 0;
		SelfRelation *selfRelation = static_cast<SelfRelation*>(this->selection->GetAt(0));
		Long right;
		Long left;
		Long top;
		Long bottom;
		while (i < 5 && index == 0) {
			if (i == 0) {
				right = selfRelation->rollNamePoints->GetAt(i).x + 20;
				left = selfRelation->rollNamePoints->GetAt(i).x - 10;
				top = selfRelation->rollNamePoints->GetAt(i).y - 10;
				bottom = selfRelation->rollNamePoints->GetAt(i).y + 10;
			}
			else if (i == 1) {
				right = selfRelation->rollNamePoints->GetAt(i).x + 30;
				left = selfRelation->rollNamePoints->GetAt(i).x - 30;
				top = selfRelation->rollNamePoints->GetAt(i).y - 10;
				bottom = selfRelation->rollNamePoints->GetAt(i).y + 10;
			}
			else if (i == 2) {
				right = selfRelation->rollNamePoints->GetAt(i).x + 10;
				left = selfRelation->rollNamePoints->GetAt(i).x - 20;
				top = selfRelation->rollNamePoints->GetAt(i).y - 10;
				bottom = selfRelation->rollNamePoints->GetAt(i).y + 10;
			}
			else if (i == 3) {
				right = selfRelation->rollNamePoints->GetAt(i).x + 10;
				left = selfRelation->rollNamePoints->GetAt(i).x - 20;
				top = selfRelation->rollNamePoints->GetAt(i).y - 10;
				bottom = selfRelation->rollNamePoints->GetAt(i).y + 10;
			}
			else if (i == 4) {
				right = selfRelation->rollNamePoints->GetAt(i).x + 10;
				left = selfRelation->rollNamePoints->GetAt(i).x - 20;
				top = selfRelation->rollNamePoints->GetAt(i).y - 10;
				bottom = selfRelation->rollNamePoints->GetAt(i).y + 10;
			}

			if (startX < right && startX > left && startY > top && startY < bottom) {
				index++;
			}
			i++;
		}
		// Ȯ���ؼ� ������ �� index ����صΰ� �� �ڽ� ������� textEdit ���� (textEdit ������ ���� �������ҵ�)

		if (index > 0) {
			this->textEdit = new TextEdit(selfRelation, i - 1);
			this->textEdit->Create(NULL, "textEdit", WS_CHILD | WS_VISIBLE, CRect(
				left,
				top,
				right,
				bottom), this, 10000, NULL);
			OnKillFocus(NULL);
		}
	}
}

void ClassDiagramForm::OnLButtonUp(UINT nFlags, CPoint point) {
	CWnd::SetFocus();

	MSG msg;
	UINT dblclkTime = GetDoubleClickTime();
	UINT elapseTime = 0;
	PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
	if (msg.message == WM_LBUTTONDBLCLK || msg.message == WM_RBUTTONDBLCLK) {
		return;
	}
	this->currentX = point.x;
	this->currentY = point.y;


	this->mouseLButton->MouseLButtonUp(this->mouseLButton, this->diagram, this->selection, this->startX, this->startY, this->currentX, this->currentY);



	this->startX = 0;
	 this->startY = 0;
	this->currentX = 0;
	this->currentY = 0;

	KillTimer(1);

	Invalidate(false);
}

void ClassDiagramForm::OnMouseMove(UINT nFlags, CPoint point) {

	if (nFlags == MK_LBUTTON) {
		this->currentX = point.x;
		this->currentY = point.y;

		Invalidate(false);
	}
	/*Long index;
	index = this->selection->SelectByPoint(point.x, point.y);
	if (index == 1) {
		SetCursor(LoadCursor(NULL, IDC_HAND));
	}
	else if (index == 2) {
		SetCursor(LoadCursor(NULL, IDC_CROSS));
	}
	else if (index == 3 || index == 5) {
		SetCursor(LoadCursor(NULL, IDC_HELP));
	}
	else if (index == 4) {
		SetCursor(LoadCursor(NULL, IDC_SIZEALL));
	}*/
}
void ClassDiagramForm::OnClose() {
	//6.1. �����Ѵ�.
	//this->Save();

	//6.2. ���̾�׷��� �����.
	if (this->diagram != NULL) {
		delete this->diagram;
	}
	if (this->selection != NULL) {
		delete this->selection;
	}
	if (this->mouseLButton != NULL) {
		delete this->mouseLButton;
	}
	if (this->keyBoard != NULL) {
		delete this->keyBoard;
	}
	if (this->historyGraphic != NULL) {
		delete this->historyGraphic;
	}
	//6.3. �����츦 �ݴ´�.
	CFrameWnd::OnClose(); // �������̵� �ڵ�����
}