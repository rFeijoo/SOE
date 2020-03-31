```
1. O que são sistemas embarcados?
   São, basicamente, firmwares embarcados em hardware com um propósito de uso específico.
```
```
2. O que são sistemas microprocesssados?
   São sistemas controlados por um microprocessador.
```
```
3. Apresente aplicações de sistemas embarcados:
	(a) Para a indústria automotiva;
	    ECU (Engine Control Unit), trata-se de um sistema embarcado em veículos para gerenciamento do motor - gerenciamento da injeção, monitoramento de torque, etc.

	(b) Para eletrodomésticos;
	    Robô aspirador de pó, trata-se de um dispositivo capaz de percorrer ambientes, evitando obstáculos, à fim de "limpar" o piso.
	    
	(c) Para automação industrial.
	    Controle de uma linha de produção, utilizando esteiras e máquinas específicas necessárias, através de uma malha de controle embarcada no controlador (processador, controlador).
```
```
4. Cite arquiteturas possíveis e as diferenças entre elas.
   RISC: apenas com registradores, ou seja, permite acesso aos dados via registrador. Suporta menos instruções, o que a torna mais veloz que a CISC.

   CISC: integra registrador com memória no mesmo barramento, ou seja, permite acesso aos dados via memória. Suporta mais instruções, tornando-a mais lenta.
```
```
5. Por que usamos o Raspberry Pi na disciplina, ao invés de outro system-on-chip?
   A raspberry pi é denominada "microcomputador", isso por que possui periféricos muito robustos tornando-a mais versátil do que outros processadores, como arduinos, ESPs e PICs. No geral, para estudar diversas aplicações embarcadas (utilização de I/Os, RTOS, LKM) é mais prático utilizar uma rasp que tem poder para processar o demandado.
```
