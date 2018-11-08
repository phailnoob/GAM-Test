
#include "SpriteReference.h"

char chart[] = {0, 219, 234};

/*
Reference Chart:
0 - Blank Spaces
1 - Walls
2 - Player
*/

char spriteReference_getSprite(char input)
{
	return chart[input];
}
