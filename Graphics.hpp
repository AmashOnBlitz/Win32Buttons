#ifndef GRAPHICS_RCINWIN32_HEADER
#define GRAPHICS_RCINWIN32_HEADER

#include <d2d1.h>

class Graphics final {
public:
    Graphics(HWND hwnd);
    ~Graphics();
    Graphics& Instance();
    bool Init();

private: // funtions
    bool setInit(bool b);
    template <typename t>
    void ReleaseID2D1Object(t& object);
private:
    bool isInit = false;
    HWND mHwnd;
    ID2D1Factory* mpfact;
    ID2D1RenderTarget* mpRend;
};

#endif //!GRAPHICS_RCINWIN32_HEADER

