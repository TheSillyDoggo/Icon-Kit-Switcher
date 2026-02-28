#pragma once

#include <Geode/Geode.hpp>
#include <Geode/ui/TextInput.hpp>

#include "../Icon.hpp"

class RenameIconKitLayer : public geode::Popup {
    public:
        Icon* icon = nullptr;
        geode::TextInput* inp = nullptr;

        virtual void keyBackClicked();

        void onClose(cocos2d::CCObject*);

        bool init(std::string const& text, Icon* icon);

        static RenameIconKitLayer* create(std::string const& text, Icon* icon);

        static void addToScene(Icon* icon);
};
