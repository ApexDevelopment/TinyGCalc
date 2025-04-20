#include "hal/hal_serial.h"

#include <stdio.h>
#ifdef _WIN32
#include <conio.h>
#else
#include <unistd.h>
#include <fcntl.h>
#endif

void hal_serial_init(void)
{
	// Nothing special needed for mock
	printf("[MockSerial] Serial initialized.\n");
}

bool hal_serial_input_available(void)
{
#ifdef _WIN32
	return _kbhit();
#else
	struct timeval tv = {0L, 0L};
	fd_set		   fds;
	FD_ZERO(&fds);
	FD_SET(0, &fds);
	return select(1, &fds, NULL, NULL, &tv) > 0;
#endif
}

char hal_serial_read_char(void)
{
	return (char) getchar(); // stdin is already line-buffered
}

void hal_serial_write_char(char c)
{
	putchar(c);
	fflush(stdout);
}

void hal_serial_write_string(const char *s)
{
	fputs(s, stdout);
	fflush(stdout);
}
