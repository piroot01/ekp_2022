#include <iostream>
#include <string>
#include <fmt/core.h>
#include <fmt/format.h>

class List {
public:

    // Method for printing contents of list.
    void Print();

    // Method for printing list as integer.
    int GetAsInt();

    // Method for insering inteager to list.
    void Insert(List* word, int& inp);

    // Reverse the order of linked list.
    void Reverse();

    // Method for inserting single char to list.
    void InsertChar(char& data);
    
    // List destructor.
    ~List();

private:

    // definition of single char in list
    typedef struct Char {
        char data;
        struct Char* next;
    } Char;

    // The first/last char in list.
    Char* headChar_ = nullptr;
};

class FastAtoi {
public:

    static int getVal(const std::string& str) {
        int tmpVal = 0, i = 0;
        bool neg = FastAtoi::neg(str[0]);
    
        if (neg)
            i = 1;
        else
            i = 0;

        while (str[i] != '\0')
            tmpVal = tmpVal * 10 + str[i++] - '0';

        if (neg)
            return tmpVal * (-1);
        else
            return tmpVal;
    }

private:
    static bool neg(const char& sign) {
        if (sign == '-')
            return true;
        else
            return false;
    }
};

void List::Insert(List* tmpList, int& inp) {
    std::string tmpStr = fmt::format_int(inp).str();
        
    if (tmpStr.compare("0") == 0)
        throw "Input is not an integer!\n";

    for (char& tmpChar : fmt::format_int(inp).str()) {
        tmpList->InsertChar(tmpChar);
    }
}

void List::Print() {
    Char* currentChar = headChar_;
    int index = 0;

    while (currentChar != nullptr) {
        //std::cout << "[" << index << "]" << ": " << currentChar->data << '\n';
        fmt::print("[{}]: {}\n", index, currentChar->data);
        currentChar = currentChar->next;
        index++;
    }
}

void List::InsertChar(char& data) {
    Char* newChar = new Char;

    // Insert char to data
    newChar->data = data;

    newChar->next = headChar_;
    headChar_ = newChar;
}

void List::Reverse() {
    Char* prevChar = nullptr;
    Char* nextChar = nullptr;
    Char* currentChar = headChar_;

    while (currentChar != nullptr) {
        nextChar = currentChar->next;
        currentChar->next = prevChar;
        prevChar = currentChar;
        currentChar = nextChar;
    }

    headChar_ = prevChar;
}

int List::GetAsInt() {
    std::string tmpStr;
    Char* currentChar = headChar_;
    
    while (currentChar != nullptr) {
        tmpStr.append(1, currentChar->data);
        currentChar = currentChar->next;
    }

    return FastAtoi::getVal(tmpStr);
}

List::~List() {
    Char* currentChar = headChar_;
    Char* nextChar = nullptr;

    while (currentChar != nullptr) {
        nextChar = currentChar->next;
        delete currentChar;
        currentChar = nextChar;
    }
}

int
main()
{
    List num;
    int inp = 314;

    // read int from stdin
    std::cin >> inp;

    try {
        num.Insert(&num, inp);
    } catch (const char* errMsg) {
        std::cerr << errMsg;
    }

    num.Reverse();
    std::cout << num.GetAsInt() << '\n';

    return 0;
}
