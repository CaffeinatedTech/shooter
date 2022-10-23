#ifndef SHOOTER_ENEMYLOADER_HPP
#define SHOOTER_ENEMYLOADER_HPP

#include "enemy.hpp"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <filesystem>
#include <vector>

namespace pt = boost::property_tree;

using namespace std;

class EnemyLoader {
private:
    vector<enemyConfig> enemyConfigs;

public:
    EnemyLoader();

    void loadEnemyConfigs();
    vector<enemyConfig> getEnemyConfigs();
};


#endif //SHOOTER_ENEMYLOADER_HPP
