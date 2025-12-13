#pragma once

// Copyright (c) 2025 Jay Rickaby

class Animation{
public:
    Animation(std::vector<sf::IntRect> givenFrames, float givenFrameTime);
    void update(float deltaTime);
    sf::IntRect getCurrentFrame();
    void reset();

private:
    std::vector<sf::IntRect> frames;
    float frameTime;
    float timer;
    int currentFrame;
};
