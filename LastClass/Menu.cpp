#include "Menu.h"
#include "ClassDiagramForm.h"
#include "MenuAction.h"
#include "ClassMenuAction.h"
#include "MemoBoxMenuAction.h"

Menu::Menu(ClassDiagramForm* classDiagramForm) {
	this->mainMenu = new CMenu;
	this->popupMenu = new CMenu;
	this->editMenu = new CMenu;
	this->supportMenu = new CMenu;
	this->drawMenu = new CMenu;
	this->relationMenu = new CMenu;
	this->mainMenu->CreateMenu();
	this->popupMenu->CreatePopupMenu();
	this->editMenu->CreatePopupMenu();
	this->supportMenu->CreatePopupMenu();
	this->drawMenu->CreatePopupMenu();
	this->relationMenu->CreatePopupMenu();

	this->popupMenu->AppendMenu(MF_STRING, 100, "새로 만들기");
	this->popupMenu->AppendMenu(MF_STRING, 101, "열기");
	this->popupMenu->AppendMenu(MF_STRING, 102, "저장");
	this->popupMenu->AppendMenu(MF_STRING, 103, "다른이름으로 저장");
	this->popupMenu->AppendMenu(MF_STRING, 105, "미리보기");
	this->popupMenu->AppendMenu(MF_STRING, 104, "인쇄하기");
	this->popupMenu->AppendMenu(MF_STRING, 106, "끝내기");
	this->editMenu->AppendMenu(MF_STRING, 107, "복사하기");
	this->editMenu->AppendMenu(MF_STRING, 108, "붙여넣기");
	this->drawMenu->AppendMenu(MF_STRING , 110, "클래스 그리기"); //
	this->drawMenu->AppendMenu(MF_STRING, 111, "메모박스 그리기"); //
	this->drawMenu->AppendMenu(MF_POPUP, (UINT_PTR)this->relationMenu->m_hMenu, "관계선 그리기");
	this->relationMenu->AppendMenu(MF_STRING, 112, "일반화");
	this->relationMenu->AppendMenu(MF_STRING, 113, "실체화");
	this->relationMenu->AppendMenu(MF_STRING, 114, "의존");
	this->relationMenu->AppendMenu(MF_STRING, 115, "연관");
	this->relationMenu->AppendMenu(MF_STRING, 116, "직접연관");
	this->relationMenu->AppendMenu(MF_STRING, 117, "집합");
	this->relationMenu->AppendMenu(MF_STRING, 118, "집합연관");
	this->relationMenu->AppendMenu(MF_STRING, 119, "합성");
	this->relationMenu->AppendMenu(MF_STRING, 120, "복합연관");
	this->relationMenu->AppendMenu(MF_STRING, 121, "메모라인");
	this->supportMenu->AppendMenu(MF_STRING, 122, "도움말 ");
	this->mainMenu->AppendMenu(MF_POPUP, (UINT_PTR)this->popupMenu->m_hMenu, "파일");
	this->mainMenu->AppendMenu(MF_POPUP, (UINT_PTR)this->editMenu->m_hMenu, "편집");
	this->mainMenu->AppendMenu(MF_POPUP, (UINT_PTR)this->drawMenu->m_hMenu, "그리기");
	this->mainMenu->AppendMenu(MF_POPUP, (UINT_PTR)this->supportMenu->m_hMenu, "도움말");
	classDiagramForm->SetMenu(this->mainMenu);
	this->supportMenu->Detach();
	this->drawMenu->Detach();
	this->relationMenu->Detach();
	this->editMenu->Detach();
	this->popupMenu->Detach();
	this->mainMenu->Detach();
}
Menu::Menu(const Menu& source){
	this->mainMenu = source.mainMenu;
	this->popupMenu = source.popupMenu;
	this->editMenu = source.editMenu;
	this->supportMenu = source.supportMenu;
}

MenuAction* Menu::MenuSelected( UINT parm_control_id) {
	if (this->menuAction != 0) {
		delete this->menuAction;
		this->menuAction = 0;
	}
	switch (parm_control_id) {
	case 110: this->menuAction = new ClassMenuAction; 
		break;
	case 111: this->menuAction = new MemoBoxMenuAction; 
		break;
	default: 
		break;
	}
	return this->menuAction;
}

Menu& Menu::operator=(const Menu& source) {
	if (this->mainMenu != NULL) {
		delete this->mainMenu;
	}

	if (this->popupMenu != NULL) {
		delete this->popupMenu;
	}

	if (this->editMenu != NULL) {
		delete this->editMenu;
	}

	if (this->supportMenu != NULL) {
		delete this->supportMenu;
	}
	this->mainMenu = source.mainMenu;
	this->popupMenu = source.popupMenu;
	this->editMenu = source.editMenu;
	this->supportMenu = source.supportMenu;

	return *this;
}

Menu::~Menu() {
	if (this->mainMenu != NULL) {
		delete this->mainMenu;
	}

	if (this->popupMenu != NULL) {
		delete this->popupMenu;
	}

	if (this->editMenu != NULL) {
		delete this->editMenu;
	}

	if (this->supportMenu != NULL) {
		delete this->supportMenu;
	}
	if (this->drawMenu != NULL) {
		delete this->drawMenu;
	}
	if (this->relationMenu != NULL) {
		delete this->relationMenu;
	}
}