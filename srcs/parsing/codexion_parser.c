/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 13:06:06 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/20 18:55:56 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "errors.h"
#include "private_codexion_parser.h"
#include "private_monitor_routine.h"

int	codexion_parser(t_codexion *codexion, int argc, char **argv)
{
	if (argc-- != 8)
		return (ARGC_ERROR);
	while (argc-- > 0)
	{
		if (is_str_numeric(argv[argc]) != 0)
			return (NONNUMERIC_ERROR);
		if (nbrcmp(argv[argc], ZERO) < 0)
			return (NEGATIVE_INT_ERROR);
		if (nbrcmp(argv[argc], INT_MAX) > 0)
			return (INT_OVERFLOW_ERROR);
	}
	codexion->number_of_coders = atoi(argv[0]);
	codexion->time_to_burnout = atoi(argv[1]);
	codexion->time_to_compile = atoi(argv[2]);
	codexion->time_to_debug = atoi(argv[3]);
	codexion->time_to_refactor = atoi(argv[4]);
	codexion->number_of_compiles_required = atoi(argv[5]);
	codexion->dongle_cooldown = atoi(argv[6]);
	if (strcmp(argv[7], "fifo") == 0)
		codexion->scheduler = schedule_fifo;
	else if (strcmp(argv[7], "edf") == 0)
		codexion->scheduler = NULL;
	else
		return (SCHEDULER_ERROR);
	return (SUCCESS);
}
