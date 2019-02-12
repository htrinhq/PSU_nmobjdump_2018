/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** my_objdump
*/

#include "objdump.h"

void display_values(Elf64_Ehdr *elf)
{
    if (elf->e_machine == EM_X86_64)
        printf("MACHINE STRUCTURE: X86_64\n");
    else
        printf("elf->e_machine value is: %d\n", elf->e_machine);
    printf("HEADER SIZE: %d\n", elf->e_ehsize);
}

int my_objdump(int fd)
{
    Elf64_Ehdr *elf;
    Elf64_Shdr *shdr;
    char *strtab;
    int filesize = lseek(fd, 0, SEEK_END);
    void *data = mmap(NULL, filesize, PROT_READ, MAP_SHARED, fd, 0);

    if (data) {
        elf = (Elf64_Ehdr *)(data);
        shdr = (Elf64_Shdr *)(data + elf->e_shoff);
        strtab = (char *)(data + shdr[elf->e_shstrndx].sh_offset);
        for (size_t i = 1; i < elf->e_shnum; i++) {
            if (shdr[i].sh_addr != 0)
                printf("Contents of section %s:\n", &strtab[shdr[i].sh_name]);
        }
        display_values(elf);
        return (0);
    }
    return (84);
}