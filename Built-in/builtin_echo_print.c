/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 12:35:42 by marvin            #+#    #+#             */
/*   Updated: 2025/07/27 12:35:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtsin.h"


void    write_echo(const char *argv)
{
    int i;

    i = 0;
    while (argv[i])
    {
        write(1, &argv[i], 1);
        i++;
    }
}
/*Esta función la utilizamos para procesar e imprimir un caracter octal*/
void    write_oct(unsigned char *argv, int *i)
{
    int count;
    int value;
    char    c;

    count = 0;
    value = 0;
    while (count < 3 && argv[*i] && argv[*i] >= '0' && argv[*i] <= '7')
    {
        value = value * 8 + (argv[*i] - '0');
        (*i)++;
        count++;
    }
    c = (char)value;
    write(1, &c, 1);
    (*i)--;
}
/*Esta función la utilizamos para procesar un caracter hexadecimal (máximo
dos dígitos hexadecimales consecutivos) e imprimirlo.

ishexdigit comprueba que el número sea hexadecimal

hex_conv lo transforma

Si no encuentra caracter válido imprime \x y retrocede el índice para
no perder el caracter actual*/
void    write_hex(unsigned char *argv, int *i)
{
        int val;
        int count;
        int digit;

        val = 0;
        count = 0;
        (*i)++;
        while (count < 2 && argv[*i] && ishexdigit((unsigned char) argv[*i]))
        {
            digit = hex_conv(argv[*i]);
            if (digit == -1)
                break ;
            val = val * 16 + digit;
            (*i)++;
            count++;
        }
        if (count > 0)
            print_char(val, i);     
        else
        {
            write(1, "\\x", 2);
            (*i)--;                     
        }
}

/* Con esta función procesamos las secuencias de escape que se producen después
de un "\"
Añadimos un retorno para poder cancelar la impresión con el comando "\c"*/
int    com_letters(unsigned char *argv, int *i)
{
    if (argv[*i] == 'a')
        write(1, "\a", 1);
    else if (argv[*i] == 'b')               
        write(1, "\b", 1);
    else if (argv[*i] == 'c')                //El comando \c detiene directamente la impresión.
        return (0);
    else if (argv[*i] == 'n')
        write(1, "\n", 1);
    else if (argv[*i] == 'r')
        write(1, "\r", 1);
    else if (argv[*i] == 't')
        write(1, "\t", 1);
    else if (argv[*i] == 'v')
        write(1, "\v", 1);
    else if (argv[*i] == 'x')
        write_hex(argv, i);
    else if (argv[*i] >= '0' && argv[*i] <= '7')
        write_oct(argv, i);
    else
    {
        write(1, "\\", 1);
        write(1, &argv[*i], 1);
    }
    return 1;
}

/* La función se utiliza para imprimir una cadena interpretando
las salidas de escape "\n"
Usamos la función com_letteres para interpretar las secuencias de escape
Añadimos un break en esa función en caso de la secuencia "\c"
Si no hay secuencia imprime los caracteres tal cual*/
void    write_echo_e(const char *argv)
{
    int i;

    i = 0;
    while (argv[i])
    {
        if (argv[i] == '\\')
        {
            i++;
            if (argv[i] == '\0') 
            {
                write(1, "\\", 1);
                break ;
            }
            if (!com_letters((unsigned char *) argv, &i))
                break ;
        }
        else
            write(1, &argv[i], 1);
        i++;
    } 
}