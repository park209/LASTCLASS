//ClassDiagramForm.cpp

#include "ClassDiagramForm.h"
#include "Diagram.h"

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
	//첨자연산자 왜 안돼는지
	this->diagram->GetAt(index).Add(this->diagram->GetAt(index).GetX(), this->diagram->GetAt(index).GetY() + 30,
		this->diagram->GetAt(index).GetX() + this->diagram->GetAt(index).GetWidth(), this->diagram->GetAt(index).GetY() + 30);
	this->diagram->GetAt(index).Add(this->diagram->GetAt(index).GetX(), (this->diagram->GetAt(index).GetY()*2 + 30 + this->diagram->GetAt(index).GetHeight())/2,
		this->diagram->GetAt(index).GetX() + this->diagram->GetAt(index).GetWidth(), (this->diagram->GetAt(index).GetY() * 2 + 30 + this->diagram->GetAt(index).GetHeight()) / 2);
	
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