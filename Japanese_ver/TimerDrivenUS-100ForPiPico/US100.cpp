#include <Arduino.h>
#include "US100.h"

int US100::getDistance()
{
    return this->dist;
}

int US100::getTemperature()
{
    return this->temp;
}

void US100::requestDistance()
{
    this->mode = US100::DATA_MODE::DIST;
    this->modeChanged = true;
}

void US100::requestTemperature()
{
    this->mode = US100::DATA_MODE::TEMP;
    this->modeChanged = true;
}

void US100::ISR_timerHandler(void *us100ptr)
{
    US100 *us100 = (US100 *)us100ptr;

    if(us100->modeChanged){

        while(Serial1.available()){
            Serial1.read();
        }

        us100->modeChanged = false;

    }

    if(us100->mode == US100::DATA_MODE::DIST){///距離モード
        if (Serial1.available() >= 2)
        {
            ///the value is retured as 16 bit unsigned int as millimeter
            ///US-100はUARTモードでは16bitの符号なし整数で距離を返す
            unsigned int msb = 0;
            unsigned int lsb = 0;

            msb = Serial1.read();
            lsb = Serial1.read();
            unsigned int distance = msb * 256 + lsb;///2byteのunsigned intとして情報を抽出
            if((us100->minDist <= distance) && (distance <= us100->maxDist)){///設定された範囲内ならば正常な測定
                us100->dist = distance;
            }else{
                ///範囲外ならば不適切な値であるとして距離を0とする
                us100->dist = 0;///assuming distance value is invalid 
            }
        }

        Serial1.flush();
        Serial1.write(0x55);///距離取得時は0x55を送信

    }else{///気温モード
        if(Serial1.available() >= 1){
            unsigned int temperature = Serial1.read() - 45U;
            us100->temp = temperature;
        }
        Serial1.flush();
        Serial1.write(0x50);
    }
}

US100::US100(unsigned int minDist, unsigned int maxDist)
{
    this->minDist = minDist;
    this->maxDist = maxDist;

}

US100::~US100()
{
}

void US100::setup()
{
    Serial1.begin(9600);///US-100とはbaud rate 9600で通信
}