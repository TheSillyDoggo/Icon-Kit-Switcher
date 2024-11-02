#pragma once

class Icon {
public:
    int cube, ship, ball, ufo, wave, robot, spider, swing, colour1, colour2, colour3, trail, jetpack, deathEffect;
    bool glow, explode; // explode is the shattering effect hope that helps
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

    matjson::Object saveToJson();

    void applyIcons();

    void addToKit();
};