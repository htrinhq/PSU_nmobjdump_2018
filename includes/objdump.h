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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int my_objdump(const char *file_name, int fd);

#endif
