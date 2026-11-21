#pragma once
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <climits>

namespace Finals {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

#pragma unmanaged

    class Graph {
    private:
        int V;
        std::vector<std::vector<int>> adj;
        bool directed;
    public:
        Graph(int vertices, bool isDirected = false) : V(vertices), directed(isDirected) {
            adj.resize(V);
        }
        void addEdge(int u, int v) {
            adj[u].push_back(v);
            if (!directed) {
                adj[v].push_back(u);
            }
        }
        std::vector<int> getNeighbors(int u) const {
            if (u < 0 || u >= V)
                return std::vector<int>();
            return adj[u];
        }
        int getV() const {
            return V;
        }
        bool isDirected() const {
            return directed;
        }
        std::pair<std::vector<int>, std::vector<int>> iterativeDFSTree(int start) {
            std::vector<bool> visited(V, false);
            std::vector<int> parent(V, -1);
            std::vector<int> order;
            std::stack<std::pair<int, int>> st;
            st.push({ start, 0 });
            parent[start] = -1;
            visited[start] = true;
            order.push_back(start);
            while (!st.empty()) {
                int v = st.top().first;
                int& idx = st.top().second;
                bool pushed = false;
                while (idx < (int)adj[v].size()) {
                    int to = adj[v][idx++];
                    if (!visited[to]) {
                        visited[to] = true;
                        parent[to] = v;
                        st.push({ to, 0 });
                        order.push_back(to);
                        pushed = true;
                        break;
                    }
                }
                if (!pushed) {
                    st.pop();
                }
            }
            return { parent, order };
        }
        std::pair<std::vector<int>, std::vector<int>> BFSTree(int start) {
            std::vector<bool> visited(V, false);
            std::vector<int> parent(V, -1);
            std::vector<int> order;
            std::queue<int> q;
            visited[start] = true;
            q.push(start);
            parent[start] = -1;
            while (!q.empty()) {
                int u = q.front(); q.pop();
                order.push_back(u);
                for (int v : adj[u]) {
                    if (!visited[v]) {
                        visited[v] = true;
                        parent[v] = u;
                        q.push(v);
                    }
                }
            }
            return { parent, order };
        }
        std::vector<int> BFS(int start, int target) {
            std::vector<bool> visited(V, false);
            std::vector<int> parent(V, -1);
            std::queue<int> q;
            visited[start] = true;
            q.push(start);
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                if (u == target) break;
                for (int v : adj[u]) {
                    if (!visited[v]) {
                        visited[v] = true;
                        parent[v] = u;
                        q.push(v);
                    }
                }
            }
            std::vector<int> path;
            if (parent[target] == -1 && target != start) {
                return path;
            }
            int current = target;
            while (current != -1) {
                path.push_back(current);
                current = parent[current];
            }
            std::reverse(path.begin(), path.end());
            return path;
        }
        void fillOrder(int v, std::vector<bool>& visited, std::stack<int>& Stack) {
            visited[v] = true;
            for (int i : adj[v]) {
                if (!visited[i]) {
                    fillOrder(i, visited, Stack);
                }
            }
            Stack.push(v);
        }
        Graph getTranspose() {
            Graph g(V, true);
            for (int v = 0; v < V; ++v) {
                for (int i : adj[v]) {
                    g.addEdge(i, v);
                }
            }
            return g;
        }
        void DFSUtilSCC(int v, std::vector<bool>& visited, std::vector<int>& component) {
            visited[v] = true;
            component.push_back(v);
            for (int i : adj[v]) {
                if (!visited[i]) {
                    DFSUtilSCC(i, visited, component);
                }
            }
        }
        std::vector<std::vector<int>> findSCCs() {
            std::stack<int> Stack;
            std::vector<bool> visited(V, false);
            for (int i = 0; i < V; ++i) {
                if (!visited[i]) {
                    fillOrder(i, visited, Stack);
                }
            }
            Graph gr = getTranspose();
            std::fill(visited.begin(), visited.end(), false);
            std::vector<std::vector<int>> sccs;
            while (!Stack.empty()) {
                int v = Stack.top();
                Stack.pop();
                if (!visited[v]) {
                    std::vector<int> component;
                    gr.DFSUtilSCC(v, visited, component);
                    sccs.push_back(component);
                }
            }
            return sccs;
        }
    };

#pragma managed

    public ref class MyForm5 : public System::Windows::Forms::Form
    {
    private:
        Graph* currentGraph;
        System::Windows::Forms::DataGridViewTextBoxColumn^ resultColumn;

    public:
        MyForm5(void)
        {
            InitializeComponent();
            currentGraph = nullptr;

            dataGridView1->ColumnCount = 1;
            resultColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            resultColumn->HeaderText = "Результат";
            resultColumn->Name = "resultColumn";
            resultColumn->ReadOnly = true;
            resultColumn->Width = 700;
            cli::array<System::Windows::Forms::DataGridViewColumn^>^ columns =
                gcnew cli::array<System::Windows::Forms::DataGridViewColumn^> { resultColumn };
            dataGridView1->Columns->AddRange(columns);

            UpdateUIState();
        }

    protected:
        ~MyForm5()
        {
            if (components)
            {
                delete components;
            }
            if (currentGraph != nullptr) {
                delete currentGraph;
                currentGraph = nullptr;
            }
        }

    private: System::Windows::Forms::Label^ label9;
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
    private: System::Windows::Forms::Label^ label10;
    private: System::Windows::Forms::Label^ label12;
    private: System::Windows::Forms::DataGridView^ dataGridView1;
    private: System::Windows::Forms::TextBox^ textBox1;
    private: System::Windows::Forms::Button^ button2;
    private: System::Windows::Forms::CheckBox^ checkBox1;
    private: System::Windows::Forms::TextBox^ textBox2;
    private: System::Windows::Forms::TextBox^ textBox3;
    private: System::Windows::Forms::Button^ button3;
    private: System::Windows::Forms::Button^ button4;
    private: System::Windows::Forms::TextBox^ textBox4;
    private: System::Windows::Forms::TextBox^ textBox5;

    private:
        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->label9 = (gcnew System::Windows::Forms::Label());
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
            this->label10 = (gcnew System::Windows::Forms::Label());
            this->label12 = (gcnew System::Windows::Forms::Label());
            this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
            this->textBox1 = (gcnew System::Windows::Forms::TextBox());
            this->button2 = (gcnew System::Windows::Forms::Button());
            this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
            this->textBox2 = (gcnew System::Windows::Forms::TextBox());
            this->textBox3 = (gcnew System::Windows::Forms::TextBox());
            this->button3 = (gcnew System::Windows::Forms::Button());
            this->button4 = (gcnew System::Windows::Forms::Button());
            this->textBox4 = (gcnew System::Windows::Forms::TextBox());
            this->textBox5 = (gcnew System::Windows::Forms::TextBox());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
            this->SuspendLayout();

            this->label9->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label9->Location = System::Drawing::Point(83, 374);
            this->label9->Name = L"label9";
            this->label9->Size = System::Drawing::Size(328, 22);
            this->label9->TabIndex = 40;
            this->label9->Text = L"8. Вивести BFS-дерево (з вершини)";

            this->label8->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label8->Location = System::Drawing::Point(83, 342);
            this->label8->Name = L"label8";
            this->label8->Size = System::Drawing::Size(417, 23);
            this->label8->TabIndex = 41;
            this->label8->Text = L"7. Вивести DFS-дерево (з вершини)";

            this->label7->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label7->Location = System::Drawing::Point(83, 309);
            this->label7->Name = L"label7";
            this->label7->Size = System::Drawing::Size(212, 20);
            this->label7->TabIndex = 42;
            this->label7->Text = L"6. Виконати задачу В (Сильно зв\'язані компоненти)";

            this->label6->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label6->Location = System::Drawing::Point(83, 275);
            this->label6->Name = L"label6";
            this->label6->Size = System::Drawing::Size(366, 20);
            this->label6->TabIndex = 43;
            this->label6->Text = L"5. Виконати задачу А (Проблема переправи)";

            this->label5->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label5->Location = System::Drawing::Point(83, 241);
            this->label5->Name = L"label5";
            this->label5->Size = System::Drawing::Size(366, 23);
            this->label5->TabIndex = 44;
            this->label5->Text = L"4. Виконати задачу Г (Найкоротший шлях)";

            this->label4->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label4->Location = System::Drawing::Point(83, 210);
            this->label4->Name = L"label4";
            this->label4->Size = System::Drawing::Size(145, 18);
            this->label4->TabIndex = 45;
            this->label4->Text = L"3. Вивести граф";

            this->label3->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label3->Location = System::Drawing::Point(83, 177);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(222, 24);
            this->label3->TabIndex = 46;
            this->label3->Text = L"2. Додати ребро до графа";

            this->button1->Location = System::Drawing::Point(168, 99);
            this->button1->Name = L"button1";
            this->button1->Size = System::Drawing::Size(91, 23);
            this->button1->TabIndex = 37;
            this->button1->Text = L"Підтвердити";
            this->button1->Click += gcnew System::EventHandler(this, &MyForm5::button1_Click);

            this->numericUpDown1->Location = System::Drawing::Point(87, 102);
            this->numericUpDown1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
            this->numericUpDown1->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
            this->numericUpDown1->Name = L"numericUpDown1";
            this->numericUpDown1->Size = System::Drawing::Size(38, 20);
            this->numericUpDown1->TabIndex = 36;
            this->numericUpDown1->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });

            this->label2->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label2->Location = System::Drawing::Point(83, 144);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(212, 21);
            this->label2->TabIndex = 47;
            this->label2->Text = L"1. Створити новий граф";

            this->label1->AutoSize = true;
            this->label1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 24, System::Drawing::FontStyle::Bold));
            this->label1->Location = System::Drawing::Point(81, 60);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(256, 36);
            this->label1->TabIndex = 35;
            this->label1->Text = L"Виберіть опцію: ";

            this->label10->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label10->Location = System::Drawing::Point(83, 407);
            this->label10->Name = L"label10";
            this->label10->Size = System::Drawing::Size(89, 20);
            this->label10->TabIndex = 39;
            this->label10->Text = L"9. Вихід";
            this->label10->Click += gcnew System::EventHandler(this, &MyForm5::label10_Click);

            this->label12->AutoSize = true;
            this->label12->Font = (gcnew System::Drawing::Font(L"Times New Roman", 24, System::Drawing::FontStyle::Bold));
            this->label12->Location = System::Drawing::Point(1060, 21);
            this->label12->Name = L"label12";
            this->label12->Size = System::Drawing::Size(294, 36);
            this->label12->TabIndex = 49;
            this->label12->Text = L"Виведення графа";

            this->dataGridView1->Location = System::Drawing::Point(833, 60);
            this->dataGridView1->Name = L"dataGridView1";
            this->dataGridView1->Size = System::Drawing::Size(749, 413);
            this->dataGridView1->TabIndex = 48;

            this->textBox1->Location = System::Drawing::Point(311, 145);
            this->textBox1->Name = L"textBox1";
            this->textBox1->Size = System::Drawing::Size(100, 20);
            this->textBox1->TabIndex = 50;
            this->textBox1->Text = L"Кількість вершин";
            this->textBox1->Click += gcnew System::EventHandler(this, &MyForm5::textBox1_Click);

            this->button2->Location = System::Drawing::Point(551, 145);
            this->button2->Name = L"button2";
            this->button2->Size = System::Drawing::Size(91, 20);
            this->button2->TabIndex = 51;
            this->button2->Text = L"Ввести";
            this->button2->UseVisualStyleBackColor = true;
            this->button2->Click += gcnew System::EventHandler(this, &MyForm5::button2_Click);

            this->checkBox1->AutoSize = true;
            this->checkBox1->Location = System::Drawing::Point(417, 147);
            this->checkBox1->Name = L"checkBox1";
            this->checkBox1->Size = System::Drawing::Size(128, 17);
            this->checkBox1->TabIndex = 52;
            this->checkBox1->Text = L"Граф орієнтований?";
            this->checkBox1->UseVisualStyleBackColor = true;

            this->textBox2->Location = System::Drawing::Point(327, 179);
            this->textBox2->Name = L"textBox2";
            this->textBox2->Size = System::Drawing::Size(100, 20);
            this->textBox2->TabIndex = 53;
            this->textBox2->Text = L"Перша вершина";
            this->textBox2->Click += gcnew System::EventHandler(this, &MyForm5::textBox2_Click);

            this->textBox3->Location = System::Drawing::Point(433, 178);
            this->textBox3->Name = L"textBox3";
            this->textBox3->Size = System::Drawing::Size(100, 20);
            this->textBox3->TabIndex = 54;
            this->textBox3->Text = L"Друга вершина";
            this->textBox3->Click += gcnew System::EventHandler(this, &MyForm5::textBox3_Click);

            this->button3->Location = System::Drawing::Point(551, 178);
            this->button3->Name = L"button3";
            this->button3->Size = System::Drawing::Size(91, 20);
            this->button3->TabIndex = 55;
            this->button3->Text = L"Ввести";
            this->button3->UseVisualStyleBackColor = true;
            this->button3->Click += gcnew System::EventHandler(this, &MyForm5::button3_Click);

            this->button4->Location = System::Drawing::Point(672, 241);
            this->button4->Name = L"button4";
            this->button4->Size = System::Drawing::Size(91, 20);
            this->button4->TabIndex = 58;
            this->button4->Text = L"Ввести";
            this->button4->UseVisualStyleBackColor = true;
            this->button4->Click += gcnew System::EventHandler(this, &MyForm5::button4_Click);

            this->textBox4->Location = System::Drawing::Point(554, 241);
            this->textBox4->Name = L"textBox4";
            this->textBox4->Size = System::Drawing::Size(100, 20);
            this->textBox4->TabIndex = 57;
            this->textBox4->Text = L"Кінцева вершина";
            this->textBox4->Click += gcnew System::EventHandler(this, &MyForm5::textBox4_Click);

            this->textBox5->Location = System::Drawing::Point(448, 242);
            this->textBox5->Name = L"textBox5";
            this->textBox5->Size = System::Drawing::Size(100, 20);
            this->textBox5->TabIndex = 56;
            this->textBox5->Text = L"Початкова вершина";
            this->textBox5->Click += gcnew System::EventHandler(this, &MyForm5::textBox5_Click);

            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(1838, 631);
            this->Controls->Add(this->button4);
            this->Controls->Add(this->textBox4);
            this->Controls->Add(this->textBox5);
            this->Controls->Add(this->button3);
            this->Controls->Add(this->textBox3);
            this->Controls->Add(this->textBox2);
            this->Controls->Add(this->checkBox1);
            this->Controls->Add(this->button2);
            this->Controls->Add(this->textBox1);
            this->Controls->Add(this->label12);
            this->Controls->Add(this->dataGridView1);
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
            this->Controls->Add(this->label1);
            this->Name = L"MyForm5";
            this->Text = L"MyForm5";
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion

    private: System::Void UpdateUIState() {
        if (currentGraph == nullptr) {
            button2->Enabled = true;
            button3->Enabled = false;
            button4->Enabled = false;
        }
        else {
            button2->Enabled = false;
            button3->Enabled = true;
            button4->Enabled = true;
        }
    }

    private: System::Void ClearResults() {
        dataGridView1->Rows->Clear();
    }

    private: System::Void AddResultRow(System::String^ text) {
        int rowIndex = dataGridView1->Rows->Add();
        dataGridView1->Rows[rowIndex]->Cells[0]->Value = text;
    }

    private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
        int option = (int)numericUpDown1->Value;

        ClearResults();

        switch (option) {
        case 1:
            AddResultRow("Вибрано опцію 1: Створити новий граф");
            AddResultRow("Використовуйте поля вводу нижче для створення графа:");
            AddResultRow("- Введіть кількість вершин");
            AddResultRow("- Вкажіть, чи орієнтований граф");
            AddResultRow("- Натисніть кнопку \"Ввести\"");
            break;
        case 2:
            AddResultRow("Вибрано опцію 2: Додати ребро до графа");
            AddResultRow("Використовуйте поля вводу нижче для додавання ребра:");
            AddResultRow("- Введіть першу вершину");
            AddResultRow("- Введіть другу вершину");
            AddResultRow("- Натисніть кнопку \"Ввести\"");
            break;
        case 3:
            AddResultRow("Вибрано опцію 3: Вивести граф");
            PrintGraph();
            break;
        case 4:
            AddResultRow("Вибрано опцію 4: Виконати задачу Г (Найкоротший шлях)");
            AddResultRow("Використовуйте поля вводу нижче для вказівки вершин:");
            AddResultRow("- Введіть початкову вершину");
            AddResultRow("- Введіть кінцеву вершину");
            AddResultRow("- Натисніть кнопку \"Ввести\"");
            break;
        case 5:
            AddResultRow("Вибрано опцію 5: Виконати задачу А (Проблема переправи)");
            SolveFerryProblem();
            break;
        case 6:
            AddResultRow("Вибрано опцію 6: Виконати задачу В (Сильно зв'язані компоненти)");
            FindSCCs();
            break;
        case 7:
            if (currentGraph == nullptr) {
                AddResultRow("Помилка: Спочатку створіть граф!");
                return;
            }
            AddResultRow("Вибрано опцію 7: Вивести DFS-дерево (з вершини 0)");
            PrintDFSTree(0);
            break;
        case 8:
            if (currentGraph == nullptr) {
                AddResultRow("Помилка: Спочатку створіть граф!");
                return;
            }
            AddResultRow("Вибрано опцію 8: Вивести BFS-дерево (з вершини 0)");
            PrintBFSTree(0);
            break;
        case 9:
            AddResultRow("Вибрано опцію 9: Вихід");
            Application::Exit();
            break;
        default:
            AddResultRow("Невірний вибір. Спробуйте ще раз.");
            break;
        }
    }

    private: System::Void textBox1_Click(System::Object^ sender, System::EventArgs^ e) {
        textBox1->Text = "";
    }

    private: System::Void textBox2_Click(System::Object^ sender, System::EventArgs^ e) {
        textBox2->Text = "";
    }

    private: System::Void textBox3_Click(System::Object^ sender, System::EventArgs^ e) {
        textBox3->Text = "";
    }

    private: System::Void textBox4_Click(System::Object^ sender, System::EventArgs^ e) {
        textBox4->Text = "";
    }

    private: System::Void textBox5_Click(System::Object^ sender, System::EventArgs^ e) {
        textBox5->Text = "";
    }

    private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
        ClearResults();

        try {
            int vertices = System::Convert::ToInt32(textBox1->Text);
            if (vertices <= 0) {
                AddResultRow("Помилка: Кількість вершин повинна бути додатною");
                return;
            }

            bool isDirected = checkBox1->Checked;

            if (currentGraph != nullptr) {
                delete currentGraph;
            }

            currentGraph = new Graph(vertices, isDirected);

            AddResultRow("Граф створено:");
            AddResultRow("Кількість вершин: " + vertices);
            AddResultRow("Тип графа: " + (isDirected ? "Орієнтований" : "Неорієнтований"));

            UpdateUIState();
        }
        catch (...) {
            AddResultRow("Помилка: Неправильний формат введення кількості вершин");
        }
    }

    private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
        ClearResults();

        if (currentGraph == nullptr) {
            AddResultRow("Помилка: Спочатку створіть граф!");
            return;
        }

        try {
            int u = System::Convert::ToInt32(textBox2->Text);
            int v = System::Convert::ToInt32(textBox3->Text);
            int maxVertex = currentGraph->getV() - 1;

            if (u < 0 || u > maxVertex || v < 0 || v > maxVertex) {
                AddResultRow("Помилка: Вершини мають бути в діапазоні [0, " + maxVertex + "]");
                return;
            }

            currentGraph->addEdge(u, v);

            if (currentGraph->isDirected()) {
                AddResultRow("Орієнтоване ребро (" + u + " -> " + v + ") додано.");
            }
            else {
                AddResultRow("Неорієнтоване ребро (" + u + " -- " + v + ") додано.");
            }
        }
        catch (...) {
            AddResultRow("Помилка: Неправильний формат введення вершин");
        }
    }

    private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
        ClearResults();

        if (currentGraph == nullptr) {
            AddResultRow("Помилка: Спочатку створіть граф!");
            return;
        }

        try {
            int start = System::Convert::ToInt32(textBox5->Text);
            int end = System::Convert::ToInt32(textBox4->Text);
            int maxVertex = currentGraph->getV() - 1;

            if (start < 0 || start > maxVertex || end < 0 || end > maxVertex) {
                AddResultRow("Помилка: Вершини мають бути в діапазоні [0, " + maxVertex + "]");
                return;
            }

            std::vector<int> path = currentGraph->BFS(start, end);

            if (path.empty()) {
                AddResultRow("Шлях між вершинами " + start + " та " + end + " не існує.");
            }
            else {
                System::String^ pathStr = "Найкоротший шлях: ";
                for (size_t i = 0; i < path.size(); ++i) {
                    pathStr += path[i];
                    if (i < path.size() - 1) pathStr += " -> ";
                }
                AddResultRow(pathStr);
                AddResultRow("Кількість ребер: " + (path.size() - 1));
            }
        }
        catch (...) {
            AddResultRow("Помилка: Неправильний формат введення вершин");
        }
    }

    private: System::Void label10_Click(System::Object^ sender, System::EventArgs^ e) {
        Application::Exit();
    }

    private: System::Void PrintGraph() {
        ClearResults();

        if (currentGraph == nullptr) {
            AddResultRow("Помилка: Граф не створено!");
            return;
        }

        AddResultRow("Граф (Вершин=" + currentGraph->getV() + ", Орієнтований=" +
            (currentGraph->isDirected() ? "Так" : "Ні") + "):");

        AddResultRow("Структура графа:");
        for (int u = 0; u < currentGraph->getV(); ++u) {
            std::vector<int> neighbors = currentGraph->getNeighbors(u);
            System::String^ neighborsStr = "";

            if (neighbors.empty()) {
                neighborsStr = "немає сусідів";
            }
            else {
                for (size_t i = 0; i < neighbors.size(); i++) {
                    neighborsStr += neighbors[i].ToString();
                    if (i < neighbors.size() - 1) neighborsStr += ", ";
                }
            }

            AddResultRow("Вершина " + u + ": " + neighborsStr);
        }
    }

    private: System::Void PrintDFSTree(int start) {
        ClearResults();

        if (currentGraph == nullptr) {
            AddResultRow("Помилка: Граф не створено!");
            return;
        }

        if (start < 0 || start >= currentGraph->getV()) {
            AddResultRow("Помилка: Неправильна вершина для DFS.");
            return;
        }

        auto res = currentGraph->iterativeDFSTree(start);
        std::vector<int> parent = res.first;
        std::vector<int> order = res.second;

        System::String^ dfsOrder = "DFS обхід з вершини " + start + ": ";
        for (size_t i = 0; i < order.size(); i++) {
            dfsOrder += order[i] + " ";
        }
        AddResultRow(dfsOrder);

        AddResultRow("DFS дерево (дитина -> батько):");
        for (int v = 0; v < currentGraph->getV(); ++v) {
            if (parent[v] != -1)
                AddResultRow(v + " -> " + parent[v]);
        }
    }

    private: System::Void PrintBFSTree(int start) {
        ClearResults();

        if (currentGraph == nullptr) {
            AddResultRow("Помилка: Граф не створено!");
            return;
        }

        if (start < 0 || start >= currentGraph->getV()) {
            AddResultRow("Помилка: Неправильна вершина для BFS.");
            return;
        }

        auto res = currentGraph->BFSTree(start);
        std::vector<int> parent = res.first;
        std::vector<int> order = res.second;

        System::String^ bfsOrder = "BFS обхід з вершини " + start + ": ";
        for (size_t i = 0; i < order.size(); i++) {
            bfsOrder += order[i] + " ";
        }
        AddResultRow(bfsOrder);

        AddResultRow("BFS дерево (дитина -> батько):");
        for (int v = 0; v < currentGraph->getV(); ++v) {
            if (parent[v] != -1)
                AddResultRow(v + " -> " + parent[v]);
        }
    }

    private: System::Void FindSCCs() {
        ClearResults();

        if (currentGraph == nullptr) {
            AddResultRow("Помилка: Граф не створено!");
            return;
        }

        if (!currentGraph->isDirected()) {
            AddResultRow("Попередження: Задача призначена для орієнтованих графів.");
            AddResultRow("Продовжуємо для заданого графа.");
        }

        std::vector<std::vector<int>> sccs = currentGraph->findSCCs();

        AddResultRow("Знайдено " + sccs.size() + " сильно зв'язаних компонент:");
        for (size_t i = 0; i < sccs.size(); ++i) {
            System::String^ component = "Компонента " + (i + 1) + ": ";
            for (size_t j = 0; j < sccs[i].size(); j++) {
                component += sccs[i][j] + " ";
            }
            AddResultRow(component);
        }
    }

    private: bool IsValidState(int state) {
        int man = (state >> 4) & 1;
        int thore = (state >> 3) & 1;
        int cat = (state >> 2) & 1;
        int chicken = (state >> 1) & 1;
        int pot = state & 1;

        if (man != thore && thore == cat) return false;
        if (man != cat && cat == chicken) return false;
        if (man != chicken && chicken == thore) return false;
        if (man != chicken && chicken == pot) return false;
        return true;
    }

    private: std::vector<int> GetNextStates(int state) {
        std::vector<int> nextStates;
        int man = (state >> 4) & 1;
        std::vector<int> companions;

        for (int i = 0; i < 4; i++) {
            if (((state >> i) & 1) == man) {
                companions.push_back(i);
            }
        }

        int newMan = man ^ 1;

        int newState = state ^ (1 << 4);
        if (IsValidState(newState)) {
            nextStates.push_back(newState);
        }

        for (int item : companions) {
            newState = state ^ (1 << 4) ^ (1 << item);
            if (IsValidState(newState)) {
                nextStates.push_back(newState);
            }
        }

        for (size_t i = 0; i < companions.size(); i++) {
            for (size_t j = i + 1; j < companions.size(); j++) {
                int item1 = companions[i];
                int item2 = companions[j];

                if ((item1 >= 1 && item1 <= 3 && item2 >= 1 && item2 <= 3) ||
                    ((item1 == 0 || item2 == 0) && ((item1 >= 1 && item1 <= 3) || (item2 >= 1 && item2 <= 3)))) {

                    newState = state ^ (1 << 4) ^ (1 << item1) ^ (1 << item2);
                    if (IsValidState(newState)) {
                        nextStates.push_back(newState);
                    }
                }
            }
        }

        return nextStates;
    }

    private: System::Void SolveFerryProblem() {
        ClearResults();
        AddResultRow("=== ЗАДАЧА А: Проблема переправи (тхор, кішка, курка, казан з зерном) ===");

        std::queue<int> q;
        std::map<int, int> parent;
        std::set<int> visited;

        int startState = 0;
        int targetState = 31;

        q.push(startState);
        visited.insert(startState);
        parent[startState] = -1;

        while (!q.empty()) {
            int curr = q.front();
            q.pop();

            if (curr == targetState) break;

            std::vector<int> nextStates = GetNextStates(curr);
            for (int next : nextStates) {
                if (visited.find(next) == visited.end()) {
                    visited.insert(next);
                    parent[next] = curr;
                    q.push(next);
                }
            }
        }

        std::vector<int> path;
        int current = targetState;
        while (current != -1) {
            path.push_back(current);
            current = parent[current];
        }
        std::reverse(path.begin(), path.end());

        AddResultRow("Розв'язок знайдено! Послідовність переходів:");

        for (size_t i = 0; i < path.size(); i++) {
            int state = path[i];
            int man = (state >> 4) & 1;
            int thore = (state >> 3) & 1;
            int cat = (state >> 2) & 1;
            int chicken = (state >> 1) & 1;
            int pot = state & 1;

            System::String^ action = "Крок " + (i + 1) + ": ";

            if (i == 0) {
                action += "Усі на лівому березі.";
            }
            else {
                int prevState = path[i - 1];
                int prevMan = (prevState >> 4) & 1;
                int prevThore = (prevState >> 3) & 1;
                int prevCat = (prevState >> 2) & 1;
                int prevChicken = (prevState >> 1) & 1;
                int prevPot = prevState & 1;

                System::Collections::Generic::List<System::String^>^ movedItems =
                    gcnew System::Collections::Generic::List<System::String^>();

                if (prevThore != thore) movedItems->Add("тхора");
                if (prevCat != cat) movedItems->Add("кішку");
                if (prevChicken != chicken) movedItems->Add("курку");
                if (prevPot != pot) movedItems->Add("казан з зерном");

                if (prevMan == 0 && man == 1) {
                    if (movedItems->Count == 0) {
                        action += "Чоловік переходить сам.";
                    }
                    else {
                        action += "Чоловік перевозить ";
                        for (int k = 0; k < movedItems->Count; k++) {
                            action += movedItems[k];
                            if (k < movedItems->Count - 1) action += " та ";
                        }
                        action += ".";
                    }
                }
                else if (prevMan == 1 && man == 0) {
                    if (movedItems->Count == 0) {
                        action += "Чоловік повертається назад.";
                    }
                    else {
                        action += "Чоловік повертається з ";
                        for (int k = 0; k < movedItems->Count; k++) {
                            action += movedItems[k];
                            if (k < movedItems->Count - 1) action += " та ";
                        }
                        action += ".";
                    }
                }
            }

            AddResultRow(action);
        }

        AddResultRow("Усі предмети успішно перевезено на правий берег!");
    }
    };
}
