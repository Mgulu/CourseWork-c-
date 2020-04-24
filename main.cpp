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
    vector<int> values;
    Node(int gValeur, int hValeur,int fValeur,int elements[],vector<int> path) {
      gValue = gValeur;
      hvalue = hValeur;
      fvalue = fValeur;
      grid = elements;   
      values = path;
    }
};

struct GreatestF {
    bool operator()( const Node& lx, const Node& rx ) const {
        return lx.fvalue < rx.fvalue;
    }
};



void addEdge(vector<int> adj[], int x, int y){       
    adj[x].push_back(y);    
    adj[y].push_back(x); 
} 

void deepCopy(int newElements[],int elements[],int elementsLength){
  for(int i=0; i<elementsLength; ++i){
    newElements[i] = elements[i];
    }
}



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




void printGraph(int elementsList[],int lengthList,int rows){
  for(int i = 0;i <lengthList;i++){
      cout << elementsList[i];
      if(i % rows-(rows-1) == 0){
        cout << "\n";
      }
    }
}

void openFile(string fileName, int elements[]){
  ifstream myFile(fileName.c_str());
  int data;
  myFile >> data; 
  int N = data;
  cout << data << endl;
 
  for(int i = 0; i < N*N;i++){
    myFile >> data; 
    elements[i] = data;
  }
}


vector<int> adj(int cur,vector<int> elChange,vector<int> dj[],int elements[],int color){
   for(auto x:dj[cur]){
     
     bool contained = false;
     if(find(elChange.begin(), elChange.end(), x) != elChange.end()) {
      contained = true;
        }
    
     if(elements[x] != elements[cur]){
       elChange.push_back(cur);       
      
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

void changeColor(vector<int> dj[], int elements[],int color){
  vector<int> elementsToChange;
  int prevColor = elements[0];
  elementsToChange = adj(0,elementsToChange,dj,elements,prevColor);
  for (int i =0 ; i < elementsToChange.size();i++){
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


int hValue(int elements[],int N){  
  unordered_set<int> color;
  for(int i =0;i < N ; i++){
    if (color.find(elements[i]) == color.end()){
        color.insert(elements[i]);
      } 
  }   
  return color.size();
} 

bool isSame(int elements[],int nElements[],int elementsSize){
  for(int i=0;i < elementsSize;i ++){
    if(elements[i] != nElements[i]){
      return false;
    }
  }
  return true;
}

void pathFind(vector<int> matrix[],int elements[],int listSize,int rowSize){
  vector<Node> openSet;
  vector<Node> closedSet;
  vector<int> path;
  Node rootNode(0,0,0,elements,path);
  openSet.push_back(rootNode); 
  Node currentNode = openSet[0];
  bool flag = false;  
  while (openSet.size() > 0 && flag == false){
    int index = 0;
    int counter = 0;
    Node currentNode = openSet[0];    
    closedSet.push_back(currentNode);        
    if(hValue(currentNode.grid,listSize) <= 2 ){
      int output = currentNode.gValue ;
      cout << "LOWEST AMOUNT OF MOVES :" << output + 1  << endl;
      cout << "WINNER WINNER CHICKEN DINNER " << endl;
      for(auto x: currentNode.values){
        cout << x;
      }
      flag = true;    
      continue;  
    } 
    
    for(int i = 1;i <10;i++){  
      int *currentGrid = new int [listSize];           
      deepCopy(currentGrid,currentNode.grid,listSize);             
      changeColor(matrix, currentGrid,i);    

      bool openFlag = false;
     
      for(auto x: openSet){
        if(isSame(x.grid,currentGrid,listSize) == true){
          openFlag = true;
          continue;
        }
      }      
      bool closedFlag = false;
     
      for(auto x:closedSet){
        if(isSame(currentGrid,x.grid,listSize) == true){
            closedFlag = true;          
            continue;
          }
      }        
    
      if (openFlag == false && closedFlag == false){
        int hvalue = hValue(currentGrid,listSize);
        int gValue = currentNode.gValue + 1;
        int fValue = hvalue + gValue;
        Node childNode(gValue,hvalue,fValue,currentGrid,currentNode.values);
        (childNode.values).push_back(i);
        openSet.push_back(childNode);                     
        }else{
         
          delete[] currentGrid; 
        }
    }    

  openSet.erase(openSet.begin());
  sort (openSet.begin(), openSet.end(),GreatestF());
  }  

  for(auto x:openSet){
    delete[] x.grid;
  } 
}


void generateGame(int listSize, int elementList[]){
  for (int i =0; i < listSize; i++){
          int ran = rand() % 6 + 1;
          elementList[i] = ran;
          
          }
}

int main() { 
  char choice;
  
  int rows = 0;
  int listLength;
  string fileNam;
  bool choiceFlag = false;
  while (choiceFlag == false){
    cout << "WELCOME , file or generate grid ? F/G" << endl;
    cin >> choice;
    if(choice == 'F' || choice == 'f'){   
      bool fileExists = false; 
      do{
        cout << "Enter file name : ";
        cin >> fileNam;
        ifstream myFile(fileNam.c_str());
        if(!myFile.fail() == true){
          fileExists = true;
          myFile >> rows ;
          listLength = rows*rows;      
          myFile.close(); 
        } else{
          
            cin.clear();
            
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Invalid File" << endl;
        }
      } while(!fileExists);

      
      choiceFlag = true;

    } else if ( choice == 'G' || choice == 'g'){       
      bool rowsFlag = false;
      do {
        cout << "Enter how many rows? (3-9) : ";
        cin >> rows;
        if(cin.good() && rows > 2 && rows <10 ){
          rowsFlag = true;
        } else {
          
            cin.clear();
            
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Needs to be a number between 3 - 9" << endl;
        }

      } while(!rowsFlag);
                  
      listLength = rows*rows;     
      choiceFlag = true;   
    }
  }

  int elementList[listLength];
  int tempList[listLength];

  if(choice == 'F' || choice == 'f'){
    openFile(fileNam,elementList);
  } else if(choice == 'G' || choice == 'g'){
    generateGame(listLength, elementList);
  }
   

  
  vector<int> matr[listLength];
  makeGraph(matr,rows);
  cout << endl;

  deepCopy(tempList,elementList,listLength);  
  
  
  printGraph(tempList,listLength,rows);  
  
 

  
  int finished = 0; 
  while (finished != 1){
    bool colorFlag = false;
    int color =0;  
    do {
        cout << "Enter Color (1-9) : ";
        cin >> color;
        if(cin.good() && color >0 && color < 10 ){
          colorFlag = true;
        } else {          
            cin.clear();            
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Needs to be a number between 1 - 9" << endl;
        }
      } while(!colorFlag);    
    changeColor(matr, elementList,color);
    printGraph(elementList,listLength,rows);
    cout << endl;    
    if(color == 0){
      finished = 1;
    } else{
    finished = checkWinner(elementList,listLength);
    }
  }
  pathFind(matr,tempList,listLength,rows);  

  return 0; 
}
