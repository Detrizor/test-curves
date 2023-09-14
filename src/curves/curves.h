#pragma once
#include "..\gui\api.h"

class CCircle : public DLL_Pure
{
	LPCSTR Type() const override { return "Circle"; }
};

class CEllipse : public DLL_Pure
{
	LPCSTR Type() const override { return "Ellipse"; }
};

class CHelix : public DLL_Pure
{
	LPCSTR Type() const override { return "Helix"; }
};
