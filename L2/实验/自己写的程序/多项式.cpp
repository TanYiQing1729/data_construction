#include <iostream>
#include  <string> 

using namespace std;

/* UPLOAD START */
// You can use VecList, LinkList or none of these structures in writing the IntPolynomial class
template <class T>
class VecList{
    private:
        int capacity;
        int length;
        T* arr;
        void doubleListSize(){
            T * oldArr = arr;
            arr = new T[2*capacity];
            capacity = 2 * capacity;
            for(int i=0;i<length;i++){
                arr[i] = oldArr[i];
            }
            delete [] oldArr;
        }
    public:
        VecList(){
            length = 0;
            capacity = 100;
            arr = new T[capacity];
        }
        VecList(T* a, int n){
            length = n;
            capacity = 100 + 2*n;
            arr = new T[capacity];
            for(int i=0;i<n;i++){
                arr[i] = a[i];
            }
        }
        ~VecList(){
            delete [] arr;
        }
        int getLength(){
            return length;
        }
        bool isEmpty(){
            return length==0;
        }
        void insertEleAtPos(int i, T x){
            if(length==capacity)
                doubleListSize();
            if(i > length || i < 0)
                throw "Illegal position";
            for(int j=length;j>i;j--)
                arr[j] = arr[j-1];
            arr[i] = x;
            length++;
        }
        T deleteEleAtPos(int i){
            if(i >= length || i < 0)
                throw "Illegal position";
            T tmp = arr[i];
            for(int j=i;j<length-1;j++)
                arr[j] = arr[j+1];
            length--;
            return tmp;
        }
        void setEleAtPos(int i, T x){
            if(i >= length || i < 0)
                throw "Illegal position";
            arr[i] = x;
        }
        T getEleAtPos(int i){
            if(i >= length || i < 0)
                throw "Illegal position";
            return arr[i];
        }
        int locateEle(T x){
            for(int i=0;i<length;i++){
                if(arr[i]==x)
                    return i;
            }
            return -1;
        }
        void printList(){
            for(int i=0;i<length;i++)
                cout << arr[i] << " ";
        }
};

class IntPolynomial{
    private:
        int* C;
        int* D;
        int num;

    public:
        IntPolynomial(){
            num = 0;
            C = nullptr;
            D = nullptr;

        }
        IntPolynomial(int * c, int * d, int n){
            num = n;
            C = new int[num];
            D = new int[num];
			for(int i=0;i<num;i++){
            	C[i]=c[i];
			}
			for(int i=0;i<num;i++){
				D[i]=d[i];
			}

			//合并同类项
			for(int i=0;i<num-1;i++){
                if(C[i]==0)
                    continue;
                for(int j=i+1;j<num;j++){
                    if(D[i]==D[j]){
                        C[i] += C[j];
                        C[j] = 0;
                    }
                }
			}

			//过滤带0项
			int newnum = 0;
			for(int i=0;i<num;i++){
                if(C[i]!=0){
                    newnum++;
                }
			}

			int* Cnew = new int[newnum];
			int* Dnew = new int[newnum];
			int idx = 0;
            for(int i=0;i<num;i++){
                if(C[i] != 0){
                    Cnew[idx] = C[i];
                    Dnew[idx] = D[i];
                    idx++;
                }
            }

            //升幂排列
            int change_c = 0;
            int change_d = 0;
            for(int i=0;i<newnum-1;i++){
                for(int j=i+1;j<newnum;j++){
                    if(Dnew[i]>Dnew[j]){
                        change_d = Dnew[i];
                        Dnew[i] = Dnew[j];
                        Dnew[j] = change_d;
                        change_c = Cnew[i];
                        Cnew[i] = Cnew[j];
                        Cnew[j] = change_c;
                    }
                }
            }


            delete[] C;
            delete[] D;
            C = Cnew;
            D = Dnew;
            num = newnum;

        }
        ~IntPolynomial(){
            delete [] C;
            delete [] D;
        }
        int getDegree(){
            if(num == 0){
                return -1;
            }
            int degree = 0;
			for(int i=0;i<num;i++){
            	if(D[i]>degree)
            	degree = D[i];
			}
			return degree;
        }

        IntPolynomial* Add(IntPolynomial* b){
			//搞一个空数组，暂存答案
			int max_num = num + b->num;
			int* temp_c = new int[max_num];
			int* temp_d = new int[max_num];
			int temp_count = 0;

			for(int i=0;i<num;i++){
                temp_c[temp_count] = C[i];
                temp_d[temp_count] = D[i];
                temp_count++;
			}

			//如果有同类相就相加，否则新增指数位
			for(int j=0;j<b->num;j++){
                bool found = 0;
                for(int i=0;i<num;i++){
                    if(temp_d[i]==b->D[j]){
                        temp_c[i] += b->C[j];
                        found = 1;
                        break;
                    }
                }
                if(found == 0){
                    temp_d[temp_count] = b->D[j];
                    temp_c[temp_count] = b->C[j];
                    temp_count++;
                }
			}

			//计算答案的长度
			int result_count = 0;

            for(int i=0;i<temp_count;i++){
                if(temp_c[i] != 0){
                    result_count++;
                }
            }
            //分配空间
            int* result_c = new int[result_count];
            int* result_d = new int[result_count];

            int idx = 0;
            for(int i=0;i<temp_count;i++){
                if(temp_c[i] != 0){
                result_c[idx] = temp_c[i];
                result_d[idx] = temp_d[i];
                idx++; // 仅有效项递增索引
                }
            }
            //升幂排列
            int change_c = 0;
            int change_d = 0;
            for(int i=0;i<result_count-1;i++){
                for(int j=i+1;j<result_count;j++){
                    if(result_d[i]>result_d[j]){
                        change_d = result_d[i];
                        result_d[i] = result_d[j];
                        result_d[j] = change_d;
                        change_c = result_c[i];
                        result_c[i] = result_c[j];
                        result_c[j] = change_c;
                    }
                }
            }
            IntPolynomial* result = new IntPolynomial(result_c, result_d, result_count);

            delete[] temp_c;
            delete[] temp_d;

            return result;
        }

        IntPolynomial* Subtract(IntPolynomial* b){
            //搞一个空数组，暂存答案
			int max_num = num + b->num;
			int* temp_c = new int[max_num];
			int* temp_d = new int[max_num];
			int temp_count = 0;

			for(int i=0;i<num;i++){
                temp_c[temp_count] = C[i];
                temp_d[temp_count] = D[i];
                temp_count++;
			}

			//如果有同类相就相减，否则新增指数位
			for(int j=0;j<b->num;j++){
                bool found = 0;
                for(int i=0;i<num;i++){
                    if(temp_d[i]==b->D[j]){
                        temp_c[i] -= b->C[j];
                        found = 1;
                        break;
                    }
                }
                if(found == 0){
                    temp_d[temp_count] = b->D[j];
                    temp_c[temp_count] = -b->C[j];
                    temp_count++;
                }
			}

			//计算答案的长度
			int result_count = 0;

            for(int i=0;i<temp_count;i++){
                if(temp_c[i] != 0){
                    result_count++;
                }
            }
            //分配空间
            int* result_c = new int[result_count];
            int* result_d = new int[result_count];

            int idx = 0;
            for(int i=0;i<temp_count;i++){
                if(temp_c[i] != 0){
                result_c[idx] = temp_c[i];
                result_d[idx] = temp_d[i];
                idx++; // 仅有效项递增索引
                }
            }

            int change_c = 0;
            int change_d = 0;
            for(int i=0;i<result_count-1;i++){
                for(int j=i+1;j<result_count;j++){
                    if(result_d[i]>result_d[j]){
                        change_d = result_d[i];
                        result_d[i] = result_d[j];
                        result_d[j] = change_d;
                        change_c = result_c[i];
                        result_c[i] = result_c[j];
                        result_c[j] = change_c;
                    }
                }
            }
            IntPolynomial* result = new IntPolynomial(result_c, result_d, result_count);

            delete[] temp_c;
            delete[] temp_d;

            return result;
        }

        IntPolynomial* Multiply(IntPolynomial* b){
            //考虑0多项式
            if(num == 0 || b->num == 0){
                return new IntPolynomial();
            }

            IntPolynomial* result = new IntPolynomial();
			int single_c = 0;
			int single_d = 0;
			int temp_c[1] = {0};
			int temp_d[1] = {0};

			for(int i=0;i<num;i++){
                for(int j=0;j<b->num;j++){
                single_c = C[i]*b->C[j];
                single_d = D[i]+b->D[j];
                temp_c[0] = {single_c};
                temp_d[0] = {single_d};
                IntPolynomial* term = new IntPolynomial(temp_c, temp_d, 1);
                IntPolynomial* old_result =  result;
                result = result->Add(term);
                delete term;
                delete old_result;
                }
			}
			return result;
        }


        void printPolynomial(){
            bool judge = 0;
			for(int i=0;i<num;i++){
				if(C[i] != 0 && C[i] != 1 && C[i] != -1){  //zhe ceng luo ji zai guan xi shu
					if(i == 0 || C[i] < 0){   //zhe ceng luo ji zai guan fu hao
						if(D[i] == 0)
						cout<<C[i];
						else if(D[i]==1)
						cout<<C[i]<<"x";
						else
						cout<<C[i]<<"x^"<<D[i];
					}
					else{
						if(D[i] == 0)
						cout<<"+"<<C[i];
						else if(D[i]==1)
						cout<<"+"<<C[i]<<"x";
						else
						cout<<"+"<<C[i]<<"x^"<<D[i];
					}
					judge = 1;
				}
				else if(C[i] == 1){
					if(i == 0){   //zhe ceng luo ji zai guan fu hao
						if(D[i] == 0)
						cout<<C[i];
						else if(D[i]==1)
						cout<<"x";
						else
						cout<<"x^"<<D[i];
					}
					else{
						if(D[i] == 0)
						cout<<"+"<<C[i];
						else if(D[i]==1)
						cout<<"+"<<"x";
						else
						cout<<"+"<<"x^"<<D[i];
					}
					judge = 1;
				}
				else if(C[i] == -1){
					if(D[i] == 0)
					cout<<C[i];
					else if(D[i]==1)
					cout<<"-"<<"x";
					else
					cout<<"-"<<"x^"<<D[i];
					judge = 1;
				}
			}
			if(judge == 0){
				cout<<"0";
			}
			cout<<endl;
        }
};

/* UPLOAD END */

void test1(){    
    int p4c[5] = {-3,-5,6,1,-1};
    int p4d[5] = {1,3,7,9,11};
    IntPolynomial p4(p4c,p4d,5);
    p4.printPolynomial();
}

void test2(){
    int p1c[3] = {3,5,-6};
    int p1d[3] = {0,1,4};
    IntPolynomial p1(p1c,p1d,3);
    
    int p4c[5] = {-3,-5,6,1,-1};
    int p4d[5] = {1,3,7,9,11};
    IntPolynomial p4(p4c,p4d,5);
    
    p1.Add(&p4)->printPolynomial();
    p4.Subtract(&p1)->printPolynomial();
    
    p4.Add(&p4)->printPolynomial();
    p4.Subtract(&p4)->printPolynomial();
}

void test3(){
    int p1c[3] = {1,-1,5};
    int p1d[3] = {0,3,7};
    IntPolynomial p1(p1c,p1d,3);
    
    int p2c[4] = {1,1,6,10};
    int p2d[4] = {0,3,20,40};
    IntPolynomial p2(p2c,p2d,4);
    
    p1.Multiply(&p2)->printPolynomial();
}

int main(){
    int x;
    cin >> x;
    switch(x){
        case 1: test1(); break;
        case 2: test2(); break;
        case 3: test3(); 
        default:
        ;
    }
    return 0;
}
