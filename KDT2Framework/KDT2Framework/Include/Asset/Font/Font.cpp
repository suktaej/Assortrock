#include "Font.h"

CFont::CFont()
{
}

CFont::~CFont()
{
    SAFE_RELEASE(mFormat);
}

bool CFont::LoadFont(IDWriteFactory5* Factory, const TCHAR* FontName, 
    int Weight, float FontSize, const TCHAR* LocalName, int Stretch)
{
    mFactory = Factory;

    if (FAILED(mFactory->CreateTextFormat(FontName, nullptr,
        (DWRITE_FONT_WEIGHT)Weight, DWRITE_FONT_STYLE_NORMAL,
        (DWRITE_FONT_STRETCH)Stretch, FontSize, LocalName,
        (IDWriteTextFormat**)&mFormat)))
        return false;

    return true;
}
