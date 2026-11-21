#pragma once
#include <vector>
#include <string>
#include <msclr/marshal_cppstd.h>
#include "ManagedStructs.h"
#include <cmath>
#include <fstream>
using namespace System;
using namespace System::Collections::Generic;

namespace Native {
    enum class SlotState { EMPTY, OCCUPIED, DELETED };

    struct TaxPayer {
        int regNumber;
        std::string surname;
        std::string name;
        std::string fathername;
        TaxPayer() : regNumber(0) {}
        TaxPayer(int n, const std::string& s, const std::string& nm, const std::string& f)
            : regNumber(n), surname(s), name(nm), fathername(f) {
        }
    };

    struct Slot {
        TaxPayer tp;
        SlotState state;
        Slot() : state(SlotState::EMPTY) {}
    };

    class HashTable {
    private:
        std::vector<Slot> table;
        int size;

        int hashFunc(int key) {
            const double A = 0.6180339887;
            double frac = key * A - std::floor(key * A);
            return static_cast<int>(size * frac);
        }

    public:
        HashTable(int n) : size(n) {
            table.resize(size);
        }

        HashTable() : HashTable(11) {}

        void Insert(int regNumber, const std::string& surname, const std::string& name, const std::string& fathername) {
            TaxPayer p(regNumber, surname, name, fathername);
            int h = hashFunc(p.regNumber);
            int i = 0;
            int firstDeleted = -1;

            while (i < size) {
                int idx = (h + i * i) % size;
                if (table[idx].state == SlotState::EMPTY) {
                    int useIdx = (firstDeleted != -1) ? firstDeleted : idx;
                    table[useIdx].tp = p;
                    table[useIdx].state = SlotState::OCCUPIED;
                    return;
                }
                else if (table[idx].state == SlotState::DELETED && firstDeleted == -1) {
                    firstDeleted = idx;
                }
                else if (table[idx].state == SlotState::OCCUPIED && table[idx].tp.regNumber == p.regNumber) {
                    table[idx].tp = p;
                    return;
                }
                ++i;
            }

            if (firstDeleted != -1) {
                table[firstDeleted].tp = p;
                table[firstDeleted].state = SlotState::OCCUPIED;
            }
        }

        void Remove(int regNumber) {
            int h = hashFunc(regNumber);
            int i = 0;
            while (i < size) {
                int idx = (h + i * i) % size;
                if (table[idx].state == SlotState::EMPTY) return;
                if (table[idx].state == SlotState::OCCUPIED && table[idx].tp.regNumber == regNumber) {
                    table[idx].state = SlotState::DELETED;
                    table[idx].tp = TaxPayer();
                    return;
                }
                ++i;
            }
        }

        List<ManagedTaxPayer>^ GetTableSnapshot() {
            List<ManagedTaxPayer>^ result = gcnew List<ManagedTaxPayer>();
            for (int i = 0; i < size; ++i) {
                ManagedTaxPayer mtp;
                mtp.regNumber = table[i].tp.regNumber;
                mtp.surname = gcnew String(table[i].tp.surname.c_str());
                mtp.name = gcnew String(table[i].tp.name.c_str());
                mtp.fathername = gcnew String(table[i].tp.fathername.c_str());
                result->Add(mtp);
            }
            return result;
        }

        List<KeyValuePair<int, ManagedTaxPayer>>^ GetOccupiedSlots() {
            List<KeyValuePair<int, ManagedTaxPayer>>^ result = gcnew List<KeyValuePair<int, ManagedTaxPayer>>();
            for (int i = 0; i < size; ++i) {
                if (table[i].state == SlotState::OCCUPIED) {
                    ManagedTaxPayer mtp;
                    mtp.regNumber = table[i].tp.regNumber;
                    mtp.surname = gcnew String(table[i].tp.surname.c_str());
                    mtp.name = gcnew String(table[i].tp.name.c_str());
                    mtp.fathername = gcnew String(table[i].tp.fathername.c_str());
                    result->Add(KeyValuePair<int, ManagedTaxPayer>(i, mtp));
                }
            }
            return result;
        }

        ManagedTaxPayer^ Search(int regNumber) {
            int h = hashFunc(regNumber);
            int i = 0;
            while (i < size) {
                int idx = (h + i * i) % size;
                if (table[idx].state == SlotState::EMPTY) return nullptr;
                if (table[idx].state == SlotState::OCCUPIED && table[idx].tp.regNumber == regNumber) {
                    ManagedTaxPayer^ mtp = gcnew ManagedTaxPayer();
                    mtp->regNumber = table[idx].tp.regNumber;
                    mtp->surname = gcnew String(table[idx].tp.surname.c_str());
                    mtp->name = gcnew String(table[idx].tp.name.c_str());
                    mtp->fathername = gcnew String(table[idx].tp.fathername.c_str());
                    return mtp;
                }
                ++i;
            }
            return nullptr;
        }

        void LoadFromFile(String^ filename) {
            std::string nativeFilename = msclr::interop::marshal_as<std::string>(filename);
            std::ifstream fin(nativeFilename);
            if (!fin.is_open()) return;

            int reg;
            std::string s, n, f;
            while (fin >> reg >> s >> n >> f) {
                Insert(reg, s, n, f);
            }
            fin.close();
        }

        int GetSize() {
            return size;
        }
    };
}

public ref class ManagedHashTable {
private:
    Native::HashTable* nativeTable;

public:
    ManagedHashTable(int size) {
        nativeTable = new Native::HashTable(size);
    }

    ManagedHashTable() : ManagedHashTable(11) {}

    ~ManagedHashTable() {
        this->!ManagedHashTable();
    }

    !ManagedHashTable() {
        delete nativeTable;
    }

    void Insert(int regNumber, String^ surname, String^ name, String^ fathername) {
        std::string s_surname = msclr::interop::marshal_as<std::string>(surname);
        std::string s_name = msclr::interop::marshal_as<std::string>(name);
        std::string s_fathername = msclr::interop::marshal_as<std::string>(fathername);
        nativeTable->Insert(regNumber, s_surname, s_name, s_fathername);
    }

    void Remove(int regNumber) {
        nativeTable->Remove(regNumber);
    }

    List<ManagedTaxPayer>^ GetTableSnapshot() {
        return nativeTable->GetTableSnapshot();
    }

    List<KeyValuePair<int, ManagedTaxPayer>>^ GetOccupiedSlots() {
        return nativeTable->GetOccupiedSlots();
    }

    ManagedTaxPayer^ Search(int regNumber) {
        return nativeTable->Search(regNumber);
    }

    void LoadFromFile(String^ filename) {
        nativeTable->LoadFromFile(filename);
    }

    void ChangeSize(int newSize) {
        delete nativeTable;
        nativeTable = new Native::HashTable(newSize);
    }
};
