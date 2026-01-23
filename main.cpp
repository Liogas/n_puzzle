/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 12:43:31 by glions            #+#    #+#             */
/*   Updated: 2026/01/23 12:53:07 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "State.hpp"
#include <unordered_map>
#include <queue>

int	heuristic(const State &current, const State &goal)
{
	
}

int	algo(State start, State dest, int heuri(const State&, const State&))
{
	std::unordered_map<State, int, StateHash> distances;
	std::unordered_map<State, State, StateHash> fathers;
	std::priority_queue<Elem, std::vector<Elem>, Cmp> tmp;

	distances[start] = 0;
	tmp.push( Elem {
		.distance= 0,
		.estimate=heuri(start.getValues(), dest.getValues()),
		.state= start
	});
	
	return (0);
}

int	main(int ac, char **av)
{
	return (algo());
}