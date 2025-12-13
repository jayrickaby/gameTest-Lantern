#pragma once

class Animation{

public:
    Animation(std::vector<sf::IntRect> givenFrames, float givenFrameTime);
    //Animation(std::vector<sf::IntRect> frames, float frameTime, bool looping);
    void update(float deltaTime);
    sf::IntRect getCurrentFrame();
    void reset();

private:
    std::vector<sf::IntRect> frames;
    float frameTime;
    float timer;
    int currentFrame;
};
