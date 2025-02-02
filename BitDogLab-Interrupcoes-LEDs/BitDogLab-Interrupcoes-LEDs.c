#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "pico/time.h"
#include <stdio.h>

#define LED_R_PIN       11    // LED RGB - componente vermelho
#define LED_WS2812_PIN  7     // Matriz WS2812
#define BUTTON_A_PIN    5     // Botão A
#define BUTTON_B_PIN    6     // Botão B

#define DEBOUNCE_DELAY_MS 50  // Intervalo de debouncing

volatile int counter = 0;    // Contador de 0 a 9
volatile absolute_time_t last_debounce_a = {0};
volatile absolute_time_t last_debounce_b = {0};

// Stub: atualiza a matriz WS2812 de acordo com o número atual
void update_matrix_display(int num) {
    // Aqui você deve implementar a rotina que converte o número em um padrão
    // para os LEDs da matriz.
    // Por enquanto, apenas imprimimos o número no console.
    printf("Display: %d\n", num);
}

// Callback de interrupção dos botões
void gpio_callback(uint gpio, uint32_t events) {
    if (gpio == BUTTON_A_PIN) {
        absolute_time_t now = get_absolute_time();
        if (absolute_time_diff_us(last_debounce_a, now) > (DEBOUNCE_DELAY_MS * 1000)) {
            counter = (counter + 1) % 10; // Incrementa e volta para 0 após 9
            last_debounce_a = now;
            update_matrix_display(counter);
        }
    } else if (gpio == BUTTON_B_PIN) {
        absolute_time_t now = get_absolute_time();
        if (absolute_time_diff_us(last_debounce_b, now) > (DEBOUNCE_DELAY_MS * 1000)) {
            counter = counter - 1;
            if (counter < 0) {
                counter = 9;
            }
            last_debounce_b = now;
            update_matrix_display(counter);
        }
    }
}

int main() {
    stdio_init_all();
    
    // Inicializa e configura o LED vermelho (LED RGB)
    gpio_init(LED_R_PIN);
    gpio_set_dir(LED_R_PIN, GPIO_OUT);

    // Inicializa os botões com resistor de pull-up interno
    gpio_init(BUTTON_A_PIN);
    gpio_set_dir(BUTTON_A_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_A_PIN);
    
    gpio_init(BUTTON_B_PIN);
    gpio_set_dir(BUTTON_B_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_B_PIN);

    // Configura as interrupções dos botões (edge falling)
    gpio_set_irq_enabled_with_callback(BUTTON_A_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);
    gpio_set_irq_enabled_with_callback(BUTTON_B_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);

    // Inicialização da matriz WS2812 caso necessário
    // ...existing code...

    bool led_state = false;
    uint64_t last_blink_time = to_ms_since_boot(get_absolute_time());

    while (1) {
        // Pisca o LED vermelho a 5 Hz (a cada 100ms)
        uint64_t now = to_ms_since_boot(get_absolute_time());
        if (now - last_blink_time >= 100) {
            led_state = !led_state;
            gpio_put(LED_R_PIN, led_state);
            last_blink_time = now;
        }
        
        // Se desejar atualizar a matriz continuamente, pode chamar a função; 
        // caso contrário, a atualização já ocorre na interrupção.
        // update_matrix_display(counter);

        sleep_ms(10);
    }
    return 0;
}