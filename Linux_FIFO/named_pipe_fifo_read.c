/*This is FIFO read program and Read would wait until writen*/

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main ()
{
	int fd, retval;
	char buffer[8];

	fd = open("/tmp/myfifo", O_RDONLY);

	/*As we have already created the fifo in the write program, we have to just open it*/
	retval = read(fd, buffer, sizeof(buffer));

	/*We will read the fifo and store the content in to the buffer*/
	fflush(stdin);

	/*we will flush the data which are already in the fifo*/
	write(1, buffer, sizeof(buffer));

	/*we are now reading the content out from the buffer and put it on to the screen*/

	close(fd);

	return 0;
}