#include "api.h"

CAPI::CAPI()
{
	hCurves = LoadLibrary(L"curves.dll");
	pCreate = (hCurves) ? (Curve_Create*)GetProcAddress(hCurves, "CreateCurve") : NULL;
}

CAPI::~CAPI()
{
	FreeLibrary(hCurves);
}

std::unique_ptr<DLL_Pure> CAPI::CreateCurve(eCurveType type)
{
	return std::unique_ptr<DLL_Pure>(pCreate(type));
}
