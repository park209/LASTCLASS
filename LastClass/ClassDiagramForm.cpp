//ClassDiagramForm.cpp

#include "ClassDiagramForm.h"
//#include "Figure.h"
#include "Diagram.h"
#include "DrawingVisitor.h"
#include "Text.h"
#include "SingleByteCharacter.h"
#include "WritingVisitor.h"
#include <math.h>

#include <iostream>
#include <fstream>

using namespace std;

BEGIN_MESSAGE_MAP(ClassDiagramForm, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_CHAR()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

ClassDiagramForm::ClassDiagramForm() { // 생성자 맞는듯
	this->diagram = NULL;
	this->text = NULL;
	this->startX = 0;
	this->startY = 0;
	this->currentX = 0;
	this->currentY = 0;
	this->rowIndex = 0;
	this->characterIndex = 0;
	this->selected = -1;
	this->classButton = false;
	this->relationButton = true;
	this->generalizationButton = false; //일반화
	this->realizationButton = false; //실체화
	this->dependencyButton = false; //의존
	this->associationButton = false; //연관화
	this->directedAssociationButton = false; //직접연관
	this->aggregationButton = false; // 집합
	this->aggregationSButton = true; // 집합연관
	this->compositionButton = false; // 합성
	this->compositionSBtton = false; // 복합연관
}

Long ClassDiagramForm::Save() {
   Long i = 0;
   Long j;
   ofstream fClass;
   ofstream fLine; // 읽을때는 of

   fClass.open("ClassSave.txt");
   fLine.open("LineSave.txt");
   if (fClass.is_open() && fLine.is_open()) {
      while (i < this->diagram->GetLength()) {
         Class object;
         object = *(this->diagram->GetAt(i));
         fClass << object.GetLength() << " " << object.GetX() << " " << object.GetY()
            << " " << object.GetWidth() << " " << object.GetHeight() << endl;
         j = 0;
         while (j < object.GetLength()) {
            Line *lineObject;
			Relation *relationObject;
			if(dynamic_cast<Line*>(object.GetAt(j))) {
				lineObject = (dynamic_cast<Line*>(object.GetAt(j)));
				fLine << lineObject->GetX() << " " << lineObject->GetY() << " " <<
					lineObject->GetWidth() << " " << lineObject->GetHeight() << endl;
			}
			else if (dynamic_cast<Relation*>(object.GetAt(j))) {
				relationObject = (dynamic_cast<Relation*>(object.GetAt(j)));

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
	Long position;
	Long i;
	Long x;
	Long y;
	Long width;
	Long height;
	Long length;
	Long lineX;
	Long lineY;
	Long lineWidth;
	Long lineHeigth;
	ifstream fClass;
	ifstream fLine;

	fClass.open("ClassSave.txt");
	fLine.open("LineSave.txt");

	if (fClass.is_open() && fLine.is_open()) {
		fClass >> length >> x >> y >> width >> height;
		while (!fClass.eof()) {
			position = this->diagram->Add(x, y, width, height);
			i = 0;
			while (i < length) {
				fLine >> lineX >> lineY >> lineWidth >> lineHeigth;
				static_cast<Class*>(this->diagram->GetAt(position))->Add(lineX, lineY, lineWidth, lineHeigth);
				i++;
			}
			fClass >> length >> x >> y >> width >> height;
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

	//1.2. 적재한다
	this->Load();

	//1.3. 윈도우를 갱신한다
	Invalidate();

	return 0;
}

void ClassDiagramForm::OnPaint() {
	CPaintDC dc(this);

	DrawingVisitor drawingVisitor;
	WritingVisitor writingVisitor;

	if (this->classButton == true) {//&& this->relationButton == true //드래그 사각형
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

	if (this->relationButton == true && this->startX != this->currentX && this->startY != this->currentY) {

		//일반화
		if (this->generalizationButton == true) {

			CPen pen;
			//pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
			CPen *oldPen = dc.SelectObject(&pen);
			dc.SetBkMode(TRANSPARENT);
			dc.MoveTo(this->startX, this->startY);
			dc.LineTo(this->currentX, this->currentY);

			CBrush white(RGB(255, 255, 255));
			CBrush black(RGB(000, 000, 000));
			CBrush myBrush;
			myBrush.CreateSolidBrush(RGB(255, 255, 255));
			CBrush *oldBrush = dc.SelectObject(&myBrush);
			CPoint pts[3];

			double degree = atan2(this->currentX - this->startX, this->startY - this->currentY); // 기울기

			double distance = sqrt(pow(this->currentX - this->startX, 2) + pow(this->startY - this->currentY, 2));
			// 루트안에 = 루트(제곱(
			double dX = (this->currentX) - (15 * (this->currentX - this->startX) / distance); //뒤로 온 기준점 x
			double dY = (this->currentY) + (15 * (this->startY - this->currentY) / distance); //뒤로 온 기준점 y

			 // 수직 기울기

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
			dc.SelectObject(oldPen);
			pen.DeleteObject();
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
			CBrush black(RGB(000, 000, 000));
			CBrush myBrush;
			myBrush.CreateSolidBrush(RGB(255, 255, 255));
			CBrush *oldBrush = dc.SelectObject(&myBrush);
			CPoint pts[3];

			double degree = atan2(this->currentX - this->startX, this->startY - this->currentY); // 기울기

			double distance = sqrt(pow(this->currentX - this->startX, 2) + pow(this->startY - this->currentY, 2));
			// 루트안에 = 루트(제곱(
			double dX = (this->currentX) - (15 * (this->currentX - this->startX) / distance); //뒤로 온 기준점 x
			double dY = (this->currentY) + (15 * (this->startY - this->currentY) / distance); //뒤로 온 기준점 y

			 // 수직 기울기

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
			dc.SelectObject(oldPen);
			pen.DeleteObject();
		}

		//연관화
		else if (this->associationButton == true) {


			CPen pen;

			CPen *oldPen = dc.SelectObject(&pen);
			dc.SetBkMode(TRANSPARENT);
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

			CBrush white(RGB(255, 255, 255));
			CBrush black(RGB(000, 000, 000));
			CBrush myBrush;
			myBrush.CreateSolidBrush(RGB(255, 255, 255));
			CBrush *oldBrush = dc.SelectObject(&myBrush);
			CPoint pts[3];

			double degree = atan2(this->currentX - this->startX, this->startY - this->currentY); // 기울기

			double distance = sqrt(pow(this->currentX - this->startX, 2) + pow(this->startY - this->currentY, 2));
			// 루트안에 = 루트(제곱(
			double dX = (this->currentX) - (15 * (this->currentX - this->startX) / distance); //뒤로 온 기준점 x
			double dY = (this->currentY) + (15 * (this->startY - this->currentY) / distance); //뒤로 온 기준점 y

			 // 수직 기울기

			pts[0].x = (this->currentX); //마우스 현재위치 점
			pts[0].y = (this->currentY);

			pts[1].x = static_cast<LONG>(dX - 15 * cos(degree)); // 윗점
			pts[1].y = static_cast<LONG>(dY - 15 * sin(degree));

			pts[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // 아랫점
			pts[2].y = static_cast<LONG>(dY + 15 * sin(degree));

			dc.SetBkMode(TRANSPARENT);
			dc.MoveTo(pts[0].x, pts[0].y);
			dc.LineTo(pts[1].x, pts[1].y);
			dc.SelectObject(oldPen);
			pen.DeleteObject();

			dc.SetBkMode(TRANSPARENT);
			dc.MoveTo(pts[0].x, pts[0].y);
			dc.LineTo(pts[2].x, pts[2].y);
			dc.SelectObject(oldPen);
			pen.DeleteObject();
		}

		//직접 연관
		else if (this->directedAssociationButton == true) {

			CPen pen;

			CPen *oldPen = dc.SelectObject(&pen);
			dc.SetBkMode(TRANSPARENT);
			dc.MoveTo(this->startX, this->startY);
			dc.LineTo(this->currentX, this->currentY);
			dc.SelectObject(oldPen);
			pen.DeleteObject();

			CBrush white(RGB(255, 255, 255));
			CBrush black(RGB(000, 000, 000));
			CBrush myBrush;
			myBrush.CreateSolidBrush(RGB(255, 255, 255));
			CBrush *oldBrush = dc.SelectObject(&myBrush);
			CPoint pts[3];

			double degree = atan2(this->currentX - this->startX, this->startY - this->currentY); // 기울기

			double distance = sqrt(pow(this->currentX - this->startX, 2) + pow(this->startY - this->currentY, 2));
			// 루트안에 = 루트(제곱(
			double dX = (this->currentX) - (15 * (this->currentX - this->startX) / distance); //뒤로 온 기준점 x
			double dY = (this->currentY) + (15 * (this->startY - this->currentY) / distance); //뒤로 온 기준점 y

			 // 수직 기울기

			pts[0].x = (this->currentX); //마우스 현재위치 점
			pts[0].y = (this->currentY);

			pts[1].x = static_cast<LONG>(dX - 15 * cos(degree)); // 윗점
			pts[1].y = static_cast<LONG>(dY - 15 * sin(degree));

			pts[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // 아랫점
			pts[2].y = static_cast<LONG>(dY + 15 * sin(degree));

			dc.SetBkMode(TRANSPARENT);
			dc.MoveTo(pts[0].x, pts[0].y);
			dc.LineTo(pts[1].x, pts[1].y);
			dc.SelectObject(oldPen);
			pen.DeleteObject();

			dc.SetBkMode(TRANSPARENT);
			dc.MoveTo(pts[0].x, pts[0].y);
			dc.LineTo(pts[2].x, pts[2].y);
			dc.SelectObject(oldPen);
			pen.DeleteObject();
		}

		//집합 연관
		else if (this->aggregationSButton == true) {

			CPen pen;

			CPen *oldPen = dc.SelectObject(&pen);
			dc.SetBkMode(TRANSPARENT);
			dc.MoveTo(this->startX, this->startY);
			dc.LineTo(this->currentX, this->currentY);
			dc.SelectObject(oldPen);
			pen.DeleteObject();

			CBrush white(RGB(255, 255, 255));
			CBrush black(RGB(000, 000, 000));
			CBrush myBrush;
			myBrush.CreateSolidBrush(RGB(255, 255, 255));
			CBrush *oldBrush = dc.SelectObject(&myBrush);
			CPoint pts[3];

			double degree = atan2(this->currentX - this->startX, this->startY - this->currentY); // 기울기

			double distance = sqrt(pow(this->currentX - this->startX, 2) + pow(this->startY - this->currentY, 2));
			// 루트안에 = 루트(제곱(
			double dX = (this->currentX) - (15 * (this->currentX - this->startX) / distance); //뒤로 온 기준점 x
			double dY = (this->currentY) + (15 * (this->startY - this->currentY) / distance); //뒤로 온 기준점 y

			 // 수직 기울기

			pts[0].x = (this->currentX); //마우스 현재위치 점
			pts[0].y = (this->currentY);

			pts[1].x = static_cast<LONG>(dX - 15 * cos(degree)); // 윗점
			pts[1].y = static_cast<LONG>(dY - 15 * sin(degree));

			pts[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // 아랫점
			pts[2].y = static_cast<LONG>(dY + 15 * sin(degree));

			dc.SetBkMode(TRANSPARENT);
			dc.MoveTo(pts[0].x, pts[0].y);
			dc.LineTo(pts[1].x, pts[1].y);
			dc.SelectObject(oldPen);
			pen.DeleteObject();

			dc.SetBkMode(TRANSPARENT);
			dc.MoveTo(pts[0].x, pts[0].y);
			dc.LineTo(pts[2].x, pts[2].y);
			dc.SelectObject(oldPen);
			pen.DeleteObject();
			//여기까지 화살표 다음부터 마름모
			distance = sqrt(pow(this->currentX - this->startX, 2) + pow(this->startY - this->currentY, 2));

			dX = (this->startX) + (15 * (this->currentX - this->startX) / distance); //뒤로 온 기준점 x



			dY = (this->startY) - (15 * (this->startY - this->currentY) / distance); //뒤로 온 기준점 y

			double dX2 = (this->startX) - ((this->currentX - this->startX) / distance);

			double dY2 = (this->startY) + ((this->startY - this->currentY) / distance);

			CPoint pts2[4];
			pts2[1].x = static_cast<LONG>(dX2); //마우스 처음 점
			pts2[1].y = static_cast<LONG>(dY2);

			pts2[0].x = static_cast<LONG>(dX - 15 * cos(degree)); // 윗점
			pts2[0].y = static_cast<LONG>(dY - 15 * sin(degree));

			pts2[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // 아랫점
			pts2[2].y = static_cast<LONG>(dY + 15 * sin(degree));

			pts2[3].x = static_cast<LONG>(dX) + static_cast<LONG>(15 * (this->currentX - this->startX) / distance); // 윗점
			pts2[3].y = static_cast<LONG>(dY) - static_cast<LONG>(15 * (this->startY - this->currentY) / distance);

			dc.SelectObject(&white);
			dc.Polygon(pts2, 4);
			dc.SelectObject(oldBrush);
			myBrush.DeleteObject();
			dc.SelectObject(oldPen);
			pen.DeleteObject();
		}

		//집합
		else if (this->aggregationButton == true) {

			CPen pen;

			CPen *oldPen = dc.SelectObject(&pen);
			dc.SetBkMode(TRANSPARENT);
			dc.MoveTo(this->startX, this->startY);
			dc.LineTo(this->currentX, this->currentY);
			dc.SelectObject(oldPen);
			pen.DeleteObject();

			CBrush white(RGB(255, 255, 255));
			CBrush black(RGB(000, 000, 000));
			CBrush myBrush;
			myBrush.CreateSolidBrush(RGB(255, 255, 255));
			CBrush *oldBrush = dc.SelectObject(&myBrush);
			CPoint pts[3];

			double degree = atan2(this->currentX - this->startX, this->startY - this->currentY); // 기울기

			double distance = sqrt(pow(this->currentX - this->startX, 2) + pow(this->startY - this->currentY, 2));
			// 루트안에 = 루트(제곱(
			double dX = (this->currentX) - (15 * (this->currentX - this->startX) / distance); //뒤로 온 기준점 x
			double dY = (this->currentY) + (15 * (this->startY - this->currentY) / distance); //뒤로 온 기준점 y

			 // 수직 기울기

			//여기까지 화살표 다음부터 마름모
			distance = sqrt(pow(this->currentX - this->startX, 2) + pow(this->startY - this->currentY, 2));

			dX = (this->startX) + (15 * (this->currentX - this->startX) / distance); //뒤로 온 기준점 x
			dY = (this->startY) - (15 * (this->startY - this->currentY) / distance); //뒤로 온 기준점 y

			double dX2 = (this->startX) - ((this->currentX - this->startX) / distance);

			double dY2 = (this->startY) + ((this->startY - this->currentY) / distance);

			CPoint pts2[4];
			pts2[1].x = static_cast<LONG>(dX2); //마우스 처음 점
			pts2[1].y = static_cast<LONG>(dY2);

			pts2[0].x = static_cast<LONG>(dX - 15 * cos(degree)); // 윗점
			pts2[0].y = static_cast<LONG>(dY - 15 * sin(degree));

			pts2[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // 아랫점
			pts2[2].y = static_cast<LONG>(dY + 15 * sin(degree));

			pts2[3].x = static_cast<LONG>(dX) + static_cast<LONG>(15 * (this->currentX - this->startX) / distance); // 윗점
			pts2[3].y = static_cast<LONG>(dY) - static_cast<LONG>(15 * (this->startY - this->currentY) / distance);

			dc.SelectObject(&white);
			dc.Polygon(pts2, 4);
			dc.SelectObject(oldBrush);
			myBrush.DeleteObject();
			dc.SelectObject(oldPen);
			pen.DeleteObject();
		}

		//합성
		else if (this->compositionButton == true) {

			CPen pen;

			CPen *oldPen = dc.SelectObject(&pen);
			dc.SetBkMode(TRANSPARENT);
			dc.MoveTo(this->startX, this->startY);
			dc.LineTo(this->currentX, this->currentY);
			dc.SelectObject(oldPen);
			pen.DeleteObject();

			CBrush white(RGB(255, 255, 255));
			CBrush black(RGB(000, 000, 000));
			CBrush myBrush;
			myBrush.CreateSolidBrush(RGB(255, 255, 255));
			CBrush *oldBrush = dc.SelectObject(&myBrush);
			CPoint pts[3];

			double degree = atan2(this->currentX - this->startX, this->startY - this->currentY); // 기울기

			double distance = sqrt(pow(this->currentX - this->startX, 2) + pow(this->startY - this->currentY, 2));
			// 루트안에 = 루트(제곱(
			double dX = (this->currentX) - (15 * (this->currentX - this->startX) / distance); //뒤로 온 기준점 x
			double dY = (this->currentY) + (15 * (this->startY - this->currentY) / distance); //뒤로 온 기준점 y

																							  // 수직 기울기


																							  //여기까지 화살표 다음부터 마름모
			distance = sqrt(pow(this->currentX - this->startX, 2) + pow(this->startY - this->currentY, 2));

			dX = (this->startX) + (15 * (this->currentX - this->startX) / distance); //뒤로 온 기준점 x
			dY = (this->startY) - (15 * (this->startY - this->currentY) / distance); //뒤로 온 기준점 y

			double dX2 = (this->startX) - ((this->currentX - this->startX) / distance);

			double dY2 = (this->startY) + ((this->startY - this->currentY) / distance);

			CPoint pts2[4];
			pts2[1].x = static_cast<LONG>(dX2); //마우스 처음 점
			pts2[1].y = static_cast<LONG>(dY2);

			pts2[0].x = static_cast<LONG>(dX - 15 * cos(degree)); // 윗점
			pts2[0].y = static_cast<LONG>(dY - 15 * sin(degree));

			pts2[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // 아랫점
			pts2[2].y = static_cast<LONG>(dY + 15 * sin(degree));

			pts2[3].x = static_cast<LONG>(dX) + static_cast<LONG>(15 * (this->currentX - this->startX) / distance); // 윗점
			pts2[3].y = static_cast<LONG>(dY) - static_cast<LONG>(15 * (this->startY - this->currentY) / distance);

			dc.SelectObject(&black);
			dc.Polygon(pts2, 4);
			dc.SelectObject(oldBrush);
			myBrush.DeleteObject();
			dc.SelectObject(oldPen);
			pen.DeleteObject();
		}
		//복합연관
		else if (this->compositionSBtton == true) {

			CPen pen;

			CPen *oldPen = dc.SelectObject(&pen);
			dc.SetBkMode(TRANSPARENT);
			dc.MoveTo(this->startX, this->startY);
			dc.LineTo(this->currentX, this->currentY);
			dc.SelectObject(oldPen);
			pen.DeleteObject();

			CBrush white(RGB(255, 255, 255));
			CBrush black(RGB(000, 000, 000));
			CBrush myBrush;
			myBrush.CreateSolidBrush(RGB(255, 255, 255));
			CBrush *oldBrush = dc.SelectObject(&myBrush);
			CPoint pts[3];

			double degree = atan2(this->currentX - this->startX, this->startY - this->currentY); // 기울기

			double distance = sqrt(pow(this->currentX - this->startX, 2) + pow(this->startY - this->currentY, 2));
			// 루트안에 = 루트(제곱(
			double dX = (this->currentX) - (15 * (this->currentX - this->startX) / distance); //뒤로 온 기준점 x
			double dY = (this->currentY) + (15 * (this->startY - this->currentY) / distance); //뒤로 온 기준점 y

			 // 수직 기울기

			pts[0].x = (this->currentX); //마우스 현재위치 점
			pts[0].y = (this->currentY);

			pts[1].x = static_cast<LONG>(dX - 15 * cos(degree)); // 윗점
			pts[1].y = static_cast<LONG>(dY - 15 * sin(degree));

			pts[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // 아랫점
			pts[2].y = static_cast<LONG>(dY + 15 * sin(degree));

			dc.SetBkMode(TRANSPARENT);
			dc.MoveTo(pts[0].x, pts[0].y);
			dc.LineTo(pts[1].x, pts[1].y);
			dc.SelectObject(oldPen);
			pen.DeleteObject();

			dc.SetBkMode(TRANSPARENT);
			dc.MoveTo(pts[0].x, pts[0].y);
			dc.LineTo(pts[2].x, pts[2].y);
			dc.SelectObject(oldPen);
			pen.DeleteObject();
			//여기까지 화살표 다음부터 마름모
			distance = sqrt(pow(this->currentX - this->startX, 2) + pow(this->startY - this->currentY, 2));

			dX = (this->startX) + (15 * (this->currentX - this->startX) / distance); //뒤로 온 기준점 x



			dY = (this->startY) - (15 * (this->startY - this->currentY) / distance); //뒤로 온 기준점 y

			double dX2 = (this->startX) - ((this->currentX - this->startX) / distance);

			double dY2 = (this->startY) + ((this->startY - this->currentY) / distance);

			CPoint pts2[4];
			pts2[1].x = static_cast<LONG>(dX2); //마우스 처음 점
			pts2[1].y = static_cast<LONG>(dY2);

			pts2[0].x = static_cast<LONG>(dX - 15 * cos(degree)); // 윗점
			pts2[0].y = static_cast<LONG>(dY - 15 * sin(degree));

			pts2[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // 아랫점
			pts2[2].y = static_cast<LONG>(dY + 15 * sin(degree));

			pts2[3].x = static_cast<LONG>(dX) + static_cast<LONG>(15 * (this->currentX - this->startX) / distance); // 윗점
			pts2[3].y = static_cast<LONG>(dY) - static_cast<LONG>(15 * (this->startY - this->currentY) / distance);

			dc.SelectObject(&black);
			dc.Polygon(pts2, 4);
			dc.SelectObject(oldBrush);
			myBrush.DeleteObject();
			dc.SelectObject(oldPen);
			pen.DeleteObject();
		}
	}

	if (this->selected != -1) {
		dc.Rectangle(this->diagram->GetAt(this->selected)->GetX() - 5,
			this->diagram->GetAt(this->selected)->GetY() - 5,
			this->diagram->GetAt(this->selected)->GetX() + 5,
			this->diagram->GetAt(this->selected)->GetY() + 5);
		dc.Rectangle(this->diagram->GetAt(this->selected)->GetX() + this->diagram->GetAt(this->selected)->GetWidth() - 5,
			this->diagram->GetAt(this->selected)->GetY() - 5,
			this->diagram->GetAt(this->selected)->GetX() + this->diagram->GetAt(this->selected)->GetWidth() + 5,
			this->diagram->GetAt(this->selected)->GetY() + 5);
		dc.Rectangle(this->diagram->GetAt(this->selected)->GetX() - 5,
			this->diagram->GetAt(this->selected)->GetY() + this->diagram->GetAt(this->selected)->GetHeight() - 5,
			this->diagram->GetAt(this->selected)->GetX() + 5,
			this->diagram->GetAt(this->selected)->GetY() + this->diagram->GetAt(this->selected)->GetHeight() + 5);
		dc.Rectangle(this->diagram->GetAt(this->selected)->GetX() + this->diagram->GetAt(this->selected)->GetWidth() - 5,
			this->diagram->GetAt(this->selected)->GetY() + this->diagram->GetAt(this->selected)->GetHeight() - 5,
			this->diagram->GetAt(this->selected)->GetX() + this->diagram->GetAt(this->selected)->GetWidth() + 5,
			this->diagram->GetAt(this->selected)->GetY() + this->diagram->GetAt(this->selected)->GetHeight() + 5);
	}

}


void ClassDiagramForm::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
	char nCharacter = nChar;

	if (this->text->GetLength() == 0) {
		Row newRow;
		this->text->Add(newRow.Clone());
	}
	SingleByteCharacter singleByteCharacter(nCharacter, this->text->GetAt(this->rowIndex)->GetLength(), this->startX+10, this->startY+5);
	this->startX += 10;
	this->text->GetAt(this->rowIndex)->Add(singleByteCharacter.Clone());
	//엔터누르거나(rowIndex+1) 다른 text로 이동하면 rowIndex 바뀌게 해야할듯

	Invalidate();
}

void ClassDiagramForm::OnLButtonDown(UINT nFlags, CPoint point) {
	this->startX = point.x;
	this->startY = point.y;
	this->currentX = point.x;
	this->currentY = point.y;
	this->selected=this->diagram->Find(this->currentX, this->currentY);
	//if (this->selected != -1 ) {
		Invalidate();
	//}
}

void ClassDiagramForm::OnLButtonUp(UINT nFlags, CPoint point) {
	this->currentX = point.x;
	this->currentY = point.y;
	
	if (this->classButton == true) {
		if (this->currentX - this->startX < 120) {
			this->currentX = this->startX + 120;
		}
		if (this->currentY - this->startY < 150) {
			this->currentY = this->startY + 150;
		}
		Long index = this->diagram->Add(this->startX, this->startY, this->currentX - this->startX, this->currentY - this->startY);

		//Class 생성자에서 Line 만드는거 추가에서 -> Class Add에서 Line 만드는거 추가에서 -> Form 마우스 드래그 끝날떄
		//끝나면서 Class 만든거에 Line 추가하는걸로 바꿈 2017.08.24

		//첨자연산자 왜 안돼는지 //선 만듦
		static_cast<Class*>(this->diagram->GetAt(index))->Add(this->startX, this->startY + 30,
			this->currentX - this->startX, this->startY + 30);
		static_cast<Class*>(this->diagram->GetAt(index))->Add(this->startX, (this->startY + 30 + this->currentY) / 2,
			this->currentX - this->startX, (this->startY + 30 + this->currentY) / 2);

		//클래스 이름, 캐럿 출력
		//CreateSolidCaret(5, 20);
		//SetCaretPos(CPoint(this->startX + 5, this->startY + 5));
		//ShowCaret();

		Invalidate();
	}
	if (this->relationButton == true) {

	}
	//this->relationButton = false;
	//Invalidate();
}

void ClassDiagramForm::OnMouseMove(UINT nFlags, CPoint point) {

	if (nFlags == MK_LBUTTON) {
		this->currentX = point.x;
		this->currentY = point.y;
		Invalidate();
	}
}


void ClassDiagramForm::OnClose() {
	//6.1. 저장한다.
	this->Save();
	//6.2. 다이어그램을 지운다.
	if (this->diagram != NULL) {
		delete this->diagram;
	}
	//6.3. 윈도우를 닫는다.
	CFrameWnd::OnClose(); // 오버라이딩 코드재사용
}



//int main(int argc, char* argv[]) {
//
//	ClassDiagramForm classDiagramForm;
//
//	cout << " dd " << endl;
//
//	classDiagramForm.diagram = new Diagram;
//
//	classDiagramForm.Load(); //로드
//
//	cout << " dd " << endl;
//	//클래스 세이브로드 확인
//	cout << classDiagramForm.diagram->GetAt(0)->GetX() << " " << classDiagramForm.diagram->GetAt(0)->GetY() << " " <<
//		classDiagramForm.diagram->GetAt(0)->GetWidth() << " " << classDiagramForm.diagram->GetAt(0)->GetHeight()
//		<< " " << classDiagramForm.diagram->GetAt(0)->GetLength() << " " << classDiagramForm.diagram->GetAt(0)->GetCapacity()
//		<< endl;
//	cout << " dd " << endl;
//	//라인 세이브로드 확인
//	cout << classDiagramForm.diagram->GetAt(0)->GetAt(0)->GetX() << " " <<
//		classDiagramForm.diagram->GetAt(0)->GetAt(0)->GetY() << " " <<
//		classDiagramForm.diagram->GetAt(0)->GetAt(0)->GetWidth() << " " <<
//		classDiagramForm.diagram->GetAt(0)->GetAt(0)->GetHeight() << " " << endl;
//	cout << " dd " << endl;
//
//	classDiagramForm.Save(); //세이브
//
//	return 0;
//}
// 

