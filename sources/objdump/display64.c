/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** display64
*/

#include "objdump.h"

void display_section_parser(Elf64_Shdr *shdr, char *strtab,
size_t i, size_t shifted)
{
    strtab += shifted + shdr[i].sh_offset;
    for (shifted = 0; shifted < shdr[i].sh_size; shifted += 16)
    {
        printf(" %0*lx", get_zero(shdr[i].sh_addr + shifted),
        shdr[i].sh_addr + shifted);
        print_section(shifted, (unsigned char *)strtab, shdr, i);
    }
}

void display_header(Elf64_Ehdr *elf, Elf64_Shdr *shdr, const char *filename)
{
    printf("\n%s:     file format %s\n", filename,
    (elf->e_ident[EI_CLASS] == ELFCLASS64) ? "elf64-x86-64" : "elf32-x86-64");
    printf("architecture: i386:x86-64, flags 0x%08x:\n",
    (unsigned)(get_flags(elf, shdr)));
    display_flags(get_flags(elf, shdr));
    printf("start address 0x%016x\n\n", (unsigned)(elf->e_entry));
}

void display_sections(Elf64_Ehdr *elf, Elf64_Shdr *shdr,
char *strtab, void *data)
{
    size_t shifted = 0;

    for (size_t i = 1; i < elf->e_shnum; i++) {
        if (shdr[i].sh_type != SHT_NOBITS
        && shdr[i].sh_type != SHT_SYMTAB
        && strcmp(&strtab[shdr[i].sh_name], ".strtab")
        && data + shdr[i].sh_offset != (void *)(strtab))
        {
            printf("Contents of section %s:\n", &strtab[shdr[i].sh_name]);
            display_section_parser(shdr, (char *) (elf), i, shifted);
        }
    }
}

void display_flags(size_t flags)
{
    int empty = 0;

    if (flags & HAS_RELOC)
        printf("%sHAS_RELOC", (!empty++) ? "" : ", ");
    if (flags & EXEC_P)
        printf("%sEXEC_P", (!empty++) ? "" : ", ");
    if (flags & HAS_SYMS)
        printf("%sHAS_SYMS", (!empty++) ? "" : ", ");
    if (flags & DYNAMIC)
        printf("%sDYNAMIC", (!empty++) ? "" : ", ");
    if (flags & D_PAGED)
        printf("%sD_PAGED", (!empty++) ? "" : ", ");
    printf("\n");
}