/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** symbol64
*/

#include "nm.h"

sym_t *get_sym_form_tab(Elf64_Sym *sym, char *strtab, size_t nb)
{
    sym_t *symbol = NULL;
    sym_t *tmp = malloc(sizeof(sym_t));

    for (size_t i = 0; i < nb; i++) {
        if (!sym[i].st_name || ELF64_ST_TYPE(sym[i].st_info) == STT_FILE)
            continue;
        tmp->name = strdup(strtab + sym[i].st_name);
        tmp->type = 'T';
        tmp->value = sym[i].st_value;
    }
    symbol = tmp;
    return symbol;
}

void print_sym(sym_t *symbol)
{
    while (symbol != NULL) {
        if (symbol->value)
            printf("%016llx %c %s\n", symbol->value, symbol->type,
                   symbol->name);
        else
            printf("%16c %c %s\n", ' ', symbol->type,
                   symbol->name);
        symbol = symbol->next;
    }
}

sym_t *find_symbol(Elf64_Shdr *shdr, char *strtab, Elf64_Ehdr *elf)
{
    sym_t *symbol = NULL;
    Elf64_Sym *sym;

    for (int i = 0; i < elf->e_shnum; i++) {
        if (shdr[i].sh_type != SHT_SYMTAB)
            continue;
        sym = (Elf64_Sym *)((char *)elf + shdr[i].sh_offset);
        if (!symbol)
            symbol = get_sym_form_tab(sym, strtab,
            shdr[i].sh_size / shdr[i].sh_entsize);
        else
            symbol->next = get_sym_form_tab(sym, strtab,
            shdr[i].sh_size / shdr[i].sh_entsize);
    }
    return symbol;
}