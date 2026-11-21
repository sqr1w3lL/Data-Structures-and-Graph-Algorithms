#pragma once
#include <msclr/marshal_cppstd.h>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <sstream> 

using namespace msclr::interop;

namespace Finals {
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    class InputData {
    private:
        std::vector<std::vector<int>> field;
        int rows, cols;
        std::pair<int, int> start, finish;
    public:
        InputData() : rows(0), cols(0), start({ 0, 0 }), finish({ 0, 0 }) {}
        void setInitialData(int r, int c, const std::vector<int>& values) {
            rows = r;
            cols = c;
            field.assign(rows, std::vector<int>(cols, 0));
            int index = 0;
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    if (index < values.size()) {
                        field[i][j] = values[index++];
                    }
                }
            }
            start = { 0, 0 };
            finish = { rows - 1, cols - 1 };
        }
        void setStartAndFinish(int sr, int sc, int fr, int fc) {
            if (sr >= 0 && sr < rows && sc >= 0 && sc < cols &&
                fr >= 0 && fr < rows && fc >= 0 && fc < cols &&
                fr >= sr && fc >= sc) {
                start = { sr, sc };
                finish = { fr, fc };
            }
            else {
                start = { 0, 0 };
                finish = { rows - 1, cols - 1 };
            }
        }
        void editParameter(int r, int c, int val) {
            if (r >= 0 && r < rows && c >= 0 && c < cols) {
                field[r][c] = val;
            }
        }
        void deleteParameter(int r, int c) {
            if (r >= 0 && r < rows && c >= 0 && c < cols) {
                field[r][c] = 0;
            }
        }
        std::vector<std::vector<int>> getField() const { return field; }
        std::pair<int, int> getStart() const { return start; }
        std::pair<int, int> getFinish() const { return finish; }
        int getRows() const { return rows; }
        int getCols() const { return cols; }
    };

    class DynamicSolver {
    public:
        static int findMinCostPath(const std::vector<std::vector<int>>& field, std::pair<int, int> start, std::pair<int, int> finish) {
            int n = field.size();
            if (n == 0) return 0;
            int m = field[0].size();
            int sr = start.first, sc = start.second;
            int fr = finish.first, fc = finish.second;
            if (sr < 0 || sc < 0 || fr >= n || fc >= m || sr > fr || sc > fc) {
                return INT_MAX;
            }
            std::vector<std::vector<int>> dp(n, std::vector<int>(m, INT_MAX));
            dp[sr][sc] = field[sr][sc];
            for (int i = sr; i <= fr; ++i) {
                for (int j = sc; j <= fc; ++j) {
                    if (i == sr && j == sc) continue;
                    int fromTop = (i > sr) ? dp[i - 1][j] : INT_MAX;
                    int fromLeft = (j > sc) ? dp[i][j - 1] : INT_MAX;
                    int fromDiag = (i > sr && j > sc) ? dp[i - 1][j - 1] : INT_MAX;
                    int minPrev = System::Math::Min(System::Math::Min(fromTop, fromLeft), fromDiag);
                    if (minPrev != INT_MAX) {
                        dp[i][j] = field[i][j] + minPrev;
                    }
                    else {
                        dp[i][j] = INT_MAX;
                    }
                }
            }
            return dp[fr][fc];
        }
    };

    class TextFormatter {
    private:
        std::vector<std::string> words;
        int maxLineLength;
    public:
        TextFormatter() : maxLineLength(0) {}
        void setInitialData(int maxLength, const std::string& text) {
            maxLineLength = maxLength;
            words.clear();
            std::istringstream iss(text);
            std::string word;
            while (iss >> word) {
                words.push_back(word);
            }
        }
        void editWord(int index, const std::string& newWord) {
            if (index >= 0 && index < words.size()) {
                words[index] = newWord;
            }
        }
        void deleteWord(int index) {
            if (index >= 0 && index < words.size()) {
                words.erase(words.begin() + index);
            }
        }
        std::vector<std::string> getWords() const { return words; }
        int getMaxLineLength() const { return maxLineLength; }
        std::pair<std::vector<std::string>, int> solveProblem() {
            if (words.empty()) {
                return { {}, 0 };
            }
            int n = words.size();
            std::vector<int> dp(n + 1, INT_MAX);
            std::vector<int> parent(n + 1, -1);
            dp[n] = 0;
            for (int i = n - 1; i >= 0; --i) {
                int currentLength = -1;
                for (int j = i; j < n; ++j) {
                    currentLength += words[j].length() + 1;
                    if (currentLength > maxLineLength) break;
                    int spaces = maxLineLength - currentLength;
                    int penalty = spaces * spaces;
                    if (j == n - 1) penalty = 0;
                    if (dp[j + 1] != INT_MAX) {
                        int totalPenalty = penalty + dp[j + 1];
                        if (totalPenalty < dp[i]) {
                            dp[i] = totalPenalty;
                            parent[i] = j;
                        }
                    }
                }
            }
            std::vector<std::string> lines;
            int i = 0;
            while (i < n && parent[i] != -1) {
                int j = parent[i];
                std::string line;
                for (int k = i; k <= j; ++k) {
                    if (!line.empty()) line += " ";
                    line += words[k];
                }
                lines.push_back(line);
                i = j + 1;
            }
            if (i < n) {
                std::string lastLine;
                for (int k = i; k < n; ++k) {
                    if (!lastLine.empty()) lastLine += " ";
                    lastLine += words[k];
                }
                lines.push_back(lastLine);
            }
            return { lines, dp[0] };
        }
    };

    public ref class MyForm4 : public System::Windows::Forms::Form
    {
    private:
        InputData* inputData;
        TextFormatter* textFormatter;
    public:
        MyForm4(void)
        {
            InitializeComponent();
            inputData = new InputData();
            textFormatter = new TextFormatter();
        }
    protected:
        ~MyForm4()
        {
            if (components)
            {
                delete components;
            }
            delete inputData;
            delete textFormatter;
        }
    private: System::Windows::Forms::Label^ label12;
    protected:
    private: System::Windows::Forms::DataGridView^ dataGridView1;
    private: System::Windows::Forms::Label^ label6;
    private: System::Windows::Forms::Label^ label5;
    private: System::Windows::Forms::Label^ label4;
    private: System::Windows::Forms::Label^ label3;
    private: System::Windows::Forms::Label^ label2;
    private: System::Windows::Forms::Button^ button1;
    private: System::Windows::Forms::NumericUpDown^ numericUpDown1;
    private: System::Windows::Forms::Label^ label1;
    private: System::Windows::Forms::Label^ label11;
    private: System::Windows::Forms::Label^ label7;
    private: System::Windows::Forms::Button^ button2;
    private: System::Windows::Forms::TextBox^ textBox1;
    private: System::Windows::Forms::TextBox^ textBox2;
    private: System::Windows::Forms::TextBox^ textBox3;
    private: System::Windows::Forms::TextBox^ textBox4;
    private: System::Windows::Forms::TextBox^ textBox5;
    private: System::Windows::Forms::Button^ button3;
    private: System::Windows::Forms::TextBox^ textBox6;
    private: System::Windows::Forms::TextBox^ textBox7;
    private: System::Windows::Forms::TextBox^ textBox8;
    private: System::Windows::Forms::Button^ button4;
    private: System::Windows::Forms::TextBox^ textBox9;
    private: System::Windows::Forms::TextBox^ textBox10;
    private: System::Windows::Forms::TextBox^ textBox11;
    private: System::Windows::Forms::Button^ button5;
    private: System::Windows::Forms::Label^ label8;
    private: System::Windows::Forms::Label^ label9;
    private: System::Windows::Forms::Label^ label10;
    private: System::Windows::Forms::Label^ label13;
    private: System::Windows::Forms::Label^ label14;
    private: System::Windows::Forms::Label^ label15;
    private: System::Windows::Forms::Label^ label16;
    private: System::Windows::Forms::Label^ label17;
    private: System::Windows::Forms::DataGridView^ dataGridView2;
    private: System::Windows::Forms::Button^ button6;
    private: System::Windows::Forms::NumericUpDown^ numericUpDown2;
    private: System::Windows::Forms::TextBox^ textBox12;
    private: System::Windows::Forms::TextBox^ textBox13;
    private: System::Windows::Forms::Button^ button7;
    private: System::Windows::Forms::Button^ button8;
    private: System::Windows::Forms::TextBox^ textBox14;
    private: System::Windows::Forms::TextBox^ textBox15;
    private: System::Windows::Forms::Label^ label18;
    private: System::Windows::Forms::Button^ button9;
    private: System::Windows::Forms::TextBox^ textBox16;
    private: System::Windows::Forms::TextBox^ textBox17;
    private: System::Windows::Forms::Button^ button10;
    private: System::Windows::Forms::TextBox^ textBox18;
    private:

        System::ComponentModel::Container^ components;
#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->label12 = (gcnew System::Windows::Forms::Label());
            this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
            this->label6 = (gcnew System::Windows::Forms::Label());
            this->label5 = (gcnew System::Windows::Forms::Label());
            this->label4 = (gcnew System::Windows::Forms::Label());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->button1 = (gcnew System::Windows::Forms::Button());
            this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->label11 = (gcnew System::Windows::Forms::Label());
            this->label7 = (gcnew System::Windows::Forms::Label());
            this->button2 = (gcnew System::Windows::Forms::Button());
            this->textBox1 = (gcnew System::Windows::Forms::TextBox());
            this->textBox2 = (gcnew System::Windows::Forms::TextBox());
            this->textBox3 = (gcnew System::Windows::Forms::TextBox());
            this->textBox4 = (gcnew System::Windows::Forms::TextBox());
            this->textBox5 = (gcnew System::Windows::Forms::TextBox());
            this->button3 = (gcnew System::Windows::Forms::Button());
            this->textBox6 = (gcnew System::Windows::Forms::TextBox());
            this->textBox7 = (gcnew System::Windows::Forms::TextBox());
            this->textBox8 = (gcnew System::Windows::Forms::TextBox());
            this->button4 = (gcnew System::Windows::Forms::Button());
            this->textBox9 = (gcnew System::Windows::Forms::TextBox());
            this->textBox10 = (gcnew System::Windows::Forms::TextBox());
            this->textBox11 = (gcnew System::Windows::Forms::TextBox());
            this->button5 = (gcnew System::Windows::Forms::Button());
            this->label8 = (gcnew System::Windows::Forms::Label());
            this->label9 = (gcnew System::Windows::Forms::Label());
            this->label10 = (gcnew System::Windows::Forms::Label());
            this->label13 = (gcnew System::Windows::Forms::Label());
            this->label14 = (gcnew System::Windows::Forms::Label());
            this->label15 = (gcnew System::Windows::Forms::Label());
            this->label16 = (gcnew System::Windows::Forms::Label());
            this->label17 = (gcnew System::Windows::Forms::Label());
            this->dataGridView2 = (gcnew System::Windows::Forms::DataGridView());
            this->button6 = (gcnew System::Windows::Forms::Button());
            this->numericUpDown2 = (gcnew System::Windows::Forms::NumericUpDown());
            this->textBox12 = (gcnew System::Windows::Forms::TextBox());
            this->textBox13 = (gcnew System::Windows::Forms::TextBox());
            this->button7 = (gcnew System::Windows::Forms::Button());
            this->button8 = (gcnew System::Windows::Forms::Button());
            this->textBox14 = (gcnew System::Windows::Forms::TextBox());
            this->textBox15 = (gcnew System::Windows::Forms::TextBox());
            this->label18 = (gcnew System::Windows::Forms::Label());
            this->button9 = (gcnew System::Windows::Forms::Button());
            this->textBox16 = (gcnew System::Windows::Forms::TextBox());
            this->textBox17 = (gcnew System::Windows::Forms::TextBox());
            this->button10 = (gcnew System::Windows::Forms::Button());
            this->textBox18 = (gcnew System::Windows::Forms::TextBox());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown2))->BeginInit();
            this->SuspendLayout();

            this->label12->AutoSize = true;
            this->label12->Font = (gcnew System::Drawing::Font(L"Times New Roman", 24, System::Drawing::FontStyle::Bold));
            this->label12->Location = System::Drawing::Point(966, 9);
            this->label12->Name = L"label12";
            this->label12->Size = System::Drawing::Size(294, 36);
            this->label12->TabIndex = 37;
            this->label12->Text = L"Ігрове поле";

            this->dataGridView1->Location = System::Drawing::Point(726, 48);
            this->dataGridView1->Name = L"dataGridView1";
            this->dataGridView1->Size = System::Drawing::Size(749, 413);
            this->dataGridView1->TabIndex = 36;

            this->label6->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label6->Location = System::Drawing::Point(50, 255);
            this->label6->Name = L"label6";
            this->label6->Size = System::Drawing::Size(187, 32);
            this->label6->TabIndex = 38;
            this->label6->Text = L"5. Розв'язати задачу";

            this->label5->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label5->Location = System::Drawing::Point(50, 232);
            this->label5->Name = L"label5";
            this->label5->Size = System::Drawing::Size(362, 23);
            this->label5->TabIndex = 39;
            this->label5->Text = L"4. Видалити параметер (робить значення 0)";

            this->label4->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label4->Location = System::Drawing::Point(50, 200);
            this->label4->Name = L"label4";
            this->label4->Size = System::Drawing::Size(217, 20);
            this->label4->TabIndex = 40;
            this->label4->Text = L"3. Редагувати параметри";

            this->label3->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label3->Location = System::Drawing::Point(50, 167);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(217, 24);
            this->label3->TabIndex = 41;
            this->label3->Text = L"2. Ввести нові параметри";

            this->label2->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label2->Location = System::Drawing::Point(50, 131);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(217, 20);
            this->label2->TabIndex = 42;
            this->label2->Text = L"1. Задати початкові дані";

            this->button1->Location = System::Drawing::Point(135, 87);
            this->button1->Name = L"button1";
            this->button1->Size = System::Drawing::Size(91, 23);
            this->button1->TabIndex = 45;
            this->button1->Text = L"Підтвердити";
            this->button1->Click += gcnew System::EventHandler(this, &MyForm4::button1_Click);

            this->numericUpDown1->Location = System::Drawing::Point(54, 90);
            this->numericUpDown1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 6, 0, 0, 0 });
            this->numericUpDown1->Name = L"numericUpDown1";
            this->numericUpDown1->Size = System::Drawing::Size(38, 20);
            this->numericUpDown1->TabIndex = 44;

            this->label1->AutoSize = true;
            this->label1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 24, System::Drawing::FontStyle::Bold));
            this->label1->Location = System::Drawing::Point(48, 48);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(256, 36);
            this->label1->TabIndex = 43;
            this->label1->Text = L"Виберіть опцію: ";

            this->label11->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label11->Location = System::Drawing::Point(50, 283);
            this->label11->Name = L"label11";
            this->label11->Size = System::Drawing::Size(217, 32);
            this->label11->TabIndex = 46;
            this->label11->Text = L"6. Вивести ігрове поле";

            this->label7->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label7->Location = System::Drawing::Point(50, 311);
            this->label7->Name = L"label7";
            this->label7->Size = System::Drawing::Size(91, 29);
            this->label7->TabIndex = 47;
            this->label7->Text = L"0. Вихід";

            this->button2->Location = System::Drawing::Point(597, 128);
            this->button2->Name = L"button2";
            this->button2->Size = System::Drawing::Size(75, 23);
            this->button2->TabIndex = 49;
            this->button2->Text = L"Ввести";
            this->button2->UseVisualStyleBackColor = true;
            this->button2->Click += gcnew System::EventHandler(this, &MyForm4::button2_Click);

            this->textBox1->Location = System::Drawing::Point(273, 129);
            this->textBox1->Name = L"textBox1";
            this->textBox1->Size = System::Drawing::Size(100, 20);
            this->textBox1->TabIndex = 48;
            this->textBox1->Text = L"Кількість рядків";

            this->textBox2->Location = System::Drawing::Point(379, 129);
            this->textBox2->Name = L"textBox2";
            this->textBox2->Size = System::Drawing::Size(100, 20);
            this->textBox2->TabIndex = 50;
            this->textBox2->Text = L"Кількість стовпців";

            this->textBox3->Location = System::Drawing::Point(485, 128);
            this->textBox3->Name = L"textBox3";
            this->textBox3->Size = System::Drawing::Size(100, 20);
            this->textBox3->TabIndex = 51;
            this->textBox3->Text = L"Усі значення через пробіл";

            this->textBox4->Location = System::Drawing::Point(485, 167);
            this->textBox4->Name = L"textBox4";
            this->textBox4->Size = System::Drawing::Size(100, 20);
            this->textBox4->TabIndex = 55;
            this->textBox4->Text = L"Нові значення";

            this->textBox5->Location = System::Drawing::Point(379, 168);
            this->textBox5->Name = L"textBox5";
            this->textBox5->Size = System::Drawing::Size(100, 20);
            this->textBox5->TabIndex = 54;
            this->textBox5->Text = L"Кількість стовпців";

            this->button3->Location = System::Drawing::Point(597, 167);
            this->button3->Name = L"button3";
            this->button3->Size = System::Drawing::Size(75, 23);
            this->button3->TabIndex = 53;
            this->button3->Text = L"Ввести";
            this->button3->UseVisualStyleBackColor = true;
            this->button3->Click += gcnew System::EventHandler(this, &MyForm4::button3_Click);

            this->textBox6->Location = System::Drawing::Point(273, 168);
            this->textBox6->Name = L"textBox6";
            this->textBox6->Size = System::Drawing::Size(100, 20);
            this->textBox6->TabIndex = 52;
            this->textBox6->Text = L"Кількість рядків";

            this->textBox7->Location = System::Drawing::Point(485, 201);
            this->textBox7->Name = L"textBox7";
            this->textBox7->Size = System::Drawing::Size(100, 20);
            this->textBox7->TabIndex = 59;
            this->textBox7->Text = L"Нове значення";

            this->textBox8->Location = System::Drawing::Point(379, 202);
            this->textBox8->Name = L"textBox8";
            this->textBox8->Size = System::Drawing::Size(100, 20);
            this->textBox8->TabIndex = 58;
            this->textBox8->Text = L"Стовпець";

            this->button4->Location = System::Drawing::Point(597, 201);
            this->button4->Name = L"button4";
            this->button4->Size = System::Drawing::Size(75, 23);
            this->button4->TabIndex = 57;
            this->button4->Text = L"Ввести";
            this->button4->UseVisualStyleBackColor = true;
            this->button4->Click += gcnew System::EventHandler(this, &MyForm4::button4_Click);

            this->textBox9->Location = System::Drawing::Point(273, 202);
            this->textBox9->Name = L"textBox9";
            this->textBox9->Size = System::Drawing::Size(100, 20);
            this->textBox9->TabIndex = 56;
            this->textBox9->Text = L"Рядок";

            this->textBox10->Location = System::Drawing::Point(531, 235);
            this->textBox10->Name = L"textBox10";
            this->textBox10->Size = System::Drawing::Size(100, 20);
            this->textBox10->TabIndex = 62;
            this->textBox10->Text = L"Стовпець";

            this->textBox11->Location = System::Drawing::Point(425, 236);
            this->textBox11->Name = L"textBox11";
            this->textBox11->Size = System::Drawing::Size(100, 20);
            this->textBox11->TabIndex = 61;
            this->textBox11->Text = L"Рядок";

            this->button5->Location = System::Drawing::Point(643, 235);
            this->button5->Name = L"button5";
            this->button5->Size = System::Drawing::Size(75, 23);
            this->button5->TabIndex = 60;
            this->button5->Text = L"Ввести";
            this->button5->UseVisualStyleBackColor = true;
            this->button5->Click += gcnew System::EventHandler(this, &MyForm4::button5_Click);

            this->label8->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label8->Location = System::Drawing::Point(50, 845);
            this->label8->Name = L"label8";
            this->label8->Size = System::Drawing::Size(91, 29);
            this->label8->TabIndex = 69;
            this->label8->Text = L"0. Вихід";

            this->label9->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label9->Location = System::Drawing::Point(50, 817);
            this->label9->Name = L"label9";
            this->label9->Size = System::Drawing::Size(217, 32);
            this->label9->TabIndex = 68;
            this->label9->Text = L"6. Показати поточний текст";

            this->label10->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label10->Location = System::Drawing::Point(50, 789);
            this->label10->Name = L"label10";
            this->label10->Size = System::Drawing::Size(187, 32);
            this->label10->TabIndex = 63;
            this->label10->Text = L"5. Розв'язати задачу";

            this->label13->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label13->Location = System::Drawing::Point(50, 766);
            this->label13->Name = L"label13";
            this->label13->Size = System::Drawing::Size(362, 23);
            this->label13->TabIndex = 64;
            this->label13->Text = L"4. Видалити слово";

            this->label14->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label14->Location = System::Drawing::Point(50, 734);
            this->label14->Name = L"label14";
            this->label14->Size = System::Drawing::Size(217, 20);
            this->label14->TabIndex = 65;
            this->label14->Text = L"3, Редагувати слово";

            this->label15->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label15->Location = System::Drawing::Point(50, 701);
            this->label15->Name = L"label15";
            this->label15->Size = System::Drawing::Size(217, 24);
            this->label15->TabIndex = 66;
            this->label15->Text = L"2. Ввести нові дані";

            this->label16->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label16->Location = System::Drawing::Point(50, 665);
            this->label16->Name = L"label16";
            this->label16->Size = System::Drawing::Size(217, 20);
            this->label16->TabIndex = 67;
            this->label16->Text = L"1. Задати початкові дані";

            this->label17->AutoSize = true;
            this->label17->Font = (gcnew System::Drawing::Font(L"Times New Roman", 24, System::Drawing::FontStyle::Bold));
            this->label17->Location = System::Drawing::Point(48, 579);
            this->label17->Name = L"label17";
            this->label17->Size = System::Drawing::Size(256, 36);
            this->label17->TabIndex = 70;
            this->label17->Text = L"Виберіть опцію: ";

            this->dataGridView2->Location = System::Drawing::Point(726, 524);
            this->dataGridView2->Name = L"dataGridView2";
            this->dataGridView2->Size = System::Drawing::Size(749, 413);
            this->dataGridView2->TabIndex = 71;

            this->button6->Location = System::Drawing::Point(135, 630);
            this->button6->Name = L"button6";
            this->button6->Size = System::Drawing::Size(91, 23);
            this->button6->TabIndex = 73;
            this->button6->Text = L"Підтвердити";
            this->button6->Click += gcnew System::EventHandler(this, &MyForm4::button6_Click);

            this->numericUpDown2->Location = System::Drawing::Point(54, 633);
            this->numericUpDown2->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 6, 0, 0, 0 });
            this->numericUpDown2->Name = L"numericUpDown2";
            this->numericUpDown2->Size = System::Drawing::Size(38, 20);
            this->numericUpDown2->TabIndex = 72;

            this->textBox12->Location = System::Drawing::Point(390, 665);
            this->textBox12->Name = L"textBox12";
            this->textBox12->Size = System::Drawing::Size(100, 20);
            this->textBox12->TabIndex = 75;
            this->textBox12->Text = L"Введіть текст без пробілів та пунктуації";

            this->textBox13->Location = System::Drawing::Point(284, 665);
            this->textBox13->Name = L"textBox13";
            this->textBox13->Size = System::Drawing::Size(100, 20);
            this->textBox13->TabIndex = 74;
            this->textBox13->Text = L"Максимальна довжина рядка";

            this->button7->Location = System::Drawing::Point(510, 665);
            this->button7->Name = L"button7";
            this->button7->Size = System::Drawing::Size(75, 23);
            this->button7->TabIndex = 76;
            this->button7->Text = L"Ввести";
            this->button7->UseVisualStyleBackColor = true;
            this->button7->Click += gcnew System::EventHandler(this, &MyForm4::button7_Click);

            this->button8->Location = System::Drawing::Point(510, 701);
            this->button8->Name = L"button8";
            this->button8->Size = System::Drawing::Size(75, 23);
            this->button8->TabIndex = 79;
            this->button8->Text = L"Ввести";
            this->button8->UseVisualStyleBackColor = true;
            this->button8->Click += gcnew System::EventHandler(this, &MyForm4::button8_Click);

            this->textBox14->Location = System::Drawing::Point(390, 701);
            this->textBox14->Name = L"textBox14";
            this->textBox14->Size = System::Drawing::Size(100, 20);
            this->textBox14->TabIndex = 78;
            this->textBox14->Text = L"Введіть текст без пробілів та пунктуації";

            this->textBox15->Location = System::Drawing::Point(284, 701);
            this->textBox15->Name = L"textBox15";
            this->textBox15->Size = System::Drawing::Size(100, 20);
            this->textBox15->TabIndex = 77;
            this->textBox15->Text = L"Максимальна довжина рядка";

            this->label18->AutoSize = true;
            this->label18->Font = (gcnew System::Drawing::Font(L"Times New Roman", 24, System::Drawing::FontStyle::Bold));
            this->label18->Location = System::Drawing::Point(966, 485);
            this->label18->Name = L"label18";
            this->label18->Size = System::Drawing::Size(294, 36);
            this->label18->TabIndex = 80;
            this->label18->Text = L"Виведення результату";

            this->button9->Location = System::Drawing::Point(510, 736);
            this->button9->Name = L"button9";
            this->button9->Size = System::Drawing::Size(75, 23);
            this->button9->TabIndex = 83;
            this->button9->Text = L"Ввести";
            this->button9->UseVisualStyleBackColor = true;
            this->button9->Click += gcnew System::EventHandler(this, &MyForm4::button9_Click);

            this->textBox16->Location = System::Drawing::Point(390, 736);
            this->textBox16->Name = L"textBox16";
            this->textBox16->Size = System::Drawing::Size(100, 20);
            this->textBox16->TabIndex = 82;
            this->textBox16->Text = L"Нове слово";

            this->textBox17->Location = System::Drawing::Point(284, 736);
            this->textBox17->Name = L"textBox17";
            this->textBox17->Size = System::Drawing::Size(100, 20);
            this->textBox17->TabIndex = 81;
            this->textBox17->Text = L"Номер слова (почанаючи з 1)";

            this->button10->Location = System::Drawing::Point(404, 766);
            this->button10->Name = L"button10";
            this->button10->Size = System::Drawing::Size(75, 23);
            this->button10->TabIndex = 85;
            this->button10->Text = L"Ввести";
            this->button10->UseVisualStyleBackColor = true;
            this->button10->Click += gcnew System::EventHandler(this, &MyForm4::button10_Click);

            this->textBox18->Location = System::Drawing::Point(284, 768);
            this->textBox18->Name = L"textBox18";
            this->textBox18->Size = System::Drawing::Size(100, 20);
            this->textBox18->TabIndex = 84;
            this->textBox18->Text = L"Слово яке потрібно видалити";

            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(1929, 988);
            this->Controls->Add(this->button10);
            this->Controls->Add(this->textBox18);
            this->Controls->Add(this->button9);
            this->Controls->Add(this->textBox16);
            this->Controls->Add(this->textBox17);
            this->Controls->Add(this->label18);
            this->Controls->Add(this->button8);
            this->Controls->Add(this->textBox14);
            this->Controls->Add(this->textBox15);
            this->Controls->Add(this->button7);
            this->Controls->Add(this->textBox12);
            this->Controls->Add(this->textBox13);
            this->Controls->Add(this->button6);
            this->Controls->Add(this->numericUpDown2);
            this->Controls->Add(this->dataGridView2);
            this->Controls->Add(this->label17);
            this->Controls->Add(this->label8);
            this->Controls->Add(this->label9);
            this->Controls->Add(this->label10);
            this->Controls->Add(this->label13);
            this->Controls->Add(this->label14);
            this->Controls->Add(this->label15);
            this->Controls->Add(this->label16);
            this->Controls->Add(this->textBox10);
            this->Controls->Add(this->textBox11);
            this->Controls->Add(this->button5);
            this->Controls->Add(this->textBox7);
            this->Controls->Add(this->textBox8);
            this->Controls->Add(this->button4);
            this->Controls->Add(this->textBox9);
            this->Controls->Add(this->textBox4);
            this->Controls->Add(this->textBox5);
            this->Controls->Add(this->button3);
            this->Controls->Add(this->textBox6);
            this->Controls->Add(this->textBox3);
            this->Controls->Add(this->textBox2);
            this->Controls->Add(this->button2);
            this->Controls->Add(this->textBox1);
            this->Controls->Add(this->label7);
            this->Controls->Add(this->label11);
            this->Controls->Add(this->button1);
            this->Controls->Add(this->numericUpDown1);
            this->Controls->Add(this->label1);
            this->Controls->Add(this->label6);
            this->Controls->Add(this->label5);
            this->Controls->Add(this->label4);
            this->Controls->Add(this->label3);
            this->Controls->Add(this->label2);
            this->Controls->Add(this->label12);
            this->Controls->Add(this->dataGridView1);
            this->Name = L"MyForm4";
            this->Text = L"MyForm4";
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown2))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();
        }
#pragma endregion

    private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
        int choice = (int)numericUpDown1->Value;
        switch (choice) {
        case 1:
            textBox1->Visible = true;
            textBox2->Visible = true;
            textBox3->Visible = true;
            button2->Visible = true;
            break;
        case 2:
            textBox6->Visible = true;
            textBox5->Visible = true;
            textBox4->Visible = true;
            button3->Visible = true;
            break;
        case 3:
            textBox9->Visible = true;
            textBox8->Visible = true;
            textBox7->Visible = true;
            button4->Visible = true;
            break;
        case 4:
            textBox11->Visible = true;
            textBox10->Visible = true;
            button5->Visible = true;
            break;
        case 5:
        {
            int result = DynamicSolver::findMinCostPath(
                inputData->getField(),
                inputData->getStart(),
                inputData->getFinish()
            );
            if (result == INT_MAX) {
                MessageBox::Show("Неможливо знайти шлях з заданими параметрами", "Помилка",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
            else {
                MessageBox::Show("Мінімальні витрати очок від [S] до [F]: " + result.ToString(),
                    "Результат", MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
        }
        break;
        case 6:
        {
            auto field = inputData->getField();
            int rows = inputData->getRows();
            int cols = inputData->getCols();
            auto start = inputData->getStart();
            auto finish = inputData->getFinish();
            dataGridView1->Rows->Clear();
            dataGridView1->Columns->Clear();
            for (int j = 0; j < cols; j++) {
                String^ columnName = "Column " + j.ToString();
                dataGridView1->Columns->Add(columnName, columnName);
            }
            for (int i = 0; i < rows; i++) {
                array<String^>^ rowValues = gcnew array<String^>(cols);
                for (int j = 0; j < cols; j++) {
                    if (i == start.first && j == start.second) {
                        rowValues[j] = "[S]";
                    }
                    else if (i == finish.first && j == finish.second) {
                        rowValues[j] = "[F]";
                    }
                    else {
                        rowValues[j] = field[i][j].ToString();
                    }
                }
                dataGridView1->Rows->Add(rowValues);
            }
        }
        break;
        case 0:
            this->Close();
            break;
        default:
            MessageBox::Show("Невірний вибір!", "Помилка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
        if (choice != 1) {
            textBox1->Visible = false;
            textBox2->Visible = false;
            textBox3->Visible = false;
            button2->Visible = false;
        }
        if (choice != 2) {
            textBox6->Visible = false;
            textBox5->Visible = false;
            textBox4->Visible = false;
            button3->Visible = false;
        }
        if (choice != 3) {
            textBox9->Visible = false;
            textBox8->Visible = false;
            textBox7->Visible = false;
            button4->Visible = false;
        }
        if (choice != 4) {
            textBox11->Visible = false;
            textBox10->Visible = false;
            button5->Visible = false;
        }
    }

    private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
        try {
            int rows = int::Parse(textBox1->Text);
            int cols = int::Parse(textBox2->Text);
            array<String^>^ valuesStr = textBox3->Text->Split(' ');
            std::vector<int> values;
            for (int i = 0; i < valuesStr->Length; i++) {
                String^ val = valuesStr[i];
                if (!String::IsNullOrWhiteSpace(val)) {
                    values.push_back(int::Parse(val));
                }
            }
            if (values.size() < rows * cols) {
                MessageBox::Show("Недостатньо значень для заповнення поля", "Помилка",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }
            inputData->setInitialData(rows, cols, values);
            MessageBox::Show("Початкові дані успішно задані!", "Успіх",
                MessageBoxButtons::OK, MessageBoxIcon::Information);
        }
        catch (Exception^ ex) {
            MessageBox::Show("Помилка вводу: " + ex->Message, "Помилка",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
        try {
            int rows = int::Parse(textBox6->Text);
            int cols = int::Parse(textBox5->Text);
            array<String^>^ valuesStr = textBox4->Text->Split(' ');
            std::vector<int> values;
            for (int i = 0; i < valuesStr->Length; i++) {
                String^ val = valuesStr[i];
                if (!String::IsNullOrWhiteSpace(val)) {
                    values.push_back(int::Parse(val));
                }
            }
            if (values.size() < rows * cols) {
                MessageBox::Show("Недостатньо значень для заповнення поля", "Помилка",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }
            inputData->setInitialData(rows, cols, values);
            MessageBox::Show("Нові параметри успішно задані!", "Успіх",
                MessageBoxButtons::OK, MessageBoxIcon::Information);
        }
        catch (Exception^ ex) {
            MessageBox::Show("Помилка вводу: " + ex->Message, "Помилка",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
        try {
            int row = int::Parse(textBox9->Text);
            int col = int::Parse(textBox8->Text);
            int value = int::Parse(textBox7->Text);
            inputData->editParameter(row, col, value);
            MessageBox::Show("Параметр успішно відредаговано!", "Успіх",
                MessageBoxButtons::OK, MessageBoxIcon::Information);
        }
        catch (Exception^ ex) {
            MessageBox::Show("Помилка вводу: " + ex->Message, "Помилка",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    private: System::Void button5_Click(System::Object^ sender, System::EventArgs^ e) {
        try {
            int row = int::Parse(textBox11->Text);
            int col = int::Parse(textBox10->Text);
            inputData->deleteParameter(row, col);
            MessageBox::Show("Параметр успішно видалено (значення = 0)!", "Успіх",
                MessageBoxButtons::OK, MessageBoxIcon::Information);
        }
        catch (Exception^ ex) {
            MessageBox::Show("Помилка вводу: " + ex->Message, "Помилка",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    private: System::Void button6_Click(System::Object^ sender, System::EventArgs^ e) {
        int choice = (int)numericUpDown2->Value;
        switch (choice) {
        case 1:
            textBox13->Visible = true;
            textBox12->Visible = true;
            button7->Visible = true;
            break;
        case 2:
            textBox15->Visible = true;
            textBox14->Visible = true;
            button8->Visible = true;
            break;
        case 3:
            textBox17->Visible = true;
            textBox16->Visible = true;
            button9->Visible = true;
            break;
        case 4:
            textBox18->Visible = true;
            button10->Visible = true;
            break;
        case 5:
        {
            auto result = textFormatter->solveProblem();
            auto lines = result.first;
            int penalty = result.second;
            if (lines.empty()) {
                MessageBox::Show("Немає тексту для форматування", "Помилка",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
            else {
                dataGridView2->Rows->Clear();
                dataGridView2->Columns->Clear();
                dataGridView2->Columns->Add("LineNumber", "№ рядка");
                dataGridView2->Columns->Add("LineContent", "Рядок");
                for (int i = 0; i < lines.size(); i++) {
                    array<String^>^ rowValues = gcnew array<String^>(2);
                    rowValues[0] = (i + 1).ToString();
                    rowValues[1] = marshal_as<String^>(lines[i]);
                    dataGridView2->Rows->Add(rowValues);
                }
                array<String^>^ penaltyRow = gcnew array<String^>(2);
                penaltyRow[0] = "Штраф:";
                penaltyRow[1] = penalty.ToString();
                dataGridView2->Rows->Add(penaltyRow);
                MessageBox::Show("Мінімальна сума квадратів зайвих пробілів: " + penalty.ToString(),
                    "Результат", MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
        }
        break;
        case 6:
        {
            auto words = textFormatter->getWords();
            dataGridView2->Rows->Clear();
            dataGridView2->Columns->Clear();
            dataGridView2->Columns->Add("WordNumber", "№");
            dataGridView2->Columns->Add("Word", "Слово");
            for (int i = 0; i < words.size(); i++) {
                array<String^>^ rowValues = gcnew array<String^>(2);
                rowValues[0] = (i + 1).ToString();
                rowValues[1] = marshal_as<String^>(words[i]);
                dataGridView2->Rows->Add(rowValues);
            }
        }
        break;
        case 0:
            this->Close();
            break;
        default:
            MessageBox::Show("Невірний вибір!", "Помилка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
        if (choice != 1) {
            textBox13->Visible = false;
            textBox12->Visible = false;
            button7->Visible = false;
        }
        if (choice != 2) {
            textBox15->Visible = false;
            textBox14->Visible = false;
            button8->Visible = false;
        }
        if (choice != 3) {
            textBox17->Visible = false;
            textBox16->Visible = false;
            button9->Visible = false;
        }
        if (choice != 4) {
            textBox18->Visible = false;
            button10->Visible = false;
        }
    }

    private: System::Void button7_Click(System::Object^ sender, System::EventArgs^ e) {
        try {
            int maxLength = int::Parse(textBox13->Text);
            std::string text = marshal_as<std::string>(textBox12->Text);
            if (maxLength <= 0) {
                throw gcnew Exception("Максимальна довжина рядка повинна бути більше 0");
            }
            textFormatter->setInitialData(maxLength, text);
            MessageBox::Show("Початкові дані успішно задані!", "Успіх",
                MessageBoxButtons::OK, MessageBoxIcon::Information);
        }
        catch (Exception^ ex) {
            MessageBox::Show("Помилка вводу: " + ex->Message, "Помилка",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    private: System::Void button8_Click(System::Object^ sender, System::EventArgs^ e) {
        try {
            int maxLength = int::Parse(textBox15->Text);
            std::string text = marshal_as<std::string>(textBox14->Text);
            if (maxLength <= 0) {
                throw gcnew Exception("Максимальна довжина рядка повинна бути більше 0");
            }
            textFormatter->setInitialData(maxLength, text);
            MessageBox::Show("Нові параметри успішно задані!", "Успіх",
                MessageBoxButtons::OK, MessageBoxIcon::Information);
        }
        catch (Exception^ ex) {
            MessageBox::Show("Помилка вводу: " + ex->Message, "Помилка",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    private: System::Void button9_Click(System::Object^ sender, System::EventArgs^ e) {
        try {
            int index = int::Parse(textBox17->Text) - 1;
            std::string newWord = marshal_as<std::string>(textBox16->Text);
            if (index < 0) {
                throw gcnew Exception("Номер слова повинен бути більше 0");
            }
            textFormatter->editWord(index, newWord);
            MessageBox::Show("Слово успішно відредаговано!", "Успіх",
                MessageBoxButtons::OK, MessageBoxIcon::Information);
        }
        catch (Exception^ ex) {
            MessageBox::Show("Помилка вводу: " + ex->Message, "Помилка",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    private: System::Void button10_Click(System::Object^ sender, System::EventArgs^ e) {
        try {
            int index = int::Parse(textBox18->Text) - 1;
            if (index < 0) {
                throw gcnew Exception("Номер слова повинен бути більше 0");
            }
            textFormatter->deleteWord(index);
            MessageBox::Show("Слово успішно видалено!", "Успіх",
                MessageBoxButtons::OK, MessageBoxIcon::Information);
        }
        catch (Exception^ ex) {
            MessageBox::Show("Помилка вводу: " + ex->Message, "Помилка",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }
    };
}
