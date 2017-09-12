//ClassDiagramForm.cpp

#include "ClassDiagramForm.h"
#include "Class.h"
#include "Line.h"
//#include "Figure.h"
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
	//ON_WM_LBUTTONDBLCLK()
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
		  // 8 = DirectedAssociation(직접연관),  9 = Aggregation(집합), 10 = Aggregations(집합연관), 11 =  Composition(합성), 12 = Compositions(복합연관)

		  FigureComposite *object = 0;
		 if (dynamic_cast<Class*>(this->diagram->GetAt(i))) {
			 object = dynamic_cast<FigureComposite*>(this->diagram->GetAt(i));
			 fClass << object->GetLength() << " " << object->GetX() << " " << object->GetY()
				 << " " << object->GetWidth() << " " << object->GetHeight() << " " << 0 << endl;
		 }

		 else if (dynamic_cast<MemoBox*>(this->diagram->GetAt(i))) {
			 object = dynamic_cast<FigureComposite*>(this->diagram->GetAt(i));
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

            //Line *lineObject;
			//Relation *relationObject;
			//if(dynamic_cast<Line*>(object.GetAt(j))) {
			//	lineObject = (dynamic_cast<Line*>(object.GetAt(j)));
			//	fLine << lineObject->GetX() << " " << lineObject->GetY() << " " <<
			//		lineObject->GetWidth() << " " << lineObject->GetHeight() << endl;
			//}
			//else if (dynamic_cast<Relation*>(object.GetAt(j))) {
			//	relationObject = (dynamic_cast<Relation*>(object.GetAt(j)));

			//}
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
	// 8 = DirectedAssociation(직접연관),  9 = Aggregation(집합), 10 = Aggregations(집합연관), 11 =  Composition(합성), 12 = Compositions(복합연관)

	if (fClass.is_open() && fLine.is_open()) {
		fClass >> length >> x >> y >> width >> height >> type;
		while (!fClass.eof()) {
			//if (type == 0) {
			//	position = this->diagram->AddClass(x, y, width, height);
			//}

			//else if (type == 1) {
			//	position = this->diagram->AddMemoBox(x, y, width, height);
			//}
			figure  = factory.Create(x, y, width, height, type);
			position = this->diagram->Add(figure);
			i = 0;
			while (position !=-1 && i < length) {
				fLine >> lineX >> lineY >> lineWidth >> lineHeight >> type;
				figure = factory.Create(lineX, lineY, lineWidth, lineHeight, type);
				dynamic_cast<FigureComposite*>(this->diagram->GetAt(position))->Add(figure);
				//if (type == 2) {
				//	dynamic_cast<Class*>(this->diagram->GetAt(position))->Add(lineX, lineY, lineWidth, lineHeight);
				//}
				//else if (type == 3) {
				//	dynamic_cast<Class*>(this->diagram->GetAt(position))->AddTemplate(lineX, lineY, lineWidth, lineHeight);
				//}
				//else if (type == 4) {
				//	dynamic_cast<Class*>(this->diagram->GetAt(position))->AddGeneralization(lineX, lineY, lineWidth, lineHeight);
				//}
				//else if (type == 5) {
				//	dynamic_cast<Class*>(this->diagram->GetAt(position))->AddRealization(lineX, lineY, lineWidth, lineHeight);
				//}
				//else if (type == 6) {
				//	dynamic_cast<Class*>(this->diagram->GetAt(position))->AddDependency(lineX, lineY, lineWidth, lineHeight);
				//}
				//else if (type == 7) {
				//	dynamic_cast<Class*>(this->diagram->GetAt(position))->AddAssociation(lineX, lineY, lineWidth, lineHeight);
				//}
				//else if (type == 8) {
				//	dynamic_cast<Class*>(this->diagram->GetAt(position))->AddDirectedAssociation(lineX, lineY, lineWidth, lineHeight);
				//}
				//else if (type == 9) {
				//	dynamic_cast<Class*>(this->diagram->GetAt(position))->AddAggregation(lineX, lineY, lineWidth, lineHeight);
				//}
				//else if (type == 10) {
				//	dynamic_cast<Class*>(this->diagram->GetAt(position))->AddAggregations(lineX, lineY, lineWidth, lineHeight);
				//}
				//else if (type == 11) {
				//	dynamic_cast<Class*>(this->diagram->GetAt(position))->AddComposition(lineX, lineY, lineWidth, lineHeight);
				//}
				//else if (type == 12) {
				//	dynamic_cast<Class*>(this->diagram->GetAt(position))->AddCompositions(lineX, lineY, lineWidth, lineHeight);
				//}
				//static_cast<Class*>(this->diagram->GetAt(position))->Add(lineX, lineY, lineWidth, lineHeigth);
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

	if (this->relationButton == false) {//드래그 사각형
		CPen pen;
		pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
		CPen *oldPen = dc.SelectObject(&pen);
		dc.SetBkMode(TRANSPARENT);
		dc.Rectangle(this->startX, this->startY, this->currentX, this->currentY);
		dc.SelectObject(oldPen);
		pen.DeleteObject();
	}
	
	this->diagram->Accept(drawingVisitor, &dc);
	this->text->Accept(writingVisitor, &dc);

	if (this->relationButton == true ){//&& this->startX != this->currentX && this->startY != this->currentY) {
		//일반화
		if (this->generalizationButton == true) {

			dc.MoveTo(this->startX, this->startY);
			dc.LineTo(this->currentX, this->currentY);

			CBrush white(RGB(255, 255, 255));
			CBrush myBrush;
			myBrush.CreateSolidBrush(RGB(255, 255, 255));
			CBrush *oldBrush = dc.SelectObject(&myBrush);

			double degree = atan2(this->currentX - this->startX, this->startY - this->currentY); // 기울기

			double distance = sqrt(pow(this->currentX - this->startX, 2) + pow(this->startY - this->currentY, 2));
			// 루트안에 = 루트(제곱(
			double dX = (this->currentX) - (15 * (this->currentX - this->startX) / distance); //뒤로 온 기준점 x
			double dY = (this->currentY) + (15 * (this->startY - this->currentY) / distance); //뒤로 온 기준점 y

			 // 수직 기울기

			CPoint pts[3];

			pts[0].x = (this->currentX); //마우스 현재위치 점
			pts[0].y = (this->currentY);

			pts[1].x = static_cast<LONG>(dX - 15 * cos(degree)); // 윗점
			pts[1].y = static_cast<LONG>(dY - 15 * sin(degree));

			pts[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // 아랫점
			pts[2].y = static_cast<LONG>(dY + 15 * sin(degree));

			dc.SelectObject(&white);
			dc.Polygon(pts, 3);
			dc.SelectObject(oldBrush);
			myBrush.DeleteObject();
		}

		//실체화
		else if (this->realizationButton == true) {

			CPen pen;
			pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
			CPen *oldPen = dc.SelectObject(&pen);
			dc.SetBkMode(TRANSPARENT);
			dc.MoveTo(this->startX, this->startY);
			dc.LineTo(this->currentX, this->currentY);
			dc.SelectObject(oldPen);
			pen.DeleteObject();

			CBrush white(RGB(255, 255, 255));
			CBrush myBrush;
			myBrush.CreateSolidBrush(RGB(255, 255, 255));
			CBrush *oldBrush = dc.SelectObject(&myBrush);

			double degree = atan2(this->currentX - this->startX, this->startY - this->currentY); // 기울기

			double distance = sqrt(pow(this->currentX - this->startX, 2) + pow(this->startY - this->currentY, 2));
			// 루트안에 = 루트(제곱(
			double dX = (this->currentX) - (15 * (this->currentX - this->startX) / distance); //뒤로 온 기준점 x
			double dY = (this->currentY) + (15 * (this->startY - this->currentY) / distance); //뒤로 온 기준점 y

			 // 수직 기울기

			CPoint pts[3];

			pts[0].x = (this->currentX); //마우스 현재위치 점
			pts[0].y = (this->currentY);

			pts[1].x = static_cast<LONG>(dX - 15 * cos(degree)); // 윗점
			pts[1].y = static_cast<LONG>(dY - 15 * sin(degree));

			pts[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // 아랫점
			pts[2].y = static_cast<LONG>(dY + 15 * sin(degree));

			dc.SelectObject(&white);
			dc.Polygon(pts, 3);
			dc.SelectObject(oldBrush);
			myBrush.DeleteObject();
		}

		//연관화
		else if (this->associationButton == true) {

			dc.MoveTo(this->startX, this->startY);
			dc.LineTo(this->currentX, this->currentY);
		}

		//의존
		else if (this->dependencyButton == true) {

			CPen pen;
			pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
			CPen *oldPen = dc.SelectObject(&pen);
			dc.SetBkMode(TRANSPARENT);
			dc.MoveTo(this->startX, this->startY);
			dc.LineTo(this->currentX, this->currentY);
			dc.SelectObject(oldPen);
			pen.DeleteObject();

			double degree = atan2(this->currentX - this->startX, this->startY - this->currentY); // 기울기

			double distance = sqrt(pow(this->currentX - this->startX, 2) + pow(this->startY - this->currentY, 2));
			// 루트안에 = 루트(제곱(
			double dX = (this->currentX) - (15 * (this->currentX - this->startX) / distance); //뒤로 온 기준점 x
			double dY = (this->currentY) + (15 * (this->startY - this->currentY) / distance); //뒤로 온 기준점 y

			 // 수직 기울기

			CPoint pts[3];

			pts[0].x = (this->currentX); //마우스 현재위치 점
			pts[0].y = (this->currentY);

			pts[1].x = static_cast<LONG>(dX - 15 * cos(degree)); // 윗점
			pts[1].y = static_cast<LONG>(dY - 15 * sin(degree));

			pts[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // 아랫점
			pts[2].y = static_cast<LONG>(dY + 15 * sin(degree));

			dc.MoveTo(pts[0].x, pts[0].y);
			dc.LineTo(pts[1].x, pts[1].y);

			dc.MoveTo(pts[0].x, pts[0].y);
			dc.LineTo(pts[2].x, pts[2].y);
		}

		//직접 연관
		else if (this->directedAssociationButton == true) {

			dc.MoveTo(this->startX, this->startY);
			dc.LineTo(this->currentX, this->currentY);

			double degree = atan2(this->currentX - this->startX, this->startY - this->currentY); // 기울기

			double distance = sqrt(pow(this->currentX - this->startX, 2) + pow(this->startY - this->currentY, 2));
			// 루트안에 = 루트(제곱(
			double dX = (this->currentX) - (15 * (this->currentX - this->startX) / distance); //뒤로 온 기준점 x
			double dY = (this->currentY) + (15 * (this->startY - this->currentY) / distance); //뒤로 온 기준점 y

			 // 수직 기울기

			CPoint pts[3];

			pts[0].x = (this->currentX); //마우스 현재위치 점
			pts[0].y = (this->currentY);

			pts[1].x = static_cast<LONG>(dX - 15 * cos(degree)); // 윗점
			pts[1].y = static_cast<LONG>(dY - 15 * sin(degree));

			pts[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // 아랫점
			pts[2].y = static_cast<LONG>(dY + 15 * sin(degree));

			dc.MoveTo(pts[0].x, pts[0].y);
			dc.LineTo(pts[1].x, pts[1].y);

			dc.MoveTo(pts[0].x, pts[0].y);
			dc.LineTo(pts[2].x, pts[2].y);
		}

		//집합 연관
		else if (this->aggregationSButton == true) {

			dc.MoveTo(this->startX, this->startY);
			dc.LineTo(this->currentX, this->currentY);

			CBrush white(RGB(255, 255, 255));
			CBrush myBrush;
			myBrush.CreateSolidBrush(RGB(255, 255, 255));
			CBrush *oldBrush = dc.SelectObject(&myBrush);

			double degree = atan2(this->currentX - this->startX, this->startY - this->currentY); // 기울기

			double distance = sqrt(pow(this->currentX - this->startX, 2) + pow(this->startY - this->currentY, 2));
			// 루트안에 = 루트(제곱(
			double dX = (this->currentX) - (15 * (this->currentX - this->startX) / distance); //뒤로 온 기준점 x
			double dY = (this->currentY) + (15 * (this->startY - this->currentY) / distance); //뒤로 온 기준점 y

			 // 수직 기울기

			CPoint pts[3];

			pts[0].x = (this->currentX); //마우스 현재위치 점
			pts[0].y = (this->currentY);

			pts[1].x = static_cast<LONG>(dX - 15 * cos(degree)); // 윗점
			pts[1].y = static_cast<LONG>(dY - 15 * sin(degree));

			pts[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // 아랫점
			pts[2].y = static_cast<LONG>(dY + 15 * sin(degree));

			dc.MoveTo(pts[0].x, pts[0].y);
			dc.LineTo(pts[1].x, pts[1].y);

			dc.MoveTo(pts[0].x, pts[0].y);
			dc.LineTo(pts[2].x, pts[2].y);


			//여기까지 화살표 다음부터 마름모

			dX = (this->startX) + (15 * (this->currentX - this->startX) / distance); //뒤로 온 기준점 x
			dY = (this->startY) - (15 * (this->startY - this->currentY) / distance); //뒤로 온 기준점 y

			double dX2 = (this->startX) - ((this->currentX - this->startX) / distance);
			double dY2 = (this->startY) + ((this->startY - this->currentY) / distance);

			CPoint pts2[4];

			pts2[0].x = static_cast<LONG>(dX - 15 * cos(degree)); // 윗점
			pts2[0].y = static_cast<LONG>(dY - 15 * sin(degree));

			pts2[1].x = static_cast<LONG>(dX2); //마우스 처음 점
			pts2[1].y = static_cast<LONG>(dY2);

			pts2[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // 아랫점
			pts2[2].y = static_cast<LONG>(dY + 15 * sin(degree));

			pts2[3].x = static_cast<LONG>(dX) + static_cast<LONG>(15 * (this->currentX - this->startX) / distance); // 윗점
			pts2[3].y = static_cast<LONG>(dY) - static_cast<LONG>(15 * (this->startY - this->currentY) / distance);

			dc.SelectObject(&white);
			dc.Polygon(pts2, 4);
			dc.SelectObject(oldBrush);
			myBrush.DeleteObject();
		}

		//집합
		else if (this->aggregationButton == true) {

			dc.MoveTo(this->startX, this->startY);
			dc.LineTo(this->currentX, this->currentY);

			CBrush white(RGB(255, 255, 255));
			CBrush myBrush;
			myBrush.CreateSolidBrush(RGB(255, 255, 255));
			CBrush *oldBrush = dc.SelectObject(&myBrush);

			double degree = atan2(this->currentX - this->startX, this->startY - this->currentY); // 기울기

			double distance = sqrt(pow(this->currentX - this->startX, 2) + pow(this->startY - this->currentY, 2));

			double dX = (this->startX) + (15 * (this->currentX - this->startX) / distance); //뒤로 온 기준점 x
			double dY = (this->startY) - (15 * (this->startY - this->currentY) / distance); //뒤로 온 기준점 y

			double dX2 = (this->startX) - ((this->currentX - this->startX) / distance);
			double dY2 = (this->startY) + ((this->startY - this->currentY) / distance);

			CPoint pts2[4];

			pts2[0].x = static_cast<LONG>(dX - 15 * cos(degree)); // 윗점
			pts2[0].y = static_cast<LONG>(dY - 15 * sin(degree));

			pts2[1].x = static_cast<LONG>(dX2); //마우스 처음 점
			pts2[1].y = static_cast<LONG>(dY2);

			pts2[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // 아랫점
			pts2[2].y = static_cast<LONG>(dY + 15 * sin(degree));

			pts2[3].x = static_cast<LONG>(dX) + static_cast<LONG>(15 * (this->currentX - this->startX) / distance); // 윗점
			pts2[3].y = static_cast<LONG>(dY) - static_cast<LONG>(15 * (this->startY - this->currentY) / distance);

			dc.SelectObject(&white);
			dc.Polygon(pts2, 4);
			dc.SelectObject(oldBrush);
			myBrush.DeleteObject();
		}

		//합성
		else if (this->compositionButton == true) {

			dc.MoveTo(this->startX, this->startY);
			dc.LineTo(this->currentX, this->currentY);

			CBrush black(RGB(000, 000, 000));
			CBrush myBrush;
			myBrush.CreateSolidBrush(RGB(255, 255, 255));
			CBrush *oldBrush = dc.SelectObject(&myBrush);


			double degree = atan2(this->currentX - this->startX, this->startY - this->currentY); // 기울기

			double distance = sqrt(pow(this->currentX - this->startX, 2) + pow(this->startY - this->currentY, 2));

			double dX = (this->startX) + (15 * (this->currentX - this->startX) / distance); //뒤로 온 기준점 x
			double dY = (this->startY) - (15 * (this->startY - this->currentY) / distance); //뒤로 온 기준점 y

			double dX2 = (this->startX) - ((this->currentX - this->startX) / distance);
			double dY2 = (this->startY) + ((this->startY - this->currentY) / distance);

			CPoint pts2[4];

			pts2[0].x = static_cast<LONG>(dX - 15 * cos(degree)); // 윗점
			pts2[0].y = static_cast<LONG>(dY - 15 * sin(degree));

			pts2[1].x = static_cast<LONG>(dX2); //마우스 처음 점
			pts2[1].y = static_cast<LONG>(dY2);

			pts2[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // 아랫점
			pts2[2].y = static_cast<LONG>(dY + 15 * sin(degree));

			pts2[3].x = static_cast<LONG>(dX) + static_cast<LONG>(15 * (this->currentX - this->startX) / distance); // 윗점
			pts2[3].y = static_cast<LONG>(dY) - static_cast<LONG>(15 * (this->startY - this->currentY) / distance);

			dc.SelectObject(&black);
			dc.Polygon(pts2, 4);
			dc.SelectObject(oldBrush);
			myBrush.DeleteObject();
		}

		//복합연관
		else if (this->compositionSBtton == true) {

			dc.MoveTo(this->startX, this->startY);
			dc.LineTo(this->currentX, this->currentY);

			CBrush black(RGB(000, 000, 000));
			CBrush myBrush;
			myBrush.CreateSolidBrush(RGB(255, 255, 255));
			CBrush *oldBrush = dc.SelectObject(&myBrush);

			double degree = atan2(this->currentX - this->startX, this->startY - this->currentY); // 기울기

			double distance = sqrt(pow(this->currentX - this->startX, 2) + pow(this->startY - this->currentY, 2));
			// 루트안에 = 루트(제곱(
			double dX = (this->currentX) - (15 * (this->currentX - this->startX) / distance); //뒤로 온 기준점 x
			double dY = (this->currentY) + (15 * (this->startY - this->currentY) / distance); //뒤로 온 기준점 y

			 // 수직 기울기
			CPoint pts[3];

			pts[0].x = (this->currentX); //마우스 현재위치 점
			pts[0].y = (this->currentY);

			pts[1].x = static_cast<LONG>(dX - 15 * cos(degree)); // 윗점
			pts[1].y = static_cast<LONG>(dY - 15 * sin(degree));

			pts[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // 아랫점
			pts[2].y = static_cast<LONG>(dY + 15 * sin(degree));

			dc.MoveTo(pts[0].x, pts[0].y);
			dc.LineTo(pts[1].x, pts[1].y);

			dc.MoveTo(pts[0].x, pts[0].y);
			dc.LineTo(pts[2].x, pts[2].y);

			//여기까지 화살표 다음부터 마름모
			distance = sqrt(pow(this->currentX - this->startX, 2) + pow(this->startY - this->currentY, 2));

			dX = (this->startX) + (15 * (this->currentX - this->startX) / distance); //뒤로 온 기준점 x
			dY = (this->startY) - (15 * (this->startY - this->currentY) / distance); //뒤로 온 기준점 y

			double dX2 = (this->startX) - ((this->currentX - this->startX) / distance);
			double dY2 = (this->startY) + ((this->startY - this->currentY) / distance);

			CPoint pts2[4];

			pts2[0].x = static_cast<LONG>(dX - 15 * cos(degree)); // 윗점
			pts2[0].y = static_cast<LONG>(dY - 15 * sin(degree));

			pts2[1].x = static_cast<LONG>(dX2); //마우스 처음 점
			pts2[1].y = static_cast<LONG>(dY2);

			pts2[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // 아랫점
			pts2[2].y = static_cast<LONG>(dY + 15 * sin(degree));

			pts2[3].x = static_cast<LONG>(dX) + static_cast<LONG>(15 * (this->currentX - this->startX) / distance); // 윗점
			pts2[3].y = static_cast<LONG>(dY) - static_cast<LONG>(15 * (this->startY - this->currentY) / distance);

			dc.SelectObject(&black);
			dc.Polygon(pts2, 4);
			dc.SelectObject(oldBrush);
			myBrush.DeleteObject();
		}
	}

	//선택 표시 막아둠
	//if (this->selected != -1) {
	if (this->relationButton == false) {
		Long i = 0;
		while (i < this->selection->GetLength()) {
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
			i++;
		}
	}

}


void ClassDiagramForm::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
	char nCharacter = nChar;
	Long key = -1;

	if (nChar == 48) {
		key = 0;
	}
	if (nChar == 49) {
		key = 1;
	}
	if (nChar == 50) {
		key = 2;
	}
	if (nChar == 51) {
		key = 3;
	}
	if (nChar == 52) {
		key = 4;
	}
	if (nChar == 53) {
		key = 5;
	}
	if (nChar == 54) {
		key = 6;
	}
	if (nChar == 55) {
		key = 7;
	}
	if (nChar == 56) {
		key = 8;
	}
	if (nChar == 57) {
		key = 9;
	}
	if (nChar == 113) {
		key = 10;
	}
	if (nChar == 119) {
		key = 11;
	}
	if (nChar == 101) {
		key = 12;
	}

	this->drawingController->ChangeState(key);

	if (this->text->GetLength() == 0) {
		Row newRow;
		this->text->Add(newRow.Clone());
	} 
	SingleByteCharacter singleByteCharacter(nCharacter);
	this->startX += 10;
	this->text->GetAt(this->rowIndex)->Add(singleByteCharacter.Clone());

	Invalidate();
}

void ClassDiagramForm::OnSetFocus(CWnd* pOldWnd) {

	this->Invalidate();
}

void ClassDiagramForm::OnLButtonDown(UINT nFlags, CPoint point) {
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

	//this->currentClassIndex = -1;
	//this->currentClassIndex = this->selection->FindByPoint(this->diagram, this->startX, this->startY);
	if (this->currentClassIndex >= 0) { //클릭한 위치에 클래스가 있었다면
		this->textEdit = new TextEdit(this, // 텍스트에딧 크기는 클래스 크기, 일단은
			this->diagram->GetAt(currentClassIndex)->GetX() + 5,
			this->diagram->GetAt(currentClassIndex)->GetY() + 33,
			this->diagram->GetAt(currentClassIndex)->GetWidth() - 5,
			this->diagram->GetAt(currentClassIndex)->GetHeight() - 5);

		this->textEdit->Create(NULL, "textEdit", WS_DLGFRAME, CRect(
			this->textEdit->GetFormX(),
			this->textEdit->GetFormY(),
			this->textEdit->GetFormX() + this->textEdit->GetWidth(),
			this->textEdit->GetFormY() + this->textEdit->GetHeight()), NULL, NULL, WS_EX_TOPMOST);
		this->textEdit->ShowWindow(SW_SHOW);
	}
}

void ClassDiagramForm::OnLButtonUp(UINT nFlags, CPoint point) {
	this->currentX = point.x;
	this->currentY = point.y;


	if (this->classButton == true) {
		if (this->currentX != this->startX && this->currentY != this->startY) {
			if (this->currentX - this->startX < 150) {
				this->currentX = this->startX + 150;
			}
			if (this->currentY - this->startY < 200) {
				this->currentY = this->startY + 200;
			}
			Long index = this->diagram->AddClass(this->startX, this->startY, this->currentX - this->startX, this->currentY - this->startY);

			//첨자연산자 왜 안돼는지 확인해야함
			static_cast<Class*>(this->diagram->GetAt(index))->Add(this->startX, this->startY + 50,
				this->currentX - this->startX, this->startY + 50);
			static_cast<Class*>(this->diagram->GetAt(index))->Add(this->startX, (this->startY + 50 + this->currentY) / 2,
				this->currentX - this->startX, (this->startY + 50 + this->currentY) / 2);

			this->textEdit = new TextEdit(this, // 텍스트에딧 크기는 클래스 크기, 일단은
				this->diagram->GetAt(index)->GetX() + 5,
				this->diagram->GetAt(index)->GetY() + 33,
				this->diagram->GetAt(index)->GetWidth() - 5,
				this->diagram->GetAt(index)->GetHeight() - 100);

			this->textEdit->Create(NULL, "textEdit", WS_DLGFRAME, CRect(
				this->textEdit->GetFormX(),
				this->textEdit->GetFormY(),
				this->textEdit->GetFormX() + this->textEdit->GetWidth(),
				this->textEdit->GetFormY() + this->textEdit->GetHeight() - 100), NULL, NULL, WS_EX_TOPMOST);
			this->textEdit->ShowWindow(SW_SHOW);
		}
	}
	//if (this->memoBoxButton == true) {
	//	if (this->currentX - this->startX < 100) {
	//		this->currentX = this->startX + 100;
	//	}
	//	if (this->currentY - this->startY < 80) {
	//		this->currentY = this->startY + 80;
	//	}
	//	this->diagram->AddMemoBox(this->startX, this->startY, this->currentX - this->startX, this->currentY - this->startY);
	//}

	//if (templateButton == true && this->selection->GetLength() == 1) {
	//	Class *object;
	//	object = dynamic_cast<Class*>(this->selection->GetAt(0));
	//	object->AddTemplate(object->GetX() + object->GetWidth() - 70, object->GetY() - 15, 80, 25);
	//}

	//if (this->relationButton == true && this->selection->GetLength() == 1) {
	//	//Long endClass = this->diagram->Find(this->currentX, this->currentY);//자기자신 연결시 0 0 0 0 값 저장됨.. 수정요 2017_09_09
	//	Long x = this->currentX;
	//	Long y = this->currentY;
	//	this->selection->FindByPoint(this->diagram, x, y);
	//	if (this->selection->GetLength() == 2 && this->selection->GetAt(0) != this->selection->GetAt(1)) {
	//		
	//		CPoint line1Start;
	//		CPoint line1End;
	//		CPoint line2Start;
	//		CPoint line2End;
	//		CPoint cross1;
	//		CPoint cross2;

	//		line1Start.x = this->startX;
	//		line1Start.y = this->startY;
	//		line1End.x = this->currentX;
	//		line1End.y = this->currentY;

	//		bool startClassCheck = false;
	//		if (startClassCheck == false) {//시작 클래스에서 선과 교차하는 면 찾기
	//			//상단
	//			line2Start.x = this->selection->GetAt(0)->GetX();
	//			line2Start.y = this->selection->GetAt(0)->GetY();
	//			line2End.x = this->selection->GetAt(0)->GetX() + this->selection->GetAt(0)->GetWidth();
	//			line2End.y = this->selection->GetAt(0)->GetY();
	//			startClassCheck = this->FindCrossPoint(line1Start, line1End, line2Start, line2End, &cross1);
	//		}
	//		if (startClassCheck == false) {
	//			//좌측
	//			line2Start.x = this->selection->GetAt(0)->GetX();
	//			line2Start.y = this->selection->GetAt(0)->GetY();
	//			line2End.x = this->selection->GetAt(0)->GetX();
	//			line2End.y = this->selection->GetAt(0)->GetY() + this->selection->GetAt(0)->GetHeight();
	//			startClassCheck = this->FindCrossPoint(line1Start, line1End, line2Start, line2End, &cross1);
	//		}
	//		if (startClassCheck == false) {
	//			//우측
	//			line2Start.x = this->selection->GetAt(0)->GetX() + this->selection->GetAt(0)->GetWidth();
	//			line2Start.y = this->selection->GetAt(0)->GetY();
	//			line2End.x = this->selection->GetAt(0)->GetX() + this->selection->GetAt(0)->GetWidth();
	//			line2End.y = this->selection->GetAt(0)->GetY() + this->selection->GetAt(0)->GetHeight();
	//			startClassCheck = this->FindCrossPoint(line1Start, line1End, line2Start, line2End, &cross1);
	//		}
	//		if (startClassCheck == false) {
	//			//하단
	//			line2Start.x = this->selection->GetAt(0)->GetX();
	//			line2Start.y = this->selection->GetAt(0)->GetY() + this->selection->GetAt(0)->GetHeight();
	//			line2End.x = this->selection->GetAt(0)->GetX() + this->selection->GetAt(0)->GetWidth();
	//			line2End.y = this->selection->GetAt(0)->GetY() + this->selection->GetAt(0)->GetHeight();
	//			startClassCheck = this->FindCrossPoint(line1Start, line1End, line2Start, line2End, &cross1);
	//		}

	//		bool endClassCheck = false;
	//		if (endClassCheck == false) {//끝 클래스에서 선과 교차하는 면 찾기
	//			//상단
	//			line2Start.x = this->selection->GetAt(1)->GetX();
	//			line2Start.y = this->selection->GetAt(1)->GetY();
	//			line2End.x = this->selection->GetAt(1)->GetX() + this->selection->GetAt(1)->GetWidth();
	//			line2End.y = this->selection->GetAt(1)->GetY();
	//			endClassCheck = this->FindCrossPoint(line1Start, line1End, line2Start, line2End, &cross2);
	//		}
	//		if (endClassCheck == false) {
	//			//좌측
	//			line2Start.x = this->selection->GetAt(1)->GetX();
	//			line2Start.y = this->selection->GetAt(1)->GetY();
	//			line2End.x = this->selection->GetAt(1)->GetX();
	//			line2End.y = this->selection->GetAt(1)->GetY() + this->selection->GetAt(1)->GetHeight();
	//			endClassCheck = this->FindCrossPoint(line1Start, line1End, line2Start, line2End, &cross2);
	//		}
	//		if (endClassCheck == false) {
	//			//우측
	//			line2Start.x = this->selection->GetAt(1)->GetX() + this->selection->GetAt(1)->GetWidth();
	//			line2Start.y = this->selection->GetAt(1)->GetY();
	//			line2End.x = this->selection->GetAt(1)->GetX() + this->selection->GetAt(1)->GetWidth();
	//			line2End.y = this->selection->GetAt(1)->GetY() + this->selection->GetAt(1)->GetHeight();
	//			endClassCheck = this->FindCrossPoint(line1Start, line1End, line2Start, line2End, &cross2);
	//		}
	//		if (endClassCheck == false) {
	//			//하단
	//			line2Start.x = this->selection->GetAt(1)->GetX();
	//			line2Start.y = this->selection->GetAt(1)->GetY() + this->selection->GetAt(1)->GetHeight();
	//			line2End.x = this->selection->GetAt(1)->GetX() + this->selection->GetAt(1)->GetWidth();
	//			line2End.y = this->selection->GetAt(1)->GetY() + this->selection->GetAt(1)->GetHeight();
	//			endClassCheck = this->FindCrossPoint(line1Start, line1End, line2Start, line2End, &cross2);
	//		}

	//		if (this->generalizationButton == true) {
	//			dynamic_cast<Class*>(this->selection->GetAt(0))->AddGeneralization(cross1.x, cross1.y, cross2.x- cross1.x, cross2.y- cross1.y);
	//			//Invalidate();
	//		}
	//		else if (this->realizationButton == true) {
	//			dynamic_cast<Class*>(this->selection->GetAt(0))->AddRealization(cross1.x, cross1.y, cross2.x - cross1.x, cross2.y - cross1.y);
	//			//Invalidate();
	//		}
	//		else if (this->associationButton == true) {
	//			dynamic_cast<Class*>(this->selection->GetAt(0))->AddAssociation(cross1.x, cross1.y, cross2.x - cross1.x, cross2.y - cross1.y);
	//			//Invalidate();
	//		}
	//		else if (this->dependencyButton == true) {
	//			dynamic_cast<Class*>(this->selection->GetAt(0))->AddDependency(cross1.x, cross1.y, cross2.x - cross1.x, cross2.y - cross1.y);
	//			//Invalidate();
	//		}
	//		else if (this->directedAssociationButton == true) {
	//			dynamic_cast<Class*>(this->selection->GetAt(0))->AddDirectedAssociation(cross1.x, cross1.y, cross2.x - cross1.x, cross2.y - cross1.y);
	//			//Invalidate();
	//		}
	//		else if (this->aggregationButton == true) {
	//			dynamic_cast<Class*>(this->selection->GetAt(0))->AddAggregation(cross1.x, cross1.y, cross2.x - cross1.x, cross2.y - cross1.y);
	//			//Invalidate();
	//		}
	//		else if (this->aggregationSButton == true) {
	//			dynamic_cast<Class*>(this->selection->GetAt(0))->AddAggregations(cross1.x, cross1.y, cross2.x - cross1.x, cross2.y - cross1.y);
	//			//Invalidate();
	//		}
	//		else if (this->compositionButton == true) {
	//			dynamic_cast<Class*>(this->selection->GetAt(0))->AddComposition(cross1.x, cross1.y, cross2.x - cross1.x, cross2.y - cross1.y);
	//			//Invalidate();
	//		}
	//		else if (this->compositionSBtton == true) {
	//			dynamic_cast<Class*>(this->selection->GetAt(0))->AddCompositions(cross1.x, cross1.y, cross2.x - cross1.x, cross2.y - cross1.y);
	//			//Invalidate();
	//		}
	//	}
	//}
	
	/*if (this->relationButton == false) {
		CRect rect;
		rect.left = this->startX;
		rect.top = this->startY;
		rect.right = this->currentX;
		rect.bottom = this->currentY;
		if (this->startX == this->currentX && this->startY == this->startY) {
			this->selection->FindByPoint(this->diagram, this->currentX, this->currentY);
		}
		else {
			this->selection->FindByArea(this->diagram, rect);
		}
	}*/
	this->drawingController->AddToArray(this->diagram, this->selection, this->startX, this->startY, this->currentX, this->currentY);
	/*Long length = this->selection->GetLength();
	this->startX = 0;
	this->startY = 0;
	this->currentX = 0;
	this->currentY = 0;*/

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
	//6.3. 윈도우를 닫는다.
	CFrameWnd::OnClose(); // 오버라이딩 코드재사용
}





