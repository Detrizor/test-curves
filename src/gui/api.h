#pragma once
#include <Windows.h>
#include <memory>

enum eCurveType;

// Abstract 'Pure' class for DLL interface
class __declspec(dllexport) DLL_Pure
{
public:
    DLL_Pure(eCurveType t) { type = t; }

private:
    eCurveType type;
};

extern "C" typedef __declspec(dllimport) DLL_Pure* __cdecl Curve_Create(eCurveType t);

class __declspec(dllexport) CAPI
{
public:
    CAPI();
    ~CAPI();

private:
    HMODULE hCurves;
    Curve_Create* pCreate;

public:
    bool Loaded() { return !!pCreate; }
    std::unique_ptr<DLL_Pure> CreateCurve(eCurveType type);
};
