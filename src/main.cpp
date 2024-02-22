#include <Geode/Geode.hpp>
#include <Geode/modify/GJGarageLayer.hpp>
#include <Geode/modify/ProfilePage.hpp>
#include <Geode/modify/CCLayerColor.hpp>

using namespace geode::prelude;

#include "IconSelectLayer.h"

class $modify(GJGarageLayerExt, GJGarageLayer) {

	void onIconSave(CCObject*) {
		CCScene::get()->addChild(IconSelectLayer::create(), CCScene::get()->getHighestChildZ() + 1);
	}

	bool init() {
		if (!GJGarageLayer::init())
			return false;

		auto menu = this->getChildByID("shards-menu");

		auto plr = SimplePlayer::create(8);

		plr->setColor(GameManager::get()->colorForIdx(GameManager::get()->m_playerColor));
		plr->setSecondColor(GameManager::get()->colorForIdx(GameManager::get()->m_playerColor2));
		if (GameManager::get()->m_playerGlow)
			plr->setGlowOutline(GameManager::get()->colorForIdx(GameManager::get()->m_playerGlowColor));

		auto btnSpr = CircleButtonSprite::create(plr, CircleBaseColor::Gray);
		btnSpr->setRotation(45.0f / 2.0f);
		btnSpr->setScale(0.85f);

		auto btn = CCMenuItemSpriteExtra::create(btnSpr, this, menu_selector(GJGarageLayerExt::onIconSave));
		menu->addChild(btn);
		menu->updateLayout();

		return true;
	}
};

class $modify (ProfilePageEXt, ProfilePage)
{
	void onSteal(CCObject*)
	{
		auto icn = Icon::createIconFromScore(m_score);

		std::stringstream ss;
		ss << Mod::get()->getSavedValue<std::string>("saved-icons");
		if (ss.str().size() != 0)
			ss << ";";
		ss << icn->saveToString();

		Mod::get()->setSavedValue<std::string>("saved-icons", ss.str());

		CCScene::get()->addChild(TextAlertPopup::create("Saved Icon to Icon Kit", 0.5f, 0.6f, 150, ""), 9999999);
	}

	void loadPageFromUserInfo(GJUserScore* p0)
	{
		ProfilePage::loadPageFromUserInfo(p0);

		if (auto menu = as<CCNode*>(this->getChildren()->objectAtIndex(0))->getChildByID("left-menu"))
		{
			auto btnSpr = CCSprite::createWithSpriteFrameName("GJ_copyBtn_001.png");
			btnSpr->setScale(0.7f);

			auto btn = CCMenuItemSpriteExtra::create(btnSpr, this, menu_selector(ProfilePageEXt::onSteal));
			btn->setID("steal-btn"_spr);
			menu->addChild(btn);
			menu->updateLayout();
		}
	}
};