/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 13:06:06 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/06 13:48:01 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_errors.h"
#include <string.h>

int	codexion_parser(t_codexion *codexion, int argc, char **argv)
{
	if (argc != 8)
		return (ARGC_ERROR);
	argc--;
	if (strcmp(argv[argc], "fifo") || strcmp(argv[argc], "edf"))
		return (SCHEDULER_ERROR);
	while (argc--)
	{
		if (!str_is_numeric(argv[argc]))
			return (NONNUMERIC_ERROR);
		if (nbrcmp(argv[argc], INT_MIN) < 0)
			return (INT_UNDERFLOW);
		if (nbrcmp(argv[argc], INT_MAX) > 0)
			return (INT_OVERFLOW);
	}
	codexion->number_of_coders = atoi(argv[0]);
	codexion->time_to_burnout = atoi(argv[1]);
	codexion->time_to_compile = atoi(argv[2]);
	codexion->time_to_debug = atoi(argv[3]);
	codexion->time_to_refactor = atoi(argv[4]);
	codexion->number_of_compiles_required = atoi(argv[5]);
	codexion->dongle_cooldown = atoi(argv[6]);
	codexion->scheduler = argv[7];
	return (SUCCESS);
}
