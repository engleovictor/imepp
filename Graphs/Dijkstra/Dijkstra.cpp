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
        map<int,bool> visopen;
    
    public:

        void addEdge(int p0, int p1, int weight) {
            verts[p0].insert(Edge(p0,p1,weight));
            verts[p1].insert(Edge(p0,p1,weight));
        }

        map<int,pair<int,int>> Dijkstra(int vert) {
            map<int,pair<int,int>> fpm;
            
            if(verts[vert].size() == 0) throw "Vetice Desconexo ou inexistente.";

            priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

            for(map<int,set<Edge>>::iterator it = verts.begin(); it != verts.end(); it ++) {
                visopen[it->first] = false;
                fpm[it->first] = make_pair((vert==it->first?0:max_int),-1);
            }
            
            pq.push(make_pair(0,vert));

            while(this->open()) {
                pair<int,int> now = pq.top();
                pq.pop();
                visopen[now.second] = true;

                for(set<Edge>::iterator it = verts[now.second].begin(); it != verts[now.second].end(); it++) {
                    int x = it->p0 == now.second ? it->p1: it->p0; 
                    pq.push(make_pair(it->weight+now.first,x));
                    if(fpm[x].first > it->weight+now.first) fpm[x] = make_pair(it->weight+now.first,now.second);
                }
            }

            return fpm;
            
        }

        bool open() {
            for(map<int,bool>::iterator it = visopen.begin(); it != visopen.end(); it++) {
                if(!it->second) return true; 
            } return false;
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

    map<int,pair<int,int>> dists = Brasil.Dijkstra(7);

    for(map<int,pair<int,int>>::iterator it = dists.begin(); it != dists.end(); it ++) {
        cout << it->first << " " << it->second.first << " " << it->second.second << endl;
    }

    return 0;
}