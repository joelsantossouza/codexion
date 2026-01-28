/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_coder_event.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:51:51 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/28 21:04:23 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "coder_internal.h"

void	log_coder_event(t_coder *coder, const char *event_msg)
{
	char	log[LOG_BUFFER_SIZE];
	char	*log_ptr;

	if (is_simulation_running() == false)
		return ;
	log_ptr = ft_stpcpy(log, timestamp_str);
	log_ptr = ft_stpcpy(log_ptr, coder_id_str);
	log_ptr = ft_stpcpy(log_ptr, event_msg);
	pthread_mutex_lock();
	write(STDOUT_FILENO, log, log_len);
	pthread_mutex_unlock();
}
