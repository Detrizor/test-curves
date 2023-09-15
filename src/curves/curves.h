#pragma once
#include "..\gui\api.h"

class CCircle : public DLL_Pure
{
public:
	CCircle();
	~CCircle() override {}

private:
	float m_fRadius;

public:
	LPCSTR Type() const override { return "Circle"; }
	float R1() const override { return m_fRadius; }
	float R2() const override { return -1.f; }
	Fvector C_t(float t) const override;
	Fvector dC_t(float t) const override;
};

class CEllipse : public DLL_Pure
{
public:
	CEllipse();
	~CEllipse() override {}

private:
	float m_fRadiusX, m_fRadiusY;

public:
	LPCSTR Type() const override { return "Ellipse"; }
	float R1() const { return m_fRadiusX; }
	float R2() const { return m_fRadiusY; }
	Fvector C_t(float t) const override;
	Fvector dC_t(float t) const override;
};

class CHelix : public DLL_Pure
{
public:
	CHelix();
	~CHelix() override {}

private:
	float m_fRadius, m_fStep;

public:
	LPCSTR Type() const override { return "Helix"; }
	float R1() const { return m_fRadius; }
	float R2() const { return m_fStep; }
	Fvector C_t(float t) const override;
	Fvector dC_t(float t) const override;
};
