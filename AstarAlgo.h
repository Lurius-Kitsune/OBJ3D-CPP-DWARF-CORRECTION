#pragma once
#include "CoreMinimal.h"
#include "Node.h"

template <typename Type>
class AstarAlgo
{
	Size gridSize;
	vector<vector<Type>> grid;

public:
	AstarAlgo(const vector<vector<Type>>& _grid)
	{
		grid = _grid;
		gridSize = Size(_grid);
	}

private:
	bool IsValid(const Coords& _coords) const
	{
		return _coords >= 0 && _coords < gridSize && grid[_coords.x][_coords.y].IsValid();
	}
	static bool CompareNodes(Node* _first, Node* _second)
	{
		return _first->GetF() > _second->GetF();
	}
	u_int ComputeIndex(const Coords& _coords) const
	{
		return _coords.y * gridSize.x + _coords.x;
	}
	vector<Coords> GetNeighbors(const Coords& _coords) const
	{
		return {
			Coords(_coords.x + 1, _coords.y),
			Coords(_coords.x - 1, _coords.y),
			Coords(_coords.x, _coords.y + 1),
			Coords(_coords.x, _coords.y - 1),
		};
	}
	vector<Coords> ReconstructPath(Node* _node) const
	{
		vector<Coords> _path;

		while (_node)
		{
			_path.insert(_path.begin(), _node->location);
			_node = _node->parent;
		}

		return _path;
	}
	void Erase(const unordered_map<u_int, Node*>& _allNodes) const
	{
		for (const pair<u_int, Node*>& _pair : _allNodes)
		{
			delete _pair.second;
		}
	}

public:
	vector<Coords> FindPath(const Coords& _start, const Coords& _end)
	{
		priority_queue<Node*, vector<Node*>, function<bool(Node*, Node*)>> _openList(CompareNodes);
		unordered_map<u_int, Node*> _allNodes;
		unordered_map<u_int, bool> _closedList;

		Node* _startNode = new Node(_start, _end, nullptr);
		_openList.push(_startNode);
		_allNodes[ComputeIndex(_start)] = _startNode;

		while (!_openList.empty())
		{
			Node* _currentNode = _openList.top();
			_openList.pop();

			// Si le noeud courant est le 'end'
			if (_currentNode->location == _end)
			{
				// On reconstruit le chemin
				const vector<Coords>& _finalPath = ReconstructPath(_currentNode);

				// On libère la mémoire
				Erase(_allNodes);

				// On retourne le chemin terminé
				return _finalPath;
			}

			// Marque le noeud actuel comme visité
			_closedList[ComputeIndex(_currentNode->location)] = true;

			// Explore les voisins
			for (const Coords& _neighborLocation : GetNeighbors(_currentNode->location))
			{
				const u_int& _neighborIndex = ComputeIndex(_neighborLocation);
				if (IsValid(_neighborLocation) && !_closedList[_neighborIndex])
				{
					Node* _neighbor = new Node(_neighborLocation, _end, _currentNode);

					// Si le voisin n'est pas dans la liste ouverte
					// ou il a un coût F plus bas
					if (_allNodes.find(_neighborIndex) == _allNodes.end() || _neighbor->GetF() < _allNodes[_neighborIndex]->GetF())
					{
						_openList.push(_neighbor);
						_allNodes[_neighborIndex] = _neighbor;
					}
					else
					{
						delete _neighbor;
					}
				}
			}

		}

		// On libère la mémoire
		Erase(_allNodes);

		// On retourne le path vide
		return vector<Coords>();
	}
};