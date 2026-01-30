/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   schedulers.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 23:30:51 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/29 23:32:59 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCHEDULERS_H
# define SCHEDULERS_H

# include "simulation_control.h"

typedef struct s_coder	t_coder;

enum e_simulation_status	wait_fifo_turn(t_coder *coder);

#endif
