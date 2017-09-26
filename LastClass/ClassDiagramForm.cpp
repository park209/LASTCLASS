//ClassDiagramForm.cpp

#include "ClassDiagramForm.h"
#include "TextEdit.h"
#include "Diagram.h"
#include "Class.h"
#include "MemoBox.h"
#include "Selection.h"
#include "Text.h"
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
#include <math.h>
#include <iostream>
#include <fstream>
using namespace std;


BEGIN_MESSAGE_MAP(ClassDiagramForm, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_CHAR()
	ON_WM_SETFOCUS()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

ClassDiagramForm::ClassDiagramForm() { // 생성자 맞는듯
	this->diagram = NULL;
	this->text = NULL;
	this->textEdit = NULL;
	this->selection = NULL;
	this->mouseLButton = NULL;
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
	//종류 구별을 위한 마지막 칸 
	// 0 = Class, 1 = MemoBox, 2 = Line, 3 = Template, 4 = Generalization(일반화), 5 = Realization(실체화), 6 = Dependency(의존), 7 = Association(연관화),
	// 8 = DirectedAssociation(직접연관),  9 = Aggregation(집합), 10 = Aggregations(집합연관), 11 =  Composition(합성), 12 = Compositions(복합연관), 13 = MemoLine
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
	ofstream fClass;
	ofstream fLine; // 읽을때는 ofstream

	fClass.open("ClassSave.txt");
	fLine.open("LineSave.txt");
	if (fClass.is_open() && fLine.is_open()) {
		while (i < this->diagram->GetLength()) {
			//종류 구별을 위한 마지막 칸 
			// 0 = Class, 1 = MemoBox, 2 = Line, 3 = Template, 4 = Generalization(일반화), 5 = Realization(실체화), 
			//6 = Dependency(의존), 7 = Association(연관화),
			// 8 = DirectedAssociation(직접연관),  9 = Aggregation(집합), 10 = Aggregations(집합연관), 
			//11 =  Composition(합성), 12 = Compositions(복합연관), 13 = MemoLine
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
				fClass << object->GetLength() << " " << object->GetX() << " " << object->GetY()
					<< " " << object->GetWidth() << " " << object->GetHeight() << " " << 1 << endl;
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
					fLine << figure->GetX() << " " << figure->GetY() << " " <<
						figure->GetWidth() << " " << figure->GetHeight() << " " << 3 << " " << 0 << endl;
				}

				else if (dynamic_cast<Generalization*>(object->GetAt(j))) {
					Relation *relation = static_cast<Relation*>(object->GetAt(j));
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
					fLine << figure->GetX() << " " << figure->GetY() << " " << figure->GetWidth() << " "
						<< figure->GetHeight() << " " << 14 <<
						" " << 0 << endl;
				}
				else if (dynamic_cast<Attribute*>(object->GetAt(j))) {
					figure = static_cast<Attribute*>(object->GetAt(j));
					fLine << figure->GetX() << " " << figure->GetY() << " " << figure->GetWidth() << " "
						<< figure->GetHeight() << " " << 15 <<
						" " << 0 << endl;
				}
				else if (dynamic_cast<Method*>(object->GetAt(j))) {
					figure = static_cast<Method*>(object->GetAt(j));
					fLine << figure->GetX() << " " << figure->GetY() << " " << figure->GetWidth() << " "
						<< figure->GetHeight() << " " << 16 <<
						" " << 0 << endl;
				}
				else if (dynamic_cast<Reception*>(object->GetAt(j))) {
					figure = static_cast<Reception*>(object->GetAt(j));
					fLine << figure->GetX() << " " << figure->GetY() << " " << figure->GetWidth() << " "
						<< figure->GetHeight() << " " << 17 <<
						" " << 0 << endl;
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

	CFrameWnd::OnCreate(lpCreateStruct); //코드재사용 오버라이딩 //상속에서
										 //1.1. 다이어그램을 준비한다
	this->diagram = new Diagram();
	this->text = new Text;
	this->selection = new Selection;
	this->mouseLButton = new MouseLButton;


	//1.2. 적재한다
	//this->Load();

	//1.3. 윈도우를 갱신한다
	Invalidate();

	return 0;
}

void ClassDiagramForm::OnPaint() {
	CPaintDC dc(this);

	DrawingVisitor drawingVisitor;
	this->diagram->Accept(drawingVisitor, &dc);

	CFont cFont;//CreateFont에 값18을 textEdit의 rowHight로 바꿔야함
	cFont.CreateFont(25, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,// 글꼴 설정
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "맑은 고딕");
	SetFont(&cFont, TRUE);
	CFont *oldFont = dc.SelectObject(&cFont); // 폰트 시작

	WritingVisitor writingVisitor;
	this->diagram->Accept(writingVisitor, &dc);

	dc.SelectObject(oldFont);
	cFont.DeleteObject();

	if (this->startX != 0 && this->startY != 0 && this->currentX != 0 && this->currentY != 0) {

		this->mouseLButton->MouseLButtonDrag(this->mouseLButton, this->diagram, this->selection, this->startX, this->startY, this->currentX, this->currentY, &dc);
	}
	this->selection->Accept(drawingVisitor, &dc);
}

void ClassDiagramForm::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {

	Class *object = static_cast<Class*>(this->selection->GetAt(0));
	this->mouseLButton->ChangeState(nChar);
	if (nChar == 100) { // D 선택항목 지우기
		while (this->selection->GetLength() != 0) {
			this->selection->Remove(this->diagram, this->selection->GetAt(this->selection->GetLength() - 1));
		}
	}
	if (nChar == 118) { // V 템플릿기호 만들기
		if (object->GetTempletePosition() == -1) {
			object->AddTemplate(object->GetX() + object->GetWidth() - 70, object->GetY() - 15, 80, 25, "");
		}
	}
	if (nChar == 102) { // F 템플릿기호 지우기
		if (object->GetTempletePosition() != -1) {
			object->RemoveTemplate();
		}
	}

	if (nChar == 104) { //H 리셉션칸 추가
		if (object->GetReceptionPosition() == -1) {
			object->AddReception(this->diagram);
		}
	}
	if (nChar == 103) { // G 리셉션칸 지우기
		if (object->GetReceptionPosition() != -1) {
			object->RemoveReception();
		}
	}
	if (nChar == 117) { // U  
		if (object->GetAttributePosition() != 1) {
			object->RemoveAttribute();
		}
	}
	if (nChar == 105) {//i메소드삭제
		if (object->GetMethodPosition() != -1) {
			object->RemoveMethod();
		}
	}
	if (nChar == 111) {//o
		if (object->GetAttributePosition() == -1) {
			object->AddAttribute(this->diagram);
		}
	}
	if (nChar == 112) {//p
		if (object->GetMethodPosition() == -1) {
			object->AddMethod(this->diagram);
		}
	}


	Invalidate();
}


void ClassDiagramForm::OnSetFocus(CWnd* pOldWnd) {
	CFrameWnd::OnSetFocus(pOldWnd);

	CWnd::SetFocus();
	Invalidate();
}

void ClassDiagramForm::OnLButtonDown(UINT nFlags, CPoint point) {
	MSG msg;
	UINT dblclkTime = GetDoubleClickTime();
	UINT elapseTime = 0;

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

	Invalidate();
}

void ClassDiagramForm::OnLButtonDblClk(UINT nFlags, CPoint point) {
	CPaintDC dc(this);
	this->startX = point.x;
	this->startY = point.y;
	this->currentX = point.x;
	this->currentY = point.y;

	//this->selection->DeleteAllItems();

	Figure* figure = this->diagram->FindItem(startX, startY);
	if (figure != NULL) {

		this->textEdit = new TextEdit(figure);

		if (dynamic_cast<MemoBox*>(figure)) {
			this->textEdit->Create(NULL, "textEdit", WS_CHILD | WS_VISIBLE, CRect(
				figure->GetX(),
				figure->GetY() + 20,
				figure->GetX() + figure->GetWidth(),
				figure->GetY() + figure->GetHeight()), this, 10000, NULL);
			OnKillFocus(NULL);
		}
		else {
			this->textEdit->Create(NULL, "textEdit", WS_CHILD | WS_VISIBLE, CRect(
				figure->GetX(),
				figure->GetY(),
				figure->GetX() + figure->GetWidth(),
				figure->GetY() + figure->GetHeight()), this, 10000, NULL);
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

	if (this->startX != this->currentX || this->startY != this->currentY) {
		//figure = this->drawingController->AddToArray(this->diagram, this->selection, this->startX, this->startY, this->currentX, this->currentY);
		this->mouseLButton->MouseLButtonUp(this->mouseLButton, this->diagram, this->selection, this->startX, this->startY, this->currentX, this->currentY);
	}
/*
	Figure *figure = 0;
	if (this->startX != this->currentX || this->startY != this->currentY) {
		figure = this->drawingController->AddToArray(this->diagram, this->selection, this->startX, this->startY, this->currentX, this->currentY);
		if (dynamic_cast<ClassButton*>(this->drawingController->buttonState)) {
			SmartPointer<Figure*> iterator = static_cast<Class*>(figure)->CreateIterator();
			for (iterator->First(); !iterator->IsDone(); iterator->Next()) {
				if (dynamic_cast<ClassName*>(iterator->Current())) {
					this->textEdit = new TextEdit(iterator->Current());
					this->textEdit->Create(NULL, "textEdit", WS_CHILD | WS_VISIBLE, CRect(
						iterator->Current()->GetX(),
						iterator->Current()->GetY(),
						iterator->Current()->GetX() + iterator->Current()->GetWidth(),
						iterator->Current()->GetY() + iterator->Current()->GetHeight()), this, 10000, NULL);
					OnKillFocus(NULL);
				}
			}
		}
	}*/

	this->startX = 0;
	this->startY = 0;
	this->currentX = 0;
	this->currentY = 0;

	KillTimer(1);

	Invalidate();
}

void ClassDiagramForm::OnMouseMove(UINT nFlags, CPoint point) {
	if (nFlags == MK_LBUTTON) {
		this->currentX = point.x;
		this->currentY = point.y;
		
		Invalidate();
	}
	if (selection->SelectByPoint(point.x, point.y)) {
		SetCursor(LoadCursor(NULL, IDC_HAND));
	}
}
void ClassDiagramForm::OnClose() {
	//6.1. 저장한다.
	//this->Save();

	//6.2. 다이어그램을 지운다.
	if (this->diagram != NULL) {
		delete this->diagram;
	}
	if (this->text != NULL) {
		delete this->text;
	}
	if (this->selection != NULL) {
		delete this->selection;
	}
	if (this->mouseLButton != NULL) {
		delete this->mouseLButton;
	}

	//6.3. 윈도우를 닫는다.
	CFrameWnd::OnClose(); // 오버라이딩 코드재사용
}