#include <fstream>
#include <iostream>
#include <limits>
#include <string>

using namespace std;

    template<class T1, class T2>
    struct duo {
        T1 data1;
        T2 data2;

        duo(T1 data1, T2 data2) : data1(data1), data2(data2) {};

        friend ostream& operator<<(ostream& out, duo& pair) {
            out << "[" << pair.data1 << " ; " << pair.data2 << "]";
            return out;
        }

        friend istream& operator>>(istream& in, duo& pair) {
            in >> pair.data1;
            in >> pair.data2;
            return in;
        }

        friend bool operator==(duo& p1, duo& p2) {
            return p1.data1 == p2.data1 && p1.data2 == p2.data2;
        }
    };

    template<class T>
    class Stack {
    private:
        struct item {
            T data;
            item* below_item;

            item(T data) : data(data), below_item(nullptr) {};
        };

        friend ostream& operator<<(ostream& out, Stack& s) {
            if (!s.empty()) {
                item* cur_item = s.m_top_element;
                while (cur_item->below_item != nullptr) {
                    out << cur_item->data << "->";
                    cur_item = cur_item->below_item;
                }
                out << cur_item->data;
            }
            else
                out << "stack is empty!";
            return out;
        }

        unsigned long int m_length;
        item* m_top_element;
    public:

        Stack() : m_top_element(nullptr), m_length(0) {};

        void push(T data);

        T* pop();

        T* peek();

        bool empty();

        unsigned long int length();

        void clear();
    };

    template<class T>
    void Stack<T>::push(T data) {
        item* new_item = new item(data);
        if (m_top_element) {
            new_item->below_item = m_top_element;
            m_top_element = new_item;
        }
        else {
            m_top_element = new_item;
        }
        m_length++;
    }

    template<class T>
    T* Stack<T>::pop() {
        if (m_top_element) {
            item* save_item = m_top_element;
            m_top_element = m_top_element->below_item;
            m_length--;
            return &save_item->data;
        }
        else
            return nullptr;
    }

    template<class T>
    T* Stack<T>::peek() {
        if (m_top_element)
            return &m_top_element->data;
        else
            return nullptr;
    }

    template<class T>
    bool Stack<T>::empty() {
        return !(m_length);
    }

    template<class T>
    unsigned long int Stack<T>::length() {
        return m_length;
    }

    template<class T>
    void Stack<T>::clear() {
        item* cur_item = m_top_element;
        item* save_item;
        while (cur_item) {
            save_item = cur_item->below_item;
            delete cur_item;
            cur_item = save_item->below_item;
        }
        m_top_element = nullptr;
        m_length = 0;
    }


    template<class T>
    class Queue {
    private:
        struct item {
            T data;
            item* prev_item;

            item(T data) : data(data), prev_item(nullptr) {};
        };

        item* m_first_item;
        item* m_last_item;
        unsigned long int m_length;

        friend ostream& operator<<(ostream& out, Queue& q) {
            if (!q.empty()) {
                item* cur_item = q.m_first_item;
                while (cur_item->prev_item) {
                    out << cur_item->data << " -> ";
                    cur_item = cur_item->prev_item;
                }
                out << cur_item->data;
            }
            else
                out << "queue is empty!";
            return out;
        };
    public:
        Queue() : m_first_item(nullptr), m_last_item(m_first_item), m_length(0) {};

        void enqueue(T data);

        T* dequeue();

        T* peek();

        bool empty();

        unsigned long int length();

        void clear();
    };

    template<class T>
    void Queue<T>::enqueue(T data) {
        item* new_item = new item(data);
        if (m_first_item) {
            if (m_first_item == m_last_item) {
                m_last_item = new_item;
                m_first_item->prev_item = m_last_item;
            }
            else {
                m_last_item->prev_item = new_item;
                m_last_item = new_item;
            }
        }
        else
            m_last_item = m_first_item = new_item;
        m_length++;
    }

    template<class T>
    T* Queue<T>::dequeue() {
        if (m_first_item) {
            item* save_item = m_first_item;
            m_first_item = m_first_item->prev_item;
            m_length--;
            return &save_item->data;
        }
        else
            return nullptr;
    }

    template<class T>
    bool Queue<T>::empty() {
        return !(m_first_item);
    }

    template<class T>
    unsigned long int Queue<T>::length() {
        return m_length;
    }

    template<class T>
    void Queue<T>::clear() {
        if (m_first_item) {
            item* cur_item = m_first_item;
            item* save_item;
            while (cur_item) {
                save_item = cur_item->prev_item;
                delete cur_item;
                cur_item = save_item;
            }
        }
        m_first_item = nullptr;
        m_last_item = m_first_item;
        m_length = 0;
    }

    template<class T>
    T* Queue<T>::peek() {
        if (m_first_item) {
            return &m_first_item->data;
        }
        else
            return nullptr;
    }

    template<class T>
    class gleipnir {
    private:
        struct item {
            T data;
            item* prev_item;
            item* next_item;

            item(T data, item* prev_item = nullptr, item* next_item = nullptr) :
                data(data), prev_item(prev_item), next_item(next_item) {};


        };

        item* m_head;
        item* m_tail;
        int m_size;

        void remove_solo();

        gleipnir(item*);

        gleipnir(gleipnir<T>*);

    public:
        void push_back(T data);

        void push_front(T data);


        void insert(T data, int position);

        int get_index(T data);

        void remove_back();

        void remove_front();

        void remove(int position);

        bool find(T& data);

        duo<gleipnir, gleipnir> split(int position);

        int size();

        bool empty();

        gleipnir();

        gleipnir(const gleipnir<T>& list);

        ~gleipnir();

        friend ostream& operator<<(ostream& out, const gleipnir& list) {
            item* cur_item = list.m_head;
            if (cur_item != nullptr) {
                while (cur_item != list.m_tail && cur_item != nullptr) {
                    out << cur_item->data << " ";
                    cur_item = cur_item->next_item;
                }
                if (list.m_tail != nullptr)
                    out << list.m_tail->data;
            }
            else {
                out << "list is empty!";
            }
            return out;
        }

        T& operator[](const int index) {
            item* cur_item = m_head;
            for (int i = 0; i < index; i++)
                cur_item = cur_item->next_item;
            return cur_item->data;
        }

    };

    template<class T>
    gleipnir<T>::gleipnir() : m_head(nullptr), m_tail(m_head), m_size(0) {};

    template<class T>
    gleipnir<T>::gleipnir(const gleipnir<T>& list) : m_head(list.m_head), m_tail(list.m_tail), m_size(list.m_size) {};

    template<class T>
    gleipnir<T>::gleipnir(item* item) :m_size(1) {
        gleipnir<T>::item* cur_item = m_head = item;
        while (cur_item->next_item != nullptr) {
            cur_item = cur_item->next_item;
            m_size++;
        }
        m_tail = cur_item;
    }

    template<class T>
    gleipnir<T>::gleipnir(gleipnir<T>* list) : m_head(list->m_head), m_tail(list->m_tail), m_size(list->m_size) {};

    template<class T>
    gleipnir<T>::~gleipnir() {
        item* save_item = m_head;
        while (save_item != m_tail && save_item != nullptr) {
            save_item = m_head->next_item;
            m_head = save_item;
        }
    }

    template<class T>
    void gleipnir<T>::push_back(T data) {
        item* new_item = new item(data);
        if (m_head == nullptr) {
            m_head = m_tail = new_item;
        }
        else {
            new_item->prev_item = m_tail;
            m_tail->next_item = new_item;
            m_tail = new_item;
        }
        m_size++;
    };

    template<class T>
    void gleipnir<T>::push_front(T data) {
        item* new_item = new item(data);
        if (m_head == nullptr) {
            m_head = m_tail = new_item;
        }
        else {
            new_item->next_item = m_head;
            m_head->prev_item = new_item;
            m_head = new_item;
        }
        m_size++;
    }

    template<class T>
    void gleipnir<T>::insert(T data, int position) {
        if (position <= m_size - 1) {
            if (position == 0) push_front(data);
            else if (position == m_size) push_back(data);
            else {
                item* cur_item = m_head;
                for (int i = 0; i < position; i++) {
                    cur_item = cur_item->next_item;
                }
                item* new_item = new item(data);
                cur_item->prev_item->next_item = new_item;
                new_item->prev_item = cur_item->prev_item;
                new_item->next_item = cur_item;
                cur_item->prev_item = new_item;
            }
            m_size++;
        }
    }

    template<class T>
    int gleipnir<T>::size() { return m_size; }

    template<class T>
    void gleipnir<T>::remove_solo() {
        delete m_head;
        m_head = m_tail = nullptr;
        m_size--;
    }

    template<class T>
    void gleipnir<T>::remove_back() {
        if (m_size > 1) {
            m_tail = m_tail->prev_item;
            delete m_tail->next_item;
            m_size--;
        }
        else if (m_size == 1)
            remove_solo();
    }

    template<class T>
    void gleipnir<T>::remove_front() {
        if (m_size > 1) {
            m_head = m_head->next_item;
            delete m_head->prev_item;
            m_size--;
        }
        else if (m_size == 1) {
            remove_solo();
        }
    }

    template<class T>
    void gleipnir<T>::remove(int position) {
        if (position <= m_size - 1) {
            if (position == 0) remove_front();
            if (position == m_size - 1) remove_back();
            else {
                item* cur_item = m_head;
                for (int i = 0; i < position; i++) {
                    cur_item = cur_item->next_item;
                }
                cur_item->prev_item->next_item = cur_item->next_item;
                cur_item->next_item->prev_item = cur_item->prev_item;
                delete cur_item;
            }
            m_size--;
        }
    }

    template<class T>
    duo<gleipnir<T>, gleipnir<T>> gleipnir<T>::split(int position) {
        if (m_size == 2 && position == 0) {
            gleipnir<T> list1, list2;
            list1.push_back(m_head->data);
            list2.push_back(m_tail->data);
            return duo<gleipnir<T>, gleipnir<T>>(list1, list2);
        }
        else if (-1 < position < m_size - 1) {
            item* cur_item = m_head;
            gleipnir<T> list1, list2;
            for (int i = 0; i <= position; i++) {
                list1.push_back(cur_item->data);
                cur_item = cur_item->next_item;
            }
            while (cur_item != nullptr) {
                list2.push_back(cur_item->data);
                cur_item = cur_item->next_item;
            }
            return duo<gleipnir<T>, gleipnir<T>>(list1, list2);
        }
        else {
            return duo<gleipnir<T>, gleipnir<T>>(gleipnir<T>(), gleipnir<T>());
        }
    }

    template<class T>
    bool gleipnir<T>::empty() {
        return (m_head == m_tail == nullptr);
    }

    template<class T>
    bool gleipnir<T>::find(T& data) {
        item* cur_item = m_head;
        while (cur_item != nullptr) {
            if (cur_item->data == data) return true;
            cur_item = cur_item->next_item;
        }
        return false;
    }

    template<class T>
    int gleipnir<T>::get_index(T data) {
        item* cur_item = m_head;
        unsigned long int index = 0;
        while (cur_item) {
            if (cur_item->data == data)
                return index;
            cur_item = cur_item->next_item;
            index++;
        }
        return -1;
    }

    gleipnir<duo<char, int>> list_count_symbols(string str) {
        gleipnir<duo<char, int>> list;
        while (!str.empty()) {
            char symbol = str[0];
            str.erase(0, 1);
            int count = 1;
            for (int i = 0; i < str.length(); i++) {
                if (str[i] == symbol) {
                    str.erase(i, 1);
                    i = 0;
                    count++;
                }
            }
            list.push_back(duo<char, int>(symbol, count));
        }
        return list;
    }

    int count_sumbols(string str, char symbol) {
        int count = 0;
        for (int i = 0; i < str.length(); i++)
            if (str[i] == symbol) count++;
        return count;
    }

string read(ifstream& f) {
    string s = "", tmp_s;
    if (f.good()) {
        while (!f.eof()) {
            getline(f, tmp_s);
            s += tmp_s + '\n';
        }
    }
    return s;
}


void fill_vertexes_list(gleipnir<char>& v, string& s) {
    for (int i = 0; i < s.length(); i++) {
        char symbol = s[i];
        if ((i % 6 == 0 || i % 6 == 2) && !v.find(symbol))
            v.push_back(symbol);
    }
}

bool bfs(int** capacity_matrix, int n, int to, int* visited, gleipnir<int>& buffer, int* parents) {
    if (buffer.size() == 0)
        return false;
    int from = buffer[0];
    buffer.remove_front();
    visited[from] = true;
    if (from == to) {
        return true;
    }
    for (int i = 0; i < n; ++i) {
        if (capacity_matrix[from][i] == 0)
            continue;
        if (visited[i] == true || buffer.find(i))
            continue;
        parents[i] = from;
        buffer.push_back(i);
    }
    return bfs(capacity_matrix, n, to, visited, buffer, parents);
}

void print_path(int from, int to, int* parents, gleipnir<char>& v) {
    if (to == from) {
       cout << v[to];
        return;
    }
    int prefrom = parents[to];
    print_path(from, prefrom, parents, v);
    cout << " -> " << v[to];
}

int** get_capacity_matrix(string& s, gleipnir<char>& v) {
    int** capacity_matrix = new int* [v.size()];
    for (int i = 0; i < s.length(); i++)
        capacity_matrix[i] = new int[v.size()];

    for (int i = 0; i < v.size(); i++)
        for (int j = 0; j < v.size(); j++)
            capacity_matrix[i][j] = 0;

    char v1, v2;
    int c;
    for (int i = 0; i < s.length(); i++) {
        if (i % 6 == 0)
            v1 = s[i];
        else if (i % 6 == 2)
            v2 = s[i];
        else if (i % 6 == 4)
            c = s[i] - '0'; 
        else if (s[i] == '\n') {
            capacity_matrix[v.get_index(v1)][v.get_index(v2)] = c;
        }
    }
    return capacity_matrix;
};

int min(int a, int b) {
    return (a < b) ? a : b;
}

int edmonds_karp_alg(int** matrix, char s, char t, gleipnir<char> v) {
    int* path = new int[v.size()];
    int to;
    int from = v.get_index(s);
    for (int j = 0; j < v.size(); j++) {
        path[j] = -1;
    }
    int* visited = new int[v.size()];
    int max_flow = 0;
    gleipnir<int> buffer;
    buffer.push_back(v.get_index(s));
    while (bfs(matrix, v.size(), v.get_index(t), visited, buffer, path)) {
        to = v.get_index(t);
        int c_min = INT_MAX;
        while (to != from) {
            c_min = min(c_min, matrix[path[to]][to]);
            to = path[to];
        }
        to = v.get_index(t);
        while (to != from) {
            matrix[path[to]][to] = matrix[path[to]][to] - c_min;
            matrix[to][path[to]] += c_min;
            to = path[to];
        }
        max_flow += c_min;
        buffer = gleipnir<int>();
        buffer.push_back(v.get_index(s));
        for (int j = 0; j < v.size(); j++)
            path[j] = -1;
        visited = new int[v.size()];
    }
    return max_flow;
}

int main() {

   

    ifstream file(R"(C:\Users\Даниил Михайлович\source\repos\AISD_CW_sem4\AISD_CW_sem4\data.txt)");
    gleipnir<char> v;
    cout << "input file:\n";
    string s = read(file);
    fill_vertexes_list(v, s);
    int** matrix = get_capacity_matrix(s, v);
    cout << s << "\nList of vertexes: " << v << "\nsize: " << v.size() << "\nmatrix is: \n";
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v.size(); j++)
            cout << matrix[i][j] << " ";
        cout << endl;
    }
    cout << "\nmax flow: " << edmonds_karp_alg(matrix, 'S', 'T', v);
   
    return 0;
}
