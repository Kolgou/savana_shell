/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbrah <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:45:48 by aaitbrah          #+#    #+#             */
/*   Updated: 2024/10/14 11:45:49 by aaitbrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1_l;
	int		s2_l;
	char	*dest;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	s1_l = ft_strlen(s1);
	s2_l = ft_strlen(s2);
	dest = (char *)malloc(s1_l + s2_l + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (i < s1_l)
	{
		dest[i] = s1[i];
		i++;
	}
	while (i < s1_l + s2_l)
	{
		dest[i] = s2[i - s1_l];
		i++;
	}
	dest[s1_l + s2_l] = '\0';
	return (dest);
}
