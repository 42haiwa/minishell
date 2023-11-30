/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:37:49 by cjouenne          #+#    #+#             */
/*   Updated: 2023/11/30 21:30:31 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*buf;
	t_env	env;

	buf = NULL;
	(void) argc;
	(void) argv;
	(void) envp;
	parse_envp(envp, &env);
	while (1)
	{
		buf = readline(PROMPT);
		check_builtins(buf);
	}
}
