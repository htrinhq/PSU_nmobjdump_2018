/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** my_objdump
*/

#include "objdump.h"

size_t get_flags(Elf64_Ehdr *elf, Elf64_Shdr *shdr)
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

void display_values(Elf64_Ehdr *elf, Elf64_Shdr *shdr, const char *filename)
{
    printf("\n%s:\tfile format %s\n", filename,
    (elf->e_ident[EI_CLASS] == ELFCLASS64) ? "elf64-x86-64" : "elf32-x86-64");
    printf("architecture: i386:x86-64, flags 0x%08x:\n",
    (unsigned)(get_flags(elf, shdr)));
    display_flags(get_flags(elf, shdr));
    printf("start address 0x%016x\n\n", (unsigned)(elf->e_entry));
}

void display_sections(Elf64_Ehdr *elf, Elf64_Shdr *shdr,
char *strtab, void *data)
{
    for (size_t i = 1; i < elf->e_shnum; i++)
    {
        if (shdr[i].sh_type != SHT_NOBITS
        && shdr[i].sh_type != SHT_SYMTAB
        && strcmp(&strtab[shdr[i].sh_name], ".strtab")
        && data + shdr[i].sh_offset != (void *)(strtab))
        {
            printf("Contents of section %s:\n", &strtab[shdr[i].sh_name]);
            printf(" %04x\n", (unsigned)(shdr[i].sh_addr));
        }
    }
}

int my_objdump(int fd, const char *filename)
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
        display_values(elf, shdr, filename);
        display_sections(elf, shdr, strtab, data);
        return (0);
        }
        return (84);
    }