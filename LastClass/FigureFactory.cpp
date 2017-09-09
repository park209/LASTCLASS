//FigureFactory.cpp

#include "FigureFactory.h"
#include "Class.h"
#include "MemoBox.h"
#include "Line.h"
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
FigureFactory::FigureFactory() {
}
FigureFactory::~FigureFactory() {
}
// 0 = Class, 1 = MemoBox, 2 = Line, 3 = Template, 4 = Generalization(일반화), 5 = Realization(실체화), 6 = Dependency(의존), 7 = Association(연관화),
// 8 = DirectedAssociation(직접연관),  9 = Aggregation(집합), 10 = Aggregations(집합연관), 11 =  Composition(합성), 12 = Compositions(복합연관)
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
	return 0;
}




#include <iostream>
using namespace std;
int main(int argc, char *argv[]) {
	FigureFactory figureFactory;
	Long i = 0;
	while (i <= 12) {
		// 0 = Class, 1 = MemoBox, 2 = Line, 3 = Template, 4 = Generalization(일반화), 5 = Realization(실체화), 6 = Dependency(의존), 7 = Association(연관화),
		// 8 = DirectedAssociation(직접연관),  9 = Aggregation(집합), 10 = Aggregations(집합연관), 11 =  Composition(합성), 12 = Compositions(복합연관)
		Figure* figure = figureFactory.Create(10, 20, 30, 40, i);
		if (dynamic_cast<Class*>(figure)) {
			cout << "클래스" << endl;
		}
		if (dynamic_cast<MemoBox*>(figure)) {
			cout << "메모박스" << endl;
		}
		if (dynamic_cast<Line*>(figure)) {
			cout << "라인" << endl;
		}
		if (dynamic_cast<Template*>(figure)) {
			cout << "템플릿" << endl;
		}
		if (dynamic_cast<Generalization*>(figure)) {
			cout << "일반화" << endl;
		}
		if (dynamic_cast<Realization*>(figure)) {
			cout << "실체화" << endl;
		}
		if (dynamic_cast<Dependency*>(figure)) {
			cout << "의존" << endl;
		}
		if (dynamic_cast<Association*>(figure)) {
			cout << "연관화" << endl;
		}
		if (dynamic_cast<DirectedAssociation*>(figure)) {
			cout << "직접연관" << endl;
		}
		if (dynamic_cast<Aggregation*>(figure)) {
			cout << "집합" << endl;
		}
		if (dynamic_cast<Aggregations*>(figure)) {
			cout << "집합연관" << endl;
		}
		if (dynamic_cast<Composition*>(figure)) {
			cout << "합성" << endl;
		}
		if (dynamic_cast<Compositions*>(figure)) {
			cout << "복합연관" << endl;
		}
		i++;
	}
	return 0;
}