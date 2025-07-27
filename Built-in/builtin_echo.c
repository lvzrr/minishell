/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 20:06:26 by marvin            #+#    #+#             */
/*   Updated: 2025/07/27 20:06:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtsin.h"

/*Usamos esta función para determinar las flags y escapes que nos envían y
discriminarlas para poder escribirlas apropiadamente.
Con com_tf parseamos las flags para, una vez terminadas de evaluar todas, 
imprimir el resto de ordenes acorde a las flags recibidas.
A priori Shell el comando echo solo trata las flags que aparecen antes del 
primer argumento que hay que imprimir*/

int builtin_echo(int argc, char **argv, char **envp)
{
    bool com_n;
    bool com_e;
    int i;

    com_n = false;
    com_e = false;
    i = 1;
    while(i< argc && is_flag(argv[i]))
    {
        com_tf(argv[i], &com_n, &com_e);
        i++;
    }
    while (i < argc)
    {
        if (com_e == true)
            write_echo_e(argv[i]);
        else
            write_echo(argv[i]);
        if (i + 1 < argc)
            write(1, " ", 1);
        i++;
    }
    if (com_n == false)
        write(1, "\n", 1);
    return (0);
}