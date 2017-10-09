//ClassDiagramForm.cpp

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
#include "ToolBar.h"
#include "StatusBar.h"

#include "Scroll.h"
#include "ScrollAction.h"

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
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

ClassDiagramForm::ClassDiagramForm() { // 생성자 맞는듯
	this->diagram = NULL;
	this->textEdit = NULL;
	this->selection = NULL;
	this->mouseLButton = NULL;
	this->keyBoard = NULL;
	this->historyGraphic = NULL;
	this->scroll = NULL;
	this->startX = 0;
	this->startY = 0;
	this->currentX = 0;
	this->currentY = 0;
	this->fileName = "";
	this->copyBuffer = NULL;
	this->isCut = 0;
}

Long ClassDiagramForm::Load() {
	Long position = -1;
	Long i;
	Long x = 0;
	Long y = 0;
	Long width = 0;
	Long height = 0;
	Long length = 0;
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


	//CFileDialog  dlgFile(true, "txt", "*", NULL, "텍스트 문서(*.txt)");
	//if (dlgFile.DoModal() == IDOK)
	//{
	//	this->fileName = dlgFile.GetPathName();
	//}
	fTest.open(this->fileName);
	//fTest.open("text.txt");
	//종류 구별을 위한 마지막 칸 
	// 0 = Class, 1 = MemoBox, 2 = Line, 3 = Template, 4 = Generalization(일반화), 5 = Realization(실체화), 6 = Dependency(의존), 7 = Association(연관화),
	// 8 = DirectedAssociation(직접연관),  9 = Aggregation(집합), 10 = Aggregations(집합연관), 11 =  Composition(합성), 12 = Compositions(복합연관), 13 = MemoLine
	// 14 = ClassName , 15 = Attribute , 16 = Method , 17 = Reception

	if (fTest.is_open()) {  
		getline(fTest, temp1);
		sscanf_s((CString)temp1.c_str(), "%d %d %d %d %d %d", &length, &x, &y, &width, &height, &type);
		while (!fTest.eof()) {
			figure = factory.Create(x, y, width, height, type);
			position = this->diagram->Add(figure);
			FigureComposite *figureComposite = static_cast<FigureComposite*>(this->diagram->GetAt(position));
			if (type == 7) {   //메모박스이면
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
				sscanf_s((CString)temp1.c_str(), "%d %d %d %d %d", &x, &y, &width, &height, &type); //말단객체
				figure = factory.Create(x, y, width, height, type);
			
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
			sscanf_s((CString)temp1.c_str(), "%d %d %d %d %d %d", &length, &x, &y, &width, &height, &type);
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
		//CFileDialog  dlgFile(false,"txt","*", OFN_CREATEPROMPT | OFN_OVERWRITEPROMPT,"텍스트 문서(*.txt)");
		//if (dlgFile.DoModal() == IDOK)
		//{
			//fileName = dlgFile.GetPathName();
		//}
	fTest.open(this->fileName);
	if (fTest.is_open()) {
		while (i < this->diagram->GetLength()) {
			//종류 구별을 위한 마지막 칸 
			// 0 = Class, 1 = MemoBox, 2 = Line, 3 = Template, 4 = Generalization(일반화), 5 = Realization(실체화), 
			//6 = Dependency(의존), 7 = Association(연관화),
			// 8 = DirectedAssociation(직접연관),  9 = Aggregation(집합), 10 = Aggregations(집합연관), 
			//11 =  Composition(합성), 12 = Compositions(복합연관), 13 = MemoLine
			// 14 = ClassName , 15 = Attribute , 16 = Method , 17 = Reception , 18 =SelfGeneralization ,
			//19 = SelfDependency , 20 = SelfAssociation , 21 = SelfDirectedAssociation
			// 22 = SelfAggregation , 23 = SelfAggregations , 24 =SelfComposition , 25 = SelfCompositions
			j = 0;
			if (dynamic_cast<Class*>(this->diagram->GetAt(i))) {
				object = static_cast<FigureComposite*>(this->diagram->GetAt(i));
				fTest << object->GetLength() << " " << object->GetX() << " " << object->GetY()
					<< " " << object->GetWidth() << " " << object->GetHeight() << " " << 0 << endl;
				while (j < object->GetLength())
				{

					k = 0;
					l = 0;
					if (dynamic_cast<ClassName*>(object->GetAt(j))) {
						figure = static_cast<ClassName*>(object->GetAt(j));
						fontSize = figure->GetFontSize();
						rowLength = figure->GetRowCount(figure->GetContent());
						fTest << figure->GetX() << " " << figure->GetY() << " " << figure->GetWidth() << " "
							<< figure->GetHeight() << " " << 1 << endl;
						fTest << fontSize << " " << rowLength << endl;
						fTest << figure->GetContent() << endl;
					}
					else if (dynamic_cast<Line*>(object->GetAt(j))) {
						figure = object->GetAt(j);
						fTest << figure->GetX() << " " << figure->GetY() << " " <<
							figure->GetWidth() << " " << figure->GetHeight() << " " << 2 << endl;
					}
					else if (dynamic_cast<Attribute*>(object->GetAt(j))) {
						figure = static_cast<Attribute*>(object->GetAt(j));
						fontSize = figure->GetFontSize();
						rowLength = figure->GetRowCount(figure->GetContent());
						fTest << figure->GetX() << " " << figure->GetY() << " " << figure->GetWidth() << " "
							<< figure->GetHeight() << " " << 3 << endl;
						fTest << fontSize << " " << rowLength << endl;
						fTest << figure->GetContent() << endl;
					}
					else if (dynamic_cast<Method*>(object->GetAt(j))) {
						figure = static_cast<Method*>(object->GetAt(j));
						fontSize = figure->GetFontSize();
						rowLength = figure->GetRowCount(figure->GetContent());
						fTest << figure->GetX() << " " << figure->GetY() << " " << figure->GetWidth() << " "
							<< figure->GetHeight() << " " << 4 << endl;
						fTest << fontSize << " " << rowLength << endl;
						fTest << figure->GetContent() << endl;
					}
					else if (dynamic_cast<Reception*>(object->GetAt(j))) {
						figure = static_cast<Reception*>(object->GetAt(j));
						fontSize = figure->GetFontSize();
						rowLength = figure->GetRowCount(figure->GetContent());
						fTest << figure->GetX() << " " << figure->GetY() << " " << figure->GetWidth() << " "
							<< figure->GetHeight() << " " << 5 << endl;
						fTest << fontSize << " " << rowLength << endl;
						fTest << figure->GetContent() << endl;
					}
					else if (dynamic_cast<Template*>(object->GetAt(j))) {
						figure = object->GetAt(j);
						fontSize = figure->GetFontSize();
						rowLength = figure->GetRowCount(figure->GetContent());
						fTest << figure->GetX() << " " << figure->GetY() << " " <<
							figure->GetWidth() << " " << figure->GetHeight() << " " << 6 << endl;
						fTest << fontSize << " " << rowLength << endl;
						fTest << figure->GetContent() << endl;
					}
					else if (dynamic_cast<MemoLine*>(object->GetAt(j))) {
						Relation *relation = static_cast<Relation*>(object->GetAt(j));
						fTest << relation->GetX() << " " << relation->GetY() << " " <<
							relation->GetWidth() << " " << relation->GetHeight() << " " << 8 << endl;
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
							relation->GetWidth() << " " << relation->GetHeight() << " " << 9 << endl;
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
							relation->GetWidth() << " " << relation->GetHeight() << " " << 10 << endl;
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
							relation->GetWidth() << " " << relation->GetHeight() << " " << 11 << endl;
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
							relation->GetWidth() << " " << relation->GetHeight() << " " << 12 << endl;
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
							relation->GetWidth() << " " << relation->GetHeight() << " " << 13 << endl;
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
							relation->GetWidth() << " " << relation->GetHeight() << " " << 14 << endl;
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
							relation->GetWidth() << " " << relation->GetHeight() << " " << 15 << endl;
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
							relation->GetWidth() << " " << relation->GetHeight() << " " << 16 << endl;
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
							relation->GetWidth() << " " << relation->GetHeight() << " " << 17 << endl;
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
						fTest << selfRelation->GetX() << " " << selfRelation->GetY() << " " << selfRelation->GetWidth() << " " << selfRelation->GetHeight() << " " << 18 << endl;
						while (l < 5) {
							fTest << selfRelation->rollNames->GetAt(l) << endl;;
							fTest << selfRelation->rollNamePoints->GetAt(l).x << " " << selfRelation->rollNamePoints->GetAt(l).y << endl;
							l++;
						}
					}
					else if (dynamic_cast<SelfDependency*>(object->GetAt(j))) {
						selfRelation = static_cast<SelfRelation*>(object->GetAt(j));
						fTest << selfRelation->GetX() << " " << selfRelation->GetY() << " " << selfRelation->GetWidth() << " " << selfRelation->GetHeight() << " " << 19 << endl;
						while (l < 5) {
							fTest << selfRelation->rollNames->GetAt(l) << endl;;
							fTest << selfRelation->rollNamePoints->GetAt(l).x << " " << selfRelation->rollNamePoints->GetAt(l).y << endl;
							l++;
						}

					}
					else if (dynamic_cast<SelfAssociation*>(object->GetAt(j))) {
						selfRelation = static_cast<SelfRelation*>(object->GetAt(j));
						fTest << selfRelation->GetX() << " " << selfRelation->GetY() << " " << selfRelation->GetWidth() << " " << selfRelation->GetHeight() << " " << 20 << endl;
						while (l < 5) {
							fTest << selfRelation->rollNames->GetAt(l) << endl;;
							fTest << selfRelation->rollNamePoints->GetAt(l).x << " " << selfRelation->rollNamePoints->GetAt(l).y << endl;
							l++;
						}
					}
					else if (dynamic_cast<SelfDirectedAssociation*>(object->GetAt(j))) {
						selfRelation = static_cast<SelfRelation*>(object->GetAt(j));
						fTest << selfRelation->GetX() << " " << selfRelation->GetY() << " " << selfRelation->GetWidth() << " " << selfRelation->GetHeight() << " " << 21 << endl;
						while (l < 5) {
							fTest << selfRelation->rollNames->GetAt(l) << endl;;
							fTest << selfRelation->rollNamePoints->GetAt(l).x << " " << selfRelation->rollNamePoints->GetAt(l).y << endl;
							l++;
						}
					}
					else if (dynamic_cast<SelfAggregation*>(object->GetAt(j))) {
						selfRelation = static_cast<SelfRelation*>(object->GetAt(j));
						fTest << selfRelation->GetX() << " " << selfRelation->GetY() << " " << selfRelation->GetWidth() << " " << selfRelation->GetHeight() << " " << 22 << endl;
						while (l < 5) {
							fTest << selfRelation->rollNames->GetAt(l) << endl;;
							fTest << selfRelation->rollNamePoints->GetAt(l).x << " " << selfRelation->rollNamePoints->GetAt(l).y << endl;
							l++;
						}
					}
					else if (dynamic_cast<SelfAggregations*>(object->GetAt(j))) {
						selfRelation = static_cast<SelfRelation*>(object->GetAt(j));
						fTest << selfRelation->GetX() << " " << selfRelation->GetY() << " " << selfRelation->GetWidth() << " " << selfRelation->GetHeight() << " " << 23 << endl;
						while (l < 5) {
							fTest << selfRelation->rollNames->GetAt(l) << endl;;
							fTest << selfRelation->rollNamePoints->GetAt(l).x << " " << selfRelation->rollNamePoints->GetAt(l).y << endl;
							l++;
						};

					}
					else if (dynamic_cast<SelfComposition*>(object->GetAt(j))) {
						selfRelation = static_cast<SelfRelation*>(object->GetAt(j));
						fTest << selfRelation->GetX() << " " << selfRelation->GetY() << " " << selfRelation->GetWidth() << " " << selfRelation->GetHeight() << " " << 24 << endl;
						while (l < 5) {
							fTest << selfRelation->rollNames->GetAt(l) << endl;;
							fTest << selfRelation->rollNamePoints->GetAt(l).x << " " << selfRelation->rollNamePoints->GetAt(l).y << endl;
							l++;
						}

					}
					else if (dynamic_cast<SelfCompositions*>(object->GetAt(j))) {
						selfRelation = static_cast<SelfRelation*>(object->GetAt(j));
						fTest << selfRelation->GetX() << " " << selfRelation->GetY() << " " << selfRelation->GetWidth() << " " << selfRelation->GetHeight() << " " << 25 << endl;
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
					<< " " << object->GetWidth() << " " << object->GetHeight() << " " << 7 << endl;;
				fTest << fontSize << " " << rowLength << endl;
				fTest << object->GetContent() << endl;
				while (j < object->GetLength()) {
					Relation *relation = static_cast<Relation*>(object->GetAt(j));
					fTest << relation->GetX() << " " << relation->GetY() << " " <<
						relation->GetWidth() << " " << relation->GetHeight() << " " << 8 << endl;
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
	return this->diagram->GetLength();
}

int ClassDiagramForm::OnCreate(LPCREATESTRUCT lpCreateStruct) {

	CWnd::OnCreate(lpCreateStruct); //코드재사용 오버라이딩 //상속에서
	CWnd::SetFocus();                        //1.1. 다이어그램을 준비한다

	this->diagram = new Diagram();
	this->selection = new Selection;
	this->mouseLButton = new MouseLButton;
	this->historyGraphic = new HistoryGraphic;
	this->keyBoard = new KeyBoard;
	this->scroll = new Scroll;

	ModifyStyle(0, WS_CLIPCHILDREN);
	SetScrollRange(SB_VERT, 0, pageHeight, 0);
	
	/*ToolBar toolBar;
	toolBar.MakeToolBar(this->GetSafeHwnd());
	
	StatusBar statusBar;
	statusBar.MakeStatusBar(this, this->GetSafeHwnd(), NULL, NULL, 5);*/


	//1.2. 적재한다
	//this->Load();
	//1.3. 윈도우를 갱신한다
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
	bitmap.CreateCompatibleBitmap(&dc, rect.right + pageWidth, rect.bottom + pageHeight);
	pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.FillSolidRect(CRect(0, 0, rect.right + pageWidth, rect.bottom + pageHeight), RGB(255, 255, 255));
	CFont cFont;//CreateFont에 값18을 textEdit의 rowHight로 바꿔야함
	cFont.CreateFont(25, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,// 글꼴 설정
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "맑은 고딕");
	SetFont(&cFont, TRUE);
	CFont *oldFont = memDC.SelectObject(&cFont);

	DrawingVisitor drawingVisitor;
	this->diagram->Accept(drawingVisitor, &memDC);
	WritingVisitor writingVisitor;
	this->diagram->Accept(writingVisitor, &memDC);
	this->selection->Accept(drawingVisitor, &memDC); // selectionFlag 추가 확인
	if (this->startX != 0 && this->startY != 0 && this->currentX != 0 && this->currentY != 0) {
		this->mouseLButton->MouseLButtonDrag(this->mouseLButton, this->diagram, this->selection, this->startX, this->startY, this->currentX, this->currentY, &memDC);
	}

	int vertCurPos = GetScrollPos(SB_VERT);
	int horzCurPos = GetScrollPos(SB_HORZ);

	dc.BitBlt(-horzCurPos,
		-vertCurPos,
		rect.right + horzCurPos,
		rect.bottom + vertCurPos,
		&memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(oldFont);
	cFont.DeleteObject();
	memDC.SelectObject(pOldBitmap);
	bitmap.DeleteObject();
	memDC.DeleteDC();
}
void ClassDiagramForm::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (nChar == 0 || nChar == 49 || nChar == 81 || nChar == 50 || nChar == 55 || nChar == 56 || nChar == 53 ||
		nChar == 57 || nChar == 48 || nChar == 52 || nChar == 54 || nChar == 87 || nChar == 51) {
		this->mouseLButton->ChangeState(nChar);
	}
	CClientDC dc(this);
	CFont cFont;//CreateFont에 값18을 textEdit의 rowHight로 바꿔야함
	cFont.CreateFont(25, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,// 글꼴 설정
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "맑은 고딕");
	SetFont(&cFont, TRUE);
	CFont *oldFont = dc.SelectObject(&cFont);
	KeyAction *keyAction = this->keyBoard->KeyDown(this, nChar, nRepCnt, nFlags);
	if (keyAction != 0) {
		keyAction->KeyPress(this,&dc);
		Invalidate(false);
	}
	dc.SelectObject(oldFont);
	cFont.DeleteObject();
}


void ClassDiagramForm::OnSetFocus(CWnd* pOldWnd) {
	CWnd::OnSetFocus(pOldWnd);
	CWnd::SetFocus();
	Invalidate(false);
}
void ClassDiagramForm::OnSize(UINT nType, int cx, int cy) {
	Invalidate(false);
}

void ClassDiagramForm::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
	ScrollAction *scrollAction = this->scroll->MoveVScroll(this, nSBCode, nPos, pScrollBar);
	if (scrollAction != 0) {
		scrollAction->Scrolling(this);
	}
	Invalidate(false);
}

void ClassDiagramForm::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
	ScrollAction *scrollAction = this->scroll->MoveHScroll(this, nSBCode, nPos, pScrollBar);
	if (scrollAction != 0) {
		scrollAction->Scrolling(this);
	}
	Invalidate(false);
}

BOOL ClassDiagramForm::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {
	CWnd::SetFocus();
	SetFocus();
	bool ret = false;
	int vertCurPos = GetScrollPos(SB_VERT);

	if (zDelta <= 0) { //마우스 휠 다운
		vertCurPos += 20;
		ret = true;
	}
	else {  //마우스 휠 업
		vertCurPos -= 20;
		ret = true;
	}
	SetScrollPos(SB_VERT, vertCurPos);
	Invalidate(false);

	return ret;
}

void ClassDiagramForm::OnLButtonDown(UINT nFlags, CPoint point) {
	CWnd::SetFocus();
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

void ClassDiagramForm::OnLButtonDblClk(UINT nFlags, CPoint point) {
	CPaintDC dc(this);

	int vertCurPos = GetScrollPos(SB_VERT);
	int horzCurPos = GetScrollPos(SB_HORZ);

	this->startX = point.x + horzCurPos;
	this->startY = point.y + vertCurPos;
	this->currentX = point.x + horzCurPos;
	this->currentY = point.y + vertCurPos;

	Figure* figure = this->diagram->FindItem(startX, startY);
	if (figure != NULL) {

		this->textEdit = new TextEdit(figure);

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

	//선택된 relationLine 이 있으면
	if (this->selection->GetLength() == 1 && dynamic_cast<Relation*>(this->selection->GetAt(0)) && !dynamic_cast<MemoLine*>(this->selection->GetAt(0))) {
		// relationLine 에서 rollNamePoints array 돌면서 points 에서 박스범위가 더블클린인지 확인한다
		Long i = 0;
		Long index = 0;
		Relation *relation = static_cast<Relation*>(this->selection->GetAt(0));
		Long right;
		Long left;
		Long top;
		Long bottom;
		while (i < 5 && index == 0) {
			if (i != 1) {
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
			if (startX < right && startX > left && startY > top && startY < bottom) {
				index++;
			}
			i++;
		}
		if (index > 0) {
			this->textEdit = new TextEdit(relation, i - 1);
			this->textEdit->Create(NULL, "textEdit", WS_CHILD | WS_VISIBLE, CRect(
				left + 1 - horzCurPos,
				top + 1 - vertCurPos,
				right - 1 - horzCurPos,
				bottom - 1 - vertCurPos), this, 10000, NULL);
		}
	}
	if (this->selection->GetLength() == 1 && dynamic_cast<SelfRelation*>(this->selection->GetAt(0))) {
		// relationLine 에서 rollNamePoints array 돌면서 points 에서 박스범위가 더블클린인지 확인한다
		Long i = 0;
		Long index = 0;
		SelfRelation *selfRelation = static_cast<SelfRelation*>(this->selection->GetAt(0));
		Long right;
		Long left;
		Long top;
		Long bottom;
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
				right = selfRelation->rollNamePoints->GetAt(i).x + 10;
				left = selfRelation->rollNamePoints->GetAt(i).x - 20;
				top = selfRelation->rollNamePoints->GetAt(i).y - 10;
				bottom = selfRelation->rollNamePoints->GetAt(i).y + 10;
			}
			else if (i == 3) {
				right = selfRelation->rollNamePoints->GetAt(i).x + 10;
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
		// 확인해서 있으면 그 index 기억해두고 그 박스 사이즈로 textEdit 연다 (textEdit 생성자 따로 만들어야할듯)

		if (index > 0) {
			this->textEdit = new TextEdit(selfRelation, i - 1);
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

void ClassDiagramForm::OnLButtonUp(UINT nFlags, CPoint point) {

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

void ClassDiagramForm::OnMouseMove(UINT nFlags, CPoint point) {

	if (nFlags == MK_LBUTTON) {

		int vertCurPos = GetScrollPos(SB_VERT);
		int horzCurPos = GetScrollPos(SB_HORZ);

		this->currentX = point.x + horzCurPos;
		this->currentY = point.y + vertCurPos;

	Invalidate(false);
	}
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

void ClassDiagramForm::OnClose() {
	CWnd::OnClose();
	//6.1. 저장한다.
	//this->Save();
	int messageBox = IDNO;
	INT_PTR int_ptr = IDOK;
	if (this->historyGraphic->undoGraphicArray->GetLength() != 0) {
		if (this->fileName == "") {
			messageBox = MessageBox(_T("변경 내용을 제목 없음에 저장하시겠습니까?"), "ClassDiagram", MB_YESNOCANCEL);

			if (messageBox == IDYES) {
				CFileDialog  dlgFile(false, "txt", "*", OFN_CREATEPROMPT | OFN_OVERWRITEPROMPT, "텍스트 문서(*.txt)");
				int_ptr = dlgFile.DoModal();
				if (int_ptr == IDOK) {
					this->fileName = dlgFile.GetPathName();
					this->Save();
				}
				//else {
				//return;  //보류
				//}
			}
		}
		else {
			CString object;
			object = "변경내용을 ";
			object.Append(this->fileName);
			object.Append("에 저장하시겠습니까?");
			messageBox = MessageBox(object, "ClassDiagram", MB_YESNOCANCEL);
			if (messageBox == IDYES) {
				this->Save();
			}
		}
	}

	//6.2. 다이어그램을 지운다.
	if (messageBox != IDCANCEL && int_ptr == IDOK) {//== IDYES || messageBox == IDNO ) {
		if (this->diagram != NULL) {
			delete this->diagram;
		}
		if (this->selection != NULL) {
			delete this->selection;
		}
		if (this->mouseLButton != NULL) {
			delete this->mouseLButton;
		}
		if (this->keyBoard != NULL) {
			delete this->keyBoard;
		}
		if (this->historyGraphic != NULL) {
			delete this->historyGraphic;
		}
		if (this != NULL) {
			delete this;
		}
	}
}