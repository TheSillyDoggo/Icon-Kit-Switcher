#pragma once

#include <Geode/Geode.hpp>
#include <Geode/ui/TextInput.hpp>

#include "../Icon.hpp"

class IconSelectLayer : public geode::Popup<std::string const&>, TextInputDelegate {
protected:
    geode::ScrollLayer* scroll = nullptr;
    geode::TextInput* searchBar = nullptr;
    cocos2d::CCLabelBMFont* error = nullptr;
    cocos2d::CCLabelBMFont* error2 = nullptr;
    bool hasAdded = false;
    bool compactMode = false;
    static inline IconSelectLayer* instance = nullptr;
public:
    std::vector<Icon*> icons = {};
    void onCompact(CCObject*);
    static IconSelectLayer* get() {
        return instance;
    }

    void refreshIcons(bool move = true);

    void onNew(cocos2d::CCObject*);

    virtual void textChanged(CCTextInputNode* p0);

    bool setup(std::string const& text);

    static IconSelectLayer* create(std::string const& text);
};