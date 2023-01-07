#include <iostream>
#include <bits/stdc++.h>
#include<vector>
using namespace std;

//Variables to store number of alternative paths
int alternatePaths=5;
int N = 5;

//Variables to store number of alternative and shortest paths
vector<vector<int>> shortest_path;
vector<vector<int>> alternative_paths;

string branches[16] = {"Islamabad","Chakwal","Karachi","Lahore","Faislabad","Gujranwala","Sahiwal","Sargodha","Multan", "DG Khan" ,"Sialkot","Jehlum", "Rawlakot", "Hydrabad", "Quetta", "Peshawar"};
struct JourneyList
{
    string name;                         // Variable to store Passenger name
    string source;                        // Variable to store Passenger phone number
    string destination;                   // Variable to store Passenger phone number
    string phone;                        // Variable to store Passenger phone number
    JourneyList* next;
};
JourneyList* first;
JourneyList* last;

// Working functions
void askForJourney(JourneyList* newJourney)
{   
    // JourneyList *newJourney = new JourneyList();
    //Incase of empty nodes (No Journeys)
    if(first == NULL){
        // int choice, option;
        
        // cout<< "************* Journey Details: ****************\n";
        // cout<<"Enter passenger name: ";
        // cin>>newJourney->name;
        // cout<<"Enter passenger phone: ";
        // cin>>newJourney->phone;
        // cout<<"Enter passenger Source: ";
        // cin>>newJourney->source;
        // cout<<"Enter passenger destination: ";
        // cin>>newJourney->destination;

        //Linking linkedlist nodes
        newJourney->next = NULL;
        first = newJourney;
        last = newJourney;
    }

    else {
        // int choice, option;
        // bool flag = true;
        
        // cout<< "************* Journey Details: ****************\n";
        // cout<<"Enter passenger name: ";
        // cin>>newJourney->name;
        // cout<<"Enter passenger phone: ";
        // cin>>newJourney->phone;
        // cout<<"Enter passenger Source: ";
        // cin>>newJourney->source;
        // cout<<"Enter passenger destination: ";
        // cin>>newJourney->destination;

        //Linking linkedlist nodes
        last->next = newJourney;
        newJourney->next = NULL;
        last = newJourney;
        
        //Checking if no more than four Journeys are placed
        // if(count< 4){
        //     cout<<endl;
        //     int choice, option;
        //     bool flag = true;

        //     cout << "************* Journey Details: ****************\n";
        //     cout<<"Enter 1 to go Islamabad: "<<endl;
            
        //     //Linking linkedlist nodes
        //     last->next = newJourney;
        //     newJourney->next = NULL;
        //     last = newJourney;
        // }
        // else{
        //     cout<<"Four Journeys are allready being prepared!! Please Wait!!";
        //     cout<<endl<<endl;
        // }
    }   
    
}

//Delivering Journeys of Passengers
void deliverJourneys(){
    JourneyList* temp = first;
    string userJourney = "";
    int count = 0;

    if(temp != NULL){
        cout<<"-------------- Your Journeys Details-------------------"<<endl;
        cout<<"----------------------------------------------"<<endl;
        cout<<"Passenger Name:          "<<temp->name<<endl;
        cout<<"Passenger Phone:         "<<temp->phone<<endl;
        cout<<"Passenger Source:         "<<temp->source<<endl;
        cout<<"Passenger Destination:         "<<temp->destination<<endl;


        //Code to print shortest path of the graph
        cout<<"Shortest Path : ------------------------------"<<endl;
        for(int i=0; i<shortest_path.size(); i++){
            for(int j=0; j<shortest_path[i].size(); j++){
                if(j == shortest_path[i].size()-1){
                    cout<<branches[shortest_path[i][j]]<<" ";
                }
                else{
                    cout<<branches[shortest_path[i][j]]<<"-->";
                }
            }
            cout<<endl;
        }

        //Code to print alternative paths of the graph
        cout<<"\nAlternative Paths : --------------------------"<<endl;
        for(int i=0; i<alternative_paths.size(); i++){
            for(int j=0; j<alternative_paths[i].size(); j++){
                if(j == alternative_paths[i].size()-1){
                    cout<<branches[alternative_paths[i][j]]<<" ";
                }
                else{
                    cout<<branches[alternative_paths[i][j]]<<"-->";
                }
            }
            cout<<endl;
        }

                
        cout<<endl<<"----------------------------------------------"<<endl;
        //Deleting the delivered Journey from Journey list (Deleting Node From Start)
        JourneyList* deleted = first;
        first = first->next;
        deleted->next = NULL;
        delete deleted;
    }
    else{
        cout<<"No Journey placed!!! Place first!!"<<endl;
    }

    cout<<endl<<endl;
}

//Functions to find paths
//======================================GLOBAL VARIABLES==========================================================
const int INF = 1000;
string dest;
vector<int>gph[16];
int graph[16][16];
int graphtime[16][16];
int visited[16];
int parent[16];
int source;
string start =branches[source];
//================================BASIC IMPLEMENTATION OF GRAPHS==================================================
void add_edge(vector<int>gph[],int u,int v){
    gph[u].push_back(v);
    gph[v].push_back(u);
}
void addEdgeDistance(int v1, int v2, int w){
		graph[v1][v2] = w;
		graph[v2][v1] = w;				
}
void addEdgeTime(int v1, int v2, int w){
		graphtime[v1][v2] = w;
		graphtime[v2][v1] = w;				
}


//======================================ALL EDGES============================================================
void printpath(vector<int>path) //Print Edges
{
    int size = path.size();
    for (int i = 0; i < size; i++)
         if(i==size-1){
            cout << branches[path[i]] <<" ";
        }   
        else{
            cout << branches[path[i]] <<"--->";
        }  
    cout << "\n\n";
}

int isNotVisited(int x, vector<int> path) //Checking if Vertices are visited or not 
{
    int size = path.size();
    for (int i = 0; i < size; i++)
        if (path[i] == x)
            return 0;
    return 1;
}

void findpaths(vector<int> g[], int source, int destination, int v) //Through BFS
{
    queue<vector<int>> q;
    vector<int> path;
    path.push_back(source);
    q.push(path);
    while (!q.empty()) {
        path = q.front();
        q.pop();
        int last = path[path.size() - 1];
        
        if (last == destination)
            if(alternatePaths >= 0){
                // cout<<"hello";
                printpath(path);
                if(shortest_path.empty()){
                    shortest_path.push_back(path);
                }
                else{
                    alternative_paths.push_back(path);
                }
                alternatePaths--;
            }
            else{
                return;
            }      

        for (int i = 0; i < g[last].size(); i++) {
            if (isNotVisited(g[last][i], path)) {
                vector<int> newpath(path);
                newpath.push_back(g[last][i]);
                q.push(newpath);
            }
        }
    }
}


int main()
{   
    //Calling code for graphs
    int distance[16];

    //Adding nodes distance with other nodes
	addEdgeDistance(1,2,5);
    addEdgeDistance(1,3,5);
    addEdgeDistance(2,3,4);
    addEdgeDistance(2,4,3);
    addEdgeDistance(3,4,7);
    addEdgeDistance(3,5,7);	
    addEdgeDistance(3,8,8);	
    addEdgeDistance(4,8,11);
    addEdgeDistance(4,13,14);
    addEdgeDistance(4,12,13);
    addEdgeDistance(5,6,4);
    addEdgeDistance(5,8,5);
    addEdgeDistance(6,7,9);
    addEdgeDistance(7,14,12);
    addEdgeDistance(8,9,3);
    addEdgeDistance(9,10,4);
    addEdgeDistance(10,16,8);
    addEdgeDistance(10,14,3);
    addEdgeDistance(11,14,7);
    addEdgeDistance(11,16,4);
    addEdgeDistance(11,12,5);
    addEdgeDistance(12,13,9);
    addEdgeDistance(12,15,4);
    addEdgeDistance(13,15,5);
    addEdgeDistance(13,16,7);
	
    //Adding graph edges
	add_edge(gph,0,5);
	add_edge(gph,0,4);
	add_edge(gph,0,3);
	add_edge(gph,0,8);
	add_edge(gph,1,2);
	add_edge(gph,1,3);
	add_edge(gph,2,3);
	add_edge(gph,2,4);
	add_edge(gph,3,4);
	add_edge(gph,3,5);
	add_edge(gph,4,12);
	add_edge(gph,4,11);
	add_edge(gph,4,10);
	add_edge(gph,5,6);
	add_edge(gph,6,7);
	add_edge(gph,7,13);
	add_edge(gph,8,9);
	add_edge(gph,9,13);
	add_edge(gph,9,15);
	add_edge(gph,10,13);
	add_edge(gph,10,15);
	add_edge(gph,10,11);
	add_edge(gph,11,14);
	add_edge(gph,11,12);
	add_edge(gph,12,14);
	add_edge(gph,12,13);
	add_edge(gph,13,15);

	    

    bool flag = true;
    vector<int> destIndex;
    while (flag){
        int option;
        cout<<endl;
        cout << "*********** Favourite Panda ***********" << endl;
        cout << "Enter 1 to book a journey ticket: "<<endl;
        cout << "Enter 2 to check journey details: "<<endl;
        cout << "Enter 3 to exit: "<<endl;
        cout<<"*****************************************"<<endl;

        cout << "Enter your choice: ";
        cin>>option;

        JourneyList *newJourney = new JourneyList();
        if(option == 1){
            // Passenger credentials
            // askForJourney();
            // cout<<endl<<endl;
            
            JourneyList *newJourney = new JourneyList();
            int choice, option;
            
            cout<< "************* Journey Details: ****************\n";
            cout<<"Enter passenger name: ";
            cin>>newJourney->name;
            cout<<"Enter passenger phone: ";
            cin>>newJourney->phone;
            cout << "Enter your destination: "<<endl;
            cout << "1. For Chakwal     |  2. For Karachi "<<endl;
            cout << "3. For Lahore      |  4. For Faislabad"<<endl;
            cout << "5. For Gujranwala  |  6. For Sahiwal"<<endl;
            cout << "7. For Sargodha    |  8. For Multan"<<endl;
            cout << "9. For DG Khan     |  10. For Sialkot"<<endl;
            cout << "11. For Jehlum     |  12. For Rawlakot"<<endl;
            cout << "13. For Hyderabad  |  14. For Quetta"<<endl;
            cout << "15. For Peshawar   | Your choice: ";
            int a;
            cin >> a;
            destIndex.push_back(a);
            


            askForJourney(newJourney);
        }
        else if(option == 2){
            shortest_path.clear();
            alternative_paths.clear();
            findpaths(gph,source,destIndex[0],16);
            destIndex.erase(destIndex.begin());
            deliverJourneys();
            alternatePaths = N;
            
        }
        else if(option == 3){
            cout<<"Thank you for using FavouritePanda!! Have a great day!!!"<<endl;
            flag = false;
        }
        else{
            cout<<"Invalid Input!!"<<endl;
        }
    }


    cout<<endl;
}