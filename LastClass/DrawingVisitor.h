//DrawingVisitor.h

#ifndef _DRAWINGVISITOR_H
#define _DRAWINGVISITOR_H

#include "Visitor.h"

class DrawingVisitor :public Visitor {
public:
	DrawingVisitor();
	~DrawingVisitor();

	void Visit(Class *object, CDC* cPaintDc);
	void Visit(MemoBox* memoBox, CDC* cPaintDc);
	void Visit(Selection *selection, CDC *cPaintDc);

	void Visit(Template *object, CDC *cPaintDc);
	void Visit(ClassName* className, CDC* cPaintDc);
	void Visit(Attribute* attribute, CDC* cPaintDc);
	void Visit(Method* method, CDC* cPaintDc);
	void Visit(Reception* reception, CDC* cPaintDc);
	void Visit(Line *line, CDC* cPaintDc);

	void Visit(Generalization *generalization, CDC* cPaintDc);		//�Ϲ�ȭ
	void Visit(Realization * realization, CDC* cPaintDc);		//��üȭ
	void Visit(Dependency *dependency, CDC* cPaintDc);		//����
	void Visit(Association *association, CDC* cPaintDc);		//����ȭ
	void Visit(DirectedAssociation *directedAssociation, CDC* cPaintDc);		//��������
	void Visit(Aggregation *aggregation, CDC* cPaintDc);		//����
	void Visit(Aggregations *aggregations, CDC* cPaintDc);		//���տ���
	void Visit(Composition *composition, CDC* cPaintDc);		//�ռ�
	void Visit(Compositions *compositions, CDC* cPaintDc);		//���տ���
	void Visit(MemoLine *memoLine, CDC *cPaintDc);

	void Visit(Text* text, CDC* cPaintDc);

};

#endif // _DRAWINGVISITOR_H
