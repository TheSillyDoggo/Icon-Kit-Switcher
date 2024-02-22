#pragma once

#include <Geode/Geode.hpp>
#include <Geode/utils/web.hpp>
#include <Geode/ui/TextInput.hpp>

using namespace geode::prelude;

#include "Icon.h"
#include "DEVSetSecret.h"

std::string toLower(const std::string& str) {
    std::string result;
    for (char c : str) {
        result += std::tolower(c);
    }
    return result;
}

class OnlineIconCell : public CCLayerColor
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

        void onAdd(CCObject* sender)
        {
            auto ico = as<Icon*>(as<CCNode*>(sender)->getUserData());
            ico->hasUploaded = true;

            ico->addToKit();
        }

        void onDev(CCObject* sender);

        void onCreator(CCObject* sender);

        bool init(Icon* icon, int i)
        {
            if (!CCLayerColor::initWithColor(ccc4(194, 114, 62, 255)))
                return false;

            this->icon = icon;

            if (i % 2 == 0)
                this->setColor(ccc3(161, 88, 44));

            this->setContentSize(ccp(350, 45));
            this->setAnchorPoint(ccp(0, 0));

            auto name = CCLabelBMFont::create((icon->name.size() != 0 ? icon->name.c_str() : "Unnamed Kit"), "bigFont.fnt");
            name->setAnchorPoint(ccp(0, 1));
            this->addChildAtPosition(name, Anchor::TopLeft, ccp(3, 0));
            name->limitLabelWidth(200, 0.45f, 0.1f);

            auto byMenu = CCMenu::create();
            byMenu->setContentSize(this->getContentSize());

            auto byText = CCLabelBMFont::create((std::string("By ") + icon->uploader).c_str(), "goldFont.fnt");
            byText->limitLabelWidth(100, 0.45f, 0.1f);
            auto by = CCMenuItemSpriteExtra::create(byText, this, menu_selector(OnlineIconCell::onCreator));
            by->setUserData(icon);
            byMenu->addChildAtPosition(by, Anchor::TopLeft, ccp(3 + name->getScaledContentSize().width + 3, -2) + (by->getContentSize() / 2) * ccp(1, -1));
            this->addChildAtPosition(byMenu, Anchor::Center);

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

            layoutIcons->setLayout(RowLayout::create()->setAutoScale(false)->setAxisAlignment(AxisAlignment::Start)->setGap(45));
            layoutIcons->setScale(0.7f);

            auto btns = CCMenu::create();
            btns->setContentSize(ccp(0, 0));

            auto use = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_downloadsIcon_001.png"), this, menu_selector(OnlineIconCell::onAdd));
            use->setUserData(icon);
            btns->addChildAtPosition(use, Anchor::Center, ccp(0, 0));

            if (strcmp(GJAccountManager::get()->m_username.c_str(), "TheSillyDoggo") || strcmp(GJAccountManager::get()->m_username.c_str(), "Uproxide"))
            {
                auto delet = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_deleteServerBtn_001.png"), this, menu_selector(OnlineIconCell::onDev));
                delet->setUserData(icon);
                delet->m_baseScale = 0.375f;
                delet->setScale(delet->m_baseScale);
                btns->addChildAtPosition(delet, Anchor::Center, ccp(18, -11));
            }

            auto id = CCLabelBMFont::create(("#" + std::to_string(icon->id)).c_str(), "chatFont.fnt");
            id->setScale(0.5f);
            id->setColor(ccc3(0, 0, 0));
            id->setOpacity(150);
            id->setAnchorPoint(ccp(1, 1));

            this->addChildAtPosition(id, Anchor::TopRight, ccp(-3, -1));
            this->addChildAtPosition(layoutIcons, Anchor::Left, ccp(16, -7));
            this->addChildAtPosition(btns, Anchor::Right, ccp(-30, 0));

            CCTouchDispatcher::get()->addTargetedDelegate(btns, -135, true);
            CCTouchDispatcher::get()->addTargetedDelegate(byMenu, -135, true);

            if (icon->name.size() == 0)
                icon->name = "Unnamed Kit";

            return true;
        }

        static OnlineIconCell* create(Icon* icon, int i)
        {
            OnlineIconCell* pRet = new OnlineIconCell();
            if (pRet && pRet->init(icon, i)) {
                pRet->autorelease();
                return pRet;
            } else {
                delete pRet;
                return nullptr;
            }
        }
};

class OnlineIconsLayer : public CCLayerColor, TextInputDelegate
{
    public:
        CCLayer* l = nullptr;
        CCLayerColor* titleBar = nullptr;
        TextInput* searchBar = nullptr;
        LoadingCircle* circle = nullptr;
        ScrollLayer* scroll = nullptr;

        CCLabelBMFont* error2 = nullptr;

        static inline bool hasGottenIcons = false;
        static inline std::string iconCode = "";
        static inline std::vector<Icon*> icons = {};

        virtual void keyBackClicked()
        {
            onClose(nullptr);
        }

        void onClose(CCObject*)
        {
            if (this->numberOfRunningActions() != 0)
                return;

            this->runAction(CCFadeTo::create(0.75f, 0));
            l->runAction(CCEaseInOut::create(CCMoveTo::create(0.75f, CCDirector::get()->getWinSize() / 2 + ccp(0, CCDirector::get()->getWinSize().height)), 2));
            this->scheduleOnce(schedule_selector(OnlineIconsLayer::removeObject), 0.75f);
        }

        void removeObject(float)
        {
            CCTouchDispatcher::get()->removeDelegate(this);

            this->removeFromParent();
        }

        void refreshIcons()
        {
            titleBar->setVisible(true);

            auto content = scroll->m_contentLayer;

            content->removeAllChildren();

            for (size_t i = 0; i < icons.size(); i++)
            {
                auto name = searchBar->getString();
                bool s = false;
                
                if (searchBar->getString().starts_with("from:"))
                {
                    if(toLower(icons[i]->uploader).find(toLower(name.substr(name.find(":") + 1, name.size() - name.find(":")))) != std::string::npos)
                        s = true;
                }
                else if (searchBar->getString().starts_with("id="))
                {
                    if(numFromString<int>((name.substr(name.find("=") + 1, name.size() - name.find("=")))) == icons[i]->id)
                        s = true;
                }
                else if (searchBar->getString().starts_with("id>"))
                {
                    if(icons[i]->id > numFromString<int>((name.substr(name.find(">") + 1, name.size() - name.find(">")))))
                        s = true;
                }
                else if (searchBar->getString().starts_with("id<"))
                {
                    if(icons[i]->id < numFromString<int>((name.substr(name.find("<") + 1, name.size() - name.find("<")))))
                        s = true;
                }
                else
                {
                    if (toLower(icons[i]->name).find(toLower(searchBar->getString())) != std::string::npos)
                        s = true;
                }

                if (s)
                {
                    auto cell = OnlineIconCell::create(icons[i], i);

                    content->addChild(cell);
                }
            }
            
            if (searchBar->getString().size() == 0)
                error2->setVisible(false);
            else
                error2->setVisible(content->getChildrenCount() == 0);

            float height = std::max<float>(scroll->getContentSize().height, 45 * content->getChildrenCount());

            content->setContentSize(ccp(content->getContentSize().width, height));

            CCArrayExt<OnlineIconCell*> objects = content->getChildren();

            int i = 0;

			for (auto* obj : objects) {
                i++;
				obj->setPositionY(height - (45 * i));
			}

            scroll->moveToTop();
        }

        void onRefresh(CCObject*)
        {
            if (circle->isVisible() == false)
            {
                OnlineIconsLayer::hasGottenIcons = false;
                circle->setVisible(true);
                scroll->m_contentLayer->removeAllChildren();

                web::AsyncWebRequest()
                .fetch("https://www.uproxide.xyz/api/v1/iconkit/getKits.php")
                .text()
                .then([this](std::string const& catgirl) {
                    this->circle->setVisible(false);
                    iconCode = catgirl;
                    OnlineIconsLayer::hasGottenIcons = true;
                    icons.clear();

                    auto js = matjson::parse(catgirl); // i love catgirl :3

                    for (size_t i = 0; i < js.as_array().size(); i++)
                    {
                        auto c = js.as_array()[i].as_object();

                        auto icn = Icon::createIconFromJson(c);
                        icons.push_back(icn);
                    }

                    this->refreshIcons();
                })
                .expect([this](std::string const& error) {
                    this->circle->setVisible(false);
                    return FLAlertLayer::create("Failed to get online kits", ("<cr>FAILED</c> to get kits: " + error).c_str(), "OK")->show();
                });
            }
        }

        void onDev(CCObject*)
        {
            SetSecretLayer::addToScene();
        }

        virtual void textChanged(CCTextInputNode* p0)
        {
            refreshIcons();
        }

        bool init()
        {
            if (!CCLayerColor::init())
                return false;

            this->setKeypadEnabled(true);

            l = CCLayer::create();
            l->setPosition(CCDirector::get()->getWinSize() / 2 + ccp(0, CCDirector::get()->getWinSize().height));
            l->ignoreAnchorPointForPosition(false);
            l->setContentSize(ccp(356, 220));

            this->addChild(l);

            this->runAction(CCFadeTo::create(0.75f, 125));

            auto left = CCSprite::createWithSpriteFrameName("GJ_table_side_001.png");
            left->setScaleY(3.438f);
            left->setAnchorPoint(ccp(0, 0));
            l->addChildAtPosition(left, Anchor::BottomLeft, ccp(-20, 0));

            auto right = CCSprite::createWithSpriteFrameName("GJ_table_side_001.png");
            right->setScaleY(3.438f);
            right->setFlipX(true);
            right->setAnchorPoint(ccp(1, 0));
            l->addChildAtPosition(right, Anchor::BottomRight, ccp(20, 0));
            
            auto top = CCSprite::createWithSpriteFrameName("GJ_table_top_001.png");
            l->addChildAtPosition(top, Anchor::Top, ccp(0, 15));

            auto bottom = CCSprite::createWithSpriteFrameName("GJ_table_bottom_001.png");
            l->addChildAtPosition(bottom, Anchor::Bottom, ccp(0, -10));

            auto title = CCLabelBMFont::create("Online Icon Kits", "bigFont.fnt");
            title->setScale(0.75f);
            l->addChildAtPosition(title, Anchor::Top, ccp(0, 18));

            auto base = CCLayerColor::create(ccc4(0, 0, 0, 180));
            base->setContentSize(l->getContentSize());
            base->setPosition(ccp(0, 0));
            base->setAnchorPoint(ccp(0, 0));
            l->addChild(base, -2);

            auto m = CCMenu::create();
            m->setContentSize(ccp(0, 0));
            l->addChildAtPosition(m, Anchor::BottomLeft, ccp(-1, 0) * l->getPosition() + ccp(l->getContentSize().width / 2, -1 * (CCDirector::get()->getWinSize().height / 2 - l->getContentSize().height / 2)));

            auto back = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_arrow_03_001.png"), this, menu_selector(OnlineIconsLayer::onClose));
            m->addChildAtPosition(back, Anchor::BottomLeft, ccp(24, CCDirector::get()->getWinSize().height - 23));

            auto refresh = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_updateBtn_001.png"), this, menu_selector(OnlineIconsLayer::onRefresh));
            m->addChildAtPosition(refresh, Anchor::BottomLeft, ccp(CCDirector::get()->getWinSize().width - 32, 32));

            l->runAction(CCEaseInOut::create(CCMoveTo::create(0.75f, CCDirector::get()->getWinSize() / 2), 2));

            CCTouchDispatcher::get()->addTargetedDelegate(this, -132, true);
            CCTouchDispatcher::get()->addTargetedDelegate(m, -133, true);

            scroll = ScrollLayer::create(ccp(350, 190));
            scroll->setAnchorPoint(ccp(0, 0));
            scroll->ignoreAnchorPointForPosition(false);
            scroll->setZOrder(-1);

            l->addChildAtPosition(scroll, Anchor::BottomLeft, ccp(3, 6));

            titleBar = CCLayerColor::create(ccc4(161, 88, 44, 255));
            titleBar->setContentSize(ccp(350, 23.5f));
            titleBar->setAnchorPoint(ccp(0, 1));
            titleBar->ignoreAnchorPointForPosition(false);
            titleBar->setZOrder(-1);
            titleBar->setVisible(false);
            l->addChildAtPosition(titleBar, Anchor::TopLeft, ccp(3, 0));

            searchBar = TextInput::create(342.0f / 0.65f, "Search Icon Kits");
            searchBar->setScale(0.65f);
            searchBar->setAnchorPoint(ccp(0, 0.5f));
            searchBar->setCommonFilter(CommonFilter::Any);
            searchBar->setDelegate(this);
            titleBar->addChildAtPosition(searchBar, Anchor::Left, ccp(4, 0));

            error2 = CCLabelBMFont::create("No results found", "bigFont.fnt");
            error2->setScale(0.625f);
            error2->setAlignment(CCTextAlignment::kCCTextAlignmentCenter);
            error2->setVisible(false);

            as<CCNodeRGBA*>(error2->getChildren()->objectAtIndex(0))->setColor(ccc3(255, 0, 0));
            as<CCNodeRGBA*>(error2->getChildren()->objectAtIndex(1))->setColor(ccc3(255, 0, 0));

            l->addChildAtPosition(error2, Anchor::Center);

            if (strcmp(GJAccountManager::get()->m_username.c_str(), "TheSillyDoggo") || strcmp(GJAccountManager::get()->m_username.c_str(), "Uproxide"))
            {
                auto devMenu = CCMenu::create();

                auto btn = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("gj_streakBtn_off_001.png"), this, menu_selector(OnlineIconsLayer::onDev));
                devMenu->addChild(btn);
                devMenu->setScale(0.55f);
                devMenu->setAnchorPoint(ccp(0, 0));
                
                l->addChildAtPosition(devMenu, Anchor::TopRight, ccp(3, 16));

                CCTouchDispatcher::get()->addTargetedDelegate(devMenu, -135, true);
            }

            CCTouchDispatcher::get()->addTargetedDelegate(searchBar->getInputNode(), -1024, true);

            CCTouchDispatcher::get()->addTargetedDelegate(scroll, -134, true);

            circle = LoadingCircle::create();
            circle->runAction(CCRepeatForever::create(CCRotateBy::create(1, 360)));
            circle->setContentSize(ccp(0, 0));
            as<CCNode*>(circle->getChildren()->objectAtIndex(0))->setPosition(ccp(0, 0));
            base->addChildAtPosition(circle, Anchor::Center);
            circle->setVisible(false);

            if (!hasGottenIcons)
            {
                circle->setVisible(true);

                web::AsyncWebRequest()
                .fetch("https://www.uproxide.xyz/api/v1/iconkit/getKits.php")
                .text()
                .then([this](std::string const& catgirl) {
                    this->circle->setVisible(false);
                    iconCode = catgirl;
                    OnlineIconsLayer::hasGottenIcons = true;

                    auto js = matjson::parse(catgirl); // i love catgirl :3

                    for (size_t i = 0; i < js.as_array().size(); i++)
                    {
                        auto c = js.as_array()[i].as_object();

                        auto icn = Icon::createIconFromJson(c);
                        icons.push_back(icn);
                    }

                    this->refreshIcons();
                })
                .expect([this](std::string const& error) {
                    this->circle->setVisible(false);
                    return FLAlertLayer::create("Failed to get online kits", ("<cr>FAILED</c> to get kits: " + error).c_str(), "OK")->show();
                });
            }
            else
            {
                refreshIcons();
            }

            return true;
        }

        CREATE_FUNC(OnlineIconsLayer);

        static void addToScene()
        {
            auto pRet = OnlineIconsLayer::create();

            CCScene::get()->addChild(pRet, CCScene::get()->getHighestChildZ() + 1);
        }
};

void OnlineIconCell::onDev(CCObject* sender)
{
    auto ico = as<Icon*>(as<CCNode*>(sender)->getUserData());

    auto circle = LoadingCircle::create();
    circle->setZOrder(69696969);
    circle->show();

    geode::createQuickPopup(
        "DEV: Delete Icon Kit",
        "Are you sure you want to\n<cr>delete</c> this kit from the servers?",
        "No", "Delete",
        [this, ico, circle](FLAlertLayer* tis, bool btn2) {
            if (btn2) {
                //delete from server
                if (auto s = getChildOfType<OnlineIconsLayer>(CCScene::get(), 0))
                {
                    s->scroll->m_contentLayer->removeAllChildren();
                    s->titleBar->setVisible(false);
                }

                web::AsyncWebRequest()
                .fetch(fmt::format("https://www.uproxide.xyz/api/v1/iconkit/deleteKit.php?Secret={}&KitID={}", Mod::get()->getSavedValue<std::string>("_devsecret"), ico->id))
                .text()
                .then([this, circle](std::string const& catgirl) {
                    circle->removeFromParent();

                    if (auto s = getChildOfType<OnlineIconsLayer>(CCScene::get(), 0))
                    {
                        s->onRefresh(nullptr);
                    }
                })
                .expect([this, circle](std::string const& error) {
                    circle->removeFromParent();
                    return FLAlertLayer::create("Failed to delete icon kit", ("<cr>FAILED</c> to delete icon kit: " + error).c_str(), "OK")->show();
                });
            }
        }
    );
}

void OnlineIconCell::onCreator(CCObject* sender)
{
    auto ico = as<Icon*>(as<CCNode*>(sender)->getUserData());

    if (auto gj = getChildOfType<OnlineIconsLayer>(CCScene::get(), 0))
    {
        gj->searchBar->setString("from:" + ico->uploader);

        gj->refreshIcons();
    }
}