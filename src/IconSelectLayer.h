#pragma once

#include <Geode/Geode.hpp>
#include <Geode/utils/web.hpp>

using namespace geode::prelude;

#include "OnlineIconsLayer.h"
#include "RenameIconKitLayer.h"
#include "Icon.h"

class IconCell : public CCLayerColor
{
    public:

        Icon* icon;

        SimplePlayer* createSprite(int id, int type)
        {
            auto plr = SimplePlayer::create(id);
            plr->updatePlayerFrame(id, as<IconType>(type));

            plr->setColor(GameManager::get()->colorForIdx(icon->colour1));
            plr->setSecondColor(GameManager::get()->colorForIdx(icon->colour2));

            if (icon->glow)
                plr->setGlowOutline(GameManager::get()->colorForIdx(icon->colour3));

            return plr;
        }

        void onUp(CCObject* sender);
        void onDown(CCObject* sender);

        void onUse(CCObject* sender);

        void onTrash(CCObject* sender);

        void onShare(CCObject* sender);

        void onRename(CCObject* sender)
        {
            auto icn = as<Icon*>(as<CCNode*>(sender)->getUserData());

            RenameIconKitLayer::addToScene(icn);
        }

        bool init(Icon* icon, int i, bool isLast)
        {
            if (!CCLayerColor::init())
                return false;

            this->icon = icon;

            if (i % 2 == 0)
                this->setOpacity(50);
            else
                this->setOpacity(100);

            this->setContentSize(ccp(350, 45));
            this->setAnchorPoint(ccp(0, 0));

            auto name = CCLabelBMFont::create((icon->name.size() != 0 ? icon->name.c_str() : "Unnamed Kit"), "bigFont.fnt");
            name->setAnchorPoint(ccp(0, 1));
            this->addChildAtPosition(name, Anchor::TopLeft, ccp(3, 0));
            name->limitLabelWidth(300, 0.45f, 0.1f);

            auto layoutIcons = CCMenu::create();
            layoutIcons->setContentSize(ccp(6969, 0));
            layoutIcons->setAnchorPoint(ccp(0, 0.5f));

            layoutIcons->addChild(createSprite(icon->cube, 0));
            layoutIcons->addChild(createSprite(icon->ship, 1));
            layoutIcons->addChild(createSprite(icon->ball, 2));
            layoutIcons->addChild(createSprite(icon->ufo, 3));
            layoutIcons->addChild(createSprite(icon->wave, 4));
            layoutIcons->addChild(createSprite(icon->robot, 5));
            layoutIcons->addChild(createSprite(icon->spider, 6));
            layoutIcons->addChild(createSprite(icon->swing, 7));
            layoutIcons->addChild(createSprite(icon->jetpack, 8));

            layoutIcons->setLayout(RowLayout::create()->setAutoScale(false)->setAxisAlignment(AxisAlignment::Start)->setGap(40));
            layoutIcons->setScale(0.7f);

            auto btns = CCMenu::create();
            btns->setScale(0.245f);
            btns->setContentSize(ccp(0, 0));

            auto use = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_selectSongBtn_001.png"), this, menu_selector(IconCell::onUse));
            use->setUserData(this);
            btns->addChildAtPosition(use, Anchor::Center, ccp(45, -45));

            auto share = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_shareBtn_001.png"), this, menu_selector(IconCell::onShare));
            share->setUserData(this);
            btns->addChildAtPosition(share, Anchor::Center, ccp(45, 45));

            use->m_baseScale = share->getContentSize().width / use->getContentSize().width;
            use->setScale(use->m_baseScale);

            auto trash = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_trashBtn_001.png"), this, menu_selector(IconCell::onTrash));
            trash->setTag(i);
            btns->addChildAtPosition(trash, Anchor::Center, ccp(-45, -45));

            auto rename = CCMenuItemSpriteExtra::create(CircleButtonSprite::create(CCSprite::createWithSpriteFrameName("geode.loader/pencil.png"), CircleBaseColor::Green, CircleBaseSize::Big), this, menu_selector(IconCell::onRename));
            rename->setUserData(icon);

            rename->m_baseScale = share->getContentSize().width / rename->getContentSize().width;
            rename->setScale(rename->m_baseScale);
            
            btns->addChildAtPosition(rename, Anchor::Center, ccp(-45, 45));

            if (icon->hasUploaded)
            {
                log::info(icon->name);

                share->setEnabled(false);
                as<CCSprite*>(share->getChildren()->objectAtIndex(0))->setColor(ccc3(100, 100, 100));
            }

            trash->m_baseScale = share->getContentSize().width / trash->getContentSize().width;
            trash->setScale(trash->m_baseScale);

            if (i != 0)
            {
                auto upSpr = CCSprite::createWithSpriteFrameName("edit_upBtn_001.png");
                upSpr->setScale(3.5f);
                auto up = CCMenuItemSpriteExtra::create(upSpr, this, menu_selector(IconCell::onUp));
                up->setTag(i);
                btns->addChildAtPosition(up, Anchor::Center, ccp(130, 45));
            }

            if (!isLast)
            {
                auto downSpr = CCSprite::createWithSpriteFrameName("edit_downBtn_001.png");
                downSpr->setScale(3.5f);
                auto down = CCMenuItemSpriteExtra::create(downSpr, this, menu_selector(IconCell::onDown));
                down->setTag(i);
                btns->addChildAtPosition(down, Anchor::Center, ccp(130, -45));
            }

            this->addChildAtPosition(layoutIcons, Anchor::Left, ccp(16, -7));
            this->addChildAtPosition(btns, Anchor::Right, ccp(-45, 0));

            if (icon->name.size() == 0)
                icon->name = "Unnamed Kit";

            CCTouchDispatcher::get()->addTargetedDelegate(btns, -131, true);

            return true;
        }

        static IconCell* create(Icon* icon, int i, bool isLast)
        {
            IconCell* pRet = new IconCell();
            if (pRet && pRet->init(icon, i, isLast)) {
                pRet->autorelease();
                return pRet;
            } else {
                delete pRet;
                return nullptr;
            }
        }
};

class IconSelectLayer : public CCLayerColor, TextInputDelegate
{
    public:
        ScrollLayer* scroll = nullptr;
        InputNode* searchBar = nullptr;
        CCLabelBMFont* error = nullptr;
        CCLabelBMFont* error2 = nullptr;
        bool hasAdded = false;

        static inline IconSelectLayer* instance = nullptr;

        std::vector<Icon*> icons = {};

        virtual void keyBackClicked()
        {
            onClose(nullptr);
        }
        
        void onClose(CCObject*)
        {
            this->removeFromParent();
        }

        void refreshIcons(bool move = true)
        {
            auto content = scroll->m_contentLayer;

            content->removeAllChildren();

            std::stringstream ss;

            for (size_t i = 0; i < icons.size(); i++)
            {
                if (toLower(icons[i]->name).find(toLower(searchBar->getString())) != std::string::npos)
                {
                    auto cell = IconCell::create(icons[i], i, i == (icons.size() - 1));

                    content->addChild(cell);
                }

                ss << icons[i]->saveToString();
                ss << ";";
            }

            auto s = ss.str();
            s = s.substr(0, s.size() - 1);

            Mod::get()->setSavedValue("saved-icons", s);
            
            error->setVisible(icons.size() == 0);

            float height = std::max<float>(scroll->getContentSize().height, 45 * content->getChildrenCount());

            content->setContentSize(ccp(content->getContentSize().width, height));

            CCArrayExt<IconCell*> objects = content->getChildren();

            int i = 0;

			for (auto* obj : objects) {
                i++;
				obj->setPositionY(height - (45 * i));
			}

            if (move)
                scroll->moveToTop();
        }

        void onNew(CCObject*)
        {
            if (!hasAdded)
            {
                hasAdded = true;

                auto icon = Icon::createIconFromCurrent();

                icons.push_back(icon);

                refreshIcons();

                return CCScene::get()->addChild(TextAlertPopup::create("Successfully saved to icon kit", 0.5f, 0.6f, 150, ""), 9999999);
            }

            CCScene::get()->addChild(TextAlertPopup::create("You've already added this icon kit", 0.5f, 0.6f, 150, ""), 9999999);
        }

        void onOnlineIcons(CCObject* sender)
        {
            OnlineIconsLayer::addToScene();
        }

        virtual void textChanged(CCTextInputNode* p0)
        {
            if (searchBar->getString().size() != 0)
            {
                error->setVisible(false);

                bool res = false;

                for (size_t i = 0; i < icons.size(); i++)
                {
                    if (toLower(icons[i]->name).find(toLower(searchBar->getString())) != std::string::npos)
                        res = true;
                }
                

                error2->setVisible(!res);
            }
            else
            {
                error->setVisible(icons.size() == 0);
                error2->setVisible(false);
            }

            refreshIcons();
        }

        bool init()
        {
            if (!CCLayerColor::init())
                return false;

            instance = this;

            auto ic = split(Mod::get()->getSavedValue<std::string>("saved-icons"), ';');

            for (size_t i = 0; i < ic.size(); i++)
            {
                icons.push_back(Icon::createIconFromString(ic[i]));
            }            

            this->setColor(ccc3(0, 0, 0));
            this->setOpacity(0);
            this->runAction(CCFadeTo::create(0.5f, 100));

            this->setKeypadEnabled(true);
            this->setKeyboardEnabled(true);

            auto size = ccp(450, 280);

            auto l = CCScale9Sprite::create("GJ_square01.png");
            l->setContentSize(size);
            l->setPosition(CCDirector::get()->getWinSize() / 2);

            auto menu = CCMenu::create();
            menu->setTouchPriority(-130);
            menu->ignoreAnchorPointForPosition(false);
            menu->setContentSize(size);
            l->addChildAtPosition(menu, Anchor::Center);

            auto title = CCLabelBMFont::create("Saved Icon Kits", "goldFont.fnt");
            title->setScale(0.75f);
            l->addChildAtPosition(title, Anchor::Top, ccp(0, -17.5f));

            auto ok = CCMenuItemSpriteExtra::create(ButtonSprite::create("OK"), this, menu_selector(IconSelectLayer::onClose));
            menu->addChildAtPosition(ok, Anchor::Bottom, ccp(0, 22.5f));

            searchBar = InputNode::create(350.0f / 0.8f, "Search Icon Kits");
            searchBar->setScale(0.8f);
            searchBar->getInput()->setDelegate(this);
            menu->addChildAtPosition(searchBar, Anchor::Top, ccp(0, -45));

            auto bg = CCScale9Sprite::create("square02_small.png");
            bg->setOpacity(75);
            bg->setContentSize(ccp(350, 160));
            l->addChildAtPosition(bg, Anchor::Center, ccp(0, -10));

            scroll = ScrollLayer::create(ccp(350, 160));
            scroll->setAnchorPoint(ccp(0, 0));
            scroll->ignoreAnchorPointForPosition(false);

            l->addChildAtPosition(scroll, Anchor::Center, ccp(0, -10) - scroll->getContentSize() / 2);

            auto add = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_newBtn_001.png"), this, menu_selector(IconSelectLayer::onNew));
            add->m_baseScale = 0.85f;
            add->setScale(add->m_baseScale);
            menu->addChildAtPosition(add, Anchor::BottomRight, ccp(-30, 30));

            auto online = CCMenuItemSpriteExtra::create(CCSprite::create("online.png"_spr), this, menu_selector(IconSelectLayer::onOnlineIcons));
            online->m_baseScale = 0.85f * 0.35f;
            online->setScale(online->m_baseScale);
            menu->addChildAtPosition(online, Anchor::BottomLeft, ccp(30, 30));

            error = CCLabelBMFont::create("Nothing here yet :(", "bigFont.fnt");
            error->setScale(0.625f);
            error->setAlignment(CCTextAlignment::kCCTextAlignmentCenter);
            error->setVisible(icons.size() == 0);

            l->addChildAtPosition(error, Anchor::Center, ccp(0, -10));

            as<CCNodeRGBA*>(error->getChildren()->objectAtIndex(17))->setColor(ccc3(94, 168, 234));
            as<CCNodeRGBA*>(error->getChildren()->objectAtIndex(18))->setColor(ccc3(94, 168, 234));

            error2 = CCLabelBMFont::create("No results found", "bigFont.fnt");
            error2->setScale(0.625f);
            error2->setAlignment(CCTextAlignment::kCCTextAlignmentCenter);
            error2->setVisible(false);

            l->addChildAtPosition(error2, Anchor::Center, ccp(0, -10));

            as<CCNodeRGBA*>(error2->getChildren()->objectAtIndex(0))->setColor(ccc3(255, 0, 0));
            as<CCNodeRGBA*>(error2->getChildren()->objectAtIndex(1))->setColor(ccc3(255, 0, 0));

            this->addChild(l);

            this->setTouchEnabled(true);
            CCTouchDispatcher::get()->addTargetedDelegate(this, -129, true);
            CCTouchDispatcher::get()->addTargetedDelegate(scroll, -130, true);

            refreshIcons();

            return true;
        }

        CREATE_FUNC(IconSelectLayer);
};

void IconCell::onUp(CCObject* sender)
{
    std::swap(IconSelectLayer::instance->icons[as<CCNode*>(sender)->getTag()], IconSelectLayer::instance->icons[as<CCNode*>(sender)->getTag() - 1]);

    IconSelectLayer::instance->refreshIcons(false);
};

void IconCell::onDown(CCObject* sender)
{
    std::swap(IconSelectLayer::instance->icons[as<CCNode*>(sender)->getTag()], IconSelectLayer::instance->icons[as<CCNode*>(sender)->getTag() + 1]);

    IconSelectLayer::instance->refreshIcons(false);
};

void IconCell::onTrash(CCObject* sender)
{
    if (CCKeyboardDispatcher::get()->getShiftKeyPressed())
    {
        IconSelectLayer::instance->icons.erase(IconSelectLayer::instance->icons.begin() + as<CCNode*>(sender)->getTag());

        IconSelectLayer::instance->refreshIcons();
    }
    else
    {
        geode::createQuickPopup(
        "Delete Kit",
        "Are you sure you want to\n<cr>delete</c> this kit?"
        #ifdef GEODE_IS_DESKTOP
        + std::string("\n(<ca>Tip:</c> hold shift to bypass this dialogue)")
        #endif
        ,
        "No", "Delete",
        [this, sender](FLAlertLayer* tis, bool btn2) {
            if (btn2) {
                IconSelectLayer::instance->icons.erase(IconSelectLayer::instance->icons.begin() + as<CCNode*>(sender)->getTag());

                IconSelectLayer::instance->refreshIcons();
            }
        }
    );
    }
};

void IconCell::onUse(CCObject* sender)
{
    auto v = as<IconCell*>(as<CCNode*>(sender)->getUserData());

    v->icon->applyIcons();

    CCScene::get()->addChild(TextAlertPopup::create("Set selected icons", 0.5f, 0.6f, 150, ""), 9999999);

    if (auto garage = getChildOfType<GJGarageLayer>(CCScene::get(), 0))
    {
        garage->updatePlayerColors();
        garage->setupIconSelect();
    }
}

void IconCell::onShare(CCObject* sender)
{
    auto icn = as<IconCell*>(as<CCNode*>(sender)->getUserData())->icon;
    
    if (icn->hasUploaded)
        return FLAlertLayer::create("Failed to upload kit", "You've <cg>already</c> uploaded this <cl>icon</c> kit.", "OK")->show();

    auto circle = LoadingCircle::create();
    circle->setFade(true);
    circle->show();

    auto url = fmt::format("https://www.uproxide.xyz/api/v1/iconkit/addNewKit.php?AccountID={}&Cube={}&Ship={}&Ball={}&Bird={}&Dart={}&Robot={}&Spider={}&Swing={}&Jetpack={}&GlowEnabled={}&GlowColor={}&PrimaryColor={}&SecondaryColor={}&KitName={}", GJAccountManager::get()->m_accountID, icon->cube, icon->ship, icon->ball, icon->ufo, icon->wave, icon->robot, icon->spider, icon->swing, icon->jetpack, icon->glow ? 1 : 0, icon->colour3, icon->colour1, icon->colour2, icon->name);

    web::AsyncWebRequest()
    .post(url)
    .text()
    .then([circle, icn, this](std::string const& catgirl) {
        circle->removeFromParent();
        icn->hasUploaded = true;
        IconSelectLayer::instance->refreshIcons(false);
        return FLAlertLayer::create("Uploaded Kit", "<cg>SUCCESS</c> uploading kit", "OK")->show();
    })
    .expect([circle](std::string const& error) {
        circle->removeFromParent();
        IconSelectLayer::instance->refreshIcons(false);
        return FLAlertLayer::create("Failed to upload kit", ("<cr>FAILED</c> to upload kit: " + error).c_str(), "OK")->show();
    });
}

void Icon::addToKit()
{
    CCScene::get()->addChild(TextAlertPopup::create("Saved Icon to Icon Kit", 0.5f, 0.6f, 150, ""), 9999999);

    IconSelectLayer::instance->icons.push_back(this);
    IconSelectLayer::instance->refreshIcons();
}

void RenameIconKitLayer::onClose(CCObject*)
{
    icon->name = inp->getString();

    IconSelectLayer::instance->refreshIcons(false);

    CCTouchDispatcher::get()->removeDelegate(this);

    this->removeFromParent();
}