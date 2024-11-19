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

Icon* Icon::createIconFromString(std::string s) {
    auto icn = new Icon();

    auto v = split(s, ':');

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
    icn->name = "Unnamed Kit";
    //icn->explode = gm->m_

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

Icon* Icon::createIconFromJson(matjson::Value js) {
    auto icn = new Icon();

    icn->id = js["uploadID"].asInt().unwrap();
    icn->accountID = js["accountID"].asInt().unwrap();

    icn->cube = js["playerCube"].asInt().unwrap();
    icn->ship = js["playerShip"].asInt().unwrap();
    icn->ball = js["playerBall"].asInt().unwrap();
    icn->ufo = js["playerBird"].asInt().unwrap();
    icn->wave = js["playerDart"].asInt().unwrap();
    icn->robot = js["playerRobot"].asInt().unwrap();
    icn->spider = js["playerSpider"].asInt().unwrap();
    icn->swing = js["playerSwing"].asInt().unwrap();
    icn->jetpack = js["playerJetpack"].asInt().unwrap();
    icn->glow = (js["glowEnabled"].asInt().unwrap() == 1 ? true : false);
    icn->colour1 = js["primaryColor"].asInt().unwrap();
    icn->colour2 = js["secondaryColor"].asInt().unwrap();
    icn->colour3 = js["glowColor"].asInt().unwrap();
    icn->name = js["kitName"].asString().unwrap();
    icn->uploader = js["uploaderName"].asString().unwrap();

    if (icn->name.starts_with('"'))
        icn->name = icn->name.substr(1);

    if (icn->name.ends_with('"'))
        icn->name = icn->name.substr(0, icn->name.size() - 1);

    if (icn->uploader.starts_with('"'))
        icn->uploader = icn->uploader.substr(1);

    if (icn->uploader.ends_with('"'))
        icn->uploader = icn->uploader.substr(0, icn->uploader.size() - 1);

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
    gm->m_playerStreak = trail;
}