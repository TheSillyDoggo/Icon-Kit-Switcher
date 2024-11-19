#include "Icon.hpp"
#include "layers/IconSelectLayer.hpp"
#include <Geode/Geode.hpp>

std::vector<std::string> Icon::split(const std::string& input, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string token;
    
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    
    return tokens;
}

Icon* Icon::createIconFromString(const std::string& s) {
    auto icn = new Icon();

    auto v = geode::utils::string::split(s, ":");

    if (v.size() > 0)
        icn->cube = std::stoi(v[0]);
    if (v.size() > 1)
        icn->ship = std::stoi(v[1]);
    if (v.size() > 2)
        icn->ball = std::stoi(v[2]);
    if (v.size() > 3)
        icn->ufo = std::stoi(v[3]);
    if (v.size() > 4)
        icn->wave = std::stoi(v[4]);
    if (v.size() > 5)
        icn->robot = std::stoi(v[5]);
    if (v.size() > 6)
        icn->spider = std::stoi(v[6]);
    if (v.size() > 7)
        icn->swing = std::stoi(v[7]);
    if (v.size() > 8)
        icn->colour1 = std::stoi(v[8]);
    if (v.size() > 9)
        icn->colour2 = std::stoi(v[9]);
    if (v.size() > 10)
        icn->colour3 = std::stoi(v[10]);
    if (v.size() > 11)
        icn->trail = std::stoi(v[11]);
    if (v.size() > 12)
        icn->glow = static_cast<bool>(std::stoi(v[12]));
    if (v.size() > 13)
        icn->name = v[13];
    if (v.size() > 14)
        icn->jetpack = std::stoi(v[14]);
    if (v.size() > 15)
        icn->hasUploaded = std::stoi(v[15]) == 1 ? true : false;

    return icn;
}

Icon* Icon::createIconFromCurrent() {
    auto icn = new Icon();

    auto gm = GameManager::get();

    icn->cube = gm->m_playerFrame;
    icn->ship = gm->m_playerShip;
    icn->ball = gm->m_playerBall;
    icn->ufo = gm->m_playerBird;
    icn->wave = gm->m_playerDart;
    icn->robot = gm->m_playerRobot;
    icn->spider = gm->m_playerSpider;
    icn->swing = gm->m_playerSwing;
    icn->jetpack = gm->m_playerJetpack;
    icn->colour1 = gm->m_playerColor;
    icn->colour2 = gm->m_playerColor2;
    icn->colour3 = gm->m_playerGlowColor;
    icn->glow = gm->m_playerGlow;
    icn->trail = gm->m_playerStreak;
    icn->deathEffect = gm->m_playerDeathEffect;
    icn->name = "Unnamed Kit";
    //icn->explode = gm->m_

    if (auto moreIcons = geode::Loader::get()->getLoadedMod("hiimjustin000.more_icons")) {
        icn->miCube = moreIcons->getSavedValue<std::string>("icon");
        icn->miShip = moreIcons->getSavedValue<std::string>("ship");
        icn->miBall = moreIcons->getSavedValue<std::string>("ball");
        icn->miUfo = moreIcons->getSavedValue<std::string>("ufo");
        icn->miWave = moreIcons->getSavedValue<std::string>("wave");
        icn->miRobot = moreIcons->getSavedValue<std::string>("robot");
        icn->miSpider = moreIcons->getSavedValue<std::string>("spider");
        icn->miSwing = moreIcons->getSavedValue<std::string>("swing");
        icn->miJetpack = moreIcons->getSavedValue<std::string>("jetpack");
        icn->miTrail = moreIcons->getSavedValue<std::string>("trail");
        icn->miDeathEffect = moreIcons->getSavedValue<std::string>("death");
    }

    return icn;
}

Icon* Icon::createIconFromScore(GJUserScore* gm) {
    auto icn = new Icon();

    icn->cube = gm->m_playerCube;
    icn->ship = gm->m_playerShip;
    icn->ball = gm->m_playerBall;
    icn->ufo = gm->m_playerUfo;
    icn->wave = gm->m_playerWave;
    icn->robot = gm->m_playerRobot;
    icn->spider = gm->m_playerSpider;
    icn->swing = gm->m_playerSwing;
    icn->jetpack = gm->m_playerJetpack;
    icn->colour1 = gm->m_color1;
    icn->colour2 = gm->m_color2;
    icn->colour3 = gm->m_color3;
    icn->glow = gm->m_glowEnabled;
    icn->name = gm->m_userName;

    return icn;
}

Icon* Icon::createIconFromJson(const matjson::Value& js) {
    auto icn = new Icon();

    icn->cube = (int)js["playerCube"].asInt().unwrapOr(1);
    icn->miCube = js["moreIconsCube"].asString().unwrapOr("");
    icn->ship = (int)js["playerShip"].asInt().unwrapOr(1);
    icn->miShip = js["moreIconsShip"].asString().unwrapOr("");
    icn->ball = (int)js["playerBall"].asInt().unwrapOr(1);
    icn->miBall = js["moreIconsBall"].asString().unwrapOr("");
    icn->ufo = (int)js["playerBird"].asInt().unwrapOr(1);
    icn->miUfo = js["moreIconsBird"].asString().unwrapOr("");
    icn->wave = (int)js["playerDart"].asInt().unwrapOr(1);
    icn->miWave = js["moreIconsDart"].asString().unwrapOr("");
    icn->robot = (int)js["playerRobot"].asInt().unwrapOr(1);
    icn->miRobot = js["moreIconsRobot"].asString().unwrapOr("");
    icn->spider = (int)js["playerSpider"].asInt().unwrapOr(1);
    icn->miSpider = js["moreIconsSpider"].asString().unwrapOr("");
    icn->swing = (int)js["playerSwing"].asInt().unwrapOr(1);
    icn->miSwing = js["moreIconsSwing"].asString().unwrapOr("");
    icn->jetpack = (int)js["playerJetpack"].asInt().unwrapOr(1);
    icn->miJetpack = js["moreIconsJetpack"].asString().unwrapOr("");
    icn->trail = (int)js["playerStreak"].asInt().unwrapOr(1);
    icn->miTrail = js["moreIconsStreak"].asString().unwrapOr("");
    icn->deathEffect = (int)js["playerExplosion"].asInt().unwrapOr(1);
    icn->miDeathEffect = js["moreIconsExplosion"].asString().unwrapOr("");
    icn->glow = js["glowEnabled"].asBool().unwrapOr(false);
    icn->colour1 = (int)js["primaryColor"].asInt().unwrapOr(0);
    icn->colour2 = (int)js["secondaryColor"].asInt().unwrapOr(0);
    icn->colour3 = (int)js["glowColor"].asInt().unwrapOr(0);
    icn->name = js["kitName"].asString().unwrapOr("Unnamed Kit");

    if (icn->name.starts_with('"'))
        icn->name = icn->name.substr(1);

    if (icn->name.ends_with('"'))
        icn->name = icn->name.substr(0, icn->name.size() - 1);

    return icn;
}

std::string Icon::saveToString() {
    std::stringstream ss;

    ss << cube;
    ss << ":";
    ss << ship;
    ss << ":";
    ss << ball;
    ss << ":";
    ss << ufo;
    ss << ":";
    ss << wave;
    ss << ":";
    ss << robot;
    ss << ":";
    ss << spider;
    ss << ":";
    ss << swing;
    ss << ":";
    ss << colour1;
    ss << ":";
    ss << colour2;
    ss << ":";
    ss << colour3;
    ss << ":";
    ss << trail;
    ss << ":";
    ss << glow;
    ss << ":";
    ss << name;
    ss << ":";
    ss << jetpack;
    ss << ":";
    ss << (hasUploaded ? 1 : 0);

    return ss.str();
}

matjson::Value Icon::saveToJson() {
    matjson::Value js;

    js["playerCube"] = cube;
    js["moreIconsCube"] = miCube;
    js["playerShip"] = ship;
    js["moreIconsShip"] = miShip;
    js["playerBall"] = ball;
    js["moreIconsBall"] = miBall;
    js["playerBird"] = ufo;
    js["moreIconsBird"] = miUfo;
    js["playerDart"] = wave;
    js["moreIconsDart"] = miWave;
    js["playerRobot"] = robot;
    js["moreIconsRobot"] = miRobot;
    js["playerSpider"] = spider;
    js["moreIconsSpider"] = miSpider;
    js["playerSwing"] = swing;
    js["moreIconsSwing"] = miSwing;
    js["playerJetpack"] = jetpack;
    js["moreIconsJetpack"] = miJetpack;
    js["playerStreak"] = trail;
    js["moreIconsStreak"] = miTrail;
    js["playerExplosion"] = deathEffect;
    js["moreIconsExplosion"] = miDeathEffect;
    js["glowEnabled"] = glow;
    js["primaryColor"] = colour1;
    js["secondaryColor"] = colour2;
    js["glowColor"] = colour3;
    js["kitName"] = name;
    return js;
}

void Icon::addToKit() {
    cocos2d::CCScene::get()->addChild(TextAlertPopup::create("Saved Icon to Icon Kit", 0.5f, 0.6f, 150, ""), 9999999);

    IconSelectLayer::get()->icons.push_back(this);
    IconSelectLayer::get()->refreshIcons();
}

void Icon::applyIcons() {
    auto gm = GameManager::get();
    gm->m_playerFrame = cube;
    gm->m_playerShip = ship;
    gm->m_playerBall = ball;
    gm->m_playerBird = ufo;
    gm->m_playerDart = wave;
    gm->m_playerRobot = robot;
    gm->m_playerSpider = spider;
    gm->m_playerSwing = swing;
    gm->m_playerJetpack = jetpack;
    gm->m_playerColor = colour1;
    gm->m_playerColor2 = colour2;
    gm->m_playerGlowColor = colour3;
    gm->m_playerGlow = glow;
    if (trail > 0) gm->m_playerStreak = trail;
    if (deathEffect > 0) gm->m_playerDeathEffect = deathEffect;

    if (auto moreIcons = geode::Loader::get()->getLoadedMod("hiimjustin000.more_icons")) {
        auto moreIconsSave = moreIcons->getSaveContainer();
        if (moreIconsSave.contains("icon")) moreIcons->setSavedValue("icon", miCube);
        if (moreIconsSave.contains("ship")) moreIcons->setSavedValue("ship", miShip);
        if (moreIconsSave.contains("ball")) moreIcons->setSavedValue("ball", miBall);
        if (moreIconsSave.contains("ufo")) moreIcons->setSavedValue("ufo", miUfo);
        if (moreIconsSave.contains("wave")) moreIcons->setSavedValue("wave", miWave);
        if (moreIconsSave.contains("robot")) moreIcons->setSavedValue("robot", miRobot);
        if (moreIconsSave.contains("spider")) moreIcons->setSavedValue("spider", miSpider);
        if (moreIconsSave.contains("swing")) moreIcons->setSavedValue("swing", miSwing);
        if (moreIconsSave.contains("jetpack")) moreIcons->setSavedValue("jetpack", miJetpack);
        if (moreIconsSave.contains("trail")) moreIcons->setSavedValue("trail", miTrail);
        if (moreIconsSave.contains("death")) moreIcons->setSavedValue("death", miDeathEffect);
    }
}