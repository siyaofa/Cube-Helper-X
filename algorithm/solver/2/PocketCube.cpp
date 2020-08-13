//https://comwrg.github.io/2018/12/26/algorithm-solve-pocket-cube/#2-%E7%8A%B6%E6%80%81%E5%8E%8B%E7%BC%A9
/*
    U
    F R B L
    D

    every face
    ---------
    | 0 | 1 |
    | 2 | 3 |
    ---------
    */

/*#include <bits/stdc++.h>*/
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

string ro_name[9] = {
        "F", "F2", "F'",
        "R", "R2", "R'",
        "U", "U2", "U'"
};

enum COLOR {
    U0, U1, U2, U3,
    F0, F1, F2, F3,
    D0, D1, D2, D3,
    R0, R1, R2, R3,
    B0, B1, B2, B3,
    L0, L1, L2, L3
};

//F-Front 顺时针 F2-顺时针两步 F3-逆时针一步 其他类推
enum Rotate {
    RF1, RF2, RF3, RR1, RR2, RR3, RU1, RU2, RU3
};

enum Corner {
    URF, UFL, ULB, UBR, DFR, DLF, DBL, DRB
};

COLOR rotation_matrix[9][24] = {
        //{ U0,U1,U2,U3, F0,F1,F2,F3,    D0,D1,D2,D3 ,   R0,R1,R2,R3,    B0,B1,B2,B3,    L0,L1,L2,L3  },
        {U0, U1, L3, L1, F2, F0, F3, F1, R2, R0, D2, D3, U2, R1, U3, R3, B0, B1, B2, B3, L0, D0, L2, D1},//F
        {U0, U1, D1, D0, F3, F2, F1, F0, U3, U2, D2, D3, L3, R1, L1, R3, B0, B1, B2, B3, L0, R2, L2, R0},//F2
        {U0, U1, R0, R2, F1, F3, F0, F2, L1, L3, D2, D3, D1, R1, D0, R3, B0, B1, B2, B3, L0, U3, L2, U2},//F'
        {U0, F1, U2, F3, F0, D1, F2, D3, D0, B2, D2, B0, R2, R0, R3, R1, U3, B1, U1, B3, L0, L1, L2, L3},//R
        {U0, D1, U2, D3, F0, B2, F2, B0, D0, U1, D2, U3, R3, R2, R1, R0, F3, B1, F1, B3, L0, L1, L2, L3},//R2
        {U0, B2, U2, B0, F0, U1, F2, U3, D0, F1, D2, F3, R1, R3, R0, R2, D3, B1, D1, B3, L0, L1, L2, L3},//R'
        {U2, U0, U3, U1, R0, R1, F2, F3, D0, D1, D2, D3, B0, B1, R2, R3, L0, L1, B2, B3, F0, F1, L2, L3},//U
        {U3, U2, U1, U0, B0, B1, F2, F3, D0, D1, D2, D3, L0, L1, R2, R3, F0, F1, B2, B3, R0, R1, L2, L3},//U2
        {U1, U3, U0, U2, L0, L1, F2, F3, D0, D1, D2, D3, F0, F1, R2, R3, R0, R1, B2, B3, B0, B1, L2, L3}//U'
};

vector<int> ro(vector<int> v, int x) {
    vector<int> data(24);
    for (int i = 0; i < 24; ++i) {
        data[i] = v[rotation_matrix[x][i]];
    }
    return data;
}

int ro_reverse(int i) {
    switch (i) {
        case 0:
        case 3:
        case 6:
            return i + 2;
        case 2:
        case 5:
        case 8:
            return i - 2;
        default:
            return i;
    }
}

vector<int> pos2color(vector<int> arr) {

    int colors[6][4] = {
            {0,  3,  6,  9},
            {1,  8,  14, 19},
            {2,  4,  13, 17},
            {5,  10, 16, 23},
            {7,  11, 20, 22},
            {12, 15, 18, 21}
    };

    for (int i = 0; i < 24; ++i) {
        for (int j = 0; j < 6; ++j) {
            for (int k = 0; k < 4; ++k) {
                if (arr[i] == colors[j][k]) {
                    arr[i] = j;
                }
            }
        }
    }
    return arr;
}

void print(vector<int> arr) {
    if (!arr.size()) {
        cout << endl;
        return;
    }
    cout << arr[0];
    for (int i = 1; i < arr.size(); ++i) {
        cout << " " << arr[i];
    }
    cout << endl;
}

ull color2num(vector<int> arr) {
    ull p[24] = {1, 6, 36, 216, 1296, 7776, 46656, 279936, 1679616, 10077696, 60466176, 362797056,
                 2176782336, 13060694016, 78364164096, 470184984576, 2821109907456, 16926659444736,
                 101559956668416, 609359740010496, 3656158440062976, 21936950640377856,
                 131621703842267136, 789730223053602816};
    ull n = 0;
    for (int i = 0; i < 24; ++i) {
        n += arr[i] * p[i];
    }
    return n;
}

vector<int> num2color(ull n) {
    vector<int> v;
    while (n) {
        v.push_back(n % 6);
        n /= 6;
    }

    return v;
}

void bfs(vector<int> arr) {
    map<ull, vector<int>> step[2];
    queue<ull> q[2];

    ull init = 3021148815593781390;
    q[0].push(init);
    step[0][init] = vector<int>();

    auto c = pos2color(arr);
    ull n = color2num(c);
    q[1].push(n);
    step[1][n] = vector<int>();

    if (n == init) {
        cout << 0 << endl;
        return;
    }

    /* print(m[n]); */

    for (int x = 0;; x = !x) {
        int q_size = q[x].size();
        /* cout << "size  " << q_size << endl; */
        for (int i = 0; i < q_size; ++i) {
            ull k = q[x].front();
            q[x].pop();
            for (int i = 0; i < 9; ++i) {
                    auto v = ro(num2color(k), i);
                v.reserve(24);
                ull n = color2num(v);

                if (step[x].find(n) != step[x].end()) {
                        continue;
                }

                vector<int> s(step[x].at(k));
                s.push_back(i);

                if (step[!x].find(n) != step[!x].end()) {
                    vector<int> &a = s, &b = step[!x].at(n);
                    if (!x) {
                        swap(a, b);
                    }
                    vector<int> ans(a);
                    for (auto p = b.rbegin(); p != b.rend(); ++p) {
                        ans.push_back(ro_reverse(*p));
                    }
                    cout << ans.size() << endl;
                    vector<int> v(arr);
                    for (int i : ans) {
                        cout << ro_name[i] << endl;
                        v = ro(v, i);
                        print(v);
                    }
                    return;
                }

                step[x][n] = s;
                q[x].push(n);
            }
        }


    }


}

int main() {
    vector<int> v(24);
    for (int i = 0; i < 24; ++i) {
        cin >> v[i];
    }

    bfs(v);


    return 0;
}