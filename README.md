## ulibc

## Example
```sh
$ clang -w -I/path/to/ulibc -g -ggdb3 -nostdlib -nostartfiles -fno-builtin -ffreestanding -nostdinc -mstackrealign -O2 example.c
```

```c
#include <stdio.h>
#include <math.h>

int main(int argc, char **argv)
{
	char tmp[32] = { 0 };
	read(0, tmp, sizeof(tmp));
	printf("tmp: %s\n", tmp);
	
	printf("exp: %f\n", expf(1.f));
	printf("log: %f\n", logf(100.f));
	return 0;
}
```