//ClassDiagramForm.cpp

#include "ClassDiagramForm.h"
#include "Figure.h"
#include "Diagram.h"
#include "DrawingVisitor.h"

#include <iostream>
#include <fstream>

using namespace std;

BEGIN_MESSAGE_MAP(ClassDiagramForm, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

ClassDiagramForm::ClassDiagramForm() { // 생성자 맞는듯
	this->diagram = NULL;
	this->startX = 0;
	this->startY = 0;
	this->currentX = 0;
	this->currentY = 0;
}

Long ClassDiagramForm::Save() {
   Long i = 0;
   Long j;
   ofstream fClass;
   ofstream fLine; // 읽을때는 of

   fClass.open("ClassSave.txt");
   fLine.open("LineSave.txt");
   if (fClass.is_open() && fLine.is_open()) {
      //if (!fClass && !fLine) {

      while (i < this->diagram->GetLength()) {
         Class object;
         object = (*static_cast<Class*>(this->diagram->GetAt(i)));
         fClass << object.GetLength() << " " << object.GetX() << " " << object.GetY()
            << " " << object.GetWidth() << " " << object.GetHeight() << endl;
         j = 0;
         while (j < object.GetLength()) {
            Line lineObject;
			lineObject = (*static_cast<Line*>(object.GetAt(j)));
            fLine << lineObject.GetX() << " " << lineObject.GetY() << " " <<
               lineObject.GetWidth() << " " << lineObject.GetHeight() << endl;
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
	//1.2. 적재한다
	this->Load();
	//1.3. 윈도우를 갱신한다
	Invalidate();

	return 0;
}

void ClassDiagramForm::OnPaint() {
	CPaintDC dc(this);
	DrawingVisitor drawingVisitor;


	this->diagram->Accept(drawingVisitor, &dc);

	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = dc.SelectObject(&pen);
	dc.SetBkMode(TRANSPARENT);
	dc.Rectangle(startX, startY, this->currentX, this->currentY);
	dc.SelectObject(oldPen);
	pen.DeleteObject();
	//Long i = 0;
	//Long x;
	//Long y;
	//Long width;
	//Long height;

	//Long objectLength;
	//Long j;
	//Long lineX;
	//Long lineY;
	//Long lineWidth;
	//Long lineHeight;

	//while (i < this->diagram->GetLength()) {
	//	x = this->diagram->GetAt(i)->GetX();
	//	y = this->diagram->GetAt(i)->GetY();
	//	width = this->diagram->GetAt(i)->GetWidth();
	//	height = this->diagram->GetAt(i)->GetHeight();
	//	dc.Rectangle(x, y, x + width, y + height); ////////////// 사각형을 만든다
	//											   // 클래스 이름 출력 확인
	//											   //dc.TextOutA(x+8, y+5, (CString)object.GetName().c_str());
	//											   //objectLength = static_cast<Class*>(this->diagram->GetAt(index))->GetLength();
	//	j = 0;
	//	while (j < static_cast<Class*>(this->diagram->GetAt(i))->GetLength()) {
	//		lineX = static_cast<Class*>(this->diagram->GetAt(i))->GetAt(j)->GetX();
	//		lineY = static_cast<Class*>(this->diagram->GetAt(i))->GetAt(j)->GetY();
	//		lineWidth = static_cast<Class*>(this->diagram->GetAt(i))->GetAt(j)->GetWidth();
	//		lineHeight = static_cast<Class*>(this->diagram->GetAt(i))->GetAt(j)->GetHeight();

	//		dc.MoveTo(lineX, lineY);
	//		dc.LineTo(lineX + lineWidth, lineY);
	//		j++;
	//	}
	//	i++;
	//}
}

void ClassDiagramForm::OnLButtonDown(UINT nFlags, CPoint point) {
	this->startX = point.x;
	this->startY = point.y;
	this->currentX = point.x;
	this->currentY = point.y;
}

void ClassDiagramForm::OnLButtonUp(UINT nFlags, CPoint point) {
	this->currentX = point.x;
	this->currentY = point.y;
	if (this->currentX - this->startX < 120) {
		this->currentX = this->startX + 120;
	}
	if (this->currentY - this->startY< 150) {
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

	//클래스 이름 출력
	//CreateSolidCaret(5, 20);
	//SetCaretPos(CPoint(this->startX + 5, this->startY + 5));
	//ShowCaret();

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
	//6.1. 저장한다.
	this->Save();
	//6.2. 다이어그램을 지운다.
	if (this->diagram != NULL) {
		delete this->diagram;
	}
	//6.3. 윈도우를 닫는다.
	CFrameWnd::OnClose(); // 오버라이딩 코드재사용
}

/*
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
ClassDiagramForm classDiagramForm;

cout << " dd " << endl;

classDiagramForm.diagram = new Diagram;

//classDiagramForm.Save();
//classDiagramForm.Load();

//클래스 세이브로드 확인
cout << classDiagramForm.diagram->GetAt(0).GetX() << " " << classDiagramForm.diagram->GetAt(0).GetY() << " " <<
classDiagramForm.diagram->GetAt(0).GetWidth() << " " << classDiagramForm.diagram->GetAt(0).GetHeight()
<< " " << classDiagramForm.diagram->GetAt(0).GetLength() << " " << classDiagramForm.diagram->GetAt(0).GetCapacity()
<< endl;
//라인 세이브로드 확인
cout << classDiagramForm.diagram->GetAt(0).GetAt(0).GetStartX() << " " <<
classDiagramForm.diagram->GetAt(0).GetAt(0).GetStartY() << " " <<
classDiagramForm.diagram->GetAt(0).GetAt(0).GetEndX() << " " <<
classDiagramForm.diagram->GetAt(0).GetAt(0).GetEndY() << " " << endl;

return 0;
}
// */