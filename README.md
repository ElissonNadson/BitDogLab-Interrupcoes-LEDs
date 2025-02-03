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
![Untitled Diagram (7)](https://github.com/user-attachments/assets/7b70ba6f-d484-4751-b033-ff5212fd04b8)

1️⃣ Inicialização: Configura os botões, a matriz de LEDs e o LED RGB.
2️⃣ Loop principal:

O LED vermelho pisca 5 vezes por segundo.
O sistema aguarda um botão ser pressionado.
3️⃣ Interrupções dos botões:
Botão A ➡️ Aumenta o número na matriz.
Botão B ➡️ Diminui o número na matriz.
4️⃣ Debouncing: Evita leituras erradas dos botões.
5️⃣ Atualização da matriz: Exibe o novo número.

---

## 🚀 Como Executar o Projeto

### 🛠️ Configuração Inicial
1. Clone o repositório:
   ```sh
   git clone https://github.com/ElissonNadson/BitDogLab-Interrupcoes-LEDs
   ```
2. Abra o projeto no **VS Code** 
3. Certifique-se de que a extensão **Raspberry Pi Pico** e  **Wokwi** estão instaladas e configuradas corretamente.
4. Clique no ícone da extensão da Pico<br>
![image](https://github.com/user-attachments/assets/f7f9b698-a829-4ae7-a716-8e7f0a7ed835)
5. Selecione importar projeto para que a pasta build seja gerada automaticamente:<br>
  - Selecione o caminho do projeto<br>

![image](https://github.com/user-attachments/assets/776f5db4-1bff-4272-a620-73e931dd6ec3)


6. Navegue até a opção Compilar Projeto:<br>

![image](https://github.com/user-attachments/assets/7d19fc93-f11d-463a-9361-b1e6671836b6)


### 🖥️ Testando no Simulador
Se quiser testar no **Wokwi**, abra o arquivo `diagram.json` e inicie a simulação.
![image](https://github.com/user-attachments/assets/e0c33157-d348-43fb-800d-320e3dc7025f)


---

## 📹 Demonstração em Vídeo  
📺 **Assista à demonstração do projeto em execução**:  

[![Demonstração do Projeto](https://img.youtube.com/vi/OXyGP3hYkRg/0.jpg)](https://youtu.be/OXyGP3hYkRg)  

🔗 [Assista no YouTube](https://youtu.be/OXyGP3hYkRg)  


---

⌨️ Desenvolvido com 💙 por **ElissonNadson**

