#include "FontSettingMenuaction.h"
#include "LastClass.h"
#include "MouseLButton.h"
#include <afxdlgs.h>
FontSettingMenuaction::FontSettingMenuaction() {
}
FontSettingMenuaction::~FontSettingMenuaction() {
}
void FontSettingMenuaction::MenuPress(LastClass* lastClass) {
	CFontDialog fontDialog;
	fontDialog.DoModal();
}