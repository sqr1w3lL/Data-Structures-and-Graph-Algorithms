#pragma once

#include <vector>
#include <string>
#include <map>

struct Sale {
    std::string product;
    int quantity;
    double pricePerUnit;
    double discount;
    std::string cashier;
    std::string time;

    Sale(const std::string& p, int q, double pp, double d, const std::string& c, const std::string& t);
};

class Node {
public:
    Sale data;
    Node* prev;
    Node* next;
    Node(const Sale& s);
};

class LinkedList {
private:
    Node* head;
    Node* tail;

public:
    LinkedList();
    ~LinkedList();

    void addAtBeginning(const Sale& sale);
    void displayAll();
    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
    Node* getHead() const;
    Node* getTail() const;
    void removeNode(const std::string& cashier);
    void displayReverse();
    void addAfter(const std::string& cashier, const Sale& sale);
};

class PriorityQueue {
public:
    struct CashierInfo {
        std::string name;
        double totalSales;
        CashierInfo(const std::string& n, double t);
    };

    void insert(const CashierInfo& ci);
    CashierInfo extractMax();
    bool isEmpty();
    void buildHeapFromVector(const std::vector<CashierInfo>& arr);
    std::vector<CashierInfo> sortUsingHeap();
    void deleteElement(const std::string& name);

private:
    std::vector<CashierInfo> heap;
    void swap(int i, int j);
    void heapifyUp(int i);
    void heapifyDown(int i);
};

class HeapSorter {
public:
    static void sort(std::vector<PriorityQueue::CashierInfo>& arr);
    static void testSorting(const LinkedList& salesList);
};
