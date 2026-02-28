#ifndef BTN_RENDERER_HEADER
#define BTN_RENDERER_HEADER

#include <Windows.h>
#include "Graphics.hpp"

class Renderer{
public:
    Renderer() : mHWnd(nullptr), mGfx(nullptr) {}
    ~Renderer() { delete mGfx; }
    virtual void SetStage(HWND hWnd);
    virtual void Render();
    HWND getCurrentStage();
private:
HWND mHWnd;
Graphics* mGfx;
};

#endif //!BTN_RENDERER_HEADER