#ifndef START_H
#define START_H
int main(int argc, char **argv);
void _start()
{
	int status = main(0, NULL);
	/* __builtin_trap(); */
	exit(status);
}
#endif
