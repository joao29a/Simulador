#include <stdlib.h>
#include "../hdr/Registradores.h"

char *TabelaRegistradores[]={"A","B","C","D","E","F","G","H","I","J","K","L",
	"M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};

Registradores registrador[QTD_REG];

void atribuirLetrasReg(Registradores *reg){
	int i;
	for (i=0;i<QTD_REG;i++)
		reg[i].reg=TabelaRegistradores[i];
}
