

//DrawingVisitor.h

#ifndef _DRAWINGVISITOR_H
#define _DRAWINGVISITOR_H

#include "Visitor.h"

typedef signed long  int Long;
class DrawingVisitor :public Visitor {
public:
	DrawingVisitor();
	~DrawingVisitor();

	void Visit(Class *object, CDC* cPaintDc);
	void Visit(Line *line, CDC* cPaintDc);
	void Visit(SingleByteCharacter *singleByteCharacter, CDC* cPaintDc);
	void Visit(DoubleByteCharacter *doubleByteCharacter, CDC* cPaintDc);
	void Visit(Row* row, CDC* cPaintDc);



	//0904�߰�	CDC* cPaintDc

	void Visit(Generalization *generalization, CDC* cPaintDc);		//�Ϲ�ȭ

	void Visit(Realization * realization, CDC* cPaintDc);		//��üȭ

	void Visit(Dependency *dependency, CDC* cPaintDc);		//����

	void Visit(Association *association, CDC* cPaintDc);		//����ȭ	CDC* cPaintDc

	void Visit(DirectedAssociation *directedAssociation, CDC* cPaintDc);		//��������

	void Visit(Aggregation *aggregation, CDC* cPaintDc);		//����

	void Visit(Aggregations *aggregations, CDC* cPaintDc);		//���տ���

	void Visit(Composition *composition, CDC* cPaintDc);		//�ռ�

	void Visit(Compositions *compositions, CDC* cPaintDc);		//���տ���

	void Visit(Template *object, CDC *cPaintDc);

	void Visit(MemoBox *memoBox, CDC *cPaintDc);   //CDC  *cPaintDc
};

#endif // _DRAWINGVISITOR_H
