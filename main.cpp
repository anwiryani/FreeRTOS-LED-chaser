#include <Arduino.h>

#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

const int led[10] = {13, 12, 14, 27, 26, 25, 18, 17, 16, 15};

void ledON(void *parameter){
  while(1){
    for (int i = 0; i < 10; i++)
    {
      digitalWrite(led[i], HIGH);
      vTaskDelay(500/portTICK_PERIOD_MS);
    }
  }
}

void ledOFF(void *parameter){
  while(1){
    for (int i = 0; i < 10; i++)
    {
      digitalWrite(led[i], LOW);
      vTaskDelay(500/portTICK_PERIOD_MS);
      if(i == 9){
        vTaskDelay(500/portTICK_PERIOD_MS);
      }
    }
  }
}

void setup()
{
  Serial.begin(9600);
  for (int i = 0; i < 10; i++)
  {
    pinMode(led[i], OUTPUT);
    digitalWrite(led[i], LOW);
  }

  xTaskCreatePinnedToCore(
    ledON,
    "led on",
    1024,
    NULL,
    1,
    NULL,
    app_cpu
  );

  xTaskCreatePinnedToCore(
    ledOFF,
    "led off",
    1024,
    NULL,
    1,
    NULL,
    app_cpu
  );
}

void loop()
{

}
