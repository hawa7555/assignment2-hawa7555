#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <syslog.h>

int main(int argc, char **argv)
{

    openlog(NULL, 0, LOG_USER);

    if(argc != 3)
    {
        syslog(LOG_ERR, "Invalid number of arguments: %d \n", argc);
        //perror(NULL);
        exit(1);
    }

    char *writefile = argv[1];
    char *writestr =  argv[2];

    int fd;

    fd = open(writefile, O_RDWR| O_CREAT | O_TRUNC, 0600);

    if(fd == -1)
    {
        syslog(LOG_ERR, "Error creating file %s \n", writefile);
        perror(NULL);
        exit(1);
    }

    ssize_t nr;
    nr = write(fd, writestr, strlen(writestr));

    syslog(LOG_DEBUG, "Writing %s to %s", writestr, writefile);

    if(nr == -1)
    {
        syslog(LOG_ERR, "Error writing to file %s\n", writefile);
        perror(NULL);
        close(fd);
        exit(1);
    }

    close(fd);
    closelog();

    return 0;
}