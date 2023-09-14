#include "curves.h"

extern "C" __declspec(dllexport) DLL_Pure* CreateCurve()
{
	DLL_Pure* res = NULL;

	switch (rand() % 3)
	{
	case 0:
		res = new CCircle();
		break;
	case 1:
		res = new CEllipse();
		break;
	case 2:
		res = new CHelix();
		break;
	}

	return res;
}
