#pragma once

#include <Geode/Geode.hpp>
#include <Geode/ui/TextInput.hpp>
#include "../FallbackTextInput.hpp"
#include "../Icon.hpp"

class IconSelectLayer : public geode::Popup, TextInputDelegate
{
    protected:
        CCMenuItemToggler* compactToggle = nullptr;
        geode::ScrollLayer* scroll = nullptr;
        FallbackTextInput* searchBar = nullptr;
        cocos2d::CCLabelBMFont* error = nullptr;
        cocos2d::CCLabelBMFont* error2 = nullptr;
        bool hasAdded = false;
        bool compactMode = false;
        static inline IconSelectLayer* instance = nullptr;

        ~IconSelectLayer();

    public:
        static IconSelectLayer* create(std::string const& text);

        std::vector<Icon*> icons = {};
        void onCompact(CCObject* sender);
        static IconSelectLayer* get() {
            return instance;
        }

        void onNew(cocos2d::CCObject* sender);

        void refreshIcons(bool move = true);
        void saveConfig();

        virtual void textChanged(CCTextInputNode* p0);

        bool setup(std::string const& text);
};