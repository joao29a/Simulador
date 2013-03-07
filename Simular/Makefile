all: simulador criar mover executar remover

criar:
	mkdir exe

simulador:
	gcc sim.c Estruturas/Interface.c Estruturas/Memorias.c Estruturas/Registradores.c Estruturas/Rotulos.c -o sim

mover:
	mv sim exe

executar:
	./exe/sim

remover:
	rm -r exe

