/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** nm64
*/

#include "nm.h"

int nm64(Elf64_Ehdr *elf)
{
    Elf64_Shdr *shdr;
    char *strtab;
    char *shstrtab;
    sym_t *symbol = NULL;

    shdr = (elf->e_shoff) ? (Elf64_Shdr *)((char *)elf + elf->e_shoff) : NULL;
    if (shdr == NULL)
        return 0;
    shstrtab = (char *)elf + shdr[elf->e_shstrndx].sh_offset;
    for (int i = 0; i < elf->e_shnum; i++)
        if (!strcmp(shstrtab + shdr[i].sh_name, ".strtab"))
            strtab = (char *)elf + shdr[i].sh_offset;
    symbol = find_symbol(shdr, strtab, elf);
    print_sym(symbol);
    return 0;
}