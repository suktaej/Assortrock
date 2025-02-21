#include "TextBlock.h"
#include "../../Scene/Scene.h"
#include "../../Scene/SceneAssetManager.h"
#include "../../Asset/AssetManager.h"
#include "../../Asset/Font/Font.h"
#include "../../Asset/Font/FontManager.h"
#include "../../Device.h"

CTextBlock::CTextBlock()
{
}

CTextBlock::~CTextBlock()
{
    SAFE_RELEASE(mLayout);
}

void CTextBlock::SetFont(const std::string& FontName)
{
    if (mScene)
        mFont = mScene->GetAssetManager()->FindFont(FontName);

    else
        mFont = CAssetManager::GetInst()->GetFontManager()->FindFont(FontName);

    CreateTextLayout();
}

void CTextBlock::SetText(const TCHAR* Text)
{
    mText = Text;

    CreateTextLayout();
}

void CTextBlock::SetTextFromInt(int Number)
{
    mText = std::to_wstring(Number);

    CreateTextLayout();
}

void CTextBlock::SetTextFromFloat(float Number)
{
    mText = std::to_wstring(Number);

    CreateTextLayout();
}

void CTextBlock::AddText(const TCHAR* Text)
{
    mText += Text;

    CreateTextLayout();
}

void CTextBlock::AddTextFromInt(int Number)
{
    mText += std::to_wstring(Number);

    CreateTextLayout();
}

void CTextBlock::AddTextFromFloat(float Number)
{
    mText += std::to_wstring(Number);

    CreateTextLayout();
}

void CTextBlock::PopBack()
{
    mText.pop_back();

    CreateTextLayout();
}

void CTextBlock::ClearText()
{
    mText.clear();

    CreateTextLayout();
}

void CTextBlock::EnableTransparency(bool Transparency)
{
    mTransparency = Transparency;
}

void CTextBlock::SetTextColor(unsigned char r, unsigned char g, 
    unsigned char b, unsigned char a)
{
    mTextColor = CAssetManager::GetInst()->GetFontManager()->FindFontColor(r, g, b, a);
}

void CTextBlock::SetTextColor(const FVector4D& Color)
{
    mTextColor = CAssetManager::GetInst()->GetFontManager()->FindFontColor(Color);
}

void CTextBlock::SetOpacity(float Opacity)
{
    mOpacity = Opacity;
}

void CTextBlock::SetFontSize(float Size)
{
    mFontSize = Size;

    if (!mLayout)
        return;

    DWRITE_TEXT_RANGE   Range = {};
    Range.startPosition = 0;
    Range.length = (UINT32)mText.length();

    mLayout->SetFontSize(mFontSize, Range);
}

void CTextBlock::SetAlignH(ETextAlignH Align)
{
    mAlignH = Align;

    if (!mLayout)
        return;

    switch (mAlignH)
    {
    case ETextAlignH::Left:
        mLayout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
        break;
    case ETextAlignH::Center:
        mLayout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
        break;
    case ETextAlignH::Right:
        mLayout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
        break;
    }
}

void CTextBlock::SetAlignV(ETextAlignV Align)
{
    mAlignV = Align;

    if (!mLayout)
        return;

    switch (mAlignV)
    {
    case ETextAlignV::Top:
        mLayout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
        break;
    case ETextAlignV::Middle:
        mLayout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
        break;
    case ETextAlignV::Bottom:
        mLayout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
        break;
    }
}

void CTextBlock::CreateTextLayout()
{
    SAFE_RELEASE(mLayout);

    mLayout = mFont->CreateLayout(mText.c_str(), (int)mText.length(),
        mSize.x, mSize.y);

    if (!mLayout)
        return;

    DWRITE_TEXT_RANGE   Range = {};
    Range.startPosition = 0;
    Range.length = (UINT32)mText.length();

    mLayout->SetFontSize(mFontSize, Range);

    switch (mAlignH)
    {
    case ETextAlignH::Left:
        mLayout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
        break;
    case ETextAlignH::Center:
        mLayout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
        break;
    case ETextAlignH::Right:
        mLayout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
        break;
    }

    switch (mAlignV)
    {
    case ETextAlignV::Top:
        mLayout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
        break;
    case ETextAlignV::Middle:
        mLayout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
        break;
    case ETextAlignV::Bottom:
        mLayout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
        break;
    }
}

bool CTextBlock::Init()
{
    CWidget::Init();

    mTarget = CDevice::GetInst()->Get2DTarget();

    SetFont("Default");
    SetTextColor(FVector4D::Black);

    CreateTextLayout();

    return true;
}

void CTextBlock::Update(float DeltaTime)
{
    CWidget::Update(DeltaTime);
}

void CTextBlock::Render()
{
    CWidget::Render();

    mTarget->BeginDraw();

    FResolution RS = CDevice::GetInst()->GetResolution();

    D2D1_POINT_2F   Point;

    Point.x = mPos.x;
    Point.y = RS.Height - mPos.y - mSize.y;
    //Point.y = mPos.y;

    if (mTransparency)
        mTextColor->SetOpacity(mOpacity);

    else
        mTextColor->SetOpacity(1.f);

    mTarget->DrawTextLayout(Point, mLayout, mTextColor,
        D2D1_DRAW_TEXT_OPTIONS_NONE);

    mTarget->EndDraw();
}

bool CTextBlock::CollisionMouse(CWidget** Result, 
    const FVector2D& MousePos)
{
    return false;
}
