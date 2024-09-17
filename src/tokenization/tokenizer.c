/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdellah <abdellah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 16:47:42 by abdellah          #+#    #+#             */
/*   Updated: 2024/08/10 16:55:30 by abdellah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


token	*setup_first_node(char **split_prompt,
		redir_func_ptr *redirection_functions)
{
	int		j;
	token	*first_node;

	j = 0;
	while (j < 6)
	{
		if (redirection_functions[j](split_prompt[0]))
		{
			first_node = malloc(sizeof(token));
			first_node->value = ft_strdup(split_prompt[0]);
			first_node->token_type = j;
			first_node->next = NULL;
			return (first_node);
		}
		j++;
	}
	return (NULL);
}

void	setup_nodes(char **split_prompt, redir_func_ptr *redirection_functions,
		token **first_node, int i)
{
	token	*node;
	int		j;

	node = *first_node;
	j = 0;
	while (split_prompt[i])
	{
		while (j < 6)
		{
			if (redirection_functions[j](split_prompt[i]))
			{
				node->next = malloc(sizeof(token));
				node = node->next;
				node->value = ft_strdup(split_prompt[i]);
				node->token_type = j;
				node->next = NULL;
				break ;
			}
			j++;
		}
		j = 0;
		i++;
	}
}

token	*tokenizer(char *prompt)
{
	redir_func_ptr	redirection_functions[6];
	char			**split_prompt;
	token			*first_node;

	redirection_functions[0] = is_HERE_DOC;
	redirection_functions[1] = is_INPUT_REDIRECTION;
	redirection_functions[2] = is_OUTPUT_REDIRECTION_APPEND_MODE;
	redirection_functions[3] = is_OUTPUT_REDIRECTION;
	redirection_functions[4] = is_PIPES;
	redirection_functions[5] = is_WORD;
	split_prompt = ft_split(prompt, " \t");
	first_node = setup_first_node(split_prompt, redirection_functions);
	setup_nodes(split_prompt, redirection_functions, &first_node, 1);
	ft_free_split(split_prompt);
	return (first_node);
}
