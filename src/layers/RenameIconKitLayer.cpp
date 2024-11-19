#include "RenameIconKitLayer.hpp"
#include "IconSelectLayer.hpp"

using namespace geode::prelude;

void RenameIconKitLayer::onClose(CCObject*) {
    icon->name = inp->getString();

    IconSelectLayer::get()->refreshIcons(false);

    Popup::onClose(nullptr);

}

bool RenameIconKitLayer::setup(std::string text, Icon* icon) {
    this->icon = icon;

    setTitle(text);

    auto menu = CCMenu::create();

    inp = TextInput::create(260, "Icon Kit Name");
    inp->setString(icon->name);
    menu->addChild(inp);
    inp->setPosition(m_mainLayer->getContentSize() / 2);

    auto ok = CCMenuItemSpriteExtra::create(ButtonSprite::create("OK"), this, menu_selector(RenameIconKitLayer::onClose));
    menu->addChild(ok);
    ok->setPosition(inp->getPosition());
    ok->setPositionY(ok->getPositionY() - 55);

    m_mainLayer->addChild(menu);
    menu->setPosition(0, 0);

    return true;
}

RenameIconKitLayer* RenameIconKitLayer::create(std::string text, Icon *icon) {
    RenameIconKitLayer* pRet = new RenameIconKitLayer();
    if (pRet->initAnchored(340, 170, text, icon)) {
        pRet->autorelease();
        return pRet;
    }
    delete pRet;
    return nullptr;
}

void RenameIconKitLayer::keyBackClicked() {
    this->onClose(nullptr);
}