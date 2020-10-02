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

    RenderWindow window;
    View mainView;
    const unsigned int FPS = 60;
    static const Time TimePerFrame;

    Font mainFont;
    Text scoreText;
    unsigned long long int displayedScore;

    Time runningTime;
    Time waveTime;
    int intermissionTime; // Number of seconds between waves.
    Time intermissionRunningTime;

    int waveKills;
    long long unsigned int waveScore;

    int gameState;
    int previousGameState;


public:
    enum STATE { RUNNING, PAUSED, INTERMISSION, GAMEOVER, TITLE };
    Engine();

    void input();
    void update(Time dt);
    void draw();

    // The main loop will be in the run function
    void run();

    int getGameState();
    void setGameState(int newGameState);

    void togglePause();

    void setupFont(Text *textItem, const Font &font, const String &value, int size, Color colour);

};


#endif //SHOOTER_ENGINE_HPP
