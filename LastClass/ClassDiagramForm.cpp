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

ClassDiagramForm::ClassDiagramForm() { // ������ �´µ�
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
	this->generalizationButton = false; //�Ϲ�ȭ
	this->realizationButton = false; //��üȭ
	this->dependencyButton = false; //����
	this->associationButton = false; //����ȭ
	this->directedAssociationButton = false; //��������
	this->aggregationButton = false; // ����
	this->aggregationSButton = true; // ���տ���
	this->compositionButton = false; // �ռ�
	this->compositionSBtton = false; // ���տ���
}

Long ClassDiagramForm::Save() {
   Long i = 0;
   Long j;
   ofstream fClass;
   ofstream fLine; // �������� of

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

	CFrameWnd::OnCreate(lpCreateStruct); //�ڵ����� �������̵� //��ӿ���
										 //1.1. ���̾�׷��� �غ��Ѵ�
	this->diagram = new Diagram();
	this->text = new Text;

	//1.2. �����Ѵ�
	this->Load();

	//1.3. �����츦 �����Ѵ�
	Invalidate();

	return 0;
}

void ClassDiagramForm::OnPaint() {
	CPaintDC dc(this);

	DrawingVisitor drawingVisitor;
	WritingVisitor writingVisitor;

	if (this->classButton == true) {//&& this->relationButton == true //�巡�� �簢��
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

		//�Ϲ�ȭ
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

			double degree = atan2(this->currentX - this->startX, this->startY - this->currentY); // ����

			double distance = sqrt(pow(this->currentX - this->startX, 2) + pow(this->startY - this->currentY, 2));
			// ��Ʈ�ȿ� = ��Ʈ(����(
			double dX = (this->currentX) - (15 * (this->currentX - this->startX) / distance); //�ڷ� �� ������ x
			double dY = (this->currentY) + (15 * (this->startY - this->currentY) / distance); //�ڷ� �� ������ y

			 // ���� ����

			pts[0].x = (this->currentX); //���콺 ������ġ ��
			pts[0].y = (this->currentY);

			pts[1].x = static_cast<LONG>(dX - 15 * cos(degree)); // ����
			pts[1].y = static_cast<LONG>(dY - 15 * sin(degree));

			pts[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // �Ʒ���
			pts[2].y = static_cast<LONG>(dY + 15 * sin(degree));

			dc.SelectObject(&white);
			dc.Polygon(pts, 3);
			dc.SelectObject(oldBrush);
			myBrush.DeleteObject();
			dc.SelectObject(oldPen);
			pen.DeleteObject();
		}

		//��üȭ
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

			double degree = atan2(this->currentX - this->startX, this->startY - this->currentY); // ����

			double distance = sqrt(pow(this->currentX - this->startX, 2) + pow(this->startY - this->currentY, 2));
			// ��Ʈ�ȿ� = ��Ʈ(����(
			double dX = (this->currentX) - (15 * (this->currentX - this->startX) / distance); //�ڷ� �� ������ x
			double dY = (this->currentY) + (15 * (this->startY - this->currentY) / distance); //�ڷ� �� ������ y

			 // ���� ����

			pts[0].x = (this->currentX); //���콺 ������ġ ��
			pts[0].y = (this->currentY);

			pts[1].x = static_cast<LONG>(dX - 15 * cos(degree)); // ����
			pts[1].y = static_cast<LONG>(dY - 15 * sin(degree));

			pts[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // �Ʒ���
			pts[2].y = static_cast<LONG>(dY + 15 * sin(degree));

			dc.SelectObject(&white);
			dc.Polygon(pts, 3);
			dc.SelectObject(oldBrush);
			myBrush.DeleteObject();
			dc.SelectObject(oldPen);
			pen.DeleteObject();
		}

		//����ȭ
		else if (this->associationButton == true) {


			CPen pen;

			CPen *oldPen = dc.SelectObject(&pen);
			dc.SetBkMode(TRANSPARENT);
			dc.MoveTo(this->startX, this->startY);
			dc.LineTo(this->currentX, this->currentY);
		}

		//����
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

			double degree = atan2(this->currentX - this->startX, this->startY - this->currentY); // ����

			double distance = sqrt(pow(this->currentX - this->startX, 2) + pow(this->startY - this->currentY, 2));
			// ��Ʈ�ȿ� = ��Ʈ(����(
			double dX = (this->currentX) - (15 * (this->currentX - this->startX) / distance); //�ڷ� �� ������ x
			double dY = (this->currentY) + (15 * (this->startY - this->currentY) / distance); //�ڷ� �� ������ y

			 // ���� ����

			pts[0].x = (this->currentX); //���콺 ������ġ ��
			pts[0].y = (this->currentY);

			pts[1].x = static_cast<LONG>(dX - 15 * cos(degree)); // ����
			pts[1].y = static_cast<LONG>(dY - 15 * sin(degree));

			pts[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // �Ʒ���
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

		//���� ����
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

			double degree = atan2(this->currentX - this->startX, this->startY - this->currentY); // ����

			double distance = sqrt(pow(this->currentX - this->startX, 2) + pow(this->startY - this->currentY, 2));
			// ��Ʈ�ȿ� = ��Ʈ(����(
			double dX = (this->currentX) - (15 * (this->currentX - this->startX) / distance); //�ڷ� �� ������ x
			double dY = (this->currentY) + (15 * (this->startY - this->currentY) / distance); //�ڷ� �� ������ y

			 // ���� ����

			pts[0].x = (this->currentX); //���콺 ������ġ ��
			pts[0].y = (this->currentY);

			pts[1].x = static_cast<LONG>(dX - 15 * cos(degree)); // ����
			pts[1].y = static_cast<LONG>(dY - 15 * sin(degree));

			pts[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // �Ʒ���
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

		//���� ����
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

			double degree = atan2(this->currentX - this->startX, this->startY - this->currentY); // ����

			double distance = sqrt(pow(this->currentX - this->startX, 2) + pow(this->startY - this->currentY, 2));
			// ��Ʈ�ȿ� = ��Ʈ(����(
			double dX = (this->currentX) - (15 * (this->currentX - this->startX) / distance); //�ڷ� �� ������ x
			double dY = (this->currentY) + (15 * (this->startY - this->currentY) / distance); //�ڷ� �� ������ y

			 // ���� ����

			pts[0].x = (this->currentX); //���콺 ������ġ ��
			pts[0].y = (this->currentY);

			pts[1].x = static_cast<LONG>(dX - 15 * cos(degree)); // ����
			pts[1].y = static_cast<LONG>(dY - 15 * sin(degree));

			pts[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // �Ʒ���
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
			//������� ȭ��ǥ �������� ������
			distance = sqrt(pow(this->currentX - this->startX, 2) + pow(this->startY - this->currentY, 2));

			dX = (this->startX) + (15 * (this->currentX - this->startX) / distance); //�ڷ� �� ������ x



			dY = (this->startY) - (15 * (this->startY - this->currentY) / distance); //�ڷ� �� ������ y

			double dX2 = (this->startX) - ((this->currentX - this->startX) / distance);

			double dY2 = (this->startY) + ((this->startY - this->currentY) / distance);

			CPoint pts2[4];
			pts2[1].x = static_cast<LONG>(dX2); //���콺 ó�� ��
			pts2[1].y = static_cast<LONG>(dY2);

			pts2[0].x = static_cast<LONG>(dX - 15 * cos(degree)); // ����
			pts2[0].y = static_cast<LONG>(dY - 15 * sin(degree));

			pts2[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // �Ʒ���
			pts2[2].y = static_cast<LONG>(dY + 15 * sin(degree));

			pts2[3].x = static_cast<LONG>(dX) + static_cast<LONG>(15 * (this->currentX - this->startX) / distance); // ����
			pts2[3].y = static_cast<LONG>(dY) - static_cast<LONG>(15 * (this->startY - this->currentY) / distance);

			dc.SelectObject(&white);
			dc.Polygon(pts2, 4);
			dc.SelectObject(oldBrush);
			myBrush.DeleteObject();
			dc.SelectObject(oldPen);
			pen.DeleteObject();
		}

		//����
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

			double degree = atan2(this->currentX - this->startX, this->startY - this->currentY); // ����

			double distance = sqrt(pow(this->currentX - this->startX, 2) + pow(this->startY - this->currentY, 2));
			// ��Ʈ�ȿ� = ��Ʈ(����(
			double dX = (this->currentX) - (15 * (this->currentX - this->startX) / distance); //�ڷ� �� ������ x
			double dY = (this->currentY) + (15 * (this->startY - this->currentY) / distance); //�ڷ� �� ������ y

			 // ���� ����

			//������� ȭ��ǥ �������� ������
			distance = sqrt(pow(this->currentX - this->startX, 2) + pow(this->startY - this->currentY, 2));

			dX = (this->startX) + (15 * (this->currentX - this->startX) / distance); //�ڷ� �� ������ x
			dY = (this->startY) - (15 * (this->startY - this->currentY) / distance); //�ڷ� �� ������ y

			double dX2 = (this->startX) - ((this->currentX - this->startX) / distance);

			double dY2 = (this->startY) + ((this->startY - this->currentY) / distance);

			CPoint pts2[4];
			pts2[1].x = static_cast<LONG>(dX2); //���콺 ó�� ��
			pts2[1].y = static_cast<LONG>(dY2);

			pts2[0].x = static_cast<LONG>(dX - 15 * cos(degree)); // ����
			pts2[0].y = static_cast<LONG>(dY - 15 * sin(degree));

			pts2[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // �Ʒ���
			pts2[2].y = static_cast<LONG>(dY + 15 * sin(degree));

			pts2[3].x = static_cast<LONG>(dX) + static_cast<LONG>(15 * (this->currentX - this->startX) / distance); // ����
			pts2[3].y = static_cast<LONG>(dY) - static_cast<LONG>(15 * (this->startY - this->currentY) / distance);

			dc.SelectObject(&white);
			dc.Polygon(pts2, 4);
			dc.SelectObject(oldBrush);
			myBrush.DeleteObject();
			dc.SelectObject(oldPen);
			pen.DeleteObject();
		}

		//�ռ�
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

			double degree = atan2(this->currentX - this->startX, this->startY - this->currentY); // ����

			double distance = sqrt(pow(this->currentX - this->startX, 2) + pow(this->startY - this->currentY, 2));
			// ��Ʈ�ȿ� = ��Ʈ(����(
			double dX = (this->currentX) - (15 * (this->currentX - this->startX) / distance); //�ڷ� �� ������ x
			double dY = (this->currentY) + (15 * (this->startY - this->currentY) / distance); //�ڷ� �� ������ y

																							  // ���� ����


																							  //������� ȭ��ǥ �������� ������
			distance = sqrt(pow(this->currentX - this->startX, 2) + pow(this->startY - this->currentY, 2));

			dX = (this->startX) + (15 * (this->currentX - this->startX) / distance); //�ڷ� �� ������ x
			dY = (this->startY) - (15 * (this->startY - this->currentY) / distance); //�ڷ� �� ������ y

			double dX2 = (this->startX) - ((this->currentX - this->startX) / distance);

			double dY2 = (this->startY) + ((this->startY - this->currentY) / distance);

			CPoint pts2[4];
			pts2[1].x = static_cast<LONG>(dX2); //���콺 ó�� ��
			pts2[1].y = static_cast<LONG>(dY2);

			pts2[0].x = static_cast<LONG>(dX - 15 * cos(degree)); // ����
			pts2[0].y = static_cast<LONG>(dY - 15 * sin(degree));

			pts2[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // �Ʒ���
			pts2[2].y = static_cast<LONG>(dY + 15 * sin(degree));

			pts2[3].x = static_cast<LONG>(dX) + static_cast<LONG>(15 * (this->currentX - this->startX) / distance); // ����
			pts2[3].y = static_cast<LONG>(dY) - static_cast<LONG>(15 * (this->startY - this->currentY) / distance);

			dc.SelectObject(&black);
			dc.Polygon(pts2, 4);
			dc.SelectObject(oldBrush);
			myBrush.DeleteObject();
			dc.SelectObject(oldPen);
			pen.DeleteObject();
		}
		//���տ���
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

			double degree = atan2(this->currentX - this->startX, this->startY - this->currentY); // ����

			double distance = sqrt(pow(this->currentX - this->startX, 2) + pow(this->startY - this->currentY, 2));
			// ��Ʈ�ȿ� = ��Ʈ(����(
			double dX = (this->currentX) - (15 * (this->currentX - this->startX) / distance); //�ڷ� �� ������ x
			double dY = (this->currentY) + (15 * (this->startY - this->currentY) / distance); //�ڷ� �� ������ y

			 // ���� ����

			pts[0].x = (this->currentX); //���콺 ������ġ ��
			pts[0].y = (this->currentY);

			pts[1].x = static_cast<LONG>(dX - 15 * cos(degree)); // ����
			pts[1].y = static_cast<LONG>(dY - 15 * sin(degree));

			pts[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // �Ʒ���
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
			//������� ȭ��ǥ �������� ������
			distance = sqrt(pow(this->currentX - this->startX, 2) + pow(this->startY - this->currentY, 2));

			dX = (this->startX) + (15 * (this->currentX - this->startX) / distance); //�ڷ� �� ������ x



			dY = (this->startY) - (15 * (this->startY - this->currentY) / distance); //�ڷ� �� ������ y

			double dX2 = (this->startX) - ((this->currentX - this->startX) / distance);

			double dY2 = (this->startY) + ((this->startY - this->currentY) / distance);

			CPoint pts2[4];
			pts2[1].x = static_cast<LONG>(dX2); //���콺 ó�� ��
			pts2[1].y = static_cast<LONG>(dY2);

			pts2[0].x = static_cast<LONG>(dX - 15 * cos(degree)); // ����
			pts2[0].y = static_cast<LONG>(dY - 15 * sin(degree));

			pts2[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // �Ʒ���
			pts2[2].y = static_cast<LONG>(dY + 15 * sin(degree));

			pts2[3].x = static_cast<LONG>(dX) + static_cast<LONG>(15 * (this->currentX - this->startX) / distance); // ����
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
	//���ʹ����ų�(rowIndex+1) �ٸ� text�� �̵��ϸ� rowIndex �ٲ�� �ؾ��ҵ�

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

		//Class �����ڿ��� Line ����°� �߰����� -> Class Add���� Line ����°� �߰����� -> Form ���콺 �巡�� ������
		//�����鼭 Class ����ſ� Line �߰��ϴ°ɷ� �ٲ� 2017.08.24

		//÷�ڿ����� �� �ȵŴ��� //�� ����
		static_cast<Class*>(this->diagram->GetAt(index))->Add(this->startX, this->startY + 30,
			this->currentX - this->startX, this->startY + 30);
		static_cast<Class*>(this->diagram->GetAt(index))->Add(this->startX, (this->startY + 30 + this->currentY) / 2,
			this->currentX - this->startX, (this->startY + 30 + this->currentY) / 2);

		//Ŭ���� �̸�, ĳ�� ���
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
	//6.1. �����Ѵ�.
	this->Save();
	//6.2. ���̾�׷��� �����.
	if (this->diagram != NULL) {
		delete this->diagram;
	}
	//6.3. �����츦 �ݴ´�.
	CFrameWnd::OnClose(); // �������̵� �ڵ�����
}



//int main(int argc, char* argv[]) {
//
//	ClassDiagramForm classDiagramForm;
//
//	cout << " dd " << endl;
//
//	classDiagramForm.diagram = new Diagram;
//
//	classDiagramForm.Load(); //�ε�
//
//	cout << " dd " << endl;
//	//Ŭ���� ���̺�ε� Ȯ��
//	cout << classDiagramForm.diagram->GetAt(0)->GetX() << " " << classDiagramForm.diagram->GetAt(0)->GetY() << " " <<
//		classDiagramForm.diagram->GetAt(0)->GetWidth() << " " << classDiagramForm.diagram->GetAt(0)->GetHeight()
//		<< " " << classDiagramForm.diagram->GetAt(0)->GetLength() << " " << classDiagramForm.diagram->GetAt(0)->GetCapacity()
//		<< endl;
//	cout << " dd " << endl;
//	//���� ���̺�ε� Ȯ��
//	cout << classDiagramForm.diagram->GetAt(0)->GetAt(0)->GetX() << " " <<
//		classDiagramForm.diagram->GetAt(0)->GetAt(0)->GetY() << " " <<
//		classDiagramForm.diagram->GetAt(0)->GetAt(0)->GetWidth() << " " <<
//		classDiagramForm.diagram->GetAt(0)->GetAt(0)->GetHeight() << " " << endl;
//	cout << " dd " << endl;
//
//	classDiagramForm.Save(); //���̺�
//
//	return 0;
//}
// 

