#include <bits/stdc++.h>
#define ll long long int
using namespace std;

// C++ program to implement Symbol Table
#include <iostream>
using namespace std;

const int MAX = 100;

class Node {

	string identifier, scope, type;
	Node* next;

public:
	Node()
	{
		next = NULL;
	}

	Node(string key, string value, string type)
	{
		this->identifier = key;
		this->scope = value;
		this->type = type;
		next = NULL;
	}

	void print()
	{
		cout << "Identifier's Name:" << identifier
			<< "\nType:" << type
			<< "\nScope: " << scope
			<< endl;
	}
	friend class SymbolTable;
};

class SymbolTable {
	
public:
	Node* head[MAX];

	SymbolTable()
	{
		for (int i = 0; i < MAX; i++)
			head[i] = NULL;
	}

	int hashf(string id); // hash function
	bool insert(string id, string scope,
				string Type);

	string find(string id);

	bool deleteRecord(string id);

	bool modify(string id, string scope,
				string Type, int lineno);

	void print()
	{
		Node * cur=head[0];
		
		while(cur!=NULL)
		{
			cur->print();
			cur=cur->next;
		}
	}
};

// Function to modify an identifier
bool SymbolTable::modify(string id, string s,
						string t, int l)
{
	int index = hashf(id);
	Node* start = head[index];

	if (start == NULL)
		return "-1";

	while (start != NULL) {
		if (start->identifier == id) {
			start->scope = s;
			start->type = t;
			return true;
		}
		start = start->next;
	}

	return false; // id not found
}

// Function to delete an identifier
bool SymbolTable::deleteRecord(string id)
{
	int index = hashf(id);
	Node* tmp = head[index];
	Node* par = head[index];

	// no identifier is present at that index
	if (tmp == NULL) {
		return false;
	}
	// only one identifier is present
	if (tmp->identifier == id && tmp->next == NULL) {
		tmp->next = NULL;
		delete tmp;
		return true;
	}

	while (tmp->identifier != id && tmp->next != NULL) {
		par = tmp;
		tmp = tmp->next;
	}
	if (tmp->identifier == id && tmp->next != NULL) {
		par->next = tmp->next;
		tmp->next = NULL;
		delete tmp;
		return true;
	}

	// delete at the end
	else {
		par->next = NULL;
		tmp->next = NULL;
		delete tmp;
		return true;
	}
	return false;
}

// Function to find an identifier
string SymbolTable::find(string id)
{
	int index = hashf(id);
	Node* start = head[index];

	if (start == NULL)
		return "-1";

	while (start != NULL) {

		if (start->identifier == id) {
			start->print();
			return start->scope;
		}

		start = start->next;
	}

	return "-1"; // not found
}

// Function to insert an identifier
bool SymbolTable::insert(string id, string scope,
						string Type)
{
	int index = hashf(id);
	Node* p = new Node(id, scope, Type);

	if (head[index] == NULL) {
		head[index] = p;
		cout << "\n"
			<< id << " inserted";

		return true;
	}

	else {
		Node* start = head[index];
		while (start->next != NULL)
			start = start->next;

		start->next = p;
		cout << "\n"
			<< id << " inserted";

		return true;
	}

	return false;
}

int SymbolTable::hashf(string id)
{
	int asciiSum = 0;

	for (int i = 0; i < id.length(); i++) {
		asciiSum = asciiSum + id[i];
	}

	return (asciiSum % 100);
}

// Driver code
int main()
{
	SymbolTable st;
	fstream file;
    string word, t, q, filename;
	
    filename = "code.txt";
    file.open(filename.c_str());
	int scope=0;
	bool storeVar=false;
	string type="-";
    while (file >> word)
    {
        if(word=="int")
		{
			storeVar=true;
			type="int";
		}
		else if(word=="string")
		{
			storeVar=true;
			type="string";
		}
		else if(storeVar)
		{
			st.insert(word, scope>0 ? "Local" : "Global", type);
			type="-";
			storeVar=false;
		}
		else if(word=="{")
		{
			scope++;
		}
		else if(word=="{")
		{
			scope--;
		}
    }
	st.print();

	return 0;
}
