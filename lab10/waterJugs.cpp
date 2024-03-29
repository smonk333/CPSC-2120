/*
 * Name:
 * Date Submitted:
 * Lab Section:
 * Assignment Name:
 */

#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

// Reflects what each node represents...
// First value units of water in A, second units of water in B
typedef pair<int,int> state;

// Each string in edge_label must be one of the following:
const string actions[] = {"Fill A",
                          "Fill B",
                          "Empty A",
                          "Empty B",
                          "Pour A->B",
                          "Pour B->A"};

// GENERIC -- these shouldn't need to be changed...
map<state, bool> visited;         // have we queued up this state for visitation?
map<state, state> pred;           // predecessor state we came from
map<state, int> dist;             // distance (# of hops) from source node
map<state, vector<state>> nbrs;   // vector of neighboring states

map<pair<state,state>, string> edge_label;

// GENERIC (breadth-first search, outward from source_node)
void search(state source_node)
{
  queue<state> to_visit;
  to_visit.push(source_node);
  visited[source_node] = true;
  dist[source_node] = 0;
  
  while (!to_visit.empty()) {
    state curnode = to_visit.front();
    to_visit.pop();
    for (state n : nbrs[curnode])
      if (!visited[n]) {
	pred[n] = curnode;
	dist[n] = 1 + dist[curnode];
	visited[n] = true;
	to_visit.push(n);
      }
  }
}

// GENERIC
void print_path(state s, state t)
{
  if (s != t) {
    print_path(s, pred[t]);
    cout << edge_label[make_pair(pred[t], t)] << ": " << "[" << t.first << "," << t.second << "]\n";
  } else {
    cout << "Initial state: " << "[" << s.first << "," << s.second << "]\n";
  }
}

void build_graph(void)
{
    for(int i = 0; i <= 3; i++) {
        for(int j = 0; j <= 4; j++) {
            state curr = make_pair(i, j);

            // Filling jug A
            state next = make_pair(3, j);
            edge_label[make_pair(curr, next)] = actions[0];
            nbrs[curr].push_back(next);

            // Filling jug B
            next = make_pair(i, 4);
            edge_label[make_pair(curr, next)] = actions[1];
            nbrs[curr].push_back(next);

            // Emptying jug A
            next = make_pair(0, j);
            edge_label[make_pair(curr, next)] = actions[2];
            nbrs[curr].push_back(next);

            // Emptying jug B
            next = make_pair(i, 0);
            edge_label[make_pair(curr, next)] = actions[3];
            nbrs[curr].push_back(next);

            // Pouring from A to B
            if(i + j >= 4) {
                next = make_pair(i + j - 4, 4);
            } else {
                next = make_pair(0, i + j);
            }
            edge_label[make_pair(curr, next)] = actions[4];
            nbrs[curr].push_back(next);

            // Pouring from B to A
            if(i + j >= 3) {
                next = make_pair(3, i + j - 3);
            } else {
                next = make_pair(i + j, 0);
            }
            edge_label[make_pair(curr, next)] = actions[5];
            nbrs[curr].push_back(next);
        }
    }
}

/*int main(void)
{
  build_graph();

  state start = make_pair(0,0);
  
  for (int i=0; i<5; i++)
    nbrs[make_pair(i,5-i)].push_back(make_pair(-1,-1));
  search (start);
  if (visited[make_pair(-1,-1)]) 
    print_path (start, pred[make_pair(-1,-1)]);
  else
    cout << "No path!\n";
  
  return 0;
}*/
