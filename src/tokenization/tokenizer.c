#include "../../include/minishell.h"

char cmd_helper(char *cmd, char *PATH_VARIABLE, int start, int i)
{

    char	*cmd_path;
	char	*potencial_path;

	while (PATH_VARIABLE[i])
	{
		if (PATH_VARIABLE[i] == ':')
		{
			potencial_path = ft_substr(PATH_VARIABLE, start, i - start);
			cmd_path = ft_strjoin(potencial_path, cmd);
			free(potencial_path);
			if (!access(cmd_path, X_OK))
			{
				free(cmd);
				return (1);
			}
			else
				free(cmd_path);
			start = ++i;
		}
		i++;
	}
	return (0);
}

char	is_COMMAND(char *cmd, char *PATH_VARIABLE)
{
	char	*cmd_ath;

	cmd = ft_strjoin("/", cmd);
	cmd_path = cmd_helper(cmd, PATH_VARIABLE, 0, 0);
	return (cmd_path);
}
char  is_COMMAND_FLAG()
{
        

}
    
char is_WORD_NO_INTERPRET()
{
        

}
char is_WORD_INTERPRET()
{


}

char is_INPUT_REDIRECTION()
{


}

char is_OUTPUT_REDIRECTION()
{


}

char is_HERE_DOC()
{


}

char  is_HERE_DOC_DELIMITER()
{
        

}

char is_OUTPUT_REDIRECTION_APPEND_MODE()
{
        

}
    
char is_PIPES()
{


}

char is_ENV_VARIABLE()
{
        
}

char is_BUILTINS ()
{


}


token* tokenizer(char *prompt)
{
    char **split_prompt;

    split_prompt = ft_split(prompt , " \t");





}



