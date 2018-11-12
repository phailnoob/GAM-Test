#include "Torch.h"
#include <stdio.h>

void placeTorch(int index, int x, int y)
{
	dataStorage_setTorchPos(index, x, y);
	dataStorage_getTorchObj(index)->active = true;
}

void destroyTorch(int index)
{
	dataStorage_setTorchPos(index, -1, -1);
	dataStorage_getTorchObj(index)->active = false;
}