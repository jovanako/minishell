## Minishell grammar

command_line		-> simple_command ('|' command_line)

simple_command		-> (assignment_list)? (redirections)? command (redirections)?
					|	assignment_list (redirections)?

assignment_list		-> assignment (assignment)*

assignment			-> identifier '=' word

command				-> word (word)*

redirections		-> redirection (redirection)*

redirection			-> '<' word
					|	'>' word
					|	'>>' word
					|	'<<' heredoc_delimiter

heredoc_delimiter	-> word

identifier			-> [a-zA-Z_][a-zA-Z0-9_]*

word 				-> [.]+