// Jacob Hohenstein
// Programming Assignment #3
// 03/25/2018

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

//binary search tree that holds account ID and the account record number
struct AccountTree			
{
	int acctID;
	long acctRecNum;
	AccountTree  * left;
	AccountTree  * right;
};

//structure for a new node in a binary search tree
struct AccountTree *newAccount(int id, long recNum)
{
	struct AccountTree  *temp = new AccountTree;
	temp->acctID = id;
	temp->acctRecNum = recNum;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}
//Declarations
void insert(AccountTree  *&, int, long);
long  AccountSearch(AccountTree  *, int);



//Functions

//function for entering a new account into the search tree
//Parameter: tree, account ID, record number
void insert(AccountTree  *&root, int ID, long recNum)
{
	if (root == NULL)
	{
		root = newAccount(ID, recNum);
	}
	else if (ID < root->acctID)
		insert(root->left, ID, recNum);
	else
		insert(root->right, ID, recNum);
}

//function for searching a binary search tree 
//Parameters: tree to be searched, account ID to search for
//Returns: Record Number 
long  AccountSearch(AccountTree  *account, int ID)
{
	if (account == NULL)
		return -1;
	if (account->acctID == ID)
		return account->acctRecNum;
	if (ID < account->acctID)
		return AccountSearch(account->left, ID);
	else
		return AccountSearch(account->right, ID);
}
int main()
{
	AccountTree  * tree = NULL;
	//information in accounts
	int AccountID;
	long recNum;
	string firstName, lastName;
	double balance;

	int userInput;
	long searchRecNum;
	ifstream myfile;

	myfile.open("accounts.dat");
	//gets the information from file and inserts the accountID and record number in the tree 
	while (!myfile.eof())
	{
		myfile >> recNum >> AccountID >> firstName >> lastName >> balance;
		insert(tree, AccountID, recNum);
	}
	myfile.close();
	//loops until the user inputs a -1 for the account ID
	while (true)
	{
		cout << "Enter account ID (or enter -1 to end searching): ";
		cin >> userInput;
		if (userInput == -1)
			break;
		//finds the record number for the searched account ID
		searchRecNum = AccountSearch(tree, userInput);
		cout << endl << "Matched record number is " << searchRecNum << endl << endl;
		cout << "Corresponding account record from the database file" << endl << endl;
		cout << setw(15) << "Record #" << setw(15) << "Account ID" << setw(15) << "First Name" << setw(15) << "Last Name" << setw(15) << "Balance" << endl;
		//if the Record number is -1
		if (searchRecNum == -1)
		{
			cout << setw(45) << "Account ID not in Data" << endl << endl;
		}
		else
		{
			myfile.open("accounts.dat");
			//loops until the account ID is found or reaches the end of the tree
			while (true)
			{
				//gets the record number, accountID, first name, last name, balance
				myfile >> recNum >> AccountID >> firstName >> lastName >> balance;
				//if the recordNum is in the tree
				if (recNum == searchRecNum)
				{
					cout << setw(15) << recNum << setw(15) << AccountID << setw(15) << firstName << setw(15) << lastName << setw(15) << balance << endl << endl;
					break;
				}
			}
			myfile.close();
		}
		cout << "----------------------------------------------------------------------------" << endl;
	}
	system("pause");
	return 0;
}