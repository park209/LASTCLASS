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
	void DrawFirstRollNameBox(Relation *relationLine, CDC *pDC);
	void DrawSecondRollNameBox(Relation *relationLine, CDC *pDC);
	void DrawThirdRollNameBox(Relation *relationLine, CDC *pDC);
	void DrawFourthRollNameBox(Relation *relationLine, CDC *pDC);
	void DrawFifthRollNameBox(Relation *relationLine, CDC *pDC);
	void DrawBoxesWithoutCurvedLine(Relation *relationLine, CDC *pDC);

	void DrawSelfRelationRollNameBox(SelfRelation *SelfRelationLine, CDC *pDC);

private:
	static DrawRollNameBoxes* instance;
};

#endif // _DRAWROLLNAMEBOXES_H