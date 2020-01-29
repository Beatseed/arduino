#include <MsTimer2.h>

#define MEASURE_COUNT 50  // время периода измерения
#define R1  30.  // сопротивление резистора R1
#define R2  10 // сопротивление резистора R2
#define ADC_U_COEFF 0.01953125 / MEASURE_COUNT

int timeCount;  // счетчик времени
long  sumU1;  // переменные для суммирования кодов АЦП
long  avarageU1; // сумма кодов АЦП (среднее значение * 500)
boolean flagReady;  // признак готовности данных измерения

void setup() {
  Serial.begin(9600); // инициализируем порт, скорость 9600
  MsTimer2::set(10, timerInterupt); // прерывания по таймеру
  MsTimer2::start();              // разрешение прерывания
}

void loop() {

  if ( flagReady == true ) {
    flagReady= false;
    // пересчет в напряжение и передача на компьютер
    Serial.print("U1 = ");
    Serial.println( (float)avarageU1  * ADC_U_COEFF, 2);
    }
}

void  timerInterupt() {

  timeCount++;  // +1 счетчик выборок усреднения
  sumU1+= analogRead(A0);  // суммирование кодов АЦП
  // проверка числа выборок усреднения
  if ( timeCount >= MEASURE_COUNT ) {
    timeCount= 0;
    avarageU1= sumU1; // перегрузка среднего значения 
    sumU1= 0;
    flagReady= true;  // признак результат измерений готов
    }
}
