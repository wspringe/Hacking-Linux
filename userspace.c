
#include <linux/unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define __NR_my_syscall 359

int main()
{
	// declare return value for system call
	int ret = 0;
	// declare buffer to hold result of system call
	char * buff;
	// set the length of the buffer
	int n = 5000;

	// allocate memory for buffer to hold result
	if( ( buff = (char *) malloc(n*sizeof(char)+1) ) == NULL ) 
		perror( "Error allocating buffer\n" );
	// perform system call, storing return value in ret
	// result of system call will be stored in buffer
	ret = syscall(__NR_my_syscall, 0, n, buff);

	// print the results of the system call - contents of buffer
	printf("  PID TTY          TIME CMD\n");
	printf("%s", buff);

	// de-allocate the memory allocated for the buffer
	free(buff);
	return 0;
}
