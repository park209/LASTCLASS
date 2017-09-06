//DrawingVisitor.cpp

#include"DrawingVisitor.h"
#include "Class.h"
#include "Generalization.h"
#include <iostream>
using namespace std;

DrawingVisitor::DrawingVisitor() {
}

void DrawingVisitor::Visit(Class *object, CDC* cPaintDc) {

	Long x = object->GetX();
	Long  y = object->GetY();;
	Long width = object->GetWidth();
	Long height = object->GetHeight();

	cout << "   Class �� �׸���" << endl;
	
	cPaintDc->Rectangle(x, y, x + width, y + height);
}
void DrawingVisitor::Visit(Line *line, CDC* cPaintDc) {
	Long x = line->GetX();
	Long  y = line->GetY();;
	Long width = line->GetWidth();

	cout << "   Line �� �׸���" << endl;
	
	cPaintDc->MoveTo(x, y);
	cPaintDc->LineTo(x + width, y);
}

void DrawingVisitor::Visit(SingleByteCharacter *singleByteCharacter, CDC* cPaintDc) {
}

void DrawingVisitor::Visit(DoubleByteCharacter *doubleByteCharacter, CDC* cPaintDc) {
}


void DrawingVisitor::Visit(Generalization *generalization) {

	Long x = generalization->GetX();
	Long  y = generalization->GetY();;
	Long width = generalization->GetWidth();
	Long height = generalization->GetHeight();
	cout << "�Ϲ�ȭ���" << " " << x << " " << y << " " << width << " " << height <<  endl;
}
//void DrawingVisitor::Visit(Relation *relation,CDC* cPaintDc) {
	//Type type = relation->GetType();

	//CPen pen;
	////pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	//CPen *oldPen = dc.SelectObject(&pen);
	//dc.SetBkMode(TRANSPARENT);
	//dc.MoveTo(this->startX, this->startY);
	//dc.LineTo(this->currentX, this->currentY);

	//CBrush white(RGB(255, 255, 255));
	//CBrush black(RGB(000, 000, 000));
	//CBrush myBrush;
	//myBrush.CreateSolidBrush(RGB(255, 255, 255));
	//CBrush *oldBrush = dc.SelectObject(&myBrush);
	//CPoint pts[3];

	//double degree = atan2(this->currentX - this->startX, this->startY - this->currentY); // ����

	//double distance = sqrt(pow(this->currentX - this->startX, 2) + pow(this->startY - this->currentY, 2));
	//// ��Ʈ�ȿ� = ��Ʈ(����(
	//double dX = (this->currentX) - (15 * (this->currentX - this->startX) / distance); //�ڷ� �� ������ x
	//double dY = (this->currentY) + (15 * (this->startY - this->currentY) / distance); //�ڷ� �� ������ y

	//																				  // ���� ����

	//pts[0].x = (this->currentX); //���콺 ������ġ ��
	//pts[0].y = (this->currentY);

	//pts[1].x = static_cast<LONG>(dX - 15 * cos(degree)); // ����
	//pts[1].y = static_cast<LONG>(dY - 15 * sin(degree));

	//pts[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // �Ʒ���
	//pts[2].y = static_cast<LONG>(dY + 15 * sin(degree));

	//dc.SelectObject(&white);
	//dc.Polygon(pts, 3);
	//dc.SelectObject(oldBrush);
	//myBrush.DeleteObject();
	//dc.SelectObject(oldPen);
	//pen.DeleteObject();
	//GENERALIZATION
	//REALIZATION
	//DEPENDENCY
	//ASSOCIATION
	//DIRECTEDASSOCIATION
	//AGGREGATION
	//AGGREGATIONS
	//COMPOSITION
	//COMPOSITIONS
//}

DrawingVisitor::~DrawingVisitor() {
}
