/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AStar.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 11:08:55 by glions            #+#    #+#             */
/*   Updated: 2026/02/19 16:17:03 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AStar.hpp"

template<typename State>
std::vector<State> reconstructPath(std::shared_ptr<Node<State>> node)
{
	std::cout << "Je veux reconstruire le path" << std::endl;
    std::vector<State> path;
    while (node != nullptr)
    {
        path.push_back(node->state);
        node = node->parent;
    }
    std::reverse(path.begin(), path.end());
    return path;
}

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
)
{
	std::priority_queue
	<
		std::shared_ptr<Node<State>>,
		std::vector<std::shared_ptr<Node<State>>>,
		CmpNode<State>
	> 							openList;
	std::unordered_set<State>	closeList;

	auto startNode = std::make_shared<Node<State>>(Node<State>{
		start, 0, calHeur(start, goal), nullptr
	});
	openList.push(startNode);
	while (!openList.empty())
	{
		auto curr = openList.top();
		openList.pop();
		if (curr->state == goal)
			return {reconstructPath(curr)};
		closeList.insert(curr->state);
		for (State n : genNeighbors(curr->state))
		{
			if (closeList.count(n))
				continue ;

			int g = curr->g + calDist(curr->state, n);
			auto nNode = std::make_shared<Node<State>>(Node<State>{
				n, g, calHeur(n, goal), curr
			});
			openList.push(nNode);
		}
	}
	return {};
};


