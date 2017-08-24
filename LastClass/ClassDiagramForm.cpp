//ClassDiagramForm.cpp

#include "ClassDiagramForm.h"
#include "Diagram.h"

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
			object = this->diagram->GetAt(i);
			fClass << object.GetLength() << " " << object.GetX() << " " << object.GetY()
				<< " " << object.GetWidth() << " " << object.GetHeight() << endl;
			j = 0;
			while (j < object.GetLength()) {
				Line lineObject;
				lineObject = object.GetAt(j);
				fLine << lineObject.GetStartX() << " " << lineObject.GetStartY() << " " <<
					lineObject.GetEndX() << " " << lineObject.GetEndY() << endl;
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
	Long index;
	Long startX;
	Long startY;
	Long endX;
	Long endY;
	ifstream fClass;
	ifstream fLine;

	fClass.open("ClassSave.txt", ios::in);
	fLine.open("LineSave.txt", ios::in);

	if (fClass.is_open() && fLine.is_open()) {
		fClass >> length >> x >> y >> width >> height;
		while (!fClass.eof()) {
			position = this->diagram->Add(x, y, width, height);
			if (length > 0) {
				fLine >> startX >> startY >> endX >> endY;
				i = 0;
			}
			while (i < length) {
				this->diagram->GetAt(position).Add(startX, startY, endX, endY);
				fLine >> startX >> startY >> endX >> endY;
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

	this->diagram = new Diagram;
	
	return 0;
}

void ClassDiagramForm::OnPaint() {
	CPaintDC dc(this); // 이건 뭔가?

	Long length = this->diagram->GetLength();
	Long i = 0;
	Long x;
	Long y;
	Long width;
	Long height;
	Class object;

	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = dc.SelectObject(&pen);
	dc.Rectangle(startX, startY, this->currentX, this->currentY);
	dc.SelectObject(oldPen);
	pen.DeleteObject();
	
	Long objectLength;
	Long j;
	Line line;

	while (i < length) {
		object = this->diagram->GetAt(i);
		x = object.GetX();
		y = object.GetY();
		width = object.GetWidth();
		height = object.GetHeight();
		dc.Rectangle(x, y, x + width, y + height); ////////////// 사각형을 만든다
		objectLength = object.GetLength();
		j = 0;
		while (j < objectLength) {
			line = object.GetAt(j);
			dc.MoveTo(line.GetStartX(), line.GetStartY());
			dc.LineTo(line.GetEndX(), line.GetEndY());
			j++;
		}
		i++;
	}
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

	//첨자연산자 왜 안돼는지
	this->diagram->GetAt(index).Add(this->diagram->GetAt(index).GetX(), this->diagram->GetAt(index).GetY() + 30,
		this->diagram->GetAt(index).GetX() + this->diagram->GetAt(index).GetWidth(), this->diagram->GetAt(index).GetY() + 30);
	this->diagram->GetAt(index).Add(this->diagram->GetAt(index).GetX(), (this->diagram->GetAt(index).GetY()*2 + 30 + this->diagram->GetAt(index).GetHeight())/2,
		this->diagram->GetAt(index).GetX() + this->diagram->GetAt(index).GetWidth(), this->diagram->GetAt(index).GetY() * 2 + 30 + this->diagram->GetAt(index).GetHeight() / 2);

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
	if (this->diagram != NULL) {
		delete this->diagram;
		//this->diagram = NULL;
	}
	CFrameWnd::OnClose(); // 오버라이딩 코드재사용
}

#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
	ClassDiagramForm classDiagramForm;

	cout << " dd " << endl;
	
	classDiagramForm.diagram = new Diagram;
	/*
	classDiagramForm.diagram->Add(100, 100, 100, 200);
	classDiagramForm.diagram->GetAt(0).Add(150, 150, 200, 200);
	// */
	//classDiagramForm.Save();
	classDiagramForm.Load();

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