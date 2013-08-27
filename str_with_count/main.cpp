#include <iostream>
#include <string>

using namespace std;

class SmartStringPointer {
public:
	SmartStringPointer() {
		string str = "a" + to_string(count);
		pointer = (string *) (int(new string(str)) + 1);
		count++;
	}

	~SmartStringPointer() {
		destructor();
	}

	//TODO: copyring constructor
	SmartStringPointer(SmartStringPointer& toCopy) {		
		destructor();
		toCopy.makeNotUnique();
		this->pointer = toCopy.pointer;
	}

	void operator =(SmartStringPointer& newValue) {
		if (&newValue == this) { return; }
		destructor();
		newValue.makeNotUnique();
		this->pointer = newValue.pointer;
	}

	void swap(SmartStringPointer& newValue) {
		string* tmp = newValue.pointer;
		newValue.pointer = this->pointer;
		this->pointer = tmp;
	}

	bool compare(const SmartStringPointer& ssp) {
		string* thisPointer = this->getPointer();
		string* sspPointer  = ssp.getPointer();

		return (*thisPointer) < (*sspPointer);
	}

	string* getString() {
		return getPointer();
	}

private:
	static int count;

	void destructor() {
		if (!isPointerUnique()) { return; }
		cout << "Destructor: " << *getPointer() << endl;
		delete getPointer();
	}

	/*
	SmartStringPointer(const string& str): pointer(new string(str) + 1) {
	}
	*/

	bool isPointerUnique() {
		return (int) pointer & 0x1;
	}

	void makeNotUnique() {
		pointer = getPointer();
	}

	string* getPointer() const {
		return (string*) (int(pointer) & 0xfffffffe);
	}

	string* pointer;
};
int SmartStringPointer::count = 0;

void sort(SmartStringPointer* arr, int size) {
	for (int i = 0; i < size - 1; i++) {
		for (int j = i + 1; j < size; j++) {
			if (arr[i].compare(arr[j])) {
				arr[i].swap(arr[j]);
			}			
		}
	}
}

int main() {
	int size = 100;
	SmartStringPointer* arr = new SmartStringPointer[size];

	for (int i = 0; i < size; i++) {
		cout << *(arr[i].getString()) << " ";
	}
	cout << endl;

	sort(arr, size);

	cout << "After sort." << endl;

	for (int i = 0; i < size; i++) {
		cout << *(arr[i].getString()) << " ";
	}
	cout << endl;

	SmartStringPointer p;
	for (int i = 0 ; i < size; i += 2) {
		p = arr[i];
	}

	delete [] arr;

	return 0;
}