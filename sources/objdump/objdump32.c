/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** objdump32
*/

#include "objdump.h"

void print_section32(size_t shifted, unsigned char *strtab,
Elf32_Shdr *shdr, size_t size)
{
    char *to_print = calloc(17, sizeof(char));
    char *hexa = calloc(36, sizeof(char));
    size_t count = 0;

    for (size_t s = 0; s < 35; s += 2, count++)
    {
        if (s == 8 || s == 17 || s == 26) {
            sprintf(hexa + s, " ");
            s++;
        }
        if (count >= shdr[size].sh_size - shifted) {
            to_print[count] = ' ';
            sprintf(hexa + s, " ");
        } else {
            sprintf(hexa + s, "%02x", strtab[count + shifted]);
            to_print[count] = (char)(isprint(strtab[count + shifted]) ?\
            strtab[count + shifted] : '.');
        }
    }
    printf(" %-35s  %-16s\n", hexa, to_print);
}

size_t get_flags32(Elf32_Ehdr *elf, Elf32_Shdr *shdr)
{
    size_t flags = 0;

    if (shdr == NULL)
        return flags;
    if (elf->e_type == ET_EXEC)
        flags |= EXEC_P;
    if (elf->e_type == ET_REL)
        flags |= HAS_RELOC;
    if (elf->e_type == ET_DYN)
        flags |= DYNAMIC;
    for (size_t x = 0; x < elf->e_shnum; x++) {
        if (shdr[x].sh_type == SHT_DYNSYM || shdr[x].sh_type == SHT_SYMTAB)
            flags |= HAS_SYMS;
        if (shdr[x].sh_type == SHT_DYNAMIC)
            flags |= D_PAGED;
    }
    return flags;
}
