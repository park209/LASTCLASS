//CMemoryDC.h

#ifndef _CMEMORYDC_H
#define _CMEMORYDC_H

#include <afxwin.h>
#include <string>

class CMemoryDC :public CDC {
private:
  //CBitmap    m_bitmap;             // Offscreen bitmap (실제 화면에 나타낼 비트맵)
  //CBitmap*  m_oldBitmap;         // bitmap originally found in CMemDC
  //CDC*        m_pDC;                // Saves CDC passed in constructor
  //CRect       m_rect;                 // Rectangle of drawing area.
  //BOOL       m_bMemDC;         // TRUE if CDC really is a Memory DC.
	CDC*		cdc;
	LOGFONT*	logFont;
	RECT*		rt;
public:
	CMemoryDC(CDC *cdc, LOGFONT *logFont, RECT *rt = 0) {
		this->cdc = 0;
		this->logFont = 0;
		if (rt == 0) {
			CFont cFont;
			cFont.CreateFontIndirect(logFont);
			cdc->SelectObject(&cFont);// 폰트 시작
		}
	}
	~CMemoryDC() {

	}
   //CMemoryDC(CDC* pDC, const CRect* pRect = NULL) : CDC()
   //{
   //   ASSERT(pDC != NULL);

   //   // Some initialization
   //   m_pDC = pDC;
   //   m_oldBitmap = NULL;
   //   m_bMemDC = !pDC->IsPrinting();    // 프린팅의 경우, FALSE 로 처리

   //                             // Get the rectangle to draw
   //   if (pRect == NULL)
   //   {
   //      pDC->GetClipBox(&m_rect);     // 메모리 DC 로 처리할 다시그릴 영역을 얻습니다.
   //   }
   //   else
   //   {
   //      m_rect = *pRect;                     // 전달 받은 매개변수 영역을 더블 버퍼링합니다.
   //   }

   //   if (m_bMemDC)
   //   {
   //      // Create a Memory DC, 메모리 DC 를 만들고, 영역을 논리 좌표에서 Device 좌표로 변경합니다.
   //      CreateCompatibleDC(pDC);
   //      pDC->LPtoDP(&m_rect);

   //      // 메모리 비트맵을 화면 표시할 영역으로 만들고, 이를 선택합니다.
   //      m_bitmap.CreateCompatibleBitmap(pDC, m_rect.Width(), m_rect.Height());
   //      m_oldBitmap = SelectObject(&m_bitmap);

   //      // 아래 부분들이 잘 처리한 경우입니다. 즉, 생성자로 전달 받은 CDC 의 매핑모드와,
   //      // 화면 비율, 그리고, 원점을 전달 받은 매개변수 그대로 적용하는 것이죠.
   //      SetMapMode(pDC->GetMapMode());

   //      // 실제 물리적 윈도우 크기
   //      SetWindowExt(pDC->GetWindowExt());
   //      // 물리적 위도우에 대한 실제 보이는 영역의 크기 비율
   //      SetViewportExt(pDC->GetViewportExt());

   //      // Device 좌표를 논리 좌표로 변경하고, 원점을 논리좌표로 화면을 나타낼 영역의 좌측 상단으로 지정한다.
   //      pDC->DPtoLP(&m_rect);
   //      SetWindowOrg(m_rect.left, m_rect.top);
   //   }
   //   else
   //   {
   //      // Make a copy of the relevent parts of the current 
   //      // DC for printing
   //      // 프린터 출력의 경우
   //      m_bPrinting = pDC->m_bPrinting;
   //      m_hDC = pDC->m_hDC;
   //      m_hAttribDC = pDC->m_hAttribDC;
   //   }

   //   // Fill background, 배경을 전달 받은 매개변수 DC 의 배경색으로 채운다.
   //   FillSolidRect(m_rect, pDC->GetBkColor());
   //}

   //~CMemoryDC()
   //{
   //   if (m_bMemDC)
   //   {
   //      // Copy the offscreen bitmap ont　　　　　o the screen. 화면을 만든 비트맵으로 나타낸다.
   //      m_pDC->BitBlt(m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(), this, m_rect.left, m_rect.top, SRCCOPY);

   //      // Swap back the original bitmap. 이전 비트맵으로 복귀 시킨다.
   //      SelectObject(m_oldBitmap);
   //   }
   //   else
   //   {
   //      // All we need to do is replace the DC with an illegal
   //      // value, this keeps us from accidentally deleting the 
   //      // handles associated with the CDC that was passed to 
   //      // the constructor.              
   //      m_hDC = m_hAttribDC = NULL;
   //   }
   //}

   // Allow usage as a pointer    
   CMemoryDC* operator->() {
      return this;
   }

   // Allow usage as a pointer    
   operator CMemoryDC*() {
      return this;
   }
};

#endif // !_CMEMORYDC_H