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
// int with each bit == 0 left of river, bit == 1 right of river
typedef int state;

// Bit position representation for wolf/goat/cabbage/me
bool bit(int x, int i) { return (x>>i) & 1; }
const int wolf=0, goat=1, cabbage=2, me=3;

// GENERIC -- these shouldn't need to be changed...
map<state, bool> visited;         // have we queued up this state for visitation?
map<state, state> pred;           // predecessor state we came from
map<state, int> dist;             // distance (# of hops) from source node
map<state, vector<state>> nbrs;   // vector of neighboring states

map<pair<state,state>, string> edge_label;

// GENERIC (breadth-first search, outward from curnode)
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

string state_string(state s)
{
  string items[4] = { "wolf", "goat", "cabbage", "you" }, result = "";
  for (int i=0; i<4; i++)
    if (!bit(s, i)) result += items[i] + " ";
  result += " |river| ";
  for (int i=0; i<4; i++)
    if (bit(s, i)) result += items[i] + " ";
  return result;
}

// GENERIC
void print_path(state s, state t)
{
  if (s != t) {
    print_path(s, pred[t]);
    cout << edge_label[make_pair(pred[t], t)] << ": " << state_string(t) << "\n";
  } else {
    cout << "Initial state: " << state_string(s) << "\n";
  }
}

string neighbor_label(int s, int t)
{
  string items[3] = { "wolf", "goat", "cabbage" }, which_cross;
  if (bit(s,me) == bit(t,me)) return "";  // must cross river
  int cross_with = 0;
  for (int i=0; i<3; i++) {
    if (bit(s,i) != bit(t,i) && bit(s,i)==bit(s,me)) { cross_with++; which_cross = items[i]; }
    if (bit(s,i) != bit(t,i) && bit(s,i)!=bit(s,me)) return "";
  }
  if (cross_with > 1) return "";
  if (cross_with == 0) return "Cross alone";
  else return "Cross with " + which_cross;
}

void build_graph() {
    for (int s = 0; s < 16; ++s) {
        if (!bit(s, me)) continue;  // boat must be on same side as me
        if (bit(s, wolf) == bit(s, goat) && bit(s, goat) != bit(s, me)) continue;  // wolf and goat alone
        if (bit(s, goat) == bit(s, cabbage) && bit(s, cabbage) != bit(s, me)) continue;  // goat and cabbage alone

        // Cross with me only
        state n = s ^ (1 << me);
        nbrs[s].push_back(n);
        nbrs[n].push_back(s);
        edge_label[{s, n}] = "Cross alone";
        edge_label[{n, s}] = "Cross alone";

        // Cross with goat
        if (bit(s, goat) == bit(s, me)) {
            n = s ^ (1 << goat) ^ (1 << me);
            nbrs[s].push_back(n);
            nbrs[n].push_back(s);
            edge_label[{s, n}] = "Cross with goat";
            edge_label[{n, s}] = "Cross with goat";
        }

        // Cross with wolf
        if (bit(s, wolf) == bit(s, me)) {
            n = s ^ (1 << wolf) ^ (1 << me);
            nbrs[s].push_back(n);
            nbrs[n].push_back(s);
            edge_label[{s, n}] = "Cross with wolf";
            edge_label[{n, s}] = "Cross with wolf";
        }

        // Cross with cabbage
        if (bit(s, cabbage) == bit(s, me)) {
            n = s ^ (1 << cabbage) ^ (1 << me);
            nbrs[s].push_back(n);
            nbrs[n].push_back(s);
            edge_label[{s, n}] = "Cross with cabbage";
            edge_label[{n, s}] = "Cross with cabbage";
        }
    }
}

int main(void)
{
  build_graph();

  state start = 0, end = 15;
  
  search(start);
  if (visited[end])
    print_path (start, end);
  else
    cout << "No path!\n";
  
  return 0;
}
