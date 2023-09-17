#ifndef US100_h
#define US100_h

class US100{
    
public:

    enum DATA_MODE{
        DIST,
        TEMP
    };

    US100(unsigned int minDist = 100U, unsigned int maxDist = 2500U);///最小、最大距離を引数に
    ~US100();

    void setup();

    int getDistance();///距離情報を取得
    int getTemperature();///気温情報を取得

    void requestDistance();///距離情報取得前に距離モードに切り替える
    void requestTemperature();///気温情報取得前に気温モードに切り替える

    static void ISR_timerHandler(void* us100ptr);///ISRタイマー用コールバック

    static const int TIMER_INTERVAL_MS = 100L;


private:

    unsigned int dist = 0;
    unsigned int minDist, maxDist;

    unsigned int temp = 0;

    DATA_MODE mode = DATA_MODE::DIST;
    bool modeChanged = false;

};

#endif