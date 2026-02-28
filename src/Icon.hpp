#pragma once

class Icon {
public:
    int cube, ship, ball, ufo, wave, robot, spider, swing, colour1, colour2, colour3, trail, jetpack, deathEffect;
    bool glow, explode; // explode (0153) is the shattering effect hope that helps
    // 0060 - Sets player icon in mini mode to default.
    // 0061 - Toggles between main and secondary color for the teleport effect in spider mode.
    // 0062 - Toggles between main and secondary color for the fire effect from dash orbs.
    // 0096 - Toggles between main and secondary color for the trail in wave mode.
    bool miniDefault, invertSpiderTeleportColor, invertFireEffectColor, invertWaveTrailColor;

    std::string name, uploader;
    bool hasUploaded = false;
    int id = 0;
    int accountID = 0;
    std::string miCube, miShip, miBall, miUfo, miWave, miRobot, miSpider, miSwing, miTrail, miJetpack, miDeathEffect;

    static std::vector<std::string> split(const std::string& input, char delimiter);

    static Icon* createIconFromString(const std::string& s);

    static Icon* createIconFromCurrent();

    static Icon* createIconFromScore(GJUserScore* gm);

    static Icon* createIconFromJson(const matjson::Value& js);

    std::string saveToString();

    matjson::Value saveToJson();

    void applyIcons();

    void addToKit();
};
