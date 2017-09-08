//ClassDiagramForm.cpp

#include "ClassDiagramForm.h"
//#include "Figure.h"
#include "Diagram.h"
#include "DrawingVisitor.h"
#include "Text.h"
#include "SingleByteCharacter.h"
#include "WritingVisitor.h"
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
	this->directedAssociationButton = true; //��������
	this->aggregationButton = false; // ����
	this->aggregationSButton = false; // ���տ���
	this->compositionButton = false; // �ռ�
	this->compositionSBtton = false; // ���տ���
	this->templateButton = false;
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
			 Figure *figure;
			 //���� ������ ���� ������ ĭ 
			 // 0 = Line, 1 = Template, 2 = Generalization(�Ϲ�ȭ), 3 = Realization(��üȭ), 4 = Dependency(����), 5 = Association(����ȭ),
			 // 6 = DirectedAssociation(��������),  7 = Aggregation(����), 8 = Aggregations(���տ���), 9 =  Composition(�ռ�), 10 = Compositions(���տ���)
			 
			 if (dynamic_cast<Line*>(object.GetAt(j))) {
				 figure = object.GetAt(j);
				 fLine << figure->GetX() << " " << figure->GetY() << " " <<
					 figure->GetWidth() << " " << figure->GetHeight() << " " << 0 << endl;
			 }

			 else if (dynamic_cast<Template*>(object.GetAt(j))) {
				 figure = object.GetAt(j);
				 fLine << figure->GetX() << " " << figure->GetY() << " " <<
					 figure->GetWidth() << " " << figure->GetHeight() << " " << 1 << endl;
			 }

			 else if (dynamic_cast<Generalization*>(object.GetAt(j))) {
				 figure = object.GetAt(j);
				 fLine << figure->GetX() << " " << figure->GetY() << " " <<
					 figure->GetWidth() << " " << figure->GetHeight() << " " << 2 << endl;
			 }

			 else if (dynamic_cast<Realization*>(object.GetAt(j))) {
				 figure = object.GetAt(j);
				 fLine << figure->GetX() << " " << figure->GetY() << " " <<
					 figure->GetWidth() << " " << figure->GetHeight() << " " << 3 << endl;
			 }

			 else if (dynamic_cast<Dependency*>(object.GetAt(j))) {
				 figure = object.GetAt(j);
				 fLine << figure->GetX() << " " << figure->GetY() << " " <<
					 figure->GetWidth() << " " << figure->GetHeight() << " " << 4 << endl;
			 }

			 else if (dynamic_cast<Association*>(object.GetAt(j))) {
				 figure = object.GetAt(j);
				 fLine << figure->GetX() << " " << figure->GetY() << " " <<
					 figure->GetWidth() << " " << figure->GetHeight() << " " << 5 << endl;
			 }

			 else if (dynamic_cast<DirectedAssociation*>(object.GetAt(j))) {
				 figure = object.GetAt(j);
				 fLine << figure->GetX() << " " << figure->GetY() << " " <<
					 figure->GetWidth() << " " << figure->GetHeight() << " " << 6 << endl;
			 }

			 else if (dynamic_cast<Aggregation*>(object.GetAt(j))) {
				 figure = object.GetAt(j);
				 fLine << figure->GetX() << " " << figure->GetY() << " " <<
					 figure->GetWidth() << " " << figure->GetHeight() << " " << 7 << endl;
			 }

			 else if (dynamic_cast<Aggregations*>(object.GetAt(j))) {
				 figure = object.GetAt(j);
				 fLine << figure->GetX() << " " << figure->GetY() << " " <<
					 figure->GetWidth() << " " << figure->GetHeight() << " " << 8 << endl;
			 }

			 else if (dynamic_cast<Composition*>(object.GetAt(j))) {
				 figure = object.GetAt(j);
				 fLine << figure->GetX() << " " << figure->GetY() << " " <<
					 figure->GetWidth() << " " << figure->GetHeight() << " " << 9 << endl;
			 }

			 else if (dynamic_cast<Compositions*>(object.GetAt(j))) {
				 figure = object.GetAt(j);
				 fLine << figure->GetX() << " " << figure->GetY() << " " <<
					 figure->GetWidth() << " " << figure->GetHeight() << " " << 10 << endl;
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
	Long lineHeight;
	ifstream fClass;
	ifstream fLine;
	Long type;

	fClass.open("ClassSave.txt");
	fLine.open("LineSave.txt");

	if (fClass.is_open() && fLine.is_open()) {
		fClass >> length >> x >> y >> width >> height;
		while (!fClass.eof()) {
			position = this->diagram->Add(x, y, width, height);
			i = 0;
			while (i < length) {
				fLine >> lineX >> lineY >> lineWidth >> lineHeight >> type;
				if (type == 0) {
					this->diagram->GetAt(position)->Add(lineX, lineY, lineWidth, lineHeight);
				}
				else if (type == 1) {
					this->diagram->GetAt(position)->AddTemplate(lineX, lineY, lineWidth, lineHeight);
				}
				else if (type == 2) {
					this->diagram->GetAt(position)->AddGeneralization(lineX, lineY, lineWidth, lineHeight);
				}
				else if (type == 3) {
					this->diagram->GetAt(position)->AddRealization(lineX, lineY, lineWidth, lineHeight);
				}
				else if (type == 4) {
					this->diagram->GetAt(position)->AddDependency(lineX, lineY, lineWidth, lineHeight);
				}
				else if (type == 5) {
					this->diagram->GetAt(position)->AddAssociation(lineX, lineY, lineWidth, lineHeight);
				}
				else if (type == 6) {
					this->diagram->GetAt(position)->AddDirectedAssociation(lineX, lineY, lineWidth, lineHeight);
				}
				else if (type == 7) {
					this->diagram->GetAt(position)->AddAggregation(lineX, lineY, lineWidth, lineHeight);
				}
				else if (type == 8) {
					this->diagram->GetAt(position)->AddAggregations(lineX, lineY, lineWidth, lineHeight);
				}
				else if (type == 9) {
					this->diagram->GetAt(position)->AddComposition(lineX, lineY, lineWidth, lineHeight);
				}
				else if (type == 10) {
					this->diagram->GetAt(position)->AddCompositions(lineX, lineY, lineWidth, lineHeight);
				}
				//static_cast<Class*>(this->diagram->GetAt(position))->Add(lineX, lineY, lineWidth, lineHeigth);
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

	if (this->relationButton == false) {//�巡�� �簢��
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

	if (this->relationButton == true /*&& this->startX != this->currentX && this->startY != this->currentY*/) {

		//�Ϲ�ȭ
		if (this->generalizationButton == true) {

			dc.MoveTo(this->startX, this->startY);
			dc.LineTo(this->currentX, this->currentY);

			CBrush white(RGB(255, 255, 255));
			CBrush myBrush;
			myBrush.CreateSolidBrush(RGB(255, 255, 255));
			CBrush *oldBrush = dc.SelectObject(&myBrush);

			double degree = atan2(this->currentX - this->startX, this->startY - this->currentY); // ����

			double distance = sqrt(pow(this->currentX - this->startX, 2) + pow(this->startY - this->currentY, 2));
			// ��Ʈ�ȿ� = ��Ʈ(����(
			double dX = (this->currentX) - (15 * (this->currentX - this->startX) / distance); //�ڷ� �� ������ x
			double dY = (this->currentY) + (15 * (this->startY - this->currentY) / distance); //�ڷ� �� ������ y

			 // ���� ����

			CPoint pts[3];

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
			CBrush myBrush;
			myBrush.CreateSolidBrush(RGB(255, 255, 255));
			CBrush *oldBrush = dc.SelectObject(&myBrush);

			double degree = atan2(this->currentX - this->startX, this->startY - this->currentY); // ����

			double distance = sqrt(pow(this->currentX - this->startX, 2) + pow(this->startY - this->currentY, 2));
			// ��Ʈ�ȿ� = ��Ʈ(����(
			double dX = (this->currentX) - (15 * (this->currentX - this->startX) / distance); //�ڷ� �� ������ x
			double dY = (this->currentY) + (15 * (this->startY - this->currentY) / distance); //�ڷ� �� ������ y

			 // ���� ����

			CPoint pts[3];

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
		}

		//����ȭ
		else if (this->associationButton == true) {

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

			double degree = atan2(this->currentX - this->startX, this->startY - this->currentY); // ����

			double distance = sqrt(pow(this->currentX - this->startX, 2) + pow(this->startY - this->currentY, 2));
			// ��Ʈ�ȿ� = ��Ʈ(����(
			double dX = (this->currentX) - (15 * (this->currentX - this->startX) / distance); //�ڷ� �� ������ x
			double dY = (this->currentY) + (15 * (this->startY - this->currentY) / distance); //�ڷ� �� ������ y

			 // ���� ����

			CPoint pts[3];

			pts[0].x = (this->currentX); //���콺 ������ġ ��
			pts[0].y = (this->currentY);

			pts[1].x = static_cast<LONG>(dX - 15 * cos(degree)); // ����
			pts[1].y = static_cast<LONG>(dY - 15 * sin(degree));

			pts[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // �Ʒ���
			pts[2].y = static_cast<LONG>(dY + 15 * sin(degree));

			dc.MoveTo(pts[0].x, pts[0].y);
			dc.LineTo(pts[1].x, pts[1].y);

			dc.MoveTo(pts[0].x, pts[0].y);
			dc.LineTo(pts[2].x, pts[2].y);
		}

		//���� ����
		else if (this->directedAssociationButton == true) {

			dc.MoveTo(this->startX, this->startY);
			dc.LineTo(this->currentX, this->currentY);

			double degree = atan2(this->currentX - this->startX, this->startY - this->currentY); // ����

			double distance = sqrt(pow(this->currentX - this->startX, 2) + pow(this->startY - this->currentY, 2));
			// ��Ʈ�ȿ� = ��Ʈ(����(
			double dX = (this->currentX) - (15 * (this->currentX - this->startX) / distance); //�ڷ� �� ������ x
			double dY = (this->currentY) + (15 * (this->startY - this->currentY) / distance); //�ڷ� �� ������ y

			 // ���� ����

			CPoint pts[3];

			pts[0].x = (this->currentX); //���콺 ������ġ ��
			pts[0].y = (this->currentY);

			pts[1].x = static_cast<LONG>(dX - 15 * cos(degree)); // ����
			pts[1].y = static_cast<LONG>(dY - 15 * sin(degree));

			pts[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // �Ʒ���
			pts[2].y = static_cast<LONG>(dY + 15 * sin(degree));

			dc.MoveTo(pts[0].x, pts[0].y);
			dc.LineTo(pts[1].x, pts[1].y);

			dc.MoveTo(pts[0].x, pts[0].y);
			dc.LineTo(pts[2].x, pts[2].y);
		}

		//���� ����
		else if (this->aggregationSButton == true) {

			dc.MoveTo(this->startX, this->startY);
			dc.LineTo(this->currentX, this->currentY);

			CBrush white(RGB(255, 255, 255));
			CBrush myBrush;
			myBrush.CreateSolidBrush(RGB(255, 255, 255));
			CBrush *oldBrush = dc.SelectObject(&myBrush);

			double degree = atan2(this->currentX - this->startX, this->startY - this->currentY); // ����

			double distance = sqrt(pow(this->currentX - this->startX, 2) + pow(this->startY - this->currentY, 2));
			// ��Ʈ�ȿ� = ��Ʈ(����(
			double dX = (this->currentX) - (15 * (this->currentX - this->startX) / distance); //�ڷ� �� ������ x
			double dY = (this->currentY) + (15 * (this->startY - this->currentY) / distance); //�ڷ� �� ������ y

			 // ���� ����

			CPoint pts[3];

			pts[0].x = (this->currentX); //���콺 ������ġ ��
			pts[0].y = (this->currentY);

			pts[1].x = static_cast<LONG>(dX - 15 * cos(degree)); // ����
			pts[1].y = static_cast<LONG>(dY - 15 * sin(degree));

			pts[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // �Ʒ���
			pts[2].y = static_cast<LONG>(dY + 15 * sin(degree));

			dc.MoveTo(pts[0].x, pts[0].y);
			dc.LineTo(pts[1].x, pts[1].y);

			dc.MoveTo(pts[0].x, pts[0].y);
			dc.LineTo(pts[2].x, pts[2].y);


			//������� ȭ��ǥ �������� ������

			dX = (this->startX) + (15 * (this->currentX - this->startX) / distance); //�ڷ� �� ������ x
			dY = (this->startY) - (15 * (this->startY - this->currentY) / distance); //�ڷ� �� ������ y

			double dX2 = (this->startX) - ((this->currentX - this->startX) / distance);
			double dY2 = (this->startY) + ((this->startY - this->currentY) / distance);

			CPoint pts2[4];

			pts2[0].x = static_cast<LONG>(dX - 15 * cos(degree)); // ����
			pts2[0].y = static_cast<LONG>(dY - 15 * sin(degree));

			pts2[1].x = static_cast<LONG>(dX2); //���콺 ó�� ��
			pts2[1].y = static_cast<LONG>(dY2);

			pts2[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // �Ʒ���
			pts2[2].y = static_cast<LONG>(dY + 15 * sin(degree));

			pts2[3].x = static_cast<LONG>(dX) + static_cast<LONG>(15 * (this->currentX - this->startX) / distance); // ����
			pts2[3].y = static_cast<LONG>(dY) - static_cast<LONG>(15 * (this->startY - this->currentY) / distance);

			dc.SelectObject(&white);
			dc.Polygon(pts2, 4);
			dc.SelectObject(oldBrush);
			myBrush.DeleteObject();
		}

		//����
		else if (this->aggregationButton == true) {

			dc.MoveTo(this->startX, this->startY);
			dc.LineTo(this->currentX, this->currentY);

			CBrush white(RGB(255, 255, 255));
			CBrush myBrush;
			myBrush.CreateSolidBrush(RGB(255, 255, 255));
			CBrush *oldBrush = dc.SelectObject(&myBrush);

			double degree = atan2(this->currentX - this->startX, this->startY - this->currentY); // ����

			double distance = sqrt(pow(this->currentX - this->startX, 2) + pow(this->startY - this->currentY, 2));

			double dX = (this->startX) + (15 * (this->currentX - this->startX) / distance); //�ڷ� �� ������ x
			double dY = (this->startY) - (15 * (this->startY - this->currentY) / distance); //�ڷ� �� ������ y

			double dX2 = (this->startX) - ((this->currentX - this->startX) / distance);
			double dY2 = (this->startY) + ((this->startY - this->currentY) / distance);

			CPoint pts2[4];

			pts2[0].x = static_cast<LONG>(dX - 15 * cos(degree)); // ����
			pts2[0].y = static_cast<LONG>(dY - 15 * sin(degree));

			pts2[1].x = static_cast<LONG>(dX2); //���콺 ó�� ��
			pts2[1].y = static_cast<LONG>(dY2);

			pts2[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // �Ʒ���
			pts2[2].y = static_cast<LONG>(dY + 15 * sin(degree));

			pts2[3].x = static_cast<LONG>(dX) + static_cast<LONG>(15 * (this->currentX - this->startX) / distance); // ����
			pts2[3].y = static_cast<LONG>(dY) - static_cast<LONG>(15 * (this->startY - this->currentY) / distance);

			dc.SelectObject(&white);
			dc.Polygon(pts2, 4);
			dc.SelectObject(oldBrush);
			myBrush.DeleteObject();
		}

		//�ռ�
		else if (this->compositionButton == true) {

			dc.MoveTo(this->startX, this->startY);
			dc.LineTo(this->currentX, this->currentY);

			CBrush black(RGB(000, 000, 000));
			CBrush myBrush;
			myBrush.CreateSolidBrush(RGB(255, 255, 255));
			CBrush *oldBrush = dc.SelectObject(&myBrush);


			double degree = atan2(this->currentX - this->startX, this->startY - this->currentY); // ����

			double distance = sqrt(pow(this->currentX - this->startX, 2) + pow(this->startY - this->currentY, 2));

			double dX = (this->startX) + (15 * (this->currentX - this->startX) / distance); //�ڷ� �� ������ x
			double dY = (this->startY) - (15 * (this->startY - this->currentY) / distance); //�ڷ� �� ������ y

			double dX2 = (this->startX) - ((this->currentX - this->startX) / distance);
			double dY2 = (this->startY) + ((this->startY - this->currentY) / distance);

			CPoint pts2[4];

			pts2[0].x = static_cast<LONG>(dX - 15 * cos(degree)); // ����
			pts2[0].y = static_cast<LONG>(dY - 15 * sin(degree));

			pts2[1].x = static_cast<LONG>(dX2); //���콺 ó�� ��
			pts2[1].y = static_cast<LONG>(dY2);

			pts2[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // �Ʒ���
			pts2[2].y = static_cast<LONG>(dY + 15 * sin(degree));

			pts2[3].x = static_cast<LONG>(dX) + static_cast<LONG>(15 * (this->currentX - this->startX) / distance); // ����
			pts2[3].y = static_cast<LONG>(dY) - static_cast<LONG>(15 * (this->startY - this->currentY) / distance);

			dc.SelectObject(&black);
			dc.Polygon(pts2, 4);
			dc.SelectObject(oldBrush);
			myBrush.DeleteObject();
		}

		//���տ���
		else if (this->compositionSBtton == true) {

			dc.MoveTo(this->startX, this->startY);
			dc.LineTo(this->currentX, this->currentY);

			CBrush black(RGB(000, 000, 000));
			CBrush myBrush;
			myBrush.CreateSolidBrush(RGB(255, 255, 255));
			CBrush *oldBrush = dc.SelectObject(&myBrush);

			double degree = atan2(this->currentX - this->startX, this->startY - this->currentY); // ����

			double distance = sqrt(pow(this->currentX - this->startX, 2) + pow(this->startY - this->currentY, 2));
			// ��Ʈ�ȿ� = ��Ʈ(����(
			double dX = (this->currentX) - (15 * (this->currentX - this->startX) / distance); //�ڷ� �� ������ x
			double dY = (this->currentY) + (15 * (this->startY - this->currentY) / distance); //�ڷ� �� ������ y

			 // ���� ����
			CPoint pts[3];

			pts[0].x = (this->currentX); //���콺 ������ġ ��
			pts[0].y = (this->currentY);

			pts[1].x = static_cast<LONG>(dX - 15 * cos(degree)); // ����
			pts[1].y = static_cast<LONG>(dY - 15 * sin(degree));

			pts[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // �Ʒ���
			pts[2].y = static_cast<LONG>(dY + 15 * sin(degree));

			dc.MoveTo(pts[0].x, pts[0].y);
			dc.LineTo(pts[1].x, pts[1].y);

			dc.MoveTo(pts[0].x, pts[0].y);
			dc.LineTo(pts[2].x, pts[2].y);

			//������� ȭ��ǥ �������� ������
			distance = sqrt(pow(this->currentX - this->startX, 2) + pow(this->startY - this->currentY, 2));

			dX = (this->startX) + (15 * (this->currentX - this->startX) / distance); //�ڷ� �� ������ x
			dY = (this->startY) - (15 * (this->startY - this->currentY) / distance); //�ڷ� �� ������ y

			double dX2 = (this->startX) - ((this->currentX - this->startX) / distance);
			double dY2 = (this->startY) + ((this->startY - this->currentY) / distance);

			CPoint pts2[4];

			pts2[0].x = static_cast<LONG>(dX - 15 * cos(degree)); // ����
			pts2[0].y = static_cast<LONG>(dY - 15 * sin(degree));

			pts2[1].x = static_cast<LONG>(dX2); //���콺 ó�� ��
			pts2[1].y = static_cast<LONG>(dY2);

			pts2[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // �Ʒ���
			pts2[2].y = static_cast<LONG>(dY + 15 * sin(degree));

			pts2[3].x = static_cast<LONG>(dX) + static_cast<LONG>(15 * (this->currentX - this->startX) / distance); // ����
			pts2[3].y = static_cast<LONG>(dY) - static_cast<LONG>(15 * (this->startY - this->currentY) / distance);

			dc.SelectObject(&black);
			dc.Polygon(pts2, 4);
			dc.SelectObject(oldBrush);
			myBrush.DeleteObject();
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
	this->selected = this->diagram->Find(this->currentX, this->currentY);
	
	//RECT area;
	//area.left = this->startX;
	//area.top = this->startY;
	//area.right = this->currentX;
	//area.bottom = this->currentY;

	//InvalidateRect(&area, true);

	//if (this->selected != -1 ) {
	//Invalidate();
	//}
}

void ClassDiagramForm::OnLButtonUp(UINT nFlags, CPoint point) {
	this->currentX = point.x;
	this->currentY = point.y;
	
	Long endClass = this->diagram->Find(this->currentX, this->currentY);

	if (this->relationButton == true && this->selected != -1 && endClass != -1) {
		
		CPoint line1Start;
		CPoint line1End;
		CPoint line2Start;
		CPoint line2End;
		CPoint cross1;
		CPoint cross2;

		line1Start.x = this->startX;
		line1Start.y = this->startY;
		line1End.x = this->currentX;
		line1End.y = this->currentY;

		bool startClassCheck = false;
		if (startClassCheck == false) {//���� Ŭ�������� ���� �����ϴ� �� ã��
			//���
			line2Start.x = this->diagram->GetAt(this->selected)->GetX();
			line2Start.y = this->diagram->GetAt(this->selected)->GetY();
			line2End.x = this->diagram->GetAt(this->selected)->GetX() + this->diagram->GetAt(this->selected)->GetWidth();
			line2End.y = this->diagram->GetAt(this->selected)->GetY();
			startClassCheck = this->FindCrossPoint(line1Start, line1End, line2Start, line2End, &cross1);
		}
		if (startClassCheck == false) {
			//����
			line2Start.x = this->diagram->GetAt(this->selected)->GetX();
			line2Start.y = this->diagram->GetAt(this->selected)->GetY();
			line2End.x = this->diagram->GetAt(this->selected)->GetX();
			line2End.y = this->diagram->GetAt(this->selected)->GetY() + this->diagram->GetAt(this->selected)->GetHeight();
			startClassCheck = this->FindCrossPoint(line1Start, line1End, line2Start, line2End, &cross1);
		}
		if (startClassCheck == false) {
			//����
			line2Start.x = this->diagram->GetAt(this->selected)->GetX() + this->diagram->GetAt(this->selected)->GetWidth();
			line2Start.y = this->diagram->GetAt(this->selected)->GetY();
			line2End.x = this->diagram->GetAt(this->selected)->GetX() + this->diagram->GetAt(this->selected)->GetWidth();
			line2End.y = this->diagram->GetAt(this->selected)->GetY() + this->diagram->GetAt(this->selected)->GetHeight();
			startClassCheck = this->FindCrossPoint(line1Start, line1End, line2Start, line2End, &cross1);
		}
		if (startClassCheck == false) {
			//�ϴ�
			line2Start.x = this->diagram->GetAt(this->selected)->GetX();
			line2Start.y = this->diagram->GetAt(this->selected)->GetY() + this->diagram->GetAt(this->selected)->GetHeight();
			line2End.x = this->diagram->GetAt(this->selected)->GetX() + this->diagram->GetAt(this->selected)->GetWidth();
			line2End.y = this->diagram->GetAt(this->selected)->GetY() + this->diagram->GetAt(this->selected)->GetHeight();
			startClassCheck = this->FindCrossPoint(line1Start, line1End, line2Start, line2End, &cross1);
		}

		bool endClassCheck = false;
		if (endClassCheck == false) {//�� Ŭ�������� ���� �����ϴ� �� ã��
			//���
			line2Start.x = this->diagram->GetAt(endClass)->GetX();
			line2Start.y = this->diagram->GetAt(endClass)->GetY();
			line2End.x = this->diagram->GetAt(endClass)->GetX() + this->diagram->GetAt(endClass)->GetWidth();
			line2End.y = this->diagram->GetAt(endClass)->GetY();
			endClassCheck = this->FindCrossPoint(line1Start, line1End, line2Start, line2End, &cross2);
		}
		if (endClassCheck == false) {
			//����
			line2Start.x = this->diagram->GetAt(endClass)->GetX();
			line2Start.y = this->diagram->GetAt(endClass)->GetY();
			line2End.x = this->diagram->GetAt(endClass)->GetX();
			line2End.y = this->diagram->GetAt(endClass)->GetY() + this->diagram->GetAt(endClass)->GetHeight();
			endClassCheck = this->FindCrossPoint(line1Start, line1End, line2Start, line2End, &cross2);
		}
		if (endClassCheck == false) {
			//����
			line2Start.x = this->diagram->GetAt(endClass)->GetX() + this->diagram->GetAt(endClass)->GetWidth();
			line2Start.y = this->diagram->GetAt(endClass)->GetY();
			line2End.x = this->diagram->GetAt(endClass)->GetX() + this->diagram->GetAt(endClass)->GetWidth();
			line2End.y = this->diagram->GetAt(endClass)->GetY() + this->diagram->GetAt(endClass)->GetHeight();
			endClassCheck = this->FindCrossPoint(line1Start, line1End, line2Start, line2End, &cross2);
		}
		if (endClassCheck == false) {
			//�ϴ�
			line2Start.x = this->diagram->GetAt(endClass)->GetX();
			line2Start.y = this->diagram->GetAt(endClass)->GetY() + this->diagram->GetAt(endClass)->GetHeight();
			line2End.x = this->diagram->GetAt(endClass)->GetX() + this->diagram->GetAt(endClass)->GetWidth();
			line2End.y = this->diagram->GetAt(endClass)->GetY() + this->diagram->GetAt(endClass)->GetHeight();
			endClassCheck = this->FindCrossPoint(line1Start, line1End, line2Start, line2End, &cross2);
		}

		if (this->generalizationButton == true) {
			this->diagram->GetAt(this->selected)->AddGeneralization( cross1.x, cross1.y, cross2.x, cross2.y);
			//Invalidate();
		}
		else if (this->realizationButton == true) {
			this->diagram->GetAt(this->selected)->AddRealization(cross1.x, cross1.y, cross2.x, cross2.y);
			//Invalidate();
		}
		else if (this->associationButton == true) {
			this->diagram->GetAt(this->selected)->AddAssociation(cross1.x, cross1.y, cross2.x, cross2.y);
			//Invalidate();
		}
		else if (this->dependencyButton == true) {
			this->diagram->GetAt(this->selected)->AddDependency(cross1.x, cross1.y, cross2.x, cross2.y);
			//Invalidate();
		}
		else if (this->directedAssociationButton == true) {
			this->diagram->GetAt(this->selected)->AddDirectedAssociation(cross1.x, cross1.y, cross2.x, cross2.y);
			//Invalidate();
		}
		else if (this->aggregationButton == true) {
			this->diagram->GetAt(this->selected)->AddAggregation(cross1.x, cross1.y, cross2.x, cross2.y);
			//Invalidate();
		}
		else if (this->aggregationSButton == true) {
			this->diagram->GetAt(this->selected)->AddAggregations(cross1.x, cross1.y, cross2.x, cross2.y);
			//Invalidate();
		}
		else if (this->compositionButton == true) {
			this->diagram->GetAt(this->selected)->AddComposition(cross1.x, cross1.y, cross2.x, cross2.y);
			//Invalidate();
		}
		else if (this->compositionSBtton == true) {
			this->diagram->GetAt(this->selected)->AddCompositions(cross1.x, cross1.y, cross2.x, cross2.y);
			//Invalidate();
		}
	}
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

		//Invalidate();

		//RECT area;
		//area.left = this->startX;
		//area.top = this->startY;
		//area.right = this->currentX;
		//area.bottom = this->currentY;

		//InvalidateRect(&area, true);
	}
	if (templateButton == true && this->selected != -1) {
		Class *object;
		object = this->diagram->GetAt(this->selected);
		object->AddTemplate(object->GetX() + object->GetWidth() - 70, object->GetY() - 15, 80, 25);
		//Invalidate();
	}
	this->startX = 0;
	this->startY = 0;
	this->currentX = 0;
	this->currentY = 0;
	Invalidate();
	//this->relationButton = false;
	//Invalidate();
}

void ClassDiagramForm::OnMouseMove(UINT nFlags, CPoint point) {

	if (nFlags == MK_LBUTTON) {
		this->currentX = point.x;
		this->currentY = point.y;
		Invalidate();
		//RECT area;
		//area.left = this->startX;
		//area.top = this->startY;
		//area.right = this->currentX;
		//area.bottom = this->currentY;

		//InvalidateRect(&area, true);
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
			crossPoint->y = static_cast<LONG>( line1Start.y + t*(double)(line1End.y - line1Start.y));
			ret = true;
		}
	}
	return ret;
 }



