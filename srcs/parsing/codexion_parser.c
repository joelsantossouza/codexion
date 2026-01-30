/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 13:06:06 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/29 23:33:26 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "codexion_parser_internal.h"
#include "schedulers.h"

enum e_exit_status	codexion_parser(t_codexion *codexion, int argc, char **argv)
{
	if (argc-- != 8)
		return (ERR_PARSER_ARGC);
	while (argc-- > 0)
	{
		if (is_str_numeric(argv[argc]) == false)
			return (ERR_PARSER_NOT_DIGIT);
		if (nbrcmp(argv[argc], "0") < 0)
			return (ERR_PARSER_NEG_INT);
		if (nbrcmp(argv[argc], INT_MAX) > 0)
			return (ERR_PARSER_OVERFLOW);
	}
	codexion->number_of_coders = atoi(argv[0]);
	codexion->time_to_burnout = atoi(argv[1]);
	codexion->time_to_compile = atoi(argv[2]);
	codexion->time_to_debug = atoi(argv[3]);
	codexion->time_to_refactor = atoi(argv[4]);
	codexion->number_of_compiles_required = atoi(argv[5]);
	codexion->dongle_cooldown = atoi(argv[6]);
	if (strcmp(argv[7], "fifo") == 0)
		codexion->wait_turn = wait_fifo_turn;
	else if (strcmp(argv[7], "edf") == 0)
		;
		//codexion->wait_turn = NULL;
	else
		return (ERR_PARSER_SCHEDULER);
	return (SUCCESS);
}
