#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <fstream>

using namespace std;

#define max_int 2147483647

struct Edge {
    int p0, p1;
    int weight;

    Edge(int _p0, int _p1, int _weight):p0(_p0), p1(_p1), weight(_weight) {
        if(_p0>_p1) swap(p0,p1);
    }

    bool operator<(Edge e) const {
        return weight < e.weight;
    }

    bool operator>(Edge e) const {
        return weight > e.weight;
    }

    bool operator==(Edge e) const {
        return (p0 == e.p0 && p1 == e.p1 && weight == e.weight);
    }

    friend ostream &operator<<(ostream &os, Edge e) {
        return os << "VERTICE " << e.p0 << " - " << "VERTICE " << e.p1 << " PESO: " << e.weight;
    }
};

class Graph {
        map<int,set<Edge>> verts;

    public:

        int size() {
            return verts.size();
        }

        void addEdge(int p0, int p1, int weight) {
            verts[p0].insert(Edge(p0,p1,weight));
            verts[p1].insert(Edge(p0,p1,weight));
        }

        void addEdge(const Edge &e) {
            verts[e.p0].insert(e);
            verts[e.p1].insert(e);
        }

        Graph Prim(int ver) {
            Graph g;
            set<int>  alred;

            priority_queue<Edge, vector<Edge>, greater<Edge>> pq;

            alred.insert(ver);

            set<Edge>::iterator it = verts[ver].begin();
            while(it != verts[ver].end()) {
                pq.push(*it);
                it++;
            }

            while(verts.size() > g.size()) {
                Edge e = pq.top();
                pq.pop();

                if(alred.find(e.p0) != alred.end() && alred.find(e.p1) != alred.end()) continue;

                else if(alred.find(e.p0) == alred.end()) {
                   
                    alred.insert(e.p0);
                    set<Edge>::iterator it = verts[e.p0].begin();
                    while(it != verts[e.p0].end()) {
                        pq.push(*it);
                        it++;
                    }
                
                } else if(alred.find(e.p1) == alred.end()) {
                    
                    alred.insert(e.p1);
                    set<Edge>::iterator it = verts[e.p1].begin();
                    while(it != verts[e.p1].end()) {
                        pq.push(*it);
                        it++;
                    }

                }
                g.addEdge(e);
            }

        
        return g;


        }

        friend ostream &operator<<(ostream &os, Graph g) {
            for(map<int,set<Edge>>::iterator it = g.verts.begin(); it != g.verts.end(); it++) {
                os << "VERTICE " << it->first << endl;
                for(set<Edge>::iterator nit = it->second.begin(); nit != it->second.end(); nit ++) {
                    if(it->first < (*nit).p1) os << *nit << endl;
                }
            } return os;
        }

};

int main() {
    Graph Brasil;

    ifstream vertices("vert");

    int a,b,c;

    while(!vertices.eof()) {
        vertices >> a >> b >> c;
        Brasil.addEdge(a,b,c);
    }

    cout << Brasil.Prim(0);

    return 0;
}