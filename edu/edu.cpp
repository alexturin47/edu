
#include <locale.h>
#include <Windows.h>
#include <string>
#include <list>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

class EduInstituts {

private:
	std::string name;
	int year;
	int out;
	int inVUZ;
	int type;

public:

	EduInstituts(int Type = -1, std::string Name = "", int Year = 2000, int Out = 0, int InVUZ = 0) : type(Type), name(Name), year(Year), out(Out), inVUZ(InVUZ) {};

	int Type() {
		return type;
	};

	int Vuz() {
		return inVUZ;
	};

	int Year() {
		return year;
	};

	int All() {
		return out;
	};

	std::string Name() {
		return name;
	};

};


class School : public EduInstituts {
private:

public:
	School(int Year = 2000, int Out = 0, int InVUZ = 0, std::string Name = "Школа") : EduInstituts(0, Name, Year, Out, InVUZ) {
	};

};

class Licey : public EduInstituts {
private:

public:
	Licey(int Year = 2000, int Out = 0, int InVUZ = 0, std::string Name = "Лицей") : EduInstituts(1, Name, Year, Out, InVUZ) {
	};

};

class Gimnazy : public EduInstituts {
private:

public:
	Gimnazy(int Year = 2000, int Out = 0, int InVUZ = 0, std::string Name = "Гимназия") : EduInstituts(2, Name, Year, Out, InVUZ) {
	};

};



class FReader {
private:
	std::string fileName;

	bool openFile() {
		std::ifstream in(fileName);
		if (in.is_open()) {
			in.close();
			return true;
		}
		return false;
	};

	void SplitLine(std::vector<std::string>& vec, std::string line, char spl) {
		std::string buff = "";
		vec.clear();
		for (int i = 0; i < line.size(); i++) {
			if (line[i] != spl) {
				buff += line[i];
			}
			else {
				vec.push_back(buff);
				buff = "";
			}
		}
		if (buff.size() != 0) {
			vec.push_back(buff);
		}
	};

public:

	FReader(std::string Name) {
		fileName = Name;
	};

	void readFile(std::vector<EduInstituts*>& inst) {
		if (!openFile()) {
			cout << "Ошибка открытия файла с данными!" << endl;
			return;
		}
		std::ifstream in(fileName);
		std::string line;

		while (getline(in, line)) {
			std::map<std::string, std::string> mp;
			std::vector<std::string> entries;
			SplitLine(entries, line, ';');

			for (string entry : entries) {
				std::vector<std::string> keyValue;
				SplitLine(keyValue, entry, '=');
				mp[keyValue[0]] = keyValue[1];
			}

			std::map<std::string, std::string> ::iterator type, year, all, vuz;
			type = mp.find("type");
			year = mp.find("year");
			all = mp.find("allOut");
			vuz = mp.find("inVuz");
			std::string t = type->second;

			School* school;
			Licey* licey;
			Gimnazy* gimnazy;

			switch (t[0]) {
			case '0':  school = new School(stoi(year->second), stoi(all->second), stoi(vuz->second), "Школа");
				inst.push_back(school);
				break;
			case '1': licey = new Licey(stoi(year->second), stoi(all->second), stoi(vuz->second), "Лицей");
				inst.push_back(licey);
				break;
			case '2': gimnazy = new Gimnazy(stoi(year->second), stoi(all->second), stoi(vuz->second), "Гимназия");
				inst.push_back(gimnazy);
				break;
			};
		}
		in.close();

	};

	

	void printAll(std::vector<EduInstituts*>& inst) {

		for (EduInstituts* item : inst) {
			string type = "";

			switch (item->Type()) {
			case 0: type = "Школа";
				break;
			case 1: type = "Лицей";
				break;
			case 2: type = "Гимназия";
				break;
			}
			cout << type << "\tГод выпуска " << item->Year() << "\tВыпущено всего " << item->All() << "\tПоступило в ВУЗЫ " << item->Vuz() <<endl;
		}
	};
};



int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	std::vector<EduInstituts*> inst;

	FReader listInst("edu.txt");
	listInst.readFile(inst);
	listInst.printAll(inst);
	
};
