#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/* copy:  copy src to dest */
int main(void)
{
    char pathname_src[FILENAME_MAX];
    char pathname_dest[FILENAME_MAX];
    int fd_src;
    int fd_dest;

    char buf[BUFSIZ];
    ssize_t nbyte;

    /* acquire input file name */
    printf("Input file: ");
    scanf("%s", pathname_src);

    /* acquire output file name */
    printf("Output file: ");
    scanf("%s", pathname_dest);

    /* open the input file */
    if ((fd_src = open(pathname_src, O_RDONLY)) == -1)
    {
        perror(pathname_src);
        exit(EXIT_FAILURE);
    }

    /* create output file */
    if ((fd_dest = open(pathname_dest, O_CREAT | O_WRONLY | O_EXCL)) == -1)
    {
        perror(pathname_dest);
        exit(EXIT_FAILURE);
    }

    /* loop until read fails */
    while ((nbyte = read(fd_src, buf, BUFSIZ)) > 0)
    {
        write(fd_dest, buf, nbyte);
    }

    /* close files */
    close(fd_src);
    close(fd_dest);

    /* write completion message to screen */
    printf("Write complete");

    /* terminate normally */
    return 0;
}
