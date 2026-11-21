#pragma once
#include <vector>
#include <map>
#include <string>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <msclr/marshal_cppstd.h>

namespace Finals {
    struct Drink {
        std::string name;
        std::string flavor;
        double salePrice;
        int available;
    };

    struct HuffmanNode {
        char ch;
        int freq;
        HuffmanNode* left;
        HuffmanNode* right;
        HuffmanNode(char c, int f, HuffmanNode* l = nullptr, HuffmanNode* r = nullptr)
            : ch(c), freq(f), left(l), right(r) {
        }
    };

    struct HuffmanNodeCompare {
        bool operator()(HuffmanNode* l, HuffmanNode* r) {
            return l->freq > r->freq;
        }
    };

    struct TruckItem {
        int idx;
        double profit;
        int avail;
    };

    ref class Truck {
    private:
        std::vector<Drink>* drinks;
        int capacity;
        double purchaseCost;
        int maxFlavorCount;

    public:
        Truck() {
            drinks = new std::vector<Drink>();
            capacity = 0;
            purchaseCost = 0.0;
            maxFlavorCount = 0;
        }

        ~Truck() {
            delete drinks;
        }

        void SetInitialData(int truckCapacity, double cost, int maxFlavor);
        void AddDrink(System::String^ name, System::String^ flavor, double salePrice, int available);
        void EditDrink(int index, System::String^ name, System::String^ flavor, double salePrice, int available);
        void DeleteDrink(int index);
        void SetFlavorLimit(int limit);
        System::Collections::Generic::List<System::Collections::Generic::Dictionary<System::String^, System::Object^>^>^ GetDrinks();
        System::Tuple<System::Collections::Generic::List<System::Collections::Generic::Dictionary<System::String^, System::Object^>^>^,
            double, double, double, int>^ SolveGreedy();
        int GetFlavorLimit() { return maxFlavorCount; }
        int GetCapacity() { return capacity; }
        double GetPurchaseCost() { return purchaseCost; }
    };

    ref class HuffmanCompressor {
    private:
        std::unordered_map<char, std::string>* huffmanCodes;
        void* root;

        void GenerateCodes(HuffmanNode* node, std::string code);
        void DeleteTree(HuffmanNode* node);
        System::String^ LoadFile(System::String^ filename);

    public:
        HuffmanCompressor() {
            huffmanCodes = new std::unordered_map<char, std::string>();
            root = nullptr;
        }

        ~HuffmanCompressor() {
            if (root) {
                DeleteTree(static_cast<HuffmanNode*>(root));
            }
            delete huffmanCodes;
        }

        System::Tuple<System::String^, double, double, double>^ Compress(System::String^ inputFilename, System::String^ outputFilename);
        System::String^ Decompress(System::String^ inputFilename, System::String^ outputFilename);
    };

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class MyForm3 : public System::Windows::Forms::Form
    {
    private:
        Truck^ truck;
        HuffmanCompressor^ compressor;
        System::Windows::Forms::NumericUpDown^ numericUpDown3;
        System::Windows::Forms::Button^ button6;

        System::Void numericUpDown1_ValueChanged(System::Object^ sender, System::EventArgs^ e);
        System::Void button1_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void button2_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void button3_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void button5_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void numericUpDown3_ValueChanged(System::Object^ sender, System::EventArgs^ e);
        System::Void button6_Click(System::Object^ sender, System::EventArgs^ e);

        void SetupDataGridViews();
        void DisplayDrinks();
        void DisplayHuffmanResults(System::String^ encodedText, System::Collections::Generic::Dictionary<System::String^, System::Char>^ codes);

    public:
        MyForm3(void)
        {
            InitializeComponent();
            truck = gcnew Truck();
            compressor = gcnew HuffmanCompressor();
            SetupDataGridViews();
        }

    protected:
        ~MyForm3()
        {
            if (components)
            {
                delete components;
            }
            delete truck;
            delete compressor;
        }

    private: System::Windows::Forms::Label^ label11;
    protected:
    private: System::Windows::Forms::Label^ label8;
    private: System::Windows::Forms::Label^ label7;
    private: System::Windows::Forms::Label^ label6;
    private: System::Windows::Forms::Label^ label5;
    private: System::Windows::Forms::Label^ label4;
    private: System::Windows::Forms::Label^ label3;
    private: System::Windows::Forms::Button^ button1;
    private: System::Windows::Forms::NumericUpDown^ numericUpDown1;
    private: System::Windows::Forms::Label^ label2;
    private: System::Windows::Forms::Label^ label1;
    private: System::Windows::Forms::DataGridView^ dataGridView1;
    private: System::Windows::Forms::Button^ button2;
    private: System::Windows::Forms::NumericUpDown^ numericUpDown2;
    private: System::Windows::Forms::Label^ label9;
    private: System::Windows::Forms::DataGridView^ dataGridView2;
    private: System::Windows::Forms::Label^ label10;
    private: System::Windows::Forms::Label^ label12;
    private: System::Windows::Forms::Label^ label13;
    private: System::Windows::Forms::Label^ label14;
    private: System::Windows::Forms::Label^ label15;
    private: System::Windows::Forms::TextBox^ textBox8;
    private: System::Windows::Forms::TextBox^ textBox5;
    private: System::Windows::Forms::TextBox^ textBox6;
    private: System::Windows::Forms::TextBox^ textBox7;
    private: System::Windows::Forms::TextBox^ textBox4;
    private: System::Windows::Forms::TextBox^ textBox3;
    private: System::Windows::Forms::TextBox^ textBox2;
    private: System::Windows::Forms::Button^ button3;
    private: System::Windows::Forms::TextBox^ textBox1;
    private: System::Windows::Forms::Button^ button5;

    private:
        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->label11 = (gcnew System::Windows::Forms::Label());
            this->label8 = (gcnew System::Windows::Forms::Label());
            this->label7 = (gcnew System::Windows::Forms::Label());
            this->label6 = (gcnew System::Windows::Forms::Label());
            this->label5 = (gcnew System::Windows::Forms::Label());
            this->label4 = (gcnew System::Windows::Forms::Label());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->button1 = (gcnew System::Windows::Forms::Button());
            this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
            this->button2 = (gcnew System::Windows::Forms::Button());
            this->numericUpDown2 = (gcnew System::Windows::Forms::NumericUpDown());
            this->label9 = (gcnew System::Windows::Forms::Label());
            this->dataGridView2 = (gcnew System::Windows::Forms::DataGridView());
            this->label10 = (gcnew System::Windows::Forms::Label());
            this->label12 = (gcnew System::Windows::Forms::Label());
            this->label13 = (gcnew System::Windows::Forms::Label());
            this->label14 = (gcnew System::Windows::Forms::Label());
            this->label15 = (gcnew System::Windows::Forms::Label());
            this->textBox8 = (gcnew System::Windows::Forms::TextBox());
            this->textBox5 = (gcnew System::Windows::Forms::TextBox());
            this->textBox6 = (gcnew System::Windows::Forms::TextBox());
            this->textBox7 = (gcnew System::Windows::Forms::TextBox());
            this->textBox4 = (gcnew System::Windows::Forms::TextBox());
            this->textBox3 = (gcnew System::Windows::Forms::TextBox());
            this->textBox2 = (gcnew System::Windows::Forms::TextBox());
            this->button3 = (gcnew System::Windows::Forms::Button());
            this->textBox1 = (gcnew System::Windows::Forms::TextBox());
            this->button5 = (gcnew System::Windows::Forms::Button());
            this->numericUpDown3 = (gcnew System::Windows::Forms::NumericUpDown());
            this->button6 = (gcnew System::Windows::Forms::Button());

            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown2))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown3))->BeginInit();

            this->SuspendLayout();

            this->numericUpDown3->Location = System::Drawing::Point(85, 605);
            this->numericUpDown3->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
            this->numericUpDown3->Name = L"numericUpDown3";
            this->numericUpDown3->Size = System::Drawing::Size(38, 20);
            this->numericUpDown3->TabIndex = 70;
            this->numericUpDown3->ValueChanged += gcnew System::EventHandler(this, &MyForm3::numericUpDown3_ValueChanged);

            this->button6->Location = System::Drawing::Point(129, 603);
            this->button6->Name = L"button6";
            this->button6->Size = System::Drawing::Size(91, 23);
            this->button6->TabIndex = 71;
            this->button6->Text = L"Підтвердити";
            this->button6->Click += gcnew System::EventHandler(this, &MyForm3::button6_Click);

            this->label11->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label11->Location = System::Drawing::Point(61, 293);
            this->label11->Name = L"label11";
            this->label11->Size = System::Drawing::Size(254, 32);
            this->label11->TabIndex = 38;
            this->label11->Text = L"0. Вихід";

            this->label8->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label8->Location = System::Drawing::Point(656, 460);
            this->label8->Name = L"label8";
            this->label8->Size = System::Drawing::Size(375, 42);
            this->label8->TabIndex = 41;
            this->label8->Text = L"Встановити обмеження на кількість діжок за смаком (0 = без обмежень)";

            this->label7->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label7->Location = System::Drawing::Point(61, 262);
            this->label7->Name = L"label7";
            this->label7->Size = System::Drawing::Size(495, 41);
            this->label7->TabIndex = 42;
            this->label7->Text = L"6. Розв\'язати задачу (жадібний алгоритм) і оновити запаси";

            this->label6->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label6->Location = System::Drawing::Point(61, 242);
            this->label6->Name = L"label6";
            this->label6->Size = System::Drawing::Size(417, 42);
            this->label6->TabIndex = 43;
            this->label6->Text = L"5. Показати всі записи";

            this->label5->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label5->Location = System::Drawing::Point(61, 219);
            this->label5->Name = L"label5";
            this->label5->Size = System::Drawing::Size(417, 42);
            this->label5->TabIndex = 44;
            this->label5->Text = L"4. Видалити запис (за номером)";

            this->label4->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label4->Location = System::Drawing::Point(61, 199);
            this->label4->Name = L"label4";
            this->label4->Size = System::Drawing::Size(417, 42);
            this->label4->TabIndex = 45;
            this->label4->Text = L"3. Редагувати запис (за номером)";

            this->label3->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label3->Location = System::Drawing::Point(61, 175);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(417, 42);
            this->label3->TabIndex = 46;
            this->label3->Text = L"2. Додати запис (напій)";

            this->button1->Location = System::Drawing::Point(215, 113);
            this->button1->Name = L"button1";
            this->button1->Size = System::Drawing::Size(91, 23);
            this->button1->TabIndex = 37;
            this->button1->Text = L"Підтвердити";
            this->button1->Click += gcnew System::EventHandler(this, &MyForm3::button1_Click);

            this->numericUpDown1->Location = System::Drawing::Point(65, 116);
            this->numericUpDown1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
            this->numericUpDown1->Name = L"numericUpDown1";
            this->numericUpDown1->Size = System::Drawing::Size(38, 20);
            this->numericUpDown1->TabIndex = 36;
            this->numericUpDown1->ValueChanged += gcnew System::EventHandler(this, &MyForm3::numericUpDown1_ValueChanged);

            this->label2->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label2->Location = System::Drawing::Point(61, 154);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(417, 42);
            this->label2->TabIndex = 47;
            this->label2->Text = L"1. Встановити початкові дані";

            this->label1->AutoSize = true;
            this->label1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 24, System::Drawing::FontStyle::Bold));
            this->label1->Location = System::Drawing::Point(59, 74);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(256, 36);
            this->label1->TabIndex = 35;
            this->label1->Text = L"Виберіть опцію: ";

            this->dataGridView1->Location = System::Drawing::Point(654, 41);
            this->dataGridView1->Name = L"dataGridView1";
            this->dataGridView1->Size = System::Drawing::Size(749, 413);
            this->dataGridView1->TabIndex = 48;

            this->button2->Location = System::Drawing::Point(1138, 460);
            this->button2->Name = L"button2";
            this->button2->Size = System::Drawing::Size(91, 23);
            this->button2->TabIndex = 50;
            this->button2->Text = L"Підтвердити";
            this->button2->Click += gcnew System::EventHandler(this, &MyForm3::button2_Click);

            this->numericUpDown2->Location = System::Drawing::Point(1057, 463);
            this->numericUpDown2->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
            this->numericUpDown2->Name = L"numericUpDown2";
            this->numericUpDown2->Size = System::Drawing::Size(38, 20);
            this->numericUpDown2->TabIndex = 49;

            this->label9->AutoSize = true;
            this->label9->Font = (gcnew System::Drawing::Font(L"Times New Roman", 24, System::Drawing::FontStyle::Bold));
            this->label9->Location = System::Drawing::Point(875, 2);
            this->label9->Name = L"label9";
            this->label9->Size = System::Drawing::Size(294, 36);
            this->label9->TabIndex = 51;
            this->label9->Text = L"Жадібний алгоритм";

            this->dataGridView2->Location = System::Drawing::Point(654, 563);
            this->dataGridView2->Name = L"dataGridView2";
            this->dataGridView2->Size = System::Drawing::Size(749, 413);
            this->dataGridView2->TabIndex = 52;

            this->label10->AutoSize = true;
            this->label10->Font = (gcnew System::Drawing::Font(L"Times New Roman", 24, System::Drawing::FontStyle::Bold));
            this->label10->Location = System::Drawing::Point(744, 524);
            this->label10->Name = L"label10";
            this->label10->Size = System::Drawing::Size(587, 36);
            this->label10->TabIndex = 53;
            this->label10->Text = L"Таблиця виведення алгоритму хафмана";

            this->label12->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label12->Location = System::Drawing::Point(87, 693);
            this->label12->Name = L"label12";
            this->label12->Size = System::Drawing::Size(417, 42);
            this->label12->TabIndex = 54;
            this->label12->Text = L"2. Розкодувати дані з файлу \'compressed.txt\'";

            this->label13->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label13->Location = System::Drawing::Point(87, 651);
            this->label13->Name = L"label13";
            this->label13->Size = System::Drawing::Size(417, 42);
            this->label13->TabIndex = 55;
            this->label13->Text = L"1. Стиснути дані з файлу \'input.txt\'";

            this->label14->AutoSize = true;
            this->label14->Font = (gcnew System::Drawing::Font(L"Times New Roman", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label14->Location = System::Drawing::Point(85, 563);
            this->label14->Name = L"label14";
            this->label14->Size = System::Drawing::Size(256, 36);
            this->label14->TabIndex = 56;
            this->label14->Text = L"Виберіть опцію: ";

            this->label15->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label15->Location = System::Drawing::Point(87, 735);
            this->label15->Name = L"label15";
            this->label15->Size = System::Drawing::Size(254, 32);
            this->label15->TabIndex = 57;
            this->label15->Text = L"0. Вихід";

            this->textBox8->Location = System::Drawing::Point(159, 460);
            this->textBox8->Name = L"textBox8";
            this->textBox8->Size = System::Drawing::Size(100, 20);
            this->textBox8->TabIndex = 64;
            this->textBox8->Text = L"Наявна кількість діжок";

            this->textBox5->Location = System::Drawing::Point(53, 485);
            this->textBox5->Name = L"textBox5";
            this->textBox5->Size = System::Drawing::Size(100, 20);
            this->textBox5->TabIndex = 63;
            this->textBox5->Text = L"Ціна продажі одної діжки";

            this->textBox6->Location = System::Drawing::Point(53, 460);
            this->textBox6->Name = L"textBox6";
            this->textBox6->Size = System::Drawing::Size(100, 20);
            this->textBox6->TabIndex = 62;
            this->textBox6->Text = L"Смак";

            this->textBox7->Location = System::Drawing::Point(53, 434);
            this->textBox7->Name = L"textBox7";
            this->textBox7->Size = System::Drawing::Size(100, 20);
            this->textBox7->TabIndex = 61;
            this->textBox7->Text = L"Назва напою";

            this->textBox4->Location = System::Drawing::Point(53, 401);
            this->textBox4->Name = L"textBox4";
            this->textBox4->Size = System::Drawing::Size(100, 20);
            this->textBox4->TabIndex = 60;
            this->textBox4->Text = L"Кількість напоїв";

            this->textBox3->Location = System::Drawing::Point(53, 376);
            this->textBox3->Name = L"textBox3";
            this->textBox3->Size = System::Drawing::Size(100, 20);
            this->textBox3->TabIndex = 59;
            this->textBox3->Text = L"Ціна закупівлі";

            this->textBox2->Location = System::Drawing::Point(53, 350);
            this->textBox2->Name = L"textBox2";
            this->textBox2->Size = System::Drawing::Size(100, 20);
            this->textBox2->TabIndex = 58;
            this->textBox2->Text = L"Місткість вантажівки";

            this->button3->Location = System::Drawing::Point(265, 455);
            this->button3->Name = L"button3";
            this->button3->Size = System::Drawing::Size(75, 23);
            this->button3->TabIndex = 65;
            this->button3->Text = L"Ввести";
            this->button3->UseVisualStyleBackColor = true;
            this->button3->Click += gcnew System::EventHandler(this, &MyForm3::button3_Click);

            this->textBox1->Location = System::Drawing::Point(109, 116);
            this->textBox1->Name = L"textBox1";
            this->textBox1->Size = System::Drawing::Size(100, 20);
            this->textBox1->TabIndex = 68;
            this->textBox1->Text = L"Номер запису";

            this->button5->Location = System::Drawing::Point(173, 432);
            this->button5->Name = L"button5";
            this->button5->Size = System::Drawing::Size(75, 23);
            this->button5->TabIndex = 69;
            this->button5->Text = L"Розв\'язати";
            this->button5->UseVisualStyleBackColor = true;
            this->button5->Click += gcnew System::EventHandler(this, &MyForm3::button5_Click);

            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(1899, 1045);
            this->Controls->Add(this->numericUpDown3);
            this->Controls->Add(this->button6);
            this->Controls->Add(this->button5);
            this->Controls->Add(this->textBox1);
            this->Controls->Add(this->button3);
            this->Controls->Add(this->textBox8);
            this->Controls->Add(this->textBox5);
            this->Controls->Add(this->textBox6);
            this->Controls->Add(this->textBox7);
            this->Controls->Add(this->textBox4);
            this->Controls->Add(this->textBox3);
            this->Controls->Add(this->textBox2);
            this->Controls->Add(this->label15);
            this->Controls->Add(this->label14);
            this->Controls->Add(this->label12);
            this->Controls->Add(this->label13);
            this->Controls->Add(this->label10);
            this->Controls->Add(this->dataGridView2);
            this->Controls->Add(this->label9);
            this->Controls->Add(this->button2);
            this->Controls->Add(this->numericUpDown2);
            this->Controls->Add(this->dataGridView1);
            this->Controls->Add(this->label11);
            this->Controls->Add(this->label8);
            this->Controls->Add(this->label7);
            this->Controls->Add(this->label6);
            this->Controls->Add(this->label5);
            this->Controls->Add(this->label4);
            this->Controls->Add(this->label3);
            this->Controls->Add(this->button1);
            this->Controls->Add(this->numericUpDown1);
            this->Controls->Add(this->label2);
            this->Controls->Add(this->label1);
            this->Name = L"MyForm3";
            this->Text = L"MyForm3";
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown2))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown3))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();
        }
#pragma endregion
    };
}
