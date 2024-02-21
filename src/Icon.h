#pragma once

std::vector<std::string> split(const std::string& input, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string token;
    
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    
    return tokens;
}

class Icon
{
    public:
        int cube, ship, ball, ufo, wave, robot, spider, swing, colour1, colour2, colour3, trail, jetpack;
        bool glow, explode; // imma be honest i dont know what explode does
        std::string name;
        bool hasUploaded = false;
        int id = 0;
        int accountID = 0;

        static Icon* createIconFromString(std::string s)
        {
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
                icn->glow = as<bool>(std::stoi(v[12]));
            if (v.size() > 13)
                icn->name = v[13];
            if (v.size() > 14)
                icn->jetpack = std::stoi(v[14]);
            if (v.size() > 15)
                icn->hasUploaded = std::stoi(v[15]) == 1 ? true : false;

            return icn;
        }

        static Icon* createIconFromCurrent()
        {
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

        static Icon* createIconFromScore(GJUserScore* gm)
        {
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

        static Icon* createIconFromJson(matjson::Object js)
        {
            auto icn = new Icon();

            icn->id = js["uploadID"].as_int();
            icn->accountID = js["accountID"].as_int();

            icn->cube = js["playerCube"].as_int();
            icn->ship = js["playerShip"].as_int();
            icn->ball = js["playerBall"].as_int();
            icn->ufo = js["playerBird"].as_int();
            icn->wave = js["playerDart"].as_int();
            icn->robot = js["playerRobot"].as_int();
            icn->spider = js["playerSpider"].as_int();
            icn->swing = js["playerSwing"].as_int();
            icn->jetpack = js["playerJetpack"].as_int();
            icn->glow = (js["glowEnabled"].as_int() == 1 ? true : false);
            icn->colour1 = js["primaryColor"].as_int();
            icn->colour2 = js["secondaryColor"].as_int();
            icn->colour3 = js["glowColor"].as_int();
            icn->name = js["kitName"].as_string();

            return icn;
        }

        std::string saveToString()
        {
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
            ss << hasUploaded ? 1 : 0;

            return ss.str();
        }

        void applyIcons()
        {
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

        void addToKit();

};