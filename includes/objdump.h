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

#endif
