#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct MemoryBlock {
    int size;
    bool occupied;
    int process_id;
};

void bestFit(vector<MemoryBlock>& memory, vector<int>& process_sizes) {
    int next_process = 0;
    while (next_process < process_sizes.size()) {
        int best_fit_index = -1;
        int best_fit_size = INT_MAX;
        for (int i = 0; i < memory.size(); i++) {
            if (!memory[i].occupied && memory[i].size >= process_sizes[next_process] && memory[i].size < best_fit_size) {
                best_fit_index = i;
                best_fit_size = memory[i].size;
            }
        }
        if (best_fit_index != -1) {
            memory[best_fit_index].occupied = true;
            memory[best_fit_index].process_id = next_process;
            next_process++;
        } else {
            break;
        }
    }
}

int main() {
    int num_blocks, num_processes;
    cout << "Best Fit Memory Allocation\n ----------------------------------------------------------\n";
    cout << "Enter the number of memory blocks: ";
    cin >> num_blocks;
    cout << "Enter the number of processes: ";
    cin >> num_processes;

    // Initialize memory blocks
    vector<MemoryBlock> memory(num_blocks);
    for (int i = 0; i < num_blocks; i++) {
        cout << "Enter the size of block " << i << ": ";
        cin >> memory[i].size;
        memory[i].occupied = false;
        memory[i].process_id = -1;
    }

    // Initialize process sizes
    vector<int> process_sizes(num_processes);
    for (int i = 0; i < num_processes; i++) {
        cout << "Enter the size of process " << i << ": ";
        cin >> process_sizes[i];
    }

    // Apply Best Fit algorithm
    bestFit(memory, process_sizes);

    // Display the memory allocation
    cout << "\nMemory Allocation:\n";
    for (const MemoryBlock& block : memory) {
        cout << "Block size: " << block.size << ", Occupied: " << (block.occupied ? "Yes (Process " + to_string(block.process_id) + ")" : "No") << "\n";
    }

    return 0;
}