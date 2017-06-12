#ifndef VOXELSENGINE_TIMER_HPP
#define VOXELSENGINE_TIMER_HPP

#include <chrono>


struct Timer
{
    using Clock = std::chrono::high_resolution_clock;
    using MilliSeconds = std::chrono::milliseconds;

    void init();
    double getTime();
    float getDelta();
    void updateFPS();
    void updateUPS();
    void update();
    int getFPS();
    int getUPS();

private:

    double lastLoopTime_;
    float timeCount_;
    int fps_;
    int fpsCount_;
    int ups_;
    int upsCount_;
};


#endif //VOXELSENGINE_TIMER_HPP
