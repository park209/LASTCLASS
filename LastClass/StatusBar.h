//StatusBar.h

#ifndef _STATUSBAR_H
#define _STATUSBAR_H

#include <afxext.h>

class StatusBar {
public:
	StatusBar();
	StatusBar(const StatusBar& source);
	~StatusBar();

	CStatusBar& GetStatusBar() const;
private:
	CStatusBar cStatusBar;
};

inline CStatusBar& StatusBar::GetStatusBar() const {
	return const_cast<CStatusBar&>(this->cStatusBar);
}


#endif // !_STATUSBAR_H
