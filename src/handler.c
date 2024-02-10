/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:38:53 by cjouenne          #+#    #+#             */
/*   Updated: 2024/02/10 03:58:50 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("\b\b	\b\b", 1);
	}
}

void	handler2(int sig, siginfo_t *info, void *ucontext)
{
	(void) sig;
	(void) info;
	(void) ucontext;
	//ft_putstr_fd("\b\b	\b\b	\b\b", 1);
}
