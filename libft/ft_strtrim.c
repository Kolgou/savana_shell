/* ************************************************************************** */
/*                                                                   	      */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbrah <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:14:23 by aaitbrah          #+#    #+#             */
/*   Updated: 2024/10/14 15:14:25 by aaitbrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_verif_set(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	s1_len;
	char	*dest;

	i = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	while (ft_verif_set(s1[i], set))
		s1++;
	s1_len = ft_strlen(s1);
	while (s1_len > 0 && ft_verif_set(s1[s1_len - 1], set))
		s1_len--;
	dest = ft_calloc(s1_len + 1, sizeof(char));
	if (dest == NULL)
		return (NULL);
	ft_memcpy(dest, s1, s1_len);
	return (dest);
}
