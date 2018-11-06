
#include "SpriteReference.h"

char chart[] = {0, 219, 234};

/*
Element 0: Blank Spaces
Element 1: Walls
ELement 2: Player
*/

char spriteReference_getSprite(char input)
{
	return chart[input];
}
