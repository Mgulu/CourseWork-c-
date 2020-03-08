#include <iostream>
#include <fstream>
#include <string>
#include<bits/stdc++.h> 
#include <list>

using namespace std;

// node and next node
void addEdge(vector<int> adj[], int u, int v) 
{   
    // Adds to the list in index U
    adj[u].push_back(v); 
    // Adds to the list in index v
    adj[v].push_back(u); 
} 
  
/*
void makeMatrix(vector<int> dj[], int N){
  int listLength = N*N;
  for(int i = 0; i < listLength ;i++){
      if(i+N <listLength){
          addEdge(dj,i,i+N);
        }
      if((i+1) % N == 0) continue;
      if(i+1 < listLength){
        addEdge(dj,i,i+1);      
    }
  }
}
*/

void makeMatrix(vector<int> dj[], int N){
  int listLength = N*N;
  for(int i = 0; i < listLength ;i++){
      if(i+N <listLength){
          addEdge(dj,i,i+N);
        }
      if((i+1) % N == 0) continue;
      if(i+1 < listLength){
        addEdge(dj,i,i+1);      
    }
  }
}
// A utility function to print the adjacency list 
// representation of graph 
void adjacent(vector<int> adj[], int V) 
{ 
    for (int v = 0; v < V; v++) 
    { 
        cout << "\n Adjacency list of vertex "
             << v << "\n head "; 
        // auto automatically gets the type of 
        for (auto x : adj[v]) 
           cout << "-> " << x; 
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
  for(int i = 0; i < N*N;i++){
    ufile >> data; 
    elements[i] = data;
  }
}




vector<int> adj(int cur,vector<int> elChange,vector<int> dj[],int elements[],int color){
   for(auto x:dj[cur]){
     // Checks to see if the value exists inside elChange
     bool contained = false;
     if(std::find(elChange.begin(), elChange.end(), x) != elChange.end()) {
      contained = true;
      }
     cout << " Current x :" << x << " Value is "
     << elements[x]  << " Current in DJ :" << cur << endl;
     if(elements[x] != elements[cur]){
       cout << " THIS IS inCORRECT x :" << x << endl;
       elChange.push_back(cur);       
     } else if(elements[x] == elements[cur] && x > cur /*&& elements[x] == color*/){
       cout << " //////THIS IS correct x :" << x << endl;
       elChange.push_back(x); 
       elChange = adj(x,elChange,dj,elements,color);      
     } else if (elements[x] == elements[cur] && x < cur && contained == false){
       cout << " //////THIS IS correct x :" << x << endl;
       elChange.push_back(x); 
       elChange = adj(x,elChange,dj,elements,color);  
     }
   }
   return elChange ;
}

void changeColor(vector<int> dj[], int elements[],int color){
  vector<int> elementsToChange;
  int prevColor = elements[0];
  elementsToChange = adj(0,elementsToChange,dj,elements,prevColor);
  for (int i =0 ; i < elementsToChange.size();i++){
    cout << " THIS IS " <<elementsToChange[i] << endl;
    elements[elementsToChange[i]] = color ;
  }  
  elements[0] = color;
}


/*
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
        cout << " ////elementsCh[changeC] value is " << elementsCh[changeC-1] << endl;
        cout << " Elements[x]: " << elements[x] << 
        " And elements[cur[i]] "<< elements[cur[i+1]]  <<endl; //D
        if(elements[x] == elements[cur[i+1]] && x > cur[i+1] && elementsCh[changeC-1] != x ){ // if same as current
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

    cur[0] = count;
    cout << " 3Count = " << count << endl; 
    cout << "THIS length of elementsCh[0] "<< elementsCh[0] << endl;
    cout << "Amount of adjacent Vectors "<< cur[0] << endl;
    for(int i = 0; i < cur[0] ; i++){
      cur[i+1] = adjac[i +1] ;
      cout << " This is cur = " << cur[i+1] << " This is adjac "
      << adjac[i + 1] << endl;
    }

  }
  for(int i = 0; i < elementsCh[0];i++){
    cout << " Value being changed :" << elementsCh[i+1] << endl;
    elements[elementsCh[i+1]] = color;
  }
  
  elements[0] = color;
}
*/


int main() { 
  string fileNam = "test.txt";
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
  cout << endl;

  printGraph(elementList,listLength,rows);

  


  /*
  for(auto x: matr[0]){
    cout << x << endl;
  } */

  ///cout << "Lenght of matr[0] = " << matr[0].size() << endl;
  /*    change color
             */
  cout << "Start of chnage color " << endl;

  /*
  cout << "Start of new change color" << endl;
  changeColor(matr,elementList,rows,2);
  printGraph(elementList,listLength,rows);

  cout << "Start of new change color" << endl;
  changeColor(matr,elementList,rows,1);
  printGraph(elementList,listLength,rows);

  cout << "Start of new change color" << endl;
  changeColor(matr,elementList,rows,2);
  printGraph(elementList,listLength,rows);
  */

  /*
  vector<int> elChange;

  elChange = adj(0,elChange,matr,elementList);

  cout << "THIS IS :"<< elChange.size() << " Size "<< endl;
  cout << "THIS IS :"<< elChange[0] << endl;
  cout << "THIS IS :"<< elChange[1] << endl;
  cout << "THIS IS :"<< elChange[2] << endl;
  cout << "THIS IS :"<< elChange[3] << endl;
  cout << "THIS IS :"<< elChange[4] << endl;
  cout << "THIS IS :"<< elChange[5] << endl;

  for (int i = 0; i << 5; i++){
    cout << "Value : " << elChange[i] << endl;
  }
  */

  printGraph(elementList,listLength,rows);
  cout << endl;
  changeColor(matr, elementList,4);
  printGraph(elementList,listLength,rows);

  changeColor(matr, elementList,2);
  printGraph(elementList,listLength,rows);
  

    return 0; 
}
