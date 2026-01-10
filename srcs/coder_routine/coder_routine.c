/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 12:16:26 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/09 16:02:53 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include "coder_routine.h"

void	*start_working(t_coder *coder)
{
	uint32_t	life_time;
	uint32_t	burnout_time;
	uint32_t	compiling;
	uint32_t	debugging;
	uint32_t	refactoring;

	get_coder_rules(&burnout_time, &compiling, &debugging, &refactoring);
	life_time = burnout_time;
	while (life_time > 0)
	{
		if (!timed_wait(&coder->is_ready_to_compile, &coder->local_mutex, &life_time))
			return (0);
		life_time = burnout_time;
		log_message(time_elapsed(NULL), coder->id, COMPILING_MSG, coder->global_mutex);
		spend_time(compiling, &life_time);
		log_message(time_elapsed(NULL), coder->id, DEBUGGING_MSG, coder->global_mutex);
		spend_time(debugging, &life_time);
		log_message(time_elapsed(NULL), coder->id, REFACTORING_MSG, coder->global_mutex);
		spend_time(refactoring, &life_time);
	}
	return (0);
}
