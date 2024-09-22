Parsing  : 

what i did here :  

i initialize the commond structure :
allocate space for the command's arguments, starting with a predefined size (INITIAL_ARGS_SIZE) just for now we 
will deal whit that 'later' [ donst matter now ] !!!
 
then i looped to check the token is a word (if a word are set or not)
 
if a command is already set store the current token as an argument then i check the token is an "INPUT_REDIRECTION"   (<)
if yes :
	move to the next token and store it as the input file
if not :  
	i have to have to free.
"
	if (!tokens || tokens->token_type != WORD) 
	{
   		 free_command(cmd);
   	 	  return NULL;
	}
if the token is an OUTPUT_REDIRECTION (>)
	move to the next token and store it as the output file

==> and then (*_*)

set the append mode if redirection is >> 

---------------------- 
	
if the token is a PIPE  ( | ) 

it recursively parses the next command and store it in a linked list usng "cmd->next"
i call parse_command()  recursively to handle the next command in the pipeline
" cmd->next = parse_command(tokens->next); "
pipes in parsing : When the parser encounters a pipe (|) 

____________________________________
