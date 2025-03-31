/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaualik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:28:07 by alaualik          #+#    #+#             */
/*   Updated: 2025/03/21 15:28:08 by alaualik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

// Built-in unset: removes one or more variables from the environment.
// Usage: unset VAR1 VAR2 ...
int	builtin_unset(int argc, char **argv, char ***env)
{
	int i;
	int j;
	int k;
	int count = 0;
	int varlen;

	// Count current environment size
	while ((*env)[count])
		count++;
	if (argc < 2)
		return (0);
	// Pour chaque variable passée en argument
	i = 1;
	while (i < argc)
	{
		varlen = strlen(argv[i]);
		// Balayage de l'environnement
		j = 0;
		while (j < count)
		{
			// Si la variable commence par argv[i] et est suivie de '='
			if (strncmp((*env)[j], argv[i], varlen) == 0 && (*env)[j][varlen] == '=')
			{
				free((*env)[j]);
				// Décaler les éléments restants vers la gauche
				k = j;
				while (k < count - 1)
				{
					(*env)[k] = (*env)[k + 1];
					k++;
				}
				(*env)[count - 1] = NULL;
				count--;
			}
			else
				j++;
		}
		i++;
	}
	return (0);
}


