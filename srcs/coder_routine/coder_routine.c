/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 16:21:50 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/27 23:56:06 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>
#include "simulation_control.h"

void	*coder_routine(t_coder *coder)
{
	while (true)
	{
		if (coder->request_two_dongles(coder) == SIMULATION_STOPPED)
			return (NULL);

		coder->reset_deadline(coder);
		coder->log_status(coder, MSG_COMPILE);
		if (coder->execute_task() == SIMULATION_STOPPED)
			return (NULL);
		coder->release_two_dongles();

		coder->log_status(coder, MSG_DEBUG);
		if (coder->execute_task() == SIMULATION_STOPPED)
			return (NULL);

		coder->log_status(coder, MSG_REFACT);
		if (coder->execute_task() == SIMULATION_STOPPED)
			return (NULL);
	}
}
