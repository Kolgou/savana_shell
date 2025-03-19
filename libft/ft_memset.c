/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbrah <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:07:51 by aaitbrah          #+#    #+#             */
/*   Updated: 2024/10/08 14:07:53 by aaitbrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int i, size_t taille)
{
	unsigned char	*c;

	c = str;
	while (taille > 0)
	{
		*c = i;
		c++;
		taille--;
	}
	return (str);
}
