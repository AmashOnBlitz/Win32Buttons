#include "Graphics.hpp"

#define CHECK_HR_OK if (hr != S_OK) return setInit(false);

Graphics::Graphics(HWND hwnd) : mHwnd(hwnd);
{
}

Graphics::~Graphics()
{
    if (mpfact) mpfact->Release();
    if (mpRend) mpRend->Release();
    mpfact = nullptr;
    mpRend = nullptr;
}

Graphics &Graphics::Instance()
{
    static Graphics g;
    return g;
}

bool Graphics::Init()
{
    HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &mpfact);
    CHECK_HR_OK; 

    RECT rect;
    GetClientRect(mHwnd, &rect);
    hr = mpfact->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(mHwnd, D2D1::SizeU(rect.right - rect.left, rect.bottom - rect.top)),
            &mpRend
        );
    CHECK_HR_OK;

    return setInit(true);
}

bool Graphics::setInit(bool b)
{
    isInit = b;
    return b;
}

template <typename t>
void ReleaseID2D1Object(t& object){
    if (object) object->Release();
}