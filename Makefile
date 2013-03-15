all: simulador executar remover

simulador:
	gcc -g -Wall -Wextra src/sim.c src/functions/Decodificador.c src/functions/FuncTexto.c src/functions/Interface.c src/functions/Memorias.c src/functions/Opcode.c src/functions/Registradores.c src/functions/Rotulos.c -o sim

executar:
	./sim

remover:
	rm sim
