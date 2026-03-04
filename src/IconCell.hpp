#pragma once

#include <Geode/Geode.hpp>
#include "Icon.hpp"
#include "FallbackTextInput.hpp"

class IconCell : public cocos2d::CCLayerColor
{
    protected:
        Icon* icon = nullptr;
        FallbackTextInput* name = nullptr;

    public:
        static IconCell* create(Icon* icon, int i, bool isLast, bool isCompactMode);
        SimplePlayer* createSprite(int id, const std::string& name, int type);

        void onUp(CCObject* sender);
        void onDown(CCObject* sender);
        void onUse(CCObject* sender);
        void onTrash(CCObject* sender);

        bool init(Icon* icon, int i, bool isLast, bool compactMode);
};