/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbrah <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:32:01 by aaitbrah          #+#    #+#             */
/*   Updated: 2024/10/10 13:32:02 by aaitbrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t len)
{
	const unsigned char	*s1_c;
	const unsigned char	*s2_c;

	s1_c = s1;
	s2_c = s2;
	while (len > 0)
	{
		if (*s1_c != *s2_c)
			return (*s1_c - *s2_c);
		len--;
		s1_c++;
		s2_c++;
	}
	return (0);
}
