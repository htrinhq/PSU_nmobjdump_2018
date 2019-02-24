/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** check
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
                return nm64(elf);
            default:
                printf("nm: %s: File format not recognized\n", filename);
                return 84;
            }
        }
    return 1;
}