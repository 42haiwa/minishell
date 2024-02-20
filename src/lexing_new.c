/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:36:39 by aallou-v          #+#    #+#             */
/*   Updated: 2024/02/20 18:32:08 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	middle_lexing(t_core *core, char *buf)
{
	if (ft_strlen(buf) == 1)
	{
		if (buf[0] == '\'')
		{
			add_block(core->get_quote[core->lex_count], core, 0);
			core->lex_count++;
			core->lex_bool[0] = 1;
			return (1);
		}
		if (buf[0] == '\"')
		{
			add_block(core->get_d_quote[core->lex_count], core, 0);
			core->lex_count2++;
			core->lex_bool[1] = 1;
			return (1);
		}
	}
}

int	first_lex(char *buf, t_core *core)
{
	if (core->lex_bool[0] || core->lex_bool[1])
		return (1);
	core->lex_n_quote = get_n_char(buf[core->lex_i], '\'');
	core->lex_n_d_quote = get_n_char(buf[core->lex_i], '\"');
	if (core->lex_n_d_quote == 0 || core->lex_n_quote == 0)
		return (0);
	if (ft_strlen(buf) > 1 && buf[0] == '\'' && buf[ft_strlen(buf) - 1] == '\'' && core->lex_n_quote <= 2)
	{
		add_block(core->get_quote[core->lex_count], core, 0);
		core->lex_count++;
		return (1);
	}
	if (ft_strlen(buf) > 1 && buf[0] == '\"' && buf[ft_strlen(buf) - 1] == '\"' && core->lex_n_d_quote <= 2)
	{
		add_block(core->get_d_quote[core->lex_count2], core, 0);
		core->lex_count2++;
		return (1);
	}
	return (middle_lexing(core, buf));
}

void	lexing(char *buf, t_core *core)
{
	char	**splited;

	splited = ft_split(buf, ' ');
	while (splited[++core->lex_i])
	{
		if (!first_lex(splited, core))
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
			ft_check_end_quote(buf, core);
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
		if (buf[i] == '|' || buf[i] == ';' || buf[i] == '>' || buf[i] == '<')
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
