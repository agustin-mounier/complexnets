#pragma once

#include "IClusteringCoefficient.h"

namespace graphpp
{
template <class Graph, class Vertex>
class WeightedClusteringCoefficient : public IClusteringCoefficient<Graph, Vertex>
{
public:
    typedef typename IClusteringCoefficient<Graph, Vertex>::Coefficient Coefficient;
    typedef typename IClusteringCoefficient<Graph, Vertex>::Degree Degree;

    // TODO check if this method is implemented correctly
    virtual Coefficient clusteringCoefficient(Graph& g, Degree d)
    {
        auto it = g.verticesIterator();
        unsigned int count = 0;
        Coefficient clusteringCoefSums = 0.0;

        while (!it.end())
        {
            Vertex* v = *it;

            if (v->degree() == d)
            {
                ++count;
                clusteringCoefSums += vertexClusteringCoefficient(v);
            }

            ++it;
        }

        return count == 0 ? 0 : clusteringCoefSums / count;
    }

    virtual Coefficient vertexClusteringCoefficient(Vertex* vertex)
    {
        Coefficient links = 0.0;
        auto it = vertex->neighborsIterator();
        Coefficient ret;

        while (!it.end())
        {
            Vertex* n = static_cast<Vertex*>(*it);

            auto innerIter = n->neighborsIterator();

            while (!innerIter.end())
            {
                Vertex* i = static_cast<Vertex*>(*innerIter);
                // if i is neighbour of vertex, we close a triangle
                if (i->isNeighbourOf(vertex))
                    links += (vertex->edgeWeight(n) + i->edgeWeight(vertex)) / 2.0;

                ++innerIter;
            }
            ++it;
        }

        if (vertex->degree() == 1 || vertex->strength() == 0)
            ret = 0;
        else
            ret = links / (vertex->strength() * (vertex->degree() - 1));

        return ret;
    }
};
}
