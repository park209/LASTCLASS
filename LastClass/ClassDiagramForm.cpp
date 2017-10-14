//ClassDiagramForm.cpp

#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"
#include "Diagram.h"
#include "Class.h"
#include "MemoBox.h"
#include "Selection.h"
#include "Template.h"
#include "ClassName.h"
#include "Method.h"
#include "Attribute.h"
#include "Reception.h"
#include "Line.h"
#include "Generalization.h"
#include "Realization.h"
#include "Dependency.h"
#include "Association.h"
#include "DirectedAssociation.h"
#include "Aggregation.h"
#include "Aggregations.h"
#include "Composition.h"
#include "Compositions.h"
#include "MemoLine.h"
#include "SelfAggregation.h"
#include "SelfAggregations.h"
#include "SelfAssociation.h"
#include "SelfComposition.h"
#include "SelfCompositions.h"
#include "SelfDependency.h"
#include "SelfDirectedAssociation.h"
#include "SelfGeneralization.h"
#include "SelfRelation.h"
#include "Figure.h"
#include "FigureFactory.h"
#include "DrawingVisitor.h"
#include "WritingVisitor.h"
#include "MovingVisitor.h"
#include "MouseLButton.h"
#include "HistoryGraphic.h"
#include "KeyBoard.h"
#include "KeyAction.h"
#include "ClassDiagramFormMenu.h"
#include "ToolBar.h"
#include "StatusBar.h"
#include "MenuAction.h"
#include "Scroll.h"
#include "ScrollAction.h"
#include "GraphicCtrlCopyKey.h"

#include <math.h>
#include <iostream>
#include <fstream>
#include <afxmsg_.h>
#include <afxext.h>
#include <afxdlgs.h>

using namespace std;


BEGIN_MESSAGE_MAP(ClassDiagramForm, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
	ON_WM_SETFOCUS()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_CLOSE()
	ON_COMMAND_RANGE(100, 140, OnMyMenu)
	ON_WM_SIZE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_MOUSEWHEEL()
	ON_WM_NCMOUSEMOVE()
END_MESSAGE_MAP()

ClassDiagramForm::ClassDiagramForm(LastClass *lastClass) { // ������ �´µ�
	this->lastClass = lastClass;
	this->diagram = NULL;
	this->textEdit = NULL;
	this->selection = NULL;
	this->mouseLButton = NULL;
	this->keyBoard = NULL;
	this->historyGraphic = NULL;
	this->scroll = NULL;
	this->classDiagramFormMenu = NULL;
	this->startX = 0;
	this->startY = 0;
	this->currentX = 0;
	this->currentY = 0;
	this->fileName = "";
	this->copyBuffer = NULL;
	this->isCut = 0;
	this->capsLockFlag = 0;
	this->numLockFlag = 0;
	this->zoomRate = 100;
}

Long ClassDiagramForm::Load() {
	Long position = -1;
	Long i;
	Long x = 0;
	Long y = 0;
	Long width = 0;
	Long height = 0;
	Long length = 0;
	Long minimumWidth = 0;
	Long minimumHeight = 0;
	Long index;
	Long type = 0;
	Long relationLength = 0;
	FigureFactory factory;
	Figure *figure;
	ifstream fTest;
	Long j;
	Long l;
	Long rowLength = 0;
	Long fontSize = 0;
	string temp1;
	string temp2;


	//CFileDialog  dlgFile(true, "txt", "*", NULL, "�ؽ�Ʈ ����(*.txt)");
	//if (dlgFile.DoModal() == IDOK)
	//{
	//	this->fileName = dlgFile.GetPathName();
	//}
	fTest.open(this->fileName);
	//fTest.open("text.txt");
	//���� ������ ���� ������ ĭ 
	// 0 = Class, 1 = MemoBox, 2 = Line, 3 = Template, 4 = Generalization(�Ϲ�ȭ), 5 = Realization(��üȭ), 6 = Dependency(����), 7 = Association(����ȭ),
	// 8 = DirectedAssociation(��������),  9 = Aggregation(����), 10 = Aggregations(���տ���), 11 =  Composition(�ռ�), 12 = Compositions(���տ���), 13 = MemoLine
	// 14 = ClassName , 15 = Attribute , 16 = Method , 17 = Reception

	if (fTest.is_open()) {  
		getline(fTest, temp1);
		sscanf_s((CString)temp1.c_str(), "%d %d %d %d %d %d %d %d", &length, &x, &y, &width, &height, &minimumWidth, &minimumHeight, &type);
		while (!fTest.eof()) {
			figure = factory.Create(x, y, width, height, minimumWidth, minimumHeight, type);
			position = this->diagram->Add(figure);
			FigureComposite *figureComposite = static_cast<FigureComposite*>(this->diagram->GetAt(position));
			if (type == 7) {   //�޸�ڽ��̸�
				getline(fTest, temp1);
				sscanf_s((CString)temp1.c_str(), "%d %d",&fontSize, &rowLength);
				j = 0;
				temp2.clear();
				while (j < rowLength) {
					getline(fTest, temp1);
					temp2.append(temp1);
					temp2.append("\n");
					j++;
				}
					Long k = temp2.find_last_of('\n');
					temp2.replace(k, 1, "\0");
					figureComposite->ReplaceString(temp2, fontSize);
			
			}
			i = 0;
			while (position != -1 && i < length) {
				getline(fTest, temp1);
				sscanf_s((CString)temp1.c_str(), "%d %d %d %d %d %d %d", &x, &y, &width, &height, &minimumWidth, &minimumHeight, &type); //���ܰ�ü
				figure = factory.Create(x, y, width, height, minimumWidth, minimumHeight, type);
			
				if (type < 7 && type != 2) {
					getline(fTest, temp1);
					sscanf_s((CString)temp1.c_str(), "%d %d", &fontSize, &rowLength);
					temp2.clear();
					j = 0;
					while (j < rowLength) {
						getline(fTest, temp1);
						temp2.append(temp1);
						temp2.append("\n");
						j++;
					}
						Long k = temp2.find_last_of('\n');
						temp2.replace(k, 1, "\0");
						figure->ReplaceString(temp2, fontSize);
						if (type == 3) {
							static_cast<Class*>(figureComposite)->Add(static_cast<Attribute*>(figure));
						}
						else if (type == 4) {
							static_cast<Class*>(figureComposite)->Add(static_cast<Method*>(figure));
						}
						else if (type == 5) {
							static_cast<Class*>(figureComposite)->Add(static_cast<Reception*>(figure));
						}
						else if (type == 6) {
							static_cast<Class*>(figureComposite)->Add(static_cast<Template*>(figure));
						}
						else {
							figureComposite->Add(figure); 
						}
				}
				if (type >= 8 && type <= 17) {
					getline(fTest, temp1);
					sscanf_s((CString)temp1.c_str(), "%d", &relationLength);
					Long cPointX;
					Long cPointY;
					CPoint cPoint;
					index = figureComposite->Add(figure);
					Relation *relation = static_cast<Relation*>(figureComposite->GetAt(index));
					j = 0;
					while (j < relationLength) {
						getline(fTest, temp1);
						sscanf_s((CString)temp1.c_str(), "%d %d", &cPointX, &cPointY);
						cPoint.x = cPointX;
						cPoint.y = cPointY;
						relation->Add(cPoint);
						j++;
					}
					if (type != 8) {
						l = 0;
						while (l < 5) {
							getline(fTest, temp1);
							if (temp1 != "") {
								relation->rollNames->Modify(l, temp1);
							}
							getline(fTest, temp1);
							sscanf_s((CString)temp1.c_str(), "%d %d", &cPointX, &cPointY);
							cPoint.x = cPointX;
							cPoint.y = cPointY;
							relation->rollNamePoints->Modify(l, cPoint);
							l++;
						}
					}
				}
				if (type >= 18 && type <= 25) {
					Long cPointX;
					Long cPointY;
					CPoint cPoint;
					index = figureComposite->Add(figure);
					SelfRelation *selfRelation = static_cast<SelfRelation*>(figureComposite->GetAt(index));
					l = 0;
					while (l < 5) {
						getline(fTest, temp1);
						if (temp1 != "") {
							selfRelation->rollNames->Modify(l, temp1);
						}
						getline(fTest, temp1);
						sscanf_s((CString)temp1.c_str(), "%d %d", &cPointX, &cPointY);
						cPoint.x = cPointX;
						cPoint.y = cPointY;
						selfRelation->rollNamePoints->Modify(l, cPoint);
						l++;
					}
				}
				if (type == 2) {
					figureComposite->Add(figure);
				}
				i++;
			}
			getline(fTest, temp1);
			sscanf_s((CString)temp1.c_str(), "%d %d %d %d %d %d %d %d", &length, &x, &y, &width, &height, &minimumWidth, &minimumHeight, &type);
		}
	}
	fTest.close();

	return this->diagram->GetLength();
}

Long ClassDiagramForm::Save() {
	Long k;
	Long i = 0;
	Long j;
	Long l;
	Long rowLength;
	Long fontSize;
	FigureComposite *object = 0;
	Figure *figure = 0;
	SelfRelation *selfRelation = 0;
	CPoint cPoint;
	string saveText;
	ofstream fTest;
	//CString fileName;
		//CFileDialog  dlgFile(false,"txt","*", OFN_CREATEPROMPT | OFN_OVERWRITEPROMPT,"�ؽ�Ʈ ����(*.txt)");
		//if (dlgFile.DoModal() == IDOK)
		//{
			//fileName = dlgFile.GetPathName();
		//}
	fTest.open(this->fileName);
	if (fTest.is_open()) {
		while (i < this->diagram->GetLength()) {
			//���� ������ ���� ������ ĭ 
			// 0 = Class, 1 = MemoBox, 2 = Line, 3 = Template, 4 = Generalization(�Ϲ�ȭ), 5 = Realization(��üȭ), 
			//6 = Dependency(����), 7 = Association(����ȭ),
			// 8 = DirectedAssociation(��������),  9 = Aggregation(����), 10 = Aggregations(���տ���), 
			//11 =  Composition(�ռ�), 12 = Compositions(���տ���), 13 = MemoLine
			// 14 = ClassName , 15 = Attribute , 16 = Method , 17 = Reception , 18 =SelfGeneralization ,
			//19 = SelfDependency , 20 = SelfAssociation , 21 = SelfDirectedAssociation
			// 22 = SelfAggregation , 23 = SelfAggregations , 24 =SelfComposition , 25 = SelfCompositions
			j = 0;
			if (dynamic_cast<Class*>(this->diagram->GetAt(i))) {
				object = static_cast<FigureComposite*>(this->diagram->GetAt(i));
				fTest << object->GetLength() << " " << object->GetX() << " " << object->GetY()
					<< " " << object->GetWidth() << " " << object->GetHeight() << " " << object->GetMinimumWidth() << " " <<object->GetMinimumHeight() << " " << 0 << endl;
				while (j < object->GetLength())
				{
					k = 0;
					l = 0;
					if (dynamic_cast<ClassName*>(object->GetAt(j))) {
						figure = static_cast<ClassName*>(object->GetAt(j));
						fontSize = figure->GetFontSize();
						rowLength = figure->GetRowCount(figure->GetContent());
						fTest << figure->GetX() << " " << figure->GetY() << " " << figure->GetWidth() << " "
							<< figure->GetHeight() << " " << figure->GetMinimumWidth() << " " << figure->GetMinimumHeight() << " " << 1 << endl;
						fTest << fontSize << " " << rowLength << endl;
						fTest << figure->GetContent() << endl;
					}
					else if (dynamic_cast<Line*>(object->GetAt(j))) {
						figure = object->GetAt(j);
						fTest << figure->GetX() << " " << figure->GetY() << " " <<
							figure->GetWidth() << " " << figure->GetHeight() << " " << figure->GetMinimumWidth() << " " << figure->GetMinimumHeight() << " " << 2 << endl;
					}
					else if (dynamic_cast<Attribute*>(object->GetAt(j))) {
						figure = static_cast<Attribute*>(object->GetAt(j));
						fontSize = figure->GetFontSize();
						rowLength = figure->GetRowCount(figure->GetContent());
						fTest << figure->GetX() << " " << figure->GetY() << " " << figure->GetWidth() << " "
							<< figure->GetHeight() << " " << figure->GetMinimumWidth() << " " << figure->GetMinimumHeight() << " " << 3 << endl;
						fTest << fontSize << " " << rowLength << endl;
						fTest << figure->GetContent() << endl;
					}
					else if (dynamic_cast<Method*>(object->GetAt(j))) {
						figure = static_cast<Method*>(object->GetAt(j));
						fontSize = figure->GetFontSize();
						rowLength = figure->GetRowCount(figure->GetContent());
						fTest << figure->GetX() << " " << figure->GetY() << " " << figure->GetWidth() << " "
							<< figure->GetHeight() << " " << figure->GetMinimumWidth() << " " << figure->GetMinimumHeight() << " " << 4 << endl;
						fTest << fontSize << " " << rowLength << endl;
						fTest << figure->GetContent() << endl;
					}
					else if (dynamic_cast<Reception*>(object->GetAt(j))) {
						figure = static_cast<Reception*>(object->GetAt(j));
						fontSize = figure->GetFontSize();
						rowLength = figure->GetRowCount(figure->GetContent());
						fTest << figure->GetX() << " " << figure->GetY() << " " << figure->GetWidth() << " "
							<< figure->GetHeight() << " " << figure->GetMinimumWidth() << " " << figure->GetMinimumHeight() << " " << 5 << endl;
						fTest << fontSize << " " << rowLength << endl;
						fTest << figure->GetContent() << endl;
					}
					else if (dynamic_cast<Template*>(object->GetAt(j))) {
						figure = object->GetAt(j);
						fontSize = figure->GetFontSize();
						rowLength = figure->GetRowCount(figure->GetContent());
						fTest << figure->GetX() << " " << figure->GetY() << " " <<
							figure->GetWidth() << " " << figure->GetHeight() << " " << figure->GetMinimumWidth() << " " << figure->GetMinimumHeight() << " " << 6 << endl;
						fTest << fontSize << " " << rowLength << endl;
						fTest << figure->GetContent() << endl;
					}
					else if (dynamic_cast<MemoLine*>(object->GetAt(j))) {
						Relation *relation = static_cast<Relation*>(object->GetAt(j));
						fTest << relation->GetX() << " " << relation->GetY() << " " <<
							relation->GetWidth() << " " << relation->GetHeight() << " " << relation->GetMinimumWidth() << " " << relation->GetMinimumHeight() << " " << 8 << endl;
						fTest << relation->GetLength() << endl;
						while (k < relation->GetLength()) {
							cPoint = relation->GetAt(k);
							fTest << cPoint.x << " " << cPoint.y << endl;
							k++;
						}
					}
					else if (dynamic_cast<Generalization*>(object->GetAt(j))) {
						Relation *relation = static_cast<Relation*>(object->GetAt(j));
						fTest << relation->GetX() << " " << relation->GetY() << " " <<
							relation->GetWidth() << " " << relation->GetHeight() << " " << relation->GetMinimumWidth() << " " << relation->GetMinimumHeight() << " " << 9 << endl;
						fTest << relation->GetLength() << endl;
						while (k < relation->GetLength()) {
							cPoint = relation->GetAt(k);
							fTest << cPoint.x << " " << cPoint.y << endl;
							k++;
						}
						while (l < 5) {
							fTest << relation->rollNames->GetAt(l) << endl;;
							fTest << relation->rollNamePoints->GetAt(l).x << " " << relation->rollNamePoints->GetAt(l).y << endl;
							l++;
						}
					}
					else if (dynamic_cast<Realization*>(object->GetAt(j))) {
						Relation *relation = static_cast<Relation*>(object->GetAt(j));
						fTest << relation->GetX() << " " << relation->GetY() << " " <<
							relation->GetWidth() << " " << relation->GetHeight() << " " << relation->GetMinimumWidth() << " " << relation->GetMinimumHeight() << " " << 10 << endl;
						fTest << relation->GetLength() << endl;
						while (k < relation->GetLength()) {
							cPoint = relation->GetAt(k);
							fTest << cPoint.x << " " << cPoint.y << endl;
							k++;
						}
						while (l < 5) {
							fTest << relation->rollNames->GetAt(l) << endl;;
							fTest << relation->rollNamePoints->GetAt(l).x << " " << relation->rollNamePoints->GetAt(l).y << endl;
							l++;
						}
					}
					else if (dynamic_cast<Dependency*>(object->GetAt(j))) {
						Relation *relation = static_cast<Relation*>(object->GetAt(j));
						fTest << relation->GetX() << " " << relation->GetY() << " " <<
							relation->GetWidth() << " " << relation->GetHeight() << " " << relation->GetMinimumWidth() << " " << relation->GetMinimumHeight() << " " << 11 << endl;
						fTest << relation->GetLength() << endl;
						while (k < relation->GetLength()) {
							cPoint = relation->GetAt(k);
							fTest << cPoint.x << " " << cPoint.y << endl;
							k++;
						}
						while (l < 5) {
							fTest << relation->rollNames->GetAt(l) << endl;;
							fTest << relation->rollNamePoints->GetAt(l).x << " " << relation->rollNamePoints->GetAt(l).y << endl;
							l++;
						}
					}
					else if (dynamic_cast<Association*>(object->GetAt(j))) {
						Relation *relation = static_cast<Relation*>(object->GetAt(j));
						fTest << relation->GetX() << " " << relation->GetY() << " " <<
							relation->GetWidth() << " " << relation->GetHeight() << " " << relation->GetMinimumWidth() << " " << relation->GetMinimumHeight() << " " << 12 << endl;
						fTest << relation->GetLength() << endl;
						while (k < relation->GetLength()) {
							cPoint = relation->GetAt(k);
							fTest << cPoint.x << " " << cPoint.y << endl;
							k++;
						}
						while (l < 5) {
							fTest << relation->rollNames->GetAt(l) << endl;;
							fTest << relation->rollNamePoints->GetAt(l).x << " " << relation->rollNamePoints->GetAt(l).y << endl;
							l++;
						}
					}
					else if (dynamic_cast<DirectedAssociation*>(object->GetAt(j))) {
						Relation *relation = static_cast<Relation*>(object->GetAt(j));
						fTest << relation->GetX() << " " << relation->GetY() << " " <<
							relation->GetWidth() << " " << relation->GetHeight() << " " << relation->GetMinimumWidth() << " " << relation->GetMinimumHeight() << " " << 13 << endl;
						fTest << relation->GetLength() << endl;
						while (k < relation->GetLength()) {
							cPoint = relation->GetAt(k);
							fTest << cPoint.x << " " << cPoint.y << endl;
							k++;
						}
						while (l < 5) {
							fTest << relation->rollNames->GetAt(l) << endl;;
							fTest << relation->rollNamePoints->GetAt(l).x << " " << relation->rollNamePoints->GetAt(l).y << endl;
							l++;
						}
					}
					else if (dynamic_cast<Aggregation*>(object->GetAt(j))) {
						Relation *relation = static_cast<Relation*>(object->GetAt(j));
						fTest << relation->GetX() << " " << relation->GetY() << " " <<
							relation->GetWidth() << " " << relation->GetHeight() << " " << relation->GetMinimumWidth() << " " << relation->GetMinimumHeight() << " " << 14 << endl;
						fTest << relation->GetLength() << endl;
						while (k < relation->GetLength()) {
							cPoint = relation->GetAt(k);
							fTest << cPoint.x << " " << cPoint.y << endl;
							k++;
						}
						while (l < 5) {
							fTest << relation->rollNames->GetAt(l) << endl;;
							fTest << relation->rollNamePoints->GetAt(l).x << " " << relation->rollNamePoints->GetAt(l).y << endl;
							l++;
						}
					}
					else if (dynamic_cast<Aggregations*>(object->GetAt(j))) {
						Relation *relation = static_cast<Relation*>(object->GetAt(j));
						fTest << relation->GetX() << " " << relation->GetY() << " " <<
							relation->GetWidth() << " " << relation->GetHeight() << " " << relation->GetMinimumWidth() << " " << relation->GetMinimumHeight() << " " << 15 << endl;
						fTest << relation->GetLength() << endl;
						while (k < relation->GetLength()) {
							cPoint = relation->GetAt(k);
							fTest << cPoint.x << " " << cPoint.y << endl;
							k++;
						}
						while (l < 5) {
							fTest << relation->rollNames->GetAt(l) << endl;;
							fTest << relation->rollNamePoints->GetAt(l).x << " " << relation->rollNamePoints->GetAt(l).y << endl;
							l++;
						}
					}

					else if (dynamic_cast<Composition*>(object->GetAt(j))) {
						Relation *relation = static_cast<Relation*>(object->GetAt(j));
						fTest << relation->GetX() << " " << relation->GetY() << " " <<
							relation->GetWidth() << " " << relation->GetHeight() << " " << relation->GetMinimumWidth() << " " << relation->GetMinimumHeight() << " " << 16 << endl;
						fTest << relation->GetLength() << endl;
						while (k < relation->GetLength()) {
							cPoint = relation->GetAt(k);
							fTest << cPoint.x << " " << cPoint.y << endl;
							k++;
						}
						while (l < 5) {
							fTest << relation->rollNames->GetAt(l) << endl;;
							fTest << relation->rollNamePoints->GetAt(l).x << " " << relation->rollNamePoints->GetAt(l).y << endl;
							l++;
						}
					}
					else if (dynamic_cast<Compositions*>(object->GetAt(j))) {
						Relation *relation = static_cast<Relation*>(object->GetAt(j));
						fTest << relation->GetX() << " " << relation->GetY() << " " <<
							relation->GetWidth() << " " << relation->GetHeight() << " " << relation->GetMinimumWidth() << " " << relation->GetMinimumHeight() << " " << 17 << endl;
						fTest << relation->GetLength() << endl;
						while (k < relation->GetLength()) {
							cPoint = relation->GetAt(k);
							fTest << cPoint.x << " " << cPoint.y << endl;
							k++;
						}
						while (l < 5) {
							fTest << relation->rollNames->GetAt(l) << endl;;
							fTest << relation->rollNamePoints->GetAt(l).x << " " << relation->rollNamePoints->GetAt(l).y << endl;
							l++;
						}
					}

					else if (dynamic_cast<SelfGeneralization*>(object->GetAt(j))) {
						selfRelation = static_cast<SelfRelation*>(object->GetAt(j));
						fTest << selfRelation->GetX() << " " << selfRelation->GetY() << " " << selfRelation->GetWidth() << " " << selfRelation->GetHeight() << " " 
							<< selfRelation->GetMinimumWidth() << " " << selfRelation->GetMinimumHeight() << " " << 18 << endl;
						while (l < 5) {
							fTest << selfRelation->rollNames->GetAt(l) << endl;;
							fTest << selfRelation->rollNamePoints->GetAt(l).x << " " << selfRelation->rollNamePoints->GetAt(l).y << endl;
							l++;
						}
					}
					else if (dynamic_cast<SelfDependency*>(object->GetAt(j))) {
						selfRelation = static_cast<SelfRelation*>(object->GetAt(j));
						fTest << selfRelation->GetX() << " " << selfRelation->GetY() << " " << selfRelation->GetWidth() << " " << selfRelation->GetHeight() << " " 
							<< selfRelation->GetMinimumWidth() << " " << selfRelation->GetMinimumHeight() << " " << 19 << endl;
						while (l < 5) {
							fTest << selfRelation->rollNames->GetAt(l) << endl;;
							fTest << selfRelation->rollNamePoints->GetAt(l).x << " " << selfRelation->rollNamePoints->GetAt(l).y << endl;
							l++;
						}

					}
					else if (dynamic_cast<SelfAssociation*>(object->GetAt(j))) {
						selfRelation = static_cast<SelfRelation*>(object->GetAt(j));
						fTest << selfRelation->GetX() << " " << selfRelation->GetY() << " " << selfRelation->GetWidth() << " " << selfRelation->GetHeight() << " " 
							<< selfRelation->GetMinimumWidth() << " " << selfRelation->GetMinimumHeight() << " " << 20 << endl;
						while (l < 5) {
							fTest << selfRelation->rollNames->GetAt(l) << endl;;
							fTest << selfRelation->rollNamePoints->GetAt(l).x << " " << selfRelation->rollNamePoints->GetAt(l).y << endl;
							l++;
						}
					}
					else if (dynamic_cast<SelfDirectedAssociation*>(object->GetAt(j))) {
						selfRelation = static_cast<SelfRelation*>(object->GetAt(j));
						fTest << selfRelation->GetX() << " " << selfRelation->GetY() << " " << selfRelation->GetWidth() << " " << selfRelation->GetHeight() << " " 
							<< selfRelation->GetMinimumWidth() << " " << selfRelation->GetMinimumHeight() << " " << 21 << endl;
						while (l < 5) {
							fTest << selfRelation->rollNames->GetAt(l) << endl;;
							fTest << selfRelation->rollNamePoints->GetAt(l).x << " " << selfRelation->rollNamePoints->GetAt(l).y << endl;
							l++;
						}
					}
					else if (dynamic_cast<SelfAggregation*>(object->GetAt(j))) {
						selfRelation = static_cast<SelfRelation*>(object->GetAt(j));
						fTest << selfRelation->GetX() << " " << selfRelation->GetY() << " " << selfRelation->GetWidth() << " " << selfRelation->GetHeight() << " " 
							<< selfRelation->GetMinimumWidth() << " " << selfRelation->GetMinimumHeight() << " " << 22 << endl;
						while (l < 5) {
							fTest << selfRelation->rollNames->GetAt(l) << endl;;
							fTest << selfRelation->rollNamePoints->GetAt(l).x << " " << selfRelation->rollNamePoints->GetAt(l).y << endl;
							l++;
						}
					}
					else if (dynamic_cast<SelfAggregations*>(object->GetAt(j))) {
						selfRelation = static_cast<SelfRelation*>(object->GetAt(j));
						fTest << selfRelation->GetX() << " " << selfRelation->GetY() << " " << selfRelation->GetWidth() << " " << selfRelation->GetHeight() << " " 
							<< selfRelation->GetMinimumWidth() << " " << selfRelation->GetMinimumHeight() << " " << 23 << endl;
						while (l < 5) {
							fTest << selfRelation->rollNames->GetAt(l) << endl;;
							fTest << selfRelation->rollNamePoints->GetAt(l).x << " " << selfRelation->rollNamePoints->GetAt(l).y << endl;
							l++;
						};

					}
					else if (dynamic_cast<SelfComposition*>(object->GetAt(j))) {
						selfRelation = static_cast<SelfRelation*>(object->GetAt(j));
						fTest << selfRelation->GetX() << " " << selfRelation->GetY() << " " << selfRelation->GetWidth() << " " << selfRelation->GetHeight() << " " 
							<< selfRelation->GetMinimumWidth() << " " << selfRelation->GetMinimumHeight() << " " << 24 << endl;
						while (l < 5) {
							fTest << selfRelation->rollNames->GetAt(l) << endl;;
							fTest << selfRelation->rollNamePoints->GetAt(l).x << " " << selfRelation->rollNamePoints->GetAt(l).y << endl;
							l++;
						}

					}
					else if (dynamic_cast<SelfCompositions*>(object->GetAt(j))) {
						selfRelation = static_cast<SelfRelation*>(object->GetAt(j));
						fTest << selfRelation->GetX() << " " << selfRelation->GetY() << " " << selfRelation->GetWidth() << " " << selfRelation->GetHeight() << " " 
							<< selfRelation->GetMinimumWidth() << " " << selfRelation->GetMinimumHeight() << " " << 25 << endl;
						while (l < 5) {
							fTest << selfRelation->rollNames->GetAt(l) << endl;;
							fTest << selfRelation->rollNamePoints->GetAt(l).x << " " << selfRelation->rollNamePoints->GetAt(l).y << endl;
							l++;
						}
					}
					j++;
				}
			}
			else if (dynamic_cast<MemoBox*>(this->diagram->GetAt(i))) {
				object = static_cast<FigureComposite*>(this->diagram->GetAt(i));
				fontSize = object->GetFontSize();
				rowLength = object->GetRowCount(object->GetContent());
				fTest << object->GetLength() << " " << object->GetX() << " " << object->GetY()
					<< " " << object->GetWidth() << " " << object->GetHeight() << " " << object->GetMinimumWidth() << " " << object->GetMinimumHeight() << " " << 7 << endl;;
				fTest << fontSize << " " << rowLength << endl;
				fTest << object->GetContent() << endl;
				while (j < object->GetLength()) {
					Relation *relation = static_cast<Relation*>(object->GetAt(j));
					fTest << relation->GetX() << " " << relation->GetY() << " " <<
						relation->GetWidth() << " " << relation->GetHeight() << " " << relation->GetMinimumWidth() << " " << relation->GetMinimumHeight() << " " << 8 << endl;
					fTest << relation->GetLength() << endl;

					while (k < relation->GetLength()) {
						cPoint = relation->GetAt(k);
						fTest << cPoint.x << " " << cPoint.y << endl;
						k++;
					}
					j++;
				}
			}
			i++;
		}
		fTest.close();
	}
	if (this->historyGraphic->undoGraphicArray->GetLength() != 0) {
		this->historyGraphic->undoGraphicArray->Clear();
		this->historyGraphic->redoGraphicArray->Clear();
	}

	return this->diagram->GetLength();
}

int ClassDiagramForm::OnCreate(LPCREATESTRUCT lpCreateStruct) {

	CWnd::OnCreate(lpCreateStruct); //�ڵ����� �������̵� //��ӿ���
	CWnd::SetFocus();                        //1.1. ���̾�׷��� �غ��Ѵ�

	this->diagram = new Diagram();
	this->selection = new Selection;
	this->mouseLButton = new MouseLButton;
	this->historyGraphic = new HistoryGraphic;
	this->keyBoard = new KeyBoard;
	this->scroll = new Scroll;
	this->classDiagramFormMenu = new ClassDiagramFormMenu(this);
	CRect rect;
	this->GetClientRect(&rect);
	ModifyStyle(0, WS_CLIPCHILDREN);

	SCROLLINFO vScinfo;
	SCROLLINFO hScinfo;
	vScinfo.cbSize = sizeof(vScinfo);
	vScinfo.fMask = SIF_ALL;
	vScinfo.nMin = 0;
	vScinfo.nMax = 2000;
	vScinfo.nPage = rect.bottom;
	vScinfo.nPos = 0;
	this->SetScrollInfo(SB_VERT, &vScinfo);

	hScinfo.cbSize = sizeof(hScinfo);
	hScinfo.fMask = SIF_ALL;
	hScinfo.nMin = 0;
	hScinfo.nMax = 4000;
	hScinfo.nPage = rect.right;
	hScinfo.nTrackPos = 0;
	hScinfo.nPos = 0;
	this->SetScrollInfo(SB_HORZ, &hScinfo);

	if ((GetKeyState(VK_CAPITAL) & 0x0001) != 0) {
		this->capsLockFlag = 1;
	}
	else {
		this->capsLockFlag = 0;
	}
	if ((GetKeyState(VK_NUMLOCK) & 0x0001) != 0) {
		this->numLockFlag = 1;
	}
	else {
		this->numLockFlag = 0;
	}
	//1.2. �����Ѵ�
	//this->Load();
	//1.3. �����츦 �����Ѵ�
	//Invalidate();


	return 0;
}

void ClassDiagramForm::OnPaint() {
	CPaintDC dc(this);
	CRect rect;
	this->GetClientRect(&rect);
	CDC memDC;
	CBitmap *pOldBitmap;
	CBitmap bitmap;
	memDC.CreateCompatibleDC(&dc);
	bitmap.CreateCompatibleBitmap(&dc, 4000, 2000);
	pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.FillSolidRect(CRect(0, 0, 4000, 2000), RGB(255, 255, 255));
	CFont cFont;//CreateFont�� ��18�� textEdit�� rowHight�� �ٲ����
	cFont.CreateFont(25, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,// �۲� ����
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "���� ���");
	SetFont(&cFont, TRUE);
	CFont *oldFont = memDC.SelectObject(&cFont);

	//memDC.SetMapMode(MM_ISOTROPIC);
	//memDC.SetWindowExt(100, 100);
	//memDC.SetViewportExt(this->zoomRate, this->zoomRate);
	if (this->zoomRate != 100) {
		CRect rectTemp = { 0, 0, 4000, 2000 };
		dc.FillSolidRect(rectTemp, RGB(255, 255, 255));
	}

	DrawingVisitor drawingVisitor;
	this->diagram->Accept(drawingVisitor, &memDC);
	WritingVisitor writingVisitor;
	this->diagram->Accept(writingVisitor, &memDC);
	this->selection->Accept(drawingVisitor, &memDC); // selectionFlag �߰� Ȯ��
	if (this->startX != 0 && this->startY != 0 && this->currentX != 0 && this->currentY != 0) {
		this->mouseLButton->MouseLButtonDrag(this->mouseLButton, this->diagram, this->selection, this->startX, this->startY, this->currentX, this->currentY, &memDC);
	}

	int vertCurPos = GetScrollPos(SB_VERT);
	int horzCurPos = GetScrollPos(SB_HORZ);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////// ��ǥ �ȸ���Ÿ� �ؿ� 3�� �ּ��ؾ���
	dc.SetMapMode(MM_ISOTROPIC);
	dc.SetWindowExt(100, 100);
	dc.SetViewportExt(this->zoomRate, this->zoomRate);

	dc.BitBlt(0, 0, rect.right * 100 / this->zoomRate, rect.bottom * 100 / this->zoomRate, &memDC, horzCurPos, vertCurPos, SRCCOPY);

}

void ClassDiagramForm::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (this->zoomRate == 100) {
		if (nChar == 0 || nChar == 49 || nChar == 81 || nChar == 50 || nChar == 55 || nChar == 56 || nChar == 53 ||
			nChar == 57 || nChar == 48 || nChar == 52 || nChar == 54 || nChar == 87 || nChar == 51) {
			this->mouseLButton->ChangeState(nChar);
		}
		if (nChar == VK_CAPITAL) {
			if ((GetKeyState(VK_CAPITAL) & 0x0001) != 0) {
				this->capsLockFlag = 1;
			}
			else {
				this->capsLockFlag = 0;
			}
			this->lastClass->statusBar->DestroyStatus();
			this->lastClass->statusBar->MakeStatusBar(this->lastClass, this->lastClass->GetSafeHwnd(), 0, 0, 5);
		}
		if (nChar == VK_NUMLOCK) {
			if ((GetKeyState(VK_NUMLOCK) & 0x0001) != 0) {
				this->numLockFlag = 1;
			}
			else {
				this->numLockFlag = 0;
			}
			this->lastClass->statusBar->DestroyStatus();
			this->lastClass->statusBar->MakeStatusBar(this->lastClass, this->lastClass->GetSafeHwnd(), 0, 0, 5);
		}

		CClientDC dc(this);
		CFont cFont;//CreateFont�� ��18�� textEdit�� rowHight�� �ٲ����
		cFont.CreateFont(25, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,// �۲� ����
			OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "���� ���");
		SetFont(&cFont, TRUE);
		CFont *oldFont = dc.SelectObject(&cFont);
		KeyAction *keyAction = this->keyBoard->KeyDown(this, nChar, nRepCnt, nFlags);
		if (keyAction != 0) {
			keyAction->KeyPress(this, &dc);
				Invalidate(false);
		}
		dc.SelectObject(oldFont);
		cFont.DeleteObject();
	}
}


void ClassDiagramForm::OnSetFocus(CWnd* pOldWnd) {
	CWnd::OnSetFocus(pOldWnd);
	CWnd::SetFocus();
	Invalidate(false);
}
void ClassDiagramForm::OnSize(UINT nType, int cx, int cy) {
	CWnd::OnSize(nType, cx, cy);
	CPaintDC dc(this);

	CRect rect;
	this->GetClientRect(&rect);
	SCROLLINFO vScinfo;
	SCROLLINFO hScinfo;
	this->GetScrollInfo(SB_VERT, &vScinfo);
	this->GetScrollInfo(SB_HORZ, &hScinfo);

	vScinfo.nPage = rect.bottom;
	hScinfo.nPage = rect.right;


	this->SetScrollInfo(SB_VERT, &vScinfo);
	this->SetScrollInfo(SB_HORZ, &hScinfo);

	Invalidate(false);
}

void ClassDiagramForm::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	SetFocus();
	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
	ScrollAction *scrollAction = this->scroll->MoveVScroll(this, nSBCode, nPos, pScrollBar);
	if (scrollAction != 0) {
		scrollAction->Scrolling(this);
	}
	Invalidate(false);
}

void ClassDiagramForm::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	SetFocus();
	CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
	ScrollAction *scrollAction = this->scroll->MoveHScroll(this, nSBCode, nPos, pScrollBar);
	if (scrollAction != 0) {
		scrollAction->Scrolling(this);
	}
	Invalidate(false);
}
void ClassDiagramForm::OnRButtonUp(UINT nFlags, CPoint point) {
	SetFocus();

	int vertCurPos = GetScrollPos(SB_VERT);
	int horzCurPos = GetScrollPos(SB_HORZ);

	this->startX = point.x + horzCurPos;
	this->startY = point.y + vertCurPos;
	this->currentX = point.x + horzCurPos;
	this->currentY = point.y + vertCurPos;

	CMenu *menu;
	if (this->selection->GetLength() > 0) {
		menu = this->classDiagramFormMenu->menu2;
		Figure *figure = this->selection->GetAt(0);
		if ((dynamic_cast<Class*>(figure))) {
			Class *object = static_cast<Class*>(figure);
			if (object->GetAttributePosition() != -1) {
				menu->EnableMenuItem(135, MF_DISABLED);
				menu->EnableMenuItem(131, MF_ENABLED);//135�߰� 131 ����
			}
			else {
				menu->EnableMenuItem(131, MF_DISABLED);
				menu->EnableMenuItem(135, MF_ENABLED);
			}
			if (object->GetMethodPosition() != -1) {
				menu->EnableMenuItem(130, MF_DISABLED);
				menu->EnableMenuItem(132, MF_ENABLED);//130 �߰� 132 ����
			}
			else {
				menu->EnableMenuItem(132, MF_DISABLED);
				menu->EnableMenuItem(130, MF_ENABLED);
			}
			if (object->GetReceptionPosition() != -1) {
				menu->EnableMenuItem(134, MF_ENABLED);
				menu->EnableMenuItem(133, MF_DISABLED);
				//133�߰� 134 ����
			}
			else {
				menu->EnableMenuItem(134, MF_DISABLED);
				menu->EnableMenuItem(133, MF_ENABLED);
			}
			if (object->GetTempletePosition() != -1) {
				//127 �߰� 128 ����
				menu->EnableMenuItem(128, MF_ENABLED);
				menu->EnableMenuItem(127, MF_DISABLED);
			}
			else {
				menu->EnableMenuItem(128, MF_DISABLED);
				menu->EnableMenuItem(127, MF_ENABLED);
			}
		
		}
		else {
			menu->EnableMenuItem(127, MF_DISABLED);
			menu->EnableMenuItem(135, MF_DISABLED);
			menu->EnableMenuItem(130, MF_DISABLED);
			menu->EnableMenuItem(133, MF_DISABLED);
			menu->EnableMenuItem(128, MF_DISABLED);
			menu->EnableMenuItem(131, MF_DISABLED);
			menu->EnableMenuItem(132, MF_DISABLED);
			menu->EnableMenuItem(134, MF_DISABLED);
		}
	}
	else {
		menu = this->classDiagramFormMenu->menu1;
	}
	ClientToScreen(&point); //��ũ�� �������� ������.
	menu->TrackPopupMenu(TPM_LEFTBUTTON | TPM_LEFTALIGN, point.x, point.y, this);

	Invalidate(false);
}
void ClassDiagramForm::OnRButtonDown(UINT nFlags, CPoint point) {
	SetFocus();

	int vertCurPos = GetScrollPos(SB_VERT);
	int horzCurPos = GetScrollPos(SB_HORZ);

	this->startX = point.x + horzCurPos;
	this->startY = point.y + vertCurPos;
	this->currentX = point.x + horzCurPos;
	this->currentY = point.y + vertCurPos;

	this->selection->DeleteAllItems();
	this->selection->SelectByPoint(this->diagram, this->currentX, this->currentY);

	Invalidate(false);
}
BOOL ClassDiagramForm::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {
	CWnd::SetFocus();
	SetFocus();
	bool ret = false;

	// nWheelScrollLines �� �ѹ��� �̵��ϴ� �� �� (Reg���� �о� �´�)
	HKEY hKey = 0;
	DWORD dwType = REG_BINARY;
	DWORD dwSize = 10;
	BYTE* pByte = new BYTE[dwSize];

	ZeroMemory(pByte, dwSize);

	RegOpenKey(HKEY_CURRENT_USER, "Control Panel\\Desktop", &hKey);
	RegQueryValueEx(hKey, "WheelScrollLines", NULL, &dwType, pByte, &dwSize);
	RegCloseKey(hKey);

	int nWheelScrollLines = atoi((char*)pByte);
	delete pByte;

	int vertCurPos = GetScrollPos(SB_VERT);

	if (GetKeyState(VK_CONTROL) >= 0) {
		if (zDelta <= 0) { //���콺 �� �ٿ�
			vertCurPos += nWheelScrollLines * 30;
		}
		else {  //���콺 �� ��
			vertCurPos -= nWheelScrollLines * 30;
		}
		ret = true;
	}
	else {
		if (zDelta <= 0) { //���콺 �� �ٿ�
			this->zoomRate -= 10;
			if (this->zoomRate < 50) {
				this->zoomRate = 50;
			}
		}
		else {  //���콺 �� ��
			this->zoomRate += 10;
			if (this->zoomRate > 200) {
				this->zoomRate = 200;
			}
		}
		this->lastClass->statusBar->DestroyStatus();
		this->lastClass->statusBar->MakeStatusBar(this->lastClass, this->lastClass->GetSafeHwnd(), 0, 0, 5);
		ret = true;
	}
	SetScrollPos(SB_VERT, vertCurPos);
	Invalidate(false);

	return ret;
}
void ClassDiagramForm::OnNcMouseMove(UINT nHitTest, CPoint point) {

	CRect rect;
	this->GetWindowRect(&rect);
	bool ret = rect.PtInRect(CPoint(this->startX, this->startY));
	if (this->startX!=0&& this->startY!=0) {
		switch (nHitTest) {
		case HTTOP: this->zoomRate++; break;
		case HTTOPLEFT:; break;
		case HTTOPRIGHT:; break;
		case HTLEFT:; break;
		case HTRIGHT:; break;
		case HTBOTTOM:; break;
		case HTBOTTOMLEFT:; break;
		case HTBOTTOMRIGHT:; break;
		default: break;
		}
	}
	Invalidate(false);
}

void ClassDiagramForm::OnLButtonDown(UINT nFlags, CPoint point) {
	if (this->zoomRate == 100) {
		CWnd::SetFocus();
		SetFocus();

		MSG msg;
		UINT dblclkTime = GetDoubleClickTime();
		UINT elapseTime = 0;
		//this->SetFocus();
		SetTimer(1, 1, NULL);
		while (elapseTime < dblclkTime) {
			PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
			if (msg.message == WM_LBUTTONDBLCLK || msg.message == WM_RBUTTONDBLCLK) {
				KillTimer(1);
			}
			elapseTime++;
		}
		int vertCurPos = GetScrollPos(SB_VERT);
		int horzCurPos = GetScrollPos(SB_HORZ);

		this->startX = point.x + horzCurPos;
		this->startY = point.y + vertCurPos;
		this->currentX = point.x + horzCurPos;
		this->currentY = point.y + vertCurPos;

		this->mouseLButton->MouseLButtonDown(this->mouseLButton, this->diagram, this->selection, this->startX, this->startY, this->currentX, this->currentY);

		KillTimer(1);
		SetCapture();
		Invalidate(false);
	}
}
void ClassDiagramForm::OnMyMenu(UINT parm_control_id) {

	MenuAction* menuAction = this->classDiagramFormMenu->MenuSelected(parm_control_id);
	if (menuAction != 0) {
		menuAction->MenuPress(this->lastClass);
	}
}
void ClassDiagramForm::OnLButtonDblClk(UINT nFlags, CPoint point) {
	if (this->zoomRate == 100) {
		CPaintDC dc(this);

		int vertCurPos = GetScrollPos(SB_VERT);
		int horzCurPos = GetScrollPos(SB_HORZ);

		this->startX = point.x + horzCurPos;
		this->startY = point.y + vertCurPos;
		this->currentX = point.x + horzCurPos;
		this->currentY = point.y + vertCurPos;

		Figure* figure = this->diagram->FindItem(startX, startY);
		if (figure != NULL && this->selection->GetLength() != 0) {

			this->textEdit = new TextEdit(this, figure);

			if (dynamic_cast<MemoBox*>(figure) || dynamic_cast<ClassName*>(figure)) {
				this->textEdit->Create(NULL, "textEdit", WS_CHILD | WS_VISIBLE, CRect(
					figure->GetX() + GabX - horzCurPos,
					figure->GetY() + GabY + MemoGab - vertCurPos,
					figure->GetX() + figure->GetWidth() - GabX - horzCurPos,
					figure->GetY() + figure->GetHeight() - GabY - vertCurPos), this, 10000, NULL);
			}
			else {
				this->textEdit->Create(NULL, "textEdit", WS_CHILD | WS_VISIBLE, CRect(
					figure->GetX() + GabX - horzCurPos,
					figure->GetY() + GabY - vertCurPos,
					figure->GetX() + figure->GetWidth() - GabX - horzCurPos,
					figure->GetY() + figure->GetHeight() - GabY - vertCurPos), this, 10000, NULL);
			}
		}

		//���õ� relationLine �� ������
		if (this->selection->GetLength() == 1 && dynamic_cast<Relation*>(this->selection->GetAt(0)) && !dynamic_cast<MemoLine*>(this->selection->GetAt(0))) {
			// relationLine ���� rollNamePoints array ���鼭 points ���� �ڽ������� ����Ŭ������ Ȯ���Ѵ�
			Long i = 0;
			Long index = 0;
			Relation *relation = static_cast<Relation*>(this->selection->GetAt(0));
			Long right;
			Long left;
			Long top;
			Long bottom;
			if (!dynamic_cast<Generalization*>(this->selection->GetAt(0)) && !dynamic_cast<Composition*>(this->selection->GetAt(0)) &&
				!dynamic_cast<Compositions*>(this->selection->GetAt(0)) && !dynamic_cast<Dependency*>(this->selection->GetAt(0)) &&
				!dynamic_cast<Realization*>(this->selection->GetAt(0))) {
				while (i < 5 && index == 0) {
					if (i == 0 || i == 2) {
						right = relation->rollNamePoints->GetAt(i).x + 20;
						left = relation->rollNamePoints->GetAt(i).x - 20;
						top = relation->rollNamePoints->GetAt(i).y - 10;
						bottom = relation->rollNamePoints->GetAt(i).y + 10;
					}
					else if (i == 1) {
						right = relation->rollNamePoints->GetAt(i).x + 40;
						left = relation->rollNamePoints->GetAt(i).x - 40;
						top = relation->rollNamePoints->GetAt(i).y - 10;
						bottom = relation->rollNamePoints->GetAt(i).y + 10;
					}
					else if (i == 3 || i == 4) {
						right = relation->rollNamePoints->GetAt(i).x + 25;
						left = relation->rollNamePoints->GetAt(i).x - 25;
						top = relation->rollNamePoints->GetAt(i).y - 10;
						bottom = relation->rollNamePoints->GetAt(i).y + 10;
					}

					if (startX < right && startX > left && startY > top && startY < bottom) {
						index++;
					}
					i++;
				}
			}
			if (index > 0) {
				this->textEdit = new TextEdit(this, relation, i - 1);
				this->textEdit->Create(NULL, "textEdit", WS_CHILD | WS_VISIBLE, CRect(
					left + 1 - horzCurPos,
					top + 1 - vertCurPos,
					right - 1 - horzCurPos,
					bottom - 1 - vertCurPos), this, 10000, NULL);
			}
		}
		if (this->selection->GetLength() == 1 && dynamic_cast<SelfRelation*>(this->selection->GetAt(0))) {
			// relationLine ���� rollNamePoints array ���鼭 points ���� �ڽ������� ����Ŭ������ Ȯ���Ѵ�
			Long i = 0;
			Long index = 0;
			SelfRelation *selfRelation = static_cast<SelfRelation*>(this->selection->GetAt(0));
			Long right;
			Long left;
			Long top;
			Long bottom;
			if (!dynamic_cast<Generalization*>(this->selection->GetAt(0)) && !dynamic_cast<Composition*>(this->selection->GetAt(0)) &&
				!dynamic_cast<Compositions*>(this->selection->GetAt(0)) && !dynamic_cast<Dependency*>(this->selection->GetAt(0)) &&
				!dynamic_cast<Realization*>(this->selection->GetAt(0))) {
				while (i < 5 && index == 0) {
					if (i == 0) {
						right = selfRelation->rollNamePoints->GetAt(i).x + 20;
						left = selfRelation->rollNamePoints->GetAt(i).x - 10;
						top = selfRelation->rollNamePoints->GetAt(i).y - 10;
						bottom = selfRelation->rollNamePoints->GetAt(i).y + 10;
					}
					else if (i == 1) {
						right = selfRelation->rollNamePoints->GetAt(i).x + 30;
						left = selfRelation->rollNamePoints->GetAt(i).x - 30;
						top = selfRelation->rollNamePoints->GetAt(i).y - 10;
						bottom = selfRelation->rollNamePoints->GetAt(i).y + 10;
					}
					else if (i == 2) {
						right = selfRelation->rollNamePoints->GetAt(i).x + 50;
						left = selfRelation->rollNamePoints->GetAt(i).x - 20;
						top = selfRelation->rollNamePoints->GetAt(i).y - 10;
						bottom = selfRelation->rollNamePoints->GetAt(i).y + 10;
					}
					else if (i == 3) {
						right = selfRelation->rollNamePoints->GetAt(i).x + 50;
						left = selfRelation->rollNamePoints->GetAt(i).x - 20;
						top = selfRelation->rollNamePoints->GetAt(i).y - 10;
						bottom = selfRelation->rollNamePoints->GetAt(i).y + 10;
					}
					else if (i == 4) {
						right = selfRelation->rollNamePoints->GetAt(i).x + 10;
						left = selfRelation->rollNamePoints->GetAt(i).x - 20;
						top = selfRelation->rollNamePoints->GetAt(i).y - 10;
						bottom = selfRelation->rollNamePoints->GetAt(i).y + 10;
					}

					if (startX < right && startX > left && startY > top && startY < bottom) {
						index++;
					}
					i++;
				}
			}
			// Ȯ���ؼ� ������ �� index ����صΰ� �� �ڽ� ������� textEdit ���� (textEdit ������ ���� �������ҵ�)

			if (index > 0) {
				this->textEdit = new TextEdit(this, selfRelation, i - 1);
				this->textEdit->Create(NULL, "textEdit", WS_CHILD | WS_VISIBLE, CRect(
					left + 1 - horzCurPos,
					top + 1 - vertCurPos,
					right - 1 - horzCurPos,
					bottom - 1 - vertCurPos), this, 10000, NULL);
				OnKillFocus(NULL);
			}
		}
		Invalidate(false);
	}
}

void ClassDiagramForm::OnLButtonUp(UINT nFlags, CPoint point) {
	if (this->zoomRate == 100) {
		MSG msg;
		UINT dblclkTime = GetDoubleClickTime();
		UINT elapseTime = 0;
		PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
		if (msg.message == WM_LBUTTONDBLCLK || msg.message == WM_RBUTTONDBLCLK) {
			return;
		}
		int vertCurPos = GetScrollPos(SB_VERT);
		int horzCurPos = GetScrollPos(SB_HORZ);

		this->currentX = point.x + horzCurPos;
		this->currentY = point.y + vertCurPos;

		this->mouseLButton->MouseLButtonUp(this->mouseLButton, this, this->diagram, this->selection, this->startX, this->startY, this->currentX, this->currentY);

		this->startX = 0;
		this->startY = 0;
		this->currentX = 0;
		this->currentY = 0;

		KillTimer(1);

		ReleaseCapture();
		Invalidate(false);
	}
}

void ClassDiagramForm::OnMouseMove(UINT nFlags, CPoint point) {
	if (this->zoomRate == 100) {
		if (nFlags == MK_LBUTTON) {
			int vertCurPos = GetScrollPos(SB_VERT);
			int horzCurPos = GetScrollPos(SB_HORZ);

			CRect testRect;
			this->GetClientRect(&testRect);
			
			//����
			if (point.x < testRect.left + 20) {
				horzCurPos -= 20;
				if (horzCurPos < 0) {
					horzCurPos = 0;
				}
			}
			if (point.x > testRect.right - 20) {
				horzCurPos += 20;
				Long maxpos = this->GetScrollLimit(SB_HORZ);
				if (horzCurPos > maxpos) {
					horzCurPos = maxpos;
				}
			}
			if (point.y < testRect.top + 20) {
				vertCurPos -= 20;
				if (vertCurPos < 0) {
					vertCurPos = 0;
				}
			}
			if (point.y > testRect.bottom - 20) {
				vertCurPos += 20;
				Long maxpos = this->GetScrollLimit(SB_VERT);
				if (vertCurPos > maxpos) {
					vertCurPos = maxpos;
				}
			}

			this->currentX = point.x + horzCurPos;
			this->currentY = point.y + vertCurPos;

			SetScrollPos(SB_HORZ, horzCurPos);
			SetScrollPos(SB_VERT, vertCurPos);

			Invalidate(false);
		}

		//Ŀ�����
		/*Long index;
		index = this->selection->SelectByPoint(point.x, point.y);
		if (index == 1) {
		SetCursor(LoadCursor(NULL, IDC_HAND));
		}
		else if (index == 2) {
		SetCursor(LoadCursor(NULL, IDC_CROSS));
		}
		else if (index == 3 || index == 5) {
		SetCursor(LoadCursor(NULL, IDC_HELP));
		}
		else if (index == 4) {
		SetCursor(LoadCursor(NULL, IDC_SIZEALL));
		}*/
	}

}

void ClassDiagramForm::OnClose() {

	
	//6.1. �����Ѵ�.
	//this->Save();

	//6.2. ���̾�׷��� �����.
		if (this->diagram != NULL) {
			delete this->diagram;
			this->diagram = NULL;
		}
		if (this->selection != NULL) {
			delete this->selection;
			this-> selection = NULL;
		}
		if (this->mouseLButton != NULL) {
			delete this->mouseLButton;
			this->mouseLButton = NULL;
		}
		if (this->keyBoard != NULL) {
			delete this->keyBoard;
			this->keyBoard = NULL;
		}
		if (this->historyGraphic != NULL) {
			delete this->historyGraphic;
			this->historyGraphic = NULL;
		}
		if (this->scroll != NULL) {
			delete this->scroll;
			this->scroll = NULL;
		}
		if (this->copyBuffer != NULL) {
			delete this->copyBuffer;
			this->copyBuffer = NULL;
		}
		CWnd::OnClose();
}