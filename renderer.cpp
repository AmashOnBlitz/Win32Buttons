#include "renderer.hpp"

void Renderer::SetStage(HWND hWnd)
{
    if (mHWnd != hWnd) mHWnd = hWnd;
}

void Renderer::Render()
{
    if (!mGfx) mGfx = new Graphics(mHWnd);
    mGfx->Init();

    RECT rect;
    GetClientRect(mHWnd,&rect);
    int w = rect.right-rect.left;
    int h = rect.bottom-rect.top;
    int x = (int)(w/2);
    int y = (int)(h/2);

    mGfx->BeginDraw();
    mGfx->drawCircle(x,y,w/2,h/2,D2D1::ColorF::Crimson);
    mGfx->EndDraw();
}

HWND Renderer::getCurrentStage()
{
    return mHWnd;
}
