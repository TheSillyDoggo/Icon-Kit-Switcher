#include "RenameIconKitLayer.hpp"
#include "IconSelectLayer.hpp"

using namespace geode::prelude;

void RenameIconKitLayer::onClose(CCObject*) {
    icon->name = inp->getString();

    IconSelectLayer::get()->refreshIcons(false);

    Popup::onClose(nullptr);

}

bool RenameIconKitLayer::setup(std::string const& text, Icon* icon) {
    this->icon = icon;

    setTitle(text);

    auto menu = CCMenu::create();
    menu->setPosition(ccp(170, 85));

    auto ok = CCMenuItemSpriteExtra::create(ButtonSprite::create("OK"), this, menu_selector(RenameIconKitLayer::onClose));
    menu->addChildAtPosition(ok, Anchor::Center, ccp(0, -55));

    inp = TextInput::create(260, "Icon Kit Name");
    inp->setString(icon->name);
    menu->addChildAtPosition(inp, Anchor::Center);

    m_mainLayer->addChild(menu);

    return true;
}

RenameIconKitLayer* RenameIconKitLayer::create(std::string const& text, Icon *icon) {
    RenameIconKitLayer* pRet = new RenameIconKitLayer();
    if (pRet->initAnchored(340.f, 170.f, text, icon)) {
        pRet->autorelease();
        return pRet;
    }
    delete pRet;
    return nullptr;
}

void RenameIconKitLayer::keyBackClicked() {
    this->onClose(nullptr);
}