/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 23:45:32 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/28 23:46:29 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

bool	check_redir(t_tok *t)
{
	if (access(t->s.data, F_OK) == -1)
		return (err_file("cannot redirect from a nonexistent file\n",
				t->s.data), false);
	if (access(t->s.data, R_OK) == -1)
		return (err_file("cannot read from file\n",
				t->s.data), false);
	return (true);
}
