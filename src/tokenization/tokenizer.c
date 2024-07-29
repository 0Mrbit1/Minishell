#include "../../include/minishell.h"


token* tokenizer(char *prompt)
{
    char **split_prompt_spaces;
    char **split_prompt_tabs;

    split_prompt_spaces = ft_split(prompt , ' ');
    
    split_prompt_tabs = ft_split(prompt , '\t'); 



}



