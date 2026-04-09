#include "IconCell.hpp"
#include "layers/IconSelectLayer.hpp"
// #include <hiimjustin000.more_icons/include/MoreIcons.hpp>

using namespace geode::prelude;

void IconCell::onUp(CCObject* sender) {
    std::swap(IconSelectLayer::get()->icons[static_cast<CCNode*>(sender)->getTag()], IconSelectLayer::get()->icons[static_cast<CCNode*>(sender)->getTag() - 1]);
    IconSelectLayer::get()->refreshIcons(false);
};

void IconCell::onDown(CCObject* sender) {
    std::swap(IconSelectLayer::get()->icons[static_cast<CCNode*>(sender)->getTag()], IconSelectLayer::get()->icons[static_cast<CCNode*>(sender)->getTag() + 1]);
    IconSelectLayer::get()->refreshIcons(false);
};

void IconCell::onTrash(CCObject* sender) {
    if (CCKeyboardDispatcher::get()->getShiftKeyPressed()) {
        IconSelectLayer::get()->icons.erase(IconSelectLayer::get()->icons.begin() + static_cast<CCNode*>(sender)->getTag());
        IconSelectLayer::get()->refreshIcons();
    }
    else {
        geode::createQuickPopup(
        "Delete Kit",
        GEODE_DESKTOP("Are you sure you want to\n<cr>delete</c> this kit?\n(<ca>Tip:</c> hold shift to bypass this dialogue)",)
        GEODE_MOBILE("Are you sure you want to\n<cr>delete</c> this kit?",)
        "No", "Delete",
        [this, sender](FLAlertLayer* tis, bool btn2) {
            if (btn2) {
                IconSelectLayer::get()->icons.erase(IconSelectLayer::get()->icons.begin() + static_cast<CCNode*>(sender)->getTag());

                IconSelectLayer::get()->refreshIcons();
            }
        }
        );
    }
};

void IconCell::onUse(CCObject* sender)
{
    //auto v = static_cast<IconCell*>(static_cast<CCNode*>(sender)->getUserData());

    this->icon->applyIcons();

    geode::Notification::create("Set selected icons")->show();

    //if (auto garage = getChildOfType<GJGarageLayer>(CCScene::get(), 0)) {
    //    garage->updatePlayerColors();
    //}
}

IconCell* IconCell::create(Icon* icon, int i, bool isLast, bool compactMode)
{
    IconCell* pRet = new IconCell();
    if (pRet->init(icon, i, isLast, compactMode)) {
        pRet->autorelease();
        return pRet;
    }
    delete pRet;
    return nullptr;
}

bool IconCell::init(Icon* icon, int i, bool isLast, bool compactMode)
{
    if (!CCLayerColor::init())
        return false;

    if (icon->name.size() == 0)
        icon->name = "Unnamed Kit";

    this->icon = icon;

    if (i % 2 == 0)
        this->setOpacity(50);
    else
        this->setOpacity(100);

    this->setContentSize(ccp(350, 45));

    this->setAnchorPoint(ccp(0, 0));

    name = FallbackTextInput::create(550, "Icon kit name");
    name->setScale(0.45f);
    name->setString(icon->name);
    name->setAnchorPoint(ccp(0, 1));
    name->setTextAlign(TextInputAlign::Left);
    name->setCallback([this](const std::string& text)
    {
        this->icon->name = text;
        IconSelectLayer::get()->saveConfig();
    });

    auto layoutIcons = CCMenu::create();
    layoutIcons->setContentSize(ccp(6969, 0));
    layoutIcons->setAnchorPoint(ccp(0, 0.5f));

    layoutIcons->addChild(createSprite(icon->cube, icon->miCube, 0));
    layoutIcons->addChild(createSprite(icon->ship, icon->miShip, 1));
    layoutIcons->addChild(createSprite(icon->ball, icon->miBall, 2));
    layoutIcons->addChild(createSprite(icon->ufo, icon->miUfo, 3));
    layoutIcons->addChild(createSprite(icon->wave, icon->miWave, 4));
    layoutIcons->addChild(createSprite(icon->robot, icon->miRobot, 5));
    layoutIcons->addChild(createSprite(icon->spider, icon->miSpider, 6));
    layoutIcons->addChild(createSprite(icon->swing, icon->miSwing, 7));
    layoutIcons->addChild(createSprite(icon->jetpack, icon->miJetpack, 8));

    layoutIcons->setLayout(RowLayout::create()->setAutoScale(false)->setAxisAlignment(AxisAlignment::Start)->setGap(40));
    layoutIcons->setScale(0.7f);

    auto btns = CCMenu::create();
    btns->setScale(0.245f);

    btns->setContentSize(ccp(0, 0));

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
    this->addChildAtPosition(btns, Anchor::Right, ccp(-45 , 0));

    auto buttonsMenu = CCMenu::create();

    auto useSpr = CCSprite::createWithSpriteFrameName("GJ_selectSongBtn_001.png");
    useSpr->setScale(0.7);
    auto useBtn = CCMenuItemSpriteExtra::create(useSpr, this, menu_selector(IconCell::onUse));
    useBtn->setTag(i);

    auto trashSpr = CCSprite::createWithSpriteFrameName("GJ_trashBtn_001.png");
    trashSpr->setScale(0.7);
    auto trashBtn = CCMenuItemSpriteExtra::create(trashSpr, this, menu_selector(IconCell::onTrash));
    trashBtn->setTag(i);

    buttonsMenu->addChild(useBtn);
    buttonsMenu->addChild(trashBtn);
    
    buttonsMenu->setLayout(AxisLayout::create()->setAutoScale(false));

    this->addChildAtPosition(name, Anchor::TopLeft, ccp(0, 0));
    this->addChildAtPosition(buttonsMenu, Anchor::Right, ccp(-60, 0));
    return true;
}


SimplePlayer* IconCell::createSprite(int id, const std::string& name, int type)
{
    auto plr = SimplePlayer::create(id);
    plr->updatePlayerFrame(id, static_cast<IconType>(type));

    plr->setColor(GameManager::get()->colorForIdx(icon->colour1));
    plr->setSecondColor(GameManager::get()->colorForIdx(icon->colour2));

    if (icon->glow)
        plr->setGlowOutline(GameManager::get()->colorForIdx(icon->colour3));

    plr->setScale(0.9f);

    // if (!name.empty()) MoreIcons::updateSimplePlayer(plr, name, static_cast<IconType>(type));

    return plr;
}