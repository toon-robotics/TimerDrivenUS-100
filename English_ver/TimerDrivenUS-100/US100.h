#ifndef US100_h
#define US100_h

class US100{
    
public:

    enum DATA_MODE{
        DIST,
        TEMP
    };

    US100(unsigned int minDist = 100U, unsigned int maxDist = 2500U);///Minimum and maximum distances as arguments
    ~US100();

    void setup();

    int getDistance();///get distance information
    int getTemperature();///get temperature information

    void requestDistance();///Switch to distance mode before acquiring distance information
    void requestTemperature();///Switch to temperature mode before acquiring temperature information

    static void ISR_timerHandler(void* us100ptr);///Callback for ISR Timer

    static const int TIMER_INTERVAL_MS = 100L;


private:

    unsigned int dist = 0;
    unsigned int minDist, maxDist;

    unsigned int temp = 0;

    DATA_MODE mode = DATA_MODE::DIST;
    bool modeChanged = false;

};

#endif