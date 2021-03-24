#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <cstdlib>
using namespace std;

class Student {
    int age, id, sum, scores[4];
    char name[30];
    public:
        void input(void)
        {
            scanf("%[^,],%d,%d", name, &age, &id);
            for (int i = 0; i < 4; i++)
                scanf(",%d", &scores[i]);
        }
        void calculate(void)
        {
            sum = 0;
            for (int i = 0; i < 4; i++)
                sum += scores[i];
        }
        void output(void)
        {
            printf("%s,%d,%d,%d", name, age, id, sum / 4);
            switch (sum % 4)
            {
                case 0: break;
                case 1: printf(".25");break;
                case 2: printf(".5");break;
                case 3: printf(".75");break;
            }
        }
};

int main() {
	Student student;        // 定义类的对象
	student.input();        // 输入数据
	student.calculate();    // 计算平均成绩
	student.output();       // 输出数据
}