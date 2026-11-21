#pragma once

#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <memory>
#include <msclr/marshal_cppstd.h>
#include <unordered_map>
#include <string>

class NetworkFlow {
private:
    int numDevices;
    std::vector<std::vector<int>> capacity;
    std::vector<std::vector<int>> flow;

    bool bfs(int source, int sink, std::vector<int>& parent) {
        std::fill(parent.begin(), parent.end(), -1);
        std::queue<int> q;
        q.push(source);
        parent[source] = -2;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v = 0; v < numDevices; ++v) {
                if (parent[v] == -1 && capacity[u][v] - flow[u][v] > 0) {
                    parent[v] = u;
                    q.push(v);
                    if (v == sink) return true;
                }
            }
        }
        return false;
    }

public:
    NetworkFlow(int devices) : numDevices(devices) {
        capacity.assign(numDevices, std::vector<int>(numDevices, 0));
        flow.assign(numDevices, std::vector<int>(numDevices, 0));
    }

    void addConnection(int fromDevice, int toDevice, int maxSpeed) {
        if (fromDevice >= 0 && fromDevice < numDevices &&
            toDevice >= 0 && toDevice < numDevices && maxSpeed >= 0) {
            capacity[fromDevice][toDevice] = maxSpeed;
        }
    }

    int maxFlow(int sourceDevice, int sinkDevice) {
        std::vector<int> parent(numDevices);
        int max_flow = 0;

        for (int i = 0; i < numDevices; ++i) {
            std::fill(flow[i].begin(), flow[i].end(), 0);
        }

        while (bfs(sourceDevice, sinkDevice, parent)) {
            int path_flow = INT_MAX;
            for (int v = sinkDevice; v != sourceDevice; v = parent[v]) {
                int u = parent[v];
                path_flow = (std::min)(path_flow, capacity[u][v] - flow[u][v]);
            }

            for (int v = sinkDevice; v != sourceDevice; v = parent[v]) {
                int u = parent[v];
                flow[u][v] += path_flow;
                flow[v][u] -= path_flow;
            }
            max_flow += path_flow;
        }
        return max_flow;
    }

    std::vector<std::pair<std::pair<int, int>, int>> getMinCutEdges(int sourceDevice) {
        std::vector<bool> visited(numDevices, false);
        std::queue<int> q;
        q.push(sourceDevice);
        visited[sourceDevice] = true;

        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v = 0; v < numDevices; ++v) {
                if (!visited[v] && capacity[u][v] - flow[u][v] > 0) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }

        std::vector<std::pair<std::pair<int, int>, int>> cutEdges;
        for (int i = 0; i < numDevices; ++i) {
            if (visited[i]) {
                for (int j = 0; j < numDevices; ++j) {
                    if (!visited[j] && capacity[i][j] > 0) {
                        cutEdges.push_back({ {i, j}, capacity[i][j] });
                    }
                }
            }
        }
        return cutEdges;
    }

    std::vector<int> getMinCutDevices(int sourceDevice) {
        std::vector<bool> visited(numDevices, false);
        std::queue<int> q;
        q.push(sourceDevice);
        visited[sourceDevice] = true;

        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v = 0; v < numDevices; ++v) {
                if (!visited[v] && capacity[u][v] - flow[u][v] > 0) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }

        std::vector<int> cut;
        for (int i = 0; i < numDevices; ++i)
            if (visited[i]) cut.push_back(i);
        return cut;
    }

    void printNetwork(System::Windows::Forms::DataGridView^ dataGridView) const {
        dataGridView->Rows->Clear();
        dataGridView->Columns->Clear();

        System::Windows::Forms::DataGridViewTextBoxColumn^ rowHeader = gcnew System::Windows::Forms::DataGridViewTextBoxColumn();
        rowHeader->HeaderText = "Пристрій";
        dataGridView->Columns->Add(rowHeader);

        for (int j = 0; j < numDevices; ++j) {
            System::Windows::Forms::DataGridViewTextBoxColumn^ col = gcnew System::Windows::Forms::DataGridViewTextBoxColumn();
            col->HeaderText = "Пристрій " + j.ToString();
            dataGridView->Columns->Add(col);
        }

        for (int i = 0; i < numDevices; ++i) {
            int rowIndex = dataGridView->Rows->Add();
            dataGridView->Rows[rowIndex]->Cells[0]->Value = "Пристрій " + i.ToString();

            for (int j = 0; j < numDevices; ++j) {
                dataGridView->Rows[rowIndex]->Cells[j + 1]->Value = capacity[i][j].ToString();
            }
        }
    }

    int getCapacity(int fromDevice, int toDevice) const {
        if (fromDevice >= 0 && fromDevice < numDevices &&
            toDevice >= 0 && toDevice < numDevices) {
            return capacity[fromDevice][toDevice];
        }
        return 0;
    }

    int getNumDevices() const {
        return numDevices;
    }
};

namespace Finals {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace msclr::interop;

    public ref class MyForm7 : public System::Windows::Forms::Form
    {
    private:
        NetworkFlow* network;
        int sourceDevice;
        int sinkDevice;

    public:
        MyForm7(void)
        {
            InitializeComponent();
            network = nullptr;
            sourceDevice = -1;
            sinkDevice = -1;

            SetupEventHandlers();
        }

    protected:
        ~MyForm7()
        {
            if (components)
            {
                delete components;
            }
            if (network != nullptr) {
                delete network;
                network = nullptr;
            }
        }
    private: System::Windows::Forms::Label^ label7;
    protected:
    private: System::Windows::Forms::Label^ label6;
    private: System::Windows::Forms::Label^ label5;
    private: System::Windows::Forms::Label^ label4;
    private: System::Windows::Forms::Label^ label3;
    private: System::Windows::Forms::Button^ button1;
    private: System::Windows::Forms::NumericUpDown^ numericUpDown1;
    private: System::Windows::Forms::Label^ label2;
    private: System::Windows::Forms::Label^ label1;
    private: System::Windows::Forms::Label^ label12;
    private: System::Windows::Forms::DataGridView^ dataGridView1;
    private: System::Windows::Forms::TextBox^ textBox4;
    private: System::Windows::Forms::TextBox^ textBox2;
    private: System::Windows::Forms::TextBox^ textBox3;
    private: System::Windows::Forms::TextBox^ textBox1;
    private: System::Windows::Forms::Button^ button3;
    private: System::Windows::Forms::Button^ button2;
    private: System::Windows::Forms::TextBox^ textBox5;
    private: System::Windows::Forms::TextBox^ textBox6;
    private: System::Windows::Forms::TextBox^ textBox7;

    private:
        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->label7 = (gcnew System::Windows::Forms::Label());
            this->label6 = (gcnew System::Windows::Forms::Label());
            this->label5 = (gcnew System::Windows::Forms::Label());
            this->label4 = (gcnew System::Windows::Forms::Label());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->button1 = (gcnew System::Windows::Forms::Button());
            this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->label12 = (gcnew System::Windows::Forms::Label());
            this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
            this->textBox4 = (gcnew System::Windows::Forms::TextBox());
            this->textBox2 = (gcnew System::Windows::Forms::TextBox());
            this->textBox3 = (gcnew System::Windows::Forms::TextBox());
            this->textBox1 = (gcnew System::Windows::Forms::TextBox());
            this->button3 = (gcnew System::Windows::Forms::Button());
            this->button2 = (gcnew System::Windows::Forms::Button());
            this->textBox5 = (gcnew System::Windows::Forms::TextBox());
            this->textBox6 = (gcnew System::Windows::Forms::TextBox());
            this->textBox7 = (gcnew System::Windows::Forms::TextBox());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
            this->SuspendLayout();

            this->label7->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label7->Location = System::Drawing::Point(57, 425);
            this->label7->Name = L"label7";
            this->label7->Size = System::Drawing::Size(417, 42);
            this->label7->TabIndex = 38;
            this->label7->Text = L"6. Вийти";

            this->label6->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label6->Location = System::Drawing::Point(57, 383);
            this->label6->Name = L"label6";
            this->label6->Size = System::Drawing::Size(417, 42);
            this->label6->TabIndex = 39;
            this->label6->Text = L"5. Показати конфігурацію мережі";

            this->label5->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label5->Location = System::Drawing::Point(57, 328);
            this->label5->Name = L"label5";
            this->label5->Size = System::Drawing::Size(417, 42);
            this->label5->TabIndex = 40;
            this->label5->Text = L"4. Показати мінімальний розріз мережі";

            this->label4->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label4->Location = System::Drawing::Point(57, 276);
            this->label4->Name = L"label4";
            this->label4->Size = System::Drawing::Size(484, 40);
            this->label4->TabIndex = 41;
            this->label4->Text = L"3. Обчислити максимальну швидкість передачі даних";

            this->label3->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label3->Location = System::Drawing::Point(57, 234);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(417, 42);
            this->label3->TabIndex = 42;
            this->label3->Text = L"2. Додати з\'єднання";

            this->button1->Location = System::Drawing::Point(142, 120);
            this->button1->Name = L"button1";
            this->button1->Size = System::Drawing::Size(91, 23);
            this->button1->TabIndex = 37;
            this->button1->Text = L"Підтвердити";

            this->numericUpDown1->Location = System::Drawing::Point(61, 123);
            this->numericUpDown1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 6, 0, 0, 0 });
            this->numericUpDown1->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
            this->numericUpDown1->Name = L"numericUpDown1";
            this->numericUpDown1->Size = System::Drawing::Size(38, 20);
            this->numericUpDown1->TabIndex = 36;
            this->numericUpDown1->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });

            this->label2->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label2->Location = System::Drawing::Point(57, 170);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(417, 21);
            this->label2->TabIndex = 43;
            this->label2->Text = L"1. Ввести конфігурацію комп\'ютерної мережі";

            this->label1->AutoSize = true;
            this->label1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 24, System::Drawing::FontStyle::Bold));
            this->label1->Location = System::Drawing::Point(55, 81);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(256, 36);
            this->label1->TabIndex = 35;
            this->label1->Text = L"Виберіть опцію: ";

            this->label12->AutoSize = true;
            this->label12->Font = (gcnew System::Drawing::Font(L"Times New Roman", 24, System::Drawing::FontStyle::Bold));
            this->label12->Location = System::Drawing::Point(1252, 42);
            this->label12->Name = L"label12";
            this->label12->Size = System::Drawing::Size(317, 36);
            this->label12->TabIndex = 45;
            this->label12->Text = L"Транспортна мережа";

            this->dataGridView1->Location = System::Drawing::Point(1035, 81);
            this->dataGridView1->Name = L"dataGridView1";
            this->dataGridView1->Size = System::Drawing::Size(749, 413);
            this->dataGridView1->TabIndex = 44;

            this->textBox4->Location = System::Drawing::Point(628, 184);
            this->textBox4->Name = L"textBox4";
            this->textBox4->Size = System::Drawing::Size(181, 20);
            this->textBox4->TabIndex = 49;
            this->textBox4->Text = L"Номер пристроя-одержувача";

            this->textBox2->Location = System::Drawing::Point(628, 158);
            this->textBox2->Name = L"textBox2";
            this->textBox2->Size = System::Drawing::Size(181, 20);
            this->textBox2->TabIndex = 48;
            this->textBox2->Text = L"Скільки з\'єднань додати";

            this->textBox3->Location = System::Drawing::Point(441, 184);
            this->textBox3->Name = L"textBox3";
            this->textBox3->Size = System::Drawing::Size(181, 20);
            this->textBox3->TabIndex = 47;
            this->textBox3->Text = L"Номер пристроя-відправника";

            this->textBox1->Location = System::Drawing::Point(441, 158);
            this->textBox1->Name = L"textBox1";
            this->textBox1->Size = System::Drawing::Size(181, 20);
            this->textBox1->TabIndex = 46;
            this->textBox1->Text = L"Кількість пристроїв у мережі";

            this->button3->Location = System::Drawing::Point(824, 170);
            this->button3->Name = L"button3";
            this->button3->Size = System::Drawing::Size(75, 23);
            this->button3->TabIndex = 50;
            this->button3->Text = L"Ввести";
            this->button3->UseVisualStyleBackColor = true;

            this->button2->Location = System::Drawing::Point(868, 233);
            this->button2->Name = L"button2";
            this->button2->Size = System::Drawing::Size(75, 23);
            this->button2->TabIndex = 53;
            this->button2->Text = L"Ввести";
            this->button2->UseVisualStyleBackColor = true;

            this->textBox5->Location = System::Drawing::Point(489, 236);
            this->textBox5->Name = L"textBox5";
            this->textBox5->Size = System::Drawing::Size(181, 20);
            this->textBox5->TabIndex = 52;
            this->textBox5->Text = L"Пристрій 2";

            this->textBox6->Location = System::Drawing::Point(293, 236);
            this->textBox6->Name = L"textBox6";
            this->textBox6->Size = System::Drawing::Size(181, 20);
            this->textBox6->TabIndex = 51;
            this->textBox6->Text = L"Пристрій 1";

            this->textBox7->Location = System::Drawing::Point(685, 236);
            this->textBox7->Name = L"textBox7";
            this->textBox7->Size = System::Drawing::Size(181, 20);
            this->textBox7->TabIndex = 54;
            this->textBox7->Text = L"Максимальна швидкість даних";

            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(1889, 722);
            this->Controls->Add(this->textBox7);
            this->Controls->Add(this->button2);
            this->Controls->Add(this->textBox5);
            this->Controls->Add(this->textBox6);
            this->Controls->Add(this->button3);
            this->Controls->Add(this->textBox4);
            this->Controls->Add(this->textBox2);
            this->Controls->Add(this->textBox3);
            this->Controls->Add(this->textBox1);
            this->Controls->Add(this->label12);
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
            this->Name = L"MyForm7";
            this->Text = L"MyForm7";
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion

    private:
        void SetupEventHandlers() {
            button1->Click += gcnew System::EventHandler(this, &MyForm7::button1_Click);
            button3->Click += gcnew System::EventHandler(this, &MyForm7::button3_Click);
            button2->Click += gcnew System::EventHandler(this, &MyForm7::button2_Click);

            textBox1->Click += gcnew System::EventHandler(this, &MyForm7::textBox1_Click);
            textBox2->Click += gcnew System::EventHandler(this, &MyForm7::textBox2_Click);
            textBox3->Click += gcnew System::EventHandler(this, &MyForm7::textBox3_Click);
            textBox4->Click += gcnew System::EventHandler(this, &MyForm7::textBox4_Click);
            textBox5->Click += gcnew System::EventHandler(this, &MyForm7::textBox5_Click);
            textBox6->Click += gcnew System::EventHandler(this, &MyForm7::textBox6_Click);
            textBox7->Click += gcnew System::EventHandler(this, &MyForm7::textBox7_Click);
        }

        std::string ToStdString(System::String^ str) {
            return marshal_as<std::string>(str);
        }

        System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
            int choice = (int)numericUpDown1->Value;

            switch (choice) {
            case 1: {
                MessageBox::Show("Використовуйте кнопку \"Ввести\" поруч з полями введення для створення конфігурації мережі", "Повідомлення");
                break;
            }
            case 2: {
                MessageBox::Show("Використовуйте кнопку \"Ввести\" поруч з полями для додавання з'єднання", "Повідомлення");
                break;
            }
            case 3: {
                if (network == nullptr || sourceDevice == -1 || sinkDevice == -1) {
                    MessageBox::Show("Спочатку введіть конфігурацію мережі!", "Помилка");
                    break;
                }

                int max_flow = network->maxFlow(sourceDevice, sinkDevice);
                MessageBox::Show("Максимальна швидкість передачі даних: " + max_flow.ToString() +
                    " Мбіт/с\nЦе максимальна кількість даних, яку можна передати від пристрою " +
                    sourceDevice.ToString() + " до пристрою " + sinkDevice.ToString() +
                    " за одиницю часу.", "Результат");
                break;
            }
            case 4: {
                if (network == nullptr || sourceDevice == -1) {
                    MessageBox::Show("Спочатку введіть конфігурацію мережі та обчисліть максимальний потік!", "Помилка");
                    break;
                }

                network->maxFlow(sourceDevice, sinkDevice);
                auto min_cut_devices = network->getMinCutDevices(sourceDevice);
                auto min_cut_edges = network->getMinCutEdges(sourceDevice);

                System::String^ result = "=== МІНІМАЛЬНИЙ РОЗРІЗ МЕРЕЖІ ===\n";
                result += "Пристрої на стороні відправника: ";

                for (int v : min_cut_devices) {
                    result += "Пристрій " + v.ToString() + " ";
                }

                result += "\nРебра розрізу:\n";

                if (min_cut_edges.empty()) {
                    result += "Розріз не знайдено (всі пристрої досяжні).\n";
                }
                else {
                    for (auto& edge : min_cut_edges) {
                        result += "  Пристрій " + edge.first.first.ToString() +
                            " -> Пристрій " + edge.first.second.ToString() +
                            " Пропускна здатність: " + edge.second.ToString() + " Мбіт/с\n";
                    }
                }

                MessageBox::Show(result, "Мінімальний розріз");
                break;
            }
            case 5: {
                if (network == nullptr) {
                    MessageBox::Show("Спочатку введіть конфігурацію мережі!", "Помилка");
                    break;
                }

                network->printNetwork(dataGridView1);
                break;
            }
            case 6: {
                this->Close();
                break;
            }
            default: {
                MessageBox::Show("Невірний вибір! Оберіть цифру від 1 до 6", "Помилка");
                break;
            }
            }
        }

        System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
            int numDevices, numConnections, source, sink;

            try {
                numDevices = System::Convert::ToInt32(textBox1->Text);
                numConnections = System::Convert::ToInt32(textBox2->Text);
                source = System::Convert::ToInt32(textBox3->Text);
                sink = System::Convert::ToInt32(textBox4->Text);
            }
            catch (...) {
                MessageBox::Show("Будь ласка, введіть коректні числові значення", "Помилка введення");
                return;
            }

            if (numDevices <= 1) {
                MessageBox::Show("Мережа повинна містити принаймні 2 пристрої!", "Помилка");
                return;
            }

            if (source < 0 || source >= numDevices || sink < 0 || sink >= numDevices || source == sink) {
                MessageBox::Show("Помилка: пристрої вказано некоректно!", "Помилка");
                return;
            }

            if (network != nullptr) {
                delete network;
            }

            network = new NetworkFlow(numDevices);
            sourceDevice = source;
            sinkDevice = sink;

            MessageBox::Show("Конфігурація мережі успішно створена!\n\nПристрої пронумеровані від 0 до " +
                (numDevices - 1).ToString() + "\nДжерело: пристрій " + source.ToString() +
                "\nСток: пристрій " + sink.ToString() + "\n\nТепер ви можете додавати з'єднання.",
                "Успіх");
        }

        System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
            if (network == nullptr) {
                MessageBox::Show("Спочатку створіть конфігурацію мережі!", "Помилка");
                return;
            }

            int fromDevice, toDevice, maxSpeed;

            try {
                fromDevice = System::Convert::ToInt32(textBox6->Text);
                toDevice = System::Convert::ToInt32(textBox5->Text);
                maxSpeed = System::Convert::ToInt32(textBox7->Text);
            }
            catch (...) {
                MessageBox::Show("Будь ласка, введіть коректні числові значення", "Помилка введення");
                return;
            }

            int numDevices = network->getNumDevices();
            if (fromDevice < 0 || fromDevice >= numDevices || toDevice < 0 || toDevice >= numDevices) {
                MessageBox::Show("Номери пристроїв мають бути в діапазоні від 0 до " + (numDevices - 1).ToString(), "Помилка");
                return;
            }

            if (maxSpeed < 0) {
                MessageBox::Show("Максимальна швидкість не може бути від'ємною!", "Помилка");
                return;
            }

            network->addConnection(fromDevice, toDevice, maxSpeed);

            MessageBox::Show("З'єднання між пристроєм " + fromDevice.ToString() +
                " та пристроєм " + toDevice.ToString() +
                " з максимальною швидкістю " + maxSpeed.ToString() +
                " Мбіт/с успішно додано!", "Успіх");
        }

        System::Void textBox1_Click(System::Object^ sender, System::EventArgs^ e) {
            if (textBox1->Text == "Кількість пристроїв у мережі") {
                textBox1->Text = "";
            }
        }

        System::Void textBox2_Click(System::Object^ sender, System::EventArgs^ e) {
            if (textBox2->Text == "Скільки з'єднань додати") {
                textBox2->Text = "";
            }
        }

        System::Void textBox3_Click(System::Object^ sender, System::EventArgs^ e) {
            if (textBox3->Text == "Номер пристроя-відправника") {
                textBox3->Text = "";
            }
        }

        System::Void textBox4_Click(System::Object^ sender, System::EventArgs^ e) {
            if (textBox4->Text == "Номер пристроя-одержувача") {
                textBox4->Text = "";
            }
        }

        System::Void textBox5_Click(System::Object^ sender, System::EventArgs^ e) {
            if (textBox5->Text == "Пристрій 2") {
                textBox5->Text = "";
            }
        }

        System::Void textBox6_Click(System::Object^ sender, System::EventArgs^ e) {
            if (textBox6->Text == "Пристрій 1") {
                textBox6->Text = "";
            }
        }

        System::Void textBox7_Click(System::Object^ sender, System::EventArgs^ e) {
            if (textBox7->Text == "Максимальна швидкість даних") {
                textBox7->Text = "";
            }
        }
    };
}
