#ifndef PATIENT_H_
#define PATIENT_H_
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string.h>

/*
Класс пациента
    - фамилия пациента
    - пол
    - возраст
    - место проживания (город)
    - диагноз
*/

class Patient {
public:
	static const int MALE = 0;
	static const int FEMALE = 1;

	int sex = 0;
	int age = 0;
	char last_name[256]{""};
	char hometown [256]{""};
	char diagnosis[256]{""};

	Patient(){}

    Patient(int s, int a, char ln[256], char ht[256], char d[256])
    {
    	sex = s;
    	age = a;
    	strcpy(last_name, ln);
    	strcpy(hometown, ht);
    	strcpy(diagnosis, d);
    }

    void write(std::string file)
    {
    	   std::ofstream wf;
    	   wf.open(file, std::ios::out | std::fstream::app | std::ios::binary);

    	   wf.write((char *) &sex, sizeof(int));
    	   wf.write((char *) &age, sizeof(int));

    	   int lsize = strlen(last_name);
    	   int hsize = strlen(hometown);
    	   int dsize = strlen(diagnosis);
    	   wf.write((char *) &lsize, sizeof(int));
    	   wf.write((char *) &hsize, sizeof(int));
    	   wf.write((char *) &dsize, sizeof(int));

    	   wf.write(last_name, sizeof(char) * lsize);
    	   wf.write(hometown, sizeof(char) * hsize);
    	   wf.write(diagnosis, sizeof(char) * dsize);

    	   wf.close();
    }

    long read(std::string file, int offset = 0)
    {
		std::ifstream rf(file, std::ios::in | std::ios::binary);
		rf.seekg(offset, std::ios::beg);

		rf.read((char *) &sex, sizeof(int));
		rf.read((char *) &age, sizeof(int));

		int lsize, hsize, dsize;
		rf.read((char *) &lsize, sizeof(int));
		rf.read((char *) &hsize, sizeof(int));
		rf.read((char *) &dsize, sizeof(int));
		rf.read(last_name, sizeof(char) * lsize);
		rf.read(hometown, sizeof(char) * hsize);
		rf.read(diagnosis, sizeof(char) * dsize);

		int noffset = rf.tellg();

		rf.close();

		return noffset;
    }

    void print()
    {
    	std::cout << "Фамилия: "<< last_name << '\n';
    	std::cout << "Возраст: "<< age << '\n';
    	std::cout << "Пол: "<< (sex == 0 ? "Мужской" : "Женский") << '\n';
    	std::cout << "Диагноз: "<< diagnosis << '\n';
    	std::cout << "Место проживания: "<< hometown << '\n';
    }

};

#endif /* PATIENT_H_ */
