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
    
    auto gameManager = GameManager::get();
    auto separateDualIcons = geode::Loader::get()->getLoadedMod("weebify.separate_dual_icons");
    auto dualSelected = separateDualIcons && separateDualIcons->getSavedValue("2pselected", false);
    icn->explode = dualSelected ? separateDualIcons->getSavedValue("deathexplode", false) : gameManager->getGameVariable("0153");
    icn->miniDefault = gm->getGameVariable("0060");
    icn->invertSpiderTeleportColor = gm->getGameVariable("0061");
    icn->invertFireEffectColor = gm->getGameVariable("0062");
    icn->invertWaveTrailColor = gm->getGameVariable("0096");

    return icn;
}

Icon* Icon::createIconFromCurrent() {
    auto icn = new Icon();

    auto gm = GameManager::get();

    auto separateDualIcons = geode::Loader::get()->getLoadedMod("weebify.separate_dual_icons");
    auto dualSelected = separateDualIcons && separateDualIcons->getSavedValue("2pselected", false);
    icn->cube = dualSelected ? separateDualIcons->getSavedValue("cube", 1) : gm->m_playerFrame;
    icn->ship = dualSelected ? separateDualIcons->getSavedValue("ship", 1) : gm->m_playerShip;
    icn->ball = dualSelected ? separateDualIcons->getSavedValue("roll", 1) : gm->m_playerBall;
    icn->ufo = dualSelected ? separateDualIcons->getSavedValue("bird", 1) : gm->m_playerBird;
    icn->wave = dualSelected ? separateDualIcons->getSavedValue("dart", 1) : gm->m_playerDart;
    icn->robot = dualSelected ? separateDualIcons->getSavedValue("robot", 1) : gm->m_playerRobot;
    icn->spider = dualSelected ? separateDualIcons->getSavedValue("spider", 1) : gm->m_playerSpider;
    icn->swing = dualSelected ? separateDualIcons->getSavedValue("swing", 1) : gm->m_playerSwing;
    icn->jetpack = dualSelected ? separateDualIcons->getSavedValue("jetpack", 1) : gm->m_playerJetpack;
    icn->colour1 = dualSelected ? separateDualIcons->getSavedValue("color1", 0) : gm->m_playerColor;
    icn->colour2 = dualSelected ? separateDualIcons->getSavedValue("color2", 0) : gm->m_playerColor2;
    icn->colour3 = dualSelected ? separateDualIcons->getSavedValue("colorglow", 0) : gm->m_playerGlowColor;
    icn->glow = dualSelected ? separateDualIcons->getSavedValue("glow", false) : gm->m_playerGlow;
    icn->trail = dualSelected ? separateDualIcons->getSavedValue("trail", 1) : gm->m_playerStreak;
    icn->deathEffect = dualSelected ? separateDualIcons->getSavedValue("death", 1) : gm->m_playerDeathEffect;
    icn->name = "Unnamed Kit";
    icn->explode = dualSelected ? separateDualIcons->getSavedValue("deathexplode", false) : gm->getGameVariable("0153");
    // separate dual icons does not affect these, it probably should but oh well
    icn->miniDefault = gm->getGameVariable("0060");
    icn->invertSpiderTeleportColor = gm->getGameVariable("0061");
    icn->invertFireEffectColor = gm->getGameVariable("0062");
    icn->invertWaveTrailColor = gm->getGameVariable("0096");

    if (auto moreIcons = geode::Loader::get()->getLoadedMod("hiimjustin000.more_icons")) {
        icn->miCube = moreIcons->getSavedValue<std::string>(dualSelected ? "icon-dual" : "icon");
        icn->miShip = moreIcons->getSavedValue<std::string>(dualSelected ? "ship-dual" : "ship");
        icn->miBall = moreIcons->getSavedValue<std::string>(dualSelected ? "ball-dual" : "ball");
        icn->miUfo = moreIcons->getSavedValue<std::string>(dualSelected ? "ufo-dual" : "ufo");
        icn->miWave = moreIcons->getSavedValue<std::string>(dualSelected ? "wave-dual" : "wave");
        icn->miRobot = moreIcons->getSavedValue<std::string>(dualSelected ? "robot-dual" : "robot");
        icn->miSpider = moreIcons->getSavedValue<std::string>(dualSelected ? "spider-dual" : "spider");
        icn->miSwing = moreIcons->getSavedValue<std::string>(dualSelected ? "swing-dual" : "swing");
        icn->miJetpack = moreIcons->getSavedValue<std::string>(dualSelected ? "jetpack-dual" : "jetpack");
        icn->miTrail = moreIcons->getSavedValue<std::string>(dualSelected ? "trail-dual" : "trail");
        icn->miDeathEffect = moreIcons->getSavedValue<std::string>(dualSelected ? "death-dual" : "death");
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

    auto gameManager = GameManager::get();
    auto separateDualIcons = geode::Loader::get()->getLoadedMod("weebify.separate_dual_icons");
    auto dualSelected = separateDualIcons && separateDualIcons->getSavedValue("2pselected", false);
    // you can't get these from a user, keep them the same as the current ones
    icn->explode = dualSelected ? separateDualIcons->getSavedValue("deathexplode", false) : gameManager->getGameVariable("0153");
    icn->miniDefault = gameManager->getGameVariable("0060");
    icn->invertSpiderTeleportColor = gameManager->getGameVariable("0061");
    icn->invertFireEffectColor = gameManager->getGameVariable("0062");
    icn->invertWaveTrailColor = gameManager->getGameVariable("0096");

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
    
    auto gameManager = GameManager::get();
    auto separateDualIcons = geode::Loader::get()->getLoadedMod("weebify.separate_dual_icons");
    auto dualSelected = separateDualIcons && separateDualIcons->getSavedValue("2pselected", false);
    
    // these may not exist due to prior updates, if they don't, set them to the current game variables to not mess anything up
    icn->explode = js.get<bool>("deathEffectExplode").unwrapOr(
      dualSelected ? separateDualIcons->getSavedValue("deathexplode", false) : gameManager->getGameVariable("0153")
    );
    icn->miniDefault = js.get<bool>("miniDefault").unwrapOr(gameManager->getGameVariable("060"));
    icn->invertSpiderTeleportColor = js.get<bool>("invertSpiderTeleportColor").unwrapOr(gameManager->getGameVariable("0061"));
    icn->invertFireEffectColor = js.get<bool>("invertFireEffectColor").unwrapOr(gameManager->getGameVariable("0062"));
    icn->invertWaveTrailColor = js.get<bool>("invertWaveTrailColor").unwrapOr(gameManager->getGameVariable("0096"));

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
    js["deathEffectExplode"] = explode;
    js["miniDefault"] = miniDefault;
    js["invertSpiderTeleportColor"] = invertSpiderTeleportColor;
    js["invertFireEffectColor"] = invertFireEffectColor;
    js["invertWaveTrailColor"] = invertWaveTrailColor;
    return js;
}

void Icon::addToKit() {
    cocos2d::CCScene::get()->addChild(TextAlertPopup::create("Saved Icon to Icon Kit", 0.5f, 0.6f, 150, ""), 9999999);

    IconSelectLayer::get()->icons.push_back(this);
    IconSelectLayer::get()->refreshIcons();
}

void Icon::applyIcons() {
    auto separateDualIcons = geode::Loader::get()->getLoadedMod("weebify.separate_dual_icons");
    auto dualSelected = separateDualIcons && separateDualIcons->getSavedValue("2pselected", false);
    auto gm = GameManager::get();
    if (dualSelected) {
        separateDualIcons->setSavedValue("cube", cube);
        separateDualIcons->setSavedValue("ship", ship);
        separateDualIcons->setSavedValue("roll", ball);
        separateDualIcons->setSavedValue("bird", ufo);
        separateDualIcons->setSavedValue("dart", wave);
        separateDualIcons->setSavedValue("robot", robot);
        separateDualIcons->setSavedValue("spider", spider);
        separateDualIcons->setSavedValue("swing", swing);
        separateDualIcons->setSavedValue("jetpack", jetpack);
        separateDualIcons->setSavedValue("color1", colour1);
        separateDualIcons->setSavedValue("color2", colour2);
        separateDualIcons->setSavedValue("colorglow", colour3);
        separateDualIcons->setSavedValue("glow", glow);
        separateDualIcons->setSavedValue("deathexplode", explode);
        if (trail > 0) separateDualIcons->setSavedValue("trail", trail);
        if (deathEffect > 0) separateDualIcons->setSavedValue("death", deathEffect);

        if (auto moreIcons = geode::Loader::get()->getLoadedMod("hiimjustin000.more_icons")) {
            auto moreIconsSave = moreIcons->getSaveContainer();
            if (moreIconsSave.contains("icon-dual")) moreIcons->setSavedValue("icon-dual", miCube);
            if (moreIconsSave.contains("ship-dual")) moreIcons->setSavedValue("ship-dual", miShip);
            if (moreIconsSave.contains("ball-dual")) moreIcons->setSavedValue("ball-dual", miBall);
            if (moreIconsSave.contains("ufo-dual")) moreIcons->setSavedValue("ufo-dual", miUfo);
            if (moreIconsSave.contains("wave-dual")) moreIcons->setSavedValue("wave-dual", miWave);
            if (moreIconsSave.contains("robot-dual")) moreIcons->setSavedValue("robot-dual", miRobot);
            if (moreIconsSave.contains("spider-dual")) moreIcons->setSavedValue("spider-dual", miSpider);
            if (moreIconsSave.contains("swing-dual")) moreIcons->setSavedValue("swing-dual", miSwing);
            if (moreIconsSave.contains("jetpack-dual")) moreIcons->setSavedValue("jetpack-dual", miJetpack);
            if (moreIconsSave.contains("trail-dual")) moreIcons->setSavedValue("trail-dual", miTrail);
            if (moreIconsSave.contains("death-dual")) moreIcons->setSavedValue("death-dual", miDeathEffect);
        }
    }
    else {
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
        gm->setGameVariable("0153", explode);

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
    // since separate dual icons does not affect these, they get set in GameManager regardless 
    gm->setGameVariable("0060", miniDefault);
    gm->setGameVariable("0061", invertSpiderTeleportColor);
    gm->setGameVariable("0062", invertFireEffectColor);
    gm->setGameVariable("0096", invertWaveTrailColor);
}
