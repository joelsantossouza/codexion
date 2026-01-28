/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 16:21:50 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/28 11:32:39 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>
#include "simulation_control.h"

void	*coder_routine(t_coder *coder)
{
	while (true)
	{
		if (request_two_dongles(coder) == SIMULATION_STOPPED)
			return (NULL);

		reset_deadline(coder);
		log_status(coder, MSG_COMPILE);
		if (execute_task() == SIMULATION_STOPPED)
			return (NULL);
		release_two_dongles();

		log_status(coder, MSG_DEBUG);
		if (execute_task() == SIMULATION_STOPPED)
			return (NULL);

		log_status(coder, MSG_REFACT);
		if (execute_task() == SIMULATION_STOPPED)
			return (NULL);
	}
}
