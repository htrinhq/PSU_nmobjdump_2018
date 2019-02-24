/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** main
*/

#include "nm.h"

int nm_main(const char *filename)
{
    Elf64_Ehdr *elf;
    int fd = open(filename, O_RDONLY);
    struct stat f_stat;

    fstat(fd, &f_stat);
    elf = mmap(NULL, f_stat.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if (elf != MAP_FAILED)
        return check_elf_format(elf, filename);
    else {
        printf("nm: %s: File format not recognized\n", filename);
        return 84;
    }
}

void name_header(int argc, const char **argv, int i)
{
    if (argc > 2)
        printf("%s:\n", argv[i]);
}

int main(int argc, char const **argv)
{
    struct stat f_info;
    int ret = 0;

    if (argc < 2) {
        if (check_file("a.out", f_info))
            return 84;
    }
    for (int i = 1; i < argc; i++) {
        if (check_file(argv[i], f_info))
            ret = 84;
        else {
            name_header(argc, argv, i);
            ret = nm_main(argv[i]);
        }
    }
    return ret;
}
