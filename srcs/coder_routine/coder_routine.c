/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 16:21:50 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/29 16:21:18 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>
#include "coder_internal.h"
#include "simulation_control.h"

void	*coder_routine(t_coder *coder)
{
	while (true)
	{
		if (request_two_dongles(coder) == SIMULATION_STOPPED)
			return (NULL);

		reset_deadline(coder);
		log_coder_event(coder, EVENT_COMPILING);
		if (execute_task() == SIMULATION_STOPPED)
			return (NULL);
		release_two_dongles();

		log_coder_event(coder, EVENT_DEBUGGING);
		if (execute_task() == SIMULATION_STOPPED)
			return (NULL);

		log_coder_event(coder, EVENT_REFACTORING);
		if (execute_task() == SIMULATION_STOPPED)
			return (NULL);
	}
}
