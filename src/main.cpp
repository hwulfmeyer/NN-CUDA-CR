
#include <iostream>
#include <fstream>
#include <string>
#include "cuda_computing.cuh"
#include "cpu_computing.h"


void
Compute_CPU();

void
Compute_GPU();

int
ReverseInt(int i);

void
ReadMNIST(std::string filename, std::vector<float> &vec);

void 
ReadMNISTLabel(std::string filename, std::vector<float> &vec);

int
main(int argc, char** argv)
{
	std::vector<float> traindata;
	std::vector<float> trainlabel;
	std::vector<float> testdata;
	std::vector<float> testlabel;
	ReadMNIST("..\\..\\data\\mnist\\train-images.idx3-ubyte", traindata);
	Compute_CPU();

	std::cout << "Everything done!";
	getchar();
	return 0;
}


void Compute_CPU()
{
	Cpu_Computing computer;
	computer.setThreads();
}

void Compute_GPU()
{
	Cuda_Computing computer;
	computer.initDevice();
}

int ReverseInt(int i)
{
	unsigned char ch1, ch2, ch3, ch4;
	ch1 = i & 255;
	ch2 = (i >> 8) & 255;
	ch3 = (i >> 16) & 255;
	ch4 = (i >> 24) & 255;
	return((int)ch1 << 24) + ((int)ch2 << 16) + ((int)ch3 << 8) + ch4;
}

void ReadMNIST(std::string filename, std::vector<float> &vec)
{
	std::ifstream file(filename, std::ios::binary);
	if (!file.is_open())
	{
		std::cout << "MNIST file not opened!" << std::endl;
	}
	else {
		int magic_number = 0;
		int number_of_images = 0;
		int n_rows = 0;
		int n_cols = 0;
		file.read((char*)&magic_number, sizeof(magic_number));
		magic_number = ReverseInt(magic_number);

		file.read((char*)&number_of_images, sizeof(number_of_images));
		number_of_images = ReverseInt(number_of_images);

		file.read((char*)&n_rows, sizeof(n_rows));
		n_rows = ReverseInt(n_rows);

		file.read((char*)&n_cols, sizeof(n_cols));
		n_cols = ReverseInt(n_cols);

		for (int i = 0; i < number_of_images * n_rows * n_cols; ++i) {
			unsigned char temp = 0;
			file.read((char *)&temp, sizeof(temp));
			vec.push_back((float)(temp) / 255.f);
		}
	}
}

void ReadMNISTLabel(std::string filename, std::vector<float> &vec) {
	std::cout << "Reading MNIST labels!" << std::endl;
	std::ifstream file(filename, std::ios::binary);
	if (file.is_open()) {
		std::cout << "MNIST label file opened!" << std::endl;
		int magic_number = 0;
		int number_of_images = 0;
		file.read((char *)&magic_number, sizeof(magic_number));
		magic_number = ReverseInt(magic_number);
		file.read((char *)&number_of_images, sizeof(number_of_images));
		number_of_images = ReverseInt(number_of_images);
		for (int i = 0; i < number_of_images; ++i) {
			unsigned char temp = 0;
			file.read((char *)&temp, sizeof(temp));
			// std::cout << (int)temp << std::endl;
			for (int j = 0; j < 10; j++) {
				if ((int)temp != j) {
					vec.push_back(0.f);
					// std::cout << "0 ";
				}
				else {
					vec.push_back(1.f);
					// std::cout << "1 ";
				}
			}
			// std::cout << std::endl;
		}
	}
	else {
		std::cout << "MNIST label file not opened!" << std::endl;
	}
}
