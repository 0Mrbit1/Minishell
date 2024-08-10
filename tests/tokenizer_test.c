/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdellah <abdellah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 16:47:09 by abdellah          #+#    #+#             */
/*   Updated: 2024/08/10 16:47:12 by abdellah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

token* setup_first_node(char **split_prompt , redir_func_ptr *redirection_functions)
{
    int j;
    token* first_node ; 

    j = 0 ;
    while (j < 6) 
    {
        if (redirection_functions[j](split_prompt[0]))
        {
            first_node = malloc(sizeof(token));
            first_node -> value = ft_strdup(split_prompt[0]) ;
            first_node -> token_type =  j;
            first_node -> next = NULL;
            return first_node;
		}
		j++;
	}
    return NULL;
}

void setup_nodes(char **split_prompt , redir_func_ptr *redirection_functions , token **first_node , int i , int j)
{
    token* node;

    node = *first_node; 
    while (split_prompt[i])
    {
		while (j < 6) 
        {
			if (redirection_functions[j](split_prompt[i]))
            {
				node -> next = malloc(sizeof(token));   
                node = node -> next;
                node -> value = ft_strdup(split_prompt[i]) ;
                node -> token_type =  j;
                node -> next = NULL ;
                break;
			}
			j++;
		}
        j = 0 ; 
		i++;
	}
}

token* tokenizer(char *prompt)
{
	typedef char (*redir_func_ptr)(char*);
	char **split_prompt;
    token* first_node;

	redir_func_ptr redirection_functions[] = {
        is_HERE_DOC,
		is_INPUT_REDIRECTION,
		is_OUTPUT_REDIRECTION_APPEND_MODE,
        is_OUTPUT_REDIRECTION,
		is_PIPES,
		is_WORD
	};
    split_prompt = ft_split(prompt, " \t");
    first_node = setup_first_node(split_prompt , redirection_functions);
    setup_nodes(split_prompt ,redirection_functions ,&first_node , 1 , 0);
    ft_free_split(split_prompt);
	return first_node;
}


int main(int argc  , char **argv )
{
    token *node; 
    token *first_node;
    token *to_free;

    node = tokenizer(argv[1]) ;
    first_node = node ; 
    
    while(node)
    {
        printf("value %s\n" , node->value);
         printf("type %u\n" , node->token_type);
         printf("________________________________\n");
        node = node-> next ; 
    }
    node = first_node ; 

    while(node)
    {
        to_free = node ; 
        free(node->value) ;
        node = node -> next ; 
        free(to_free);
    }

}