/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** my_objdump
*/

#include "objdump.h"

int my_objdump32(Elf32_Ehdr *elf, const char *filename, void *data)
{
    Elf32_Shdr *shdr;
    char *strtab;

    shdr = (Elf32_Shdr *)(data + elf->e_shoff);
    strtab = (char *)(data + shdr[elf->e_shstrndx].sh_offset);
    display_header32(elf, shdr, filename);
    display_sections32(elf, shdr, strtab, data);
    return (0);
}

int my_objdump64(Elf64_Ehdr *elf, const char *filename, void *data)
{
    Elf64_Shdr *shdr;
    char *strtab;

    shdr = (Elf64_Shdr *)(data + elf->e_shoff);
    strtab = (char *)(data + shdr[elf->e_shstrndx].sh_offset);
    display_header(elf, shdr, filename);
    display_sections(elf, shdr, strtab, data);
    return (0);
}

int my_objdump(int fd, const char *filename)
{
    Elf64_Ehdr *elf;
    Elf32_Ehdr *elf32;
    int filesize = lseek(fd, 0, SEEK_END);
    void *data = mmap(NULL, filesize, PROT_READ, MAP_SHARED, fd, 0);

    if (data) {
        elf = (Elf64_Ehdr *)(data);
        if (!check_elf_format(elf)) {
            printf ("objdump: %s: File format not recognized\n", filename);
            return (1);
        }
        if (elf->e_ident[EI_CLASS] == ELFCLASS32) {
            elf32 = (Elf32_Ehdr *)(data);
            free(elf);
            return (my_objdump32(elf32, filename, data));
        }
        return (my_objdump64(elf, filename, data));
    }
    return (1);
}