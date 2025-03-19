/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbrah <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:10:23 by aaitbrah          #+#    #+#             */
/*   Updated: 2024/10/16 16:10:25 by aaitbrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(char const *s, char c)
{
	char	last;
	int		i;
	int		j;

	last = c;
	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (last == c && s[i] != c)
		{
			j++;
		}
		last = s[i];
		i++;
	}
	return (j);
}

static char	*ft_create_word(const char *s, char c, int *i)
{
	int		j;
	int		z;
	char	*small;

	j = 0;
	while (s[*i + j] != '\0' && s[*i + j] != c)
	{
		j++;
	}
	small = (char *)malloc((j + 1) * sizeof(char));
	if (!small)
		return (NULL);
	z = 0;
	while (z < j)
	{
		small[z] = s[*i];
		z++;
		(*i)++;
	}
	small[j] = '\0';
	return (small);
}

static void	*ft_freeall(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		y;
	char	**res;

	if (s == NULL)
		return (NULL);
	res = (char **)malloc((ft_count(s, c) + 1) * sizeof(*res));
	if (!res)
		return (NULL);
	i = 0;
	y = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		res[y] = ft_create_word(s, c, &i);
		if (!res[y])
			return (ft_freeall(res));
		y++;
	}
	res[y] = NULL;
	return (res);
}
