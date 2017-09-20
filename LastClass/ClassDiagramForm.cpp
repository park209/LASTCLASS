//ClassDiagramForm.cpp
#include "SelfAggregation.h"
 #include  "SelfAggregations.h"
 #include  "SelfAssociation.h"
 #include  "SelfComposition.h"
 #include  "SelfCompositions.h"
 #include  "SelfDependency.h"
 #include  "SelfDirectedAssociation.h"
 #include  "SelfGeneralization.h"
 #include "SelfRelation.h"
#include "ClassDiagramForm.h"
#include "Class.h"
#include "Line.h"
#include "Figure.h"
#include "Diagram.h"
#include "DrawingVisitor.h"
#include "Text.h"
#include "SingleByteCharacter.h"
#include "WritingVisitor.h"
#include "TextEdit.h"
#include "Template.h"
#include "Generalization.h"
#include "Realization.h"
#include "Dependency.h"
#include "Association.h"
#include "DirectedAssociation.h"
#include "Aggregation.h"
#include "Aggregations.h"
#include "Composition.h"
#include "Compositions.h"
#include "MemoBox.h"
#include "Selection.h"
#include "DrawingController.h"
#include "FigureFactory.h"
#include "MemoLine.h"
#include "Unclicked.h"
#include "ClassName.h"
#include "Method.h"
#include "Attribute.h"
#include "Reception.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include "MovingVisitor.h"

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

ClassDiagramForm::ClassDiagramForm() { // ������ �´µ�
	this->diagram = NULL;
	this->text = NULL;
	this->textEdit = NULL;
	this->selection = NULL;
	this->drawingController = NULL;
	this->startX = 0;
	this->startY = 0;
	this->currentX = 0;
	this->currentY = 0;
	this->currentClassIndex = -1;
	this->rowIndex = 0;
	this->characterIndex = 0;
}

Long ClassDiagramForm::Save() {
	Long k;
	Long i = 0;
	Long j;
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


Long ClassDiagramForm::TextSave() {
	Long i = 0;
	string s;
	ofstream fText;
	fText.open("Text.txt");
	if (fText.is_open()) {
		while (i < this->text->GetLength()) {
			s = this->text->GetAt(i)->PrintRowString();
			fText << this->text->GetAt(i)->GetX() << ' ' << this->text->GetAt(i)->GetY() << ' ' << this->text->GetAt(i)->GetRowHeight() << ' ' << endl;
			fText << s << endl;
			i++;
		}
		fText.close();
	}
	return i;
}

Long ClassDiagramForm::TextLoad() {
	FigureFactory textCreator;
	Long i = 0;
	Long x = 0;
	Long y = 0;
	Long rowHeight = 0;
	Long classID = -1;
	string str;
	TextComponent* Component = NULL;
	ifstream fText;

	fText.open("Text.txt");
	if (fText.is_open()) {
		while (!fText.eof() || getline(fText, str)) {
			fText >> x >> y >> rowHeight >> classID;
			getline(fText, str);
			fText.clear();
			getline(fText, str);
			fText.clear();

			Component = textCreator.CreateRow(x, y, rowHeight, classID, str);
			this->text->Add(Component);
			i++;
		}
	}
	return i;
}

int ClassDiagramForm::OnCreate(LPCREATESTRUCT lpCreateStruct) {

	CFrameWnd::OnCreate(lpCreateStruct); //�ڵ����� �������̵� //��ӿ���
										 //1.1. ���̾�׷��� �غ��Ѵ�
	this->diagram = new Diagram();
	this->text = new Text;
	this->selection = new Selection;
	this->drawingController = new DrawingController;

	//1.2. �����Ѵ�
	//this->Load();
	//this->TextLoad();
	//1.3. �����츦 �����Ѵ�
	Invalidate();

	return 0;
}

void ClassDiagramForm::OnPaint() {
	CPaintDC dc(this);

	DrawingVisitor drawingVisitor;
	WritingVisitor writingVisitor;

	this->diagram->Accept(drawingVisitor, &dc);
	this->text->Accept(writingVisitor, &dc);
	
	if (this->startX != 0 && this->startY != 0 && this->currentX != 0 && this->currentY != 0) {
		this->drawingController->Draw(this->selection, this->startX, this->startY, this->currentX, this->currentY, &dc);
	}

	this->selection->Accept(drawingVisitor, &dc);
	
}

	void ClassDiagramForm::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
		Class *object;
	if (nChar == 100) { // D �����׸� �����
		this->selection->Remove(this->diagram,this->selection->GetAt(0));
	}
	if (nChar == 102) { // F ���ø���ȣ �����
		object = static_cast<Class*>(this->selection->GetAt(0));
		object->RemoveTemplate();
	}
	if (nChar == 103) { // G ������ĭ �����
		object = static_cast<Class*>(this->selection->GetAt(0));
		object->RemoveReception();
	}
	this->drawingController->ChangeState(nChar);
	
	Invalidate();
}

void ClassDiagramForm::OnSetFocus(CWnd* pOldWnd) {

	this->Invalidate();
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
	
	this->selection->DeleteAllItems();

	Long x = this->startX;
	Long y = this->startY;
	this->selection->SelectByPoint(this->diagram, x, y);
	

	KillTimer(1);

	Invalidate();
}


void ClassDiagramForm::OnLButtonDblClk(UINT nFlags, CPoint point) {
	CPaintDC dc(this);
	this->startX = point.x;
	this->startY = point.y;
	this->currentX = point.x;
	this->currentY = point.y;

	Figure* figure = this->diagram->FindItem(startX, startY);
	if (figure != NULL) {

		this->textEdit = new TextEdit(figure);

		this->textEdit->Create(NULL, "textEdit", WS_DLGFRAME, CRect(
			figure->GetX()+5,
			figure->GetY()+33,
			figure->GetX() + figure->GetWidth()+5,
			figure->GetY() + figure->GetHeight()+33), NULL, NULL, WS_EX_TOPMOST);
		this->textEdit->ShowWindow(SW_SHOW);
	}
}

void ClassDiagramForm::OnLButtonUp(UINT nFlags, CPoint point) {
	MSG msg;
	UINT dblclkTime = GetDoubleClickTime();
	UINT elapseTime = 0;
	PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
	if (msg.message == WM_LBUTTONDBLCLK || msg.message == WM_RBUTTONDBLCLK) {
		return;
	}
	this->currentX = point.x;
	this->currentY = point.y;

	if (dynamic_cast<Unclicked*>(this->drawingController->buttonState)) {
		MovingVisitor movingVisitor;
		Long distanceX = currentX - startX;
		Long distanceY = currentY - startY;
		this->selection->Accept(this->diagram,movingVisitor, distanceX, distanceY);
		if (this->selection->GetLength() == 0) {
			CRect area;
			area.left = this->startX;
			area.top = this->startY;
			area.right = this->currentX;
			area.bottom = this->currentY;
			this->selection->SelectByArea(this->diagram, area);
		}
	}

	Figure *figure = 0;
	if (this->startX != this->currentX || this->startY != this->currentY) {
		figure = this->drawingController->AddToArray(this->diagram, this->selection, this->startX, this->startY, this->currentX, this->currentY);
	
	}

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
}



void ClassDiagramForm::OnClose() {
	//6.1. �����Ѵ�.
	//this->Save();
	//this->TextSave();
	//6.2. ���̾�׷��� �����.
	if (this->diagram != NULL) {
		delete this->diagram;
	}
	if (this->text != NULL) {
		delete this->text;
	}
	if (this->selection != NULL) {
		delete this->selection;
	}
	if (this->drawingController != NULL) {
		delete this->drawingController;
	}
	
	//6.3. �����츦 �ݴ´�.
	CFrameWnd::OnClose(); // �������̵� �ڵ�����
}
