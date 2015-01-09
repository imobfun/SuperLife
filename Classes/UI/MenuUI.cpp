//
//  MenuUI.cpp
//  SuperLife
//
//  Created by wang haibo on 14-8-13.
//
//

#include "MenuUI.h"
#include "SceneFactory.h"
#include "UIMgr.h"
#include "CommonUtility.h"
USING_NS_CC;

// 构造函数
MenuUI::MenuUI(BaseScene* owner)
{
    m_pOwnerScene = owner;
    m_pFreeModeBtn = nullptr;
    m_pMissionModeBtn = nullptr;
    m_pHelpBtn  = nullptr;
}
// 析构函数
MenuUI::~MenuUI()
{
}
// 加载文件
void MenuUI::loadUI(const std::string& file)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Color3B color = SceneFactory::getInstance()->getSceneColor();
    auto labelTitle = Label::createWithTTF(CommonUtility::getLocalString("MainTitle"), CommonUtility::getLocalString("MainFont"), 120);
    labelTitle->setColor(color);
    labelTitle->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - labelTitle->getContentSize().height));
    this->addChild(labelTitle);
    
    m_pMissionModeBtn = ui::Button::create("btnLBN.png", "btnLBD.png");
    m_pMissionModeBtn->setPosition(Vec2(origin.x + visibleSize.width/2,340));
    m_pMissionModeBtn->addTouchEventListener(CC_CALLBACK_2(MenuUI::pressMissionModeBtn, this));
    m_pMissionModeBtn->setTitleFontName(CommonUtility::getLocalString("CommonFont"));
    m_pMissionModeBtn->setTitleColor(color);
    m_pMissionModeBtn->setTitleFontSize(24);
    m_pMissionModeBtn->setTitleText(CommonUtility::getLocalString("MissionMode"));
    m_pMissionModeBtn->setColor(color);
    this->addChild(m_pMissionModeBtn);
    
    m_pFreeModeBtn = ui::Button::create("btnLBN.png", "btnLBD.png");
    m_pFreeModeBtn->setPosition(Vec2(origin.x + visibleSize.width/2,260));
    m_pFreeModeBtn->addTouchEventListener(CC_CALLBACK_2(MenuUI::pressFreeModeBtn, this));
    m_pFreeModeBtn->setTitleFontName(CommonUtility::getLocalString("CommonFont"));
    m_pFreeModeBtn->setTitleColor(color);
    m_pFreeModeBtn->setTitleFontSize(24);
    m_pFreeModeBtn->setTitleText(CommonUtility::getLocalString("FreeMode"));
    m_pFreeModeBtn->setColor(color);
    this->addChild(m_pFreeModeBtn);

#if CC_TARGET_PLATFORM == CC_PLATFORM_MAC
    m_pEditorBtn = ui::Button::create("btnLBN.png", "btnLBD.png");
    m_pEditorBtn->setPosition(Vec2(origin.x + visibleSize.width/2,180));
    m_pEditorBtn->addTouchEventListener(CC_CALLBACK_2(MenuUI::pressEditorBtn, this));
    m_pEditorBtn->setTitleFontName(CommonUtility::getLocalString("CommonFont"));
    m_pEditorBtn->setTitleColor(color);
    m_pEditorBtn->setTitleFontSize(24);
    m_pEditorBtn->setTitleText(CommonUtility::getLocalString("EditorMode"));
    m_pEditorBtn->setColor(color);
    this->addChild(m_pEditorBtn);
#else
    m_pShopBtn = ui::Button::create("btnLBN.png", "btnLBD.png");
    m_pShopBtn->setPosition(Vec2(origin.x + visibleSize.width/2,180));
    m_pShopBtn->addTouchEventListener(CC_CALLBACK_2(MenuUI::pressShopBtn, this));
    m_pShopBtn->setTitleFontName(CommonUtility::getLocalString("CommonFont"));
    m_pShopBtn->setTitleColor(color);
    m_pShopBtn->setTitleFontSize(24);
    m_pShopBtn->setTitleText(CommonUtility::getLocalString("Shop"));
    m_pShopBtn->setColor(color);
    this->addChild(m_pShopBtn);
#endif
    
    m_pHelpBtn = ui::Button::create("btnLBN.png", "btnLBD.png");
    m_pHelpBtn->setPosition(Vec2(origin.x + visibleSize.width/2,100));
    m_pHelpBtn->addTouchEventListener(CC_CALLBACK_2(MenuUI::pressHelpBtn, this));
    m_pHelpBtn->setTitleFontName(CommonUtility::getLocalString("CommonFont"));
    m_pHelpBtn->setTitleColor(color);
    m_pHelpBtn->setTitleFontSize(24);
    m_pHelpBtn->setTitleText(CommonUtility::getLocalString("HelpInfo"));
    m_pHelpBtn->setColor(color);
    this->addChild(m_pHelpBtn);
    
    //auto labelMadeBy = Label::createWithTTF("Made by Irenicus", CommonUtility::getLocalString("SecondFont"), 10);
    //labelMadeBy->setColor(color);
    //labelMadeBy->setPosition(Vec2(860,10));
    //this->addChild(labelMadeBy);
}

// 点击任务模式按钮
void MenuUI::pressMissionModeBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        BaseScene* missionListScene = SceneFactory::getInstance()->createSceneByID(SCENE_MISSION_LIST);
        Director::getInstance()->replaceScene(missionListScene);
    }
}
// 点击自由模式按钮
void MenuUI::pressFreeModeBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        BaseScene* mainScene = SceneFactory::getInstance()->createSceneByID(SCENE_MAIN);
        Director::getInstance()->replaceScene(mainScene);
    }
}
// 点击闪电按钮
void MenuUI::pressShopBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        BaseScene* shopScene = SceneFactory::getInstance()->createSceneByID(SCENE_SHOP);
        Director::getInstance()->replaceScene(shopScene);
    }
}
// 点击编辑模式按钮
void MenuUI::pressEditorBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        BaseScene* editorScene = SceneFactory::getInstance()->createSceneByID(SCENE_EDITOR);
        Director::getInstance()->replaceScene(editorScene);
    }
}
// 点击帮助说明按钮
void MenuUI::pressHelpBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        BaseScene* helpInfoScene = SceneFactory::getInstance()->createSceneByID(SCENE_HELPINFO);
        Director::getInstance()->replaceScene(helpInfoScene);
    }
}