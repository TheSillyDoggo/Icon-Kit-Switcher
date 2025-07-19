#include <Geode/Geode.hpp>
#include <Geode/modify/GJGarageLayer.hpp>
#include <Geode/modify/ProfilePage.hpp>
#include <Geode/modify/CCLayerColor.hpp>

using namespace geode::prelude;

#include "layers/IconSelectLayer.hpp"

$on_mod(Loaded) {
	if (!Mod::get()->getSaveContainer().contains("saved-icons-v2"))
	{
		std::vector<matjson::Value> savedIconsV2;
		auto v = string::split(Mod::get()->getSavedValue<std::string>("saved-icons"), ";");

		for (auto& s : v)
		{
			auto icn = Icon::createIconFromString(s);
			savedIconsV2.push_back(icn->saveToJson());
		}

		Mod::get()->setSavedValue("saved-icons-v2", savedIconsV2);
	}
}

class $modify(GJGarageLayerExt, GJGarageLayer) {

	void onIconSave(CCObject*) {
		IconSelectLayer::create("Icon Kits")->show();
	}

	bool init() {
		if (!GJGarageLayer::init())
			return false;

		auto menu = this->getChildByID("shards-menu");

		auto btn = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("gj_folderBtn_001.png"), this, menu_selector(GJGarageLayerExt::onIconSave));
		menu->addChild(btn);
		menu->updateLayout();

		return true;
	}
};

class $modify (ProfilePageExt, ProfilePage)
{
	struct Fields {
		bool hasLoaded = false;
	};

	void onSteal(CCObject*)
	{
		auto icn = Icon::createIconFromScore(m_score);
		auto savedIcons = Mod::get()->getSavedValue<std::vector<matjson::Value>>("saved-icons-v2");
		savedIcons.push_back(icn->saveToJson());
		Mod::get()->setSavedValue("saved-icons-v2", savedIcons);

		CCScene::get()->addChild(TextAlertPopup::create("Saved Icon to Icon Kit", 0.5f, 0.6f, 150, ""), 9999999);
	}

	void loadPageFromUserInfo(GJUserScore* p0)
	{
		ProfilePage::loadPageFromUserInfo(p0);

		if (auto menu = m_mainLayer->getChildByID("left-menu"))
		{
			if (!m_fields->hasLoaded)
			{
				m_fields->hasLoaded = true;
				
				auto btnSpr = CCSprite::createWithSpriteFrameName("GJ_copyBtn_001.png");
				btnSpr->setScale(0.7f);

				auto btn = CCMenuItemSpriteExtra::create(btnSpr, this, menu_selector(ProfilePageExt::onSteal));
				btn->setID("steal-btn"_spr);
				menu->addChild(btn);
				menu->updateLayout();
			}
		}
	}
};
