/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** my_objdump
*/

#include "objdump.h"

int my_objdump(int fd, const char *filename)
{
    Elf64_Ehdr *elf;
    Elf64_Shdr *shdr;
    char *strtab;
    int filesize = lseek(fd, 0, SEEK_END);
    void *data = mmap(NULL, filesize, PROT_READ, MAP_SHARED, fd, 0);

    if (data) {
        elf = (Elf64_Ehdr *)(data);
        if (!check_elf_format(elf)) {
            printf ("objdump: %s: File format not recognized\n", filename);
            return (1);
        }
        shdr = (Elf64_Shdr *)(data + elf->e_shoff);
        strtab = (char *)(data + shdr[elf->e_shstrndx].sh_offset);
        display_header(elf, shdr, filename);
        display_sections(elf, shdr, strtab, data);
        return (0);
    }
    return (1);
}