#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sysexits.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s INPUTTEXT\n", argv[0]);
        return EX_USAGE;
    }

    int fd = open("/dev/tty", O_RDWR);
    if (fd == -1) {
        perror("re-open controlling terminal");
        return EX_UNAVAIL;
    }

    for (char *p = argv[1] ; *p ; ++p)
        if (ioctl(fd, TIOCSTI, p) == -1) {
            perror("ioctl(TIOCSTI)");
            return 1;
        }

    return 0;
}
