#ifndef STDDEF_H
#define STDDEF_H
#define NULL 0

int main(int argc, char **argv);
void _start()
{
	int status = main(0, NULL);
	/* __builtin_trap(); */
	exit(status);
}
#endif
