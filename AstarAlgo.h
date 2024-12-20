#pragma once
#include "CoreMinimal.h"
#include "Node.h"

template <typename Type>
class AstarAlgo
{
	Size gridSize;
	vector<vector<Type>> grid;
public:
	INLINE u_int Heuristic(const Coords& _coordsA, const Coords& _coordsB)const
	{
		return abs(_coordsA.x - _coordsB.x) + abs(_coordsA.y - _coordsB.y);
	}

public:

	AstarAlgo(const vector<vector<Type>>& _grid)
	{
		grid = _grid;
		gridSize = Size(grid);
	}

private:
	bool IsValid(const Coords& _coords)const
	{
		return _coords>= 0 && _coords < gridSize;
	}
	bool CopareNodes(Node* _first, Node* _second)
	{
		return _first->GetF() > _second->GetF();
	}

	vector<Coords> GetNeighbors(const Coords& _coords) const
	{
		return
		{
			Coords(_coords.x +1, _coords.y),
			Coords(_coords.x -1, _coords.y),
			Coords(_coords.x , _coords.y + 1),
			Coords(_coords.x, _coords.y -1),
		}
	}

	u_int ComputeIndex(const Coords& _coords) const
	{
		return _coords.y * gridSize.x + _coords.x;
	}

	vector<Coords> ReconstructPath(Node* _node)
	{
		vector<Coords> _path;

		while (_node)
		{
			_path.push_back(_node->location);
			_node = _node->parent;
		}

		return _path;
	}

	void Erase(const unordered_map<u_int, Node*>& _allNodes)
	{

	}

public:
	vector<Coords> FindPath(const Coords& _start, const Coords& _end)
	{
		priority_queue<Node*, vector<Node*>, function<bool(Node*, Node*)>> _openList(CopareNodes);
		unordered_map<u_int, Node*> _allNode;
		unordered_map<u_int, bool> _closedList;

		Node* _startNode = new Node(_start, _end, nullptr);

		_openList.push(_startNode);
		_allNode[ComputeIndex(_start)] = _startNode;

		while (!_openList.empty())
		{
			Node* _currentNode = _openList.top();
			_openList.pop();

			// Si le noeud  courant est le 'end' alors path
			if (_currentNode->location == _end)
			{
				// On reconstruit le chemin
				const vector<Coords>& _path = ReconstructPath(_currentNode);

				Erase(_allNode);

				return _path;
			}

			// Marque le noeud actuel comme visiter;

			_closedList[ComputeIndex(_currentNode->location)] = true;

			// Explore les voisins
			for (const Coords& _neighborLocation : GetNeighbors(_currentNode))
			{
				const u_int& _neighborIndex = ComputeIndex(_neighborLocation->location);
				if (IsValid(_neighborLocation) && !_closedList[_neighborIndex])
				{
					Node* _neighbor = new Node(_neighborLocation, _end, _currentNode);

					// Si le voison n'est pas dans la liste ouverte
					// Ou  il à un coût F plus bas
					if (_allNode.find(_neighborLocation.y * gridSize.x + _neighborLocation.x)
						|| _gCost + _hCost < _allNode[_neighborIndex]->GetF())
					{
						_openList.push(_neighbor);
						_allNode[_neighborIndex] = _neighbor;
					}
				}
			}
		}

		Erase(_allNode);
		return vector<Coords>();
	}


};

