Simulador de Assembly Genérico

by João Almeida de Jesus

Caso criarem algum arquivo .c novo alterem o makefile para o gcc compilar tal arquivo.

Compilação:

- Digite "make" na linha de comando no lugar em que o Makefile está.

Execução:

- Parâmetros:
	- -e (executar)
	- -es (executar step-by-step)
	- -m (mostra todas as memórias)
	- -md (mostra memória de dados)
	- -mc (mostra memória de instrução)
	- -r (mostra registradores)
- Exemplo:
	- ./simular (nome-do-arquivo) -e -m
		- O simulador irá executar as instruções do arquivo, e depois da execução irá mostrar todas as memórias.
	- ./simular (nome-do-arquivo) -m -e
		- Irá mostrar a memória antes da execução do programa.
	- ./simular (nome-do-arquivo) -m -e -r -md
		- Irá mostrar a memória, executar, mostrar os registradores depois da execução, e por fim, a memória de dados.
Restrições:
	- O nome de uma variavel da memória deve ser maior que 1.
	- Para criar uma função, deve-se usar "@" antes do nome da função.
	- As instruções devem estar identada por tab.
	- Rótulos de loop, ou rótulos de funções não devem estar identadas por tabs. E após um rótulo, a instrução não poderá ser na mesma linha.
