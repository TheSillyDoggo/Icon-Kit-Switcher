#pragma once

#include <Geode/Geode.hpp>

class FallbackTextInput : public geode::TextInput
{
    protected:
        std::string lastCheck = "";

        void updateCheck(float);

    public:
        static FallbackTextInput* create(float width, geode::ZStringView placeholder, geode::ZStringView font = "bigFont.fnt");
};