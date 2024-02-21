#pragma once

#include <Geode/Geode.hpp>
#include <Geode/utils/web.hpp>
#include <Geode/ui/TextInput.hpp>

using namespace geode::prelude;

#include "IconSelectLayer.h"

class RenameIconKitLayer : public CCLayerColor
{
    public:
        Icon* icon = nullptr;
        TextInput* inp = nullptr;

        virtual void keyBackClicked()
        {
            onClose(nullptr);
        }

        void onClose(CCObject*);

        bool init(Icon* icon)
        {
            if (!CCLayerColor::init())
                return false;

            this->setKeypadEnabled(true);
            this->icon = icon;

            auto panel = CCScale9Sprite::create("GJ_square01.png");
            panel->setContentSize(ccp(340, 170));
            this->addChildAtPosition(panel, Anchor::Center);

            auto title = CCLabelBMFont::create("Change Icon Kit Name", "goldFont.fnt");
            title->setScale(0.8f);
            this->addChildAtPosition(title, Anchor::Center, ccp(0, 70));

            auto menu = CCMenu::create();

            auto ok = CCMenuItemSpriteExtra::create(ButtonSprite::create("OK"), this, menu_selector(RenameIconKitLayer::onClose));
            menu->addChildAtPosition(ok, Anchor::Center, ccp(0, -63));

            inp = TextInput::create(260, "Icon Kit Name");
            inp->setString(icon->name);
            menu->addChildAtPosition(inp, Anchor::Center);

            this->addChild(menu);

            this->runAction(CCFadeTo::create(0.5f, 125));
            this->ignoreAnchorPointForPosition(true);

            CCTouchDispatcher::get()->addTargetedDelegate(this, -169, true);
            CCTouchDispatcher::get()->addTargetedDelegate(menu, -170, true);

            return true;
        }

        static RenameIconKitLayer* create(Icon* icon)
        {
            RenameIconKitLayer* pRet = new RenameIconKitLayer();
            if (pRet && pRet->init(icon)) {
                pRet->autorelease();
                return pRet;
            } else {
                delete pRet;
                return nullptr;
            }
        }

        static void addToScene(Icon* icon)
        {
            auto pRet = RenameIconKitLayer::create(icon);

            CCScene::get()->addChild(pRet, CCScene::get()->getHighestChildZ() + 1);
        }
};