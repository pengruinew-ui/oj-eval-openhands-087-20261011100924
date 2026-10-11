#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Function to find where the nth ball lands by simulating
int findFinalPosition(int D, long long n) {
    int num_switches = (1 << (D - 1)) - 1; // Only internal nodes are switches
    
    // Initialize all switches to 0 (closed)
    vector<int> switches(num_switches + 1, 0); // 1-indexed
    
    // Simulate all balls up to n to find where the nth ball lands
    int final_position = 0;
    
    for (long long ball = 1; ball <= n; ball++) {
        int current_pos = 1; // Start at root
        
        // Drop the ball through the tree
        while (current_pos <= num_switches) {
            if (switches[current_pos] == 0) {
                // Switch is closed, open it and go left
                switches[current_pos] = 1;
                current_pos = current_pos * 2; // Go left
            } else {
                // Switch is open, close it and go right
                switches[current_pos] = 0;
                current_pos = current_pos * 2 + 1; // Go right
            }
        }
        
        // Ball has reached a leaf
        final_position = current_pos;
    }
    
    return final_position;
}

// Function to simulate the ball dropping process and compute leaf states
vector<int> computeLeafStates(int D, long long n) {
    int num_switches = (1 << (D - 1)) - 1; // Only internal nodes are switches
    int num_leaves = 1 << (D - 1); // 2^(D-1)
    
    // Initialize all switches to 0 (closed)
    vector<int> switches(num_switches + 1, 0); // 1-indexed
    vector<int> leaf_counts(num_leaves, 0);
    
    // Simulate each ball
    for (long long ball = 1; ball <= n; ball++) {
        int current_pos = 1; // Start at root
        
        // Drop the ball through the tree
        while (current_pos <= num_switches) {
            if (switches[current_pos] == 0) {
                // Switch is closed, open it and go left
                switches[current_pos] = 1;
                current_pos = current_pos * 2; // Go left
            } else {
                // Switch is open, close it and go right
                switches[current_pos] = 0;
                current_pos = current_pos * 2 + 1; // Go right
            }
        }
        
        // Ball has reached a leaf
        int leaf_index = current_pos - num_switches - 1; // Convert to 0-indexed
        if (leaf_index >= 0 && leaf_index < num_leaves) {
            leaf_counts[leaf_index]++;
        }
    }
    
    // Convert leaf counts to states (1 if odd, 0 if even)
    vector<int> leaf_states(num_leaves);
    for (int i = 0; i < num_leaves; i++) {
        leaf_states[i] = leaf_counts[i] % 2;
    }
    
    return leaf_states;
}

int main() {
    int D;
    long long n;
    
    cin >> D >> n;
    
    // Find the final position of the nth ball
    int final_position = findFinalPosition(D, n);
    
    // Compute the final states of all leaf nodes
    vector<int> leaf_states = computeLeafStates(D, n);
    
    // Output the results
    cout << final_position << endl;
    
    for (int i = 0; i < leaf_states.size(); i++) {
        if (i > 0) cout << " ";
        cout << leaf_states[i];
    }
    cout << endl;
    
    return 0;
}