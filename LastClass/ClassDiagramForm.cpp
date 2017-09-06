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

	if (this->relationButton == false) {//&& this->relationButton == true //드래그 사각형
		CPen pen;
		pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
		CPen *oldPen = dc.SelectObject(&pen);
		dc.SetBkMode(TRANSPARENT);
		dc.Rectangle(startX, startY, this->currentX, this->currentY);
		dc.SelectObject(oldPen);
		pen.DeleteObject();
	}

	if (this->relationButton == true) {
		CPen pen;
		pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
		CPen *oldPen = dc.SelectObject(&pen);
		dc.SetBkMode(TRANSPARENT);
		dc.MoveTo(startX, startY);
		dc.LineTo(this->currentX, this->currentY);

		//if (this->currentX > this->startX && this->currentY > this->startY) {
		//float degree = atan2(static_cast<float>(this->currentY - this->startY), static_cast<float>(this->currentX - this->startX)) * 180 / 3.1415f;
		////Long newX = this->currentX + (static_cast<Long>(cos(degree) * 50));
		////Long newY = this->currentY + (static_cast<Long>(sin(degree) * 50));
		//Long newX = this->currentX - 10 * cos(degree);
		//Long newY = this->currentY - 20;
		Long newX = this->currentX - 40;
		Long newY = this->currentY;
		//dc.Rectangle(newX, newY, newX + 50, newY + 50);
		Long newX1 = this->currentX;
		Long newY1 = this->currentY + 40;
		CPoint pts[3];

	
	//	float degree = atan2(static_cast<float>(this->currentX - this->startX), static_cast<float>(this->currentY - this->startY)) * 180 / 3.1415f;
	//
/*		CPoint pts[4];
		pts[0].x = this->currentX;
		pts[0].y = this->currentY;
		
		pts[1].x = newX;
		pts[1].y = newY;

		//pts[2].x = newX1;
		//pts[2].y = newY1;

		
		/*while (newY != newX1) {
			newY--;;
			newX1++;
		}
		Long newX2 = newY;
		Long newY2 =newX1;


		pts[2].x = newX2;
		pts[2].y = newY2;
		pts[3].x = newX2;
		pts[3].y = newY2;
		
		dc.Polygon(pts, 3);
		*/
		
		dc.SelectObject(oldPen);
		pen.DeleteObject();
	}
	this->diagram->Accept(drawingVisitor,&dc);

	this->text->Accept(writingVisitor, &dc);

	if (this->relationButton == true) {
		CPen pen;
		pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
		CPen *oldPen = dc.SelectObject(&pen);
		dc.SetBkMode(TRANSPARENT);
		dc.MoveTo(startX, startY);
		dc.LineTo(this->currentX, this->currentY);
		
		dc.SelectObject(oldPen);
		pen.DeleteObject();
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

	//CPoint pts[3];
	//CPoint point1(10, 10);
	//CPoint point2(500, 500);
	//CPoint point3(250, 400);
	//pts[0] = point1;
	//pts[1] = point2;
	//[2] = point3;

	//dc.Polygon(pts, 3);

}
	/*char testChar ='a'; //text 출력확인용 코드들
	CString cs(testChar);
	char testChar1 = 'b';
	cs.AppendChar(testChar1); // string 뒤에 char 추가 함수
	dc.TextOut(100, 100, cs);*/


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
	
	Invalidate();
	
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