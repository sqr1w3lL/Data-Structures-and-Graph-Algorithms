#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include <climits>
#include <algorithm>
#include <tuple>
#include <sstream>
#include <msclr/marshal_cppstd.h>

struct Edge {
	int to;
	int weight;
	Edge(int t, int w) : to(t), weight(w) {}
};

class CityGraph {
private:
	std::vector<std::vector<Edge>> adjList;
	std::unordered_map<std::string, int> cityToIndex;
	std::vector<std::string> indexToCity;

public:
	void addCity(const std::string& name) {
		if (cityToIndex.count(name) == 0) {
			int idx = (int)cityToIndex.size();
			cityToIndex[name] = idx;
			indexToCity.push_back(name);
			adjList.resize(idx + 1);
		}
	}

	void addRoad(const std::string& from, const std::string& to, int dist) {
		addCity(from);
		addCity(to);
		int u = cityToIndex[from];
		int v = cityToIndex[to];
		adjList[u].push_back(Edge(v, dist));
		adjList[v].push_back(Edge(u, dist));
	}

	int getCityIndex(const std::string& name) const {
		auto it = cityToIndex.find(name);
		if (it != cityToIndex.end()) return it->second;
		return -1;
	}

	std::string getCityName(int idx) const {
		if (idx >= 0 && idx < (int)indexToCity.size()) return indexToCity[idx];
		return "Unknown";
	}

	int cityCount() const { return (int)indexToCity.size(); }

	const std::vector<Edge>& getAdjList(int idx) const {
		if (idx >= 0 && idx < (int)adjList.size())
			return adjList[idx];
		static std::vector<Edge> empty;
		return empty;
	}

	std::vector<int> dijkstra(int start, int end, int& totalDist) {
		int n = (int)adjList.size();
		std::vector<int> dist(n, INT_MAX);
		std::vector<int> prev(n, -1);
		std::vector<bool> visited(n, false);

		dist[start] = 0;

		for (int i = 0; i < n; ++i) {
			int u = -1;
			for (int j = 0; j < n; ++j) {
				if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
					u = j;
				}
			}

			if (u == -1 || dist[u] == INT_MAX) break;
			visited[u] = true;

			for (const Edge& e : adjList[u]) {
				if (dist[u] + e.weight < dist[e.to]) {
					dist[e.to] = dist[u] + e.weight;
					prev[e.to] = u;
				}
			}
		}

		std::vector<int> path;
		for (int at = end; at != -1; at = prev[at]) {
			path.push_back(at);
		}
		std::reverse(path.begin(), path.end());

		totalDist = dist[end];
		if (dist[end] == INT_MAX) {
			return std::vector<int>();
		}
		return path;
	}

	std::vector<std::vector<int>> floydWarshall() {
		int n = (int)adjList.size();
		std::vector<std::vector<int>> dist(n, std::vector<int>(n, INT_MAX));

		for (int i = 0; i < n; ++i) {
			dist[i][i] = 0;
		}

		for (int i = 0; i < n; ++i) {
			for (const Edge& e : adjList[i]) {
				if (e.weight < dist[i][e.to]) {
					dist[i][e.to] = e.weight;
				}
			}
		}

		for (int k = 0; k < n; ++k) {
			for (int i = 0; i < n; ++i) {
				if (dist[i][k] == INT_MAX) continue;
				for (int j = 0; j < n; ++j) {
					if (dist[k][j] != INT_MAX && dist[i][k] + dist[k][j] < dist[i][j]) {
						dist[i][j] = dist[i][k] + dist[k][j];
					}
				}
			}
		}

		return dist;
	}
};

class InequalitySystem {
private:
	int numVars;
	std::vector<std::tuple<int, int, int>> edges;

public:
	InequalitySystem(int T) : numVars(T) {}

	void addInequality(int j, int i, int w) {
		edges.push_back(std::make_tuple(j, i, w));
	}

	bool solve(std::vector<int>& dist) {
		int V = numVars + 1;
		std::vector<std::tuple<int, int, int>> allEdges = edges;

		for (int i = 0; i < numVars; ++i) {
			allEdges.push_back(std::make_tuple(numVars, i, 0));
		}

		dist.assign(V, INT_MAX);
		dist[numVars] = 0;

		for (int iter = 0; iter < V - 1; ++iter) {
			bool updated = false;
			for (size_t idx = 0; idx < allEdges.size(); ++idx) {
				int u = std::get<0>(allEdges[idx]);
				int v = std::get<1>(allEdges[idx]);
				int w = std::get<2>(allEdges[idx]);

				if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
					dist[v] = dist[u] + w;
					updated = true;
				}
			}
			if (!updated) break;
		}

		for (size_t idx = 0; idx < allEdges.size(); ++idx) {
			int u = std::get<0>(allEdges[idx]);
			int v = std::get<1>(allEdges[idx]);
			int w = std::get<2>(allEdges[idx]);

			if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
				return false;
			}
		}

		dist.pop_back();
		return true;
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

	public ref class MyForm6 : public System::Windows::Forms::Form
	{
	private:
		CityGraph* cityGraph;

	public:
		MyForm6(void)
		{
			InitializeComponent();
			cityGraph = new CityGraph();
			InitializeDefaultData();
			SetupEventHandlers();
		}

	protected:
		~MyForm6()
		{
			if (components)
			{
				delete components;
			}
			if (cityGraph) {
				delete cityGraph;
				cityGraph = nullptr;
			}
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
	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::DataGridView^ dataGridView1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::TextBox^ textBox6;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::TextBox^ textBox5;
	private: System::Windows::Forms::TextBox^ textBox8;
	private: System::Windows::Forms::Button^ button5;
	private: System::Windows::Forms::TextBox^ textBox7;
	private: System::Windows::Forms::TextBox^ textBox9;
	private: System::Windows::Forms::TextBox^ textBox4;

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
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->textBox8 = (gcnew System::Windows::Forms::TextBox());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			this->textBox9 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();

			this->label11->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label11->Location = System::Drawing::Point(76, 430);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(370, 20);
			this->label11->TabIndex = 38;
			this->label11->Text = L"0. Вихід";

			this->label8->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label8->Location = System::Drawing::Point(76, 364);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(503, 30);
			this->label8->TabIndex = 41;
			this->label8->Text = L"7. Розв’язати систему нерівностей (Беллман-Форд)";

			this->label7->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label7->Location = System::Drawing::Point(76, 326);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(549, 20);
			this->label7->TabIndex = 42;
			this->label7->Text = L"6. Найкоротші шляхи між усіма парами міст (Флойд-Воршелл)";

			this->label6->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label6->Location = System::Drawing::Point(76, 295);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(434, 20);
			this->label6->TabIndex = 43;
			this->label6->Text = L"5. Найкоротший шлях між двома містами (Дейкстра)";

			this->label5->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label5->Location = System::Drawing::Point(76, 263);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(370, 20);
			this->label5->TabIndex = 44;
			this->label5->Text = L"4. Вивести дороги між містами (Граф)";

			this->label4->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label4->Location = System::Drawing::Point(76, 231);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(370, 20);
			this->label4->TabIndex = 45;
			this->label4->Text = L"3. Вивести список міст";

			this->label3->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(76, 197);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(275, 20);
			this->label3->TabIndex = 46;
			this->label3->Text = L"2. Додати дорогу між містами";

			this->button1->Location = System::Drawing::Point(172, 116);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(91, 23);
			this->button1->TabIndex = 37;
			this->button1->Text = L"Підтвердити";
			this->button1->Click += gcnew System::EventHandler(this, &MyForm6::button1_Click);

			this->numericUpDown1->Location = System::Drawing::Point(91, 119);
			this->numericUpDown1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 7, 0, 0, 0 });
			this->numericUpDown1->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 0, 0, 0, 0 });
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Size = System::Drawing::Size(38, 20);
			this->numericUpDown1->TabIndex = 36;
			this->numericUpDown1->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 0, 0, 0, 0 });

			this->label2->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(76, 168);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(157, 21);
			this->label2->TabIndex = 47;
			this->label2->Text = L"1. Додати місто";

			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 24, System::Drawing::FontStyle::Bold));
			this->label1->Location = System::Drawing::Point(74, 60);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(256, 36);
			this->label1->TabIndex = 35;
			this->label1->Text = L"Виберіть опцію: ";

			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"Times New Roman", 24, System::Drawing::FontStyle::Bold));
			this->label12->Location = System::Drawing::Point(1390, 21);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(261, 36);
			this->label12->TabIndex = 49;
			this->label12->Text = L"Виведення даних";

			this->dataGridView1->Location = System::Drawing::Point(1157, 60);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->Size = System::Drawing::Size(935, 500);
			this->dataGridView1->TabIndex = 48;

			this->button2->Location = System::Drawing::Point(357, 166);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 51;
			this->button2->Text = L"Ввести";
			this->button2->Click += gcnew System::EventHandler(this, &MyForm6::button2_Click);

			this->textBox1->Location = System::Drawing::Point(251, 166);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 20);
			this->textBox1->TabIndex = 50;
			this->textBox1->Text = L"Введіть нове місто";
			this->textBox1->Click += gcnew System::EventHandler(this, &MyForm6::textBox1_Click);

			this->button3->Location = System::Drawing::Point(755, 193);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 23);
			this->button3->TabIndex = 53;
			this->button3->Text = L"Ввести";
			this->button3->Click += gcnew System::EventHandler(this, &MyForm6::button3_Click);

			this->textBox2->Location = System::Drawing::Point(385, 197);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(100, 20);
			this->textBox2->TabIndex = 52;
			this->textBox2->Text = L"Перше місто";
			this->textBox2->Click += gcnew System::EventHandler(this, &MyForm6::textBox2_Click);

			this->textBox3->Location = System::Drawing::Point(507, 196);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(100, 20);
			this->textBox3->TabIndex = 54;
			this->textBox3->Text = L"Друге місто";
			this->textBox3->Click += gcnew System::EventHandler(this, &MyForm6::textBox3_Click);

			this->textBox6->Location = System::Drawing::Point(638, 294);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(100, 20);
			this->textBox6->TabIndex = 57;
			this->textBox6->Text = L"Кінець шляху";
			this->textBox6->Click += gcnew System::EventHandler(this, &MyForm6::textBox6_Click);

			this->button4->Location = System::Drawing::Point(755, 292);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(75, 23);
			this->button4->TabIndex = 56;
			this->button4->Text = L"Ввести";
			this->button4->Click += gcnew System::EventHandler(this, &MyForm6::button4_Click);

			this->textBox5->Location = System::Drawing::Point(516, 295);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(100, 20);
			this->textBox5->TabIndex = 55;
			this->textBox5->Text = L"Початок шляху";
			this->textBox5->Click += gcnew System::EventHandler(this, &MyForm6::textBox5_Click);

			this->textBox8->Location = System::Drawing::Point(638, 354);
			this->textBox8->Name = L"textBox8";
			this->textBox8->Size = System::Drawing::Size(120, 20);
			this->textBox8->TabIndex = 60;
			this->textBox8->Text = L"Кількість нерівностей";
			this->textBox8->Click += gcnew System::EventHandler(this, &MyForm6::textBox8_Click);

			this->button5->Location = System::Drawing::Point(898, 364);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(75, 23);
			this->button5->TabIndex = 59;
			this->button5->Text = L"Ввести";
			this->button5->Click += gcnew System::EventHandler(this, &MyForm6::button5_Click);

			this->textBox7->Location = System::Drawing::Point(525, 354);
			this->textBox7->Name = L"textBox7";
			this->textBox7->Size = System::Drawing::Size(100, 20);
			this->textBox7->TabIndex = 58;
			this->textBox7->Text = L"Кількість змінних";
			this->textBox7->Click += gcnew System::EventHandler(this, &MyForm6::textBox7_Click);

			this->textBox9->Location = System::Drawing::Point(507, 393);
			this->textBox9->Name = L"textBox9";
			this->textBox9->Size = System::Drawing::Size(380, 20);
			this->textBox9->TabIndex = 61;
			this->textBox9->Text = L"Введіть кожну нерівність у форматі (i j w), де x_i - x_j <= w (через пробіл)";
			this->textBox9->Click += gcnew System::EventHandler(this, &MyForm6::textBox9_Click);

			this->textBox4->Location = System::Drawing::Point(638, 196);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(100, 20);
			this->textBox4->TabIndex = 62;
			this->textBox4->Text = L"Відстань між ними";
			this->textBox4->Click += gcnew System::EventHandler(this, &MyForm6::textBox4_Click);

			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1918, 745);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->textBox9);
			this->Controls->Add(this->textBox8);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->textBox7);
			this->Controls->Add(this->textBox6);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->textBox5);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label12);
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
			this->Name = L"MyForm6";
			this->Text = L"MyForm6";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private:
		std::string ToStdString(System::String^ str) {
			return msclr::interop::marshal_as<std::string>(str);
		}

		System::String^ ToSystemString(const std::string& str) {
			return msclr::interop::marshal_as<System::String^>(str);
		}

		void InitializeDefaultData() {
			std::vector<std::string> cities = {
				"Київ", "Харків", "Одеса", "Львів", "Дніпро",
				"Чернігів", "Полтава", "Ужгород", "Суми", "Миколаїв", "Тернопіль"
			};

			for (const std::string& city : cities) {
				cityGraph->addCity(city);
			}

			cityGraph->addRoad("Київ", "Харків", 480);
			cityGraph->addRoad("Київ", "Дніпро", 450);
			cityGraph->addRoad("Київ", "Львів", 550);
			cityGraph->addRoad("Київ", "Чернігів", 160);
			cityGraph->addRoad("Київ", "Полтава", 350);
			cityGraph->addRoad("Київ", "Миколаїв", 500);
			cityGraph->addRoad("Харків", "Суми", 300);
			cityGraph->addRoad("Харків", "Полтава", 140);
			cityGraph->addRoad("Харків", "Дніпро", 200);
			cityGraph->addRoad("Одеса", "Миколаїв", 130);
			cityGraph->addRoad("Одеса", "Львів", 750);
			cityGraph->addRoad("Одеса", "Ужгород", 1000);
			cityGraph->addRoad("Львів", "Ужгород", 260);
			cityGraph->addRoad("Львів", "Тернопіль", 140);
			cityGraph->addRoad("Чернігів", "Суми", 320);
			cityGraph->addRoad("Миколаїв", "Дніпро", 380);
			cityGraph->addRoad("Полтава", "Суми", 250);
			cityGraph->addRoad("Полтава", "Дніпро", 160);
			cityGraph->addRoad("Дніпро", "Миколаїв", 380);
			cityGraph->addRoad("Ужгород", "Львів", 260);
		}

		void SetupEventHandlers() {
		}

		void DisplayList(const std::vector<std::string>& items, const std::string& header) {
			dataGridView1->Rows->Clear();
			dataGridView1->Columns->Clear();

			DataGridViewTextBoxColumn^ col = gcnew DataGridViewTextBoxColumn();
			col->HeaderText = ToSystemString(header);
			dataGridView1->Columns->Add(col);

			for (const auto& item : items) {
				int rowIndex = dataGridView1->Rows->Add();
				dataGridView1->Rows[rowIndex]->Cells[0]->Value = ToSystemString(item);
			}
		}

		void DisplayGraph() {
			dataGridView1->Rows->Clear();
			dataGridView1->Columns->Clear();

			DataGridViewTextBoxColumn^ cityCol = gcnew DataGridViewTextBoxColumn();
			cityCol->HeaderText = "Місто";
			dataGridView1->Columns->Add(cityCol);

			DataGridViewTextBoxColumn^ neighborsCol = gcnew DataGridViewTextBoxColumn();
			neighborsCol->HeaderText = "Сусіди (місто, відстань)";
			dataGridView1->Columns->Add(neighborsCol);

			int cityCount = cityGraph->cityCount();
			for (int i = 0; i < cityCount; ++i) {
				std::string cityName = cityGraph->getCityName(i);
				std::string neighbors = "";

				const auto& edges = cityGraph->getAdjList(i);
				for (size_t j = 0; j < edges.size(); ++j) {
					const Edge& e = edges[j];
					std::string neighborName = cityGraph->getCityName(e.to);
					neighbors += "(" + neighborName + ", " + std::to_string(e.weight) + ")";
					if (j < edges.size() - 1) neighbors += ", ";
				}

				int rowIndex = dataGridView1->Rows->Add();
				dataGridView1->Rows[rowIndex]->Cells[0]->Value = ToSystemString(cityName);
				dataGridView1->Rows[rowIndex]->Cells[1]->Value = ToSystemString(neighbors);
			}
		}

		void DisplayFloydWarshall() {
			std::vector<std::vector<int>> dist = cityGraph->floydWarshall();
			int n = dist.size();

			dataGridView1->Rows->Clear();
			dataGridView1->Columns->Clear();

			DataGridViewTextBoxColumn^ headerCol = gcnew DataGridViewTextBoxColumn();
			headerCol->HeaderText = "З \\ В";
			dataGridView1->Columns->Add(headerCol);

			for (int j = 0; j < n; ++j) {
				DataGridViewTextBoxColumn^ col = gcnew DataGridViewTextBoxColumn();
				col->HeaderText = ToSystemString(cityGraph->getCityName(j));
				dataGridView1->Columns->Add(col);
			}

			for (int i = 0; i < n; ++i) {
				int rowIndex = dataGridView1->Rows->Add();
				dataGridView1->Rows[rowIndex]->Cells[0]->Value = ToSystemString(cityGraph->getCityName(i));

				for (int j = 0; j < n; ++j) {
					System::String^ value;
					if (dist[i][j] == INT_MAX) {
						value = "Немає";
					}
					else {
						value = dist[i][j].ToString();
					}
					dataGridView1->Rows[rowIndex]->Cells[j + 1]->Value = value;
				}
			}
		}

		System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
			int choice = (int)numericUpDown1->Value;

			switch (choice) {
			case 0:
				this->Close();
				break;
			case 3:
			{
				std::vector<std::string> cities;
				int count = cityGraph->cityCount();
				for (int i = 0; i < count; ++i) {
					cities.push_back(std::to_string(i + 1) + ". " + cityGraph->getCityName(i));
				}
				DisplayList(cities, "Список міст");
			}
			break;
			case 4:
				DisplayGraph();
				break;
			case 6:
				DisplayFloydWarshall();
				break;
			default:
				MessageBox::Show("Ця опція доступна через окремі кнопки", "Повідомлення");
				break;
			}
		}

		System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
			std::string cityName = ToStdString(textBox1->Text);
			if (cityName.empty() || cityName == "Введіть нове місто") {
				MessageBox::Show("Будь ласка, введіть назву міста", "Помилка");
				return;
			}

			if (cityGraph->getCityIndex(cityName) != -1) {
				MessageBox::Show("Місто вже існує", "Помилка");
			}
			else {
				cityGraph->addCity(cityName);
				MessageBox::Show("Місто додано", "Успіх");
			}
		}

		System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
			std::string from = ToStdString(textBox2->Text);
			std::string to = ToStdString(textBox3->Text);
			std::string distStr = ToStdString(textBox4->Text);

			if (from.empty() || from == "Перше місто" ||
				to.empty() || to == "Друге місто" ||
				distStr.empty() || distStr == "Відстань між ними") {
				MessageBox::Show("Будь ласка, заповніть усі поля", "Помилка");
				return;
			}

			int dist;
			try {
				dist = std::stoi(distStr);
			}
			catch (...) {
				MessageBox::Show("Відстань має бути числом", "Помилка");
				return;
			}

			if (dist < 0) {
				MessageBox::Show("Відстань не може бути від'ємною", "Помилка");
				return;
			}

			if (cityGraph->getCityIndex(from) == -1) {
				MessageBox::Show("Перше місто не знайдено. Спочатку додайте його.", "Помилка");
				return;
			}

			if (cityGraph->getCityIndex(to) == -1) {
				MessageBox::Show("Друге місто не знайдено. Спочатку додайте його.", "Помилка");
				return;
			}

			cityGraph->addRoad(from, to, dist);
			MessageBox::Show("Дорога додана", "Успіх");
		}

		System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
			std::string start = ToStdString(textBox5->Text);
			std::string end = ToStdString(textBox6->Text);

			if (start.empty() || start == "Початок шляху" ||
				end.empty() || end == "Кінець шляху") {
				MessageBox::Show("Будь ласка, введіть обидва міста", "Помилка");
				return;
			}

			int s = cityGraph->getCityIndex(start);
			int endIdx = cityGraph->getCityIndex(end);

			if (s == -1) {
				MessageBox::Show("Початкове місто не знайдено", "Помилка");
				return;
			}

			if (endIdx == -1) {
				MessageBox::Show("Кінцеве місто не знайдено", "Помилка");
				return;
			}

			int totalDist;
			std::vector<int> path = cityGraph->dijkstra(s, endIdx, totalDist);

			if (path.empty()) {
				MessageBox::Show("Шляху не існує", "Результат");
			}
			else {
				std::string pathStr = "Найкоротший шлях: ";
				for (size_t i = 0; i < path.size(); ++i) {
					pathStr += cityGraph->getCityName(path[i]);
					if (i + 1 < path.size()) pathStr += " -> ";
				}
				pathStr += "\nВідстань: " + std::to_string(totalDist) + " км";
				MessageBox::Show(ToSystemString(pathStr), "Результат");
			}
		}

		System::Void button5_Click(System::Object^ sender, System::EventArgs^ e) {
			std::string tStr = ToStdString(textBox7->Text);
			std::string kStr = ToStdString(textBox8->Text);
			std::string inequalities = ToStdString(textBox9->Text);

			if (tStr.empty() || tStr == "Кількість змінних" ||
				kStr.empty() || kStr == "Кількість нерівностей") {
				MessageBox::Show("Будь ласка, введіть кількість змінних та нерівностей", "Помилка");
				return;
			}

			int T, K;
			try {
				T = std::stoi(tStr);
				K = std::stoi(kStr);
			}
			catch (...) {
				MessageBox::Show("Кількість змінних та нерівностей мають бути числами", "Помилка");
				return;
			}

			if (T <= 0 || K <= 0) {
				MessageBox::Show("Кількість змінних та нерівностей має бути додатною", "Помилка");
				return;
			}

			InequalitySystem sys(T);
			std::istringstream iss(inequalities);
			int count = 0;
			int i_idx, j_idx, w;

			while (count < K && iss >> i_idx >> j_idx >> w) {
				sys.addInequality(j_idx - 1, i_idx - 1, w);
				count++;
			}

			if (count < K) {
				MessageBox::Show("Недостатньо нерівностей. Потрібно " + K.ToString() + " нерівностей.", "Помилка");
				return;
			}

			std::vector<int> dist;
			if (!sys.solve(dist)) {
				MessageBox::Show("Розв'язку не існує (виявлено негативний цикл)", "Результат");
			}
			else {
				std::string result = "Розв'язок знайдено:\n";
				for (int i = 0; i < T; ++i) {
					result += "x_" + std::to_string(i + 1) + " = " + std::to_string(dist[i]) + "\n";
				}
				MessageBox::Show(ToSystemString(result), "Результат");
			}
		}

		System::Void textBox1_Click(System::Object^ sender, System::EventArgs^ e) {
			if (textBox1->Text == "Введіть нове місто") {
				textBox1->Text = "";
			}
		}

		System::Void textBox2_Click(System::Object^ sender, System::EventArgs^ e) {
			if (textBox2->Text == "Перше місто") {
				textBox2->Text = "";
			}
		}

		System::Void textBox3_Click(System::Object^ sender, System::EventArgs^ e) {
			if (textBox3->Text == "Друге місто") {
				textBox3->Text = "";
			}
		}

		System::Void textBox4_Click(System::Object^ sender, System::EventArgs^ e) {
			if (textBox4->Text == "Відстань між ними") {
				textBox4->Text = "";
			}
		}

		System::Void textBox5_Click(System::Object^ sender, System::EventArgs^ e) {
			if (textBox5->Text == "Початок шляху") {
				textBox5->Text = "";
			}
		}

		System::Void textBox6_Click(System::Object^ sender, System::EventArgs^ e) {
			if (textBox6->Text == "Кінець шляху") {
				textBox6->Text = "";
			}
		}

		System::Void textBox7_Click(System::Object^ sender, System::EventArgs^ e) {
			if (textBox7->Text == "Кількість змінних") {
				textBox7->Text = "";
			}
		}

		System::Void textBox8_Click(System::Object^ sender, System::EventArgs^ e) {
			if (textBox8->Text == "Кількість нерівностей") {
				textBox8->Text = "";
			}
		}

		System::Void textBox9_Click(System::Object^ sender, System::EventArgs^ e) {
			if (textBox9->Text == "Введіть кожну нерівність у форматі (i j w), де x_i - x_j <= w (через пробіл)") {
				textBox9->Text = "";
			}
		}
	};
}
