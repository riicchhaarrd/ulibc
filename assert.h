#ifndef ASSERT_H
#define ASSERT_H

#include <stdio.h>

//TODO: FIXME fix preprocessor add __FILE__, __LINE__ and stringify #
void assert_(int expr)
{
	if (!expr)
	{
		printf("expression failed\n");
        /* int3(); */
        /* int3(); */
        /* int3(); */
	}
}
#define assert(x)

#endif
