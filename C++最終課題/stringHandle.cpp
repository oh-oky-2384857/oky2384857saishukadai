#include <DxLib.h>
#include "stringHandle.h"

int stringHandle::size30 = 0;
int stringHandle::size40 = 0;

void stringHandle::MakeHandles() {
	size30 = CreateFontToHandle(NULL, 30, 7, -1);//文字ハンドル作成;
	size40 = CreateFontToHandle(NULL, 40, 7, -1);//文字ハンドル作成;
}