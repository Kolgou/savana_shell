/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbrah <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:52:17 by aaitbrah          #+#    #+#             */
/*   Updated: 2024/10/18 16:52:19 by aaitbrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*dest;

	if (!*lst || !del || !lst)
		return ;
	while (*lst)
	{
		dest = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = dest;
	}
	(*lst) = NULL;
}
