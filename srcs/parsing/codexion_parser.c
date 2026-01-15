/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 13:06:06 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/15 09:44:33 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include "codexion_parser.h"
#include "parsing_errors.h"
#include <string.h>
#include <stdlib.h>

int	codexion_parser(t_codexion *codexion, int argc, char **argv)
{
	if (argc-- != 8)
		return (ARGC_ERROR);
	while (argc-- > 0)
	{
		if (!is_str_numeric(argv[argc]))
			return (NONNUMERIC_ERROR);
		if (nbrcmp(argv[argc], ZERO) < 0)
			return (NEGATIVE_INT_ERROR);
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
	if (strcmp(argv[7], "fifo") == 0)
		codexion->scheduler = fifo_scheduler;
	else if (strcmp(argv[7], "edf") == 0)
		return (0);
	else
		return (SCHEDULER_ERROR);
	return (SUCCESS);
}
