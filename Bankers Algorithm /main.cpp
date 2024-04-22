/*
Criteria = Resource Allocation
Mode = Banker's Algorithm (Safety Algorithm)
*/

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main() {
    vector<int> MaxR = {10, 15, 20};
    vector< vector<int>> AllocR = {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}};
    vector< vector<int>> Max = {{7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}};
    vector<int> Available = {5, 10 , 15};
    vector< vector<int>> need(5, vector<int>(3));
    vector<int> visited(5,-1);
    vector<int> sequence(5,-1);
    
    for(int i = 0; i < 5; i++){
        for(int j = 0; j< 3 ; j ++){
            need[i][j] = (Max[i][j] - AllocR[i][j]);
        }
    }
    int index = 0;
    
    for(int i = 0; i< 5; i++){
        for(int j = 0; j < 5;j++){
            if(visited[j] == -1 && need[j][0] <= Available[0] && need[j][1] <= Available[1] && need[j][2] <= Available[2]){
                visited[j] = j;
                sequence[index++] = j;
                for(int k = 0 ;k < 3; k++){
                    Available[k] += AllocR[j][k];
                }
                break;
            }
        }
    }
    
    if(find(sequence.begin(), sequence.end(), -1) != sequence.end()){
        cout << "deadlock"<<endl;
    }
    else{
        for(auto i : sequence){
            cout << i << "\t";
        }
    }
    return 0;
}

