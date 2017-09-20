

//WritingVisitor.h

#ifndef _WRITINGVISITOR_H
#define _WRITINGVISITOR_H
typedef signed long  int Long;
#include "Visitor.h" 

class WritingVisitor : public Visitor {
public:
	WritingVisitor();
	~WritingVisitor();

	void Visit(Line *line, CDC* cPaintDc);
	void Visit(Class *object, CDC* cPaintDc);
	void Visit(SingleByteCharacter *singleByteCharacter, CDC* cPaintDc);
	void Visit(DoubleByteCharacter *doubleByteCharacter, CDC* cPaintDc);
	void Visit(Row* row, CDC* cPaintDc);
	void Visit(Text* text, CDC* cPaintDc);

	 void Visit(Generalization *generalization, CDC* cPaintDc) ;		//�Ϲ�ȭ

     void Visit(Realization * realization, CDC* cPaintDc);		//��üȭ

	 void Visit(Dependency *dependency, CDC* cPaintDc) ;		//����

	 void Visit(Association *association, CDC* cPaintDc) ;		//����ȭ  , CDC* cPaintDc

	 void Visit(DirectedAssociation *directedAssociation, CDC* cPaintDc) ;		//��������

	 void Visit(Aggregation *aggregation, CDC* cPaintDc);		//����

	 void Visit(Aggregations *aggregations, CDC* cPaintDc) ;		//���տ���

	 void Visit(Composition *composition, CDC* cPaintDc) ;		//�ռ�

	 void Visit(Compositions *compositions, CDC* cPaintDc) ;		//���տ���

	 void Visit(Template *object, CDC *cPaintDc);

	 void Visit(MemoBox *memoBox, CDC *cPaintDc);

	 void Visit(MemoLine* memobox, CDC *cPaintDc);

	 void Visit(ClassName *className, CDC *cPaintDc);

	 void Visit(Method *method, CDC *cPaintDc);

	 void Visit(Attribute *attribute, CDC *cPaintDc);

	 void Visit(Selection *selection, CDC *cPaintDc);
	   // CDC  *cPaintDc
	 void Visit(Diagram *diagram, Selection *selection, Long distanceX, Long distanceY);

	 void Visit(SelfGeneralization *selfGeneralization, CDC *cPaintDc);

	 void Visit(SelfAggregation *selfAggregation, CDC *cPaintDc);

	 void Visit(SelfDependency *selfdependency, CDC *cPaintDc);

	 void Visit(SelfAssociation *selfAssociation, CDC *cPaintDc);

	 void Visit(SelfAggregations *selfAggregations, CDC *cPaintDc);

	 void Visit(SelfDirectedAssociation *selfDirectedAssociation, CDC *cPaintDc);

	 void Visit(SelfComposition *selfComposition, CDC *cPaintDc);

	 void Visit(SelfCompositions *selfCompositions, CDC *cPaintDc);
};

#endif // _WRITINGVISITOR_H