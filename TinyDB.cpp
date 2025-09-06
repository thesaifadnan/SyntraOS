/* To keep things simple, access specifiers are set to -> public */

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>

#define NEW_LINE std::cout << '\n';

constexpr bool LOG_STATUS = true;

enum class ReturnStatus {
  success,
  failure
};

using string = std::string;
using serial_t = size_t;

template <typename KEY_TYPE, typename VALUE_TYPE>
using map = std::map<KEY_TYPE, VALUE_TYPE>;

template <typename KEY_TYPE, typename VALUE_TYPE>
using unordered_map = std::unordered_map<KEY_TYPE, VALUE_TYPE>;

template <typename DATA_TYPE>
using set = std::set<DATA_TYPE>;

template <typename DATA_TYPE>
using vector = std::vector<DATA_TYPE>;


// template <typename DATA_TYPE>
class Cell {
private:
  string value;
  
public:
  // Default Constructor
  Cell() : value("NULL") { }
  
  // Parameterized Constructor
  Cell(string value) : value(value) {
    // Blah-Blah Black Sheep
  }

  string getValue() const {
    return value;
  }

  void setValue(const string& newValue) {
    value = newValue;
  }
};

class Attribute {
  string title;
  unordered_map<serial_t, Cell> records;

public:
  // Default Constructor
  Attribute(string title) : title(title) { }

  // Parameterized Constructor
  // Attribute(string title, serial_t serialKey) : title(title), records({{serialKey, Cell()}}) { }

  void setTitle(const string& newTitle) {
    title = newTitle;
  }

  string getTitle() const {
    return title;
  }

  string getValueAtRecord(serial_t serialKey) {
    return records[serialKey].getValue();
  }

  void updateRecord(serial_t serialKey, string cellValue) {
    /* Validate if the [serialKey] is already present in the table. */
    // if (records.find(serialKey) != records.end()) {
    //   NEW_LINE
    //   std::cerr << "Serial key [" << serialKey << "] is already present, updating to Value [" << cellValue << "].";
    //   NEW_LINE
    // } 

    records[serialKey] = cellValue;

    if (LOG_STATUS) {
      std::cout << "UPDATED";
      NEW_LINE
      std::cout << "Attribute [\"" << title << "\"] @ Serial [\"" << serialKey << "\"] : Value [\"" << cellValue << "\"]";
      NEW_LINE 
    }
  }


};

class Table {
public:
  serial_t nextSerialKey;
  set<serial_t> serialSet;
  unordered_map<string, Attribute> attributes; 

  Table() : nextSerialKey(0) { }

  bool findAttribute(const string& attribute) {
    if (attributes.find(attribute) == attributes.end()) {
      return false;
    }

    return true;
  }

  void updateAttribute(const string& newAttribute) {
    /* Validate if the [newAttribute] is already present in the table. */
    // if (attributes.find(newAttribute) != attributes.end()) {
    //   NEW_LINE
    //   std::cerr << "Cannot insert attribute [" << newAttribute << "]";
    //   NEW_LINE
    //   std::cerr << "Already present";
    //   NEW_LINE

    // }

    /* If the attribute is not present, add it. */
    // attributes[newAttribute] = Attribute(newAttribute);
    attributes.emplace(newAttribute, Attribute(newAttribute));

    if (LOG_STATUS) {
      std::cout << "UPDATED";
      NEW_LINE
      std::cout << "Attribute [\"" << newAttribute << "\"] with Title [\"" << newAttribute << "\"]";
      NEW_LINE 
    }
  }

  ReturnStatus insertInstance(const vector<string>& operandAttributes, const vector<string>& operandCellValues) {
    if (operandAttributes.empty() || operandCellValues.empty()) {
      NEW_LINE
      std::cerr << "Cannot insert instance with empty attributes or cell values";
      NEW_LINE

      return ReturnStatus::failure;
    }

    if (operandAttributes.size() != operandCellValues.size()) {
      NEW_LINE
      std::cerr << "Cannot insert instance with different-sized attributes and cell values";
      NEW_LINE

      return ReturnStatus::failure;
    }

    for (int index = 0; index < operandAttributes.size(); index++) {
      if (! findAttribute(operandAttributes[index])) {
        NEW_LINE
        std::cerr << "Cannot insert at attribute [" << operandAttributes[index] << "]";
        NEW_LINE
        std::cerr << "No such attribute"; 
        NEW_LINE

        return ReturnStatus::failure;
      }

      attributes[operandAttributes[index]].updateRecord(nextSerialKey, operandCellValues[index]);
      serialSet.insert(nextSerialKey);
    }

    nextSerialKey++;
    return ReturnStatus::success;
  }

  void printTable() {
    vector<string> attributeTitles;

    for (const auto& attribute : attributes) {
      attributeTitles.push_back(attribute.second.getTitle());
    }

    for (const auto& title : attributeTitles) {
      std::cout << title << " | ";
    }

    NEW_LINE

    for (const auto& serialKey : serialSet) {
      for (const auto& title : attributeTitles) {
        std::cout << attributes[title].getValueAtRecord(serialKey) << " | ";
      }

      NEW_LINE
    }
  }
};

int main() {
  vector<string> attributes = {"name", "age"};
  vector<string> cellValues = {"Shashank", "21"};

  Table table;

  table.insertInstance(attributes, cellValues);

  return 0;
}