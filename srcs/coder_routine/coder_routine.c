/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 16:21:50 by joesanto          #+#    #+#             */
/*   Updated: 2026/02/09 20:32:22 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>
#include "coder_internal.h"
#include "simulation_control.h"
#include "dongle_protocols.h"
#include "codexion_config_control.h"
#include "codexion.h"

void	*coder_routine(t_coder *coder)
{
	const t_codexion_config	*config = get_codexion_config();

	if (DEADLINE_START == CODER_START)
		reset_deadline(coder, config->time_to_burnout);
	while (am_i_alive(coder) == true)
	{
		if (request_two_dongles(coder) == SIMULATION_STOPPED)
			return (NULL);

		reset_deadline(coder, config->time_to_burnout);
		log_coder_event(coder, EVENT_COMPILING);
		if (execute_task(coder, config->time_to_compile) == SIMULATION_STOPPED)
			return (NULL);
		release_two_dongles(coder);
		update_compilations_done(coder);

		log_coder_event(coder, EVENT_DEBUGGING);
		if (execute_task(coder, config->time_to_debug) == SIMULATION_STOPPED)
			return (NULL);

		log_coder_event(coder, EVENT_REFACTORING);
		if (execute_task(coder, config->time_to_refactor) == SIMULATION_STOPPED)
			return (NULL);
	}
	return (NULL);
}
