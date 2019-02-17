/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** my_objdump
*/

#include "objdump.h"

int get_zero(size_t nb)
{
    size_t i = 0;

    while (nb / 10) {
        nb /= 10;
        i++;
    }
    return (i < 4 ? 4 : i);
}

void print_section(size_t shifted, unsigned char *strtab,
Elf64_Shdr *shdr, size_t size)
{
    char *to_print = calloc(17, sizeof(char));
    char *hexa = calloc(36, sizeof(char));
    size_t count = 0;

    for (size_t s = 0; s < 35; s += 2, count++) {
        if (s == 8 || s == 17 || s == 26) {
            sprintf(hexa + s, " ");
            s++;
        }
        if (count >= shdr[size].sh_size - shifted) {
            to_print[count] = ' ';
            sprintf(hexa + s, " ");
        } else {
            sprintf(hexa + s, "%02x", strtab[count + shifted]);
            to_print[count] = (char)(isprint(strtab[count + shifted]) ?
            strtab[count + shifted] : '.');
        }
    }
    printf(" %-35s  %-16s\n", hexa, to_print);
}

void display_section_parser(Elf64_Shdr *shdr, char *strtab,
size_t i, size_t shifted)
{
    strtab += shifted + shdr[i].sh_offset;
    for (shifted = 0; shifted < shdr[i].sh_size; shifted += 16) {
        printf(" %0*lx", get_zero(shdr[i].sh_addr + shifted),
        shdr[i].sh_addr + shifted);
        print_section(shifted, (unsigned char *) strtab, shdr, i);
    }
}

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

int check_elf_format(Elf64_Ehdr *elf)
{
    return ((elf->e_ident[EI_MAG0] == ELFMAG0
    && elf->e_ident[EI_MAG1] == ELFMAG1
    && elf->e_ident[EI_MAG2] == ELFMAG2
    && elf->e_ident[EI_MAG3] == ELFMAG3) ? 1 : 0);
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