#include "US100.h"

///Arduino Leonardoを想定

///タイマーを利用する際に必要
#define USE_TIMER_3 true

#include "TimerInterrupt_Generic.h"
#include "ISR_Timer_Generic.h"

ISR_Timer ISR_timer;///ISRタイマー

static const unsigned long HARDWARE_TIMER_INTERVAL_MS = 5UL;

///US-100
US100* us100;

///ISRタイマーを利用するためのハードウェアタイマー用コールバック関数
void timerHandler(){
  ISR_timer.run();
}

void setup() {

  Serial.begin(9600);///シリアルモニターに表示するためのシリアル通信開始

  us100 = new US100(20,4500);///US-100の作成。引数は最小距離と最大距離（指定しない場合デフォルト値が入る）
  us100->setup();///セットアップ開始

  ITimer3.init();///ハードウェアタイマー初期化

  // ISRタイマー実行のためのハードウェアタイマーの設定(TimerInterrupt_Genericのサンプルコード参照)
  if (ITimer3.attachInterruptInterval(HARDWARE_TIMER_INTERVAL_MS, timerHandler))
  {
    Serial.print(F("Starting  ITimer3 OK, millis() = ")); 
    Serial.println(millis());
  }
  else{
    Serial.println(F("Can't set ITimer3. Select another freq. or timer"));
  }

  ///ISRタイマーの実行間隔とコールバック関数を設定
  ISR_timer.setInterval(US100::TIMER_INTERVAL_MS, US100::ISR_timerHandler, us100);

}


void loop() {

  int dist = us100->getDistance();
        
  Serial.print("Distance: ");
  Serial.print(dist);
  Serial.println("mm");

  delay(100);

}