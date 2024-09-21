#include "mini_shell.h"


// tokenize and parse the input

int main()
{
      char *input = NULL;
      token *tokens = NULL;
      t_command *cmd_list = NULL;

    while (1337) 
    {
        input=readline("minishell(*-*)> ");
        
        /******/   
        
        tokens = tokenizer(input);   
        cmd_list = parse_command(tokens);

        // here Ms.bit  i did a test to execute the parsed commands /*it wrk*/ok
        // execute_pipeline(cmd_list); ;) 
        /*******
         * 
         * 
         * 
        */
        // free memory after execution
        print_parsed_command(cmd_list);
        free(input);
        input = NULL;
     }
    return 0;
}
 