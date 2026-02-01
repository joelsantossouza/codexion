/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 16:43:45 by joesanto          #+#    #+#             */
/*   Updated: 2026/02/01 17:05:34 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "coder_internal.h"
#include "codexion_config_control.h"
#include "codexion.h"

void	*monitor_routine(t_coder coders[])
{
	const t_codexion_config	*config = get_codexion_config();
	bool					is_burned_out;
	uint32_t				coders_done_compiling;
	uint32_t				i;

	while (true)
	{
		i = -1;
		coders_done_compiling = 0;
		while (++i < config->number_of_coders)
		{
			pthread_mutex_lock(&coders[i].mutex);
			//coders_done_compiling += coders[i].compilations_done >= config->number_of_compiles_required;
			is_burned_out = millis() >= coders[i].deadline_ms;
			pthread_mutex_unlock(&coders[i].mutex);
			if (is_burned_out == true)
			{
				stop_simulation();
				log_coder_event(&coders[i], EVENT_BURNOUT);
				return (NULL);
			}
		}
		if (coders_done_compiling == config->number_of_coders)
			return (stop_simulation(), NULL);
	}
}
