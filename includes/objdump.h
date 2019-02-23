/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** objdump
*/

#ifndef OBJDUMP_H_
#define OBJDUMP_H_

#include <elf.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <libelf.h>
#include <zconf.h>
#include <string.h>
#include <sys/mman.h>
#include "flags.h"

int my_objdump(int fd, const char *filename);
void display_section_parser(Elf64_Shdr *shdr, char *strtab,
size_t i, size_t shifted);
void display_header(Elf64_Ehdr *elf, Elf64_Shdr *shdr, const char *filename);
void display_sections(Elf64_Ehdr *elf, Elf64_Shdr *shdr,
char *strtab, void *data);
void display_flags(size_t flags);
void print_section(size_t shifted, unsigned char *strtab,
Elf64_Shdr *shdr, size_t size);
int get_zero(size_t nb);
size_t get_flags(Elf64_Ehdr *elf, Elf64_Shdr *shdr);
int check_elf_format(Elf64_Ehdr *elf);
void display_section_parser32(Elf32_Shdr *shdr, char *strtab,
size_t i, size_t shifted);
void display_header32(Elf32_Ehdr *elf, Elf32_Shdr *shdr, const char *filename);
void display_sections32(Elf32_Ehdr *elf, Elf32_Shdr *shdr,
char *strtab, void *data);
void print_section32(size_t shifted, unsigned char *strtab,
Elf32_Shdr *shdr, size_t size);
size_t get_flags32(Elf32_Ehdr *elf, Elf32_Shdr *shdr);

#endif
