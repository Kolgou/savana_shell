/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbrah <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:01:04 by aaitbrah          #+#    #+#             */
/*   Updated: 2024/10/10 14:01:06 by aaitbrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*csrc;
	char	*cdst;

	cdst = (char *)dest;
	csrc = (char *)src;
	if (!dest && !src)
		return (NULL);
	if (dest <= src)
	{
		while (n--)
			*cdst++ = *csrc++;
	}
	else if (dest > src)
	{
		cdst += n - 1;
		csrc += n - 1;
		while (n--)
			*cdst-- = *csrc--;
	}
	return (dest);
}
