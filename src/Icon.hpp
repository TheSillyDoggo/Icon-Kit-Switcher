#pragma once

class Icon {
public:
    int cube, ship, ball, ufo, wave, robot, spider, swing, colour1, colour2, colour3, trail, jetpack, deathEffect;
    bool glow, explode; // imma be honest i dont know what explode does
    std::string name, uploader;
    bool hasUploaded = false;
    int id = 0;
    int accountID = 0;

    static std::vector<std::string> split(const std::string& input, char delimiter);

    static Icon* createIconFromString(std::string s);

    static Icon* createIconFromCurrent();

    static Icon* createIconFromScore(GJUserScore* gm);

    static Icon* createIconFromJson(matjson::Object js);

    std::string saveToString();

    void applyIcons();

    void addToKit();
};