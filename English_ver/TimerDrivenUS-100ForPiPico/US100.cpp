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

    if(us100->mode == US100::DATA_MODE::DIST){///distance mode
        if (Serial1.available() >= 2)
        {
            ///US-100 returns distance as 16-bit unsigned integer in UART mode.The unit is mm.
            unsigned int msb = 0;
            unsigned int lsb = 0;

            msb = Serial1.read();
            lsb = Serial1.read();
            unsigned int distance = msb * 256 + lsb;///Extract information as 2-byte unsigned int
            if((us100->minDist <= distance) && (distance <= us100->maxDist)){///It is considered a normal measurement if it is within the set range.
                us100->dist = distance;
            }else{
                ///If it is out of range, the distance is set to 0 as it is an inappropriate value.
                us100->dist = 0;
            }
        }

        Serial1.flush();
        Serial1.write(0x55);///Send 0x55 when acquiring distance

    }else{///temperature mode
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
    Serial1.begin(9600);///Communicates with US-100 at a baud rate of 9600
}