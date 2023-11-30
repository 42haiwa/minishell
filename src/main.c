/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: cjouenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:37:49 by cjouenne          #+#    #+#             */
/*   Updated: 2023/11/30 16:50:29 by cjouenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*buf;

	buf = NULL;
	(void) argc;
	(void) argv;
	(void) envp;
	while (1)
	{
		buf = readline(PROMPT);
	}
=======
/*   By: aallou-v <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:26:01 by aallou-v          #+#    #+#             */
/*   Updated: 2023/11/30 15:26:29 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	main(int argc, char **argv)
{
	return (0);
>>>>>>> 9bf2c31229a4e353e37210f9d1831eecdc11c569
}
