//============================================================================
// Name        : CPPL.cpp
// Author      : Group 4
// Version     : 1.0.1.5
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <cstddef>
#include <stdlib.h>
using namespace std;

class InstaNetwork{
private:
	int i, j, k, x, bit;
	bool error = false;
	string line;
	ifstream file;
	list<int> *followers ;
	int V;
	int *followerCount;

public:
	bool isErrorInInput(){return error;}
	vector<vector<int> > loadNetwork(int dataStackSize);
	void getInput(int dataSize); //Extra utility function to input data manually into the file.
	void findConnections(vector<vector<int> > base);
	void showNetwork(vector<vector<int> > base, int size);
	bool areFollowers(unsigned roll_num_1, unsigned roll_num_2, vector<vector<int> >base); //**depriciated
	vector<int> commonLinks(unsigned roll_num_1, unsigned roll_num_2, vector<vector<int> >base);
	void findFollowers( vector<vector<int> >base);
	void setFollowerslist(vector<vector<int> > base, int dataStackSize); // set the followers for a student.
	bool linked(int roll_num_1, int roll_num_2, int dataStackSize); // find if link exits from one student to another.
	void noConnecttionFound(int roll_num_1, int roll_num_2); // if not connection found.
	void printAllLinks(int roll_num_1, int roll_num_2, int dataStackSize); // print found links, modified BFS algorithm.
	void findRoute(int src, int dest, bool visits[], int link[], int &index, int dataStackSize); // initilizer for findRoute(...)
    	void followEachOther(vector<vector<int> >base);
   	void followedByBoth(int roll_num_1,int roll_num_2, vector<vector<int> >base);
    	void followBoth(int roll_num_1, int roll_num_2,vector<vector<int> > base);
   	int CountFollowers(vector<vector<int> > base, int roll_num);
    	void findMaxFollowers(vector<vector<int> > base, int dataStackSize);
    	void saveFollowerCount(vector<vector<int> > base, int dataStackSize);


    //void maxFollowers(vector<vector<int> >base);
    //int firstIndex(int arr[],int low, int high);
    //int colWith1s(vector<vector<int> >base);
    };

int firstIndex(int arr[], int low, int high)
{
    if(high >= low)
    {
    int mid = low + (high - low)/2;
    if ( ( mid == 0 || arr[mid-1] == 0) && arr[mid] == 1)
      return mid;

    else if (arr[mid] == 0)
      return firstIndex(arr, (mid + 1), high);

    else
      return firstIndex(arr, low, (mid -1));
  }
  return -1;
}


int colWith1s(vector<vector<int> >base)
{
    int maxColIndex = 0, max = -1;
    int i,j, index;
    for (i = 0; i < base.size(); i++)
    {
       index = firstIndex (base[i], 0, base.size()-1);
       if (index != -1 && base.size()-index > max)
       {
           max = base.size() - index;
           maxColIndex = i+1;
       }
    }

    return (maxColIndex);
}

void InstaNetwork::getInput(int dataStackSize){

		int flag =0, bitCount=0;
		string line;
		ofstream file1;
		file1.open("DataFile.csv",  ios::out | ios::trunc );
		cin.ignore();

	for(int i =0; i<dataStackSize ; i++){


		getline(cin, line);


		size_t f = line.find_first_not_of("01,");
		if (f!=string::npos){
			//illegeal character not found!
			cout<<"Wrong Input!"<<endl;
			file1.close();
			break;

		}else{
			// string okay
			string bit;
			stringstream linestream(line);
			bitCount = 0;
			while(getline(linestream,bit,',')){

				bitCount++;

				if(bit.size() != 1){
					flag = 1;
					break;
				}
			  }

			if(flag == 0 && bitCount == dataStackSize)
				file1<<line<<endl;
			else{
				cout<<"Error in Input!!"<<endl;
				break;
			}
		     }
		}
			file1.close();
	}

// @Params : int, int, bool *, int *, int
//
//		1st point, from which the route is to be found.
// 		2nd point, to which the route is to be found.
//  	[] for maintaining all the visited nodes.
//  	[] for keeping track of traversed path.
//  	array index for counting number of nodes traversed.

void InstaNetwork::findRoute(int src, int dest,  bool visits[], int link[], int &index, int dataStackSize){

		// setting the status for current node => visted
	    visits[src] = true;

	    // save the current node into path list. +1-> for index mapping in the output!
	    link[index] = src+1;
	    index++;

	    // print all the addresses if destination is reached.
	    if (src == dest)
	    {
	        for (int i = 0; i<index; i++)
	            cout << link[i] << " ";
	        cout << endl;
	    }
	    else // else, go to the unvisited route in the followers of source (src) and check again!
	    {
	       list<int>::iterator i;
	        for (i = followers[src].begin(); i != followers[src].end(); ++i)
	            if (!visits[*i])
	                findRoute(*i, dest, visits, link, index, dataStackSize);
	    }

	    // remove the current node/ index form the path array!
	    // the recall path is 1 index before this.
	    index--;
	    visits[src] = false;
}

// @Params : int, int
// 		link flow; student 1(roll_num_1) ---> student 2(roll_num_2)

void InstaNetwork::printAllLinks(int roll_num_1, int roll_num_2, int dataStackSize){

	list<int>::iterator i;

	bool *visits = new bool[dataStackSize];
	int *link = new int[dataStackSize];
	int index = 0;

	for(int i =0 ;i<dataStackSize ; i++)
		visits[i] = false;

	findRoute(roll_num_1, roll_num_2, visits, link, index, dataStackSize);
}
// @Params : int, int
// if no connections between the students is found print status.

void InstaNetwork::noConnecttionFound(int roll_num_1, int roll_num_2){
	cout<<"No Link Exits Between Roll #"<<roll_num_1<<" and Roll #"<<roll_num_2<<endl;
}

bool InstaNetwork::linked(int roll_num_1, int roll_num_2, int dataStackSize){

	// basic BFS algorithm for testing connectivity b/w roll_num_2 and roll_num_1
	if(roll_num_1 == roll_num_2 )
	return true;

	bool *visits = new bool[dataStackSize];
	// set all nodes to be unvisited.
	for(int i=0;i<dataStackSize;i++)
		visits[i] = false;

	list<int> queue;
	// update status to visited for the current node/follower.
	visits[roll_num_1] = true;
	// push the visited node to queue and go ahead.
	queue.push_back(roll_num_1);
	list<int>::iterator itr;

	while(!queue.empty()){
		// pop the front entry from the queue.
		int front = queue.front();
		queue.pop_front();

		// cheack all the followers of front entry, if any of the is the destination,
		// then return true else mark the un-visited entries, visited and move them to the
		// queue.
		for(itr = followers[front].begin(); itr != followers[front].end() ; ++itr ){
			if(*itr == roll_num_2)
			return true;

			if(!visits[*itr]){
				visits[*itr] = true;
				queue.push_back(*itr);
			}
		}
	}
	return false;
}

// @Params : vactor[2D]
// 		contains the adjency matrix for the input data.
void InstaNetwork::setFollowerslist(vector<vector<int> >base, int dataStackSize){

	followers = new list<int>[dataStackSize];
	for(unsigned i=0; i<base.size(); i++)
		for(unsigned j=0; j<base[i].size(); j++)
			if(base.at(i).at(j)==1)
			followers[i].push_back(j);

}

// @Params : null
//	Loads the network details from external file to program context.
vector<vector<int> > InstaNetwork::loadNetwork(int dataStackSize){
	
	int bitCount=0, flag=0;
	vector< vector<int> > base;
	file.open("DataFile.csv");

	//initialising []base by 0

	cin.ignore();
	for(int i=0; i< dataStackSize ; i++){
	   
	   int bit_;
    	   vector<int> v;
	   bitCount=0;
	   getline(file,line);
		
	    size_t f = line.find_first_not_of("01,");

    	if (f!=string::npos){
    	//illegeal character not found!
    	flag=1;
    	file.close();
    	error = true;
    	break;
}
  else{
    	string bit;
    	stringstream linestream(line);
    	while(getline(linestream,bit,',')){
    	istringstream (bit)>> bit_;

    	bitCount++;

    	if(bit.size() != 1){
    		flag = 1;
    		break;
    	}
    	else v.push_back(bit_);

    }
    	if(flag == 0 && bitCount == dataStackSize)
    	    base.push_back(v);
    	else{
    		error = true;

    	}
}

}
	file.close();
	return base;
}

// @Params : vector[2D]
// 		Utility function for printing the network model.
void InstaNetwork::showNetwork(vector<vector<int> > base, int size){

	cout<< "      ";

	for(i=0;i<size;i++)
		cout<<i+1<<"  ";

	cout<<endl;
	cout<< "      ";

	for(i=0;i<size;i++)
		cout<<"---";
	cout<<endl;
	
	for(unsigned i=0;i<base.size();i++){
	   if(i+1 >= 10)
		cout << i+1<<"|"<<"   ";
	   else
		cout<<i+1<<" |"<<"   ";

	    for( unsigned j=0;j<base[i].size();j++){
		cout<<base[i][j]<<"  ";
	}
		cout<<endl;
     }
	cout<<endl<<endl;
}

// @Params : vector[2d]
// 		cheack for mutual followers among studends
//       student A <---> student B

// @Params : unsigned, unsigned, vector[2D]
//		check if, given two students follow each other or not.

bool InstaNetwork::areFollowers(unsigned roll_num_1, unsigned roll_num_2, vector<vector<int> >base){

	if(base.at(roll_num_1 -1).at(roll_num_2 -1) == 1 && base.at(roll_num_2 -1).at(roll_num_1 -1) == 1)
		return true;
	
	return false;
}

void InstaNetwork::followEachOther(vector<vector<int> >base)
{
    int i,j;
     for(i=0;i<base.size();i++){
        for(j=i+1;j<base[i].size();j++){
            if(base[j][i] ==1 && base[i][j] == 1)
                cout<<i+1<<" and "<<j+1<<" follow each other"<<endl;
        }
    }
}
void InstaNetwork::followedByBoth(int roll_num_1,int roll_num_2,vector<vector<int> > base)
{
    int j,flag=0;
    for(j=0; j<base.size(); j++){
        if(roll_num_1 == roll_num_2){
            cout<<"No one can be followed by himself \n";
            break;
        }
        else if(base[roll_num_1-1][j] == 1 && base[roll_num_2-1][j]==1){
            cout<<j+1<<",";
            flag=1;
        }

    }
    cout<<" followed by both "<<roll_num_1<<" and "<<roll_num_2<<endl;
    
	if(flag != 1)
        cout<<"No one is followed by both of them \n";
}

void InstaNetwork::followBoth(int roll_num_1, int roll_num_2,vector<vector<int> > base)
{
    int i,flag=0;
    for(i = 0; i < base.size(); i++){
        if(roll_num_1 == roll_num_2){
            cout<<"No one can follow himself \n";
            break;
        }
        else if(base[i][roll_num_1-1] == 1 && base[i][roll_num_2-1] == 1){
            cout<<i+1<<",";
            flag=1;
        }
    }
    cout<<" follow both "<<roll_num_1<<" and "<<roll_num_2<<endl;
    if(flag!=1)
        cout<<"They don't follow a common person \n";
}

// @Params : unsigned, vector[2D]
//		will return all the followers of a student.

void InstaNetwork::maxFollowers( vector<vector<int> >base)
{
//function to count the row with maximum 1

    int i,j;
    vector<vector<int> >base2;
    //making rows into columns
        for(i=0;i<base.size();i++)
            for(j=0;j<base[i].size();j++)
		   base2[j][i]=base[i][j];

     cout<<"Student with max followers is " << colWith1s(base2);*/
}

void InstaNetwork::findConnections(vector<vector<int> > base){
	for(unsigned i=0; i<base[roll_num].size(); i++){
		if(base.at(roll_num).at(i)==1)
			followers.push_back(i);
	}
}


int InstaNetwork::CountFollowers(vector<vector<int> > base, int roll_num){
        int count_ = 0;
	for(unsigned j = 0; j<base.size() ; j++ )
		if(base.at(roll_num).at(j) ==1)
		count_++;
	
	return count_;
}

void InstaNetwork::saveFollowerCount(vector<vector<int> > base, int dataStackSize){
	followerCount = new int[dataStackSize];

	//for(unsigned int i = 0; i<dataStackSize ; i ++)
		//followerCount[i] = CountFollowers(base, i+1);

}
void InstaNetwork::findMaxFollowers(vector<vector<int> > base, int dataStackSize){

	saveFollowerCount(base, dataStackSize);
	int *roll_arr = new int[50];
	int max_f = 0, j=0;
	
	for(unsigned i=0;i<dataStackSize; i++){
			if(followerCount[i] >= max_f)
				roll_arr[j] = i+1;
			j++;
	}
	
	for(unsigned i =0 ; i < j ; i++)
		cout<<"Roll #"<<roll_arr[i]<<" has maximum followers i.e "<<followerCount[roll_arr[i]-1]<<endl; 
}

int main() {

	InstaNetwork network;
	unsigned roll_num_1,
	roll_num_2,
	dataStackSize;
	int choice,i,j;
	char ch;

	cout<<"\n\n"<<"\t\t\t\t\t===========Welcome to the Instagram Network===========\n";
	cout<<"  \n Enter Total Number of students in the Network! ";
	cin>>dataStackSize;

	//network.getInput(dataStackSize);
	
	vector<vector<int> > base = network.loadNetwork(dataStackSize);
	if(!network.isErrorInInput()){
	network.showNetwork(base, dataStackSize);

	//network.findConnections(base);



	network.setFollowerslist(base, dataStackSize);
   
    do{
        cout<<"\n\n\tWant do u want to know about from this network ?\n";
        cout<<"1. Students who follow each other \n";
        cout<<"2. Any 2 students follow each other, if NO get all the reachable paths \n";
        cout<<"3. Who all are the students followed by both of them \n";
        cout<<"4. Who all are the students who follow both of them \n";
        cout<<"5. Who has the maximum followers \n";
        cout<<"6. Exit out of the program \n";
        cout<<"Enter your choice\n";
        cin>>choice;
   
	if(choice==2||choice==3||choice==4){
            cout<<"Hello";
	
		while(true){
		   cout<<"Enter two roll numbers!"<<endl;
		   cin >> roll_num_1 >> roll_num_2;

		if(roll_num_1 > dataStackSize || roll_num_2 > dataStackSize || roll_num_1 == 0 || roll_num_2 == 0)
			cout<<"Invalid Roll numbers "<<endl;
		
		else break;
	}
    }

	if(choice==1){
        network.followEachOther(base);
    }
	if(choice==2){
	if(network.areFollowers(roll_num_1, roll_num_2, base))
		cout<< "Roll no "<< roll_num_1<< " and "<< "Roll no "<< roll_num_2<< " follow each other!!";

	else{
        cout<<"Here"<<endl;
		if(network.linked(roll_num_1-1, roll_num_2-1, dataStackSize)){
                cout<<"Here1"<<endl;
			network.printAllLinks(roll_num_1-1, roll_num_2-1, dataStackSize);
		}
		else{
                cout<<"Here2"<<endl;
			network.noConnecttionFound(roll_num_1, roll_num_2);
	}
     }
  }
	else if(choice==3)
        network.followedByBoth(roll_num_1,roll_num_2,base);
    
    else if(choice==4)
        network.followBoth(roll_num_1,roll_num_2,base);
    
    else if(choice==5)
    	 network.findMaxFollowers(base, dataStackSize);
   
    else if(choice==6)
       	 exit(0);
    
	    cout<<"\nDo you want to continue ?? (Y/N)";
    cin>>ch;
    }while(ch=='y'||ch=='Y');
 }
	else 
	    cout<<"Error in input!!"<<endl;
	
	return 0;
}
