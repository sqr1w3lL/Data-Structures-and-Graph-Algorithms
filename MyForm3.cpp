#include "MyForm3.h"
#include <msclr/marshal_cppstd.h>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace Finals;
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;

bool CompareItems(const TruckItem& a, const TruckItem& b) {
    return a.profit > b.profit;
}

void Truck::SetInitialData(int truckCapacity, double cost, int maxFlavor) {
    capacity = truckCapacity;
    purchaseCost = cost;
    maxFlavorCount = maxFlavor;
}

void Truck::AddDrink(System::String^ name, System::String^ flavor, double salePrice, int available) {
    Drink d;
    d.name = msclr::interop::marshal_as<std::string>(name);
    d.flavor = msclr::interop::marshal_as<std::string>(flavor);
    d.salePrice = salePrice;
    d.available = available;
    drinks->push_back(d);
}

void Truck::EditDrink(int index, System::String^ name, System::String^ flavor, double salePrice, int available) {
    if (index >= 0 && index < static_cast<int>(drinks->size())) {
        (*drinks)[index].name = msclr::interop::marshal_as<std::string>(name);
        (*drinks)[index].flavor = msclr::interop::marshal_as<std::string>(flavor);
        (*drinks)[index].salePrice = salePrice;
        (*drinks)[index].available = available;
    }
}

void Truck::DeleteDrink(int index) {
    if (index >= 0 && index < static_cast<int>(drinks->size())) {
        drinks->erase(drinks->begin() + index);
    }
}

void Truck::SetFlavorLimit(int limit) {
    maxFlavorCount = limit;
}

List<Dictionary<String^, Object^>^>^ Truck::GetDrinks() {
    List<Dictionary<String^, Object^>^>^ result = gcnew List<Dictionary<String^, Object^>^>();
    for (const auto& drink : *drinks) {
        Dictionary<String^, Object^>^ row = gcnew Dictionary<String^, Object^>();
        row->Add("name", gcnew String(drink.name.c_str()));
        row->Add("flavor", gcnew String(drink.flavor.c_str()));
        row->Add("salePrice", drink.salePrice);
        row->Add("available", drink.available);
        result->Add(row);
    }
    return result;
}

Tuple<List<Dictionary<String^, Object^>^>^, double, double, double, int>^ Truck::SolveGreedy() {
    std::vector<TruckItem> items;
    for (size_t i = 0; i < drinks->size(); ++i) {
        double profit = (*drinks)[i].salePrice - purchaseCost;
        TruckItem item;
        item.idx = static_cast<int>(i);
        item.profit = profit;
        item.avail = (*drinks)[i].available;
        items.push_back(item);
    }

    std::sort(items.begin(), items.end(), CompareItems);

    int remaining = capacity;
    double totalProfit = 0.0;
    double totalRevenue = 0.0;
    double totalCost = 0.0;

    List<Dictionary<String^, Object^>^>^ results = gcnew List<Dictionary<String^, Object^>^>();

    for (const auto& it : items) {
        if (remaining == 0) break;
        if (it.profit <= 0.0) continue;

        int take = std::min<int>(remaining, it.avail);
        if (take <= 0) continue;

        remaining -= take;
        totalProfit += take * it.profit;
        totalRevenue += take * (*drinks)[it.idx].salePrice;
        totalCost += take * purchaseCost;

        (*drinks)[it.idx].available -= take;

        Dictionary<String^, Object^>^ row = gcnew Dictionary<String^, Object^>();
        row->Add("name", gcnew String((*drinks)[it.idx].name.c_str()));
        row->Add("flavor", gcnew String((*drinks)[it.idx].flavor.c_str()));
        row->Add("take", take);
        row->Add("salePrice", (*drinks)[it.idx].salePrice);
        row->Add("profit", it.profit);
        results->Add(row);
    }

    return gcnew Tuple<List<Dictionary<String^, Object^>^>^, double, double, double, int>(
        results, totalProfit, totalRevenue, totalCost, remaining
    );
}

void HuffmanCompressor::GenerateCodes(HuffmanNode* node, std::string code) {
    if (!node) return;
    if (!node->left && !node->right) {
        (*huffmanCodes)[node->ch] = code;
        return;
    }
    GenerateCodes(node->left, code + "0");
    GenerateCodes(node->right, code + "1");
}

void HuffmanCompressor::DeleteTree(HuffmanNode* node) {
    if (node) {
        DeleteTree(node->left);
        DeleteTree(node->right);
        delete node;
    }
}

String^ HuffmanCompressor::LoadFile(String^ filename) {
    std::string nativeFilename = msclr::interop::marshal_as<std::string>(filename);
    std::ifstream file(nativeFilename);
    if (!file.is_open()) {
        throw gcnew System::IO::FileNotFoundException(L"Не вдалося відкрити файл: " + filename);
    }
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return gcnew String(content.c_str());
}

Tuple<String^, double, double, double>^ HuffmanCompressor::Compress(String^ inputFilename, String^ outputFilename) {
    String^ text = LoadFile(inputFilename);
    if (text->Length == 0) {
        throw gcnew Exception(L"Файл порожній. Стиснення неможливе.");
    }

    std::unordered_map<char, int> freq;
    for (int i = 0; i < text->Length; i++) {
        char c = static_cast<char>(text[i]);
        freq[c]++;
    }

    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, HuffmanNodeCompare> pq;
    for (const auto& p : freq) {
        pq.push(new HuffmanNode(p.first, p.second));
    }

    while (pq.size() > 1) {
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();
        pq.push(new HuffmanNode('\0', left->freq + right->freq, left, right));
    }

    if (!pq.empty()) {
        root = static_cast<void*>(pq.top());
    }

    if (root) {
        GenerateCodes(static_cast<HuffmanNode*>(root), "");
    }

    System::Text::StringBuilder^ encoded = gcnew System::Text::StringBuilder();
    for (int i = 0; i < text->Length; i++) {
        char c = static_cast<char>(text[i]);
        auto it = huffmanCodes->find(c);
        if (it != huffmanCodes->end()) {
            encoded->Append(gcnew String(it->second.c_str()));
        }
    }

    std::string nativeOutput = msclr::interop::marshal_as<std::string>(outputFilename);
    std::ofstream outFile(nativeOutput);
    outFile << msclr::interop::marshal_as<std::string>(encoded->ToString()) << std::endl;
    for (const auto& p : *huffmanCodes) {
        outFile << p.second << ":" << p.first << std::endl;
    }
    outFile.close();

    size_t originalSize = static_cast<size_t>(text->Length);
    size_t compressedSize = (encoded->Length + 7) / 8;
    double ratio = (compressedSize > 0) ? static_cast<double>(originalSize) / compressedSize : 0.0;

    return gcnew Tuple<String^, double, double, double>(
        encoded->ToString(), static_cast<double>(originalSize),
        static_cast<double>(compressedSize), ratio
    );
}

String^ HuffmanCompressor::Decompress(String^ inputFilename, String^ outputFilename) {
    std::string nativeInput = msclr::interop::marshal_as<std::string>(inputFilename);
    std::ifstream inFile(nativeInput);
    if (!inFile.is_open()) {
        throw gcnew System::IO::FileNotFoundException(L"Не вдалося відкрити файл: " + inputFilename);
    }

    std::string encoded;
    std::getline(inFile, encoded);

    std::unordered_map<std::string, char> reverseCodes;
    std::string line;
    while (std::getline(inFile, line)) {
        if (line.empty()) continue;
        size_t pos = line.find(':');
        if (pos != std::string::npos) {
            std::string code = line.substr(0, pos);
            char ch = line[pos + 1];
            reverseCodes[code] = ch;
        }
    }
    inFile.close();

    std::string decoded = "";
    std::string current = "";
    for (char bit : encoded) {
        current += bit;
        if (reverseCodes.find(current) != reverseCodes.end()) {
            decoded += reverseCodes[current];
            current = "";
        }
    }

    std::string nativeOutput = msclr::interop::marshal_as<std::string>(outputFilename);
    std::ofstream outFile(nativeOutput);
    outFile << decoded;
    outFile.close();

    return gcnew String(decoded.c_str());
}

void MyForm3::SetupDataGridViews() {
    dataGridView1->Columns->Add("number", L"№");
    dataGridView1->Columns->Add("name", L"Назва");
    dataGridView1->Columns->Add("flavor", L"Смак");
    dataGridView1->Columns->Add("salePrice", L"Ціна продажу");
    dataGridView1->Columns->Add("available", L"Наявність");
    dataGridView1->Columns["number"]->Width = 30;
    dataGridView1->Columns["name"]->Width = 150;
    dataGridView1->Columns["flavor"]->Width = 150;
    dataGridView1->Columns["salePrice"]->Width = 100;
    dataGridView1->Columns["available"]->Width = 100;

    dataGridView2->Columns->Add("symbol", L"Символ");
    dataGridView2->Columns->Add("code", L"Код");
    dataGridView2->Columns["symbol"]->Width = 80;
    dataGridView2->Columns["code"]->Width = 400;
}

void MyForm3::DisplayDrinks() {
    dataGridView1->Rows->Clear();
    auto drinksList = truck->GetDrinks();
    for (int i = 0; i < drinksList->Count; i++) {
        auto drink = drinksList[i];
        dataGridView1->Rows->Add(
            (i + 1).ToString(),
            drink["name"]->ToString(),
            drink["flavor"]->ToString(),
            String::Format(L"{0:F2}", drink["salePrice"]),
            drink["available"]->ToString()
        );
    }
}

void MyForm3::DisplayHuffmanResults(String^ encodedText, Dictionary<String^, Char>^ codes) {
    dataGridView2->Rows->Clear();
    for each (KeyValuePair<String^, Char> ^ pair in codes) {
        dataGridView2->Rows->Add(
            pair->Value.ToString(),
            pair->Key
        );
    }
}

System::Void MyForm3::button1_Click(System::Object^ sender, System::EventArgs^ e) {
    try {
        int option = Convert::ToInt32(numericUpDown1->Value);
        switch (option) {
        case 1:
        {
            if (textBox2->Text->Length == 0 || textBox3->Text->Length == 0) {
                MessageBox::Show(L"Будь ласка, введіть місткість вантажівки та ціну закупівлі");
                return;
            }
            int capacity = Convert::ToInt32(textBox2->Text);
            double purchaseCost = Convert::ToDouble(textBox3->Text);
            int maxFlavor = 0;
            if (textBox4->Text->Length > 0) {
                maxFlavor = Convert::ToInt32(textBox4->Text);
            }
            truck->SetInitialData(capacity, purchaseCost, maxFlavor);
            MessageBox::Show(L"Початкові дані встановлено");
            DisplayDrinks();
        }
        break;
        case 2:
        {
            if (textBox7->Text->Length == 0 || textBox6->Text->Length == 0 ||
                textBox5->Text->Length == 0 || textBox8->Text->Length == 0) {
                MessageBox::Show(L"Будь ласка, заповніть всі поля для напою");
                return;
            }
            truck->AddDrink(
                textBox7->Text,
                textBox6->Text,
                Convert::ToDouble(textBox5->Text),
                Convert::ToInt32(textBox8->Text)
            );
            MessageBox::Show(L"Напій додано");
            DisplayDrinks();
        }
        break;
        case 3:
        {
            if (textBox1->Text->Length == 0) {
                MessageBox::Show(L"Будь ласка, введіть номер запису для редагування");
                return;
            }
            int index = Convert::ToInt32(textBox1->Text) - 1;
            if (index < 0 || index >= truck->GetDrinks()->Count) {
                MessageBox::Show(L"Некоректний номер запису");
                return;
            }
            if (textBox7->Text->Length == 0 || textBox6->Text->Length == 0 ||
                textBox5->Text->Length == 0 || textBox8->Text->Length == 0) {
                MessageBox::Show(L"Будь ласка, заповніть всі поля для напою");
                return;
            }
            truck->EditDrink(
                index,
                textBox7->Text,
                textBox6->Text,
                Convert::ToDouble(textBox5->Text),
                Convert::ToInt32(textBox8->Text)
            );
            MessageBox::Show(L"Запис оновлено");
            DisplayDrinks();
        }
        break;
        case 4:
        {
            if (textBox1->Text->Length == 0) {
                MessageBox::Show(L"Будь ласка, введіть номер запису для видалення");
                return;
            }
            int index = Convert::ToInt32(textBox1->Text) - 1;
            if (index < 0 || index >= truck->GetDrinks()->Count) {
                MessageBox::Show(L"Некоректний номер запису");
                return;
            }
            truck->DeleteDrink(index);
            MessageBox::Show(L"Запис видалено");
            DisplayDrinks();
        }
        break;
        case 5:
            DisplayDrinks();
            break;
        case 6:
        {
            try {
                auto result = truck->SolveGreedy();
                auto assignments = result->Item1;
                double totalProfit = result->Item2;
                double totalRevenue = result->Item3;
                double totalCost = result->Item4;
                int remaining = result->Item5;

                dataGridView1->Rows->Clear();
                for (int i = 0; i < assignments->Count; i++) {
                    auto row = assignments[i];
                    dataGridView1->Rows->Add(
                        (i + 1).ToString(),
                        row["name"]->ToString(),
                        row["flavor"]->ToString(),
                        String::Format(L"{0:F2}", row["salePrice"]),
                        row["take"]->ToString() + L" діжок"
                    );
                }

                String^ message = String::Format(
                    L"Загальний прибуток: {0:F2} грн\nЗагальна виручка: {1:F2} грн\n"
                    L"Загальна собівартість: {2:F2} грн\nЗалишилось місця: {3} діжок",
                    totalProfit, totalRevenue, totalCost, remaining
                );
                MessageBox::Show(message, L"Результати розрахунку");

                DisplayDrinks();
            }
            catch (Exception^ ex) {
                MessageBox::Show(L"Помилка при розрахунку: " + ex->Message);
            }
        }
        break;
        case 7:
        {
            if (numericUpDown2->Value < 0) {
                MessageBox::Show(L"Обмеження не може бути від'ємним");
                return;
            }
            truck->SetFlavorLimit(Convert::ToInt32(numericUpDown2->Value));
            MessageBox::Show(L"Обмеження оновлено");
        }
        break;
        case 0:
            this->Close();
            break;
        default:
            MessageBox::Show(L"Некоректний вибір");
            break;
        }
    }
    catch (FormatException^) {
        MessageBox::Show(L"Помилка формату даних. Перевірте введені значення.");
    }
    catch (Exception^ ex) {
        MessageBox::Show(L"Помилка: " + ex->Message);
    }
}

System::Void MyForm3::button3_Click(System::Object^ sender, System::EventArgs^ e) {
    try {
        if (textBox7->Text->Length == 0 || textBox6->Text->Length == 0 ||
            textBox5->Text->Length == 0 || textBox8->Text->Length == 0) {
            MessageBox::Show(L"Будь ласка, заповніть всі поля для напою");
            return;
        }
        truck->AddDrink(
            textBox7->Text,
            textBox6->Text,
            Convert::ToDouble(textBox5->Text),
            Convert::ToInt32(textBox8->Text)
        );
        MessageBox::Show(L"Напій додано");
        DisplayDrinks();
    }
    catch (Exception^ ex) {
        MessageBox::Show(L"Помилка: " + ex->Message);
    }
}

System::Void MyForm3::button2_Click(System::Object^ sender, System::EventArgs^ e) {
    try {
        truck->SetFlavorLimit(Convert::ToInt32(numericUpDown2->Value));
        MessageBox::Show(L"Обмеження оновлено");
    }
    catch (Exception^ ex) {
        MessageBox::Show(L"Помилка: " + ex->Message);
    }
}


System::Void MyForm3::button5_Click(System::Object^ sender, System::EventArgs^ e) {
    try {
        auto result = truck->SolveGreedy();
        auto assignments = result->Item1;
        double totalProfit = result->Item2;
        double totalRevenue = result->Item3;
        double totalCost = result->Item4;
        int remaining = result->Item5;

        dataGridView1->Rows->Clear();
        for (int i = 0; i < assignments->Count; i++) {
            auto row = assignments[i];
            dataGridView1->Rows->Add(
                (i + 1).ToString(),
                row["name"]->ToString(),
                row["flavor"]->ToString(),
                String::Format(L"{0:F2}", row["salePrice"]),
                row["take"]->ToString() + L" діжок"
            );
        }

        String^ message = String::Format(
            L"Загальний прибуток: {0:F2} грн\nЗагальна виручка: {1:F2} грн\n"
            L"Загальна собівартість: {2:F2} грн\nЗалишилось місця: {3} діжок",
            totalProfit, totalRevenue, totalCost, remaining
        );
        MessageBox::Show(message, L"Результати розрахунку");

        DisplayDrinks();
    }
    catch (Exception^ ex) {
        MessageBox::Show(L"Помилка при розрахунку: " + ex->Message);
    }
}

System::Void MyForm3::numericUpDown1_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
    int option = Convert::ToInt32(numericUpDown1->Value);
    textBox2->Visible = false;
    textBox3->Visible = false;
    textBox4->Visible = false;
    textBox7->Visible = false;
    textBox6->Visible = false;
    textBox5->Visible = false;
    textBox8->Visible = false;
    button3->Visible = false;
    textBox1->Visible = false;

    switch (option) {
    case 1:
        textBox2->Visible = true;
        textBox3->Visible = true;
        textBox4->Visible = true;
        break;
    case 2:
    case 3:
        textBox7->Visible = true;
        textBox6->Visible = true;
        textBox5->Visible = true;
        textBox8->Visible = true;
        button3->Visible = true;
        if (option == 3) {
            textBox1->Visible = true;
        }
        break;
    case 4:
        textBox1->Visible = true;
        break;
    case 7:
        numericUpDown2->Visible = true;
        button2->Visible = true;
        break;
    }
}

System::Void MyForm3::numericUpDown3_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
    int option = Convert::ToInt32(numericUpDown3->Value);
    switch (option) {
    case 0:
        label15->Text = L"0. Вихід";
        break;
    case 1:
        label15->Text = L"1. Стиснути дані з файлу 'input.txt'";
        break;
    case 2:
        label15->Text = L"2. Розкодувати дані з файлу 'compressed.txt'";
        break;
    default:
        label15->Text = L"Некоректний вибір";
        break;
    }
}

System::Void MyForm3::button6_Click(System::Object^ sender, System::EventArgs^ e) {
    try {
        int option = Convert::ToInt32(numericUpDown3->Value);
        if (option == 1) {
            auto result = compressor->Compress(L"input.txt", L"compressed.txt");
            String^ encodedText = result->Item1;
            double originalSize = result->Item2;
            double compressedSize = result->Item3;
            double ratio = result->Item4;

            String^ message = String::Format(
                L"Розмір оригіналу: {0} байт\n"
                L"Розмір стиснутого: ~{1} байт\n"
                L"Коефіцієнт стиснення: {2:F2}x\n"
                L"Результат збережено у 'compressed.txt'",
                originalSize, compressedSize, ratio
            );
            MessageBox::Show(message, L"Стиснення завершено");
        }
        else if (option == 2) {
            String^ decodedText = compressor->Decompress(L"compressed.txt", L"decoded.txt");
            MessageBox::Show(
                L"Декодований текст збережено у 'decoded.txt'\n" +
                decodedText->Substring(0, Math::Min(200, decodedText->Length)) +
                (decodedText->Length > 200 ? L"..." : L""),
                L"Розкодування завершено"
            );
        }
        else if (option == 0) {
            this->Close();
        }
        else {
            MessageBox::Show(L"Некоректний вибір. Виберіть 0, 1 або 2.");
        }
    }
    catch (Exception^ ex) {
        MessageBox::Show(L"Помилка: " + ex->Message);
    }
}
