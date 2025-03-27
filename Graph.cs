using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Text;
using System.Threading.Tasks;

namespace GraphNamespace
{
    public class Path<T1, T2>
    {
        private List<(T1, T1, T2)> _edges;

        public Path()
        {
            _edges = new List<(T1, T1, T2)> ();
        }

        public Path(List<(T1, T1, T2)> edges)
        {
            _edges = edges;
        }

        public Path(Path<T1, T2> path)
        {
            _edges = new List<(T1, T1, T2)>(path._edges);
        }

        public void AddEdge((T1, T1, T2) edge)
        {
            _edges.Add (edge);
        }

        public T2 GetLength()
        {
            T2 length = default (T2);

            foreach ((T1, T1, T2) edge in _edges)
            {
                length += ((dynamic)edge.Item3);
            }

            return length;
        }

        public string ConvertToString()
        {
            int count = _edges.Count;

            if (count == 0)
                return "";

            string path = _edges[0].Item1.ToString() + "->";

            for (int i = 0; i < count - 1; i++)
            {
                path += _edges[i].Item3.ToString() + "->" + _edges[i].Item2.ToString() + "->";
            }

            path += _edges[count - 1].Item3.ToString() + "->" + _edges[count - 1].Item2.ToString();

            return path;
        }
    }




    public class Graph<T1, T2> where T2 : IComparable<T2>
    {
        private class Vertex
        {
            private T1 _value;
            private List<(Vertex, T2)> _adjVertices;

            public Vertex(T1 value, List<(Vertex, T2)> adjVertices)
            {
                _value = value;
                _adjVertices = adjVertices;
            }

            public T1 GetValue() { return _value; }

            public List<(Vertex, T2)> GetAdjVertices() { return _adjVertices; }

            public void AddAdjVertex((Vertex, T2) newAdjVertex)
            {
                _adjVertices.Add(newAdjVertex);
            }
        }

        private List<Vertex> _vertices;



        public Graph()
        {
            _vertices = new List<Vertex>();
        }

        public Graph(T1 value)
        {
            _vertices = new List<Vertex>() { new Vertex(value, new List<(Vertex, T2)>()) };
        }

        public void AddVertex(T1 value)
        {
            foreach (Vertex vertex in _vertices)
            {
                if (value.Equals(vertex.GetValue()))
                    throw new ArgumentException();
            }

            _vertices.Add(new Vertex(value, new List<(Vertex, T2)>()));
        }

        public void AddVertex(T1 value, List<(T1, T2)> adjVertices, List<(T1, T2)> verticesPointThis)
        {
            foreach (Vertex vertex in _vertices)
            {
                if (value.Equals(vertex.GetValue()))
                    throw new ArgumentException();
            }

            Vertex newVertex = new Vertex(value, new List<(Vertex, T2)>());

            foreach ((T1, T2) adjVertex in adjVertices)
            {
                bool exist = false;

                foreach (Vertex vertex in _vertices)
                {
                    if (vertex.GetValue().Equals(adjVertex.Item1))
                    {
                        newVertex.AddAdjVertex((vertex, adjVertex.Item2));
                        exist = true;
                        break;
                    }
                }

                if (!exist)
                    throw new ArgumentException();
            }

            foreach ((T1, T2) vertexPointThis in verticesPointThis)
            {
                bool exist = false;

                foreach (Vertex vertex in _vertices)
                {
                    if (vertex.GetValue().Equals(vertexPointThis.Item1))
                    {
                        vertex.AddAdjVertex((newVertex, vertexPointThis.Item2));
                        exist = true;
                        break;
                    }
                }

                if (!exist)
                    throw new ArgumentException();
            }

            _vertices.Add(newVertex);

        }

        public void AddEdge(T1 vertexStart, T1 vertexEnd, T2 value)
        {
            int indexVertexStart = _vertices.FindIndex(item => item.GetValue().Equals(vertexStart));

            if (indexVertexStart < 0)
                throw new ArgumentException();
            else
            {
                int indexVertexEnd = _vertices.FindIndex(item => item.GetValue().Equals(vertexEnd));

                if ((indexVertexEnd < 0) || (_vertices[indexVertexStart].GetAdjVertices().Exists(item => item.Item1.GetValue().Equals(vertexEnd))))
                    throw new ArgumentException();
                else
                {
                    _vertices[indexVertexStart].AddAdjVertex((_vertices[indexVertexEnd], value));
                }
            }
        }



        public void RemoveVertex(T1 value)
        {
            Vertex removedVertex = null;
            List<(Vertex, T2)> adjVertices;
            (Vertex, T2) removedAdjVertex = default;

            foreach (Vertex vertex in _vertices)
            {
                if (value.Equals(vertex.GetValue()))
                    removedVertex = vertex;
                else
                {
                    adjVertices = vertex.GetAdjVertices();
                    removedAdjVertex = default;

                    foreach ((Vertex, T2) adjVertex in adjVertices)
                    {
                        if (value.Equals(adjVertex.Item1.GetValue()))
                        {
                            removedAdjVertex = adjVertex;
                            break;
                        }
                    }

                    if (!(removedAdjVertex.Equals(default)))
                        adjVertices.Remove(removedAdjVertex);
                }
            }

            if (removedVertex != null)
                _vertices.Remove(removedVertex);
            else
                throw new ArgumentException();
        }

        public void RemoveEdge(T1 vertexStart, T1 vertexEnd)
        {
            int indexVertexStart = _vertices.FindIndex(item => item.GetValue().Equals(vertexStart));

            if (indexVertexStart < 0)
                throw new ArgumentException();
            else
            {
                List<(Vertex, T2)> adjVertices = _vertices[indexVertexStart].GetAdjVertices();
                int numberRemovedElements = adjVertices.RemoveAll(item => item.Item1.GetValue().Equals(vertexEnd));

                if (numberRemovedElements == 0)
                    throw new ArgumentException();
            }
        }


        public bool ContainsVertex(T1 vertex)
        {
            return _vertices.Exists(item => item.GetValue().Equals(vertex));
        }

        public bool ContainsEdge(T1 vertexStart, T1 vertexEnd)
        {
            int indexVertexStart = _vertices.FindIndex(item => item.GetValue().Equals(vertexStart));

            if (indexVertexStart < 0)
                return false;

            List<(Vertex, T2)> adjVertices = _vertices[indexVertexStart].GetAdjVertices();

            if (!(adjVertices.Exists(item => item.Item1.GetValue().Equals(vertexEnd))))
                return false;

            return true;
        }


        private void DFS(Vertex vertex, List<T1> checkedNodes)
        {
            Stack<Vertex> stack = new Stack<Vertex>();
            stack.Push(vertex);
            Vertex currentVertex;
            List<(Vertex, T2)> adjVertices;

            while (stack.Count > 0)
            {
                currentVertex = stack.Pop();
                checkedNodes.Add(currentVertex.GetValue());
                adjVertices = currentVertex.GetAdjVertices();

                foreach ((Vertex, T2) adjVertex in adjVertices)
                {
                    if (!(checkedNodes.Exists(item => item.Equals(adjVertex.Item1.GetValue()))))
                        stack.Push(adjVertex.Item1);
                }
            }
        }

        private List<T1> templateDFS(T1 vertexStart)
        {
            List<T1> checkedNodes = new List<T1>();
            int indexVertexStart = _vertices.FindIndex(item => item.GetValue().Equals(vertexStart));

            if (indexVertexStart < 0)
                throw new ArgumentException();

            DFS(_vertices[indexVertexStart], checkedNodes);

            foreach (Vertex vertex in _vertices)
            {
                if (!(checkedNodes.Exists(item => item.Equals(vertex.GetValue()))))
                    DFS(vertex, checkedNodes);
            }

            return checkedNodes;
        }

        public List<T1> DFS(T1 vertexStart)
        {
            return templateDFS(vertexStart);
        }

        public List<T1> DFS()
        {
            if (_vertices.Count > 0)
                return templateDFS(_vertices[0].GetValue());

            return new List<T1>();
        }



        private void BFS(Vertex vertex, List<T1> checkedNodes)
        {
            Queue<Vertex> queue = new Queue<Vertex>();
            queue.Enqueue(vertex);
            Vertex currentVertex;
            List<(Vertex, T2)> adjVertices;

            while (queue.Count > 0)
            {
                currentVertex = queue.Dequeue();
                checkedNodes.Add(currentVertex.GetValue());
                adjVertices = currentVertex.GetAdjVertices();

                foreach ((Vertex, T2) adjVertex in adjVertices)
                {
                    if (!(checkedNodes.Exists(item => item.Equals(adjVertex.Item1.GetValue()))))
                        queue.Enqueue(adjVertex.Item1);
                }
            }
        }

        public List<T1> templateBFS(T1 vertexStart)
        {
            List<T1> checkedNodes = new List<T1>();
            int indexVertexStart = _vertices.FindIndex(item => item.GetValue().Equals(vertexStart));

            if (indexVertexStart < 0)
                throw new ArgumentException();

            BFS(_vertices[indexVertexStart], checkedNodes);

            foreach (Vertex vertex in _vertices)
            {
                if (!(checkedNodes.Exists(item => item.Equals(vertex.GetValue()))))
                    BFS(vertex, checkedNodes);
            }

            return checkedNodes;
        }

        public List<T1> BFS(T1 vertexStart)
        {
            return templateBFS(vertexStart);
        }

        public List<T1> BFS()
        {
            if (_vertices.Count > 0)
                return templateBFS(_vertices[0].GetValue());

            return new List<T1>();
        }


        private Graph<T1, T2> CreateInvertedGraph()
        {
            Graph<T1, T2> invertedGraph = new Graph<T1, T2>();

            foreach (Vertex vertex in _vertices)
            {
                invertedGraph.AddVertex(vertex.GetValue());
            }

            List<(Vertex, T2)> adjVertices;
            T1 vertexValue;

            foreach (Vertex vertex in _vertices)
            {
                adjVertices = vertex.GetAdjVertices();
                vertexValue = vertex.GetValue();

                foreach ((Vertex, T2) adjVertex in adjVertices)
                {
                    invertedGraph.AddEdge(adjVertex.Item1.GetValue(), vertexValue, adjVertex.Item2);
                }
            }

            return invertedGraph;
        }

        private void GetOrderVertices(Vertex vertex, List<T1> checkedNodes, List<T1> orderVertices)
        {
            checkedNodes.Add(vertex.GetValue());
            List<(Vertex, T2)> adjVertices = vertex.GetAdjVertices();

            foreach ((Vertex, T2) adjVertex in adjVertices)
            {
                if (!(checkedNodes.Exists(item => item.Equals(adjVertex.Item1.GetValue()))))
                    GetOrderVertices(adjVertex.Item1, checkedNodes, orderVertices);
            }

            orderVertices.Add(vertex.GetValue());
        }

        public Graph<string, T2> GetCondensation()
        {
            Graph<T1, T2> invertedGraph = CreateInvertedGraph();
            List<T1> checkedNodes = new List<T1>();
            List<T1> orderVertices = new List<T1>();

            foreach (Vertex vertex in _vertices)
            {
                if (!(checkedNodes.Exists(item => item.Equals(vertex.GetValue()))))
                    GetOrderVertices(vertex, checkedNodes, orderVertices);
            }

            List<T1> SCC = new List<T1>();
            List<T1> adjVerticesForSCC;
            List<(List<T1>, List<T1>)> allSCC = new List<(List<T1>, List<T1>)>();
            Vertex currentVertex;
            List<(Vertex, T2)> adjVertices;
            Graph<string, T2> condensation = new Graph<string, T2>();
            
            while (orderVertices.Count > 0)
            {
                SCC = new List<T1>();
                adjVerticesForSCC = new List<T1>();
                currentVertex = invertedGraph._vertices.Find(item => item.GetValue().Equals(orderVertices[orderVertices.Count - 1]));
                DFS(currentVertex, SCC);

                foreach (T1 component in SCC)
                {
                    orderVertices.Remove(component);
                    invertedGraph.RemoveVertex(component);
                    currentVertex = _vertices.Find(item => item.GetValue().Equals(component));
                    adjVertices = currentVertex.GetAdjVertices();

                    foreach ((Vertex, T2) adjVertex in adjVertices)
                    {
                        if (!(adjVerticesForSCC.Exists(item => item.Equals(adjVertex.Item1.GetValue()))))
                            adjVerticesForSCC.Add(adjVertex.Item1.GetValue());
                    }
                }

                condensation.AddVertex(String.Join(";", SCC));
                allSCC.Add((SCC, adjVerticesForSCC));
            }

            foreach ((List<T1>, List<T1>) component_1 in allSCC)
            {
                adjVerticesForSCC = component_1.Item2;

                foreach ((List<T1>, List<T1>) component_2 in allSCC)
                {
                    if (!(component_1.Equals(component_2))) {
                        foreach (T1 adjVertexForSCC in adjVerticesForSCC)
                        {
                            if (component_2.Item1.Exists(item => item.Equals(adjVertexForSCC)))
                            {
                                condensation.AddEdge(String.Join(";", component_1.Item1), String.Join(";", component_2.Item1), default(T2));
                                break;
                            }
                        }
                    }
                }
            }

            return condensation;
        }

        
        private void TopSortDFS(List<T1> order, List<int> countIn, List<int> countOut, int index)
        {
            countIn[index] = 1;
            Vertex currentVertex = _vertices[index];
            List<(Vertex, T2)> adjVertices = currentVertex.GetAdjVertices();
            int indexAdjVertex;

            foreach ((Vertex, T2) adjVertex in adjVertices)
            {
                indexAdjVertex = _vertices.FindIndex(item => item.Equals(adjVertex.Item1));

                if ((countIn[indexAdjVertex] == 1) && (countOut[indexAdjVertex] == 0))
                    throw new Exception();

                if (countIn[indexAdjVertex] == 0)
                {
                    try
                    {
                        TopSortDFS(order, countIn, countOut, indexAdjVertex);
                    }
                    catch
                    {
                        throw;
                    }
                }
            }

            order.Insert(0, currentVertex.GetValue());
            countOut[index] = 1;
        }
        
        public List<T1> TopologicalSort()
        {
            List<T1> order = new List<T1>();
            int numberVertices = _vertices.Count;
            List<int> countIn = Enumerable.Repeat(0, numberVertices).ToList();
            List<int> countOut = Enumerable.Repeat(0, numberVertices).ToList();
            
            for (int i = 0; i < numberVertices; i++)
            {
                if (countIn[i] == 0)
                {
                    try
                    {
                        TopSortDFS(order, countIn, countOut, i);
                    }
                    catch
                    {
                        throw;
                    }
                }
            }
            
            return order;
        }



        private void ShortestPathBFS(Vertex vertex, List<(T1, T2, Path<T1, T2>)> distances)
        {
            T1 vertexStartValue = vertex.GetValue();
            Queue<Vertex> queue = new Queue<Vertex>();
            List<Vertex> checkedVertices = new List<Vertex>();
            queue.Enqueue(vertex);
            Vertex currentVertex;
            List<(Vertex, T2)> adjVertices;
            int index;
            (T1, T2, Path<T1, T2>) currentDistance;
            (T1, T2, Path<T1, T2>) currentDistanceAdjVertex;
            Path<T1, T2> path;
            
            while (queue.Count > 0)
            {
                currentVertex = queue.Dequeue();
                checkedVertices.Add(currentVertex);
                adjVertices = currentVertex.GetAdjVertices();

                foreach ((Vertex, T2) adjVertex in adjVertices)
                {
                    index = distances.FindIndex(item => item.Item1.Equals(adjVertex.Item1.GetValue()));
                    currentDistance = distances.Find(item => item.Item1.Equals(currentVertex.GetValue()));

                    path = new Path<T1, T2>(currentDistance.Item3); //{ (adjVertex.Item1.GetValue(), adjVertex.Item2) };
                    path.AddEdge((currentVertex.GetValue(), adjVertex.Item1.GetValue(), adjVertex.Item2));
                   
                    if (index < 0)
                    {
                        distances.Add((adjVertex.Item1.GetValue(), ((dynamic)currentDistance.Item2) + ((dynamic)adjVertex.Item2), path));
                    }
                    else
                    {
                        currentDistanceAdjVertex = distances[index];

                        if ((dynamic)currentDistanceAdjVertex.Item2 > (((dynamic)currentDistance.Item2) + ((dynamic)adjVertex.Item2)))
                            distances[index] = ((adjVertex.Item1.GetValue(), (((dynamic)currentDistance.Item2) + ((dynamic)adjVertex.Item2)), path));
                    }

                    if (!(checkedVertices.Contains(adjVertex.Item1)))
                        queue.Enqueue(adjVertex.Item1);
                }
            }
        }

        public Path<T1, T2> GetShortestPath(T1 vertexStart, T1 vertexEnd)
        {
            int indexVertexStart = _vertices.FindIndex(item => item.GetValue().Equals(vertexStart));

            if (indexVertexStart < 0)
                throw new ArgumentException();

            int indexVertexEnd = _vertices.FindIndex(item => item.GetValue().Equals(vertexEnd));

            if (indexVertexEnd < 0)
                throw new ArgumentException();

            if (vertexStart.Equals(vertexEnd))
                return new Path<T1, T2>();

            List<(T1, T2, Path<T1, T2>)> distances = new List<(T1, T2, Path<T1, T2>)>() { (vertexStart, default(T2), new Path<T1, T2>())};

            ShortestPathBFS(_vertices[indexVertexStart], distances);

            int index = distances.FindIndex(item => item.Item1.Equals(vertexEnd));

            if (index < 0)
                throw new ArgumentException();

            (T1, T2, Path<T1, T2>) shortestDistance = distances[index];

            return shortestDistance.Item3;
        }



        /*public void Traversal()
        {
            Console.Write("Count: ");
            Console.WriteLine(_vertices.Count);
            foreach (Vertex vertex in _vertices)
            {
                Console.WriteLine("vertex");
                Console.WriteLine(vertex.GetValue());
                Console.WriteLine("Adj vertices:");
                List<(Vertex, T2)> adjVertices = vertex.GetAdjVertices();
                foreach ((Vertex, T2) adjVertex in adjVertices)
                {
                    Console.Write(adjVertex.Item1.GetValue());
                    Console.Write(' ');
                    Console.WriteLine(adjVertex.Item2);
                }
                
                Console.WriteLine();
            }
        }*/

    }
}


