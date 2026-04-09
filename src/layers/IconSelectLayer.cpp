#include "IconSelectLayer.hpp"
#include "../IconCell.hpp"

using namespace geode::prelude;

IconSelectLayer* IconSelectLayer::create(std::string const& text)
{
    auto ret = new IconSelectLayer();
    if (ret->init(ccp(450.f, 280.f), "geode.loader/GE_square03.png"))
    {
        ret->setup(text);
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

void IconSelectLayer::onCompact(CCObject* sender)
{
    compactMode = !compactMode;
    Mod::get()->setSavedValue<bool>("use-compact-mode", compactMode);

    refreshIcons();
}

void IconSelectLayer::saveConfig()
{
    std::vector<matjson::Value> arr;
    for (size_t i = 0; i < icons.size(); i++)
    {
        arr.push_back(icons[i]->saveToJson());
    }

    Mod::get()->setSavedValue("saved-icons-v2", arr);
}

void IconSelectLayer::refreshIcons(bool move) {
    auto content = scroll->m_contentLayer;
    content->removeAllChildren();

    std::stringstream ss;

    std::string searchLower = string::toLower(searchBar->getString());

    std::vector<matjson::Value> arr;
    for (size_t i = 0; i < icons.size(); i++)
    {
        if (string::toLower(icons[i]->name).find(searchLower) != std::string::npos)
        {
            auto cell = IconCell::create(icons[i], i, i == (icons.size() - 1), compactMode);

            content->addChild(cell);
        }

        arr.push_back(icons[i]->saveToJson());
    }

    Mod::get()->setSavedValue("saved-icons-v2", arr);
    
    error->setVisible(icons.size() == 0);

    float height = std::max<float>(scroll->getContentSize().height, 45 * content->getChildrenCount());

    if (!compactMode)
    {
        height = std::max<float>(scroll->getContentSize().height, 60 * content->getChildrenCount());
    }

    content->setContentSize(ccp(content->getContentSize().width, height));

    CCArrayExt<IconCell*> objects = content->getChildren();

    int i = 0;

    for (auto* obj : objects) {
        i++;
        if (compactMode)
            obj->setPositionY(height - (45 * i));
        else
            obj->setPositionY(height - (60 * i));
    }

    if (move)
        scroll->moveToTop();
}

void IconSelectLayer::onNew(CCObject* sender) {
    if (!hasAdded)
    {
        hasAdded = true;

        auto icon = Icon::createIconFromCurrent();

        icons.push_back(icon);

        refreshIcons();

        geode::Notification::create("Successfully saved to icon kit")->show();
    }

    geode::Notification::create("You've already added this icon kit")->show();
}

void IconSelectLayer::textChanged(CCTextInputNode* p0)
{
    if (searchBar->getString().size() != 0)
    {
        error->setVisible(false);

        bool res = false;

        std::string searchLower = string::toLower(searchBar->getString());

        for (size_t i = 0; i < icons.size(); i++)
        {
            if (string::toLower(icons[i]->name).find(searchLower) != std::string::npos)
            {
                res = true;
                break;
            }
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

bool IconSelectLayer::setup(std::string const& text)
{
    setTitle(text, "goldFont.fnt", 0.8);
    
    compactMode = Mod::get()->getSavedValue<bool>("use-compact-mode", true);
    instance = this;

    auto compactOff = ButtonSprite::create(CCSprite::createWithSpriteFrameName("GJ_smallModeIcon_001.png"), 40, false, 40, "GJ_button_01.png", 1.0f);
    auto compactOn = ButtonSprite::create(CCSprite::createWithSpriteFrameName("GJ_smallModeIcon_001.png"), 40, false, 40, "GJ_button_02.png", 1.0f);

    compactToggle = CCMenuItemToggler::create(compactOff, compactOn, this, menu_selector(IconSelectLayer::onCompact));
    compactToggle->toggle(compactMode);

    auto ic = Mod::get()->getSavedValue<std::vector<matjson::Value>>("saved-icons-v2");

    for (size_t i = 0; i < ic.size(); i++)
    {
        icons.push_back(Icon::createIconFromJson(ic[i]));
    }

    auto menu = CCMenu::create();
    m_mainLayer->addChildAtPosition(menu, Anchor::Center);

    auto ok = CCMenuItemSpriteExtra::create(ButtonSprite::create("OK"), this, menu_selector(IconSelectLayer::onClose));
    menu->addChildAtPosition(ok, Anchor::Bottom, ccp(0, 45));

    searchBar = FallbackTextInput::create(350.0f / 0.8f, "Search Icon Kits");
    searchBar->setCommonFilter(CommonFilter::Any);
    searchBar->setScale(0.8f);
    searchBar->setDelegate(this);
    menu->addChildAtPosition(searchBar, Anchor::Top, ccp(0, -75));

    auto bg = CCScale9Sprite::create("square02_small.png");
    bg->setOpacity(75);
    bg->setContentSize(ccp(350, 160));
    m_mainLayer->addChildAtPosition(bg, Anchor::Center, ccp(0, -10));

    scroll = ScrollLayer::create(ccp(350, 160));
    scroll->m_peekLimitTop = 15;
    scroll->m_peekLimitBottom = 15;
    scroll->setAnchorPoint(ccp(0, 0));
    scroll->ignoreAnchorPointForPosition(false);

    m_mainLayer->addChildAtPosition(scroll, Anchor::Center, ccp(0, -10) - scroll->getContentSize() / 2);

    auto add = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_newBtn_001.png"), this, menu_selector(IconSelectLayer::onNew));
    add->m_baseScale = 0.85f;
    add->setScale(add->m_baseScale);
    menu->addChildAtPosition(add, Anchor::BottomRight, ccp(-30, 30));

    //auto online = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_myServerBtn_001.png"), this, menu_selector(IconSelectLayer::onOnlineIcons));
    //menu->addChildAtPosition(online, Anchor::BottomLeft, ccp(30, 30));

    error = CCLabelBMFont::create("Nothing here yet :(", "bigFont.fnt");
    error->setScale(0.625f);
    error->setAlignment(CCTextAlignment::kCCTextAlignmentCenter);
    error->setVisible(icons.size() == 0);

    m_mainLayer->addChildAtPosition(error, Anchor::Center, ccp(0, -10));

    static_cast<CCNodeRGBA*>(error->getChildren()->objectAtIndex(17))->setColor(ccc3(94, 168, 234));
    static_cast<CCNodeRGBA*>(error->getChildren()->objectAtIndex(18))->setColor(ccc3(94, 168, 234));

    error2 = CCLabelBMFont::create("No results found", "bigFont.fnt");
    error2->setScale(0.625f);
    error2->setAlignment(CCTextAlignment::kCCTextAlignmentCenter);
    error2->setVisible(false);

    m_mainLayer->addChildAtPosition(error2, Anchor::Center, ccp(0, -10));

    static_cast<CCNodeRGBA*>(error2->getChildren()->objectAtIndex(0))->setColor(ccc3(255, 0, 0));
    static_cast<CCNodeRGBA*>(error2->getChildren()->objectAtIndex(1))->setColor(ccc3(255, 0, 0));

    refreshIcons();

    return true;
}

IconSelectLayer::~IconSelectLayer()
{
    for (auto icon : icons)
    {
        delete icon;
    }
}