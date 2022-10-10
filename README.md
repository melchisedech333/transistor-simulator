# Transistor Simulator

Este código trata-se de uma brincadeira com noções envolvendo o funcionamento de transistores. A ideia é emular transistores MOSFET's do tipo N e P, e emular as ligações dos fios entre os mesmos. Com isto criar portas lógicas, para com elas ir escalando nos níveis de abstração.

Portas lógicas implementadas:
- NOT
- NAND
- XOR (composta por portas NAND)
- AND (comporta por NAND e NOT)

Obs: internamente a aplicação ativa a flag <b>Vdd</b>, significando que há energia no circuito. Onde é conectado um fio do Power Supply ao transistor (no source para P-TYPE, no drain para N-TYPE). Para os casos onde é feito o uso de portas já existentes para criar outras (como a XOR), o Vdd da porta em questão é conectado ao Vdd de cada uma das sub-portas, fazendo assim com que a energia percorra os circuitos caminhando em direção ao Ground.


#### Gate examples:

```c
// ***
gate_t *not = create_gate(GATE_NOT);

not->input1 = 0;
run_gate(not);

reset_gate(not);
not->input1 = 1;
run_gate(not);

// ***
gate_t *nand = create_gate(GATE_NAND);

nand->input1 = 0;
nand->input2 = 0;
run_gate(nand);

reset_gate(nand);
nand->input1 = 1;
nand->input2 = 0;
run_gate(nand);

reset_gate(nand);
nand->input1 = 0;
nand->input2 = 1;
run_gate(nand);

reset_gate(nand);
nand->input1  = 1;
nand->input2  = 1;
run_gate(nand);

// ***
gate_t *xor = create_gate(GATE_XOR);

xor->input1 = 1;
xor->input2 = 1;
run_gate(xor);

reset_gate(xor);
xor->input1 = 0;
xor->input2 = 0;
run_gate(xor);

reset_gate(xor);
xor->input1 = 0;
xor->input2 = 1;
run_gate(xor);

reset_gate(xor);
xor->input1 = 1;
xor->input2 = 0;
run_gate(xor);

// ***
gate_t *and = create_gate(GATE_AND);

and->input1 = 0;
and->input2 = 0;
run_gate(and);
```


