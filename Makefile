all: simulador executar remover

simulador:
	gcc -g src/sim.c src/functions/FuncTexto.c src/functions/Interface.c src/functions/Memorias.c src/functions/Registradores.c src/functions/Rotulos.c -o sim

executar:
	./sim

remover:
	rm sim
