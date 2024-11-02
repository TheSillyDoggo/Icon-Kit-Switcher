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

    icn->cube = js.contains("playerCube") && js["playerCube"].is_number() ? js["playerCube"].as_int() : 1;
    icn->miCube = js.contains("moreIconsCube") && js["moreIconsCube"].is_string() ? js["moreIconsCube"].as_string() : "";
    icn->ship = js.contains("playerShip") && js["playerShip"].is_number() ? js["playerShip"].as_int() : 1;
    icn->miShip = js.contains("moreIconsShip") && js["moreIconsShip"].is_string() ? js["moreIconsShip"].as_string() : "";
    icn->ball = js.contains("playerBall") && js["playerBall"].is_number() ? js["playerBall"].as_int() : 1;
    icn->miBall = js.contains("moreIconsBall") && js["moreIconsBall"].is_string() ? js["moreIconsBall"].as_string() : "";
    icn->ufo = js.contains("playerBird") && js["playerBird"].is_number() ? js["playerBird"].as_int() : 1;
    icn->miUfo = js.contains("moreIconsBird") && js["moreIconsBird"].is_string() ? js["moreIconsBird"].as_string() : "";
    icn->wave = js.contains("playerDart") && js["playerDart"].is_number() ? js["playerDart"].as_int() : 1;
    icn->miWave = js.contains("moreIconsDart") && js["moreIconsDart"].is_string() ? js["moreIconsDart"].as_string() : "";
    icn->robot = js.contains("playerRobot") && js["playerRobot"].is_number() ? js["playerRobot"].as_int() : 1;
    icn->miRobot = js.contains("moreIconsRobot") && js["moreIconsRobot"].is_string() ? js["moreIconsRobot"].as_string() : "";
    icn->spider = js.contains("playerSpider") && js["playerSpider"].is_number() ? js["playerSpider"].as_int() : 1;
    icn->miSpider = js.contains("moreIconsSpider") && js["moreIconsSpider"].is_string() ? js["moreIconsSpider"].as_string() : "";
    icn->swing = js.contains("playerSwing") && js["playerSwing"].is_number() ? js["playerSwing"].as_int() : 1;
    icn->miSwing = js.contains("moreIconsSwing") && js["moreIconsSwing"].is_string() ? js["moreIconsSwing"].as_string() : "";
    icn->jetpack = js.contains("playerJetpack") && js["playerJetpack"].is_number() ? js["playerJetpack"].as_int() : 1;
    icn->miJetpack = js.contains("moreIconsJetpack") && js["moreIconsJetpack"].is_string() ? js["moreIconsJetpack"].as_string() : "";
    icn->trail = js.contains("playerStreak") && js["playerStreak"].is_number() ? js["playerStreak"].as_int() : 1;
    icn->miTrail = js.contains("moreIconsStreak") && js["moreIconsStreak"].is_string() ? js["moreIconsStreak"].as_string() : "";
    icn->deathEffect = js.contains("playerExplosion") && js["playerExplosion"].is_number() ? js["playerExplosion"].as_int() : 1;
    icn->miDeathEffect = js.contains("moreIconsExplosion") && js["moreIconsExplosion"].is_string() ? js["moreIconsExplosion"].as_string() : "";
    icn->glow = js.contains("glowEnabled") && js["glowEnabled"].is_bool() ? js["glowEnabled"].as_bool() : false;
    icn->colour1 = js.contains("primaryColor") && js["primaryColor"].is_number() ? js["primaryColor"].as_int() : 0;
    icn->colour2 = js.contains("secondaryColor") && js["secondaryColor"].is_number() ? js["secondaryColor"].as_int() : 0;
    icn->colour3 = js.contains("glowColor") && js["glowColor"].is_number() ? js["glowColor"].as_int() : 0;
    icn->name = js.contains("kitName") && js["kitName"].is_string() ? js["kitName"].as_string() : "Unnamed Kit";

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

matjson::Object Icon::saveToJson() {
    matjson::Object js;

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