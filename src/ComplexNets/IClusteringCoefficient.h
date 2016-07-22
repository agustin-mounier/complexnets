#ifndef ICLUSTERING_COEFFICIENT_H
#define ICLUSTERING_COEFFICIENT_H

namespace graphpp
{
template<class Graph, class Vertex>
class IClusteringCoefficient
{
public:
    typedef double Coefficient;
    typedef typename Vertex::Degree Degree;
    virtual Coefficient clusteringCoefficient(Graph& g, Degree d) = 0;
    virtual Coefficient vertexClusteringCoefficient(Vertex* vertex) = 0;
    
    virtual Coefficient vertexClusteringCoefficient(Vertex* vertex, bool out, bool in)
    {
        return vertexClusteringCoefficient(vertex);
    }
    
    virtual Coefficient clusteringCoefficient(Graph &g, Degree d, bool out, bool in)
    {
        return clusteringCoefficient(g, d);
    }
    
};
}
#endif
