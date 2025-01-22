/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:07:35 by ngordobi          #+#    #+#             */
/*   Updated: 2025/01/22 13:02:55 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	next_fragment(char *arg, int i, int fragment)
{
	char	q;

	if (fragment == 1)
		while (arg[i] != '\0' && arg[i] != '"' && arg[i] != '\'')
			i++;
	else if (fragment == 2)
	{
		q = arg[i - 1];
		while (arg[i] != '\0' && arg[i] != q)
			i++;
	}
	else if (fragment == 3)
		while (arg[i] != '\0')
			i++;
	else if (fragment == 4)
		while (arg[++i] != '\0')
			if (arg[i] == '"' || arg[i] == '\'')
				break ;
	return (i);
}

char	*quote_fragment(char *arg, char *dup, int i, int j)
{
	char	*sub;
	char	*dup_2;

	if (j > i && dup == NULL)
		dup_2 = ft_substr(arg, i, j - i);
	else if (j > i && dup != NULL)
	{
		sub = ft_substr(arg, i, j - i);
		dup_2 = ft_strjoin(dup, sub);
		free(sub);
	}
	else if (j <= i && dup != NULL)
		dup_2 = ft_strdup(dup);
	if (dup != NULL)
		free(dup);
	return (dup_2);
}

char	*rm_quotes(char *arg, int i)
{
	int		j;
	int		k;
	char	*dup;

	if (ft_strcmp(arg, "''") == 0)
		return (arg);
	if (arg == NULL)
		return (ft_strdup(""));
	i = next_fragment(arg, i, 1);
	if (arg[i] == '\0')
		return (arg);
	dup = NULL;
	if (i > 0)
		dup = ft_substr(arg, 0, i);
	j = next_fragment(arg, ++i, 2);
	dup = quote_fragment(arg, dup, i, j);
	k = ft_strlen(dup);
	i = next_fragment(arg, ++j, 3);
	dup = quote_fragment(arg, dup, j, i);
	if (dup == NULL)
		return (ft_strdup(""));
	i = next_fragment(dup, k - 1, 4);
	if (dup[i] != '\0')
		return (free(arg), rm_quotes(dup, k));
	return (free(arg), dup);
}
