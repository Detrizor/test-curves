#include "api.h"

CAPI::CAPI()
{
	m_hCurves = LoadLibrary(L"curves.dll");
	m_pCreate = (m_hCurves) ? (CurveCreate*)GetProcAddress(m_hCurves, "CreateCurve") : NULL;
}

CAPI::~CAPI()
{
	FreeLibrary(m_hCurves);
}

Curve CAPI::CreateCurve() const
{
	return std::unique_ptr<DLL_Pure>(m_pCreate());
}
