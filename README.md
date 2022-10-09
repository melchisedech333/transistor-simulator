# Transistor Simulator

Este código trata-se de uma brincadeira com noções envolvendo o funcionamento de transistores. A ideia é emular transistores MOSFET's do tipo N e P, e emular as ligações dos fios entre os mesmos. Com isto criar portas lógicas, para com elas ir escalando nos níveis de abstração.

Portas lógicas implementadas:
- NOT
- NAND
- XOR (composta por portas NAND)

Obs: internamente a aplicação ativa a flag <b>Vdd</b>, significando que há energia no circuito. Onde é conectado um fio do Power Supply ao transistor (no source para P-TYPE, no drain para N-TYPE). Para os casos onde é feito o uso de portas já existentes para criar outras (como a XOR), o Vdd do gate em questão é conectado ao Vdd de cada uma das sub-portas, fazendo assim com que a energia percorra os circuitos caminhando em direção ao Ground.


