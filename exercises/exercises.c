#include <stdio.h>
#include <stdlib.h>
#include "exercises.h"


int main(void)
{
	init_rng();
	printf("%s\n", coin_flip() ? "HEADS" : "TAILS");
	return 0;
}
