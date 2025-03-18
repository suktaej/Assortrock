#include "D1Widget.h"
#include "../Common/Image.h"
#include "../../Scene/Scene.h"
#include "../../Scene/SceneUIManager.h"
#include "../../Scene/SceneManager.h"
#include "../../Scene/SceneMain.h"
#include "../../Scene/SceneEditor.h"
#include "../../Device.h"
#include "../../GameManager.h"

CD1Widget::CD1Widget()
{
}

CD1Widget::~CD1Widget()
{
}

bool CD1Widget::Init()
{
    CUserWidget::Init();

    //FResolution RS = CDevice::GetInst()->GetResolution();
    //CSharedPtr<CImage>  Back = mScene->GetUIManager()->CreateWidget<CImage>("Back");

    //Back->SetTexture("StartBack", TEXT("Texture\\Back.png"));
    //Back->SetSize((float)RS.Width, (float)RS.Height);

    //AddWidget(Back);

    return true;
}
