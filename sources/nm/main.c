/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** main
*/

#include "nm.h"

int nm64(Elf64_Ehdr *elf, const char *filename)
{
    printf("NM64\n");
    return 64;
}

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

int check_elf_format(Elf64_Ehdr *elf, const char *filename)
{
    if (elf->e_ident[0] == ELFMAG0 &&
        elf->e_ident[1] == ELFMAG1 &&
        elf->e_ident[2] == ELFMAG2 &&
        elf->e_ident[3] == ELFMAG3) {
            switch (elf->e_ident[4]) {
            case ELFCLASS32:
                return 0;
            case ELFCLASS64:
                return nm64(elf, filename);
            default:
                printf("nm: %s: File format not recognized\n", filename);
                return 84;
            }
        }
    return 1;
}

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

int main(int argc, char const *argv[])
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
        else
            ret = nm_main(argv[i]);
    }
    return ret;
}
