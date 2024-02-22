#pragma once

#include <Geode/Geode.hpp>
#include <Geode/utils/web.hpp>
#include <Geode/ui/TextInput.hpp>

using namespace geode::prelude;

#include "IconSelectLayer.h"

class SetSecretLayer : public CCLayerColor
{
    public:
        TextInput* inp = nullptr;

        virtual void keyBackClicked()
        {
            onClose(nullptr);
        }

        void onClose(CCObject*)
        {
            Mod::get()->setSavedValue<std::string>("_devsecret", inp->getString());

            CCTouchDispatcher::get()->removeDelegate(this);

            this->removeFromParent();
        }

        bool init()
        {
            if (!CCLayerColor::init())
                return false;

            this->setKeypadEnabled(true);

            auto panel = CCScale9Sprite::create("GJ_square01.png");
            panel->setContentSize(ccp(340, 170));
            this->addChildAtPosition(panel, Anchor::Center);

            auto title = CCLabelBMFont::create("DEV: Set Secret", "bigFont.fnt");
            title->setScale(0.8f);
            this->addChildAtPosition(title, Anchor::Center, ccp(0, 70));

            auto menu = CCMenu::create();

            auto ok = CCMenuItemSpriteExtra::create(ButtonSprite::create("OK"), this, menu_selector(SetSecretLayer::onClose));
            menu->addChildAtPosition(ok, Anchor::Center, ccp(0, -63));

            inp = TextInput::create(260, "Secret");
            inp->setString(Mod::get()->getSavedValue<std::string>("_devsecret"));
            inp->setCommonFilter(CommonFilter::Any);
            menu->addChildAtPosition(inp, Anchor::Center);

            this->addChild(menu);

            this->runAction(CCFadeTo::create(0.5f, 125));
            this->ignoreAnchorPointForPosition(true);

            CCTouchDispatcher::get()->addTargetedDelegate(this, -169, true);
            CCTouchDispatcher::get()->addTargetedDelegate(menu, -170, true);

            return true;
        }

        static SetSecretLayer* create()
        {
            SetSecretLayer* pRet = new SetSecretLayer();
            if (pRet && pRet->init()) {
                pRet->autorelease();
                return pRet;
            } else {
                delete pRet;
                return nullptr;
            }
        }

        static void addToScene()
        {
            auto pRet = SetSecretLayer::create();

            CCScene::get()->addChild(pRet, CCScene::get()->getHighestChildZ() + 1);
        }
};