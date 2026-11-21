#pragma once
#include "data.h"
#include "MyForm2.h" 
#include "MyForm3.h"
#include "MyForm4.h" 
#include "MyForm5.h" 
#include "MyForm6.h" 
#include "MyForm7.h" 
#include <msclr/marshal_cppstd.h>
#include <vector>
#include <map>
#include <sstream>
using namespace System::Drawing;
using namespace System::Windows::Forms;

namespace Finals {
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class MyForm : public Form
    {
    private:
        ::LinkedList* m_salesList;
        std::map<std::string, double>* m_cashierSales;
    private: System::Windows::Forms::Label^ label12;
    private: System::Windows::Forms::ToolStripMenuItem^ жадібніАлгоритмиToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ динамічнеПрограмуванняToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ алгоритмиОбходуГрафаToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ алгоритмиПошукуНайкоротшихШляхівУГрафіToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ моделюванняТранспортноїМережіЗаДопомогоюГрафівToolStripMenuItem;

           PriorityQueue* m_priorityQueue;

           void UpdateCashierStatistics()
           {
               delete m_cashierSales;
               m_cashierSales = new std::map<std::string, double>();

               Node* current = m_salesList->getHead();
               while (current != nullptr) {
                   double finalPrice = current->data.quantity * current->data.pricePerUnit * (1 - current->data.discount);
                   (*m_cashierSales)[current->data.cashier] += finalPrice;
                   current = current->next;
               }

               delete m_priorityQueue;
               m_priorityQueue = new PriorityQueue();

               for (const auto& pair : *m_cashierSales) {
                   m_priorityQueue->insert(PriorityQueue::CashierInfo(pair.first, pair.second));
               }
           }

    public:
        MyForm(void)
        {
            InitializeComponent();
            m_salesList = new ::LinkedList();
            m_salesList->loadFromFile("data.txt");
            m_cashierSales = new std::map<std::string, double>();
            m_priorityQueue = new PriorityQueue();
            UpdateCashierStatistics();
        }

    protected:
        ~MyForm()
        {
            delete m_salesList;
            delete m_cashierSales;
            delete m_priorityQueue;
            if (components)
            {
                delete components;
            }
        }

    private:
        System::Windows::Forms::MenuStrip^ menuStrip1;
        System::Windows::Forms::ToolStripMenuItem^ менюToolStripMenuItem;
        System::Windows::Forms::ToolStripMenuItem^ вихідToolStripMenuItem1;
        System::Windows::Forms::ToolStripMenuItem^ лінійніСтруктуриДанихToolStripMenuItem;
        System::Windows::Forms::ToolStripMenuItem^ дереваТаГештаблиціToolStripMenuItem;
        System::Windows::Forms::Label^ label1;
        System::Windows::Forms::DataGridView^ dataGridView1;
        System::Windows::Forms::Label^ label2;
        System::Windows::Forms::NumericUpDown^ numericUpDown1;
        System::Windows::Forms::Button^ button1;
        System::Windows::Forms::Label^ label3;
        System::Windows::Forms::Label^ label4;
        System::Windows::Forms::Label^ label5;
        System::Windows::Forms::Label^ label6;
        System::Windows::Forms::Label^ label7;
        System::Windows::Forms::Label^ label8;
        System::Windows::Forms::Label^ label9;
        System::Windows::Forms::Label^ label10;
        System::Windows::Forms::Label^ label11;
        System::Windows::Forms::TextBox^ textBox1;
        System::Windows::Forms::Button^ button2;
        System::Windows::Forms::TextBox^ textBox2;
        System::Windows::Forms::TextBox^ textBox3;
        System::Windows::Forms::TextBox^ textBox4;
        System::Windows::Forms::TextBox^ textBox5;
        System::Windows::Forms::TextBox^ textBox6;
        System::Windows::Forms::TextBox^ textBox7;
        System::Windows::Forms::TextBox^ textBox8;
        System::Windows::Forms::Button^ button3;
        System::ComponentModel::IContainer^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
            this->менюToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->вихідToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->лінійніСтруктуриДанихToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->дереваТаГештаблиціToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->жадібніАлгоритмиToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->динамічнеПрограмуванняToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->алгоритмиОбходуГрафаToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->алгоритмиПошукуНайкоротшихШляхівУГрафіToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->моделюванняТранспортноїМережіЗаДопомогоюГрафівToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
            this->button1 = (gcnew System::Windows::Forms::Button());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->label4 = (gcnew System::Windows::Forms::Label());
            this->label5 = (gcnew System::Windows::Forms::Label());
            this->label6 = (gcnew System::Windows::Forms::Label());
            this->label7 = (gcnew System::Windows::Forms::Label());
            this->label8 = (gcnew System::Windows::Forms::Label());
            this->label9 = (gcnew System::Windows::Forms::Label());
            this->label10 = (gcnew System::Windows::Forms::Label());
            this->label11 = (gcnew System::Windows::Forms::Label());
            this->textBox1 = (gcnew System::Windows::Forms::TextBox());
            this->button2 = (gcnew System::Windows::Forms::Button());
            this->textBox2 = (gcnew System::Windows::Forms::TextBox());
            this->textBox3 = (gcnew System::Windows::Forms::TextBox());
            this->textBox4 = (gcnew System::Windows::Forms::TextBox());
            this->textBox5 = (gcnew System::Windows::Forms::TextBox());
            this->textBox6 = (gcnew System::Windows::Forms::TextBox());
            this->textBox7 = (gcnew System::Windows::Forms::TextBox());
            this->textBox8 = (gcnew System::Windows::Forms::TextBox());
            this->button3 = (gcnew System::Windows::Forms::Button());
            this->label12 = (gcnew System::Windows::Forms::Label());
            this->menuStrip1->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
            this->SuspendLayout();

            this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(8) {
                this->менюToolStripMenuItem,
                    this->лінійніСтруктуриДанихToolStripMenuItem, this->дереваТаГештаблиціToolStripMenuItem, this->жадібніАлгоритмиToolStripMenuItem,
                    this->динамічнеПрограмуванняToolStripMenuItem, this->алгоритмиОбходуГрафаToolStripMenuItem, this->алгоритмиПошукуНайкоротшихШляхівУГрафіToolStripMenuItem,
                    this->моделюванняТранспортноїМережіЗаДопомогоюГрафівToolStripMenuItem
            });
            this->menuStrip1->Location = System::Drawing::Point(0, 0);
            this->menuStrip1->Name = L"menuStrip1";
            this->menuStrip1->Size = System::Drawing::Size(1653, 24);
            this->menuStrip1->TabIndex = 0;
            this->menuStrip1->Text = L"menuStrip1";

            this->менюToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->вихідToolStripMenuItem1 });
            this->менюToolStripMenuItem->Name = L"менюToolStripMenuItem";
            this->менюToolStripMenuItem->Size = System::Drawing::Size(53, 20);
            this->менюToolStripMenuItem->Text = L"Меню";

            this->вихідToolStripMenuItem1->Name = L"вихідToolStripMenuItem1";
            this->вихідToolStripMenuItem1->Size = System::Drawing::Size(102, 22);
            this->вихідToolStripMenuItem1->Text = L"Вихід";
            this->вихідToolStripMenuItem1->Click += gcnew System::EventHandler(this, &MyForm::вихідToolStripMenuItem1_Click);

            this->лінійніСтруктуриДанихToolStripMenuItem->Name = L"лінійніСтруктуриДанихToolStripMenuItem";
            this->лінійніСтруктуриДанихToolStripMenuItem->Size = System::Drawing::Size(149, 20);
            this->лінійніСтруктуриДанихToolStripMenuItem->Text = L"Лінійні структури даних";

            this->дереваТаГештаблиціToolStripMenuItem->Name = L"дереваТаГештаблиціToolStripMenuItem";
            this->дереваТаГештаблиціToolStripMenuItem->Size = System::Drawing::Size(145, 20);
            this->дереваТаГештаблиціToolStripMenuItem->Text = L"Дерева та Геш-таблиці";
            this->дереваТаГештаблиціToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::дереваТаГештаблиціToolStripMenuItem_Click);

            this->жадібніАлгоритмиToolStripMenuItem->Name = L"жадібніАлгоритмиToolStripMenuItem";
            this->жадібніАлгоритмиToolStripMenuItem->Size = System::Drawing::Size(125, 20);
            this->жадібніАлгоритмиToolStripMenuItem->Text = L"Жадібні алгоритми";
            this->жадібніАлгоритмиToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::ЖадібніалгоритмиToolStripMenuItem_Click);

            this->динамічнеПрограмуванняToolStripMenuItem->Name = L"динамічнеПрограмуванняToolStripMenuItem";
            this->динамічнеПрограмуванняToolStripMenuItem->Size = System::Drawing::Size(168, 20);
            this->динамічнеПрограмуванняToolStripMenuItem->Text = L"Динамічне програмування";
            this->динамічнеПрограмуванняToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::динамічнеПрограмуванняToolStripMenuItem_Click);

            this->алгоритмиОбходуГрафаToolStripMenuItem->Name = L"алгоритмиОбходуГрафаToolStripMenuItem";
            this->алгоритмиОбходуГрафаToolStripMenuItem->Size = System::Drawing::Size(158, 20);
            this->алгоритмиОбходуГрафаToolStripMenuItem->Text = L"Алгоритми обходу графа";
            this->алгоритмиОбходуГрафаToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::алгоритмиОбходуГрафаToolStripMenuItem_Click);

            this->алгоритмиПошукуНайкоротшихШляхівУГрафіToolStripMenuItem->Name = L"алгоритмиПошукуНайкоротшихШляхівУГрафіToolStripMenuItem";
            this->алгоритмиПошукуНайкоротшихШляхівУГрафіToolStripMenuItem->Size = System::Drawing::Size(288, 20);
            this->алгоритмиПошукуНайкоротшихШляхівУГрафіToolStripMenuItem->Text = L"Алгоритми пошуку найкоротших шляхів у графі";
            this->алгоритмиПошукуНайкоротшихШляхівУГрафіToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::алгоритмиПошукуНайкоротшихШляхівУГрафіToolStripMenuItem_Click);

            this->моделюванняТранспортноїМережіЗаДопомогоюГрафівToolStripMenuItem->Name = L"моделюванняТранспортноїМережіЗаДопомогоюГрафівToolStripMenuItem";
            this->моделюванняТранспортноїМережіЗаДопомогоюГрафівToolStripMenuItem->Size = System::Drawing::Size(339, 20);
            this->моделюванняТранспортноїМережіЗаДопомогоюГрафівToolStripMenuItem->Text = L"Моделювання транспортної мережі за допомогою графів";
            this->моделюванняТранспортноїМережіЗаДопомогоюГрафівToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::моделюванняТранспортноїМережіЗаДопомогоюГрафівToolStripMenuItem_Click);

            this->label1->AutoSize = true;
            this->label1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 24, System::Drawing::FontStyle::Bold));
            this->label1->Location = System::Drawing::Point(12, 53);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(256, 36);
            this->label1->TabIndex = 1;
            this->label1->Text = L"Виберіть опцію: ";

            this->dataGridView1->Location = System::Drawing::Point(604, 72);
            this->dataGridView1->Name = L"dataGridView1";
            this->dataGridView1->Size = System::Drawing::Size(749, 413);
            this->dataGridView1->TabIndex = 2;

            this->label2->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label2->Location = System::Drawing::Point(14, 137);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(417, 42);
            this->label2->TabIndex = 34;
            this->label2->Text = L"1. Вивести список продажів";

            this->numericUpDown1->Location = System::Drawing::Point(18, 95);
            this->numericUpDown1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
            this->numericUpDown1->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
            this->numericUpDown1->Name = L"numericUpDown1";
            this->numericUpDown1->Size = System::Drawing::Size(38, 20);
            this->numericUpDown1->TabIndex = 4;
            this->numericUpDown1->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });

            this->button1->Location = System::Drawing::Point(99, 92);
            this->button1->Name = L"button1";
            this->button1->Size = System::Drawing::Size(91, 23);
            this->button1->TabIndex = 5;
            this->button1->Text = L"Підтвердити";
            this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click_1);

            this->label3->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label3->Location = System::Drawing::Point(14, 158);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(417, 42);
            this->label3->TabIndex = 33;
            this->label3->Text = L"2. Вивести касирів за сумарними продажами";

            this->label4->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label4->Location = System::Drawing::Point(14, 182);
            this->label4->Name = L"label4";
            this->label4->Size = System::Drawing::Size(417, 42);
            this->label4->TabIndex = 32;
            this->label4->Text = L"3. Знайти найкращого продавця";

            this->label5->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label5->Location = System::Drawing::Point(14, 202);
            this->label5->Name = L"label5";
            this->label5->Size = System::Drawing::Size(417, 42);
            this->label5->TabIndex = 31;
            this->label5->Text = L"4. Вивести список продажів у зворотньому порядку";

            this->label6->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label6->Location = System::Drawing::Point(14, 225);
            this->label6->Name = L"label6";
            this->label6->Size = System::Drawing::Size(417, 42);
            this->label6->TabIndex = 30;
            this->label6->Text = L"5. Протестувати пірамідальне сортування";

            this->label7->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label7->Location = System::Drawing::Point(14, 245);
            this->label7->Name = L"label7";
            this->label7->Size = System::Drawing::Size(417, 42);
            this->label7->TabIndex = 29;
            this->label7->Text = L"6. Зберегти дані у файл";

            this->label8->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label8->Location = System::Drawing::Point(14, 265);
            this->label8->Name = L"label8";
            this->label8->Size = System::Drawing::Size(417, 42);
            this->label8->TabIndex = 28;
            this->label8->Text = L"7. Видалити один продаж певного касира зі списку";

            this->label9->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label9->Location = System::Drawing::Point(14, 288);
            this->label9->Name = L"label9";
            this->label9->Size = System::Drawing::Size(417, 42);
            this->label9->TabIndex = 27;
            this->label9->Text = L"8. Видалити всі продажі певного касира зі статистики";

            this->label10->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label10->Location = System::Drawing::Point(14, 310);
            this->label10->Name = L"label10";
            this->label10->Size = System::Drawing::Size(417, 42);
            this->label10->TabIndex = 26;
            this->label10->Text = L"9. Додати новий продаж існуючого касира";

            this->label11->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label11->Location = System::Drawing::Point(14, 331);
            this->label11->Name = L"label11";
            this->label11->Size = System::Drawing::Size(417, 42);
            this->label11->TabIndex = 25;
            this->label11->Text = L"10. Вихід";
            this->label11->Click += gcnew System::EventHandler(this, &MyForm::label11_Click);

            this->textBox1->Location = System::Drawing::Point(619, 494);
            this->textBox1->Name = L"textBox1";
            this->textBox1->Size = System::Drawing::Size(100, 20);
            this->textBox1->TabIndex = 15;
            this->textBox1->Text = L"Введіть ім\'я";

            this->button2->Location = System::Drawing::Point(725, 494);
            this->button2->Name = L"button2";
            this->button2->Size = System::Drawing::Size(75, 23);
            this->button2->TabIndex = 16;
            this->button2->Text = L"Ввести";
            this->button2->UseVisualStyleBackColor = true;

            this->textBox2->Location = System::Drawing::Point(903, 490);
            this->textBox2->Name = L"textBox2";
            this->textBox2->Size = System::Drawing::Size(100, 20);
            this->textBox2->TabIndex = 17;
            this->textBox2->Text = L"Введіть ім\'я касира, після якого додати запис";

            this->textBox3->Location = System::Drawing::Point(903, 516);
            this->textBox3->Name = L"textBox3";
            this->textBox3->Size = System::Drawing::Size(100, 20);
            this->textBox3->TabIndex = 18;
            this->textBox3->Text = L"Назва продукту";

            this->textBox4->Location = System::Drawing::Point(903, 541);
            this->textBox4->Name = L"textBox4";
            this->textBox4->Size = System::Drawing::Size(100, 20);
            this->textBox4->TabIndex = 19;
            this->textBox4->Text = L"Кількість";

            this->textBox5->Location = System::Drawing::Point(1009, 541);
            this->textBox5->Name = L"textBox5";
            this->textBox5->Size = System::Drawing::Size(100, 20);
            this->textBox5->TabIndex = 22;
            this->textBox5->Text = L"Час";

            this->textBox6->Location = System::Drawing::Point(1009, 516);
            this->textBox6->Name = L"textBox6";
            this->textBox6->Size = System::Drawing::Size(100, 20);
            this->textBox6->TabIndex = 21;
            this->textBox6->Text = L"Дисконт";

            this->textBox7->Location = System::Drawing::Point(1009, 490);
            this->textBox7->Name = L"textBox7";
            this->textBox7->Size = System::Drawing::Size(100, 20);
            this->textBox7->TabIndex = 20;
            this->textBox7->Text = L"Ціна за одиницю";

            this->textBox8->Location = System::Drawing::Point(1115, 516);
            this->textBox8->Name = L"textBox8";
            this->textBox8->Size = System::Drawing::Size(100, 20);
            this->textBox8->TabIndex = 23;
            this->textBox8->Text = L"Новий запис касира";

            this->button3->Location = System::Drawing::Point(1221, 513);
            this->button3->Name = L"button3";
            this->button3->Size = System::Drawing::Size(75, 23);
            this->button3->TabIndex = 24;
            this->button3->Text = L"Ввести";
            this->button3->UseVisualStyleBackColor = true;
            this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);

            this->label12->AutoSize = true;
            this->label12->Font = (gcnew System::Drawing::Font(L"Times New Roman", 24, System::Drawing::FontStyle::Bold));
            this->label12->Location = System::Drawing::Point(811, 33);
            this->label12->Name = L"label12";
            this->label12->Size = System::Drawing::Size(366, 36);
            this->label12->TabIndex = 35;
            this->label12->Text = L"Лінійні структури даних";

            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(1653, 754);
            this->Controls->Add(this->label12);
            this->Controls->Add(this->button3);
            this->Controls->Add(this->textBox8);
            this->Controls->Add(this->textBox5);
            this->Controls->Add(this->textBox6);
            this->Controls->Add(this->textBox7);
            this->Controls->Add(this->textBox4);
            this->Controls->Add(this->textBox3);
            this->Controls->Add(this->textBox2);
            this->Controls->Add(this->button2);
            this->Controls->Add(this->textBox1);
            this->Controls->Add(this->label11);
            this->Controls->Add(this->label10);
            this->Controls->Add(this->label9);
            this->Controls->Add(this->label8);
            this->Controls->Add(this->label7);
            this->Controls->Add(this->label6);
            this->Controls->Add(this->label5);
            this->Controls->Add(this->label4);
            this->Controls->Add(this->label3);
            this->Controls->Add(this->button1);
            this->Controls->Add(this->numericUpDown1);
            this->Controls->Add(this->label2);
            this->Controls->Add(this->dataGridView1);
            this->Controls->Add(this->label1);
            this->Controls->Add(this->menuStrip1);
            this->MainMenuStrip = this->menuStrip1;
            this->Name = L"MyForm";
            this->Text = L"Самостійна робота";
            this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
            this->menuStrip1->ResumeLayout(false);
            this->menuStrip1->PerformLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion

    private:
        System::Void button1_Click_1(System::Object^ sender, System::EventArgs^ e) {
            int option = (int)numericUpDown1->Value;
            dataGridView1->Rows->Clear();
            dataGridView1->Columns->Clear();

            switch (option) {
            case 1:
            {
                dataGridView1->Columns->Add("Time", "Час");
                dataGridView1->Columns->Add("Product", "Продукт");
                dataGridView1->Columns->Add("Quantity", "Кількість");
                dataGridView1->Columns->Add("Price", "Ціна");
                dataGridView1->Columns->Add("Discount", "Дисконт (%)");
                dataGridView1->Columns->Add("Cashier", "Касир");

                Node* current = m_salesList->getHead();
                while (current != nullptr) {
                    auto& s = current->data;
                    dataGridView1->Rows->Add(
                        msclr::interop::marshal_as<String^>(s.time),
                        msclr::interop::marshal_as<String^>(s.product),
                        s.quantity.ToString(),
                        s.pricePerUnit.ToString("F2"),
                        (s.discount * 100).ToString("F1"),
                        msclr::interop::marshal_as<String^>(s.cashier)
                    );
                    current = current->next;
                }
            }
            break;

            case 2:
            {
                auto sorted = m_priorityQueue->sortUsingHeap();
                dataGridView1->Columns->Add("Cashier", "Касир");
                dataGridView1->Columns->Add("TotalSales", "Загальні продажі");
                for (const auto& ci : sorted) {
                    dataGridView1->Rows->Add(
                        msclr::interop::marshal_as<String^>(ci.name),
                        ci.totalSales.ToString("F2")
                    );
                }
            }
            break;

            case 3:
            {
                auto sorted = m_priorityQueue->sortUsingHeap();
                if (!sorted.empty()) {
                    auto& top = sorted[0];
                    MessageBox::Show("Найкращий продавець: " +
                        msclr::interop::marshal_as<String^>(top.name) + " (" +
                        top.totalSales.ToString("F2") + " грн.)", "Результат");
                }
            }
            break;

            case 4:
            {
                dataGridView1->Columns->Add("Time", "Час");
                dataGridView1->Columns->Add("Product", "Продукт");
                dataGridView1->Columns->Add("Quantity", "Кількість");
                dataGridView1->Columns->Add("Price", "Ціна");
                dataGridView1->Columns->Add("Discount", "Дисконт (%)");
                dataGridView1->Columns->Add("Cashier", "Касир");

                Node* current = m_salesList->getTail();
                while (current != nullptr) {
                    auto& s = current->data;
                    dataGridView1->Rows->Add(
                        msclr::interop::marshal_as<String^>(s.time),
                        msclr::interop::marshal_as<String^>(s.product),
                        s.quantity.ToString(),
                        s.pricePerUnit.ToString("F2"),
                        (s.discount * 100).ToString("F1"),
                        msclr::interop::marshal_as<String^>(s.cashier)
                    );
                    current = current->prev;
                }
            }
            break;

            case 5:
            {
                std::vector<PriorityQueue::CashierInfo> realData;
                Node* current = m_salesList->getHead();
                while (current != nullptr) {
                    double finalPrice = current->data.quantity * current->data.pricePerUnit * (1 - current->data.discount);
                    realData.push_back(PriorityQueue::CashierInfo(current->data.cashier, finalPrice));
                    current = current->next;
                }

                HeapSorter::sort(realData);

                dataGridView1->Columns->Add("Cashier", "Касир");
                dataGridView1->Columns->Add("Sales", "Продажі");

                for (const auto& ci : realData) {
                    dataGridView1->Rows->Add(
                        msclr::interop::marshal_as<String^>(ci.name),
                        ci.totalSales.ToString("F2")
                    );
                }
            }
            break;

            case 6:
                m_salesList->saveToFile("output.txt");
                MessageBox::Show("Дані збережено у файл output.txt", "Збережено");
                break;

            case 7:
            {
                auto cashierName = textBox1->Text;
                std::string nativeName = msclr::interop::marshal_as<std::string>(cashierName);
                m_salesList->removeNode(nativeName);
                UpdateCashierStatistics();
                MessageBox::Show("Продаж касира " + cashierName + " видалено.", "Видалено");
            }
            break;

            case 8:
            {
                auto cashierName = textBox1->Text;
                std::string nativeName = msclr::interop::marshal_as<std::string>(cashierName);

                m_cashierSales->erase(nativeName);
                m_priorityQueue->deleteElement(nativeName);

                MessageBox::Show("Касир " + cashierName + " видалений зі статистики.", "Видалено");
            }
            break;

            case 9:
                MessageBox::Show("Використовуйте форму нижче для додавання продажу.", "Інструкція");
                break;

            case 10:
                this->Close();
                break;

            default:
                MessageBox::Show("Неправильний вибір, спробуйте ще раз.", "Помилка");
                break;
            }
        }

        System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
            try {
                std::string targetCashier = msclr::interop::marshal_as<std::string>(textBox2->Text);
                std::string product = msclr::interop::marshal_as<std::string>(textBox3->Text);
                int quantity = System::Int32::Parse(textBox4->Text);
                double price = System::Double::Parse(textBox7->Text);
                double discount = System::Double::Parse(textBox6->Text);
                std::string time = msclr::interop::marshal_as<std::string>(textBox5->Text);
                std::string newCashier = msclr::interop::marshal_as<std::string>(textBox8->Text);

                bool found = false;
                Node* current = m_salesList->getHead();
                while (current != nullptr) {
                    if (current->data.cashier == targetCashier) {
                        found = true;
                        break;
                    }
                    current = current->next;
                }
                if (!found) {
                    MessageBox::Show("Касира '" + textBox2->Text + "' не знайдено.", "Помилка");
                    return;
                }

                Sale newSale(product, quantity, price, discount, newCashier, time);
                m_salesList->addAfter(targetCashier, newSale);
                UpdateCashierStatistics();
                MessageBox::Show("Новий продаж додано після касира " + textBox2->Text + ".", "Успіх");
            }
            catch (System::FormatException^) {
                MessageBox::Show("Помилка введення: переконайтеся, що кількість, ціна та дисконт — це числа.\n"
                    "Використовуйте крапку як десятковий розділювач (наприклад: 12.99).", "Невірний формат");
            }
            catch (System::Exception^ ex) {
                MessageBox::Show("Невідома помилка: " + ex->Message, "Помилка");
            }
        }

        System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
        }

        System::Void вихідToolStripMenuItem1_Click(System::Object^ sender, System::EventArgs^ e) {
            this->Close();
        }

        System::Void дереваТаГештаблиціToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
            Finals::MyForm2^ form2 = gcnew Finals::MyForm2();
            form2->Show();
        }
        System::Void ЖадібніалгоритмиToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
            Finals::MyForm3^ form3 = gcnew Finals::MyForm3();
            form3->Show();
        }
        System::Void динамічнеПрограмуванняToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
            Finals::MyForm4^ form4 = gcnew Finals::MyForm4();
            form4->Show();
        }
        System::Void алгоритмиОбходуГрафаToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
            Finals::MyForm5^ form5 = gcnew Finals::MyForm5();
            form5->Show();
        }
        System::Void алгоритмиПошукуНайкоротшихШляхівУГрафіToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
            Finals::MyForm6^ form6 = gcnew Finals::MyForm6();
            form6->Show();
        }
        System::Void моделюванняТранспортноїМережіЗаДопомогоюГрафівToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
            Finals::MyForm7^ form7 = gcnew Finals::MyForm7();
            form7->Show();
        }
        System::Void label11_Click(System::Object^ sender, System::EventArgs^ e) {
            this->Close();
        }
    };
}
