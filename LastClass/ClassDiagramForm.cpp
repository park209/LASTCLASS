//ClassDiagramForm.cpp

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
	this->drawingController = NULL;
	this->startX = 0;
	this->startY = 0;
	this->currentX = 0;
	this->currentY = 0;
	this->currentClassIndex = -1;
	this->rowIndex = 0;
	this->characterIndex = 0;
	//this->selected = -1;
	this->classButton = false;
	this->relationButton = false;
	this->generalizationButton = false; //일반화
	this->realizationButton = false; //실체화
	this->dependencyButton = false; //의존
	this->associationButton = false; //연관화  
	this->directedAssociationButton = false; //직접연관
	this->aggregationButton = false; // 집합
	this->aggregationSButton = false; // 집합연관
	this->compositionButton = false; // 합성
	this->compositionSBtton = false; // 복합연관
	this->templateButton = false;
	this->memoBoxButton = false;
}

Long ClassDiagramForm::Save() {
   Long i = 0;
   Long j;
   ofstream fClass;
   ofstream fLine; // 읽을때는 ofstream

   fClass.open("ClassSave.txt");
   fLine.open("LineSave.txt");
   if (fClass.is_open() && fLine.is_open()) {
      while (i < this->diagram->GetLength() ) {
		  //종류 구별을 위한 마지막 칸 
		  // 0 = Class, 1 = MemoBox, 2 = Line, 3 = Template, 4 = Generalization(일반화), 5 = Realization(실체화), 6 = Dependency(의존), 7 = Association(연관화),
		  // 8 = DirectedAssociation(직접연관),  9 = Aggregation(집합), 10 = Aggregations(집합연관), 11 =  Composition(합성), 12 = Compositions(복합연관), 13 = MemoLine

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
         //object = dynamic_cast<Class*>(this->diagram->GetAt(i));
         //fClass << object->GetLength() << " " << object->GetX() << " " << object->GetY()
         //   << " " << object->GetWidth() << " " << object->GetHeight() << endl;
         j = 0;
         while (j < object->GetLength()) {
			 Figure *figure;
			 
			 if (dynamic_cast<Line*>(object->GetAt(j))) {
				 figure = object->GetAt(j);
				 fLine << figure->GetX() << " " << figure->GetY() << " " <<
					 figure->GetWidth() << " " << figure->GetHeight() << " " << 2 << endl;
			 }

			 else if (dynamic_cast<Template*>(object->GetAt(j))) {
				 figure = object->GetAt(j);
				 fLine << figure->GetX() << " " << figure->GetY() << " " <<
					 figure->GetWidth() << " " << figure->GetHeight() << " " << 3 << endl;
			 }

			 else if (dynamic_cast<Generalization*>(object->GetAt(j))) {
				 figure = object->GetAt(j);
				 fLine << figure->GetX() << " " << figure->GetY() << " " <<
					 figure->GetWidth() << " " << figure->GetHeight() << " " << 4 << endl;
			 }

			 else if (dynamic_cast<Realization*>(object->GetAt(j))) {
				 figure = object->GetAt(j);
				 fLine << figure->GetX() << " " << figure->GetY() << " " <<
					 figure->GetWidth() << " " << figure->GetHeight() << " " << 5 << endl;
			 }

			 else if (dynamic_cast<Dependency*>(object->GetAt(j))) {
				 figure = object->GetAt(j);
				 fLine << figure->GetX() << " " << figure->GetY() << " " <<
					 figure->GetWidth() << " " << figure->GetHeight() << " " << 6 << endl;
			 }

			 else if (dynamic_cast<Association*>(object->GetAt(j))) {
				 figure = object->GetAt(j);
				 fLine << figure->GetX() << " " << figure->GetY() << " " <<
					 figure->GetWidth() << " " << figure->GetHeight() << " " << 7 << endl;
			 }

			 else if (dynamic_cast<DirectedAssociation*>(object->GetAt(j))) {
				 figure = object->GetAt(j);
				 fLine << figure->GetX() << " " << figure->GetY() << " " <<
					 figure->GetWidth() << " " << figure->GetHeight() << " " << 8 << endl;
			 }

			 else if (dynamic_cast<Aggregation*>(object->GetAt(j))) {
				 figure = object->GetAt(j);
				 fLine << figure->GetX() << " " << figure->GetY() << " " <<
					 figure->GetWidth() << " " << figure->GetHeight() << " " << 9 << endl;
			 }

			 else if (dynamic_cast<Aggregations*>(object->GetAt(j))) {
				 figure = object->GetAt(j);
				 fLine << figure->GetX() << " " << figure->GetY() << " " <<
					 figure->GetWidth() << " " << figure->GetHeight() << " " << 10 << endl;
			 }

			 else if (dynamic_cast<Composition*>(object->GetAt(j))) {
				 figure = object->GetAt(j);
				 fLine << figure->GetX() << " " << figure->GetY() << " " <<
					 figure->GetWidth() << " " << figure->GetHeight() << " " << 11 << endl;
			 }

			 else if (dynamic_cast<Compositions*>(object->GetAt(j))) {
				 figure = object->GetAt(j);
				 fLine << figure->GetX() << " " << figure->GetY() << " " <<
					 figure->GetWidth() << " " << figure->GetHeight() << " " << 12 << endl;
			 }

			 else if (dynamic_cast<MemoLine*>(object->GetAt(j))) {
				 figure = object->GetAt(j);
				 fLine << figure->GetX() << " " << figure->GetY() << " " <<
					 figure->GetWidth() << " " << figure->GetHeight() << " " << 13 << endl;
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
	ifstream fClass;
	ifstream fLine;
	Long type;

	FigureFactory factory;
	Figure *figure;

	fClass.open("ClassSave.txt");
	fLine.open("LineSave.txt");

	//종류 구별을 위한 마지막 칸 
	// 0 = Class, 1 = MemoBox, 2 = Line, 3 = Template, 4 = Generalization(일반화), 5 = Realization(실체화), 6 = Dependency(의존), 7 = Association(연관화),
	// 8 = DirectedAssociation(직접연관),  9 = Aggregation(집합), 10 = Aggregations(집합연관), 11 =  Composition(합성), 12 = Compositions(복합연관), 13 = MemoLine

	if (fClass.is_open() && fLine.is_open()) {
		fClass >> length >> x >> y >> width >> height >> type;
		while (!fClass.eof()) {
			figure  = factory.Create(x, y, width, height, type);
			position = this->diagram->Add(figure);
			i = 0;
			while (position !=-1 && i < length) {
				fLine >> lineX >> lineY >> lineWidth >> lineHeight >> type;
				figure = factory.Create(lineX, lineY, lineWidth, lineHeight, type);
				static_cast<FigureComposite*>(this->diagram->GetAt(position))->Add(figure);
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

	CFrameWnd::OnCreate(lpCreateStruct); //코드재사용 오버라이딩 //상속에서
										 //1.1. 다이어그램을 준비한다
	this->diagram = new Diagram();
	this->text = new Text;
	this->selection = new Selection;
	this->drawingController = new DrawingController;

	//1.2. 적재한다
	//this->Load();
	//this->TextLoad();
	//1.3. 윈도우를 갱신한다
	Invalidate();

	return 0;
}

void ClassDiagramForm::OnPaint() {
	CPaintDC dc(this);

	DrawingVisitor drawingVisitor;
	WritingVisitor writingVisitor;

	this->diagram->Accept(drawingVisitor, &dc);
	this->text->Accept(writingVisitor, &dc);

	this->drawingController->Draw(this->startX, this->startY, this->currentX, this->currentY, &dc);

	//선택 표시 막아둠
	//if (this->selected != -1) {
	
		Long i = 0;
		while (i < this->selection->GetLength()) {
			if (dynamic_cast<Class*>(this->selection->GetAt(i))) {
				if (dynamic_cast<Class*>(this->selection->GetAt(i))->GetTempletePosition() == -1) {
					dc.Rectangle(this->selection->GetAt(i)->GetX() - 5,
						this->selection->GetAt(i)->GetY() - 5,
						this->selection->GetAt(i)->GetX() + 5,
						this->selection->GetAt(i)->GetY() + 5);
					dc.Rectangle(this->selection->GetAt(i)->GetX() + this->selection->GetAt(i)->GetWidth() - 5,
						this->selection->GetAt(i)->GetY() - 5,
						this->selection->GetAt(i)->GetX() + this->selection->GetAt(i)->GetWidth() + 5,
						this->selection->GetAt(i)->GetY() + 5);
					dc.Rectangle(this->selection->GetAt(i)->GetX() - 5,
						this->selection->GetAt(i)->GetY() + this->selection->GetAt(i)->GetHeight() - 5,
						this->selection->GetAt(i)->GetX() + 5,
						this->selection->GetAt(i)->GetY() + this->selection->GetAt(i)->GetHeight() + 5);
					dc.Rectangle(this->selection->GetAt(i)->GetX() + this->selection->GetAt(i)->GetWidth() - 5,
						this->selection->GetAt(i)->GetY() + this->selection->GetAt(i)->GetHeight() - 5,
						this->selection->GetAt(i)->GetX() + this->selection->GetAt(i)->GetWidth() + 5,
						this->selection->GetAt(i)->GetY() + this->selection->GetAt(i)->GetHeight() + 5);
				}
				else {
					Long j = 0;
					while (j < dynamic_cast<Class*>(this->selection->GetAt(i))->GetLength()) {
						if (dynamic_cast<Template*>(dynamic_cast<Class*>(this->selection->GetAt(i))->GetAt(j))) {
							dc.Rectangle(
								this->selection->GetAt(i)->GetX() - 5,
								dynamic_cast<Template*>(dynamic_cast<Class*>(this->selection->GetAt(i))->GetAt(j))->GetY() - 5,
								this->selection->GetAt(i)->GetX() + 5,
								dynamic_cast<Template*>(dynamic_cast<Class*>(this->selection->GetAt(i))->GetAt(j))->GetY() + 5);
							dc.Rectangle(
								dynamic_cast<Template*>(dynamic_cast<Class*>(this->selection->GetAt(i))->GetAt(j))->GetX() +
								dynamic_cast<Template*>(dynamic_cast<Class*>(this->selection->GetAt(i))->GetAt(j))->GetWidth() - 5,
								dynamic_cast<Template*>(dynamic_cast<Class*>(this->selection->GetAt(i))->GetAt(j))->GetY() - 5,
								dynamic_cast<Template*>(dynamic_cast<Class*>(this->selection->GetAt(i))->GetAt(j))->GetX() +
								dynamic_cast<Template*>(dynamic_cast<Class*>(this->selection->GetAt(i))->GetAt(j))->GetWidth() + 5,
								dynamic_cast<Template*>(dynamic_cast<Class*>(this->selection->GetAt(i))->GetAt(j))->GetY() + 5);
							dc.Rectangle(
								this->selection->GetAt(i)->GetX() - 5,
								this->selection->GetAt(i)->GetY() + this->selection->GetAt(i)->GetHeight() - 5,
								this->selection->GetAt(i)->GetX() + 5,
								this->selection->GetAt(i)->GetY() + this->selection->GetAt(i)->GetHeight() + 5);
							dc.Rectangle(
								dynamic_cast<Template*>(dynamic_cast<Class*>(this->selection->GetAt(i))->GetAt(j))->GetX() +
								dynamic_cast<Template*>(dynamic_cast<Class*>(this->selection->GetAt(i))->GetAt(j))->GetWidth() - 5,
								this->selection->GetAt(i)->GetY() + this->selection->GetAt(i)->GetHeight() - 5,
								dynamic_cast<Template*>(dynamic_cast<Class*>(this->selection->GetAt(i))->GetAt(j))->GetX() +
								dynamic_cast<Template*>(dynamic_cast<Class*>(this->selection->GetAt(i))->GetAt(j))->GetWidth() + 5,
								this->selection->GetAt(i)->GetY() + this->selection->GetAt(i)->GetHeight() + 5);

						}
						j++;
					}


				}
			}

			if (dynamic_cast<MemoBox*>(this->selection->GetAt(i))) {

				dc.Rectangle(this->selection->GetAt(i)->GetX() - 5,
					this->selection->GetAt(i)->GetY() - 5,
					this->selection->GetAt(i)->GetX() + 5,
					this->selection->GetAt(i)->GetY() + 5);
				dc.Rectangle(this->selection->GetAt(i)->GetX() + this->selection->GetAt(i)->GetWidth() - 5,
					this->selection->GetAt(i)->GetY() - 5,
					this->selection->GetAt(i)->GetX() + this->selection->GetAt(i)->GetWidth() + 5,
					this->selection->GetAt(i)->GetY() + 5);
				dc.Rectangle(this->selection->GetAt(i)->GetX() - 5,
					this->selection->GetAt(i)->GetY() + this->selection->GetAt(i)->GetHeight() - 5,
					this->selection->GetAt(i)->GetX() + 5,
					this->selection->GetAt(i)->GetY() + this->selection->GetAt(i)->GetHeight() + 5);
				dc.Rectangle(this->selection->GetAt(i)->GetX() + this->selection->GetAt(i)->GetWidth() - 5,
					this->selection->GetAt(i)->GetY() + this->selection->GetAt(i)->GetHeight() - 5,
					this->selection->GetAt(i)->GetX() + this->selection->GetAt(i)->GetWidth() + 5,
					this->selection->GetAt(i)->GetY() + this->selection->GetAt(i)->GetHeight() + 5);

			}
		if (dynamic_cast<Realization*>(this->selection->GetAt(i)) || dynamic_cast<Generalization*>(this->selection->GetAt(i)) || dynamic_cast<Dependency*>(this->selection->GetAt(i)) ||
			dynamic_cast<Association*>(this->selection->GetAt(i)) || dynamic_cast<Aggregation*>(this->selection->GetAt(i)) || dynamic_cast<Aggregations*>(this->selection->GetAt(i)) ||
			dynamic_cast<Composition*>(this->selection->GetAt(i)) || dynamic_cast<Compositions*>(this->selection->GetAt(i)) || dynamic_cast<DirectedAssociation*>(this->selection->GetAt(i)) ||
			dynamic_cast<MemoLine*>(this->selection->GetAt(i))) {
			dc.Rectangle(this->selection->GetAt(i)->GetX() - 5,
				this->selection->GetAt(i)->GetY() - 5,
				this->selection->GetAt(i)->GetX() + 5,
				this->selection->GetAt(i)->GetY() + 5);
			dc.Rectangle(this->selection->GetAt(i)->GetX() + (this->selection->GetAt(i)->GetWidth() / 2) - 5,
				this->selection->GetAt(i)->GetY() + (this->selection->GetAt(i)->GetHeight() / 2) - 5,
				this->selection->GetAt(i)->GetX() + (this->selection->GetAt(i)->GetWidth() / 2) + 5,
				this->selection->GetAt(i)->GetY() + (this->selection->GetAt(i)->GetHeight() / 2) + 5);
			dc.Rectangle(this->selection->GetAt(i)->GetX() + this->selection->GetAt(i)->GetWidth() - 5,
				this->selection->GetAt(i)->GetY() + this->selection->GetAt(i)->GetHeight() - 5,
				this->selection->GetAt(i)->GetX() + this->selection->GetAt(i)->GetWidth() + 5,
				this->selection->GetAt(i)->GetY() + this->selection->GetAt(i)->GetHeight() + 5);

		}
		i++;
	}
}
void ClassDiagramForm::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {

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
	//this->selected = this->diagram->Find(this->currentX, this->currentY);
	this->selection->DeleteAllItems();
	//if (this->relationButton == true) {
	Long x = this->startX;
	Long y = this->startY;
	this->selection->FindByPoint(this->diagram, x, y);
	//}

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

		this->textEdit = new TextEdit(figure); // 

		this->textEdit->Create(NULL, "textEdit", WS_DLGFRAME, CRect(
			figure->GetX(),
			figure->GetY(),
			figure->GetX() + figure->GetWidth(),
			figure->GetY() + figure->GetHeight()), NULL, NULL, WS_EX_TOPMOST);
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
		CRect area;
		area.left = this->startX;
		area.top = this->startY;
		area.right = this->currentX;
		area.bottom = this->currentY;
		this->selection->FindByArea(this->diagram, area);
	}

	Figure *figure = 0;
	if (this->startX != this->currentX && this->startY != this->currentY) {
		figure = this->drawingController->AddToArray(this->diagram, this->selection, this->startX, this->startY, this->currentX, this->currentY);
	}

	if (dynamic_cast<Class*>(figure)) {
		Class* tempClass = static_cast<Class*>(figure);

		ClassName className(this->startX + 5, this->startY + 33, this->currentX - this->startX - 10, 20, "11111");
		tempClass->Add(className.Clone());
		Attribute attribute(this->startX + 5, this->startY + 53, this->currentX - this->startX - 10, (this->startY + 50 + this->currentY) / 2, "2222"); // 내용값은 수정해야함
		tempClass->Add(attribute.Clone());
		Method method(this->startX + 5, (this->startY + 50 + this->currentY) / 2, this->currentX - this->startX - 10, this->currentY, "3333");
		tempClass->Add(method.Clone());

		this->textEdit = new TextEdit(figure);

		this->textEdit->Create(NULL, "textEdit", WS_DLGFRAME, CRect(
			figure->GetX(),
			figure->GetY(),
			figure->GetX() + figure->GetWidth(),
			figure->GetY() + figure->GetHeight()), NULL, NULL, WS_EX_TOPMOST);
		this->textEdit->ShowWindow(SW_SHOW);
	}

	if (this->startX != this->currentX && this->startY != this->currentY) {
		this->drawingController->AddToArray(this->diagram, this->selection, this->startX, this->startY, this->currentX, this->currentY);
	}
	//Long length = this->selection->GetLength();

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

bool ClassDiagramForm::FindCrossPoint(const CPoint& line1Start, const CPoint& line1End, const CPoint& line2Start, const CPoint& line2End, CPoint *crossPoint) {
	double t;
	double s;
	bool ret = false;
	double under = (line2End.y - line2Start.y)*(line1End.x - line1Start.x) - (line2End.x - line2Start.x)*(line1End.y - line1Start.y);
	if (under != 0) {
		double _t = (line2End.x - line2Start.x)*(line1Start.y - line2Start.y) - (line2End.y - line2Start.y)*(line1Start.x - line2Start.x);
		double _s = (line1End.x - line1Start.x)*(line1Start.y - line2Start.y) - (line1End.y - line1Start.y)*(line1Start.x - line2Start.x);
		t = _t / under;
		s = _s / under;
		if (t >= 0.0 && t <= 1.0 && s >= 0.0 && s <= 1.0 && _t != 0 && _s != 0) {
			crossPoint->x = static_cast<LONG>(line1Start.x + t*(double)(line1End.x - line1Start.x));
			crossPoint->y = static_cast<LONG>(line1Start.y + t*(double)(line1End.y - line1Start.y));
			ret = true;
		}
	}
	return ret;
}

void ClassDiagramForm::OnClose() {
	//6.1. 저장한다.
	//this->Save();
	//this->TextSave();
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
	if (this->drawingController != NULL) {
		delete this->drawingController;
	}
	
	//6.3. 윈도우를 닫는다.
	CFrameWnd::OnClose(); // 오버라이딩 코드재사용
}
