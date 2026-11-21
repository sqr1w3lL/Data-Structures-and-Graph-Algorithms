#pragma once

#include "ManagedStructs.h"
#include "ManagedHashTable.h"
#include "ManagedBinaryTree.h"
#include <msclr/marshal_cppstd.h>

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::ComponentModel;

namespace Finals {

    public ref class MyForm2 : public Form
    {
    private:
        ManagedHashTable^ hashTable;
        ManagedBinaryTree^ binaryTree;
        System::ComponentModel::Container^ components;

        Label^ label1;
        Label^ label2;
        Label^ label3;
        Label^ label4;
        Label^ label5;
        Label^ label6;
        Label^ label7;
        Label^ label8;
        Label^ label9;
        Label^ label10;
        Label^ label11;
        Label^ label12;
        Label^ label13;
        Label^ label14;
        Label^ label15;
        Label^ label16;
        Label^ label17;
        Label^ label18;
        Label^ label19;

        NumericUpDown^ numericUpDown1;
        NumericUpDown^ numericUpDown2;
        NumericUpDown^ numericUpDown3;

        Button^ button1;
        Button^ button2;
        Button^ button3;
        Button^ button4;
        Button^ button5;
        Button^ button6;
        Button^ button7;

        DataGridView^ dataGridView1;
        DataGridView^ dataGridView2;

        TextBox^ textBox1;
        TextBox^ textBox2;
        TextBox^ textBox3;
        TextBox^ textBox4;
        TextBox^ textBox5;
        TextBox^ textBox6;
        TextBox^ textBox7;
        TextBox^ textBox8;
        TextBox^ textBox9;
        TextBox^ textBox10;
        TextBox^ textBox11;

    public:
        MyForm2()
        {
            InitializeComponent();
            hashTable = gcnew ManagedHashTable(11);
            binaryTree = gcnew ManagedBinaryTree();
        }

    protected:
        ~MyForm2()
        {
            if (components)
            {
                delete components;
            }
        }

#pragma region Windows Form Designer generated code
        void InitializeComponent()
        {
            this->components = gcnew System::ComponentModel::Container();
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->label4 = (gcnew System::Windows::Forms::Label());
            this->label5 = (gcnew System::Windows::Forms::Label());
            this->label6 = (gcnew System::Windows::Forms::Label());
            this->label7 = (gcnew System::Windows::Forms::Label());
            this->label8 = (gcnew System::Windows::Forms::Label());
            this->label9 = (gcnew System::Windows::Forms::Label());
            this->label10 = (gcnew System::Windows::Forms::Label());
            this->label11 = (gcnew System::Windows::Forms::Label());
            this->label12 = (gcnew System::Windows::Forms::Label());
            this->label13 = (gcnew System::Windows::Forms::Label());
            this->label14 = (gcnew System::Windows::Forms::Label());
            this->label15 = (gcnew System::Windows::Forms::Label());
            this->label16 = (gcnew System::Windows::Forms::Label());
            this->label17 = (gcnew System::Windows::Forms::Label());
            this->label18 = (gcnew System::Windows::Forms::Label());
            this->label19 = (gcnew System::Windows::Forms::Label());
            this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
            this->numericUpDown2 = (gcnew System::Windows::Forms::NumericUpDown());
            this->numericUpDown3 = (gcnew System::Windows::Forms::NumericUpDown());
            this->button1 = (gcnew System::Windows::Forms::Button());
            this->button2 = (gcnew System::Windows::Forms::Button());
            this->button3 = (gcnew System::Windows::Forms::Button());
            this->button4 = (gcnew System::Windows::Forms::Button());
            this->button5 = (gcnew System::Windows::Forms::Button());
            this->button6 = (gcnew System::Windows::Forms::Button());
            this->button7 = (gcnew System::Windows::Forms::Button());
            this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
            this->dataGridView2 = (gcnew System::Windows::Forms::DataGridView());
            this->textBox1 = (gcnew System::Windows::Forms::TextBox());
            this->textBox2 = (gcnew System::Windows::Forms::TextBox());
            this->textBox3 = (gcnew System::Windows::Forms::TextBox());
            this->textBox4 = (gcnew System::Windows::Forms::TextBox());
            this->textBox5 = (gcnew System::Windows::Forms::TextBox());
            this->textBox6 = (gcnew System::Windows::Forms::TextBox());
            this->textBox7 = (gcnew System::Windows::Forms::TextBox());
            this->textBox8 = (gcnew System::Windows::Forms::TextBox());
            this->textBox9 = (gcnew System::Windows::Forms::TextBox());
            this->textBox10 = (gcnew System::Windows::Forms::TextBox());
            this->textBox11 = (gcnew System::Windows::Forms::TextBox());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown2))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown3))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->BeginInit();
            this->SuspendLayout();

            this->label1->AutoSize = true;
            this->label1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 24, System::Drawing::FontStyle::Bold));
            this->label1->Location = System::Drawing::Point(124, 93);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(222, 36);
            this->label1->TabIndex = 0;
            this->label1->Text = L"Оберіть опцію";

            this->label2->AutoSize = true;
            this->label2->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label2->Location = System::Drawing::Point(122, 212);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(272, 19);
            this->label2->TabIndex = 15;
            this->label2->Text = L"1. Завантажити з файлу (taxpayers.txt)";

            this->label3->AutoSize = true;
            this->label3->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label3->Location = System::Drawing::Point(122, 233);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(208, 19);
            this->label3->TabIndex = 18;
            this->label3->Text = L"2. Вставити платника вручну";

            this->label4->AutoSize = true;
            this->label4->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label4->Location = System::Drawing::Point(122, 257);
            this->label4->Name = L"label4";
            this->label4->Size = System::Drawing::Size(243, 19);
            this->label4->TabIndex = 19;
            this->label4->Text = L"3. Видалити платника за номером";

            this->label5->AutoSize = true;
            this->label5->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label5->Location = System::Drawing::Point(122, 277);
            this->label5->Name = L"label5";
            this->label5->Size = System::Drawing::Size(376, 19);
            this->label5->TabIndex = 20;
            this->label5->Text = L"4. Шукати платника";

            this->label6->AutoSize = true;
            this->label6->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label6->Location = System::Drawing::Point(122, 300);
            this->label6->Name = L"label6";
            this->label6->Size = System::Drawing::Size(155, 19);
            this->label6->TabIndex = 21;
            this->label6->Text = L"5. Показати таблицю";

            this->label7->AutoSize = true;
            this->label7->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label7->Location = System::Drawing::Point(122, 330);
            this->label7->Name = L"label7";
            this->label7->Size = System::Drawing::Size(67, 19);
            this->label7->TabIndex = 26;
            this->label7->Text = L"0. Вихід";

            this->numericUpDown1->Location = System::Drawing::Point(126, 170);
            this->numericUpDown1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
            this->numericUpDown1->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 0, 0, 0, 0 });
            this->numericUpDown1->Name = L"numericUpDown1";
            this->numericUpDown1->Size = System::Drawing::Size(38, 20);
            this->numericUpDown1->TabIndex = 16;
            this->numericUpDown1->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 0, 0, 0, 0 });

            this->button1->Location = System::Drawing::Point(207, 167);
            this->button1->Name = L"button1";
            this->button1->Size = System::Drawing::Size(91, 23);
            this->button1->TabIndex = 17;
            this->button1->Text = L"Підтвердити";

            this->textBox2->Location = System::Drawing::Point(230, 415);
            this->textBox2->Name = L"textBox2";
            this->textBox2->Size = System::Drawing::Size(100, 20);
            this->textBox2->TabIndex = 40;
            this->textBox2->Text = L"Введіть номер платника";

            this->textBox3->Location = System::Drawing::Point(126, 389);
            this->textBox3->Name = L"textBox3";
            this->textBox3->Size = System::Drawing::Size(100, 20);
            this->textBox3->TabIndex = 41;
            this->textBox3->Text = L"Прізвище";

            this->textBox7->Location = System::Drawing::Point(126, 415);
            this->textBox7->Name = L"textBox7";
            this->textBox7->Size = System::Drawing::Size(100, 20);
            this->textBox7->TabIndex = 42;
            this->textBox7->Text = L"Ім\'я";

            this->textBox6->Location = System::Drawing::Point(126, 441);
            this->textBox6->Name = L"textBox6";
            this->textBox6->Size = System::Drawing::Size(100, 20);
            this->textBox6->TabIndex = 43;
            this->textBox6->Text = L"По батькові";

            this->textBox10->Location = System::Drawing::Point(323, 170);
            this->textBox10->Name = L"textBox10";
            this->textBox10->Size = System::Drawing::Size(100, 20);
            this->textBox10->TabIndex = 58;
            this->textBox10->Text = L"Введіть номер платника";

            this->button3->Location = System::Drawing::Point(431, 170);
            this->button3->Name = L"button3";
            this->button3->Size = System::Drawing::Size(91, 23);
            this->button3->TabIndex = 44;
            this->button3->Text = L"Підтвердити";

            this->button4->Location = System::Drawing::Point(350, 412);
            this->button4->Name = L"button4";
            this->button4->Size = System::Drawing::Size(91, 23);
            this->button4->TabIndex = 45;
            this->button4->Text = L"Підтвердити";

            this->numericUpDown3->Location = System::Drawing::Point(925, 490);
            this->numericUpDown3->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
            this->numericUpDown3->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 0, 0, 0, 0 });
            this->numericUpDown3->Name = L"numericUpDown3";
            this->numericUpDown3->Size = System::Drawing::Size(38, 20);
            this->numericUpDown3->TabIndex = 46;
            this->numericUpDown3->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 0, 0, 0, 0 });

            this->button5->Location = System::Drawing::Point(990, 490);
            this->button5->Name = L"button5";
            this->button5->Size = System::Drawing::Size(91, 23);
            this->button5->TabIndex = 47;
            this->button5->Text = L"Підтвердити";

            this->label17->AutoSize = true;
            this->label17->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label17->Location = System::Drawing::Point(701, 490);
            this->label17->Name = L"label17";
            this->label17->Size = System::Drawing::Size(209, 19);
            this->label17->TabIndex = 48;
            this->label17->Text = L"Введіть розмір Геш-таблиці";

            this->label18->AutoSize = true;
            this->label18->Font = (gcnew System::Drawing::Font(L"Times New Roman", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label18->Location = System::Drawing::Point(806, 34);
            this->label18->Name = L"label18";
            this->label18->Size = System::Drawing::Size(173, 31);
            this->label18->TabIndex = 49;
            this->label18->Text = L"Геш-таблиця";

            this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->dataGridView1->Location = System::Drawing::Point(528, 68);
            this->dataGridView1->Name = L"dataGridView1";
            this->dataGridView1->Size = System::Drawing::Size(749, 413);
            this->dataGridView1->TabIndex = 27;

            this->label13->AutoSize = true;
            this->label13->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label13->Location = System::Drawing::Point(122, 674);
            this->label13->Name = L"label13";
            this->label13->Size = System::Drawing::Size(335, 19);
            this->label13->TabIndex = 29;
            this->label13->Text = L"1. Завантажити студентів з файлу (students.txt)";

            this->numericUpDown2->Location = System::Drawing::Point(126, 632);
            this->numericUpDown2->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
            this->numericUpDown2->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 0, 0, 0, 0 });
            this->numericUpDown2->Name = L"numericUpDown2";
            this->numericUpDown2->Size = System::Drawing::Size(38, 20);
            this->numericUpDown2->TabIndex = 30;
            this->numericUpDown2->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 0, 0, 0, 0 });

            this->button2->Location = System::Drawing::Point(207, 629);
            this->button2->Name = L"button2";
            this->button2->Size = System::Drawing::Size(91, 23);
            this->button2->TabIndex = 31;
            this->button2->Text = L"Підтвердити";

            this->label12->AutoSize = true;
            this->label12->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label12->Location = System::Drawing::Point(122, 695);
            this->label12->Name = L"label12";
            this->label12->Size = System::Drawing::Size(208, 19);
            this->label12->TabIndex = 32;
            this->label12->Text = L"2. Вставити студента вручну";

            this->label11->AutoSize = true;
            this->label11->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label11->Location = System::Drawing::Point(122, 719);
            this->label11->Name = L"label11";
            this->label11->Size = System::Drawing::Size(224, 19);
            this->label11->TabIndex = 33;
            this->label11->Text = L"3. Видалити студента за кодом";

            this->label10->AutoSize = true;
            this->label10->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label10->Location = System::Drawing::Point(122, 739);
            this->label10->Name = L"label10";
            this->label10->Size = System::Drawing::Size(143, 19);
            this->label10->TabIndex = 34;
            this->label10->Text = L"4. Пошук за кодом";

            this->label9->AutoSize = true;
            this->label9->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label9->Location = System::Drawing::Point(122, 762);
            this->label9->Name = L"label9";
            this->label9->Size = System::Drawing::Size(217, 19);
            this->label9->TabIndex = 35;
            this->label9->Text = L"5. Показати структуру дерева";

            this->label8->AutoSize = true;
            this->label8->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label8->Location = System::Drawing::Point(122, 847);
            this->label8->Name = L"label8";
            this->label8->Size = System::Drawing::Size(67, 19);
            this->label8->TabIndex = 36;
            this->label8->Text = L"0. Вихід";

            this->label14->AutoSize = true;
            this->label14->Font = (gcnew System::Drawing::Font(L"Times New Roman", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label14->Location = System::Drawing::Point(120, 557);
            this->label14->Name = L"label14";
            this->label14->Size = System::Drawing::Size(222, 36);
            this->label14->TabIndex = 37;
            this->label14->Text = L"Оберіть опцію";

            this->label15->AutoSize = true;
            this->label15->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label15->Location = System::Drawing::Point(122, 790);
            this->label15->Name = L"label15";
            this->label15->Size = System::Drawing::Size(301, 19);
            this->label15->TabIndex = 38;
            this->label15->Text = L"6. Студенти з найкращим середнім балом";

            this->label16->AutoSize = true;
            this->label16->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label16->Location = System::Drawing::Point(122, 819);
            this->label16->Name = L"label16";
            this->label16->Size = System::Drawing::Size(298, 19);
            this->label16->TabIndex = 39;
            this->label16->Text = L"7. Студенти з найгіршим середнім балом";

            this->textBox5->Location = System::Drawing::Point(126, 881);
            this->textBox5->Name = L"textBox5";
            this->textBox5->Size = System::Drawing::Size(100, 20);
            this->textBox5->TabIndex = 50;
            this->textBox5->Text = L"Прізвище";

            this->textBox4->Location = System::Drawing::Point(126, 907);
            this->textBox4->Name = L"textBox4";
            this->textBox4->Size = System::Drawing::Size(100, 20);
            this->textBox4->TabIndex = 51;
            this->textBox4->Text = L"Ініціали";

            this->textBox1->Location = System::Drawing::Point(126, 933);
            this->textBox1->Name = L"textBox1";
            this->textBox1->Size = System::Drawing::Size(100, 20);
            this->textBox1->TabIndex = 52;
            this->textBox1->Text = L"Група";

            this->textBox8->Location = System::Drawing::Point(323, 632);
            this->textBox8->Name = L"textBox8";
            this->textBox8->Size = System::Drawing::Size(100, 20);
            this->textBox8->TabIndex = 53;
            this->textBox8->Text = L"Введіть код студента";

            this->button6->Location = System::Drawing::Point(431, 629);
            this->button6->Name = L"button6";
            this->button6->Size = System::Drawing::Size(91, 23);
            this->button6->TabIndex = 54;
            this->button6->Text = L"Підтвердити";

            this->textBox9->Location = System::Drawing::Point(242, 907);
            this->textBox9->Name = L"textBox9";
            this->textBox9->Size = System::Drawing::Size(100, 20);
            this->textBox9->TabIndex = 55;
            this->textBox9->Text = L"середній бал";

            this->textBox11->Location = System::Drawing::Point(239, 881);
            this->textBox11->Name = L"textBox11";
            this->textBox11->Size = System::Drawing::Size(100, 20);
            this->textBox11->TabIndex = 59;
            this->textBox11->Text = L"Введіть код студента, якого хочете додать";

            this->button7->Location = System::Drawing::Point(366, 904);
            this->button7->Name = L"button7";
            this->button7->Size = System::Drawing::Size(91, 23);
            this->button7->TabIndex = 56;
            this->button7->Text = L"Підтвердити";

            this->label19->AutoSize = true;
            this->label19->Font = (gcnew System::Drawing::Font(L"Times New Roman", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label19->Location = System::Drawing::Point(796, 537);
            this->label19->Name = L"label19";
            this->label19->Size = System::Drawing::Size(202, 31);
            this->label19->TabIndex = 57;
            this->label19->Text = L"Бінарне дерево";

            this->dataGridView2->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->dataGridView2->Location = System::Drawing::Point(528, 571);
            this->dataGridView2->Name = L"dataGridView2";
            this->dataGridView2->Size = System::Drawing::Size(749, 413);
            this->dataGridView2->TabIndex = 28;

            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(1949, 996);
            this->Controls->Add(this->textBox11);
            this->Controls->Add(this->textBox10);
            this->Controls->Add(this->label19);
            this->Controls->Add(this->button7);
            this->Controls->Add(this->textBox9);
            this->Controls->Add(this->button6);
            this->Controls->Add(this->textBox8);
            this->Controls->Add(this->textBox1);
            this->Controls->Add(this->textBox4);
            this->Controls->Add(this->textBox5);
            this->Controls->Add(this->label18);
            this->Controls->Add(this->label17);
            this->Controls->Add(this->button5);
            this->Controls->Add(this->numericUpDown3);
            this->Controls->Add(this->button4);
            this->Controls->Add(this->button3);
            this->Controls->Add(this->textBox6);
            this->Controls->Add(this->textBox7);
            this->Controls->Add(this->textBox3);
            this->Controls->Add(this->textBox2);
            this->Controls->Add(this->label16);
            this->Controls->Add(this->label15);
            this->Controls->Add(this->label14);
            this->Controls->Add(this->label8);
            this->Controls->Add(this->label9);
            this->Controls->Add(this->label10);
            this->Controls->Add(this->label11);
            this->Controls->Add(this->label12);
            this->Controls->Add(this->button2);
            this->Controls->Add(this->numericUpDown2);
            this->Controls->Add(this->label13);
            this->Controls->Add(this->dataGridView2);
            this->Controls->Add(this->dataGridView1);
            this->Controls->Add(this->label7);
            this->Controls->Add(this->label6);
            this->Controls->Add(this->label5);
            this->Controls->Add(this->label4);
            this->Controls->Add(this->label3);
            this->Controls->Add(this->button1);
            this->Controls->Add(this->numericUpDown1);
            this->Controls->Add(this->label2);
            this->Controls->Add(this->label1);
            this->Name = L"MyForm2";
            this->Text = L"MyForm2";
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown2))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown3))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();

            this->button1->Click += gcnew EventHandler(this, &MyForm2::button1_Click);
            this->button2->Click += gcnew EventHandler(this, &MyForm2::button2_Click);
            this->button3->Click += gcnew EventHandler(this, &MyForm2::button3_Click);
            this->button4->Click += gcnew EventHandler(this, &MyForm2::button4_Click);
            this->button5->Click += gcnew EventHandler(this, &MyForm2::button5_Click);
            this->button6->Click += gcnew EventHandler(this, &MyForm2::button6_Click);
            this->button7->Click += gcnew EventHandler(this, &MyForm2::button7_Click);
        }
#pragma endregion

    private:
        System::Void button1_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void button2_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void button3_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void button4_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void button5_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void button6_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void button7_Click(System::Object^ sender, System::EventArgs^ e);
    };
}
