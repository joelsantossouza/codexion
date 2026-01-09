/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_message.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 12:40:53 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/09 13:33:25 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdint.h>

void	log_message(uint64_t timestamp_in_ms, uint32_t coder_id, const char *msg, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	printf("%lu %d %s\n", timestamp_in_ms, coder_id, msg);
	pthread_mutex_unlock(mutex);
}
