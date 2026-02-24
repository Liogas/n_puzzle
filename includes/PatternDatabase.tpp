/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PatternDatabase.tpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 12:04:54 by glions            #+#    #+#             */
/*   Updated: 2026/02/24 15:57:53 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

template<
	PatternState T,
	typename	AbstractFn,
	typename	NeighborsFn
>
PatternDatabase<T, AbstractFn, NeighborsFn>::PatternDatabase(
	const std::vector<TileType>& pattern,
	const T & goal,
	AbstractFn abstractFn,
	NeighborsFn neighborsFn
):
	_pattern(pattern.begin(), pattern.end()),
	_goal(goal),
	_abstractFn(abstractFn),
	_neighborsFn(neighborsFn)
{}

template<
	PatternState T,
	typename	AbstractFn,
	typename	NeighborsFn
>
void PatternDatabase<T, AbstractFn, NeighborsFn>::build()
{
    std::cout << "Appel de la fonction build" << std::endl;
	T goalPattern = _abstractFn(_goal);
	std::queue<T>	open;
	open.push(goalPattern);
	_distances[goalPattern] = 0;
	while (!open.empty())
	{
		T	curr = open.front();
		open.pop();
		int	currDist = _distances[curr];
		for (auto n : _neighborsFn(curr))
		{	
			T nPattern = _abstractFn(n);
			if (_distances.find(nPattern) == _distances.end())
			{
				_distances[nPattern] = currDist + 1;
				open.push(nPattern);
			}
		}	
	}
}

template<
	PatternState T,
	typename	AbstractFn,
	typename	NeighborsFn
>
int PatternDatabase<T, AbstractFn, NeighborsFn>::getDistance(const T& state) const
{
    auto it = _distances.find(state);
    if (it != _distances.end())
        return it->second;
    return 0;
}

template<
	PatternState T,
	typename	AbstractFn,
	typename	NeighborsFn
>
T	PatternDatabase<T, AbstractFn, NeighborsFn>::abstractState(const T &s) const
{
	T	copy = s;
	for (auto &tile : copy.board)
	{
		if (!_pattern.contains(tile) && tile != 0)
			tile = 0;
	}
	return (copy);
}

