#include "FallbackTextInput.hpp"
#include <Geode/modify/CCTextInputNode.hpp>

using namespace geode::prelude;

FallbackTextInput* FallbackTextInput::create(float width, ZStringView placeholder, ZStringView font)
{
    auto ret = new FallbackTextInput();
    if (ret->init(width, placeholder, font))
    {
        ret->schedule(schedule_selector(FallbackTextInput::updateCheck));
        ret->updateCheck(0);
        ret->getInputNode()->setUserFlag("fallback"_spr, true);
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

void FallbackTextInput::updateCheck(float)
{
    if (lastCheck != getString())
    {
        lastCheck = getString();

        bool useFallback = false;

        if (!getString().empty())
        {
            auto ch = getInputNode()->m_textLabel->getConfiguration()->getCharacterSet();

            for (auto str : utils::string::split(getString()))
            {
                if (!ch->contains((int)str))
                {
                    useFallback = true;
                    break;
                }
            }
        }

        getInputNode()->m_textField->setVisible(useFallback);
        getInputNode()->m_textLabel->setVisible(!useFallback);
    }
}

CCLabelTTF* getStaticTTF()
{
    static Ref<CCLabelTTF> instance = CCLabelTTF::create("", "Arial", 24);

    return instance;
}

class $modify (CCTextInputNode)
{
    virtual bool onTextFieldInsertText(cocos2d::CCTextFieldTTF* pSender, char const* text, int nLen, cocos2d::enumKeyCodes keyCodes)
    {
        if (getUserFlag("fallback"_spr))
        {
            m_allowedChars = text;
            m_maxLabelLength = getString().size() + nLen + 69;
        }
        
        return CCTextInputNode::onTextFieldInsertText(pSender, text, nLen, keyCodes);
    }

    void updateBlinkLabelToChar(int index)
    {
        CCTextInputNode::updateBlinkLabelToChar(index);

        if (getUserFlag("fallback"_spr) && m_textField->isVisible())
        {
            std::string str = index == -1 ? getString() : std::string(getString()).substr(0, index);

            getStaticTTF()->setString(str.c_str());
            m_cursor->setPositionX((-m_textField->getScaledContentWidth() * m_textField->getAnchorPoint().x) + getStaticTTF()->getScaledContentWidth());
        }
    }
};