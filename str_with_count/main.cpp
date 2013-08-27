#include <iostream>
#include <string>

using namespace std;

class SmartStringPointer {
public:
	SmartStringPointer() {
		string str = "a" + to_string(count);
		pointer = new String(str);
		count++;
	}

	/*
	static SmartStringPointer* createStringPointer(const string& str) {
		return new SmartStringPointer(str);
	}
	*/

	~SmartStringPointer() {
		if (!isPointerUnique()) { return; }
		delete pointer;
	}

	//TODO: copyring constructor
	SmartStringPointer(SmartStringPointer& toCopy) {
		toCopy.makeNotUnique();
		this->pointer = toCopy.pointer;
	}

	void operator =(SmartStringPointer& newValue) {
		newValue.makeNotUnique();
		this->pointer = newValue.pointer;
	}

	void swap(SmartStringPointer& newValue) {
		String* tmp = newValue.pointer;
		newValue.pointer = this->pointer;
		this->pointer = tmp;
	}

	bool compare(const SmartStringPointer& ssp) {
		String* thisPointer = this->getPointer();
		// cout << hex << ssp.pointer      << endl;
		// cout << hex << ssp.getPointer() << endl;
		String* sspPointer  = ssp.getPointer();

		return thisPointer->compare(*sspPointer);
	}

	string* getString() {
		return getPointer()->getString();
	}

private:
	static int count;

	class String {
	public:
		String(const string& s) {
			str = new string(s);
		}

		~String() {
			//TODO: print smth
			cout << "Destructor: " << *str << endl;
			delete str;
		}

		bool compare(const String& str) {
			return this->str < str.str;
		}

		string* getString() {
			return str;
		}

	private:
		string* str;
	};

	SmartStringPointer(const string& str): pointer(new String(str)) {
	}

	bool isPointerUnique() {
		return !((int) pointer & 0x1);
	}

	void makeNotUnique() {
		pointer = (String *) ((int) pointer + 1);
	}

	String* getPointer() const {
		return (String*) (int(pointer) & 0xfffffffe);
	}

	String* pointer;
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