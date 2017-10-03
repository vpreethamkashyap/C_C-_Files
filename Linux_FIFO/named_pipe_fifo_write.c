/* Named Pipes OR FIFO for Linux Inter Process Communication */

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	int fd,retval;
	char buffer[8] = "TESTDATA";

	fflush(stdin);

	retval = mkfifo("/tmp/myfifo", 0666);

	/*To create a FIFO we are permitted to create in /tmp directory alone nad give 0666 permissions*/
	fd = open("/tmp/myfifo", O_WRONLY);

	/*As the FIFO is already created we can just open it now and the location of the file is "/tmp/myfifo"*/
	write(fd, buffer, sizeof(buffer));

	/*We are now writing into the fifo*/
	close(fd);

	return 0;
}