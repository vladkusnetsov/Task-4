#include "vector"
#include <stdio.h> 
#include <chrono>
#include <iostream>
#include <algorithm>
#include "set"
#include "math.h"


bool check_vec(std::vector<int> vec, int value)
{
	bool flag = false;
	if (vec.size() == 0)
	{
		return flag;
	}
	
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i] == value) {
			flag = true;
		}
	}
	return flag;
}
 
float mean(std::vector<float> vec)
{
	int N = vec.size();
	if (N == 0) {
		return 0.0;
	}
	
	float result = 0;

	for (int i = 0; i < N; i++)
	{
		result += vec[i];
	}

	return result / N;
}

float standart_miss(std::vector<float> vec)
{
	int N = vec.size();
	float vec_mean = mean(vec);
	float result = 0;

	for (int i = 0; i < vec.size(); i++)
	{
		result += (vec[i] - vec_mean) * (vec[i] - vec_mean);
	}

	return std::sqrt(result / N);
}


int main() {
	std::cout << "input count of numbers" << std::endl;
	//lets generate random numbers

	std::vector<int> supply_vector;
	std::vector<int> test_vector;
	std::set<int> test_set;
	int temp_value = 0;
	bool flag = false;
	int N = 0;
	auto begin = std::chrono::steady_clock::now();
	auto end = std::chrono::steady_clock::now();
	auto elapsed_ms_vec = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
	auto elapsed_ms_set = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

	std::vector<float> results;

	for (int j = 0; j < 100000; j++)
	{
		supply_vector.clear();
		test_set.clear();
		test_vector.clear();

		N = rand();
		N = N%10 + 5; //not big N


		while (supply_vector.size() != N)
		{
			temp_value = rand();

			if (not check_vec(supply_vector, temp_value))
			{
				supply_vector.push_back(temp_value);

			}
		}
		using nanoseconds = std::chrono::duration<long long, std::nano>;
		
		for (int i = 0; i < N; i++)
		{
			test_vector.push_back(supply_vector[i]);
		}
		begin = std::chrono::steady_clock::now();
		std::sort(test_vector.begin(), test_vector.end());
		end = std::chrono::steady_clock::now();
		elapsed_ms_vec = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
		
		std::cout << "The time of vec: " << elapsed_ms_vec.count() << " ns\n";

		begin = std::chrono::steady_clock::now();
		for (int i = 0; i < N; i++)
		{
			test_set.insert(supply_vector[i]);
		}
		end = std::chrono::steady_clock::now();
		elapsed_ms_set = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
		std::cout << "The time of set: " << elapsed_ms_set.count() << " ns\n";

		results.push_back(elapsed_ms_set.count()/elapsed_ms_vec.count());
	}
	std::cout << "*********************" << std::endl;
	std::cout << "constant is: " << mean(results) << " with standart error: " << standart_miss(results) << std::endl;

}