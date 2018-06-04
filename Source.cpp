#include <fstream>
#include <iostream>
#include <string>
#include <vector>
//#include "ArgumentManager.h"

using namespace std;

struct Node {
	int value;
	Node* next;
	Node *prev;
};

class LinkedList {
private:
	Node *head;
	Node *tail;
	int size;
	int remainder;
	bool positive;
	int digits;
public:
	LinkedList() {																						
		head = tail = NULL;
		size = 0;
		remainder = 0;
		positive = true;
	}

	LinkedList(string num, int digitsPerNode) {															
		digits = digitsPerNode;
		string temp = num;
		if (temp[0] == '-') {
			temp = temp.substr(1, temp.length());
			positive = false;
		}
		else {
			positive = true;
		}
		remainder = temp.length() % digitsPerNode;
		size = (temp.length() / digitsPerNode) + remainder;
		if (remainder == 0) {
			for (int i = 0; i < temp.length(); i += digitsPerNode) {
				add(stoi(temp.substr(i, digitsPerNode)));
			}
		}
		else {
			add(stoi(temp.substr(0, remainder)));
			for (int i = remainder; i < temp.length(); i += digitsPerNode) {
				add(stoi(temp.substr(i, digitsPerNode)));
			}
		}

	}

	~LinkedList() {																						

	}

	void print() {
		string zeros = "";
		for (int x = 0; x < digits; x++) {
			zeros += "0";
		}
		if (isPositive() == false) {
			cout << "-";
		}
		Node* curr = head;
		cout << head->value;
		while (curr->next) {
			curr = curr->next;
			if (curr->value == 0) {
				cout << zeros;
			}
			else {
				cout << curr->value;
			}
		}
	}

	int getSize() {																						
		return size;
	}

	bool isPositive() {																					
		return positive;
	}

	bool operator<(LinkedList a) {															

		Node* temp1 = head;
		Node* temp2 = a.head;
		if (isPositive() == false && a.isPositive() == true) {
			return true;
		}
		if (isPositive() == false && a.isPositive() == false) {
			if (getSize() > a.getSize()) {
				return true;
			}
			else if (getSize() < a.getSize()) {
				return false;
			}
			else if (getSize() == a.getSize()) {
				while (temp1) {
					if (temp1->value > temp2->value) {
						return true;
					}
					else if (temp1->value < temp2->value) {
						return false;
					}
					else if (temp1->value == temp2->value) {
						temp1 = temp1->next;
						temp2 = temp2->next;
					}
				}
			}
		}
		if (a.isPositive() && a.isPositive()) {
			if (getSize() < a.getSize()) {
				return true;
			}
			else if (getSize() > a.getSize()) {
				return false;
			}
			else if (getSize() == a.getSize()) {
				while (temp1) {
					if (temp1->value < temp2->value) {
						return true;
					}
					else if (temp1->value > temp2->value) {
						return false;
					}
					else if (temp1->value == temp2->value) {
						temp1 = temp1->next;
						temp2 = temp2->next;
					}
				}

			}
		}
		return false;
	}

	void add(int val) {																					
		Node *temp = new Node();
		temp->value = val;
		temp->next = NULL;
		temp->prev = NULL;
		if (!(head)) {
			head = tail = temp;
		}
		else {
			tail->next = temp;
			temp->prev = tail;
			tail = temp;
		}
	}
};

static vector<LinkedList> swap(vector<LinkedList>& arr, int& index1, int& index2) {													
	vector<LinkedList> newList = arr;
	LinkedList temp = arr[index1];
	arr[index1] = arr[index2];
	arr[index2] = temp;
	return arr;
}

static vector<LinkedList> selectionSort(vector<LinkedList>& a) {
	int nums = a.size();
	int comps = 0;
	int swaps = 0;
	int Ocomps = nums*(nums - 1) / 2;
	int Oswaps = 0;
	LinkedList min;
	LinkedList temp;
	int indexOfMin = 0;
	bool newMin = false;
	for (int i = 0; i < a.size(); i++) {
		min = a[i];
		indexOfMin = i;
		newMin = false;
		for (int j = i + 1; j < a.size(); j++) {
			comps++;
			if (a[j] < min) {
				min = a[j];
				newMin = true;
				indexOfMin = j;
			}
		}
		if (newMin) {
			swap(a, indexOfMin, i);
			swaps++;
		}
	}
	ofstream foo("bigO.txt", ios_base::app);
	foo << "select\t" << nums << "\t" << comps << "\t" << swaps << "\t" << Ocomps << "\t" << Oswaps << endl;
	return a;
}

static vector<LinkedList> merge(vector<LinkedList>& a, vector<LinkedList>& b) {
	vector<LinkedList> c;
	int nums = a.size();
	int comps = 0;
	int swaps = 0;
	int Ocomps = nums*(nums - 1) / 2;
	int Oswaps = 0;
	while (a.size() > 0 && b.size() > 0) {
		comps++;
		if (a[0] < b[0]) {
			c.push_back(a[0]);
			a.erase(a.begin());

		}
		else {
			c.push_back(b[0]);
			b.erase(b.begin());

		}
	}
	while (a.size() > 0) {
		c.push_back(a[0]);
		a.erase(a.begin());
	}
	while (b.size() > 0) {
		c.push_back(b[0]);
		b.erase(b.begin());
		swaps++;
	}
	ofstream foo("bigO.txt", ios_base::app);
	foo << "merge\t" << 2 * nums << "\t" << comps << "\t" << swaps << "\t" << Ocomps << "\t" << Oswaps << endl;
	return c;
}

static vector<LinkedList> mergeSort(vector<LinkedList>& a) {
	vector<LinkedList> l1;
	vector<LinkedList> l2;

	if (a.size() == 1) {
		return a;
	}
	else {
		for (int i = 0; i < a.size() / 2; i++) {
			l1.push_back(a[i]);
		}
		for (int i = a.size() / 2; i < a.size(); i++) {
			l2.push_back(a[i]);
		}

		l1 = mergeSort(l1);
		l2 = mergeSort(l2);
	}

	return merge(l1, l2);
}

static vector<LinkedList> insertionSort(vector<LinkedList>& a) {
	int nums = a.size();
	int comps = 0;
	int swaps = 0;
	int Ocomps = nums*(nums - 1) / 2 + nums;
	int Oswaps = 0;
	int holePosition;
	LinkedList valueToInsert;
	int curr;
	if (a.size() == 1) {
		return a;
	}
	else {
		for (int i = 1; i < a.size(); i++) {
			swaps++;
			valueToInsert = a[i];
			holePosition = i;
			while (holePosition > 0 && valueToInsert < a[holePosition - 1]) {
				comps++;
				a[holePosition] = a[holePosition - 1];
				holePosition = holePosition - 1;
			}
			a[holePosition] = valueToInsert;
		}
	}
	ofstream foo("bigO.txt", ios_base::app);
	foo << "insert\t" << nums << "\t" << comps << "\t" << swaps << "\t" << Ocomps << "\t" << Oswaps << endl;
	return a;
}

static int partition(vector<LinkedList>& a, int left, int right, LinkedList pivot, int& comps, int& swaps) {
	for (int i = left; i <= right; ++i) {
		comps++;
		if (a[i] < pivot) {
			swap(a[i], a[left]);
			swaps++;
			left++;
		}
	}
	return left - 1;
}

static vector<LinkedList> quickSort(vector<LinkedList>& a, int left, int right) {
	vector<LinkedList> b; vector<LinkedList> c;
	int nums = a.size();
	int comps = 0;
	int swaps = 0;
	int Ocomps = nums*(nums - 1) / 2 + nums;
	int Oswaps = nums*(nums - 1) / 2 + nums;
	bool cd = true;
	if (left >= right) return a;

	int middle = left + (right - left) / 2;
	swap(a[middle], a[left]);
	int midpoint = partition(a, left + 1, right, a[left], comps, swaps);
	swap(a[left], a[midpoint]);
	quickSort(a, left, midpoint);
	quickSort(a, midpoint + 1, right);

	ofstream foo("bigO.txt", ios_base::app);
	foo << "quick\t" << nums << "\t" << comps << "\t" << swaps << "\t" << Ocomps << "\t" << Oswaps << endl;


	return a;
}

static void min_heapify(vector<LinkedList>& a, int i, int& comps, int& swaps) {
	comps++;
	int min = i;
	int left = min + 1;
	int right = min + 2;
	if (right < a.size() && a[right] < a[min]) {
		swap(a, right, left);
		swaps++;
	}
	if (left < a.size() && a[left] < a[min]) {
		swap(a, left, min);
		swaps++;
	}
	if (min != i) {
		min_heapify(a, min - 1, comps, swaps);
	}
}

static vector<LinkedList> heapSort(vector<LinkedList>& a) {
	int nums = a.size();
	int comps = 0;
	int swaps = 0;
	int Ocomps = nums*(nums - 1) / 2;
	int Oswaps = 0;
	for (int i = 0; i < a.size(); i++) {
		min_heapify(a, i, comps, swaps);
	}
	ofstream foo("bigO.txt", ios_base::app);
	foo << "heap\t" << nums << "\t" << comps << "\t" << swaps << "\t" << Ocomps << "\t" << Oswaps << endl;
	return a;
}

int main(int argc, char* argv[])
{
	std::ofstream outfile("bigO.txt");
	outfile.open("bigO.txt");
	outfile << "algorithm\t" << "#numbers(n)\t" << "#Comparisons\t" << "#Swaps\t" << "#bigOComparisons\t" << "#bigOSwaps" << endl;

	/***************************************
		Change to test LinkedList sort methods
	*****************************************/
	string algorithm = "insert";	


	int digitsPerNode = 3;
	LinkedList a("36753562912709360626", digitsPerNode);
	vector<LinkedList> nums;
	nums.push_back(a);
	LinkedList b("18792023759228973612", digitsPerNode);
	nums.push_back(b);
	LinkedList c("93194784503610632061", digitsPerNode);
	nums.push_back(c);
	LinkedList d("55476569374525474430", digitsPerNode);
	nums.push_back(d);
	LinkedList e("78688431492068926649", digitsPerNode);
	nums.push_back(e);
	LinkedList f("50487172722610615949", digitsPerNode);
	nums.push_back(f);
	LinkedList g("19177115977673656394", digitsPerNode);
	nums.push_back(g);
	LinkedList h("81293908850963856115", digitsPerNode);
	nums.push_back(h);
	LinkedList i("98481030444476317596", digitsPerNode);
	nums.push_back(i);
	LinkedList j("21785741859753883189", digitsPerNode);
	nums.push_back(j);

	if (algorithm == "heap") {
		nums = heapSort(nums);
		for (int i = 0; i < nums.size(); i++) {
			nums[i].print();
			cout << endl;
		}
	}
	else if (algorithm == "quick") {
		quickSort(nums, 0, nums.size() - 1);
		for (int i = 0; i < nums.size(); i++) {
			nums[i].print();
			cout << endl;
		}
	}
	else if (algorithm == "select") {
		selectionSort(nums);
		for (int i = 0; i < nums.size(); i++) {
			nums[i].print();
			cout << endl;
		}
	}
	else if (algorithm == "insert") {
		insertionSort(nums);
		for (int i = 0; i < nums.size(); i++) {
			nums[i].print();
			cout << endl;
		}
	}
	else if (algorithm == "merge") {
		nums = mergeSort(nums);
		for (int i = 0; i < nums.size(); i++) {
			nums[i].print();
			cout << endl;
		}
	}
	system("pause");
	return 0;
}

