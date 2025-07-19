/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_parser.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:29:24 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/18 12:30:04 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_PARSER_H
# define MINI_PARSER_H

# include "mini_lexer.h"

void	collapse_at(t_vec *tokv, t_tok *t);
void	collapse_to_delim(t_vec *tokv, t_tok *t);
void	join_seq(t_vec *tokv);
void	var_recon(t_vec *tokv);
void	var_recon_instr(t_vec *tokv);
void	del_unused(t_vec *tokv, size_t idx);
#endif
