//DrawRollNameBoxes.h

#ifndef _DRAWROLLNAMEBOXES_H
#define _DRAWROLLNAMEBOXES_H

#include "Array.h"
#include "afxwin.h"

class Relation;
class SelfRelation;
class DrawRollNameBoxes {
public:
	static DrawRollNameBoxes* Instance();
public:
	DrawRollNameBoxes();
	DrawRollNameBoxes(const DrawRollNameBoxes& source);
	~DrawRollNameBoxes();
public:
	void DrawFirstRollNameBox(Relation *relationLine, CDC *cPaintDc);
	void DrawSecondRollNameBox(Relation *relationLine, CDC *cPaintDc);
	void DrawThirdRollNameBox(Relation *relationLine, CDC *cPaintDc);
	void DrawFourthRollNameBox(Relation *relationLine, CDC *cPaintDc);
	void DrawFifthRollNameBox(Relation *relationLine, CDC *cPaintDc);
	void DrawBoxesWithoutCurvedLine(Relation *relationLine, CDC *cPaintDc);

	void DrawSelfRelationRollNameBox(SelfRelation *SelfRelationLine, CDC *cPaintDc);

private:
	static DrawRollNameBoxes* instance;
};

#endif // _DRAWROLLNAMEBOXES_H