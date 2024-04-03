#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdint>

//taken from dataset website
const uint64_t num_vertex = 6262104; //vertex numbering goes from 1 to 6262104
const uint64_t num_edges = 15119284; //number of lines in dataset, will be inly used to display progress bar

const char file_path[] = "Dataset/KONECT/dimacs9-W/out.dimacs9-W";

struct node
{
    //no data field as index itself is data
    node *par;
    uint64_t rank;
};

struct edge
{
    uint64_t value1;
    uint64_t value2;
};

// number of nodes are fixed (4039) so using an array to store nodes

node node_list[num_vertex];

//this function initiates all the num_vertex nodes to a default value
void MAKE_SET(node *x) //x is the index
{
    x->par = x;
    x->rank = 0;
}

node *FIND_SET(node *x)
{
    if (x != x->par)
        x->par = FIND_SET(x->par);

    return x->par;
}

void LINK(node *x, node *y)
{
    if (x->rank > y->rank)
        y->par = x;
    else
        x->par = y;

    if (x->rank == y->rank)
        y->rank++;
}

void UNION(edge temp)
{
    if (temp.value1 != temp.value2)
        LINK(FIND_SET(&node_list[temp.value1]), FIND_SET(&node_list[temp.value2]));
}

void update_edge(edge &given_edge, ifstream &fin)
{
    if (!fin.eof())
    {
        char line[100];
        fin.getline(line, 100);

        //removing commented lines
        if (line[0] == '%')
        {
            while (line[0] == '%')
                fin.getline(line, 100);
        }

        stringstream str_strm;
        str_strm << line; //convert the string s into stringstream

        char num[20];

        str_strm >> num;
        given_edge.value1 = atoi(num) -1 ; //convert 1 indexed to 0 indexed

        str_strm >> num;
        given_edge.value2 = atoi(num) -1 ;//convert 1 indexed to 0 indexed

        // cout << given_edge.value1 << " " << given_edge.value2 << endl;
    }
}

const int num_iter = 1;

int main()
{
    float avg_time = 0;

    for (int master = 0; master < num_iter; master++)
    {
        float start_time = clock();

        for (int i = 0; i < num_vertex; i++)
            MAKE_SET(&node_list[i]);

        ifstream fin(file_path, ios::in);

        edge temp;
        for (int i = 0; i < num_edges; i++)
        {
            update_edge(temp, fin);
            UNION(temp);

            cout << (float)i / num_edges * 100 << "% done \r";
        }

        fin.close();

        float end_time = clock();

        float time_taken = (end_time - start_time) * 1000 / CLOCKS_PER_SEC;
        avg_time += time_taken;
        cout << "Time Taken: " << time_taken << "ms" << endl;
    }

    avg_time /= num_iter;
    cout << "Average Time Taken: " << avg_time << "ms" << endl;
}