
# 📦 Ponte Rolante Com Garra com ESP32

## 🏭 **Contexto do Problema de Negócio**

Em ambientes industriais, especialmente em linhas de montagem ou centros de distribuição, há uma demanda crescente por automação do transporte de peças, componentes ou produtos entre diferentes estações de trabalho (postos).

Atualmente, muitas empresas ainda utilizam transporte manual ou semi-automatizado, o que gera:

- Ineficiências no tempo de deslocamento  
- Erros humanos na entrega em postos errados  
- Riscos ergonômicos aos operadores  

---

## ✅ **Requisitos Funcionais do Sistema**

- **Seleção de destino via botões físicos:** O sistema deve permitir ao operador escolher entre três destinos (P1, P2, P3) usando botões do tipo push-button.  
- **Controle de movimentação do carro:** O sistema deve mover o carro para a esquerda ou direita, dependendo da posição atual e do destino selecionado.  
- **Fechamento da garra antes da movimentação:** O sistema deve fechar a garra antes de iniciar o deslocamento.  
- **Leitura de sensores de fim de curso:** O sistema deve usar sensores para detectar quando o carro chegou ao destino correto.  
- **Abertura da garra ao final do deslocamento:** Ao chegar no destino, a garra deve ser aberta automaticamente.  
- **Atualização da posição atual:** O sistema deve registrar a nova posição após a movimentação.  
- **Exibição de status em display LCD:** O sistema deve exibir mensagens informando ações como "movendo", "chegou", "já no destino".  
- **Prevenção de comandos simultâneos:** O sistema deve ignorar novos comandos enquanto uma movimentação estiver em andamento.  

---

## ⚙️ **Requisitos Não Funcionais**

- **Tempo de resposta:** O sistema deve iniciar a movimentação em até 1 segundo após o botão ser pressionado.  
- **Robustez contra múltiplos acionamentos:** O sistema deve filtrar pressões repetidas ou ruídos nos botões para evitar comportamentos inesperados.  
- **Segurança na operação:** O sistema deve garantir que o carro só se mova quando não estiver sobre um fim de curso acionado (evitar falso positivo).  
- **Simplicidade na interface:** Interface simples com botões físicos e feedback visual no LCD, facilitando o uso por operadores sem treinamento técnico.  
- **Escalabilidade:** O sistema deve permitir futuras expansões para mais postos ou uma interface em um servidor com alterações mínimas.  
- **Tempo de abertura/fechamento padronizado da garra:** A garra deve operar com tempo controlado (1 segundo) para garantir padronização.  

---

## 📐 **Regras de Negócio**

- **Movimento da garra:** Só pode ocorrer com o carro parado, evitando falhas mecânicas ou acidentes.  
- **Movimento do carro:** Só inicia se a garra estiver fechada, garantindo que o item esteja preso.  
- **Novo comando durante movimento:** Não é permitido, evitando mudanças inesperadas de destino.  
- **Direção do movimento:** Determinada automaticamente (esquerda ou direita), reduzindo erros.  
- **Sensor de fim de curso:** Deve ser ignorado se já estiver acionado ao iniciar o sistema (evita falso positivo).  

---

## 🔁 **Fluxograma do Processo**

1. **Início** – O operador energiza a máquina.  
2. **Leitura da posição** – O sistema identifica a posição inicial.  
3. **J1 (P1 pressionado):** A máquina vai apenas para a **direita** quando outro botão for pressionado.  
4. **J2 (P2 pressionado):** A máquina pode ir para **esquerda ou direita**.  
5. **J3 (P3 pressionado):** A máquina vai apenas para a **esquerda** quando outro botão for pressionado.  
6. **Leitura de botão:** Identifica a interrupção externa e aciona o comando.  
7. **Deslocamento direita:** Move até o fim de curso do destino.  
8. **Deslocamento esquerda:** Move até o fim de curso do destino.  

📌 **Figura 1 - Fluxo Grafset do programa.**  
![grafset](plataformaguindaste/image/grafset.png)
**Fonte: Autor.**

---

## 🔌 **Esquemático Preliminar (Wokwi)**

O circuito utiliza:
- ESP32 de 38 pinos  
- Display LCD  
- 3 botões para representar os postos (P1, P2, P3)  
- 3 botões menores como sensores de fim de curso  
- 1 chave liga/desliga  

📌 **Figura 2 - Esquemático feito no Wokwi.**  
![esquematico_worki](plataformaguindaste/image/esquematico.png)
**Fonte: Autor.**

---

## 📊 **Lista de Materiais e Orçamento**

Consulta realizada em **02/05/2025**.

| ITEM | NOME | VALOR UNITÁRIO | QTD | REFERÊNCIA |
|------|------|----------------|-----|-------------|
| 1 | ESP32-WROOM-32U DevKitC V4 com Wi-Fi e Bluetooth | R$ 59,83 | 1 | [UsinaInfo](https://www.usinainfo.com.br/esp32/esp32-wroom-32u-devkitc-v4-com-wifi-e-bluetooth-7077.html) |
| 2 | Display LCD 16x2 I2C com Fundo Verde - OUTLET | R$ 16,44 | 1 | [UsinaInfo](https://www.usinainfo.com.br/display-arduino/display-lcd-16x2-i2c-com-fundo-verde-outlet-9099.html) |
| 3 | Push Button 12x12x4 | R$ 1,55 | 6 | [UsinaInfo](https://www.usinainfo.com.br/push-buttons/push-button-chave-tactil-12x12x4-para-projetos-2985.html) |
| 4 | LED 5mm Vermelho (10 unid.) | R$ 2,50 | 1 | [RoboCore](https://www.robocore.net/display-led/led-difuso-5mm-vermelho-10-unidades) |
| 5 | LED 5mm Azul (10 unid.) | R$ 2,60 | 1 | [RoboCore](https://www.robocore.net/display-led/led-difuso-5mm-azul-10-unidades) |
| 6 | Interruptor Liga/Desliga tipo Gangorra | R$ 2,77 | 1 | [UsinaInfo](https://www.usinainfo.com.br/interruptores-e-pulsadores/interruptor-ligadesliga-tipo-gangorra-10a120-6a250v-preto-3763.html) |
| 7 | Resistor 1kΩ (10 unid.) | R$ 0,75 | 1 | [RoboCore](https://www.robocore.net/resistor-potenciometro/resistor-1k-pacote-com-10-unidades) |
| 8 | Placa Borne Adaptadora ESP32 | R$ 42,90 | 1 | [Saravati](https://www.saravati.com.br/placa-borne-adaptadora-esp32s-terminal-adapter-38-pinos.html) |
| 9 | Placa de Circuito Impresso Dupla Face | R$ 6,90 | 1 | [MakerHero](https://www.makerhero.com/produto/placa-de-circuito-impresso-dupla-face/) |

📌 **Custo Total Estimado:** **R$ 136,24**  
**Fonte: Autor.**
