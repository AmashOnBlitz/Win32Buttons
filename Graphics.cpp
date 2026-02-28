#include "Graphics.hpp"

#define CHECK_HR_OK if (FAILED(hr)) return setInit(false);
#define GUARD_NO_INIT if (!misInit) return;

#pragma region Initializers 

Graphics::Graphics(HWND hwnd)
    : mHwnd(hwnd),
      mpfact(nullptr),
      mpRend(nullptr),
      mpBrush(nullptr),
      misInit(false)
{
}

Graphics::~Graphics()
{
    ReleaseID2D1Object(mpfact);
    ReleaseID2D1Object(mpRend);
}

bool Graphics::Init()
{
    if (misInit) return true;
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

    hr = mpRend->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black),&mpBrush);
    CHECK_HR_OK;

    return setInit(true);
}

bool Graphics::IsInit()
{
    return misInit;
}

#pragma region Draw Functions

void Graphics::BeginDraw()
{
    GUARD_NO_INIT;
    mpRend->BeginDraw(); 
    mpRend->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED);
    mpRend->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_CLEARTYPE); 
}

void Graphics::EndDraw()
{
    GUARD_NO_INIT;
    mpRend->EndDraw();
}

void Graphics::Resize(UINT w, UINT h)
{
    GUARD_NO_INIT;
    if (mpRend) mpRend->Resize(D2D1::SizeU(w, h));
}

void Graphics::ClearScreen(float r, float g, float b, float a)
{
    GUARD_NO_INIT;
    mpRend->Clear(D2D1::ColorF(r, g, b, a));
}

void Graphics::ClearScreen(D2D1::ColorF color)
{
    GUARD_NO_INIT;
    mpRend->Clear(D2D1::ColorF(color));
}

void Graphics::drawCircle(float x, float y, float radiusX, float radiusY, float r, float g, float b, float a, float strokeW)
{
    GUARD_NO_INIT;
    mpBrush->SetColor(D2D1::ColorF(r,g,b,a));
    mpRend->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x,y),radiusX,radiusY),mpBrush,strokeW);
}

void Graphics::drawCircle(float x, float y, float radiusX, float radiusY, D2D1::ColorF color, float strokeW)
{
    GUARD_NO_INIT;
    mpBrush->SetColor(D2D1::ColorF(color));
    mpRend->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x,y),radiusX,radiusY),mpBrush,strokeW);
}

#pragma region Private Functions

bool Graphics::setInit(bool b)
{
    misInit = b;
    return b;
}
