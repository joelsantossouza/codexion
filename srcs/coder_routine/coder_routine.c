/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 12:16:26 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/19 21:40:33 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_coder_routine.h"

void	*start_working(t_coder *coder)
{
	const t_coder_config	*config = coder_config(NULL, NULL, NULL, NULL);
	const uint32_t			*tasks = config->tasks;
	const uint32_t			time_to_burnout = config->burnout;
	const char				*msg = {
		COMPILING_MSG,
		DEBUGGING_MSG,
		REFACTORING_MSG
	};
	uint32_t				task;

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
			mutex_log_msg(time_elapsed(NULL), coder->id, msg[task], &coder->local_mutex);
			if (do_task(tasks[task++], &coder->execution_remaining) == STOP_EXECUTION)
				return (NULL);
		}

		mutex_log_msg(time_elapsed(0), coder->id, COMPILING_MSG, coder->global_mutex);
		spend_time(compiling, &life_time);
		mutex_set_flag(&coder->state, DONGLES_RELEASED, &coder->local_mutex);
		mutex_log_msg(time_elapsed(0), coder->id, DEBUGGING_MSG, coder->global_mutex);
		spend_time(debugging, &life_time);
		mutex_log_msg(time_elapsed(0), coder->id, REFACTORING_MSG, coder->global_mutex);
		spend_time(refactoring, &life_time);
	}
}
