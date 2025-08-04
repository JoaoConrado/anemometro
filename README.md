# Anemômetro em C++

Este projeto é uma implementação de um anemômetro, focado em medir a velocidade do vento. Desenvolvido em **C**, ele se concentra em um código de baixo nível para interagir com o hardware, realizar cálculos precisos e fornecer uma solução eficiente e leve.

## 🚀 O que você vai encontrar aqui?

* **Lógica de Medição:** O código implementa a lógica para calcular a velocidade do vento a partir dos pulsos gerados pelo sensor do anemômetro.
* **Código de Baixo Nível:** Foco em otimizar o uso da memória e do processamento, ideal para sistemas embarcados e microcontroladores.
* **Cálculos de Engenharia:** As funções do código convertem os dados brutos do sensor em unidades de velocidade do vento, como m/s ou km/h.

## 🧠 Como Funciona

A lógica do projeto se baseia na leitura de pulsos de um sensor (geralmente um sensor de efeito Hall) que é ativado pela rotação das pás do anemômetro. O código em C realiza os seguintes passos:

1.  **Contagem de Pulsos:** O programa conta o número de pulsos em um intervalo de tempo predefinido.
2.  **Cálculo da Frequência:** Com a contagem e o tempo, é calculada a frequência de rotação.
3.  **Conversão de Unidade:** A frequência é então convertida para a velocidade do vento usando uma fórmula de calibração específica para o sensor.

## 🛠️ Como Utilizar

Este projeto é modular e pode ser facilmente adaptado para diferentes plataformas de hardware, como **Arduino**, **ESP32** ou outros microcontroladores.

1.  **Configurar Hardware:** Conecte o anemômetro a um microcontrolador, garantindo a correta conexão do pino de sinal.
2.  **Ajustar Constantes:** No código, ajuste a constante de calibração (`CALIBRATION_FACTOR`) para corresponder às especificações do seu sensor.
3.  **Compilar e Rodar:** Compile o código utilizando o compilador C apropriado para sua plataforma e faça o upload para o microcontrolador.
