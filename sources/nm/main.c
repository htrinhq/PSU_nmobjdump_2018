/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** main
*/

#include "nm.h"

int main(int argc, char const *argv[])
{
    if (argc != 2)
        return 84;
    printf("NM: %s\n", argv[1]);
    return 0;
}
