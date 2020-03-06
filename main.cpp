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
  

void makeMatrix(vector<int> dj[], int N){
  int listLength = N*N;
  for(int i = 0; i < listLength;++i){
      if(i+1 < listLength){
        addEdge(dj,i,i+1);
      }
      if(i+N <listLength){
        addEdge(dj,i,i+N);
      }
    }

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

void openFile(string fileName, int elements[]){
  ifstream ufile("example.txt");
  int data;
  // gets first element of list
  ufile >> data; 
  // N x N 
  int N = data;
  
  cout << data << endl;
  cout <<"START OF LOOP \n";
  // Gets all the int's inside the txt
  for(int i = 0; i < N*N;++i){
    ufile >> data; 
    elements[i] = data;
  }
}

void changeColor(vector<int> dj[], int elements[],int N,int color){
  
  bool flag = true;
  int count = 0;
  while (flag == true){
    flag = false;
    //int adjac[dj[count].size()];
    //int i = 0;
    for(auto x: dj[count]){
      //adjac[i] = x;
      //i++;
      if(elements[x] == elements[count]){
        elements[x] = color;
        flag = true;
      }      
    }
  }
  elements[0] = color;
}



int main() { 
  /*  Making list of elements     */
  //opens file
  ifstream ufile("example.txt");
  int data;
  // gets first element of list
  ufile >> data; 
  int rows = data;
  ufile.close();
  int elementList[rows*rows];
  string fileNam = "example.txt";
  // returns list of elements
  openFile(fileNam,elementList);
  for(int i = 0; i < rows*rows;++i){
    cout << elementList[i] << endl; 
  }
  /*   Making graph       */
  int listLength = rows*rows;
  vector<int> matr[listLength];
  makeMatrix(matr,rows);

  adjacent(matr,listLength);
  printGraph(elementList,listLength,rows);



  for(auto x: matr[0]){
    cout << x << endl;
  }

  cout << "Lenght of matr[0] = " << matr[0].size() << endl;

  int cc = 2;
  changeColor(matr,elementList,rows,cc);
  printGraph(elementList,listLength,rows);
  




    return 0; 


    

    




}
