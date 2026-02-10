/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 13:06:06 by joesanto          #+#    #+#             */
/*   Updated: 2026/02/10 09:46:17 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "codexion.h"
#include "codexion_parser_internal.h"

enum e_exit_status	codexion_parser(t_codexion_config *config,
									int argc, char **argv)
{
	if (argc-- != 8)
		return (ERR_PARSER_ARGC);
	while (argc-- > 0)
	{
		if (is_str_numeric(argv[argc]) == false)
			return (ERR_PARSER_NOT_DIGIT);
		if (nbrcmp(argv[argc], "0") < 0)
			return (ERR_PARSER_NEG_INT);
		if (nbrcmp(argv[argc], INT_MAX_STR) > 0)
			return (ERR_PARSER_OVERFLOW);
	}
	config->num_coders = atoi(argv[0]);
	if (config->num_coders > MAX_CODERS)
		return (ERR_PARSER_MAX_CODERS);
	config->time_to_burnout = atoi(argv[1]);
	config->time_to_compile = atoi(argv[2]);
	config->time_to_debug = atoi(argv[3]);
	config->time_to_refactor = atoi(argv[4]);
	config->num_compiles_required = atoi(argv[5]);
	config->dongle_cooldown = atoi(argv[6]);
	if (strcmp(argv[7], "fifo") == 0)
		config->scheduler = enqueue;
	else if (strcmp(argv[7], "edf") == 0)
		config->scheduler = priority_enqueue;
	else
		return (ERR_PARSER_SCHEDULER);
	return (SUCCESS);
}
