/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharik <acharik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 08:24:20 by acharik           #+#    #+#             */
/*   Updated: 2023/11/28 05:55:42 by acharik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void 	ft_free_split(char **split)
{
    int i ;

    i = 0; 

    while(split[i])
    {
        free(split[i]);
        i++;
    }
    free(split);



}