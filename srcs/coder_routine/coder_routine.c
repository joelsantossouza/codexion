/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 12:16:26 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/18 13:58:11 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include "coder_routine.h"
#include "mutex_log_msg.h"
#include "mutex_set_flag.h"

void	*start_working(t_coder *coder)
{
	uint32_t	life_time;
	uint32_t	burnout_time;
	uint32_t	compiling;
	uint32_t	debugging;
	uint32_t	refactoring;

	coder_config(&burnout_time, &compiling, &debugging, &refactoring);
	life_time = burnout_time;
	while (life_time > 0)
	{
		if (!wait_to_compile(&coder->state, &coder->local_mutex, &life_time))
			return (0);
		life_time = burnout_time;
		mutex_log_msg(time_elapsed(0), coder->id, COMPILING_MSG, coder->global_mutex);
		spend_time(compiling, &life_time);
		mutex_set_flag(&coder->state, DONGLES_RELEASED, &coder->local_mutex);
		mutex_log_msg(time_elapsed(0), coder->id, DEBUGGING_MSG, coder->global_mutex);
		spend_time(debugging, &life_time);
		mutex_log_msg(time_elapsed(0), coder->id, REFACTORING_MSG, coder->global_mutex);
		spend_time(refactoring, &life_time);
	}
	return (0);
}
