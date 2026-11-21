#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <stdexcept>
#include <windows.h>
#include "data.h" 

Sale::Sale(const std::string& p, int q, double pp, double d, const std::string& c, const std::string& t)
    : product(p), quantity(q), pricePerUnit(pp), discount(d), cashier(c), time(t) {
}

Node::Node(const Sale& s) : data(s), prev(nullptr), next(nullptr) {}

LinkedList::LinkedList() : head(nullptr), tail(nullptr) {}

LinkedList::~LinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

void LinkedList::addAtBeginning(const Sale& sale) {
    Node* newNode = new Node(sale);
    if (head == nullptr) {
        head = tail = newNode;
    }
    else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
}
Node* LinkedList::getHead() const { return head; }
Node* LinkedList::getTail() const { return tail; }
void LinkedList::addAfter(const std::string& cashier, const Sale& sale) {
    Node* current = head;
    while (current != nullptr && current->data.cashier != cashier) {
        current = current->next;
    }

    if (current != nullptr) {
        Node* newNode = new Node(sale);
        if (current->next == nullptr) {
            current->next = newNode;
            newNode->prev = current;
            tail = newNode;
        }
        else {
            newNode->next = current->next;
            newNode->prev = current;
            current->next->prev = newNode;
            current->next = newNode;
        }
    }
}

void LinkedList::removeNode(const std::string& cashier) {
    Node* current = head;
    while (current != nullptr && current->data.cashier != cashier) {
        current = current->next;
    }

    if (current == nullptr) return;

    if (current->prev != nullptr) {
        current->prev->next = current->next;
    }
    else {
        head = current->next;
    }

    if (current->next != nullptr) {
        current->next->prev = current->prev;
    }
    else {
        tail = current->prev;
    }

    delete current;
}

void LinkedList::displayAll() {
    Node* current = head;
    while (current != nullptr) {
        std::cout << "Час: " << current->data.time << ", Продукт: " << current->data.product
            << ", Кількість: " << current->data.quantity << ", Ціна: " << current->data.pricePerUnit <<
            ", Дисконт: " << current->data.discount * 100 << "%"
            << ", Кассир: " << current->data.cashier << std::endl;
        current = current->next;
    }
}

void LinkedList::displayReverse() {
    Node* current = tail;
    while (current != nullptr) {
        std::cout << "Час: " << current->data.time << ", Продукт: " << current->data.product
            << ", Кількість: " << current->data.quantity << ", Ціна: " << current->data.pricePerUnit
            << ", Кассир: " << current->data.cashier << std::endl;
        current = current->prev;
    }
}

void LinkedList::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    Node* current = head;
    while (current != nullptr) {
        file << current->data.time << " "
            << current->data.product << " "
            << current->data.quantity << " "
            << current->data.pricePerUnit << " "
            << current->data.discount << " "
            << current->data.cashier << std::endl;
        current = current->next;
    }
    file.close();
}

void LinkedList::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string time, product, cashier;
        int quantity;
        double price, discount;

        if (iss >> time >> product >> quantity >> price >> discount >> cashier) {
            Sale sale(product, quantity, price, discount, cashier, time);
            addAtBeginning(sale);
        }
    }
    file.close();
}

PriorityQueue::CashierInfo::CashierInfo(const std::string& n, double t) : name(n), totalSales(t) {}

void PriorityQueue::swap(int i, int j) {
    std::swap(heap[i], heap[j]);
}

void PriorityQueue::heapifyUp(int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap[i].totalSales <= heap[parent].totalSales) break;
        swap(i, parent);
        i = parent;
    }
}

void PriorityQueue::heapifyDown(int i) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int largest = i;

    if (left < heap.size() && heap[left].totalSales > heap[largest].totalSales)
        largest = left;
    if (right < heap.size() && heap[right].totalSales > heap[largest].totalSales)
        largest = right;

    if (largest != i) {
        swap(i, largest);
        heapifyDown(largest);
    }
}

void PriorityQueue::insert(const CashierInfo& ci) {
    heap.push_back(ci);
    heapifyUp(static_cast<int>(heap.size()) - 1);
}

PriorityQueue::CashierInfo PriorityQueue::extractMax() {
    if (isEmpty()) {
        throw std::runtime_error("Купа пуста");
    }

    CashierInfo max = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    if (!heap.empty()) {
        heapifyDown(0);
    }
    return max;
}

bool PriorityQueue::isEmpty() {
    return heap.empty();
}

void PriorityQueue::buildHeapFromVector(const std::vector<CashierInfo>& arr) {
    heap = arr;
    for (int i = static_cast<int>(heap.size()) / 2 - 1; i >= 0; i--) {
        heapifyDown(i);
    }
}

std::vector<PriorityQueue::CashierInfo> PriorityQueue::sortUsingHeap() {
    std::vector<CashierInfo> sorted;
    PriorityQueue temp = *this;

    while (!temp.isEmpty()) {
        sorted.push_back(temp.extractMax());
    }
    return sorted;
}

void PriorityQueue::deleteElement(const std::string& name) {
    int index = -1;
    for (int i = 0; i < static_cast<int>(heap.size()); i++) {
        if (heap[i].name == name) {
            index = i;
            break;
        }
    }

    if (index == -1) return;

    heap[index] = heap.back();
    heap.pop_back();

    if (index < static_cast<int>(heap.size())) {
        heapifyUp(index);
        heapifyDown(index);
    }
}

void HeapSorter::sort(std::vector<PriorityQueue::CashierInfo>& arr) {
    PriorityQueue pq;
    pq.buildHeapFromVector(arr);
    arr.clear();
    std::vector<PriorityQueue::CashierInfo> sorted = pq.sortUsingHeap();
    arr = sorted;
}

void HeapSorter::testSorting(const LinkedList& salesList) {
    std::vector<PriorityQueue::CashierInfo> realData;
    Node* current = salesList.getHead();
    while (current != nullptr) {
        double finalPrice = current->data.quantity * current->data.pricePerUnit * (1 - current->data.discount);
        realData.push_back(PriorityQueue::CashierInfo(current->data.cashier, finalPrice));
        current = current->next;
    }

    std::cout << "\nПеред сортуванням: ";
    for (const auto& ci : realData) {
        std::cout << ci.name << ": " << ci.totalSales << " грн. ";
    }

    sort(realData);

    std::cout << "\nПісля сортування: ";
    for (const auto& ci : realData) {
        std::cout << ci.name << ": " << ci.totalSales << " грн. ";
    }
    std::cout << std::endl;
}
