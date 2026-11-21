#pragma once
#include <vector>
#include <string>
#include <msclr/marshal_cppstd.h>
#include "ManagedStructs.h"
#include <fstream>
#include <cmath>
#include <algorithm> 
using namespace System;
using namespace System::Collections::Generic;

namespace Native {
    struct Student {
        int code;
        std::string surname;
        std::string initials;
        std::string group;
        double avgMark;
        Student() : code(0), avgMark(0.0) {}
        Student(int c, const std::string& s, const std::string& i, const std::string& g, double m)
            : code(c), surname(s), initials(i), group(g), avgMark(m) {
        }
    };

    struct BSTNode {
        Student data;
        BSTNode* left;
        BSTNode* right;
        BSTNode(const Student& s) : data(s), left(nullptr), right(nullptr) {}
    };

    class BinarySearchTree {
    private:
        BSTNode* root;

        BSTNode* insertRec(BSTNode* node, const Student& s) {
            if (!node) return new BSTNode(s);
            if (s.code < node->data.code)
                node->left = insertRec(node->left, s);
            else if (s.code > node->data.code)
                node->right = insertRec(node->right, s);
            else
                node->data = s;
            return node;
        }

        BSTNode* searchRec(BSTNode* node, int code) {
            if (!node) return nullptr;
            if (code == node->data.code) return node;
            if (code < node->data.code) return searchRec(node->left, code);
            else return searchRec(node->right, code);
        }

        BSTNode* findMin(BSTNode* node) {
            while (node && node->left) node = node->left;
            return node;
        }

        BSTNode* removeRec(BSTNode* node, int code) {
            if (!node) return nullptr;
            if (code < node->data.code) {
                node->left = removeRec(node->left, code);
            }
            else if (code > node->data.code) {
                node->right = removeRec(node->right, code);
            }
            else {
                if (!node->left && !node->right) {
                    delete node;
                    return nullptr;
                }
                else if (!node->left) {
                    BSTNode* tmp = node->right;
                    delete node;
                    return tmp;
                }
                else if (!node->right) {
                    BSTNode* tmp = node->left;
                    delete node;
                    return tmp;
                }
                else {
                    BSTNode* mn = findMin(node->right);
                    node->data = mn->data;
                    node->right = removeRec(node->right, mn->data.code);
                }
            }
            return node;
        }

        void findBestRec(BSTNode* node, double& bestMark, std::vector<Student>& best) {
            if (!node) return;
            findBestRec(node->left, bestMark, best);
            if (node->data.avgMark > bestMark) {
                bestMark = node->data.avgMark;
                best.clear();
                best.push_back(node->data);
            }
            else if (std::abs(node->data.avgMark - bestMark) < 1e-6) {
                best.push_back(node->data);
            }
            findBestRec(node->right, bestMark, best);
        }

        void findWorstRec(BSTNode* node, double& worstMark, std::vector<Student>& worst) {
            if (!node) return;
            findWorstRec(node->left, worstMark, worst);
            if (node->data.avgMark < worstMark) {
                worstMark = node->data.avgMark;
                worst.clear();
                worst.push_back(node->data);
            }
            else if (std::abs(node->data.avgMark - worstMark) < 1e-6) {
                worst.push_back(node->data);
            }
            findWorstRec(node->right, worstMark, worst);
        }

        void displayTreeRec(BSTNode* node, List<String^>^ lines, int indent) {
            if (!node) return;
            displayTreeRec(node->right, lines, indent + 4);

            String^ indentStr = gcnew String(' ', indent);
            String^ line = indentStr + node->data.code.ToString() + " (" +
                gcnew String(node->data.surname.c_str()) + ")";
            lines->Add(line);

            displayTreeRec(node->left, lines, indent + 4);
        }

        void cleanup(BSTNode* node) {
            if (!node) return;
            cleanup(node->left);
            cleanup(node->right);
            delete node;
        }

    public:
        BinarySearchTree() : root(nullptr) {}

        ~BinarySearchTree() {
            cleanup(root);
        }

        void Insert(int code, const std::string& surname, const std::string& initials,
            const std::string& group, double avgMark) {
            Student student(code, surname, initials, group, avgMark);
            root = insertRec(root, student);
        }

        Student* Search(int code) {
            BSTNode* node = searchRec(root, code);
            if (node) return &(node->data);
            return nullptr;
        }

        void Remove(int code) {
            root = removeRec(root, code);
        }

        List<ManagedStudent>^ FindBestStudents() {
            double bestMark = -1e9;
            std::vector<Student> best;
            findBestRec(root, bestMark, best);

            List<ManagedStudent>^ result = gcnew List<ManagedStudent>();
            for (const auto& student : best) {
                ManagedStudent ms;
                ms.code = student.code;
                ms.surname = gcnew String(student.surname.c_str());
                ms.initials = gcnew String(student.initials.c_str());
                ms.group = gcnew String(student.group.c_str());
                ms.avgMark = student.avgMark;
                result->Add(ms);
            }
            return result;
        }

        List<ManagedStudent>^ FindWorstStudents() {
            double worstMark = 1e9;
            std::vector<Student> worst;
            findWorstRec(root, worstMark, worst);

            List<ManagedStudent>^ result = gcnew List<ManagedStudent>();
            for (const auto& student : worst) {
                ManagedStudent ms;
                ms.code = student.code;
                ms.surname = gcnew String(student.surname.c_str());
                ms.initials = gcnew String(student.initials.c_str());
                ms.group = gcnew String(student.group.c_str());
                ms.avgMark = student.avgMark;
                result->Add(ms);
            }
            return result;
        }

        List<String^>^ GetTreeStructure() {
            List<String^>^ lines = gcnew List<String^>();
            displayTreeRec(root, lines, 0);
            return lines;
        }

        void LoadFromFile(String^ filename) {
            std::string nativeFilename = msclr::interop::marshal_as<std::string>(filename);
            std::ifstream fin(nativeFilename);
            if (!fin.is_open()) return;

            int code;
            std::string s, i, g;
            double m;
            while (fin >> code >> s >> i >> g >> m) {
                Insert(code, s, i, g, m);
            }
            fin.close();
        }
    };
}

public ref class ManagedBinaryTree {
private:
    Native::BinarySearchTree* nativeTree;

public:
    ManagedBinaryTree() {
        nativeTree = new Native::BinarySearchTree();
    }

    ~ManagedBinaryTree() {
        this->!ManagedBinaryTree();
    }

    !ManagedBinaryTree() {
        delete nativeTree;
    }

    void Insert(int code, String^ surname, String^ initials, String^ group, double avgMark) {
        std::string s_surname = msclr::interop::marshal_as<std::string>(surname);
        std::string s_initials = msclr::interop::marshal_as<std::string>(initials);
        std::string s_group = msclr::interop::marshal_as<std::string>(group);
        nativeTree->Insert(code, s_surname, s_initials, s_group, avgMark);
    }

    Nullable<ManagedStudent> Search(int code) {
        Native::Student* student = nativeTree->Search(code);
        if (student) {
            ManagedStudent ms;
            ms.code = student->code;
            ms.surname = gcnew String(student->surname.c_str());
            ms.initials = gcnew String(student->initials.c_str());
            ms.group = gcnew String(student->group.c_str());
            ms.avgMark = student->avgMark;
            return ms;
        }
        return Nullable<ManagedStudent>();
    }

    void Remove(int code) {
        nativeTree->Remove(code);
    }

    List<ManagedStudent>^ FindBestStudents() {
        return nativeTree->FindBestStudents();
    }

    List<ManagedStudent>^ FindWorstStudents() {
        return nativeTree->FindWorstStudents();
    }

    List<String^>^ GetTreeStructure() {
        return nativeTree->GetTreeStructure();
    }

    void LoadFromFile(String^ filename) {
        nativeTree->LoadFromFile(filename);
    }
};
