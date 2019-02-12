#include <iostream>
#include <vector>
/*

Имеется натуральное число n. За один ход с ним можно произвести следующие действия:

    Вычесть единицу
    Разделить на два
    Разделить на три

При этом стоимость каждой операции - текущее значение n. 
Стоимость преобразования - суммарная стоимость всех операций в 
преобразовании. Вам необходимо с помощью последовательностей 
указанных операций преобразовать число n в единицу таким образом, 
чтобы стоимость преобразования была наименьшей. Делить можно только нацело.

*/



int main(int argc, char const *argv[])
{
	int n;

	std::cin >> n;

	std::vector<int> x(n + 1), y(n + 1);

    for (int i = 2; i <= n; i++) {
        x[i] = x[i - 1] + i;
        y[i] = 1;

        if (i % 2 == 0 && x[i / 2] + i < x[i]) {
            x[i] = x[i / 2] + i;
            y[i] = 2;
        }
        if (i % 3 == 0 && x[i / 3] + i < x[i]) {
            x[i] = x[i / 3] + i;
            y[i] = 3;
        }

    }

    std::cout << x.back() << std::endl;

	int current = n;
	while (current > 1) {
		if (y[current] == 1) {
			std::cout << "-1";
			current--;
		}
		else if (y[current] == 2) {
			std::cout << "/2";
			current /= 2;
		}
		else {
			std::cout << "/3";
			current /= 3;
		}
		if (current != 1) std::cout << " ";
	}
	std::cout << std::endl;
	
	return 0;

}



