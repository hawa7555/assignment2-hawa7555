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
    openlog(NULL, 0, LOG_USER);               //open log with LOG_USER facility

    if(argc != 3)
    {
        syslog(LOG_ERR, "Invalid number of arguments: %d \n", argc);
        //perror(NULL);                                             //no error, will print success
        exit(1);
    }

    char *writefile = argv[1];
    char *writestr =  argv[2];

    int fd;
    
    //open/create file
    fd = open(writefile, O_RDWR| O_CREAT | O_TRUNC, 0600);         //octal, not decimal

    //Error creating file
    if(fd == -1)
    {
        syslog(LOG_ERR, "Error creating file %s \n", writefile);
        perror(NULL);
        exit(1);
    }

    //Writing to file
    ssize_t nr;
    size_t str_length = strlen(writestr);
    nr = write(fd, writestr, str_length);    

    syslog(LOG_DEBUG, "Writing %s to %s", writestr, writefile);

    //Error writing to file
    if(nr == -1)
    {
        syslog(LOG_ERR, "Error writing to file %s\n", writefile);
        perror(NULL);
        close(fd);
        closelog();
        exit(1);
    }

    //partial write error
    else if(nr != str_length)
    {
       syslog(LOG_ERR, "Partial Write error to file %s\n", writefile);
       perror(NULL);
       close(fd);
       closelog();
       exit(1); 
    }

    close(fd);
    closelog();
    return 0;
}