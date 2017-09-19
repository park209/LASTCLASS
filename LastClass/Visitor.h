//Visitor.h

#ifndef _VISITOR_H
#define _VISITOR_H

#include <afxwin.h>
//MainForm Control Class
class Class;
class MemoBox;
//Entity Class
class Template;
class ClassName;
class Method;
class Attribute;
class Selection;
class Reception;
class Line;
//Entity Class
class Generalization;
class Realization;
class Dependency;
class Association;
class DirectedAssociation;
class Aggregation;
class Aggregations;
class Composition;
class Compositions;
class MemoLine;
//SubForm Control Class
class Text;
class Visitor{
public:
	virtual ~Visitor();

	virtual void Visit(Class *object, CDC* cPaintDc) = 0;
	virtual void Visit(MemoBox* memobox, CDC *cPaintDc) = 0;

	virtual void Visit(Template *object, CDC *cPaintDc) = 0;
	virtual void Visit(ClassName *className, CDC *cPaintDc) = 0;
	virtual void Visit(Method *method, CDC *cPaintDc) = 0;
	virtual void Visit(Attribute *attribute, CDC *cPaintDc) = 0;
	virtual void Visit(Reception* reception, CDC* cPaintDc) = 0;
	virtual void Visit(Line *line, CDC* cPaintDc) = 0;

	virtual void Visit(Generalization *generalization, CDC* cPaintDc) = 0;		//�Ϲ�ȭ
	virtual void Visit(Realization * realization, CDC* cPaintDc) = 0;		//��üȭ
	virtual void Visit(Dependency *dependency, CDC* cPaintDc) = 0;		//����
	virtual void Visit(Association *association, CDC* cPaintDc) = 0;		//����ȭ , CDC* cPaintDc
	virtual void Visit(DirectedAssociation *directedAssociation, CDC* cPaintDc) = 0;		//��������
	virtual void Visit(Aggregation *aggregation, CDC* cPaintDc) = 0;		//����
	virtual void Visit(Aggregations *aggregations, CDC* cPaintDc) = 0;		//���տ���
	virtual void Visit(Composition *composition, CDC* cPaintDc) = 0;		//�ռ�
	virtual void Visit(Compositions *compositions, CDC* cPaintDc) = 0;		//���տ���
	virtual void Visit(MemoLine* memobox, CDC *cPaintDc) = 0; //�޸�

	virtual void Visit(Text* text, CDC *cPaintDc) = 0;
protected:
	Visitor();
};

#endif // _VISITOR_H
