//ClassDiagramForm.cpp

#include "ClassDiagramForm.h"
#include "Diagram.h"

BEGIN_MESSAGE_MAP(ClassDiagramForm, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

ClassDiagramForm::ClassDiagramForm() {
	this->diagram = NULL;
}


int ClassDiagramForm::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CFrameWnd::OnCreate(lpCreateStruct);
	this->diagram = new Diagram;
	this->diagram->Add(100, 100, 30, 30);
	this->diagram->Add(200, 200, 50, 50);
	this->diagram->Add(300, 300, 40, 40);

	return 0;
}

void ClassDiagramForm::OnPaint() {
	CPaintDC dc(this);

	Long length = this->diagram->GetLength();
	Long i = 0;
	Long x;
	Long y;
	Long width;
	Long height;
	Class object;

	while (i < length) {
		object = this->diagram->GetAt(i);
		x = object.GetX();
		y = object.GetY();
		width = object.GetWidth();
		height = object.GetHeight();
		dc.Rectangle(x, y, x + width, y + height);
		i++;
	}
}

void ClassDiagramForm::OnClose() {
	if (this->diagram != NULL) {
		delete this->diagram;
		this->diagram = NULL;
	}
	CFrameWnd::OnClose();
}
