#include "defenitions.h"

bool read_file(int fd, char **str, size_t *f_size) {
    size_t rd;
    char buf[BUFFER_SIZE + 1];
    char *copy;

    if (fd < 0) {
        return false;
    }

    if (read(fd, buf, 0) <= -1) {
        return false;
    }
    *f_size = 0;
    *str = calloc(1, sizeof(char));
    copy = NULL;
    while ((rd = read(fd, buf, BUFFER_SIZE)) > 0) {
        copy = calloc(*f_size + rd + 1, sizeof(char));
        memcpy(copy, *str, *f_size);
        memcpy(copy + *f_size, buf, rd);
        copy[*f_size + rd] = '\0';
        *f_size += rd;
        free(*str);
        *str = copy;
    }
    return true;
}
