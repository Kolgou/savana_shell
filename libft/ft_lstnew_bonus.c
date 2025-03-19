/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbrah <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:44:21 by aaitbrah          #+#    #+#             */
/*   Updated: 2024/10/18 12:44:23 by aaitbrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*contento;

	contento = (t_list *)malloc(sizeof(*contento));
	if (!contento)
		return (NULL);
	contento->next = NULL;
	contento->content = content;
	return (contento);
}
