/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:36:39 by aallou-v          #+#    #+#             */
/*   Updated: 2024/02/15 18:39:53 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	first_lexing(t_core *core, char **splited)
{
	if (splited[core->lex_i][0] == '\"'
		&& !core->lex_bool[0] && !core->lex_bool[1])
	{
		add_block(core->get_d_quote[core->lex_count], core, 0);
		core->lex_bool[0] = 1;
		core->lex_count++;
		if (splited[core->lex_i][ft_strlen(splited[core->lex_i]) - 1] == '\"'
			&& ft_strlen(splited[core->lex_i]) > 1)
			core->lex_bool[0] = 0;
		return (1);
	}
	else if (splited[core->lex_i][0] == '\'' && !core->lex_bool[1]
		&& !core->lex_bool[0])
	{
		add_block(core->get_quote[core->lex_count2], core, 0);
		core->lex_bool[1] = 1;
		core->lex_count2++;
		if (splited[core->lex_i][ft_strlen(splited[core->lex_i]) - 1] == '\''
			&& ft_strlen(splited[core->lex_i]) > 1)
			core->lex_bool[1] = 0;
		return (1);
	}
	return (0);
}

void	end_lexing(char **splited, t_core *core)
{
	core->lex_i = 0;
	while (splited[core->lex_i])
	{
		free(splited[core->lex_i]);
		core->lex_i++;
	}
	free(splited);
}

void	middle_lexing(t_core *core, char **splited)
{
	if (splited[core->lex_i][ft_strlen(splited[core->lex_i]) - 1] == '\"')
		core->lex_bool[0] = 0;
	if (splited[core->lex_i][ft_strlen(splited[core->lex_i]) - 1] == '\'')
		core->lex_bool[1] = 0;
}

void	lexing(char *buf, t_core *core)
{
	char	**splited;

	splited = ft_split(buf, ' ');
	while (splited[++core->lex_i])
	{
		if (first_lexing(core, splited) == 0)
		{
			if (!core->lex_bool[0] && !core->lex_bool[1])
			{
				if (get_delimiter(splited[core->lex_i]))
					add_block(get_delimiter(splited[core->lex_i]), core, 1);
				else
				{
					if (splited[core->lex_i][0] != '$')
						add_block(splited[core->lex_i], core, 0);
					else
						add_block(get_envp(ft_strchr(splited[core->lex_i],
									splited[core->lex_i][1]), core), core, 0);
				}
			}
			else
				middle_lexing(core, splited);
		}
	}
	end_lexing(splited, core);
}

void	pre_lexing(char *buf, t_core *core)
{
	size_t	i;

	core->get_d_quote = get_double_quote(buf);
	core->get_quote = get_quote(buf);
	replace_main(core);
	i = -1;
	while (buf[++i])
	{
		if (buf[i] == '|' || buf[i] == ';' || buf[i] == '\"'
			|| buf[i] == '>' || buf[i] == '<' || buf[i] == '\'')
		{
			if (buf[i + 1] != ' ')
				buf = add_char(buf, ' ', i + 1);
			if (i > 0 && buf[i - 1] != ' ')
				buf = add_char(buf, ' ', i);
		}
		if (buf[i] == '$')
		{
			if (buf[i - 1] != ' ' && buf[i - 1] != '$')
				buf = add_char(buf, ' ', i);
		}
	}
	init_lexing(core);
	lexing(buf, core);
	free(buf);
}
