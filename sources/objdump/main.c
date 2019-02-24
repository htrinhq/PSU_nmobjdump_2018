/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** main
*/

#include "objdump.h"

int single_arg(void)
{
    int fd;
    fd = open("a.out", O_RDONLY);
    if (fd == -1) {
        printf("objdump: 'a.out': No such file\n");
        return (1);
    }
    if (my_objdump(fd, "a.out"))
        return (1);
    return (0);
}

int multiple_args(int argc, const char **argv)
{
    int fd;
    int value = 0;

    for (int i = 1; i < argc; i++) {
        fd = open(argv[i], O_RDONLY);
        if (fd == -1)
        {
            printf("objdump: '%s': No such file\n", argv[i]);
            value++;
            continue;
        }
        if (my_objdump(fd, argv[i]))
            value++;
    }
    return (value != 0 ? 84 : 0);
}

int main(int argc, const char **argv)
{
    return ((argc < 2) ? (single_arg() ? 84 : 0) : multiple_args(argc, argv));
}
