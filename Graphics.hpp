#ifndef GRAPHICS_RCINWIN32_HEADER
#define GRAPHICS_RCINWIN32_HEADER

#include <d2d1.h>

class Graphics final {
public:
    Graphics(HWND hwnd);
    ~Graphics();
    bool Init();
    bool IsInit();
    void BeginDraw();
    void EndDraw(); 
    void Resize(UINT w, UINT h);
    void ClearScreen(float r, float g, float b, float a = 1.0f);
    void ClearScreen(D2D1::ColorF color);
    void drawCircle(float x, float y, float xradius, float yradius, float r, float g, float b, float a, float strokeW = 1.0f);
    void drawCircle(float x, float y, float xradius, float yradius, D2D1::ColorF color, float strokeW = 1.0f);

private: // funtions
    bool setInit(bool b);
    template <typename t>
    void ReleaseID2D1Object(t* object){
        if (object) object->Release();
        object = nullptr;
    }
private:
    bool misInit = false;
    HWND mHwnd;
    ID2D1Factory* mpfact;
    ID2D1HwndRenderTarget* mpRend;
    ID2D1SolidColorBrush* mpBrush;
};

#endif //!GRAPHICS_RCINWIN32_HEADER

