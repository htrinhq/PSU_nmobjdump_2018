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

void display_section_parser(Elf64_Shdr *shdr, char *strtab,
size_t i, size_t bit_shifted)
{
    char *hexa = calloc(36, sizeof(char));
    char *printed_array = calloc(17, sizeof(char));
    size_t size = 0;
   // size_t max = (bit_shifted + shdr[i].sh_size < 16) ?
   // 16 - (16 - bit_shifted + shdr[i].sh_size) : 16;

    strtab += bit_shifted + shdr[i].sh_offset;
    for (bit_shifted = 0; bit_shifted < shdr[i].sh_size; bit_shifted += 16) {
        printf(" %0*lu", get_zero(shdr[i].sh_addr + bit_shifted), shdr[i].sh_addr + bit_shifted);
        for (size_t count = 0; count < 35 && count < bit_shifted + shdr[i].sh_size; count += 2) {
            if (count == 8 || count == 17 || count == 26) {
                sprintf(hexa + count, " ");
                count++;
            }
            isprint(strtab[size + bit_shifted]) ?
            sprintf(hexa + count, "%02x", strtab[size + bit_shifted]) :
            sprintf(hexa + count, "00");
            printed_array[size] = (char)(isprint(strtab[size + bit_shifted])) ?
            strtab[size + bit_shifted] : '.';
            size++;
        }
        printf(" %-35s  %-16s\n", hexa, printed_array);
        size = 0;
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
            printf(" %04x ", (unsigned)(shdr[i].sh_addr));
            display_section_parser(shdr, strtab, i, 0);
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
        display_header(elf, shdr, filename);
        display_sections(elf, shdr, strtab, data);
        return (0);
    }
    return (84);
}