#pragma once
#include "_vector3d.h"
#include <Windows.h>
#include <memory>
#include <vector>

// Abstract 'Pure' class for DLL interface
class __declspec(dllexport) DLL_Pure
{
public:
    virtual ~DLL_Pure() {}
    virtual LPCSTR Type() const = 0;
    virtual float R1() const = 0;
    virtual float R2() const = 0;
    virtual Fvector C_t(float t) const = 0;
    virtual Fvector dC_t(float t) const = 0;
};

extern "C" typedef __declspec(dllimport) DLL_Pure* __cdecl CurveCreate();

typedef std::unique_ptr<DLL_Pure> Curve;
typedef std::vector<Curve> Curves;

class __declspec(dllexport) CAPI
{
public:
    CAPI();
    ~CAPI();

private:
    HMODULE m_hCurves;
    CurveCreate* m_pCreate;

public:
    bool Loaded() const { return !!m_pCreate; }
    Curve CreateCurve() const;
};
