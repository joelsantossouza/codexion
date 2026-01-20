/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 12:16:26 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/20 22:59:49 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_coder_routine.h"

void	*start_working(t_coder *coder)
{
	uint32_t				task;
	const t_coder_config	*config = coder_config(NULL, NULL, NULL, NULL);
	const uint32_t			*tasks = config->tasks;
	const uint32_t			time_to_burnout = config->burnout;
	const char				*msg[NUMBER_OF_TASKS] = {
		COMPILING_MSG,
		DEBUGGING_MSG,
		REFACTORING_MSG
	};

	while (TRUE)
	{
		if (wait_to_compile(coder) == STOP_EXECUTION)
			return (NULL);
		pthread_mutex_lock(&coder->local_mutex);
		coder->execution_remaining = time_to_burnout;
		enqueue(&coder->compilations_history, millis() + tasks[COMPILE]);
		pthread_mutex_unlock(&coder->local_mutex);
		task = 0;
		while (task < NUMBER_OF_TASKS)
		{
			log_coder_activity(coder, msg[task]);
			if (do_task(coder, tasks[task++]) == STOP_EXECUTION)
				return (NULL);
		}
	}
}
