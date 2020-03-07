#include <iostream>
#include <fstream>
#include <string>
#include<bits/stdc++.h> 
#include <list>

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
  ifstream ufile(fileName);
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
  // first element is count rest are potential elements
  bool flag = true;
  int cur[N*N];
  cur[0] = 1;
  cur[1] = 0;
  int count;
  int changeC = 1;
  int elementsCh[N*N];
  elementsCh[0] = 0;
  int adjac[N*N];
  int loopLength = cur[0];
  while (flag == true){
    flag = false;
    int loopLength = cur[0]; // length of current
    // adjacent nodes
    cout << " THIS IS START \n \n";
    cout << " Current length of cur  : " << loopLength << endl;///D
    for(int i = 0; i < loopLength;i++){
      cout << " Current value = " << cur[i+1] << endl;
      int adjLength = dj[cur[i+1]].size();
      adjac[0] = adjLength;
      cout << " Numve of adj elements : " << adjLength << endl; //D
      count = 0;
      for(auto x:dj[cur[i+1]]){ // for each adjacent element
        cout << " Current adjacent vector : " << x << endl; //D
        cout << " Elements[x]: " << elements[x] << 
        " And elements[cur[i]] "<< elements[cur[i+1]]  <<endl; //D
        if(elements[x] == elements[cur[i+1]] && x > cur[i+1]){ // if same as current
          cout << ">>>> change C value before " << elementsCh[0] <<
          endl;
          elementsCh[0] = changeC;
          elementsCh[changeC] = x;
          changeC++;
          cout << "***** Value of current in If statement " << x <<
          endl;
          cout << " ////elementsCh[changeC] value is " << elementsCh[changeC-1] << endl;
          cout << " Count = " << count << endl;
          //elements[x] = color; 
          flag = true;
          adjac[count + 1] = x;
          cout << " Value at adjac[count] : " << adjac[count + 1] << endl;
          count++;
        } 
        
      }
      
    }
    

    int adjLength = sizeof(adjac)/sizeof(adjac[0]); //D
    cout << " Current adj length : " << adjLength << endl; //D
    cur[0] = count;
    cout << " 3Count = " << count << endl; 
    cout << "THIS length of elementsCh[0] "<< elementsCh[0] << endl;
    for(int i = 0; i < cur[0] ; i++){
      cur[i+1] = adjac[i +1] ;
      cout << " This is cur = " << cur[i+1] << " This is adjac "
      << adjac[i + 1] << endl;
    }

  }

  



  for(int i = 0; i < elementsCh[0];i++){
    elements[elementsCh[i+1]] = color;
  }
  
  elements[0] = color;
}



int main() { 
  string fileNam = "four.txt";
  /*  Making list of elements     */
  //opens file
  ifstream ufile(fileNam);
  int data;
  // gets first element of list
  ufile >> data; 
  int rows = data;
  ufile.close();
  int elementList[rows*rows];
  // returns list of elements
  openFile(fileNam,elementList);
  /*   Making graph       */
  int listLength = rows*rows;
  vector<int> matr[listLength];
  makeMatrix(matr,rows);

  adjacent(matr,listLength);
  printGraph(elementList,listLength,rows);


  /*
  for(auto x: matr[0]){
    cout << x << endl;
  } */

  ///cout << "Lenght of matr[0] = " << matr[0].size() << endl;
  /*    change color
             */
  cout << "Start of chnage color " << endl;

  
  changeColor(matr,elementList,rows,1);
  printGraph(elementList,listLength,rows);

  changeColor(matr,elementList,rows,6);
  printGraph(elementList,listLength,rows);

  changeColor(matr,elementList,rows,2);
  printGraph(elementList,listLength,rows);

  changeColor(matr,elementList,rows,3);
  printGraph(elementList,listLength,rows);

  changeColor(matr,elementList,rows,2);
  printGraph(elementList,listLength,rows);



  

    return 0; 
}
