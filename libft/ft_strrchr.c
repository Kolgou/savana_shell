/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbrah <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:45:45 by aaitbrah          #+#    #+#             */
/*   Updated: 2024/10/08 16:45:46 by aaitbrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	*ptr;

	i = ft_strlen(str);
	ptr = (char *)str;
	while (i >= 0)
	{
		if ((unsigned char)c == ptr[i])
		{
			while (ptr[i])
			{
				return (&ptr[i]);
			}
			i++;
		}
		i--;
		if ((unsigned char)c == ptr[i])
			return (&ptr[i]);
	}
	return (NULL);
}
