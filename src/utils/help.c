/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 01:15:54 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/19 01:16:16 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	phelp(void)
{
	ft_printf(ANSI_MAGENTA"mini - a POSIX-like shell\n"ANSI_RESET
		"usage: minishell [--debug] [-c 'command']\n\n"
		ANSI_GREEN"options:\n"ANSI_RESET
		"  --debug          enable verbose debug output"
		" (lexer, parser, heredoc streams)\n"
		"  -c <command>     run a one-liner and exit\n"
		ANSI_GREEN"features:\n"ANSI_RESET
		"  heredoc          << operator with proper quote handling\n"
		"  token joining    merges adjacent tokens into composite strings\n"
		"  variable syntax  $VAR, \"$VAR\" supported\n"
		"  env scope        export, unset, and dynamic env available\n"
		"  builtins         echo, cd, exit, export, unset, env\n"
		"  signal handling  proper SIGINT/SIGQUIT integration\n"
		"  command chaining supports &&, || in grouped () blocks\n"
		"  redirections     <, >, >> with proper fd management\n"
		"  pipelines        command1 | command2 | command3 supported\n"
		"  syntax errors    parser catches malformed constructs\n"
		"  shell level      SHLVL increments across spawns\n"
		"\n"
		ANSI_YELLOW"limitations:\n"ANSI_RESET
		"  no job control   fg/bg/suspend not implemented\n"
		"  no globbing      ?, [] wildcards are expanded only in '.'\n"
		"\n"
		"for more info: read the code, xx\n"
		);
}
