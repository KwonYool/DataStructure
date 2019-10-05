#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class MatrixElement {
public:
   int row, col;
   int value;
};

class SparseMatrix {
public:
   int size, nonZero;
   MatrixElement* ele;
   SparseMatrix(int s, int n) : size(s), nonZero(n) {
      ele = new MatrixElement[n];
   }
   ~SparseMatrix() {}

   void addElement(int r, int c, int v) {
      static int indexResult = 0;
      ele[indexResult].row = r;
      ele[indexResult].col = c;
      ele[indexResult].value = v;
      indexResult++;
   }
   int find(int i, int j) {
      int val = 0;
      for (int k = 0; k < nonZero; k++) {
         if (i == ele[k].row && j == ele[k].col)
            val = ele[k].value;
      }
      return val;
   }
   void Multi(SparseMatrix& B, SparseMatrix& Res) {
      int non = 0;
      for (int i = 1; i < Res.size + 1; i++) {
         for (int j = 1; j < Res.size + 1; j++) {
            int value = 0;
            for (int k = 1; k < Res.size + 1; k++) {
               if (find(i, k) != 0 && B.find(k, j) != 0)
                  value += find(i, k) * B.find(k, j);
            }
            if (value != 0) {
               Res.addElement(i, j, value);
               non++;
            }
         }
      }
      Res.nonZero = non;
   }
};

int main(void)
{
   int size, non;
   char comma;
   ifstream in("matrix.inp");
   if (!in.is_open()) {
      cout << "Input File Error" << endl;
      return 0;
   }

   in >> size >> non;
   SparseMatrix A(size, non);
   for (int i = 0; i < A.nonZero; i++) {
      in >> A.ele[i].row;
      in >> comma;
      in >> A.ele[i].col;
      in >> comma;
      in >> A.ele[i].value;
   }
   in >> size >> non;
   SparseMatrix B(size, non);
   for (int i = 0; i < B.nonZero; i++) {
      in >> B.ele[i].row;
      in >> comma;
      in >> B.ele[i].col;
      in >> comma;
      in >> B.ele[i].value;
   }
   in.close();

   if (A.size != B.size) {
      cout << "Multiplication Impossible." << endl;
      return 0;
   }

   SparseMatrix Result(size, A.nonZero * B.nonZero);
   A.Multi(B, Result);

   ofstream out("matrix.out");
   if (out.is_open()) {
      out << Result.size << endl;
      for (int i = 1; i < Result.size + 1; i++) {
         for (int j = 1; j < Result.size + 1; j++) {
            out << Result.find(i, j);
            if (j == Result.size)
               out << endl;
            else
               out << ",";
         }
      }
   }
   out.close();
   return 0;
}
