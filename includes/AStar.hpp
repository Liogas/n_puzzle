/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AStar.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 10:53:17 by glions            #+#    #+#             */
/*   Updated: 2026/02/19 16:08:25 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGOSTAR_HPP
# define ALGOSTAR_HPP

#include <vector>
#include <queue>
#include <unordered_set>
#include <algorithm>
#include <memory>

template<typename State>
struct Node
{
	State							state;
	int								g;
	int								h;
	std::shared_ptr<Node<State>>	parent;
};

template<typename State>
concept AStarState =
	std::copyable<State> &&
	std::equality_comparable<State> &&
	requires(State s)
	{
		{ std::hash<State>{}(s)} -> std::convertible_to<std::size_t>;
	};

template<
	AStarState State,
	typename NeighborsFn,
	typename DistFn,
	typename HeurFn
>
std::vector<State> AStar(
	const State		&start,
	const State		&goal,
	NeighborsFn 	genNeighbors,
	DistFn 			calDist,
	HeurFn			calHeur
);

template<AStarState State>
struct CmpNode
{
	bool operator()(const std::shared_ptr<Node<State>>& a,
        const std::shared_ptr<Node<State>>& b
	) const 
	{
		return (a->g + a->h) > (b->g + b->h);
	}
};	

# include "AStar.tpp"

#endif