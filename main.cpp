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


int vContains(int num , vector<int> numbers){
  if (std::find(numbers.begin(), numbers.end(), num) != numbers.end())
    // Contains
		return 1;
	else
    // Dosent contain
		return 0;
}


vector<int> adj(int cur,vector<int> elChange,vector<int> dj[],int elements[],int color){
   for(auto x:dj[cur]){
     // Checks to see if the value exists inside elChange
     bool contained = false;
     if(std::find(elChange.begin(), elChange.end(), x) != elChange.end()) {
      contained = true;
      }
     //cout << " Current x :" << x << " Value is "
     //<< elements[x]  << " Current in DJ :" << cur << endl;
     if(elements[x] != elements[cur]){
       //cout << " THIS IS inCORRECT x :" << x << endl;
       elChange.push_back(cur);       
     } else if(elements[x] == elements[cur] && x > cur && contained == false){
       //cout << " //////THIS IS correct x :" << x << endl;
       elChange.push_back(x); 
       elChange = adj(x,elChange,dj,elements,color);      
     } else if (elements[x] == elements[cur] && x < cur && contained == false){
       //cout << " //////THIS IS correct x :" << x << endl;
       elChange.push_back(x); 
       elChange = adj(x,elChange,dj,elements,color);  
     }
   }
   return elChange ;
}


int gValue(int elements[],int current , int adj){
  if (elements[current] == elements[adj]){
    return 0;
  } else if (elements[current] != elements[adj]){
    return 1;
  }
}

int hValue(int elements[],vector<int> dj[],int adj){
    int counter = 0;
    for(auto x:dj[adj]){      
      if(elements[x] == elements[adj]){        
        counter -=1;
      } else if(elements[x]!= elements[adj]){  
        counter +=1;
      }
    }
    return counter;
}


void pathFind(vector<int> dj[],int elements[]){
  vector<int> openSet;
  vector<int> closedSet;
  vector<int> path;
  openSet.push_back(0);
  int previousFcost = 1000;
  while (openSet.size() > 0){
     //cout << "First element in openSet " << openSet[0] << endl;
    int currentNode = openSet[0];
    cout << " This is current Node :" << currentNode << endl;
    // if statement for the first index
    //cout << "current Node = " << currentNode << endl;
    if(currentNode != 0){
    // calculate adjacent
        for(auto x: openSet){
          //cout << " In open : " << x << endl;
          //cout << " Current Node : and X :"
          //<< currentNode << " " << x << endl;;
          int fCost = hValue(elements,dj,x) + gValue(elements,currentNode,x);
          cout << " Fcost : " << fCost<<" X Node : "
          << x <<endl;
          cout << "Previous F cost "<< previousFcost << endl;         
          if(fCost < previousFcost && vContains(x, closedSet) == 0 ){
            currentNode = x;
            previousFcost = fCost;
          }
        }        
    } 
    
    path.push_back(currentNode);
    
    openSet.erase(openSet.begin()+0);
    closedSet.push_back(currentNode);

    
    for(auto x: dj[currentNode]){
      if(vContains(x, closedSet) == 1)continue;
      //if(vContains(x,openSet)==0)
      openSet.push_back(x); 
    }   



  }

  int steps =0;
  for(int i=0;i < path.size()-1;i++){
    //cout << path[i] << " -> " << path[i+1] << endl;
    //cout << path[i] << " -> " << path[i+1] << endl;
    if(gValue(elements,path[i],path[i+1]) == 1){
      steps += gValue(elements,path[i],path[i+1]);
      cout << path[i] << " -> " << path[i+1] << endl;
      cout << " Change color to:" << elements[path[i+1]] << endl;
    }
  }
  // Needs to be divided by 2 as it repeats the first half again
  cout << " THESE ARE THE STEPS " << steps << endl;
}




void changeColor(vector<int> dj[], int elements[],int color){
  vector<int> elementsToChange;
  int prevColor = elements[0];
  elementsToChange = adj(0,elementsToChange,dj,elements,prevColor);
  for (int i =0 ; i < elementsToChange.size();i++){
    //cout << " THIS IS " <<elementsToChange[i] << endl;
    elements[elementsToChange[i]] = color ;
  }  
  elements[0] = color;
}





int checkWinner(int elements[],int N){
  int counter = 0;
  int color = elements[0];
  for(int i =1;i < N ; i++){
    if(elements[i] == color){
      counter +=1;
    }
  }
  if(counter == N-1){
    cout << "\n **" <<"Well Done , You've won ! **";
    return 1;
  }else{
    return 0;
  }
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
        }1

        
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
  string fileNam = "example.txt";
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

  //adjacent(matr,listLength);
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
  
   


  pathFind(matr,elementList);

  int finished = 0;
  while (finished != 1){
    int color;
    cout << "Color to change to from 1-6: ";
    //TODO add check for 1-6
    cin >> color;
    changeColor(matr, elementList,color);
    printGraph(elementList,listLength,rows);
    finished = checkWinner(elementList,listLength);
  }




    return 0; 
}
