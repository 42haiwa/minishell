/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjouenne <cjouenne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 19:47:31 by aallou-v          #+#    #+#             */
/*   Updated: 2024/03/12 15:15:18 by cjouenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(t_core *core)
{
	char	*path;

	core->err_code = 0;
	path = getcwd(NULL, 0);
	printf("%s\n", path);
	free(path);
}
