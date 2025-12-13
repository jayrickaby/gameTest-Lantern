#include <SFML/Graphics.hpp>
#include "animation.h"

// Copyright (c) 2025 Jay Rickaby

Animation::Animation(std::vector<sf::IntRect> givenFrames, float givenFrameTime){
    frames = givenFrames;
    frameTime = givenFrameTime;
}

void Animation::update(float deltaTime){
    timer += deltaTime;
    if (timer >= frameTime){
        timer = 0.f;
        currentFrame = (currentFrame + 1) % frames.size();
    }
}

void Animation::reset(){
    currentFrame = 0;
}

sf::IntRect Animation::getCurrentFrame() {
    return frames[currentFrame];
}




