/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** main
*/

#include "nm.h"

int check_file(const char *filename, struct stat f_info)
{
    if (access(filename, F_OK) != 0) {
        printf("nm: '%s': No such file\n", filename);
        return 1;
    }
    if (stat(filename, &f_info) != 0) {
        printf("nm: Error stat\n");
        return 1;
    }
    if (!S_ISREG(f_info.st_mode)) {
        printf("nm: Warning: '%s' is not an ordinary file\n", filename);
        return 1;
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    struct stat f_info;

    if (argc < 2) {
        if (check_file("a.out", f_info))
            return 84;
    }
    for (int i = 1; i < argc; i++) {
        if (check_file(argv[i], f_info))
            continue;
    }
    return 0;
}
