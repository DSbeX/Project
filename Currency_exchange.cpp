#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

const char FILENAME[] = "valuti.dat";
fstream fp;
const int max_valuti = 50;
int broiValuti = 0;

struct Valuta {
	string ime_valuta;
	string isoCode;
	double kurs_prodava;
	double kurs_kupuva;
	double nalichnost;
	double maksSumazaObmen;
	bool turguva_se;
};

// Функция за добавяне на валута
void dobavi_valuta(Valuta valuti[], int& broiValuti);

// Функция за извеждане на всички валути
void pokaji_valuti(const Valuta valuti[], int broiValuti);

// Функция за извеждане на всички валути
void podmenu_tursene_izvejdane(Valuta valuti[], int broiValuti);

// Функция за намиране и извеждане на валутата с най-ниска наличност
void nai_niska_nalichnost(const Valuta valuti[], int broiValuti);

// Функция за търсене и извеждане на валута по въведен от клавиатурата код по ISO
void tusrsene_isoCode(const Valuta valuti[], int broiValuti);

// Функция за подреждане на основния масив с валути по марж
void podredba_marj(Valuta valuti[], int broiValuti);

// Функция за подреждане на основния масив с валути по наименование
void podredba_naimenovanie(Valuta valuti[], int broiValuti);

// Функция за управление на файл - записване на масива с валути във файл (двоичен)
void create_file(const Valuta valuti[], int& broiValuti);

// Функция за управление на файл - зареждане на масива с валути от файл (двоичен)
void chetene_f(Valuta valuti[], int& broiValuti);

// Функция за намиране на валути с по-голяма наличност и по-нисък марж
void namirane_nai_skupi_valuti_isoCode(const Valuta valuti[], int broiValuti);

// Подменю за операции свързани с наименованието на валутите
void podmenu_naimenovanie_valuta(Valuta valuti[], int broiValuti);

// Подменю за операции свързани с управление на файловете
void podmenu_upravlenie_fail(Valuta valuti[], int broiValuti);

// Функция за извършване на транзакции - покупка/продажба на валута
void izvurshvane_tranzakciq(Valuta valuti[], int broiValuti);

int main()
{
	// Масив от валути с максимален размер max_valuti
	Valuta valuti[max_valuti];

	chetene_f(valuti, broiValuti);

	// Променлива за избор на опции в главното меню
	int izbor;
	do
	{
		// Извеждане на опциите в главното меню
		cout << "1. Dobavi valuta" << endl;
		cout << "2. Pokaji valutite" << endl;
		cout << "3. Tursene i izvejdane na ekrana" << endl;
		cout << "4. Sortirai po marj v namalqvasht red." << endl;
		cout << "5. Upravlenie na faila" << endl;
		cout << "6. Nameri valuti s po-golqma stoinost ot vuvedenata i chiito marj e pod wuweden ot klawiaturata procent." << endl;
		cout << "7. Pokupko-prodajba na valuta." << endl;
		cout << "0. Izhod" << endl;
		cout << "Vuvedete vashiq izbor." << endl;
		// Въвеждане на избора от потребителя
		cin >> izbor;

		// Обработка на избора с помощта на switch
		switch (izbor)
		{
		case 1:
			dobavi_valuta(valuti, broiValuti);
			break;
		case 2:
			pokaji_valuti(valuti, broiValuti);
			break;
		case 3:
			podmenu_tursene_izvejdane(valuti, broiValuti);
			int r;
			cin >> r;
			switch (r)
			{
			case 1:
				nai_niska_nalichnost(valuti, broiValuti);
				break;
			case 2:
				tusrsene_isoCode(valuti, broiValuti);
				break;
			case 3:
				cout << "Obratno kum menuto." << endl;
				break;
			default:
				break;
			}
			break;
		case 4:
			podredba_marj(valuti, broiValuti);
			break;
		case 5:
			podmenu_upravlenie_fail(valuti, broiValuti);
			int m;
			cin >> m;
			switch (m)
			{
			case 1:
				create_file(valuti, broiValuti);
				break;
			case 2:
				chetene_f(valuti, broiValuti);
				break;
			default:
				break;
			}
			break;
		case 6:
			podmenu_naimenovanie_valuta(valuti, broiValuti);
			int z;
			cin >> z;
			switch (z)
			{
			case 1:
				podredba_naimenovanie(valuti, broiValuti);
				break;
			case 2:
				namirane_nai_skupi_valuti_isoCode(valuti, broiValuti);
				break;
			default:
				break;
			}
			break;
		case 7:
			izvurshvane_tranzakciq(valuti, broiValuti);
			break;
		case 0:
			cout << "Izhod ot programata. Dannite se zapametqvat." << endl;
			create_file(valuti, broiValuti);
			break;
		default:
			cout << "Nevaliden izbor. Molq opitaite otnovo." << endl;
		}
	} while (izbor != 0); // Повтаряне на цикъла докато потребителят не въведе невалидна опция
	return 0;
}

void dobavi_valuta(Valuta valuti[], int& broiValuti)
{
	// Променлива за бройката на валутите, които потребителят иска да добави
	int n;
	cout << "Vuvedete kolko valuti iskate da dobavite: ";
	// Въвеждане на броя на валутите, които потребителят иска да добави
	cin >> n;

	// Проверка дали броя на валутите е валиден
	if (n <= 0)
	{
		cout << "Nevaliden broi valuti za dobavqne. Molq vuvedete polojitelno chislo." << endl;
		return;
	}

	// Проверка дали общият брой валути след добавянето не надвишава максималния лимит
	if (broiValuti + n > max_valuti)
	{
		cout << "Nadvishava se maksimalniq broi ot pozvolenite valuti.";
		return;
	}

	// Цикъл за въвеждане на данни за всяка добавяна валута
	for (int i = broiValuti; i < broiValuti + n; ++i)
	{
		cout << "Dobavete danni za valuta: " << i + 1 << endl;

		// Въвеждане на данни за валутата
		cout << "Naimenovianie na valutata: ";
		cin >> valuti[i].ime_valuta;
		cout << "ISO code: ";
		cin >> valuti[i].isoCode;
		cout << "Kurs prodava: ";
		cin >> valuti[i].kurs_prodava;
		cout << "Kurs kupuva: ";
		cin >> valuti[i].kurs_kupuva;
		cout << "Nalichnost: ";
		cin >> valuti[i].nalichnost;
		cout << "Maksimalna tranzakciq: ";
		cin >> valuti[i].maksSumazaObmen;
		cout << "Turguva li se(vuvedete 1 za da i 0 za ne): ";
		cin >> valuti[i].turguva_se;
	}

	// Увеличаване на брояча на валутите
	broiValuti += n;

	// Извеждане на съобщение за успешно добавени валути
	cout << n << "valuti sa dobaveni uspeshno." << endl;
}

void pokaji_valuti(const Valuta valuti[], int broiValuti)
{

	// Проверка дали има налични валути
	if (broiValuti != 0)
	{
		// Извеждане на заглавен ред с имената на полетата в таблицата
		cout << "Vsichki valuti" << endl;
		cout << left << setw(10) << "ISO Code" << left << setw(7) << "Ime" << left << setw(15) << "Kurs prodava" << left << setw(15)
			<< "Kurs kupuva" << left << setw(15) << "Smetka" << left << setw(18) << "Maks tranzakciq" << left << setw(15) << "Turguva se" << endl;
	}
	else
	{
		// Извеждане на съобщение, че няма налични валути и приключване на функцията
		cout << "Nqma nalichni valuti." << endl;
		cout << endl;
		return;
	}

	// Извеждане на информацията за всяка валута в таблица
	for (int i = 0; i < broiValuti; i++)
	{
		cout << left << setw(10) << valuti[i].isoCode << left << setw(7) << valuti[i].ime_valuta << left << setw(15) << valuti[i].kurs_prodava
			<< left << setw(15) << valuti[i].kurs_kupuva << left << setw(15) << valuti[i].nalichnost << left << setw(18) << valuti[i].maksSumazaObmen << left << setw(15) << valuti[i].turguva_se << endl;

	}

}

void podmenu_tursene_izvejdane(Valuta valuti[], int broiValuti)
{
	cout << "-----------------------------------------------------------------------------------" << endl;
	cout << "1. Namirane i izvejdane na valutata s nai-niska nalichnost." << endl;
	cout << "2. Tursene i izvejdane na valuta po vuveden ot klaviaturata kod po ISO." << endl;
	cout << "3. Vrushtane kum glavnoto menu." << endl;
}

void podmenu_upravlenie_fail(Valuta valuti[], int broiValuti)
{
	cout << "-------------------------------------------------------------------------------------" << endl;
	cout << "1. Izvejdane na masiva s valuti ot fail." << endl;
	cout << "2. Vuvejdane na masiva s valuti ot fail." << endl;
}

void nai_niska_nalichnost(const Valuta valuti[], int broiValuti)
{

	// Проверка дали има налични валути
	if (broiValuti == 0)
	{
		cout << "Nqma nalichni valuti." << endl;
		return;
	}

	// Инициализация на минималната стойност и индекса на валутата с най-ниска наличност
	double minstoinost = valuti[0].nalichnost;
	int minindex = 0;

	// Намиране на валутата с най-ниска наличност в масива
	for (int i = 1; i < broiValuti; ++i)
	{
		if (valuti[i].nalichnost < minstoinost)
		{
			minstoinost = valuti[i].nalichnost;
			minindex = i;
		}
	}

	// Извеждане на информация за валутата с най-ниска наличност
	cout << "Valuti s nai niska stoinost: " << endl;
	cout << "Naimenovanie: " << valuti[minindex].ime_valuta << endl;
	cout << "ISO Code: " << valuti[minindex].isoCode << endl;
	cout << "Balance: " << valuti[minindex].nalichnost << endl;
}

void tusrsene_isoCode(const Valuta valuti[], int broiValuti)
{

	// Проверка дали има налични валути
	if (broiValuti == 0)
	{
		cout << "Nqma nalichni valuti" << endl;
		return;
	}

	// Потребителски вход за търсене на ISO Code
	string turseneIsoCode;
	cout << "Vuvedete ISO Code koito da se tursi: ";
	cin >> turseneIsoCode;

	// Търсене на валута по въведения ISO Code
	for (int i = 0; i < broiValuti; ++i)
	{
		if (valuti[i].isoCode == turseneIsoCode)
		{
			// Извеждане на информация за намерената валута
			cout << "Vashata valuta: " << endl;
			cout << "Naimenovanie na valuta: " << valuti[i].ime_valuta << endl;
			cout << "ISO Code: " << valuti[i].isoCode << endl;
			cout << "Balance: " << valuti[i].nalichnost << endl;
			return;
		}
	}
	// Извеждане на съобщение, ако валутата не е намерена
	cout << "Valuta s ISO Code '" << turseneIsoCode << "' ne e namerena." << endl;
}

void podredba_marj(Valuta valuti[], int broiValuti)
{

	// Проверка дали има налични валути
	if (broiValuti == 0)
	{
		cout << "Nqma nalichni valuti." << endl;
		return;
	}
	//Флаг за проверка дали масивът е вече сортиран
	bool sortirano = false;
	// Сортиране на валутите по разлика между курса на продажба и купува
	for (int i = 0; i < broiValuti - 1; ++i)
	{
		sortirano = true; // Предполагаме че масивът е сортиран
		for (int j = 0; j < broiValuti - i - 1; ++j)
		{
			double marjA = valuti[j].kurs_prodava - valuti[j].kurs_kupuva;
			double marjB = valuti[j + 1].kurs_prodava - valuti[j + 1].kurs_kupuva;

			// Проверка за намаляващ ред на разликата между курса на продажба и купува
			if (marjA < marjB)
			{
				// Размяна на местата на валутите
				Valuta temp = valuti[j];
				valuti[j] = valuti[j + 1];
				valuti[j + 1] = temp;

				sortirano = false; // Ако правим размяна масивът не е сортиран.
			}
		}
		if (sortirano)
		{
			break;
		}
	}
	cout << "Valutite sa sortirani po marj v namalqvasht red." << endl;
}

void create_file(const Valuta valuti[], int& broiValuti) {

	fstream fp(FILENAME, ios::out | ios::binary); //създаване на файл
	if (!fp.is_open()) {
		cout << "Greshka pri otvarqne na faila za zapis." << endl;
		return;
	}
	fp.write((char*)&broiValuti, sizeof(int)); // записване на броя на валутите в началото на файла

	for (int i = 0; i < broiValuti; i++) // записване на данните за всяка валута във файла
	{
		int razmer = valuti[i].ime_valuta.size();
		fp.write((char*)&razmer, sizeof(razmer));
		fp.write((char*)&(valuti[i].ime_valuta[0]), razmer); // записване на размера на името на валутата и самото име

		razmer = valuti[i].isoCode.size();
		fp.write((char*)&razmer, sizeof(razmer)); // записване на големината на исо кода
		fp.write((char*)&(valuti[i].isoCode[0]), razmer); // записване на исо кода

		fp.write((char*)&valuti[i].kurs_prodava, sizeof(double)); // записване на курс продава
		fp.write((char*)&valuti[i].kurs_kupuva, sizeof(double)); // записване на курс купува
		fp.write((char*)&valuti[i].nalichnost, sizeof(double)); // записване за наличност
		fp.write((char*)&valuti[i].maksSumazaObmen, sizeof(double)); // записване на макс сума за обмен
		fp.write((char*)&valuti[i].turguva_se, sizeof(bool)); // записване дали се търгува
	}

	fp.close(); // затваряне на файл
	cout << "Dannite sa uspeshno zapisani vuv faila." << endl;

}

void chetene_f(Valuta valuti[], int& broiValuti) {

	fstream fp(FILENAME, ios::in | ios::binary); // отваряне на файл

	if (!fp.is_open()) {
		cout << "Greshka pri otvarqne na faila za chetene." << endl;
		return;
	}

	fp.read((char*)&broiValuti, sizeof(int));

	for (int i = 0; i < broiValuti; i++)
	{
		int golemina;
		fp.read((char*)&golemina, sizeof(golemina));
		valuti[i].ime_valuta.resize(golemina);
		fp.read((char*)&(valuti[i].ime_valuta[0]), golemina);

		fp.read((char*)&golemina, sizeof(golemina));
		valuti[i].isoCode.resize(golemina);
		fp.read((char*)&(valuti[i].isoCode[0]), golemina);

		fp.read((char*)&valuti[i].kurs_prodava, sizeof(double));
		fp.read((char*)&valuti[i].kurs_kupuva, sizeof(double));
		fp.read((char*)&valuti[i].nalichnost, sizeof(double));
		fp.read((char*)&valuti[i].maksSumazaObmen, sizeof(double));
		fp.read((char*)&valuti[i].turguva_se, sizeof(bool));
	}
	fp.close();

	cout << "Dannite sa uspeshno zaredeni ot faila." << endl;
}

void namirane_nai_skupi_valuti_isoCode(const Valuta valuti[], int broiValuti)
{

	// Проверка дали има налични валути
	if (broiValuti == 0)
	{
		cout << "Nqma nalichni valuti." << endl;
		return;
	}

	// Въвеждане на стойност за праг на наличност
	double stoinost_prag;
	cout << "Vuvedete stoinost za prag sprqmo koito da izlizat valutite s po-golqma nalichnost: ";
	cin >> stoinost_prag;

	// Въвеждане на праг за марж в проценти
	double prag_marj;
	cout << "Vuvedete prag za marja v procenti ot koito tezi s po maluk procent da se izpishat: ";
	cin >> prag_marj;

	// Брояч за валутите, отговарящи на критериите
	int valuta_kriterii = 0;

	// Обхождане на валутите и извеждане на тези, които отговарят на критериите
	for (int i = 0; i < broiValuti; ++i)
	{
		if (valuti[i].nalichnost > stoinost_prag && (((valuti[i].kurs_prodava - valuti[i].kurs_kupuva) / valuti[i].kurs_prodava) * 100) < prag_marj)
		{
			cout << "Valuta otgovarqshta na tezi kriterii e: " << endl;
			cout << "Naimenovanie: " << valuti[i].ime_valuta << endl;
			cout << "ISO Code: " << valuti[i].isoCode << endl;
			cout << "Nalichnost: " << valuti[i].nalichnost << endl;
			cout << "Marj: " << (((valuti[i].kurs_prodava - valuti[i].kurs_kupuva) / valuti[i].kurs_prodava) * 100) << "%" << endl;
			valuta_kriterii += 1;
		}
	}

	// Извеждане на съобщение, ако няма валути, отговарящи на критериите
	if (valuta_kriterii == 0) {
		cout << "Nqma valuti otgovarqshti na kriteriq" << endl;
	}
}

void podmenu_naimenovanie_valuta(Valuta valuti[], int broiValuti)
{
	cout << "------------------------------------------------------" << endl;
	cout << "1. Izvejdane na valutite koito se turguvat v podreden red po naimenovanieto na valutata." << endl;
	cout << "2. Valuti koito sa nad balans vuveden ot vas i marj s procent po-nisuk vuveden ot vas." << endl;
	cout << "3. Vrushtane kum glavnoto menu." << endl;
}

void podredba_naimenovanie(Valuta valuti[], int broiValuti)
{

	// Създаване на временен масив за сортиране
	Valuta* tempValuti = new Valuta[broiValuti];
	for (int i = 0; i < broiValuti; ++i)
	{
		tempValuti[i] = valuti[i];
	}

	bool sortirano = false;
	// Сортиране на временния масив по име на валутата
	for (int i = 0; i < broiValuti - 1; ++i)
	{
		sortirano = true; // Предполагаме, че масивът е сортиран
		for (int j = 0; j < broiValuti - i - 1; ++j)
		{
			if (tempValuti[j].ime_valuta > tempValuti[j + 1].ime_valuta)
			{
				Valuta tem = tempValuti[j];
				tempValuti[j] = tempValuti[j + 1];
				tempValuti[j + 1] = tem;

				sortirano = false; // Ако се направи размяна, масивът не е сортиран
			}
		}
		if (sortirano)
		{
			break;
		}
	}

	// Извеждане на сортираните валути по име
	cout << "Valutite sa podredeni po naimenovanie:" << endl;
	pokaji_valuti(tempValuti, broiValuti);

	// Освобождаване на заделената памет за временния масив
	delete[] tempValuti;
}

void izvurshvane_tranzakciq(Valuta valuti[], int broiValuti)
{

	// Въвеждане на ISO код на валутата
	string isoCode;
	cout << "Vuvedete ISO code na valutata: ";
	cin >> isoCode;

	// Търсене на валутата в масива
	int index = -1;
	for (int i = 0; i < broiValuti; ++i)
	{
		if (valuti[i].isoCode == isoCode)
		{
			index = i;
			break;
		}
	}

	// Проверка дали валутата е намерена
	if (index != -1)
	{
		// Проверка дали валутата се търгува
		if (valuti[index].turguva_se)
		{
			double suma;

			// Определяне на действието - покупка или продажба
			cout << "Izberete deistvie: " << endl;
			cout << "1. Pokupka" << endl;
			cout << "2. Prodajba" << endl;
			int jelanie;
			cout << "Vuvedete vashiq izbor(1-2): ";
			cin >> jelanie;

			switch (jelanie)
			{
			case 1:
				cout << "Vuvedete suma za pokupka: ";
				cin >> suma;
				break;
			case 2:
				cout << "Vuvedete suma za prodajba: ";
				cin >> suma;
				break;
			default:
				cout << "Nevaliden izbor. Operaciqta shte bude prekratena." << endl;
				return;
			}
			if (valuti[index].kurs_prodava > valuti[index].kurs_kupuva)
			{
				cout << "Vuvedete suma za pokupka: ";
				cin >> suma;
			}
			else
			{
				cout << "Vuvedete suma za prodajba: ";
				cin >> suma;
			}

			// Проверка дали сумата е валидна и дали има достатъчна наличност
			if (suma <= valuti[index].maksSumazaObmen && suma <= valuti[index].nalichnost)
			{
				// Извършване на транзакцията
				valuti[index].nalichnost -= suma;
				double razlika = valuti[index].kurs_prodava - valuti[index].kurs_kupuva;
				double sumaBGN = suma / valuti[index].kurs_kupuva;

				// Избор на действие - покупка или продажба
				if (jelanie == 1)
				{
					valuti[0].nalichnost += sumaBGN;
				}
				else
				{
					valuti[0].nalichnost -= sumaBGN;
				}
				// Извеждане на съобщение за успешна транзакция
				cout << "Uspeshna ";
				if (jelanie == 1)
				{
					cout << "pokupka";
				}
				else
				{
					cout << "prodajba";
				}
				cout << " na " << suma << " " << valuti[index].ime_valuta << "." << endl;
			}
			else
			{
				// Извеждане на съобщение за грешка
				cout << "Greshka: Nevalidna suma ili nedostatychna nalichnost." << endl;
			}
		}
		else
		{
			// Извеждане на съобщение, че валутата не се търгува
			cout << "Valutata ne se turguva." << endl;
		}
	}
	else
	{
		// Извеждане на съобщение, че валутата не е намерена
		cout << "Valutata s ISO Code '" << isoCode << "' ne e namerena." << endl;
	}
}