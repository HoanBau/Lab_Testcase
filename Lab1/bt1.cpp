#include <iostream>
#include <sstream>
#include <cmath>
#include <string>
#include <vector>
using namespace std;

int solveQuartic(double a, double b, double c, double x[]) {
    // Truong hop phuong trinh 0 = 0 → vo so nghiem
    if (a == 0 && b == 0 && c == 0) return -1;

    // Truong hop a = 0, b = 0 nhung c ≠ 0 → vo nghiem
    if (a == 0 && b == 0) return 0;

    // Truong hop a = 0 → phuong trinh bac 2: b*x^2 + c = 0
    if (a == 0) {
        double y = -c / b;
        if (y < 0) return 0;  // neu y < 0 thi vo nghiem
        x[0] = sqrt(y);
        x[1] = -sqrt(y);
        return 2;
    }

    // Giai phuong trinh bac 2: a*y^2 + b*y + c = 0
    double delta = b*b - 4*a*c;
    if (delta < 0) return 0; // vo nghiem neu delta < 0

    double y1 = (-b + sqrt(delta)) / (2*a);
    double y2 = (-b - sqrt(delta)) / (2*a);

    int count = 0;
    // Neu y1 >= 0 thi sinh ra 2 nghiem x = ±sqrt(y1)
    if (y1 >= 0) {
        x[count++] = sqrt(y1);
        x[count++] = -sqrt(y1);
    }
    // Neu y2 >= 0 va khac y1 thi sinh ra 2 nghiem nua
    if (y2 >= 0 && fabs(y2 - y1) > 1e-9) {
        x[count++] = sqrt(y2);
        x[count++] = -sqrt(y2);
    }
    return count;
}

// Ham so sanh double
bool isEqual(double a, double b, double eps=1e-5){ return fabs(a-b)<eps; }

void runTest(double a, double b, double c, string expected){
    double x[4];
    int n = solveQuartic(a, b, c, x);

    // Xay dung chuoi output thuc te
    ostringstream out;
    if (n == -1) out << "Vo so nghiem";
    else if (n == 0) out << "Vo nghiem";
    else {
        out << "Phuong trinh co " << n << " nghiem la: ";
        for (int i = 0; i < n; i++) 
            out << round(x[i]*100000)/100000.0 << " ";
    }

    // In ra de so sanh
    cout << "Input: " << a << " " << b << " " << c << endl;
    cout << "Output:   " << out.str() << endl;
    cout << "Expected: " << expected << endl;

    // Kiểm tra PASSED/FAILED dựa trên nghiệm
    bool passed = false;
    if (expected.find("Vo so nghiem") != string::npos && n == -1) passed = true;
    else if (expected.find("Vo nghiem") != string::npos && n == 0) passed = true;
    else {
        // Tách số từ expected
        vector<double> expVals;
        istringstream iss(expected);
        string word;
        while(iss >> word){
            try {
                double num = stod(word);
                expVals.push_back(num);
            } catch(...) {}
        }
        if(expVals.size() == n){
            passed = true;
            for(int i=0;i<n;i++){
                if(!isEqual(x[i],expVals[i])){ passed=false; break; }
            }
        }
    }
    cout << (passed ? "PASSED\n\n" : "FAILED\n\n");
}

int main(){
    // Test-cases
    runTest(0,0,0,"Vo so nghiem.");
    runTest(0,0,5,"Vo nghiem.");
    runTest(0,2,-8,"Phuong trinh co 2 nghiem thuc: 2 -2 ");
    runTest(1,-5,4,"Phuong trinh co 4 nghiem thuc: 2 -2 1 -1 ");
    runTest(1,0,-4,"Phuong trinh co 2 nghiem thuc: 1.41421 -1.41421 ");
    runTest(1,0,4,"Vo nghiem.");
    runTest(1,2,1,"Vo nghiem.");
    runTest(1,-2,1,"Phuong trinh co 2 nghiem thuc: 1 -1 ");
    runTest(2,3,1,"Vo nghiem.");
    runTest(1,-1,0,"Phuong trinh co 3 nghiem thuc: 0 1 -1 ");
    return 0;
}


