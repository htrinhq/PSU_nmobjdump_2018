/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** main
*/

#include "objdump.h"

int main(int argc, char const *argv[])
{
    int fd;

    if (argc < 2) {
        fd = open("a.out", O_RDONLY);
        if (fd == -1)
            return (84);
        my_objdump(fd, "a.out");
        return (0);
    }
    for (int i = 1; i < argc; i++) {
        fd = open(argv[i], O_RDONLY);
        if (fd == -1) {
            printf("No such File: %s\n", argv[i]);
            return (84);
        }
        my_objdump(fd, argv[i]);
    }
    return 0;
}
