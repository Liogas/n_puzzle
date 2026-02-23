/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PatternDatabase.tpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 12:04:54 by glions            #+#    #+#             */
/*   Updated: 2026/02/23 15:15:53 by glions           ###   ########.fr       */
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
    const T& goal,
	AbstractFn abstractFn,
	NeighborsFn	neighborsFn,

) : 
	_pattern(pattern.begin(), pattern.end()),
	_goal(goal),
	_abstractFn(abstractFn),
	_neighborsFn(neighborsFn)
{}

template<PatternState T>
void PatternDatabase<T>::build()
{
    std::cout << "Appel de la fonction build" << std::endl;
	T goalPattern = this->_abstractFn(this->_goal);
	std::queue<T>	open;
	open.push(goalPattern);
	this->_distances[goalPattern] = 0;
	while (!open.empty())
	{
		T	curr = open.front();
		open.pop();
		int	currDist = this->_distances[curr];
		for (auto n : this->_neighborsFn(curr))
		{	
			T nPattern = this->_abstractFn(n);
			if (this->_distances.find(nPattern) == this->_distances.end())
			{
				this->_distances[nPattern] = currDist + 1;
				open.push(nPattern);
			}
		}	
	}
}

template<PatternState T>
int PatternDatabase<T>::getDistance(const T& state) const
{
    auto it = _distances.find(state);
    if (it != _distances.end())
        return it->second;
    return 0;
}

template<PatternState T>
T	PatternDatabase<T>::abstractState(const T &s) const
{
	T	copy = s;
	for (auto &tile : copy.board)
	{
		if (!this->_pattern.contains(tile) && tile != 0)
			tile = 0;
	}
	return (copy);
}

