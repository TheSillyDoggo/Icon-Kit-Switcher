#include "IconCell.hpp"
#include "layers/RenameIconKitLayer.hpp"
#include "layers/IconSelectLayer.hpp"
#include <hiimjustin000.more_icons/include/MoreIcons.hpp>

using namespace geode::prelude;

void IconCell::onRename(CCObject* sender) {
    //auto icn = as<Icon*>(as<CCNode*>(sender)->getUserData());

    RenameIconKitLayer::create("Rename Icon", this->icon)->show();
}

void IconCell::onUp(CCObject* sender) {
    std::swap(IconSelectLayer::get()->icons[as<CCNode*>(sender)->getTag()], IconSelectLayer::get()->icons[as<CCNode*>(sender)->getTag() - 1]);
    IconSelectLayer::get()->refreshIcons(false);
};

void IconCell::onDown(CCObject* sender) {
    std::swap(IconSelectLayer::get()->icons[as<CCNode*>(sender)->getTag()], IconSelectLayer::get()->icons[as<CCNode*>(sender)->getTag() + 1]);
    IconSelectLayer::get()->refreshIcons(false);
};

void IconCell::onTrash(CCObject* sender) {
    if (CCKeyboardDispatcher::get()->getShiftKeyPressed()) {
        IconSelectLayer::get()->icons.erase(IconSelectLayer::get()->icons.begin() + as<CCNode*>(sender)->getTag());
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
                IconSelectLayer::get()->icons.erase(IconSelectLayer::get()->icons.begin() + as<CCNode*>(sender)->getTag());

                IconSelectLayer::get()->refreshIcons();
            }
        }
        );
    }
};

void IconCell::onUse(CCObject* sender) {
    //auto v = as<IconCell*>(as<CCNode*>(sender)->getUserData());

    this->icon->applyIcons();

    CCScene::get()->addChild(TextAlertPopup::create("Set selected icons", 0.5f, 0.6f, 150, ""), 9999999);

    //if (auto garage = getChildOfType<GJGarageLayer>(CCScene::get(), 0)) {
    //    garage->updatePlayerColors();
    //}
}

IconCell* IconCell::create(Icon* icon, int i, bool isLast, bool compactMode) {
    IconCell* pRet = new IconCell();
    if (pRet->init(icon, i, isLast, compactMode)) {
        pRet->autorelease();
        return pRet;
    }
    delete pRet;
    return nullptr;
}

bool IconCell::init(Icon* icon, int i, bool isLast, bool compactMode) {
    if (!CCLayerColor::init())
        return false;

    this->icon = icon;

    if (i % 2 == 0)
        this->setOpacity(50);
    else
        this->setOpacity(100);

    this->setContentSize(ccp(350, 45));

    this->setAnchorPoint(ccp(0, 0));

    auto nameMenu = CCMenu::create();
    this->addChild(nameMenu);

    auto name = CCLabelBMFont::create((icon->name.size() != 0 ? icon->name.c_str() : "Unnamed Kit"), "bigFont.fnt");
    name->limitLabelWidth(300, 0.45f, 0.1f);

    auto nameBtn = CCMenuItemSpriteExtra::create(name, this, menu_selector(IconCell::onRename));
    nameBtn->setAnchorPoint(ccp(0, 0.5));
    nameBtn->setUserData(icon);
    nameBtn->setPosition(-628, -169);
    nameMenu->addChild(nameBtn);

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

    this->addChildAtPosition(buttonsMenu, Anchor::Right, ccp(-60, 0));

    if (icon->name.size() == 0)
        icon->name = "Unnamed Kit";

    return true;
}


SimplePlayer* IconCell::createSprite(int id, const std::string& name, int type) {
    auto plr = SimplePlayer::create(id);
    plr->updatePlayerFrame(id, as<IconType>(type));

    plr->setColor(GameManager::get()->colorForIdx(icon->colour1));
    plr->setSecondColor(GameManager::get()->colorForIdx(icon->colour2));

    if (icon->glow)
        plr->setGlowOutline(GameManager::get()->colorForIdx(icon->colour3));

    plr->setScale(0.9f);

    if (!name.empty()) MoreIcons::updateSimplePlayer(plr, name, as<IconType>(type));

    return plr;
}