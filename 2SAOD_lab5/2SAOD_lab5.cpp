#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Структура для представления ребра графа
struct Edge {
    int src, dest, weight;
};

// Структура для представления графа
class Graph {
public:
    int V, E; // Количество вершин и ребер
    vector<Edge> edges; // Вектор ребер

    // Конструктор
    Graph(int V, int E) {
        this->V = V;
        this->E = E;
    }

    // Добавление ребра в граф
    void addEdge(int src, int dest, int weight) {
        edges.push_back({ src, dest, weight });
    }

    // Алгоритм Прима для поиска минимального остовного дерева
    void primMST() {
        vector<int> parent(V, -1); // Массив для хранения родительских вершин
        vector<int> key(V, INT_MAX); // Массив для хранения весов ключей
        vector<bool> inMST(V, false); // Массив для хранения информации о включении вершины в остовное дерево

        // Используем минимальную кучу (priority_queue) для эффективного выбора вершины с минимальным весом
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        // Начинаем с вершины 0
        key[0] = 0;
        pq.push({ 0, 0 });

        // Проходим по всем вершинам
        while (!pq.empty()) {
            int u = pq.top().second; // Выбираем вершину с минимальным ключом
            pq.pop();

            inMST[u] = true; // Включаем вершину в остовное дерево

            // Обновляем ключи и добавляем вершины, смежные с u, в очередь
            for (auto& edge : edges) {
                int v = edge.dest;
                int weight = edge.weight;
                if (!inMST[v] && weight < key[v]) {
                    key[v] = weight;
                    parent[v] = u;
                    pq.push({ key[v], v });
                }
            }
        }

        // Выводим остовное дерево
        cout << "Остовное дерево, найденное алгоритмом Прима:\n";
        for (int i = 1; i < V; ++i)
            cout << parent[i] << " - " << i << endl;
    }

    // Алгоритм Краскала для поиска минимального остовного дерева
    void kruskalMST() {
        vector<pair<int, pair<int, int>>> sortedEdges; // Вектор ребер, отсортированный по весу
        vector<int> parent(V); // Массив для хранения родительских вершин
        for (int i = 0; i < V; ++i)
            parent[i] = i;

        // Сортируем ребра по весу
        sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
            return a.weight < b.weight;
            });

        // Проходим по всем ребрам и добавляем их в остовное дерево, если они не образуют цикл
        cout << "Остовное дерево, найденное алгоритмом Краскала:\n";
        for (const auto& edge : edges) {
            int u = edge.src;
            int v = edge.dest;
            int setU = find(parent, u);
            int setV = find(parent, v);
            if (setU != setV) {
                cout << u << " - " << v << endl;
                parent[setU] = setV;
            }
        }
    }

    // Функция для нахождения корня дерева
    int find(vector<int>& parent, int i) {
        if (parent[i] == i)
            return i;
        return find(parent, parent[i]);
    }
};

int main() {
    system("chcp 1251");
    int V, E; // Количество вершин и ребер
    cout << "Введите количество вершин и ребер графа: ";
    cin >> V >> E;

    Graph graph(V, E); // Создаем граф

    // Вводим ребра графа
    cout << "Введите ребра графа (src dest weight):\n";
    for (int i = 0; i < E; ++i) {
        int src, dest, weight;
        cin >> src >> dest >> weight;
        graph.addEdge(src, dest, weight);
    }

    // Вызываем алгоритм Прима
    graph.primMST();

    // Вызываем алгоритм Краскала
    graph.kruskalMST();

    return 0;
}
