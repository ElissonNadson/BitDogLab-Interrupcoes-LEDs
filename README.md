# 🚀 BitDogLab - Interrupções e LEDs  

Este projeto explora o uso de interrupções no microcontrolador **RP2040** utilizando a placa de desenvolvimento **BitDogLab**. O objetivo é controlar LEDs comuns e LEDs endereçáveis **WS2812**, além de implementar o **debouncing** via software para botões de entrada.  

## 🎯 Objetivos  
- Compreender o funcionamento e a aplicação de interrupções em microcontroladores.  
- Implementar **debouncing** para evitar múltiplas leituras ao pressionar botões.  
- Controlar LEDs RGB e uma matriz de LEDs **WS2812**.  
- Utilizar **resistores de pull-up internos** nos botões.  
- Desenvolver um projeto funcional integrando hardware e software.  

## 🛠 Componentes Utilizados  
Os seguintes componentes estão conectados à placa **BitDogLab**:  

| Componente | Conexão |
|------------|---------|
| **Matriz 5x5 WS2812** | GPIO 7 |
| **LED RGB** (Vermelho, Verde, Azul) | GPIOs 11, 12, 13 |
| **Botão A** | GPIO 5 |
| **Botão B** | GPIO 6 |

## ✨ Funcionalidades Implementadas  
1. **LED RGB**  
   - O LED vermelho do **LED RGB** pisca continuamente **5 vezes por segundo**.  
   
2. **Matriz WS2812**  
   - Exibe números de **0 a 9** com efeitos visuais.  
   - Formato fixo (como segmentos de display de 7 segmentos) ou um estilo criativo, desde que seja legível.  

3. **Botões com Interrupção e Debouncing**  
   - **Botão A**: incrementa o número exibido na matriz de LEDs.  
   - **Botão B**: decrementa o número exibido na matriz de LEDs.  
   - Ambas as funcionalidades usam **interrupções (IRQ)** e **debouncing via software**.  

## 🔧 Requisitos Técnicos  
1. **Uso de Interrupções:** todas as interações com botões são feitas via **IRQ**.  
2. **Debouncing via Software:** evita leituras falsas ao pressionar botões.  
3. **Controle de LEDs:** tanto LEDs comuns quanto **WS2812** são manipulados.  
4. **Código Bem Estruturado:** organizado e comentado para facilitar o entendimento.  



## 🔄 Fluxo do Sistema

1. **Inicialização do Sistema**
   - Configura GPIOs para **botões, LED RGB e Matriz WS2812**.
   - Define **interrupções (IRQ)** para capturar eventos dos botões.
   - Aplica **debouncing** para evitar acionamentos errados.

2. **Loop Principal**
   - Mantém o LED RGB piscando a cada **200ms**.
   - Exibe o **número atual** na matriz WS2812.
   - Aguarda eventos de **interrupção dos botões**.

3. **Tratamento dos Botões**
   - **Botão A pressionado:** incrementa o número e atualiza a matriz.
   - **Botão B pressionado:** decrementa o número e atualiza a matriz.

---

## 🚀 Como Executar o Projeto

### 🛠️ Configuração Inicial
1. Clone o repositório:
   ```sh
   git clone https://github.com/ElissonNadson/BitDogLab-Interrupcoes-LEDs
   ```
2. Abra o projeto no **VS Code** ou no **CLion**.
3. Configure o ambiente do **Pico SDK**.
4. Compile o código:
   ```sh
   mkdir build && cd build
   cmake ..
   make
   ```
5. Conecte a **BitDogLab** via USB e envie o binário.


### 🖥️ Testando no Simulador
Se quiser testar no **Wokwi**, abra o arquivo `diagram.json` e inicie a simulação.

---

## 📹 Demonstração em Vídeo
📺 **Assista à demonstração do projeto em execução**:

🔗 [Video da execução no hardware]([https://www.youtube.com/](https://youtu.be/OXyGP3hYkRg))

https://youtu.be/OXyGP3hYkRg

---

⌨️ Desenvolvido com 💙 por **ElissonNadson**

