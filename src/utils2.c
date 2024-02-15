/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 04:00:35 by aallou-v          #+#    #+#             */
/*   Updated: 2024/02/15 14:15:52 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_ending(char c)
{
	return (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '$' || c == '\''
		|| c == '\t' || c == '\v' || c == '\"');
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	get_n_char(const char *s1, char c)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (s1[++i])
	{
		if (s1[i] == c)
			count++;
	}
	return (count);
}
