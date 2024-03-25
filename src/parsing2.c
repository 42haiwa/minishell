/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjouenne <cjouenne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:00:50 by cjouenne          #+#    #+#             */
/*   Updated: 2024/03/25 15:18:21 by cjouenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	verify_token2(size_t *i, t_node **current,
	t_node **father, t_core *core)
{
	if (ft_strncmp(&core->lexer_out[*i], "GREATGREAT", 10) == 0)
	{
		*current = node_init(ft_strdup("GREATGREAT"));
		node_add_son(core->execution_three, *current);
		*father = NULL;
		*i += 10;
		*current = node_init(dup_until(&core->lexer_out[*i], END, 1));
		node_add_son(core->execution_three, *current);
	}
	if (ft_strncmp(&core->lexer_out[*i], "LESS", 4) == 0)
	{
		*current = node_init(ft_strdup("LESS"));
		node_add_son(core->execution_three, *current);
		*father = NULL;
		*i += 4;
		*current = node_init(dup_until(&core->lexer_out[*i], END, 1));
		node_add_son(core->execution_three, *current);
	}
	if (ft_strncmp(&core->lexer_out[*i], "GREAT", 5) == 0)
	{
		*current = node_init(ft_strdup("GREAT"));
		node_add_son(core->execution_three, *current);
		*father = NULL;
		*i += 5;
		*current = node_init(dup_until(&core->lexer_out[*i], END, 1));
		node_add_son(core->execution_three, *current);
	}
}

void	verify_token(size_t *i, t_node **current,
	t_node **father, t_core *core)
{
	if (ft_strncmp(&core->lexer_out[*i], "PIPE", 4) == 0)
	{
		*current = node_init(ft_strdup("PIPE"));
		node_add_son(core->execution_three, *current);
		*father = NULL;
	}
	if (ft_strncmp(&core->lexer_out[*i], "SEMICOLON", 9) == 0)
	{
		*current = node_init(ft_strdup("SEMICOLON"));
		node_add_son(core->execution_three, *current);
		*father = NULL;
	}
	if (ft_strncmp(&core->lexer_out[*i], "LESSLESS", 8) == 0)
	{
		*current = node_init(ft_strdup("LESSLESS"));
		node_add_son(core->execution_three, *current);
		*father = NULL;
		*i += 8;
		*current = node_init(dup_until(&core->lexer_out[*i], END, 1));
		node_add_son(core->execution_three, *current);
	}
	verify_token2(i, current, father, core);
}
