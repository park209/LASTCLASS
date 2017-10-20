//LastClass.cpp

#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "Menu.h"
#include "menuAction.h"
#include "Scroll.h"
#include "HistoryGraphic.h"
#include "StatusBar.h"
#include "ToolBar.h"
#include "PrintPreview.h"
#include "resource.h"
#include "ResizeVisitor.h"
#include "KnockKnock.h"
#include "Diagram.h"
#include <afxdlgs.h>
#include <afxext.h>
#include <afxstatusbar.h>
#include "resource.h"
#include <afxcmn.h>
using namespace std;

BEGIN_MESSAGE_MAP(LastClass, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
	ON_WM_SETFOCUS()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_KILLFOCUS()
	ON_WM_CLOSE()
	ON_COMMAND_RANGE(100, 125, OnMyMenu)
	ON_COMMAND_RANGE(40002, 40015, OnMyToolBar)
	ON_WM_SIZE()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

LastClass::LastClass() {
	this->classDiagramForm = NULL;
	this->menu = NULL;
	this->toolBar = NULL;
	this->statusBar = NULL;
	this->printPreview = NULL;
}

int LastClass::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CFrameWnd::OnCreate(lpCreateStruct); //코드재사용 오버라이딩 //상속에서
	CRect rect;
	this->GetClientRect(&rect);

	this->statusBar = new StatusBar;
	this->toolBar = new ToolBar;
	rect.top += 45;
	//rect.left += 60;
	//rect.right -= 60;
	rect.bottom -= 66;
	this->classDiagramForm = new ClassDiagramForm(this);
	this->classDiagramForm->Create(NULL, "classDiagramForm", WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL, rect, this, 100000);
	this->menu = new Menu(this);

	//this->toolBar->MakeToolBar(this->GetSafeHwnd());
	//this->toolBar->MakeAnotherToolBar(this->GetSafeHwnd());
	//this->statusBar->MakeStatusBar(this, this->GetSafeHwnd(), NULL, NULL, 5);

	return 0;
}

void LastClass::OnMyMenu(UINT parm_control_id) {

	if (parm_control_id == 104 || parm_control_id == 105) {

		ResizeVisitor visitor(this->classDiagramForm->zoomRate, 100);
		this->classDiagramForm->zoomRate = 100;
		this->classDiagramForm->SetMemoGab(20 * this->classDiagramForm->zoomRate / 100);
		this->classDiagramForm->SetGabX(8 * this->classDiagramForm->zoomRate / 100);
		this->classDiagramForm->SetGabY(4 * this->classDiagramForm->zoomRate / 100);
		this->classDiagramForm->SetCaretWidth(2 * this->classDiagramForm->zoomRate / 100);
		CDC memDC;
		this->classDiagramForm->diagram->Accept(visitor, &memDC);

		KnockKnock *knocking = new KnockKnock;
		knocking->Knocking(this->classDiagramForm);
		if (knocking != NULL) {
			delete knocking;
		}

		this->statusBar->DestroyStatus();
		this->statusBar->MakeStatusBar(this, this->GetSafeHwnd(), NULL, NULL, 5);

		SCROLLINFO vScinfo;
		SCROLLINFO hScinfo;

		this->classDiagramForm->GetScrollInfo(SB_VERT, &vScinfo);
		this->classDiagramForm->GetScrollInfo(SB_HORZ, &hScinfo);
		CRect rect;
		this->GetClientRect(&rect);
		vScinfo.nPage = rect.Height();
		hScinfo.nPage = rect.Width();

		vScinfo.nMax = 2000 * this->classDiagramForm->zoomRate / 100;
		hScinfo.nMax = 4000 * this->classDiagramForm->zoomRate / 100;

		if (vScinfo.nPos > vScinfo.nMax - (int)vScinfo.nPage) {
			vScinfo.nPos = vScinfo.nMax - (int)vScinfo.nPage;
		}
		if (hScinfo.nPos > hScinfo.nMax - (int)hScinfo.nPage) {
			hScinfo.nPos = hScinfo.nMax - (int)hScinfo.nPage;
		}
		this->classDiagramForm->SetScrollInfo(SB_VERT, &vScinfo);
		this->classDiagramForm->SetScrollInfo(SB_HORZ, &hScinfo);
	}
	MenuAction* menuAction = this->menu->MenuSelected(parm_control_id);
	if (menuAction != 0) {
		menuAction->MenuPress(this);
	}
}

void LastClass::OnKillFocus(CWnd *pNewWnd) {
	//CFrameWnd::OnKillFocus(pNewWnd);
}

void LastClass::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
}

void LastClass::OnSetFocus(CWnd* pOldWnd) {
	CFrameWnd::OnSetFocus(pOldWnd);
	CWnd::SetFocus();
	Invalidate(false);
}

void LastClass::OnSize(UINT nType, int cx, int cy) {
	//ModifyStyle(0, WS_CLIPCHILDREN);
	CFrameWnd::OnSize(nType, cx, cy);
	CRect rect;
	this->GetClientRect(&rect);
	if (this->classDiagramForm != NULL) {
		this->toolBar->DestroyToolBar();
		this->toolBar->MakeToolBar(this->GetSafeHwnd());
		this->toolBar->ChangeToolBarSize(&rect);
	}
	//this->toolBar->MakeAnotherToolBar(this->GetSafeHwnd());
	if (this->classDiagramForm != NULL) {
		this->statusBar->DestroyStatus();
		this->statusBar->MakeStatusBar(this, this->GetSafeHwnd(), NULL, NULL, 5);
	}
	//this->toolBar->ChangeAnotherToolBarSize(&rect);
	//this->statusBar->ChangeStatusBarSize(&rect);
	rect.top += 45;
	//rect.left += 60;
	//rect.right -= 60;
	rect.bottom -= 66;
	//this->classDiagramForm->MoveWindow(rect.left, rect.top, rect.right, rect.bottom, 1);
	if (this->classDiagramForm != NULL) {
		this->classDiagramForm->SetWindowPos(this, rect.left, rect.top, rect.right, rect.bottom, SWP_NOMOVE | SWP_NOZORDER);
		this->RedrawWindow();
		this->classDiagramForm->Invalidate(FALSE);
	}
	CRect rect1;
	this->GetClientRect(&rect1);
	rect1.top = rect1.bottom - 20;
	//rect1.right = rect1.left + 10;
	this->InvalidateRect(rect1);

	//ModifyStyle(WS_CLIPCHILDREN, 0);
}

BOOL LastClass::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {
	return false;
}

void LastClass::OnLButtonDown(UINT nFlags, CPoint point) {
	CFrameWnd::OnLButtonDown(nFlags, point);
}

void LastClass::OnLButtonDblClk(UINT nFlags, CPoint point) {
	CFrameWnd::OnLButtonDblClk(nFlags, point);
}

void LastClass::OnLButtonUp(UINT nFlags, CPoint point) {
	CFrameWnd::OnLButtonDown(nFlags, point);
}

void LastClass::OnMouseMove(UINT nFlags, CPoint point) {
	CFrameWnd::OnMouseMove(nFlags, point);
}
void LastClass::OnMyToolBar(UINT parm_control_id) {
	if (parm_control_id == 40011 || parm_control_id == 40012) {



		ResizeVisitor visitor(this->classDiagramForm->zoomRate, 100);
		this->classDiagramForm->zoomRate = 100;
		this->classDiagramForm->SetMemoGab(20 * this->classDiagramForm->zoomRate / 100);
		this->classDiagramForm->SetGabX(8 * this->classDiagramForm->zoomRate / 100);
		this->classDiagramForm->SetGabY(4 * this->classDiagramForm->zoomRate / 100);
		this->classDiagramForm->SetCaretWidth(2 * this->classDiagramForm->zoomRate / 100);
		CDC memDC;
		this->classDiagramForm->diagram->Accept(visitor, &memDC);

		KnockKnock *knocking = new KnockKnock;
		knocking->Knocking(this->classDiagramForm);
		if (knocking != NULL) {
			delete knocking;
		}




		this->statusBar->DestroyStatus();
		this->statusBar->MakeStatusBar(this, this->GetSafeHwnd(), NULL, NULL, 5);
		SCROLLINFO vScinfo;
		SCROLLINFO hScinfo;

		this->classDiagramForm->GetScrollInfo(SB_VERT, &vScinfo);
		this->classDiagramForm->GetScrollInfo(SB_HORZ, &hScinfo);
		CRect rect;
		this->GetClientRect(&rect);
		vScinfo.nPage = rect.Height();
		hScinfo.nPage = rect.Width();

		vScinfo.nMax = 2000 * this->classDiagramForm->zoomRate / 100;
		hScinfo.nMax = 4000 * this->classDiagramForm->zoomRate / 100;

		if (vScinfo.nPos > vScinfo.nMax - (int)vScinfo.nPage) {
			vScinfo.nPos = vScinfo.nMax - (int)vScinfo.nPage;
		}
		if (hScinfo.nPos > hScinfo.nMax - (int)hScinfo.nPage) {
			hScinfo.nPos = hScinfo.nMax - (int)hScinfo.nPage;
		}
		this->classDiagramForm->SetScrollInfo(SB_VERT, &vScinfo);
		this->classDiagramForm->SetScrollInfo(SB_HORZ, &hScinfo);
	}
	CClientDC dc(this);
	this->toolBar->ButtonSelected(parm_control_id, this, this->classDiagramForm, &dc);
}
void LastClass::OnClose() {
	//6.2. 다이어그램을 지운다.
	int messageBox = IDNO;
	INT_PTR int_ptr = IDOK;
	if (this->classDiagramForm->historyGraphic->undoGraphicArray->GetLength() != 0 
		|| this->classDiagramForm->historyGraphic->redoGraphicArray->GetLength() != 0) {
		if (this->classDiagramForm->fileName == "") {
			messageBox = MessageBox(_T("변경 내용을 제목 없음에 저장하시겠습니까?"), "ClassDiagram", MB_YESNOCANCEL);

			if (messageBox == IDYES) {
				CFileDialog  dlgFile(false, "txt", "*", OFN_CREATEPROMPT | OFN_OVERWRITEPROMPT, "텍스트 문서(*.txt)");
				int_ptr = dlgFile.DoModal();
				if (int_ptr == IDOK) {
					ResizeVisitor resizeVisitor1(this->classDiagramForm->zoomRate, 100);
					CDC dc;
					this->classDiagramForm->diagram->Accept(resizeVisitor1, &dc);

					this->classDiagramForm->diagram->Accept(resizeVisitor1, &dc);
					this->classDiagramForm->fileName = dlgFile.GetPathName();
					this->classDiagramForm->Save();
				}
				//else {
				//return;  //보류
				//}
			}
		}
		else {
			CString object;
			object = "변경내용을 ";
			object.Append(this->classDiagramForm->fileName);
			object.Append("에 저장하시겠습니까?");
			messageBox = MessageBox(object, "ClassDiagram", MB_YESNOCANCEL);
			if (messageBox == IDYES) {
				ResizeVisitor resizeVisitor1(this->classDiagramForm->zoomRate, 100);
				CDC dc;
				this->classDiagramForm->diagram->Accept(resizeVisitor1, &dc);

				this->classDiagramForm->Save();
			}
		}
	}
	//6.2. 다이어그램을 지운다.
	if (messageBox != IDCANCEL && int_ptr == IDOK) {//== IDYES || messageBox == IDNO ) {
		if (this->classDiagramForm != NULL) {
			this->classDiagramForm->OnClose();
			delete this->classDiagramForm;
			this->classDiagramForm = NULL;
		}
		if (this->menu != NULL) {
			delete this->menu;
			this->menu = NULL;
		}
		if (this->toolBar != NULL) {
			this->toolBar->DestroyToolBar();
			delete this->toolBar;
			this->toolBar = NULL;
		}
		if (this->statusBar != NULL) {
			this->statusBar->DestroyStatus();
			delete this->statusBar;
			this->statusBar = NULL;
		}
		if (this->printPreview != NULL) {
			this->printPreview->OnClose();
			this->printPreview = NULL;
		}
		CFrameWnd::OnClose(); // 오버라이`딩 코드재사용
	}
}