/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:41:04 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/18 18:47:39 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdint.h>
# include <sys/types.h>

// UTILS
# define TRUE				1
# define FALSE				0

typedef struct s_codexion
{
	uint32_t	number_of_coders;
	uint32_t	time_to_burnout;
	uint32_t	time_to_compile;
	uint32_t	time_to_debug;
	uint32_t	time_to_refactor;
	uint32_t	number_of_compiles_required;
	uint32_t	dongle_cooldown;
	t_scheduler	scheduler;
}	t_codexion;

typedef void	*(*t_routine)(void *);

// TIME MANIPULATION
uint64_t	millis(void);
uint64_t	time_elapsed(uint64_t *new_start);

#endif
