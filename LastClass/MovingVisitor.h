//MovingVisitor.h

#ifndef _MOVINGVISITOR_H
#define _MOVINGVISITOR_H

#include"Visitor.h"

typedef signed long  int Long;
class MovingVisitor :public Visitor {
public:
	MovingVisitor();
	~MovingVisitor();

	void Visit(Class *object, CDC* cPaintDc);
	void Visit(Line *line, CDC* cPaintDc);
	void Visit(SingleByteCharacter *singleByteCharacter, CDC* cPaintDc);
	void Visit(DoubleByteCharacter *doubleByteCharacter, CDC* cPaintDc);
	void Visit(Row* row, CDC* cPaintDc);
	void Visit(Text* text, CDC* cPaintDc);

	//0904추가	CDC* cPaintDc

	void Visit(Generalization *generalization, CDC* cPaintDc);		//일반화

	void Visit(Realization * realization, CDC* cPaintDc);		//실체화

	void Visit(Dependency *dependency, CDC* cPaintDc);		//의존

	void Visit(Association *association, CDC* cPaintDc);		//연관화	CDC* cPaintDc

	void Visit(DirectedAssociation *directedAssociation, CDC* cPaintDc);		//직접연관

	void Visit(Aggregation *aggregation, CDC* cPaintDc);		//집합

	void Visit(Aggregations *aggregations, CDC* cPaintDc);		//집합연관

	void Visit(Composition *composition, CDC* cPaintDc);		//합성

	void Visit(Compositions *compositions, CDC* cPaintDc);		//복합연관

	void Visit(Template *object, CDC *cPaintDc);

	void Visit(MemoBox *memoBox, CDC *cPaintDc);   //CDC  *cPaintDc

	void Visit(MemoLine *memoLine, CDC *cPaintDc);

	void Visit(ClassName *className, CDC *cPaintDc);

	void Visit(Method *method, CDC *cPatinDc);

	void Visit(Attribute *attribute, CDC *cPaintDc);

	void Visit(Selection *selection, CDC *cPaintDc);

	void Visit(Diagram *diagram,Selection *selection, Long distanceX, Long distanceY);

	void Visit(SelfGeneralization *selfGeneralization, CDC *CPatinDc);

	void Visit(SelfDependency *selfDependency, CDC *CPatinDc);

	void Visit(SelfAggregation *selfAggregation, CDC *CPatinDc);

	void Visit(SelfAssociation *selfAssociation, CDC *cPaintDc);

	void Visit(SelfAggregations *selfAggregations, CDC *cPaintDc);

	void Visit(SelfDirectedAssociation *selfDirectedAssociation, CDC *cPaintDc);

	void Visit(SelfComposition *selfComposition, CDC *cPaintDc);

	void Visit(SelfCompositions *selfCompositions, CDC *cPaintDc);
};



#endif //_MOVINGVISITOR_H