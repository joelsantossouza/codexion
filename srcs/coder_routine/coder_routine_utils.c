/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:51:51 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/28 16:54:18 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	log_coder_event(t_coder *coder, const char *event_msg)
{
	if (is_simulation_running() == false)
		return ;
	pthread_mutex_lock();
	pthread_mutex_unlock();
}
