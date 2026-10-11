#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Function to compute both final position and leaf states in one simulation
pair<int, vector<int>> simulateBalls(int D, long long n) {
    int num_switches = (1 << (D - 1)) - 1; // Only internal nodes are switches
    int num_leaves = 1 << (D - 1); // 2^(D-1)
    
    vector<int> switches(num_switches + 1, 0); // 1-indexed
    vector<int> leaf_counts(num_leaves, 0);
    int final_position = 0;
    
    for (long long ball = 1; ball <= n; ball++) {
        int current_pos = 1;
        
        while (current_pos <= num_switches) {
            if (switches[current_pos] == 0) {
                switches[current_pos] = 1;
                current_pos = current_pos * 2;
            } else {
                switches[current_pos] = 0;
                current_pos = current_pos * 2 + 1;
            }
        }
        
        final_position = current_pos;
        int leaf_index = current_pos - num_switches - 1;
        if (leaf_index >= 0 && leaf_index < num_leaves) {
            leaf_counts[leaf_index]++;
        }
    }
    
    vector<int> leaf_states(num_leaves);
    for (int i = 0; i < num_leaves; i++) {
        leaf_states[i] = leaf_counts[i] % 2;
    }
    
    return make_pair(final_position, leaf_states);
}

// Function to find where the nth ball lands
int findFinalPosition(int D, long long n) {
    return simulateBalls(D, n).first;
}

// Function to compute the final state of all leaf nodes
vector<int> computeLeafStates(int D, long long n) {
    return simulateBalls(D, n).second;
}

int main() {
    int D;
    long long n;
    
    cin >> D >> n;
    
    // Compute both results in one simulation
    auto result = simulateBalls(D, n);
    int final_position = result.first;
    vector<int> leaf_states = result.second;
    
    // Output the results
    cout << final_position << endl;
    
    for (int i = 0; i < leaf_states.size(); i++) {
        if (i > 0) cout << " ";
        cout << leaf_states[i];
    }
    cout << endl;
    
    return 0;
}