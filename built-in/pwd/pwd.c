/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaualik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 22:56:57 by alaualik          #+#    #+#             */
/*   Updated: 2025/03/20 22:56:58 by alaualik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    size_t size = 1024;
    char *buffer = malloc(size);

    if (buffer == NULL)
    {
        perror("malloc");
        return 1;
    }
    if (getcwd(buffer, size) != NULL)
        printf("%s\n", buffer);
    else
    {
        perror("getcwd");
        free(buffer);
        return 1;
    }
    free(buffer);
    return 0;
}
