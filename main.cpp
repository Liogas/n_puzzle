/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 12:43:31 by glions            #+#    #+#             */
/*   Updated: 2026/01/24 01:45:43 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "State.hpp"
#include <unordered_map>
#include <queue>

int		calc(int y, int x, int v, const State &goal)
{
	for (size_t i = 0; i < goal.getValues().size(); i++)
	{
		for(size_t j = 0; j < goal.getValues()[i].size(); j++)
		{
			if (goal.getValues()[i][j] == v)
				return (abs(y - (int)i) + abs(x - (int)j));
		}
	}
	return (0);
}

int	manhattan(const State &current, const State &goal)
{
	int	estimation = 0;
	for (size_t i = 0; i < current.getValues().size(); i++)
	{
		for (size_t j = 0; j < current.getValues()[i].size(); j++)
		{
			if (current.getValues()[i][j] != 0)
				estimation += calc(i, j, current.getValues()[i][j], goal);	
		}
	}
	return (estimation);
}

int	algo(State &start, State &dest, int heur(const State&, const State&))
{
	std::unordered_map<State, int, StateHash> distances;
	std::unordered_map<State, State, StateHash> fathers;
	std::priority_queue<Elem, std::vector<Elem>, Cmp> tmp;

	distances[start] = 0;
	tmp.push( Elem {
		.distance= 0,
		.estimate=heur(start, dest),
		.state= start
	});
	while (!tmp.empty())
	{
		Elem curr = tmp.top();
		tmp.pop();
		std::cout << "State actuel traite : " << curr.state << std::endl;
		if (curr.state == dest)
		{
			std::cout << "Dest atteind donc on stop" << std::endl;
			break;
		}
		if (curr.distance > distances[curr.state])
		{
			std::cout << "Ignoré car plus petite distance existe" << std::endl;
			continue;
		}
		std::vector<State> neighbors = curr.state.genNeighbors();
		for (State n : neighbors)
		{
			int d = distances[curr.state] + 1;
			auto it = distances.find(n);
			if (it == distances.end() || it->second > d)
			{
				distances[n] = d;
				fathers.erase(n);
				fathers.emplace(n, curr.state);
				tmp.push(Elem({
					.distance= distances[n],
					.estimate=heur(n, dest),
					.state= n
				}));
			}
		}
	}
	std::cout << "Start : " << std::endl << start << std::endl;
	std::cout << "Dest : " << std::endl;
	std::cout << "Start : " << std::endl << dest << std::endl;
	std::cout << "Distance : " << distances[dest] << std::endl;
	std::cout << "Chemin parcouru : " << std::endl;
	std::cout << dest << std::endl;
	int i = 0;
	std::cout << std::endl;
	State curr = dest;
	while (curr != start)
	{
		curr = fathers.at(curr);
		std::cout << curr << std::endl;
		i++;
		std::cout << std::endl;
		std::cout << i << std::endl;
		std::cout << std::endl;
	}
	return (0);
}

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	State start = {{{ 
		{7, 2, 1}, 
		{4, 6, 0}, 
		{5, 8, 3} 
	}}};
	State dest = {{{ 
		{1, 2, 3}, 
		{4, 5, 6}, 
		{7, 8, 0} 
	}}};	
	return (algo(start, dest, manhattan));
}