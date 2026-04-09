#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdbool.h>
#include <stdio.h>

#define BLINK_GPIO GPIO_NUM_2
#define LED_START_CONDITION false

static bool led_state = LED_START_CONDITION;

// Codex generated this function then I perfomed set it up
static void init_blink_gpio(void) {
  const gpio_config_t io_conf = {
      .pin_bit_mask = 1ULL << BLINK_GPIO,
      .mode = GPIO_MODE_OUTPUT,
      .pull_up_en = GPIO_PULLUP_ENABLE,
      .pull_down_en = GPIO_PULLDOWN_DISABLE,
      .intr_type = GPIO_INTR_DISABLE,
  };

  gpio_config(&io_conf);
  gpio_set_level(BLINK_GPIO, led_state);
}

static void toggle_blink_gpio(void) {
  led_state = !led_state;
  gpio_set_level(BLINK_GPIO, led_state);
}

static void blink_task(void *pvParameters) {
  (void)pvParameters;

  while (1) {
    toggle_blink_gpio();
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void app_main(void) {
  init_blink_gpio();
  xTaskCreate(blink_task, "blink_task", 2048, NULL, 5, NULL);
}
