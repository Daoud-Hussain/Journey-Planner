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

string branches[61] = {"Islamabad","Chakwal","Karachi","Lahore"
,"Faislabad","Gujranwala","Sahiwal","Sargodha","Multan", "DG Khan" ,
"Sialkot","Jehlum", "Rawlakot", "Hydrabad", "Quetta", "Peshawar", "Bagh","Sawabi","Tandoadama","Bhawalpur","layyah","Bhawalnagar",
"Wazirabad","Mirpurkhass","Kotaddu", "Ghotki" ,
"Mirpur","chaman", "Mansehra", "Arifwala", "Mianwali", "Khushab",
"Kasuur","Attock","Abbotabad","Sadiaqabad","Mardan","Gujjrat","Hasilpur",
"Jatio","Pakpattan", "Baadiin" ,
"Rahimyarkhan","Jhang", "Charsada", "Jajja", "Khankot", "Jaranwala","Gojra",
"Muzafargarh","DIkhan","Narowal","Larkana","Sakhuur","Veharii","Gilgit","Bakkhar", "Nawabshah" ,
"Umerkot","Texila", "Kohat"};
struct JourneyList
{
    string name;                         // Variable to store Passenger name
    string source;                        // Variable to store Passenger Source
    string destination;                   // Variable to store Passenger destination
    string phone;                        // Variable to store Passenger phone number
    JourneyList* next;
};
JourneyList* first;
JourneyList* last;

// Working functions
void askForJourney(JourneyList* newJourney)
{   
    //Incase of empty nodes (No Journeys)
    if(first == NULL){

        //Linking linkedlist nodes
        newJourney->next = NULL;
        first = newJourney;
        last = newJourney;
    }

    else {

        //Linking linkedlist nodes
        last->next = newJourney;
        newJourney->next = NULL;
        last = newJourney;
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
vector<int>gph[61];
int graph[61][61];
int graphtime[61][61];
int visited[61];
int parent[61];
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



    

//Main method starting here!!
int main()
{   
    //Calling code for graphs
    int distance[61];

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
    // ------------------------------------------------------------------------
    addEdgeDistance(1,16,7);
    addEdgeDistance(16,17,8);
    addEdgeDistance(17,18,3);
    addEdgeDistance(18,19,6);
     addEdgeDistance(19,61,3);
     addEdgeDistance(19,53,7);
     addEdgeDistance(7,20,6);
     addEdgeDistance(20,37,5);	
    addEdgeDistance(20,21,3);	
     addEdgeDistance(21,22,2);
     addEdgeDistance(22,24,5);
     addEdgeDistance(22,23,4);
     addEdgeDistance(24,25,7);
     addEdgeDistance(25,26,15);
     addEdgeDistance(26,27,6);
     addEdgeDistance(27,28,7);
     addEdgeDistance(28,29,5);
     addEdgeDistance(29,32,6);
     addEdgeDistance(30,31,9);
     addEdgeDistance(31,32,5);
    // //-----------------------------------------------------------------------
     addEdgeDistance(31,43,13);
     addEdgeDistance(32,33,4);
     addEdgeDistance(33,34,7);
     addEdgeDistance(34,35,2);
     addEdgeDistance(35,36,1);
     addEdgeDistance(36,58,14);	
     addEdgeDistance(43,42,13);
     addEdgeDistance(43,44,10);
     addEdgeDistance(42,41,12);
     addEdgeDistance(44,45,3);
     addEdgeDistance(44,46,19);
     addEdgeDistance(40,39,7);
     addEdgeDistance(39,58,12);
     addEdgeDistance(58,38,7);
     addEdgeDistance(38,37,12);
     addEdgeDistance(57,56,5);
     addEdgeDistance(56,55,5);
     addEdgeDistance(55,59,3);
     addEdgeDistance(55,51,10);
     addEdgeDistance(59,60,5);
     addEdgeDistance(49,48,7);	
     addEdgeDistance(48,47,8);
     addEdgeDistance(47,46,6);
     addEdgeDistance(49,50,7);
     addEdgeDistance(50,51,9);
     addEdgeDistance(51,52,8);
     addEdgeDistance(52,53,2);
     addEdgeDistance(53,54,7);
    addEdgeDistance(40,41,2);
    
	
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

    //.......................................	
    add_edge(gph,1,16);
    add_edge(gph,16,17);
    add_edge(gph,17,18);
	add_edge(gph,18,19);
	add_edge(gph,19,53);
	add_edge(gph,19,61);
	add_edge(gph,19,6);
	add_edge(gph,53,52);
	add_edge(gph,53,54);
	add_edge(gph,52,51);
	add_edge(gph,51,54);
	add_edge(gph,51,50);
	add_edge(gph,51,55);
	add_edge(gph,49,48);
	add_edge(gph,48,47);
	add_edge(gph,47,46);
	add_edge(gph,46,44);
	add_edge(gph,43,44);
	add_edge(gph,44,45);
	add_edge(gph,42,43);
	add_edge(gph,42,41);
	add_edge(gph,41,33);
    add_edge(gph,40,39);
	add_edge(gph,39,58);
	add_edge(gph,58,38);
	add_edge(gph,58,36);
	add_edge(gph,35,36);
	add_edge(gph,22,23);
	add_edge(gph,21,22);
	add_edge(gph,21,20);
	add_edge(gph,20,7);
	add_edge(gph,30,31);
	add_edge(gph,31,32);
	add_edge(gph,32,29);
	add_edge(gph,32,33);
	add_edge(gph,28,29);
	add_edge(gph,28,27);
	add_edge(gph,26,27);
	add_edge(gph,25,26);
	add_edge(gph,24,25);
    add_edge(gph,57,56);
    add_edge(gph,22,24);
    add_edge(gph,34,35);
    add_edge(gph,33,34);
    add_edge(gph,37,38);
    add_edge(gph,55,59);
    add_edge(gph,59,60);
    add_edge(gph,49,50);
    add_edge(gph,55,56);
    add_edge(gph,40,41);
    
    
	
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
            
            JourneyList *newJourney = new JourneyList();
            int choice, option;
            cout<< "<<<<************************************* Journey Path Details: *********************************************>>>>\n";
            cout<<"Enter passengers name here : ";
            cin>>newJourney->name;
            cout<<"Enter passenger Contact Number: ";
            cin>>newJourney->phone;
            cout << "Enter your destination Here: "<<endl<<endl;
            cout << "1. For Chakwal              |  2. For Karachi             |  3. For Lahore                |  4. For Faislabad"<<endl;
            cout << "5. For Gujranwala           |  6. For Sahiwal             |  7. For Sargodha              |  8. For Multan"<<endl;      
	        cout << "9. For DG Khan              |  10. For Sialkot            |  11. For Jehlum               |  12. For Rawlakot"<<endl;
            cout << "13. For Hyderabad           |  14. For Quetta             |  15. For Peshawar             |"<<endl;
			cout << "16. For Bagh                |  17. For Sawabi             |  18. For Tandoadam            |  19. For Bahawalpur"<<endl;
			cout << "20. For Laayah              |  21. For bhawalnagar        |  22. For Wazirabad            |  23. For MirpurKhas"<<endl;
			cout << "24. For KotAddu             |  25. For Ghotki              |  26. For Mirpur               |  27. For Chaman"<<endl;
			cout << "28. For Mansehra            |  29. For Arifwala           |  30. For Mianwali             |  31. For Khushab"<<endl;
			cout << "32. For Kasur               |  33. For Attock             |  34. For Abbotabad            |  35. For Sadaqabad"<<endl;
			cout << "36. For Mardan              |  37. For Gujrat             |  38. For Hasilpur             |  39. For Jatoi"<<endl;
			cout << "40. For Pakpatten           |  41. For baddin             |  42. For Rahimyarkhan         |  43. For Jhangg"<<endl;
			cout << "44. For Charsada            |  45. For Jajja              |  46. For Khankot              |  47. For Jaranwala"<<endl;
			cout << "48. For Gojra               |  49. For Muzafargarh        |  50. For DIkhan               |  51. For Narowal"<<endl;
			cout << "52. For Larkana             |  53. For sakhur             |  54. For Vehari               |  55. For Gilgit"<<endl;
			cout << "56. For Bakhar              |  57. For Nawabshah          |  58. For Umerkot              |  59. For Texila"<<endl;            
			                                 cout<<"60. For Kohat"<<endl;              
			
			cout<< "<<<<********************************************************************************************************>>>>\n\n";
			cout<< "Your choice: ";
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
            cout<<"Thank you for using Journey Planner!! Have a great day!!!"<<endl;
            flag = false;
        }
        else{
            cout<<"Invalid Input!!"<<endl;
        }
    }


    cout<<endl;
}