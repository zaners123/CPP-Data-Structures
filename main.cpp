#include <iostream>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>
#include <fstream>

#include <structures.h>

using namespace std;

void flip(string &s) {

	/*string res;
	for (int i = s.size()-1; i >= 0; --i) {
		res+=s.at(i);
	}
	return res;*/

}


template <class T> void flip(T arr[], size_t length) {
	for (size_t i = 0; i < length/2; i++) {
		T temp = arr[i];
		arr[i] = arr[length-i-1];
		arr[length-i-1] = temp;
	}
	string x = "hey";
	x.at(0);
}

//main ways to test or use lists
void fiddleWithLinked() {
	LinkedList<string>list{};
	list.put("apple");
	list.put("banana");
	list.put("cherry");
	list.print();

	cout<<list[0];

	list.remove("banana");
	list.print();
	list.remove("apple");
	list.remove("cherry");
	list.print();
}
/**Just messes with the linked list to see if it works
 * */
void fiddleWithDLL() {
	auto* firstNode = new DoublyLinkedNode<string>(nullptr, nullptr,"Welcome to my Linked List");
	cout<<"First Node "<<*firstNode<<'\n';
	auto list = DoublyLinkedList<string>(firstNode);
	list.insertNodeAfter(*list.first, "Middle of the LIST");
	list.insertNodeAfter(*list.last, "End of data, here we go");
	//list.print();
	auto thfi = list.insertNodeAfter(*list.last, "next");
	list.insertNodeAfter(*list.last, "goin");
	list.insertNodeAfter(*list.last, "far");
	list.insertNodeBefore(*list.first, "makin it");
	list.insertNodeBefore(*list.first, "goes");
	list.insertNodeBefore(*list.last, "go");
	auto* fifteen = list.insertNodeBefore(*list.last, "fly");
	auto* oneohone = list.insertNodeAfter(*list.last, "zoom");
	list.insertNodeAfter(*list.first, "woosh");
	list.insertNodeAfter(*oneohone, "fly");
	list.insertNodeBefore(*list.first, "speed");
	list.removeNode(*list.first);//remove speed
	list.removeNode(*list.first);
	list.removeNode(*fifteen);
	list.removeNode(*list.first);
	list.insertNodeAfter(*list.first, "second");

	//testing MAKE THE LAST ELEMENT LINK TO THE FIRST UH OH (creates recursive loop of links
	//list.last->next = list.root;

	list.printArr();
}
/**Messes with the Circular Linked List class
 * */
void fiddleWithCLL() {
	auto intCLL = CircularLinkedList<int>();
	intCLL.insertNode(15);
	intCLL.insertNode(20);
	intCLL.insertNode(20);
	intCLL.insertNode(25);
	intCLL.insertNode(30);
	intCLL.printArr();

	auto stringCLL = CircularLinkedList<string>();
	stringCLL.insertNode("Apple");
	stringCLL.insertNode("Banana");
	auto cake = stringCLL.insertNode("Cake");
	stringCLL.insertNode("Dragon");
	stringCLL.insertNode("Egg");
	stringCLL.insertNode("Frame");
	stringCLL.insertNode("Goat");
	stringCLL.insertNode("Hat");
	stringCLL.insertNode("Igloo");
	stringCLL.insertNode("Juice");
	stringCLL.removeNode(cake);
	stringCLL.printArr();
	//remove way more nodes than exist
	/*for (int i = 0; i < 15; ++i) {
		stringCLL.removeNextNode();
	}*/
	stringCLL.printArr();

	cout << stringCLL.getNext()->val << '\n';
	cout << stringCLL.getNext()->val << '\n';
	cout << stringCLL.getNext()->val << '\n';
}
/**Mess around with the Dynamic Stack class
 * */
void fiddleWithDS() {
	auto stack = StackLIFO<string>();
	stack.push("In the Stack");
	stack.push("Up the Stack");
	stack.push("Far up the Stack");
	stack.push("Top'a da stack");
	while (!stack.isEmpty()) {
		cout << "Whats Poppin: " << stack.pop() << '\n';
	}
	stack.push("newly added");
	cout << "Peekin: " << stack.peek() << '\n';
	cout << "Empty? " << (stack.isEmpty() ? "Yes" : "No") << '\n';
}
/**Visual stack editor
 * */
void stackUI() {

	//choice constants
	const int CHOICE_EXIT = 0;
	const int CHOICE_PUSH = 1;
	const int CHOICE_POP = 2;
	const int CHOICE_PEEK = 3;

	auto stack = StackLIFO<string>();

	//TODO maybe
	//StackLIFO<string> stack;

	while (true) {
		cout << "What do you want to do?\n";
		cout << CHOICE_EXIT << ". Exit\n";
		cout << CHOICE_PUSH << ". Push to the stack\n";
		cout << CHOICE_POP << ". Pop off the stack\n";
		cout << CHOICE_PEEK << ". Peek at the stack\n";
		int choice;
		cin >> choice;
		if (choice == CHOICE_EXIT) break;
		string in;
		switch (choice) {
			case CHOICE_PUSH:
				//this is in a block because you can't define variables in a switch, unless it has limited scope.
				cout << "What do you want to push?\n";

				//set variable "in" with spaces allowed
				char input[100];
				cin.getline(input, sizeof(input));
				in = input;

				cout << "Pushing \"" << in << "\" to the stack";
				stack.push(in);
				continue;
			case CHOICE_POP:
				cout << "Popping Stack\n";
				if (stack.isEmpty()) {
					cout << "Empty stack" << '\n';
				} else {
					cout<<stack.pop()<<'\n';
				}
				continue;
			case CHOICE_PEEK:
				cout << "Peeking Stack\n";
				if (stack.isEmpty()) {
					cout << "Empty stack" << '\n';
				} else {
					cout<<stack.peek()<<'\n';
				}
				continue;
			default:
				break;
		}
	}
}
long long factorial(long long i) {
	if (i<=1) return 1;
	return factorial(i-1)*i;
}
void fiddleWithBinaryTree() {
	BinaryTree<int> intTree;
	intTree.put(0);
	for(int i=0;i<5;i++) {
		intTree.put(i);
		intTree.put(-i);
	}
	intTree.put(6);
	intTree.put(8);
	intTree.put(3);
	intTree.put(4);
	intTree.put(2);
	intTree.put(1);
	intTree.put(5);
	intTree.put(12);
	intTree.put(9);
	intTree.put(10);
	cout<<"BEFORE REMOVING 3\n";
	intTree.print();
	intTree.remove(3);
	cout<<"AFTER REMOVING 3\n";
	intTree.print();
	/*tree.insertNode("root");
	for (char i = 'a'; i <= 'z'; ++i) {
		string s(&i);
		tree.put(s);
	}*/
	cout<<"PRE ORDER\n";
	intTree.preOrder();
	cout<<"IN ORDER\n";
	intTree.inOrder();
	cout<<"POST ORDER\n";
	intTree.postOrder();

	cout<<"Contains 2? "<<(intTree.containsKey(2)?"YES\n":"NO\n");
	cout<<"Contains -3? "<<(intTree.containsKey(3)?"YES\n":"NO\n");
	cout<<"Contains 5? "<<(intTree.containsKey(5)?"YES\n":"NO\n");
}
void fiddleWithBinaryTreeMap() {
	BinaryTreeMap<int,string> map;
	map.put(6,"Fruit");
	map.put(8,"Hats");
	map.put(3,"Crayon?");
	map.put(4,"Dragon");
	map.put(5,"Eggplant");
	map.put(12,"Lemon");
	map.put(9,"Igloo");
	map.put(10,"JackRabbit");
	map.put(1,"apple");
	map.put(15,"Orange");
//	map.print();
	map.inOrder();
	cout<<"Tree's value at 5: "<<*map.get(5)<<'\n';
	cout<<"Tree's length: "<<map.getLength()<<'\n';
	map.sortTree();
}
void atbash(string &s) {
	for (char &i : s) {
		if (isupper(i)) {
			i = 'Z'- i+'A';
		} else if (islower(i)) {
			i = 'z'- i+'a';
		}
	}
}
void fileParse() {
	ifstream fileStream("/home/zaners123/Desktop/trump.txt");
	string line;
	while (getline(fileStream,line)) {
		atbash(line);
		cout<<""<<line<<'\n';
	}

	string msg = "abcABC123";
	cout<<"input "<<msg<<'\n';
	atbash(msg);
	cout<<"output "<<msg<<'\n';
	int arr[] = {1,2,3,4,5};
	flip(arr, 5);

	string b = "Bees are sharp";
	flip(b);
	cout<<"flip: "<<b<<'\n';
}

class Color {
	unsigned char r;
	unsigned char g;
	unsigned char b;
public:
	Color(unsigned char r, unsigned char g, unsigned char b) {
		this->r = r;
		this->g = g;
		this->b = b;
	}
};
class Animal {
protected:
	int coolness = 0;
	int legs = 0;
	Color eyeColor = Color(0,0,0);
public:
	//for overloading operators, override == and <. Then base the rest off of those two
	bool operator==(const Animal& other) const { return other.coolness == coolness; }
	bool operator<(const Animal& other) const { return coolness < other.coolness; }
	//base off others for simplicity and to not repeat the same data
	bool operator!=(const Animal& other) const { return !(*this == other); }
	bool operator>(const Animal& other) const { return !((*this == other) || (*this < other)); }
	bool operator>=(const Animal& other) const { return !(*this < other); }

	//needs to be over written when it is equal to zero
	virtual string getSound() const = 0;
};
class Dog : public Animal {
public:
	virtual string getSound() const override {
		string sound;
		int legI = legs;
		while (legI-- > 0) {
			sound+=" *step* ";
		}
		sound+="BARK";
		return sound;
	}
	Dog() : Animal() {
		//dogs are cool and have 4 legs
		coolness += 10;
		legs = 4;
		eyeColor = Color(200,128,0);
	}
};
/**main as of your first StackOverflow question:
 * you have to use VV public there because then it will, by default, privately inheret things. Now it goes in protected.*/
class BigDog : public Dog {
public:
	//use the initializer of dog (implied i guess)
	/*BigDog() : Dog() {}*/
	BigDog() : Dog() {
		//big dogs are very cool
		coolness+=5;
	}
	virtual string getSound() const override {
		string sound;
		int legI = legs;
		while (legI-- > 0) {
			sound+=" *step* ";
		}
		sound+="BOOF BOOF";
		return sound;
	}
};
/**A subclass of Dog. Well known for being quieter.*/
class SmallDog : public Dog {
public:
	SmallDog() : Dog() {

	}
	virtual string getSound() {
//		string sound = Dog::getSound();
		string sound;
		for (int i=0;i<legs;i++) {
			sound+="tap ";
		}
		sound+="Yip";
		return sound;
	}
};
struct Student {
	string name;
	int score = 0;
public:
	bool operator<(const Student& other) const {
		return score < other.score;
	}
	bool operator>(const Student& other) const {
		return score > other.score;
	}
};
template <class T> void mySwap(T &a, T &b) {
	T temp = move(a);
	a = move(b);
	b = move(temp);
}
class NegativeException : public::exception {
	string err;
public:
	explicit NegativeException(string err) {
		this->err = err;
	}
	const char* what() const noexcept override {
		return err.c_str();
	}
};
class Minutes {
	int minutes;
public:
	explicit Minutes(int minutes = 0) {
		if (minutes < 0) {
			throw NegativeException("Minutes can't be negative");
		}
		this->minutes = minutes;
	}
	//friends get access to private/protected variables
	//friend Minutes operator+(const Minutes& a, int minutes);
	Minutes operator+(const int& a) const {
		return Minutes(minutes + a);
	}
	//make it negative
	Minutes operator-() {
		return Minutes(-minutes);
	}

	//move assignment, give ownership to parameter and return *this. The noexcept means it won't throw errors
	/*Minutes& operator=(Minutes&& moveTo) noexcept {
		//if moving to itself or something?
		if (&moveTo == this) return *this;

		minutes = moveTo.minutes;
		//moveTo.minutes = nullptr;
		return *this;
	}*/

	/*void operator+=(int time) {
		minutes += time;
	}*/
	friend void printMinutes(Minutes m);
};
/*Minutes operator+(const Minutes& a, int minutes) {
	return Minutes(a.minutes+minutes);
}*/
//printMinutes is a friend of Minutes, so it can access private
void printMinutes(Minutes m) {
	cout<<"This is "<<m.minutes<<" minutes, accessed by a friend\n";
}

void fiddleClassy() {
	Minutes m(15);

	m = m + 40;

	printMinutes(m);

	SmallDog smallDog;
	cout<< smallDog.getSound()<<'\n';

	cout<< Dog().getSound()<<'\n';

	BigDog bigDog;
	cout<<bigDog.getSound()<<'\n';

	if (bigDog==smallDog) {
		cout << "Big dog is EQUAL TOSmallDog\n";
	} else if (bigDog < smallDog) {
		cout << "Big dog is LESS THAN SmallDog\n";
	} else {
		cout << "Big dog is GREATER THAN SmallDog\n";
	}

	Dog& dog = bigDog;
	cout<<"The dog of bigDog: "<<dog.getSound()<<'\n';
}
void builtIn() {
	//main built in std::array<type, len>. Advantage is it can give you the length
	std::array<int, 10> ints = {51, 12, 13,-15,24,24626,-1000};//rest of array given zeroes
	cout << "ints length is " << ints.size() << '\n';
	for (size_t i{0}; i < ints.size(); ++i) {
		cout << "ints[" << i << "] equals " << ints[i] << " equals " << ints.at(i) << '\n';
	}
	cout<<"Sort ints\n";
	//sort std::array
	std::sort(ints.begin(), ints.end());
	for (size_t i{0}; i < ints.size(); ++i) {
		cout << "ints[" << i << "] equals " << ints[i] << " equals " << ints.at(i) << '\n';
	}
	cout<<"\nUsing std::vector\n";
	//main built in vector is dynamically sized
	std::vector<int> vector = {1,2,3};
	vector.resize(5);
	vector.resize(7);
	vector.at(3) = 3;
	for (size_t i{0}; i < vector.size();++i) {
		cout<<"Vector ["<<i<<"] is "<<vector[i]<<'\n';
	}
	//main std::list
	list<pair<int,string>> list;
	list.emplace_back(5,"y");
	list.emplace_back(4,"d");
	for (auto x = list.begin(); x != list.end(); ++x) {
		std::cout << (*x).first<<" -> "<<(*x).second<<'\n';
	}
	for (auto x : list) {
		std::cout << (x).first<<" -> "<<(x).second<<'\n';
	}
	//main other
	string s = "Hey wassup";
	const char* cstr = s.c_str();
	while (*cstr != '\0') {
		cout<<*cstr;
		cstr++;
	}
	int x=5;
	int y=3;
	cout<<'('<<x<<','<<y<<")\n";
	mySwap(x, y);
	cout<<'('<<x<<','<<y<<")\n";
	auto numS = 0;
	cout<<"Number of students:";
	cin >> numS;
	std::vector<Student> students;
	students.resize(numS);
	for (auto i = 0; i < numS; ++i) {
		students[i] = Student();
		cout<<"Name: ";
		cin >> students[i].name;
		cout<<"Score: ";
		cin >> students[i].score;
	}
	std::sort(students.rbegin(),students.rend());
	for(auto s : students) {
		cout<<s.name<< " grade "<<s.score<<'\n';
	}
}

template <class T> bool ascending(T a, T b) {
	return a < b;
}
template <class T> bool descending(T a, T b) {
	return a > b;
}
//main function pointers
template <class T> void selectionSort(T arr[], int size, bool (*comparator)(T,T) = ascending) {
	for (int i = 0; i < size; ++i) {
		int swapIndex = i;
		//if any other elements are smaller, set smallest
		for (int j = i+1; j < size; ++j) {
			/*if (arr[j] < arr[i]) {
				smallest = j;
			}*/
			if (comparator(arr[j],arr[i])) {
				swapIndex = j;
			}
		}
		mySwap(arr[i], arr[swapIndex]);
	}
}
void bees(int i){
	cout<<"There are "<<i<<" Bees\n";
}
void funcPointer() {
	void (*beesP)(int) = bees;
	bees(2);
	beesP(3);

	string bugs[] = {"Bee","Ladybug","Butterfly","Wasp","Spider","Arachnid"};
	cout<<"Inside funcPointer\n";
	cout<<"Ascending Bugs:\n";
	//ascending implied
	selectionSort(bugs,6);
	for (const auto &bug : bugs) { cout<< bug <<'\n'; }
	cout<<"Decending Bugs:\n";
	selectionSort(bugs,6, descending);
	for (const auto &bug : bugs) { cout<< bug <<'\n'; }

}

class Timer {
	using clock = std::chrono::high_resolution_clock;
	std::chrono::time_point<clock> start;
public:
	Timer() : start(clock::now()) {}
	double getElapsed() const {
		return chrono::duration_cast<chrono::duration<double,ratio<1>>>(clock::now() - start).count();
	}
	~Timer() {
		cout<<"Time: "<<getElapsed()<<"s";
	}
};

const string ones[] = {"One","Two","Three","Four","Five","Six","Seven","Eight","Nine"};
const string teens[] = {"Eleven","Twelve","Thirteen","Fourteen","Fifteen","Sixteen","Seventeen","Eighteen","Nineteen"};
const string tens[] = {"Ten","Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety"};
const string unitName[] = {"","Thousand","Million","Billion","Trillion","Quadrillion","Quintillion","Sextillion","Septillion","Octillion","Nonillion","Decillion","Undecillion","Duodecillion"};
//like wordyNumber, but only for numbers from 0 to 999
string wordyUnit(int i) {
	string ret;
	if (i>=100) {
		//add the number of hundreds ("five" hundred)
		ret+=ones[((i%1000)/100)-1];
		//add the word "hundred"
		ret += " hundred";
		//add 3 for the "and"
		if (i%100 != 0) {
			ret+=" and";
		}
	}
	if (i%100 > 10 && i%100 < 20) {
		//add teens ("fifteen")
		ret+=' '+teens[i%100-11];
	} else {
		//add tens place ("fifty")
		if (i%100==10 || i%100 >= 20) {
			ret+=' '+tens[((i%100)/10)-1];
		}
		//add ones place ("five")
		if (i%10 != 0) {
			ret+=' '+ones[i%10-1];
		}
	}
	return ret;
}
template <class T> string wordyNumber(T i) {
	//zero is an exception
	if (i==0) return "Zero";
	string ret;
	for (auto unit = 13; unit >= 0; --unit) {
		int unitValue = (i/((long)pow(1000,unit)))%1000;
//		cout<<"Unit "<<unit<<" value "<<unitValue;
		if (unitValue>0) {
			//the word unit for this chunk
			ret+= " "+wordyUnit(unitValue);
			ret+= " "+unitName[unit];
		}
	}
	return ret;
}
void openHashMap() {
	//string map of length 10, with keys of ints that are hashed into ints
	OpenHashMap<int, string, int> map;

//	cout<< wordyNumber(123456789123456789123);

	for (unsigned short i = 0; i < 1500; ++i) {
		map.put(i, wordyNumber(i));
	}

	//map.print(false);
	map.print(true);
	cout<<"Getting numbers\n";
	cout<<"Get 7: "<<map.get(7)<<'\n';
	cout<<"Get 15: "<<map.get(15)<<'\n';
	cout<<"Get 27: "<<map.get(27)<<'\n';
	cout<<"Get 256: "<<map.get(256)<<'\n';
	cout<<"Get 1234: "<<map.get(1234)<<'\n';

}
void closedHashMap() {
	ClosedHashMap<int, string, 3, int> map;
//	map.print();
	for (int i = 0; i <15; ++i) {
		map.put(i, wordyNumber(i));
	}
	map.print();
	cout<<"7 is "<<map.get(7)<<'\n';
	map.remove(7);
//	cout<<"32 is "<<map.get(32)<<'\n';
	map.print();
	try {
		cout<<"7 is "<<map.get(7)<<'\n';
		cerr<<"Seven is NOT SUPPOSED TO BE IN THE MAP";
	} catch (DoesNotContain& c) {
		cout<<"Good, seven is not there\n";
	}
}
void leak() {
	cout<<"about to leak some memory\n";
	/*while(true) {
		auto* map = new ClosedHashMap<int, string, 150, int>();
		map->put(15,"Hey");
	}*/
}

void skipList() {
	//following estimates use following test and i5 16GB ram SSD
	//30.59-34.34s to add 10,000,000 simple nodes
	//13.5-13.6s to add 5,000,000 simple nodes
	//4.901-5.232s to add 2,000,000 simple nodes
	//2.03-2.06s to add 1,000,000 simple nodes
	//.91-.92s to add 500,000 simple nodes
	srand(12);
	SkipList<long, long,18> l;
//	l.put(69,"Sixty Nine");
//	l.put(420,"Four Twenty");
	for (auto i = 0; i < 1000000; ++i) {
//		long val = ((long)rand()) *  rand();
//		val = rand()%100;
		l.put(((long)rand()) *  rand(), ((long)rand()) *  rand());
	}
//	cout<<"Lol Nice "<<l.get(420)<<'\n';
//	l.printKeyMap();
//	l.print();
//	cout<<"Removing\n";
//	l.remove(420);
//	l.remove(69);
//	l.printKeyMap();
//	l.print();
}

void queueFIFO() {
	auto l = QueueFIFO<string>();
	l.put("Head Data");
	l.put("Next");
	l.put("Going");
	l.put("Last");
	while (!l.isEmpty()) {
		cout<<"Head is "<<l.pop()<<'\n';
	}
}
int main() {
	Timer t;
	queueFIFO();
//	skipList();
//	cout<<"Lol Nice "<<l.get(420)<<'\n';
	//leak();
//	fiddleWithLinked();
//	closedHashMap();
//	openHashMap();
	//fiddleClassy();
//	funcPointer();
//	builtIn();
//	fiddleClassy();
	//fiddleWithBinaryTreeMap();
//	auto list = LinkedList<Pair <int,string> >();
	//fiddleWithBinaryTree();
//	cout<<"Fact 15 is "<<factorial(15)<<'\n';
//	stackUI();
//	fiddleWithDS();
//	fiddleWithCLL();
//	fiddleWithDLL();
	return 0;
}