#include <iostream>
#include <vector>

using namespace std;

struct MemoryBlock {
    int size;
    bool occupied;
    int process_id;
};

void nextFit(vector<MemoryBlock>& memory, vector<int>& process_sizes) {
    int next_block = 0;
    int next_process = 0;
    while (next_process < process_sizes.size()) {
        if (next_block == memory.size()) {
            next_block = 0;
        }
        if (!memory[next_block].occupied && memory[next_block].size >= process_sizes[next_process]) {
            memory[next_block].occupied = true;
            memory[next_block].process_id = next_process;
            next_process++;
        }
        next_block++;
    }
}

int main() {
    int num_blocks, num_processes;
    cout << "Next Fit Memory Allocation\n ----------------------------------------------------------\n";
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

    // Apply Next Fit algorithm
    nextFit(memory, process_sizes);

    // Display the memory allocation
    cout << "\nMemory Allocation:\n";
    for (const MemoryBlock& block : memory) {
        cout << "Block size: " << block.size << ", Occupied: " << (block.occupied ? "Yes (Process " + to_string(block.process_id) + ")" : "No") << "\n";
    }

    return 0;
}