/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjouenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:38:53 by cjouenne          #+#    #+#             */
/*   Updated: 2023/12/08 16:24:13 by cjouenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process(int sig)
{
	if (sig == SIGINT)
	{
		kill(g_core->son_pid, SIGINT);
	}
}

void	handler(int sig)
{
	if (g_core->son_pid > 0)
	{
		process(sig);
		return;
	}
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
