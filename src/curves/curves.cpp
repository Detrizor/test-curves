#include "..\gui\api.h"
#include "curves.h"

extern "C" __declspec(dllexport) DLL_Pure* CreateCurve(eCurveType t)
{
	DLL_Pure* res = new DLL_Pure(t);

	return res;
}
