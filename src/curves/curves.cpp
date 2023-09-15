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

////////////////////////////////////////////////////////////////////////////////////

CCircle::CCircle()
{
	m_fRadius = float(rand() % 1000) / 10.f;
}

Fvector CCircle::C_t(float t) const
{
	return {
		m_fRadius * _cos(t),
		m_fRadius * _sin(t),
		0.f
	};
}

Fvector CCircle::dC_t(float t) const
{
	return {
		m_fRadius * (-_sin(t)),
		m_fRadius * _cos(t),
		0.f
	};
}

////////////////////////////////////////////////////////////////////////////////////

CEllipse::CEllipse()
{
	m_fRadiusX = float(rand() % 1000) / 10.f;
	m_fRadiusY = float(rand() % 1000) / 10.f;
}

Fvector CEllipse::C_t(float t) const
{
	return {
		m_fRadiusX * _cos(t),
		m_fRadiusY * _sin(t),
		0.f
	};
}

Fvector CEllipse::dC_t(float t) const
{
	return {
		m_fRadiusX * (-_sin(t)),
		m_fRadiusY * _cos(t),
		0.f
	};
}

////////////////////////////////////////////////////////////////////////////////////

CHelix::CHelix()
{
	m_fRadius = float(rand() % 1000) / 10.f;
	m_fStep = float(rand() % 1000) / 10.f;
}

Fvector CHelix::C_t(float t) const
{
	return {
		m_fRadius * _cos(t),
		m_fRadius * _sin(t),
		m_fStep * t / PI_MUL_2
	};
}

Fvector CHelix::dC_t(float t) const
{
	return {
		m_fRadius * (-_sin(t)),
		m_fRadius * _cos(t),
		m_fStep / PI_MUL_2
	};
}
