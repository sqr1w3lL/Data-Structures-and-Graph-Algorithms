#include "MyForm2.h"
#include <msclr/marshal_cppstd.h>

using namespace Finals;
using namespace System;
using namespace System::Windows::Forms;

System::Void MyForm2::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
    int option = (int)numericUpDown1->Value;
    dataGridView1->Rows->Clear();
    dataGridView1->Columns->Clear();

    switch (option)
    {
    case 1:
        hashTable->LoadFromFile("taxpayers.txt");
        MessageBox::Show("Завантажено з taxpayers.txt");
        break;
    case 2:
        try {
            int num = Int32::Parse(textBox2->Text);
            String^ s = textBox3->Text;
            String^ n = textBox7->Text;
            String^ f = textBox6->Text;
            hashTable->Insert(num, s, n, f);
            MessageBox::Show("Платника додано");
        }
        catch (...) { MessageBox::Show("Помилка вводу"); }
        break;
    case 3:
        try {
            int num = Int32::Parse(textBox10->Text);
            hashTable->Remove(num);
            MessageBox::Show("Видалено");
        }
        catch (...) { MessageBox::Show("Помилка вводу"); }
        break;
    case 4:
        try {
            int num = Int32::Parse(textBox10->Text);
            auto res = hashTable->Search(num);
            if (res != nullptr) {
                MessageBox::Show("Знайдено:\n" +
                    res->regNumber.ToString() + " " +
                    res->surname + " " +
                    res->name + " " +
                    res->fathername);
            }
            else {
                MessageBox::Show("Не знайдено");
            }
        }
        catch (...) { MessageBox::Show("Помилка вводу"); }
        break;
    case 5:
    {
        dataGridView1->Columns->Add("Idx", "Індекс");
        dataGridView1->Columns->Add("State", "Стан");
        dataGridView1->Columns->Add("Reg", "Рег. №");
        dataGridView1->Columns->Add("S", "Прізвище");
        dataGridView1->Columns->Add("N", "Ім'я");
        dataGridView1->Columns->Add("F", "По батькові");

        auto snapshot = hashTable->GetOccupiedSlots();
        for each (auto pair in snapshot) {
            String^ state = "OCCUPIED";
            dataGridView1->Rows->Add(
                pair.Key.ToString(),
                state,
                pair.Value.regNumber.ToString(),
                pair.Value.surname,
                pair.Value.name,
                pair.Value.fathername
            );
        }
    }
    break;
    case 0:
        this->Close();
        break;
    default:
        MessageBox::Show("Невірна опція");
    }
}

System::Void MyForm2::button2_Click(System::Object^ sender, System::EventArgs^ e)
{
    int option = (int)numericUpDown2->Value;
    dataGridView2->Rows->Clear();
    dataGridView2->Columns->Clear();

    switch (option)
    {
    case 1:
        binaryTree->LoadFromFile("students.txt");
        MessageBox::Show("Завантажено з students.txt");
        break;
    case 2:
        try {
            int code = Int32::Parse(textBox11->Text);
            String^ s = textBox5->Text;
            String^ i = textBox4->Text;
            String^ g = textBox1->Text;
            double m;
            if (!Double::TryParse(textBox9->Text, m)) {
                MessageBox::Show("Невірний формат середнього балу");
                return;
            }
            binaryTree->Insert(code, s, i, g, m);
            MessageBox::Show("Студента додано");
        }
        catch (...) { MessageBox::Show("Помилка вводу"); }
        break;
    case 3:
        try {
            int code = Int32::Parse(textBox8->Text);
            binaryTree->Remove(code);
            MessageBox::Show("Видалено");
        }
        catch (...) { MessageBox::Show("Помилка вводу"); }
        break;
    case 4:
        try {
            int code = Int32::Parse(textBox8->Text);
            auto res = binaryTree->Search(code);
            if (res.HasValue) {
                auto s = res.Value;
                MessageBox::Show("Знайдено:\n" +
                    s.code.ToString() + " " +
                    s.surname + " " +
                    s.initials + " " +
                    s.group + " " +
                    s.avgMark.ToString("F2"));
            }
            else MessageBox::Show("Не знайдено");
        }
        catch (...) { MessageBox::Show("Помилка вводу"); }
        break;
    case 5:
    {
        dataGridView2->Columns->Add("Tree", "Структура дерева");
        auto lines = binaryTree->GetTreeStructure();
        for each (String ^ line in lines)
            dataGridView2->Rows->Add(line);
    }
    break;
    case 6:
    {
        dataGridView2->Columns->Add("Code", "Код");
        dataGridView2->Columns->Add("S", "Прізвище");
        dataGridView2->Columns->Add("I", "Ініціали");
        dataGridView2->Columns->Add("G", "Група");
        dataGridView2->Columns->Add("Avg", "Середній бал");

        auto best = binaryTree->FindBestStudents();
        for each (auto s in best) {
            dataGridView2->Rows->Add(
                s.code.ToString(),
                s.surname,
                s.initials,
                s.group,
                s.avgMark.ToString("F2")
            );
        }
    }
    break;
    case 7:
    {
        dataGridView2->Columns->Add("Code", "Код");
        dataGridView2->Columns->Add("S", "Прізвище");
        dataGridView2->Columns->Add("I", "Ініціали");
        dataGridView2->Columns->Add("G", "Група");
        dataGridView2->Columns->Add("Avg", "Середній бал");

        auto worst = binaryTree->FindWorstStudents();
        for each (auto s in worst) {
            dataGridView2->Rows->Add(
                s.code.ToString(),
                s.surname,
                s.initials,
                s.group,
                s.avgMark.ToString("F2")
            );
        }
    }
    break;
    case 0:
        this->Close();
        break;
    default:
        MessageBox::Show("Невірна опція");
    }
}

System::Void MyForm2::button3_Click(System::Object^ sender, System::EventArgs^ e) {
    try {
        int num = Int32::Parse(textBox10->Text);
        hashTable->Remove(num);
        MessageBox::Show("Видалено з геш-таблиці");
    }
    catch (...) { MessageBox::Show("Помилка вводу"); }
}

System::Void MyForm2::button4_Click(System::Object^ sender, System::EventArgs^ e) {
    try {
        int num = Int32::Parse(textBox2->Text);
        String^ s = textBox3->Text;
        String^ n = textBox7->Text;
        String^ f = textBox6->Text;
        hashTable->Insert(num, s, n, f);
        MessageBox::Show("Додано в геш-таблицю");
    }
    catch (...) { MessageBox::Show("Помилка вводу"); }
}

System::Void MyForm2::button5_Click(System::Object^ sender, System::EventArgs^ e) {
    try {
        int newSize = (int)numericUpDown3->Value;
        hashTable->ChangeSize(newSize);
        MessageBox::Show("Розмір геш-таблиці змінено на " + newSize.ToString());
    }
    catch (...) { MessageBox::Show("Помилка"); }
}

System::Void MyForm2::button6_Click(System::Object^ sender, System::EventArgs^ e) {
    try {
        int code = Int32::Parse(textBox8->Text);
        binaryTree->Remove(code);
        MessageBox::Show("Видалено з бінарного дерева");
    }
    catch (...) { MessageBox::Show("Помилка вводу"); }
}

System::Void MyForm2::button7_Click(System::Object^ sender, System::EventArgs^ e) {
    try {
        int code = Int32::Parse(textBox11->Text);
        String^ s = textBox5->Text;
        String^ i = textBox4->Text;
        String^ g = textBox1->Text;
        double m;
        if (!Double::TryParse(textBox9->Text, m)) {
            MessageBox::Show("Невірний формат середнього балу");
            return;
        }
        binaryTree->Insert(code, s, i, g, m);
        MessageBox::Show("Додано в бінарне дерево");
    }
    catch (...) { MessageBox::Show("Помилка вводу"); }
}
