/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnstr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbrah <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:35:57 by aaitbrah          #+#    #+#             */
/*   Updated: 2024/10/09 14:35:58 by aaitbrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t	i;
	size_t	len;

	i = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (big[i] != '\0')
	{
		len = 0;
		while (big[i + len] == little[len] && (i + len) < n)
		{
			if (big[i + len] == '\0' && little[len] == '\0')
				return ((char *)&big[i]);
			len++;
		}
		if (little[len] == '\0')
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
