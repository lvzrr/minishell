/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 21:53:51 by marvin            #+#    #+#             */
/*   Updated: 2025/07/27 21:53:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtsin.h"

/*Comprobamos si una cadena representa una flag válida para el comando echo.
Verificamos que la flag comience con un '-' y que contenga únicamente los
caracteres "n", "e" y "E" */
int     is_flag(const char *argv)
{
    int i = 1;
    if (argv[0] != '-' || argv[1] == '\0')
        return 0;
    while (argv[i])
    {
        if (argv[i] != 'n' && argv[i] != 'e' && argv[i] != 'E')
            return 0;
        i++;
    }
    return 1;
}
/*Comprobación de si el número es hexadecimal*/
int ishexdigit(unsigned char c)
{
    if ( (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'))
        return(1);
    else
        return (0);
}
/*Conversión número a hexadecimal*/
int hex_conv(char c)
{
    if (c >= '0' && c <= '9')
        c = c - '0'; 
    else if (c >= 'a' && c <= 'f')
        c = c - 'a' + 10;
    else if (c >= 'A' && c <= 'F')
        c = c - 'A' + 10;
    else
        return (-1);
    return (c);
}

void    print_char(int value, int *i)
{
    char c;

    c = (char)value;
    write(1, &c, 1);
    (*i)--;                            // Hay que retroceder porque el bucle principal va a avanzar.
}
/* En esta función comprobamos las flags.
La flag n puede aparecer de multiples formas ("-n", "-nn" "-nnn") y con esto cubrimos todas
las posibilidades.
La flag E desactiva a la flag e siempre que aparezca antes que ella, por eso es el mismo
bool para ambos casos */
void    com_tf(const char *str, bool *com_n, bool *com_e)
{
    int i;

    i = 1;
    while(str[i])
    {
        if(str[i] == 'n')
            *com_n = true;
        else if (str[i] == 'e')
            *com_e = true;
        else if (str[i] == 'E')
            *com_e = false;
        i++;
    }
}