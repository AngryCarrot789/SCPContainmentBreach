#ifndef HF_TIMER
#define HF_TIMER

#include <Windows.h>
#include <cstdint>
class Timer {
public:
    static const int TicksPerSecond = 10000000;

    Timer() {
        QueryPerformanceFrequency(&frequency);
    }

    void Start() {
        QueryPerformanceCounter(&t1);
    }

    float Stop() {
        QueryPerformanceCounter(&t2);
        return float(t2.QuadPart - t1.QuadPart) / frequency.QuadPart;
    }

    int64_t GetSystemTicks() {
        QueryPerformanceCounter(&t2);
        return t2.QuadPart;
    }

    int64_t SecondsToTicks(long float s) {
        return int64_t(frequency.QuadPart * s);
    }

    float StopStart() {
        const float result = Stop();
        t1 = t2;
        return result;
    }

    static float SecondsElapsed(int64_t prevTicks, int64_t ticksNow) {
        int64_t tickDiff = ticksNow - prevTicks;
        return float(tickDiff) / float(TicksPerSecond);
    }

private:
    LARGE_INTEGER frequency;        // ticks per second
    LARGE_INTEGER t1, t2;           // ticks
};
#endif