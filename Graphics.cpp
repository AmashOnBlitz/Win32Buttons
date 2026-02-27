#include "Graphics.hpp"

Graphics &Graphics::Instance()
{
    static Graphics g;
    return g;
}