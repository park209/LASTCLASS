//FigureFactory.cpp

#include "FigureFactory.h"
#include "Class.h"
#include "Line.h"
#include "MemoBox.h"
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
#include "TextComponent.h"
#include "Row.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include "MemoLine.h"

FigureFactory::FigureFactory() {
}
FigureFactory::~FigureFactory() {
}

TextComponent* FigureFactory::CreateRow(Long x, Long y, Long rowHeight, Long classID, string stringCharacter) {
	Row* row = new Row;
	ULong i = 0;

	while (i < strlen(stringCharacter.c_str())) {
		if (stringCharacter[i] & 0x80) {
			char character[2] = { 0, };
			character[0] = stringCharacter[i];
			character[1] = stringCharacter[i + 1];
			i++;
			DoubleByteCharacter doubleTemp(character);
			row->Add(doubleTemp.Clone());
		}
		else {
			SingleByteCharacter singleTemp(stringCharacter[i]);
			row->Add(singleTemp.Clone());
		}
		i++;
	}
	return row->Clone();

	/*stringCharacter.at(i);
	if (sizeof(stringCharacter.at(i)) == 1) {
	char single = stringCharacter.at(i);
	dynamic_cast<Row*>(row)->Add(this->CreateSingleCharacter(single));
	}
	else if (sizeof(stringCharacter.at(i)) == 2) {
	char character[2] = { 0, };
	*character = stringCharacter.at(i);
	dynamic_cast<Row*>(row)->Add(this->CreateDoubleCharacter(character));
	}
	i++;
	}
	return row; */
}

// 0 = Class, 1 = MemoBox, 2 = Line, 3 = Template, 4 = Generalization(�Ϲ�ȭ), 5 = Realization(��üȭ), 6 = Dependency(����), 7 = Association(����ȭ),
// 8 = DirectedAssociation(��������),  9 = Aggregation(����), 10 = Aggregations(���տ���), 11 =  Composition(�ռ�), 12 = Compositions(���տ���)
Figure* FigureFactory::Create(Long x, Long y, Long width, Long height, Long type) {
	if (type == 0) {
		return new Class(x, y, width, height);
	}
	if (type == 1) {
		return new MemoBox(x, y, width, height);
	}
	if (type == 2) {
		return new Line(x, y, width, height);
	}
	if (type == 3) {
		return new Template(x, y, width, height);
	}
	if (type == 4) {
		return new Generalization(x, y, width, height);
	}
	if (type == 5) {
		return new Realization(x, y, width, height);
	}
	if (type == 6) {
		return new Dependency(x, y, width, height);
	}
	if (type == 7) {
		return new Association(x, y, width, height);
	}
	if (type == 8) {
		return new DirectedAssociation(x, y, width, height);
	}
	if (type == 9) {
		return new Aggregation(x, y, width, height);
	}
	if (type == 10) {
		return new Aggregations(x, y, width, height);
	}
	if (type == 11) {
		return new Composition(x, y, width, height);
	}
	if (type == 12) {
		return new Compositions(x, y, width, height);
	}
	if (type == 13) {
		return new MemoLine(x, y, width, height);
	}
	return 0;
}



//
//#include <iostream>
//using namespace std;
//int main(int argc, char *argv[]) {
//	FigureFactory figureFactory;
//	Long i = 0;
//	while (i <= 12) {
//		// 0 = Class, 1 = MemoBox, 2 = Line, 3 = Template, 4 = Generalization(�Ϲ�ȭ), 5 = Realization(��üȭ), 6 = Dependency(����), 7 = Association(����ȭ),
//		// 8 = DirectedAssociation(��������),  9 = Aggregation(����), 10 = Aggregations(���տ���), 11 =  Composition(�ռ�), 12 = Compositions(���տ���)
//		Figure* figure = figureFactory.Create(10, 20, 30, 40, i);
//		if (dynamic_cast<Class*>(figure)) {
//			cout << "Ŭ����" << endl;
//		}
//		if (dynamic_cast<MemoBox*>(figure)) {
//			cout << "�޸�ڽ�" << endl;
//		}
//		if (dynamic_cast<Line*>(figure)) {
//			cout << "����" << endl;
//		}
//		if (dynamic_cast<Template*>(figure)) {
//			cout << "���ø�" << endl;
//		}
//		if (dynamic_cast<Generalization*>(figure)) {
//			cout << "�Ϲ�ȭ" << endl;
//		}
//		if (dynamic_cast<Realization*>(figure)) {
//			cout << "��üȭ" << endl;
//		}
//		if (dynamic_cast<Dependency*>(figure)) {
//			cout << "����" << endl;
//		}
//		if (dynamic_cast<Association*>(figure)) {
//			cout << "����ȭ" << endl;
//		}
//		if (dynamic_cast<DirectedAssociation*>(figure)) {
//			cout << "��������" << endl;
//		}
//		if (dynamic_cast<Aggregation*>(figure)) {
//			cout << "����" << endl;
//		}
//		if (dynamic_cast<Aggregations*>(figure)) {
//			cout << "���տ���" << endl;
//		}
//		if (dynamic_cast<Composition*>(figure)) {
//			cout << "�ռ�" << endl;
//		}
//		if (dynamic_cast<Compositions*>(figure)) {
//			cout << "���տ���" << endl;
//		}
//		i++;
//	}
//	return 0;
//}