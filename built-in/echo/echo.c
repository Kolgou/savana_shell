/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaualik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 20:00:56 by alaualik          #+#    #+#             */
/*   Updated: 2025/03/21 20:00:57 by alaualik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_n_option(const char *str)
{
    if (str[0] != '-')
        return (false);

    int i = 1;
    while (str[i] != '\0')
    {
        if (str[i] != 'n')
            return (false);
        i++;
    }

    return (str[1] != '\0');
}

void my_echo(int ac, char **av)
{
    bool n_option = false;

    int i = 1;
    while (i < ac && is_n_option(av[i]))
    {
        n_option = true;
        i++;
    }

    while (i < ac)
    {
        printf("%s", av[i]);
        i++;
        if (i < ac)
            printf(" ");
    }

    if (!n_option)
        printf("\n");
}

int main(int ac, char **av)
{
    my_echo(ac, av);
    return (0);
}
