#include "recipe.h"
#include <ctime>
#include <chrono>
using namespace std;
vector<string> Union(vector<string> v1, vector<string> v2) {
	vector<string> result;
	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());
	set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(result));
	return result;
}
vector<string> Intersection(vector<string> v1, vector<string> v2) {
	vector<string> result;
	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());
	set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(result));
	return result;
}
vector<string> difference(vector<string> v1, vector<string> v2) {
	vector<string> result;
	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());
	set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(result));
	return result;
}
class userInterface
{
private:
	recipeManu menu;
	vector<string> favorIngredients;
	vector<vector<string>> dishVec;
	int choice;
public:
	userInterface()
	{
		cout << "-----------------------------------------------------" << endl;
		cout << "Welcome to the final project of Group 62 for COP3530!" << endl;
		cout << "     The databse includes over 2,000,000 recipes!    " << endl;
		cout << "Please select data structure for implementation: " << endl;
		cout << "1. Binary Search Tree" << endl;
		cout << "2. Sets made by hash table" << endl;
		cin >> this->choice;
		if (!userSelect(choice))
		{
			userInterface();
		};
	}
	bool userSelect(int choice)
	{
		if (choice == 1)
		{
			cout << "Please input the size of database you want to check" << endl;
			int size;
			cin >> size;
			menu.buildRecipeManu(size);
			clock_t start = clock();
			menu.buildBstIngredMap();
			clock_t end = clock();
			cout << "The time consume for insertion BST database is " << (double)(end - start) / CLOCKS_PER_SEC << " seconds" << endl;
			searchMenu(menu);
			return true;
		}
		else if (choice == 2)
		{
			cout << "Please input the size of database you want to check" << endl;
			int size;
			cin >> size;
			menu.buildRecipeManu(size);
			clock_t start = clock();
			menu.buildIngredMap();
			clock_t end = clock();
			cout << "The time consume for insertion hash table set database is " << (double)(end - start) / CLOCKS_PER_SEC << " seconds" << endl;
			searchMenu(menu);
			return true;
		}
		else if (choice == 0)
		{
			return true;
		}
		else
		{
			cout << "Invalid input, please retype 1 or 2" << endl;
			return false;
		}
	}
	void searchMenu(recipeManu inserted)
	{
		cout << "Please list the name of ingredients you want to search: " << endl;
		string input;
		cin >> input;
		if (this->choice == 1)
		{
			auto start = std::chrono::high_resolution_clock::now();
			Node* temp = menu.search(menu.getRoot(), input);
			auto elapsed = std::chrono::high_resolution_clock::now() - start;
			long long microseconds = chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
			cout << "The time consume for searching " << input << " in BST database is " << microseconds << " microseconds" << endl;
			
			if (temp != NULL)
			{
				favorIngredients.push_back(input);
				vector<string> curVec = temp->dish;
				dishVec.push_back(curVec);
				cout << "There are " << curVec.size() << " items found, do you want to see the result? 1.Yes 2. No" << endl;
				int c;
				cin >> c;
				if (c == 1) 
				{
				cout << "There are " << curVec.size() << " that can made by " << input << endl;
				for (int i = 0; i < curVec.size(); i++)
				{
					cout << curVec[i] << ", ";
				}
				cout << endl;
				}
			}
		}
		if (this->choice == 2)
		{
			unordered_map<string, vector<string>> cur = menu.getIngredMap();
			auto start = std::chrono::high_resolution_clock::now();
			auto itr = cur.find(input);
			auto elapsed = std::chrono::high_resolution_clock::now() - start;
			long long microseconds = chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
			if (itr == cur.end())
			{
				cout << "Does not exist" << endl;
			}
			cout << "The time consume for searching " << input << " in hash map database is " << microseconds << " microseconds" << endl;
			if (itr != cur.end())
			{
				favorIngredients.push_back(input);
				vector<string> curVec = itr->second;
				dishVec.push_back(curVec);
				cout << "There are " << curVec.size() << " items found, do you want to see the result? 1.Yes 2. No" << endl;
				int c;
				cin >> c;
				if (c == 1)
				{
					for (int i = 0; i < curVec.size(); i++)
					{
						cout << curVec[i] << ", ";
					}
					cout << endl;
				}
			}
		}
		cout << "1. Create a new database" << endl;
		cout << "2. Searching a new item" << endl;
		cout << "3. Show all the dishes I can make" << endl;
		cout << "4. Show all the dishes that used all ingredients" << endl;
		cout << "0. Exist" << endl;
		int newChoice;
		cin >> newChoice;
		if (newChoice == 1)
		{
			userInterface();
		}
		else if (newChoice == 2)
		{
			searchMenu(menu);
		}
		else if (newChoice == 3||newChoice == 4)
		{
			setMani(newChoice);
		}
		else if (newChoice == 0)
		{
			return;
		}
	}
	void setMani(int choice)
	{
		if (choice == 3)
		{
			int x = dishVec.size();
			int y = 0;
			for (int i = 0; i < x; i++)
			{
				y += dishVec[i].size();
			}
			cout << "There are " << y << " dishes you can make" << endl;
			for (int i = 0; i < x; i++)
			{
				vector<string> temp = dishVec[i];
				for (int j = 0; j < temp.size(); j++)
				{
					cout << temp[j] << ", ";
				}
			}
			cout << endl;
		}
		else if (choice == 4)
		{
			cout << "195" << endl;
			vector<string> result = dishVec[0];
			if (dishVec.size() == 1)
			{
				cout << "There are " << dishVec[0].size() << " dishes you can make" << endl;
				for (int i = 0; i < dishVec[0].size(); i++)
				{
					cout << dishVec[0][i] << ", ";
				}
				cout << endl;
			}
			for (int i = 1; i < dishVec.size(); i++)
			{
				result = Intersection(result, dishVec[1]);
			}
			cout << "There are " << result.size() << " dishes you can make" << endl;
			for (int i = 0; i < result.size(); i++)
			{
				cout << result[i];
				if (i != result.size() - 1)
				{
					cout << ", ";
				}
			}
			cout << endl;
		}
		cout << "1. Create a new database" << endl;
		cout << "2. Searching a new item" << endl;
		cout << "3. Show all the dishes I can make" << endl;
		cout << "4. Show all the dishes that used all ingredients" << endl;
		cout << "0. Exist" << endl;
		int newChoice;
		cin >> newChoice;
		if (newChoice == 1)
		{
			userInterface();
		}
		else if (newChoice == 2)
		{
			searchMenu(menu);
		}
		else if (newChoice == 3 || newChoice == 4)
		{
			setMani(newChoice);
		}
		else if (newChoice == 0)
		{
			return;
		}
	}
};
void main()
{
	userInterface();
}