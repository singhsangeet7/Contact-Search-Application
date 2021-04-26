// C++ Program to Implement a Contact Add/Search
// Using Trie Data Structure
#include <bits/stdc++.h>
#include<algorithm>
using namespace std;

struct TrieNode
{
	// Each Trie Node contains a Map 'child'
	// where each alphabet points to a Trie
	// Node.
	unordered_map<char,TrieNode*> child;

	// 'isLast' is true if the node represents
	// end of a contact
	bool isLast;
	// 'toReverse' is true if string has both first and
	// last name sperated by space
	bool toReverse;

	// Default Constructor
	TrieNode()
	{
		// Initialize all the Trie nodes with NULL
		for (int i = 65; i <= 122; i++)
		{
            		char c=i;
			child[c] = NULL;
        	}
		isLast = false;
		toReverse=false;
	}
};

// Making root NULL for ease so that it doesn't
// have to be passed to all functions.
TrieNode *root = NULL;


// Insert a Contact into the Trie
void insert(string name,bool toReverse)
{
	int len = name.length();

	// 'itr' is used to iterate the Trie Nodes
	TrieNode *itr = root;
	for (int i = 0; i < len; i++)
	{
		// Check if the s[i] is already present in
		// Trie
		TrieNode *nextNode = itr->child[name[i]];
		if (nextNode == NULL)
		{
			// If not found then create a new TrieNode
			nextNode = new TrieNode();

			// Insert into the Map
			itr->child[name[i]] = nextNode;
		}

		// Move the iterator, to point to next
		// Trie Node
		itr = nextNode;

		// If its the last character of the string 's'
		// then mark 'isLast' as true
		if (i == len - 1){

			itr->isLast = true;
			if(toReverse==true)
			{
                		itr->toReverse = true;
			}
        	}

	}
}

// This function simply displays all dictionary words
// going through current node. String 'prefix'
// represents string corresponding to the path from
// root to curNode.
void displayContactsUtil(TrieNode *curNode, string prefix)
{
	// Check if the string 'prefix' ends at this Node
	// If yes then display the string found so far
	if (curNode->isLast){

        // case where last name also exits
        // if exists reverse both last and first name to get orignal order
	    if(curNode->toReverse)
	    {
	    int index;
	    index = prefix.find_last_of("_");
	    string first_name = prefix.substr(index+1);
	    string last_name=prefix.substr(0, index);
	    string last_first_name=first_name+" "+last_name;
	    cout <<last_first_name<<endl;
	    }
	   else{
	       transform(prefix.begin(), prefix.end(), prefix.begin(), [](char ch) {
	       return ch == '_' ? ' ' : ch;
	      });
	    cout << prefix << endl;
	}
    }

	// Find all the adjacent Nodes to the current
	// Node and then call the function recursively
	// This is similar to performing DFS on a graph
	for (int i = 65; i <= 122; i++)
	{
        char c=i;
		TrieNode *nextNode = curNode->child[c];
		if (nextNode != NULL)
			displayContactsUtil(nextNode, prefix + (char)c);

	}
}

// Display suggestions of the prefix entered by user
void displayContacts(string str)
{
	TrieNode *curNode = root;

	string prefix = "";
	int len = str.length();
   	bool nodeFound=true;

    	// Bring the node pointer to the last element
    	// of prefix if exists
	for (int i=0; i<len; i++)
	{
		// 'prefix' stores the string formed so far
		prefix += (char)str[i];

		// Get the last character entered
		char lastChar = prefix[i];

		// Find the Node corresponding to the last
		// character of 'prefix' which is pointed by
		// prevNode of the Trie
		curNode = curNode->child[lastChar];

		// If nothing found, then break the loop as
		// no more prefixes are going to be present.
		if (curNode == NULL)
		{
           		nodeFound=false;
			cout << "\n No Results Found for  " << str<<endl<<endl;
			break;
		}
    }

    // pass node pointer pointing to last char of prefix
    // performing dfs after that char for suggestions
    if(nodeFound){
        cout << "\nSuggestions based on input name -->  " << prefix<<endl;
        displayContactsUtil(curNode, prefix);
    }
}

// Driver program to test above functions
int main()
{

    cout<<endl<<":::::::::::: WELCOME TO CONTACT DIRECTORY :::::::::::::::::"<<endl;
    // to initialise root node for first insert
    bool flag=true;
    while(1)
    {
        cout<<endl<<" 1) Add contact 2) Search Contact 3) Exit "<<endl;
        int option;
        cin>>option;
        cout<<endl;
        cin.ignore();
        if(option==1)
        {
            if(flag)
            {
            root = new TrieNode();
            flag=false;
            }
            cout<<"ENTER NAME: ";

            cout << endl << "---> ";
            string full_name;
            // input name for insertion
            getline(cin, full_name);

            int index;
            index = full_name.find_last_of(" ");

            // check if name has spaces i.e last name also exists
            if(index!=-1){
                string last_name = full_name.substr(index+1);
                string first_name=full_name.substr(0, index);
                string last_first_name=last_name+"_"+first_name;

                // if last name also exits, passing lastname_firstname and toReverse as True
                insert(last_first_name,true);
            }

            // replacing spaces with underscore for simplicity
            transform(full_name.begin(), full_name.end(), full_name.begin(), [](char ch) {
                return ch == ' ' ? '_' : ch;
            });
            // passing full_name with toReverse as False
            insert(full_name,false);
        }
        else if(option==2)
        {
            //if searching inserted before atleast 1 insertion
            if(flag)
            {
                cout<<"Please Insert Name before Searching"<<endl;
            }
            else{
                string s;
                cout<<"Enter Name To Search: ";
                cout << endl << "---> ";
                getline(std::cin, s);
                displayContacts(s);
            }
        }
        else if (option==3){
             cout<<"::::::: Happy Searching :::::::::"<<endl;
            break;
        }
        else{
        cout<<":::::::::::: Invalid Input :::::::::::::::"<<endl<<endl;
        cout<<":::::::::::: Please Enter 1 or 2 or 3 ::::::::::::"<<endl;
        }
    }
	return 0;
}

