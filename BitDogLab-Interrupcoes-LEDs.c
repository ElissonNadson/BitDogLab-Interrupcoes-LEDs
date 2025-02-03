#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "pico/time.h"
#include <stdio.h>
#include "ws2812.h" // Adicione esta linha

#define LED_WS2812_PIN 7
#define BOTAO_A_PIN    5
#define BOTAO_B_PIN    6
#define DEBOUNCE_DELAY_MS 200
#define NUM_PIXELS 25

// Matriz de números para exibição
const double numeros[10][NUM_PIXELS] = {
    // Numero 0
    {0.0, 1.0, 1.0, 1.0, 0.0,
     1.0, 1.0, 0.0, 0.0, 1.0,
     1.0, 0.0, 1.0, 0.0, 1.0,
     1.0, 0.0, 0.0, 1.0, 1.0,
     0.0, 1.0, 1.0, 1.0, 0.0},
    // Numero 1
    {0.0, 0.0, 1.0, 0.0, 0.0,
     0.0, 1.0, 1.0, 0.0, 0.0,
     0.0, 0.0, 1.0, 0.0, 0.0,
     0.0, 0.0, 1.0, 0.0, 0.0,
     0.0, 1.0, 1.0, 1.0, 0.0},
    // Numero 2
    {0.0, 1.0, 1.0, 1.0, 0.0,
     0.0, 0.0, 0.0, 1.0, 0.0,
     0.0, 1.0, 1.0, 1.0, 0.0,
     0.0, 1.0, 0.0, 0.0, 0.0,
     0.0, 1.0, 1.0, 1.0, 0.0},
    // Numero 3
    {0.0, 1.0, 1.0, 1.0, 0.0,
     0.0, 0.0, 0.0, 1.0, 0.0,
     0.0, 1.0, 1.0, 1.0, 0.0,
     0.0, 0.0, 0.0, 1.0, 0.0,
     0.0, 1.0, 1.0, 1.0, 0.0},
    // Numero 4
    {0.0, 0.0, 0.0, 1.0, 0.0,
     0.0, 0.0, 1.0, 1.0, 0.0,
     0.0, 1.0, 0.0, 1.0, 0.0,
     1.0, 1.0, 1.0, 1.0, 1.0,
     0.0, 0.0, 0.0, 1.0, 0.0},
    // Numero 5
    {0.0, 1.0, 1.0, 1.0, 0.0,
     0.0, 1.0, 0.0, 0.0, 0.0,
     0.0, 1.0, 1.0, 1.0, 0.0,
     0.0, 0.0, 0.0, 1.0, 0.0,
     0.0, 1.0, 1.0, 1.0, 0.0},
    // Numero 6
    {0.0, 1.0, 1.0, 1.0, 0.0,
     0.0, 1.0, 0.0, 0.0, 0.0,
     0.0, 1.0, 1.0, 1.0, 0.0,
     0.0, 1.0, 0.0, 1.0, 0.0,
     0.0, 1.0, 1.0, 1.0, 0.0},
    // Numero 7
    {0.0, 1.0, 1.0, 1.0, 0.0,
     0.0, 0.0, 0.0, 1.0, 0.0,
     0.0, 0.0, 1.0, 0.0, 0.0,
     0.0, 1.0, 0.0, 0.0, 0.0,
     1.0, 1.0, 1.0, 1.0, 1.0},
    // Numero 8
    {0.0, 1.0, 1.0, 1.0, 0.0,
     0.0, 1.0, 0.0, 1.0, 0.0,
     0.0, 1.0, 1.0, 1.0, 0.0,
     0.0, 1.0, 0.0, 1.0, 0.0,
     0.0, 1.0, 1.0, 1.0, 0.0},
    // Numero 9
    {0.0, 1.0, 1.0, 1.0, 0.0,
     0.0, 1.0, 0.0, 1.0, 0.0,
     0.0, 1.0, 1.0, 1.0, 0.0,
     0.0, 0.0, 0.0, 1.0, 0.0,
     0.0, 1.0, 1.0, 1.0, 0.0}
};

volatile int contador = 0;
volatile absolute_time_t ultimo_debounce_a = {0};
volatile absolute_time_t ultimo_debounce_b = {0};

void atualizar_display_matriz(int numero) {
    printf("Exibindo número: %d\n", numero);
    for (int i = 0; i < NUM_PIXELS; i++) {
        if (numeros[numero][i]) {
            ws2812_set_pixel(i, 255, 255, 255); // Branco
        } else {
            ws2812_set_pixel(i, 0, 0, 0); // Desligado
        }
    }
    ws2812_show();
}

void tratar_interrupcao_botao(uint gpio, uint32_t eventos) {
    absolute_time_t agora = get_absolute_time();
    if (gpio == BOTAO_A_PIN) {
        if (absolute_time_diff_us(ultimo_debounce_a, agora) > (DEBOUNCE_DELAY_MS * 1000)) {
            contador = (contador + 1) % 10;
            ultimo_debounce_a = agora;
            atualizar_display_matriz(contador);
        }
    } else if (gpio == BOTAO_B_PIN) {
        if (absolute_time_diff_us(ultimo_debounce_b, agora) > (DEBOUNCE_DELAY_MS * 1000)) {
            contador = (contador - 1 + 10) % 10;
            ultimo_debounce_b = agora;
            atualizar_display_matriz(contador);
        }
    }
}

int main() {
    stdio_init_all();
    ws2812_init(LED_WS2812_PIN);
    atualizar_display_matriz(contador);
    
    gpio_init(BOTAO_A_PIN);
    gpio_set_dir(BOTAO_A_PIN, GPIO_IN);
    gpio_pull_up(BOTAO_A_PIN);
    gpio_init(BOTAO_B_PIN);
    gpio_set_dir(BOTAO_B_PIN, GPIO_IN);
    gpio_pull_up(BOTAO_B_PIN);
    
    gpio_set_irq_enabled_with_callback(BOTAO_A_PIN, GPIO_IRQ_EDGE_FALL, true, &tratar_interrupcao_botao);
    gpio_set_irq_enabled_with_callback(BOTAO_B_PIN, GPIO_IRQ_EDGE_FALL, true, &tratar_interrupcao_botao);
    
    while (1) {
        sleep_ms(10);
    }
    return 0;
}
