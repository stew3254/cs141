#include<iostream>

int main()
{
	float radius = 2.5;
	const float PI = 3.141592654;

	float circumference = 2 * PI * radius;
	float area = PI * radius * radius;

	std::cout << "The area is " << area << std::endl;
	std::cout << "The circumference is " << circumference << std::endl;

	return 0;
}
