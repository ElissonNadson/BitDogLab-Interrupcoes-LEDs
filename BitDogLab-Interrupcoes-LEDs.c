#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "pico/time.h"
#include <stdio.h>

// Nomes claros e descritivos para os pinos
#define LED_VERMELHO_PIN       11    // LED RGB - componente vermelho
#define LED_WS2812_PIN         7     // Matriz WS2812
#define BOTAO_A_PIN            5     // Botão A
#define BOTAO_B_PIN            6     // Botão B

#define DEBOUNCE_DELAY_MS 50  // Intervalo de debouncing

// Variáveis globais com nomes autoexplicativos
volatile int contador = 0;                   
volatile absolute_time_t ultimo_debounce_a = {0};
volatile absolute_time_t ultimo_debounce_b = {0};

// Função para atualizar o display da matriz WS2812 conforme o número
void atualizar_display_matriz(int numero) {
    // Conversão do número para o padrão visual desejado na matriz
    printf("Exibindo número: %d\n", numero);
}

// Função de tratamento de interrupção dos botões
void tratar_interrupcao_botao(uint gpio, uint32_t eventos) {
    if (gpio == BOTAO_A_PIN) {
        absolute_time_t agora = get_absolute_time();
        if (absolute_time_diff_us(ultimo_debounce_a, agora) > (DEBOUNCE_DELAY_MS * 1000)) {
            contador = (contador + 1) % 10;
            ultimo_debounce_a = agora;
            atualizar_display_matriz(contador);
        }
    } else if (gpio == BOTAO_B_PIN) {
        absolute_time_t agora = get_absolute_time();
        if (absolute_time_diff_us(ultimo_debounce_b, agora) > (DEBOUNCE_DELAY_MS * 1000)) {
            contador = contador - 1;
            if (contador < 0) {
                contador = 9;
            }
            ultimo_debounce_b = agora;
            atualizar_display_matriz(contador);
        }
    }
}

int main() {
    stdio_init_all();
    
    // Inicializa e configura o LED vermelho (LED RGB)
    gpio_init(LED_VERMELHO_PIN);
    gpio_set_dir(LED_VERMELHO_PIN, GPIO_OUT);

    // Inicializa os botões com resistor de pull-up interno
    gpio_init(BOTAO_A_PIN);
    gpio_set_dir(BOTAO_A_PIN, GPIO_IN);
    gpio_pull_up(BOTAO_A_PIN);
    
    gpio_init(BOTAO_B_PIN);
    gpio_set_dir(BOTAO_B_PIN, GPIO_IN);
    gpio_pull_up(BOTAO_B_PIN);

    // Configura as interrupções dos botões (borda de descida)
    gpio_set_irq_enabled_with_callback(BOTAO_A_PIN, GPIO_IRQ_EDGE_FALL, true, &tratar_interrupcao_botao);
    gpio_set_irq_enabled_with_callback(BOTAO_B_PIN, GPIO_IRQ_EDGE_FALL, true, &tratar_interrupcao_botao);

    // Inicialização da matriz WS2812, se necessário
    // ...existing code...

    bool led_estado = false;
    uint64_t tempo_ultimo_blink = to_ms_since_boot(get_absolute_time());

    while (1) {
        uint64_t agora = to_ms_since_boot(get_absolute_time());
        if (agora - tempo_ultimo_blink >= 100) {
            led_estado = !led_estado;
            gpio_put(LED_VERMELHO_PIN, led_estado);
            tempo_ultimo_blink = agora;
        }
        
        // Se desejar atualizar a matriz continuamente, pode chamar a função; 
        // caso contrário, a atualização já ocorre na interrupção.
        // atualizar_display_matriz(contador);

        sleep_ms(10);
    }
    return 0;
}