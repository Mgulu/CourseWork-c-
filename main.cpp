  #include <iostream>
#include <fstream>
#include <string>
#include<bits/stdc++.h> 
#include <list>

using namespace std;

class Node {       
  public:                
    int gValue;
    int hvalue;
    int fvalue;     
    int *grid;  
    Node(int gValeur, int hValeur,int fValeur,int elements[]) {
      gValue = gValeur;
      hvalue = hValeur;
      fvalue = fValeur;
      grid = elements;
      
    }
};

void deepCopy(int newElements[],int elements[],int elementsLength){
  for(int i=0; i<elementsLength; ++i)
    newElements[i] = elements[i];

}

/* Prints all the elements in a  vector*/
void print(vector<int> printList){
  for(int i =0;i < printList.size();i++){
    cout << printList[i] << " ";
  }
  cout<< endl;
}


/* Adds values to the array of vectors */
void addEdge(vector<int> adj[], int x, int y) 
{   
    // Adds to the list in index x
    adj[x].push_back(y); 
    // Adds to the list in index y
    adj[y].push_back(x); 
} 
  

/* Makes the graph with all the connections between nodes */
void makeGraph(vector<int> dj[], int N){
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

/* Prints the elements in the list in grid format */
void printGraph(int elementsList[],int lengthList,int rows){
  for(int i = 0;i <lengthList;i++){
      cout << elementsList[i];
      if(i % rows-(rows-1) == 0){
        cout << "\n";
      }
    }
}

/* Opens and reads all the data from a file */
void openFile(string fileName, int elements[]){
  ifstream ufile(fileName);
  int data;
  // gets first element of list
  ufile >> data; 
  // N x N 
  int N = data;
  cout << data << endl;
  // Gets all the int's inside the txt
  for(int i = 0; i < N*N;i++){
    ufile >> data; 
    elements[i] = data;
  }
}


/* Checks if an element is in a vector list */
int vContains(int num , vector<int> numbers){
  if (std::find(numbers.begin(), numbers.end(), num) != numbers.end())
    // Contains
		return 1;
	else
    // Dosent contain
		return 0;
}

/* Looks for all the adjacent elements that are the same
    Starting from the pivot.
    reutrns: elements to be changed */
vector<int> adj(int cur,vector<int> elChange,vector<int> dj[],int elements[],int color){
   for(auto x:dj[cur]){
     // Checks to see if the value exists inside elChange
     bool contained = false;
     if(std::find(elChange.begin(), elChange.end(), x) != elChange.end()) {
      contained = true;
        }
     // If the elements are not the same only push back the parent
     if(elements[x] != elements[cur]){
       elChange.push_back(cur);       
       // recursively calls adj for elements who have similar values
     } else if(elements[x] == elements[cur] && x > cur && contained == false){

       elChange.push_back(x); 
       elChange = adj(x,elChange,dj,elements,color);      
     } else if (elements[x] == elements[cur] && x < cur && contained == false){
  
       elChange.push_back(x); 
       elChange = adj(x,elChange,dj,elements,color);  
     }
   }
   return elChange ;
}

/* Procedure that changes the the color of elements in grid */
void changeColor(vector<int> dj[], int elements[],int color){
  vector<int> elementsToChange;
  int prevColor = elements[0];
  elementsToChange = adj(0,elementsToChange,dj,elements,prevColor);
  for (int i =0 ; i < elementsToChange.size();i++){
    elements[elementsToChange[i]] = color ;
  }  
  elements[0] = color;
}


/* Checks if two elements are the same then returns a value */
int gValue(int elements[],int current , int adj){
  if (elements[current] == elements[adj]){
    return 0;
  } else {
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


/*
int *goalState(int adj, int elements[]){
  int yo[25];
  for(int i =0; i < 25;i++){
    yo[i] = yo[adj];
  }
  return yo;
}

int hValue(int elements[],vector<int> dj,int adj){

  changeColor(dj, elements,elements[path[i+1]] )
  
}
*/

/* Checks if all the elements are the same */
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

/* Checks if all the elements are the same */
int missPlaced(int elements[],int N){
  int counter = 0;
  int color = elements[0];
  for(int i =1;i < N ; i++){
    if(elements[i] != color){
      counter +=1;
    }
  }
  return counter;
}

/*
int missPlaced(int elements[],int N){
  //int counter = 0;
  //int color = elements[0];
  std::unordered_set<int> colours;
  for(int i =0;i < N ; i++){
    if (colours.find(elements[i]) == colours.end()){
        colours.insert(elements[i]);
      } 
  }
  unordered_set<int> :: iterator itr;  
    // iterator itr loops from begin() till end() 
  for (itr = colours.begin(); itr != colours.end(); itr++) {
      Fcout << *itr << " " << endl; 
    } 
  
  return colours.size();
}*/



bool isSame(int elements[],int nElements[],int elementsSize){
  for(int i=0;i < elementsSize;i ++){
    if(elements[i] != nElements[i]){
      return false;
    }
  }
  return true;
}

int won(int elements[],int size){
  int same[2] = {0,0};
  int u = 0; 
  for(int i =0;i < size ; i++){
    if(elements[0] != elements[i]){
      same[u] = elements[i];
      u += 1;
    }
  }
  if(same[0] != same[1]){
    return 1;
  } else if (same[0] == same[1]){
    return 0;
  }

}


void pathFind(vector<int> dj[],int elements[],int listSize,int rowSize){
  vector<Node> openSet;
  vector<Node> closedSet;
  vector<int> path;
  Node rootNode(0,0,0,elements);
  openSet.push_back(rootNode); 
  Node currentNode = openSet[0];
  int loop = 0;
  int currentUnique = missPlaced(elements,listSize);
  int previousGrid[listSize];
  while (openSet.size() > 0 ){
    int lowestFcost = 100000;
    int index = 0;
    int counter = 0;
    for(auto x: openSet){
      if(x.fvalue < lowestFcost){
        lowestFcost = x.fvalue;
        currentNode = x;
        index = counter;   
      }
      counter += 1;
    }
    
   

    loop +=1;
    closedSet.push_back(currentNode);
    //cout << " ClosedSet Size : " << closedSet.size() << endl;
    cout << " LOOP :" << loop << endl;
   // cout << " LowestFcost & CurrentGrid :" << lowestFcost << endl;  
    printGraph(currentNode.grid,listSize,rowSize);
    cout << endl;
    
    cout << endl;
    cout << "Current Gvalue " << currentNode.gValue << endl;
    cout << "Current Hvalue " << currentNode.hvalue << endl;
    if(missPlaced(currentNode.grid,listSize) < 3){
      int output = currentNode.gValue + won(currentNode.grid,listSize);
      cout << "LOWEST AMOUNT OF MOVES :" << output  << endl;
      cout << "WINNER WINNER CHICKEN DINNER " << endl;
      exit(0);      
    } 

    

    for(int i =1;i <10;i++){  
      int * currentGrid;
      currentGrid = new int [listSize];    
      //int currentGrid[listSize];
      //cout << currentGrid << endl;
      deepCopy(currentGrid,currentNode.grid,listSize);       
      //cout << endl;
      changeColor(dj, currentGrid,i);
      //cout << endl;
      


      bool openFlag = false;
      for(auto x: openSet){
        if(isSame(x.grid,currentGrid,listSize) == true){
          openFlag = true;
          continue;
        }
      }
      
      bool closedFlag = false;
      for(auto x:closedSet){
        if(isSame(currentGrid,x.grid,listSize) == true &&
          x.gValue > currentNode.gValue +1){
            x.gValue = currentNode.gValue + 1;
            closedFlag = true;
            //cout << " IN HERE " << endl;
            //printGraph(currentGrid,listSize,rowSize);
            //cout << " IN HERE " << endl;
            continue;
          }
        else if(isSame(currentGrid,x.grid,listSize) == true &&
          x.gValue < currentNode.gValue +1 ){
            closedFlag = true;
            //cout << " Outchea " << endl;
            //printGraph(currentGrid,listSize,rowSize);
            //cout << " Outchea " << endl;
            continue;
          }
        
        if (openFlag == false && closedFlag == false){
          int hValue = missPlaced(currentGrid,listSize);
          int gValue = currentNode.gValue +1 ;
          int fValue = hValue + gValue;
          Node childNode(gValue,hValue,fValue,currentGrid);
          openSet.push_back(childNode);   
          //cout << " Added To Openset " << endl;         
          //printGraph(currentGrid,listSize,rowSize);  
          //cout << " hValye " << childNode.hvalue << endl;
          //cout << " Added To Openset " << endl;
          }

      }     

    }
  
  vector<int> inOpen;
  int indexN = 0;
  for(auto x: openSet){
    if(isSame(currentNode.grid,x.grid,listSize)){
      inOpen.push_back(indexN);
    }
    indexN +=1;
  }

  for(auto x:inOpen){
    openSet.erase(openSet.begin() + x);
  }
  cout << endl;

  
  cout << " OpenSet Size : " << openSet.size() << endl;
  
  }



}


/* Checks if an element is in a vector list 
vector<int> pathFind(vector<int> dj[],int elements[]){
  vector<int> openSet;
  vector<int> closedSet;
  vector<int> path;
  vector<int> finalPath;
  openSet.push_back(0);
  int previousFcost = 1000;  
  while (openSet.size() > 0){
    
    int currentNode = openSet[0];
   
        for(auto x: openSet){
         
          int fCost = hValue(elements,dj,x) + gValue(elements,currentNode,x);
          //cout << " Fcost : " << fCost<<" X Node : "
          //<< x <<endl;       
          if(fCost < previousFcost ){
            currentNode = x;
            previousFcost = fCost;
          }
        }  
    
   
    path.push_back(currentNode);

    
    openSet.erase(openSet.begin()+0);
    closedSet.push_back(currentNode);

    
    for(auto x: dj[currentNode]){
      if(vContains(x, closedSet) == 1)continue;
      if(vContains(x,openSet)==1)continue;
      openSet.push_back(x); 
    }   

    
    for(auto x: openSet){     
        if(vContains(x, closedSet) == 1)continue;
        if(vContains(x,openSet)==1)continue;
        openSet.push_back(x); 
      }
  }
  
  int steps =0;
  for(int i=0;i < path.size()-1;i++){
    
    if(gValue(elements,path[i],path[i+1]) == 1 ){     
      finalPath.push_back(elements[path[i+1]]);
      changeColor(dj, elements,elements[path[i+1]]);
      steps += gValue(elements,path[i],path[i+1]);
      
    }
  }
  
  return finalPath;
}
*/









/* Makes a random grid  */
void generateGame(int listSize, int elementList[]){
  for (int i =0; i < listSize; i++){
          int ran = rand() % 6 + 1;
          elementList[i] = ran;
          //cout << gen[i] << endl;
          }

}


int main() { 
  char choice;
  cout << "WELCOME , file or generate grid ? F/G" << endl;
  cin >> choice;
  int rows;
  int listLength;
  string fileNam;
  if(choice == 'F'){    
    cout << "Enter file name : ";
    cin >> fileNam;
    ifstream ufile(fileNam);
    ufile >> rows ;
    listLength = rows*rows;
    ufile.close();
    

  } else if ( choice == 'G'){
    cout << "Enter how many rows? : ";
     cin >> rows ;
    listLength = rows*rows;
    

  }

  int elementList[listLength];
  int tempList[listLength];



  
  if(choice == 'F'){
    openFile(fileNam,elementList);
  } else if(choice == 'G'){
    generateGame(listLength, elementList);
  }
  
  
  /* deep copy 
  int deepCopy[listLength];
  memcpy(deepCopy,elementList,listLength);
  cout << elementList <<  endl;
  */
  
  
  
  /*   Making graph       */
  
  vector<int> matr[listLength];
  makeGraph(matr,rows);


  cout << endl;

  
  for(int i=0; i<listLength; ++i)
        tempList[i] = elementList[i];
  
  
  printGraph(tempList,listLength,rows);  
  
  
  pathFind(matr,tempList,listLength,rows);

  /*
  int finished = 0;
  while (finished != 1){
    int color;
    cout << "Color to change to from 1-6: ";
    //TODO add check for 1-6
    cin >> color;
    changeColor(matr, elementList,color);
    printGraph(elementList,listLength,rows);
    if(color == 0){
      finished = 1;
    } else{
    finished = checkWinner(elementList,listLength);
    }
  }
  cout << " Minimum moves to finish was " << bestPath.size()<<endl;
  cout<< "These were the best moves :";
  print(bestPath);
  */



    return 0; 
}
