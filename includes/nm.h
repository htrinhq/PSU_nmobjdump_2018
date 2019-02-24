/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** nm
*/

#ifndef NM_H_
#define NM_H_

#include <elf.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ctype.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <libelf.h>
#include <zconf.h>
#include <string.h>
#include <sys/mman.h>
#include "flags.h"

typedef struct sym {
    char *name;
    char type;
    unsigned long long value;
    struct sym *next;
} sym_t;

void print_sym(sym_t *symbol);
sym_t *find_symbol(Elf64_Shdr *shdr, char *strtab, Elf64_Ehdr *elf);
sym_t *find_symbol(Elf64_Shdr *shdr, char *strtab, Elf64_Ehdr *elf);
sym_t *get_sym_form_tab(Elf64_Sym *sym, char *strtab, size_t nb);
int nm64(Elf64_Ehdr *elf);
int check_file(const char *filename, struct stat f_info);
int check_elf_format(Elf64_Ehdr *elf, const char *filename);

#endif
