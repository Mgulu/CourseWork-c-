#include <iostream>
#include <fstream>
#include <string>
#include<bits/stdc++.h> 

using namespace std;

// node and next node
void addEdge(vector<int> adj[], int u, int v) 
{ 
    adj[u].push_back(v); 
    adj[v].push_back(u); 
} 
  

void matrix(vector<int> graphM , int values[],int n){
  /*
  for(int i =0;i<n;i++){
    matrix[row][]
  }
  */

}
// A utility function to print the adjacency list 
// representation of graph 
void adjacent(vector<int> adj[], int V) 
{ 
    for (int v = 0; v < V; ++v) 
    { 
        cout << "\n Adjacency list of vertex "
             << v << "\n head "; 
        // auto automatically gets the type of 
        for (auto x : adj[v]) 
           cout << "-> " << x; 
        printf("\n"); 
    } 
} 

void printGraph(int elementsList[],int lengthList,int rows){
  for(int i = 0;i <lengthList;i++){
      cout << elementsList[i];
      if(i % rows-(rows-1) == 0){
        cout << "\n";
      }
    }
}



int main() { 
  //opens file
  ifstream ufile("example.txt");
  int data;
  // gets first element of list
  ufile >> data; 
  // N x N 
  int N = data;
  int length = N*N;
  int elements[length];
  cout << data << endl;
  cout <<"START OF LOOP \n";
  // Gets all the int's inside the txt
  for(int i = 0; i < length;++i){
    ufile >> data; 
    elements[i] = data;
    cout << data << endl; 

  }
  /*
  if (file.is_open()) {
    std::string line;
    while (getline(file, line)) {
        // using printf() in all tests for consistency
        printf("%s \n", line.c_str());
    }
  
    file.close();
  }
  */
  ufile.close();
  /*
  int V = 9; 
    vector<int> adj[V]; 
    addEdge(adj, 0, 1); 
    addEdge(adj, 0, 3); 
    addEdge(adj, 1, 2); 
    addEdge(adj, 1, 4); 
    addEdge(adj, 2, 5); 
    addEdge(adj, 3, 4); 
    addEdge(adj, 3, 6); 
    addEdge(adj, 4, 5); 
    addEdge(adj, 4, 7);
    addEdge(adj, 5, 8);
    addEdge(adj, 6, 7);
    addEdge(adj, 7, 8);
    adjacent(adj, V); 
    // have a list of all the values in correct index 
  */

    cout << "START OF ELEMENTS \n";
    for(int i = 0; i < length;i++){
      cout << elements[i] << endl; 
  }

    cout << "starts of DJ \n";
    vector<int> dj[length];

    // Makes the graph
    for(int i = 0; i < length;++i){
      if(i+1 < length){
        addEdge(dj,i,i+1);
      }
      if(i+N <length){
        addEdge(dj,i,i+N);
      }
    }
    // Print all adjacencies.
    adjacent(dj,length);

    // Print the graph 
    printGraph(elements,length,N);
   
   







    return 0; 


    

    




}
