#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Function to find where the nth ball lands
int findFinalPosition(int D, long long n) {
    int num_switches = (1 << (D - 1)) - 1; // Only internal nodes are switches
    
    // For small n, use simulation
    if (n <= 1000000) {
        vector<int> switches(num_switches + 1, 0); // 1-indexed
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
        }
        
        return final_position;
    } else {
        // For large n, use mathematical approach
        int position = 1;
        long long temp_n = n;
        
        for (int level = 1; level < D; level++) {
            if (temp_n % 2 == 1) {
                position = position * 2 + 1;
                temp_n = (temp_n + 1) / 2;
            } else {
                position = position * 2;
                temp_n = temp_n / 2;
            }
        }
        
        return position;
    }
}

// Function to compute the final state of all leaf nodes
vector<int> computeLeafStates(int D, long long n) {
    int num_leaves = 1 << (D - 1); // 2^(D-1)
    vector<int> leaf_states(num_leaves, 0);
    
    // Use simulation for small n, mathematical approach for large n
    if (n <= 1000000) {
        // Use simulation for small n
        int num_switches = (1 << (D - 1)) - 1; // Only internal nodes are switches
        vector<int> switches(num_switches + 1, 0); // 1-indexed
        vector<int> leaf_counts(num_leaves, 0);
        
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
            
            int leaf_index = current_pos - num_switches - 1;
            if (leaf_index >= 0 && leaf_index < num_leaves) {
                leaf_counts[leaf_index]++;
            }
        }
        
        for (int i = 0; i < num_leaves; i++) {
            leaf_states[i] = leaf_counts[i] % 2;
        }
    } else {
        // Use mathematical approach for large n
        // For each leaf, compute how many balls reach it using the efficient algorithm
        for (int leaf = 0; leaf < num_leaves; leaf++) {
            long long balls_to_leaf = 0;
            long long temp_n = n;
            int current_pos = 1;
            int target_leaf = leaf + (1 << (D - 1));
            
            // Trace from root to the target leaf
            int num_switches = (1 << (D - 1)) - 1;
            while (current_pos <= num_switches) {
                if (temp_n % 2 == 1) {
                    if (target_leaf > current_pos * 2 + 1) {
                        current_pos = current_pos * 2 + 1;
                        temp_n = (temp_n + 1) / 2;
                    } else {
                        current_pos = current_pos * 2;
                        temp_n = temp_n / 2;
                    }
                } else {
                    if (target_leaf > current_pos * 2) {
                        current_pos = current_pos * 2 + 1;
                        temp_n = temp_n / 2;
                    } else {
                        current_pos = current_pos * 2;
                        temp_n = temp_n / 2;
                    }
                }
            }
            
            if (current_pos == target_leaf) {
                balls_to_leaf = temp_n;
            }
            
            leaf_states[leaf] = balls_to_leaf % 2;
        }
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