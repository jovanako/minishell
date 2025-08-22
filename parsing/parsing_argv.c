/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_argv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 21:55:41 by jkovacev          #+#    #+#             */
/*   Updated: 2025/08/22 19:26:02 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_token_type	get_token_type(t_list *node)
{
	t_token	*token;

	if (!node)
		return (UNDEFINED);
	token = (t_token *)node->content;
	return (token->type);
}

static int	get_argv_size(char **argv)
{
	int	i;

	i = 0;
	while (argv && argv[i])
		i++;
	return (i);
}

static	bool	add_argument(t_command *cmd, char *arg)
{
	int		i;
	int		argv_size;
	char	**tmp_argv;
	
	argv_size = get_argv_size(cmd->argv);
	tmp_argv = malloc((argv_size + 2) * sizeof(char *));
	if (!tmp_argv)
		return (false);
	i = 0;
	while (i < argv_size)
	{
		tmp_argv[i] = cmd->argv[i];
		i++;
	}
	tmp_argv[i] = arg;
	tmp_argv[i + 1] = NULL;
	free(cmd->argv);
	cmd->argv = tmp_argv;
	return (true);
}

bool	parse_argv(t_parse_ctx *ctx, t_command *command)
{
	while (get_token_type(ctx->current) == WORD_TOKEN)
	{
		if (!add_argument(command, get_current(ctx)->lexeme))
			return (false);
		p_advance(ctx);
	}
	return (true);
}
