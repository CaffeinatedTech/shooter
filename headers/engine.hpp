#ifndef SHOOTER_ENGINE_HPP
#define SHOOTER_ENGINE_HPP

#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;

class Engine {
private:
    //TextureHolder th;

    Vector2f resolution;
    int levelWidth;

    const unsigned int FPS = 60;
    static const Time TimePerFrame;
    Time runningTime;
    Time waveTime;
    int intermissionTime; // Number of seconds between waves.
    Time intermissionRunningTime;

    int waveKills;
    long long unsigned int waveScore;

    RenderWindow window;

    View mainView;

public:
    Engine();

    void update(Time dt);
    void draw();

    // The main loop will be in the run function
    void run();

};


#endif //SHOOTER_ENGINE_HPP
