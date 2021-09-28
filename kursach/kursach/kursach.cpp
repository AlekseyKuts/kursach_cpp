#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#pragma comment(lib,"ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>
#include <winsock2.h>
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace std;

SOCKET newConnection;


const char* cin_const = "cincincin";
// ШИФРОВЩИК, НЕ ТРОГАТЬ, УДАРИТ ТОКОМ
// ШИФРОВЩИК, НЕ ТРОГАТЬ, УДАРИТ ТОКОМ
string cypher(string cyph, int q) {
    for (int i = 0; i < cyph.size(); i++)
        cyph[i] += q;
    return cyph;
}
// ШИФРОВЩИК, НЕ ТРОГАТЬ, УДАРИТ ТОКОМ
// ШИФРОВЩИК, НЕ ТРОГАТЬ, УДАРИТ ТОКОМ

void send_cl(string a) {
    char msg[512];
    strcpy(msg, a.c_str());
    send(newConnection, msg, sizeof(msg), NULL);
}

string recv_str() {
    char msg[512];
    recv(newConnection, msg, sizeof(msg), NULL);
    return string(msg);
}

string d_toSTR(double a) {
    string str;
    stringstream cont;
    cont.clear();
    cont << a;
    cont >> str;
    return str;
}

//ЛИЧНЫЙ ПЕРЕВОДЧИК В INT, ПОТОМУ КАК АТОИ УЖАСЕН
int toInt(string a, int left, int right) {
    int z;
    if (a.size() == 0) {
        send_cl("system(\"CLS\")");
        return -1;
    }
    try {
        for (int i = 0; i < a.size(); i++)
            if (a[i] < '0' || a[i] > '9') throw "Введенное значение не является числовым или содержит лишние символы, повторите попытку ввода\n\n\n";
        z = stoi(a.c_str());
        if ((z < left && left != -1) || (z > right && right != -1)) throw "Введенное значение выходит за пределы возможных числовых значений, повторите попытку ввода\n\n\n";
        return z;
    }
    catch (const char* b) {
        send_cl("system(\"CLS\")");
        send_cl(b);
        return -1;
    }
}

//ЛИЧНЫЙ ПЕРЕВОДЧИК В DOUBLE, ПОТОМУ КАК АТОФ УЖАСЕН
double toDouble(string a, double left, double right) {
    double z;
    int count_dot = 0;
    if (a.size() == 0) {
        send_cl("system(\"CLS\")");
        return -1;
    }
    try {
        for (int i = 0; i < a.size(); i++)
            if ((a[i] == ',' || a[i] == '.') && !count_dot) {
                count_dot++;
                a[i] = ',';
            }
            else if (a[i] < '0' || a[i] > '9') throw "Введенное значение не является числовым или содержит лишние символы, повторите попытку ввода\n\n\n";
        z = stof(a.c_str());
        if ((z < left && left != -1) || (z > right && right != -1)) throw "Введенное значение выходит за пределы возможных числовых значений, повторите попытку ввода\n\n\n";
        return z;
    }
    catch (const char* b) {
        send_cl("system(\"CLS\")");
        send_cl(b);
        return -1;
    }
}

//ШАБЛОННЫЙ ПОМОЩНИК СОРТИРОВКИ
template <class X> int compare(X a, X b) {
    if (a > b) return 1;
    else if (a < b) return 2;
    else return 0;
}
//

void copy_report() {
    send_cl("system(\"CLS\")");
    ifstream fin("aim_report.txt");
    ofstream fout("C:/aim_report_copy.txt");
    fout << fin.rdbuf();
    fin.close();
    fout.close();
    send_cl("Копия отчета создана и находится по пути C:\\aim_report_copy.txt\n\n");
    send_cl("system(\"pause\")");
    send_cl("system(\"CLS\")");
}

class product {
protected:
    string name, type, brand;
    double price;
    int product_count;
public:

    virtual void putData() = 0;
    virtual void getFile(ofstream& fout) = 0;
    virtual void getData() = 0;
    virtual bool putFile(ifstream&) = 0;
};

class meat : protected product {
protected:
    string animal;
    double weight;
public:
    void putData() {
        send_cl("Введите наименование товара: ");
        send_cl(cin_const);
        name = recv_str();
        send_cl("system(\"CLS\")");
        send_cl("Введите тип товара: ");
        send_cl(cin_const);
        type = recv_str();
        send_cl("system(\"CLS\")");
        send_cl("Введите марку товара: ");
        send_cl(cin_const);
        brand = recv_str();
        send_cl("system(\"CLS\")");
        send_cl("Введите вид мяса: ");
        send_cl(cin_const);
        animal = recv_str();
        string trash;
        send_cl("system(\"CLS\")");
        while (true) {
            send_cl("Введите вес товара(чтобы обозначить, что значение не целое используйте точку либо запятую): ");
            send_cl(cin_const);
            trash = recv_str();
            weight = toDouble(trash, 0.001, -1);
            if (weight == -1) continue;
            break;
        }
        send_cl("system(\"CLS\")");
        while (true) {
            send_cl("Введите цену товара(чтобы обозначить, что значение не целое используйте точку либо запятую): ");
            send_cl(cin_const);
            trash = recv_str();
            price = toDouble(trash, 0.1, -1);
            if (price == -1) continue;
            break;
        }
        send_cl("system(\"CLS\")");
        while (true) {
            send_cl("Введите количество товара(только целые значения): ");
            send_cl(cin_const);
            trash = recv_str();
            product_count = toInt(trash, 0, -1);
            if (product_count == -1) continue;
            break;
        }
        send_cl("system(\"CLS\")");

    }
    void updateData(int typ) {
        string trash;
        send_cl("system(\"CLS\")");
        if (typ == 1) {
            send_cl("Введите наименование товара: ");
            send_cl(cin_const);
            name = recv_str();
            send_cl("system(\"CLS\")");
        }
        else if (typ == 2) {
            send_cl("Введите тип товара: ");
            send_cl(cin_const);
            type = recv_str();
            send_cl("system(\"CLS\")");
        }
        else if (typ == 3) {
            send_cl("Введите марку товара: ");
            send_cl(cin_const);
            brand = recv_str();
            send_cl("system(\"CLS\")");
        }
        else if (typ == 4) {
            send_cl("Введите вид мяса: ");
            send_cl(cin_const);
            animal = recv_str();
            
            send_cl("system(\"CLS\")");
        }
        else if (typ == 5) {
            while (true) {
                send_cl("Введите вес товара(чтобы обозначить, что значение не целое используйте точку либо запятую): ");
                send_cl(cin_const);
                trash = recv_str();
                weight = toDouble(trash, 0.001, -1);
                if (weight == -1) continue;
                break;
            }
            send_cl("system(\"CLS\")");
        }
        else if (typ == 6) {
            while (true) {
                send_cl("Введите цену товара(чтобы обозначить, что значение не целое используйте точку либо запятую): ");
                send_cl(cin_const);
                trash = recv_str();
                price = toDouble(trash, 0.1, -1);
                if (price == -1) continue;
                break;
            }
            send_cl("system(\"CLS\")");
        }
        else if (typ == 7) {
            while (true) {
                send_cl("Введите количество товара(только целые значения): ");
                send_cl(cin_const);
                trash = recv_str();
                product_count = toInt(trash, 0, -1);
                if (product_count == -1) continue;
                break;
            }
            send_cl("system(\"CLS\")");
        }
    }
    bool putFile(ifstream& fin) {
        string buf;
        if (getline(fin, name)) {
            if (name == "\n") return false;
            getline(fin, type);
            getline(fin, brand);
            getline(fin, animal);
            getline(fin, buf);
            weight = toDouble(buf, -1, -1);
            getline(fin, buf);
            price = toDouble(buf, -1, -1);
            getline(fin, buf);
            product_count = atoi(buf.c_str());
            return true;
        }
        else return false;
    }
    void getFile(ofstream& fout) {
        fout << name << endl << type << endl << brand << endl << animal << endl << weight << endl << price << endl << product_count << endl;
    }
    void getData() {
        send_cl("\n _____________________");
        send_cl("\n|                     | ");
        send_cl("\n| Наименование товара | ");
        send_cl(name.c_str());
        //send_cl("\n_______________________");
        send_cl("\n| Тип товара          | ");
        send_cl(type.c_str());
        //send_cl("\n_______________________");
        send_cl("\n| Марка товара        | ");
        send_cl(brand.c_str());
        //send_cl("\n_______________________");
        send_cl("\n| Вид мяса            | ");
        send_cl(animal.c_str());
        //send_cl("\n_______________________");
        send_cl("\n| Вес                 | ");
        send_cl(d_toSTR(weight));
        //send_cl("\n_______________________");
        send_cl("\n| Цена                | ");
        send_cl(d_toSTR(price));
        //send_cl("\n_______________________");
        send_cl("\n| Количество          | ");
        send_cl(to_string(product_count));
        send_cl("\n|_____________________| ");
        send_cl("\n\n\n");
    }
    void getReport(ofstream& fout) {
        fout << "\nНаименование товара - " << name << "\nТип товара - " << type << "\nМарка товара - " << brand << "\nВид мяса - " << animal << "\nВес - " << weight << "\nЦена - " << price << "\nКоличество - " << product_count << endl;
    }
    int getIntData() {
        return product_count;
    }
    string getStrData(string s) {
        if (s == "name") return name;
        else if (s == "type") return type;
        else if (s == "brand") return brand;
        else if (s == "animal") return animal;
    }
    double getDoubleData(string s) {
        if (s == "price") return price;
        else if (s == "weight") return weight;
    }

};

class order {
    string code;
    meat meat_o;
public:
    void getData() {
        send_cl("\nКод заказа - ");
        send_cl(code.c_str());
        meat_o.getData();
    }
    void putData() {
        send_cl("Введите код заказа: ");
        send_cl(cin_const);
        code = recv_str();
    }
    void meatPutData() {
        meat_o.putData();
    }
    void getFile(ofstream& fout) {
        fout << code << endl;
        meat_o.getFile(fout);
    }
    bool meatPutFile(ifstream& fin) {
        return meat_o.putFile(fin);
    }
    bool putFile(ifstream& fin) {
        if (getline(fin, code)) {
            return meat_o.putFile(fin);
        }
        else return false;
    }
    void getMeat_o(meat a) {
        meat_o = a;
    }
};

class imprt : public order {
    string provider;
public:
    void getData() {
        send_cl("\nПоставщик - ");
        send_cl(provider.c_str());
        order::getData();
    }
    void putData() {
        send_cl("Введите фамилию поставщика: ");
        send_cl(cin_const);
        provider = recv_str();
    }
    void getFile(ofstream& fout) {
        fout << "import" << endl;
        fout << provider << endl;
        order::getFile(fout);
    }
    bool putFile(ifstream& fin) {
        if (getline(fin, provider)) {
            return order::putFile(fin);
        }
        else return false;
    }
};

class exprt : public order {
    string client;
public:
    void getData() {
        send_cl("\nЗаказчик - ");
        send_cl(client.c_str());
        order::getData();
    }
    void putData() {
        send_cl("Введите фамилию заказчика: ");
        send_cl(cin_const);
        client = recv_str();
    }
    void getFile(ofstream& fout) {
        fout << "export" << endl;
        fout << client << endl;
        order::getFile(fout);
    }
    bool putFile(ifstream& fin) {
        if (getline(fin, client)) {
            return order::putFile(fin);
        }
        else return false;
    }
};

class user {


protected:
    string login, password;
public:
    void menu() {
        send_cl("system(\"CLS\")");
        string trash;
        int operation;
        while (true) {
            send_cl("Добро пожаловать в меню пользователя\n\n");
            send_cl("1. Просмотр данных\n2. Поиск записи по заданному параметру\n3. Сортировка записей\n4. Фильтрация записей по некоторым параметрам\n5. Вывод отчета по данным в файл\n0. Выход из меню\n\nВведите номер выбранной операции, одной цифрой и без пробелов: ");
            send_cl(cin_const);
            trash = recv_str();
            operation = toInt(trash, 0, 5);
            if (operation == -1) continue;
            if (operation == 0) return;
            if (operation == 1) getTableData();
            else if (operation == 2) find_d();
            else if (operation == 3) sort_d();
            else if (operation == 4) filter_d();
            else if (operation == 5) report();
        }
    }
    void getTableData() {
        int page = 0;
        ifstream fin("meat.txt");
        meat meat;
        send_cl("system(\"CLS\")");
        send_cl("Меню просмотра данных\n\n");
        while (meat.putFile(fin)) {
            page++;
            send_cl("    | Товар №");
            send_cl(to_string(page));
            send_cl(" |\n\n");
            meat.getData();
        }
        fin.close();
        send_cl("system(\"pause\")");
        send_cl("system(\"CLS\")");
    }
    /*void show_d() {
        int page = 0;
        ifstream fin("meat.txt");
        meat meat;
        while (meat.putFile(fin)) {
            send_cl("system(\"CLS\")");
            send_cl("Меню просмотра данных\n\n");
            page++;
            send_cl("Страница №");
            send_cl(to_string(page));
            send_cl("\n\n");
            meat.getData();
            send_cl("system(\"pause\")");
        }
        fin.close();
        send_cl("system(\"CLS\")");
    };*/
    void sort_d() {
        send_cl("system(\"CLS\")");
        send_cl("Меню сортировки\n\n");
        vector<meat> meats;
        ifstream fin("meat.txt");
        meat dop;
        meat meat;
        while (meat.putFile(fin)) {
            meats.push_back(meat);
        }
        fin.close();
        string type_st;
        int type;
        while (true) {
            send_cl("Выберите параметр по которому будет проводиться сортировка:\n\n1.Наименование товара\n2.Тип товара\n3.Марка товара\n4.Вид мяса\n5.Вес\n6.Цена\n7.Количество продукта\n\nВведите нужный номер одной цифрой, без точки: ");
            send_cl(cin_const);
            type_st = recv_str();
            type = toInt(type_st, 1, 7);
            if (type == -1) continue;
            break;
        }
        int direction;
        send_cl("system(\"CLS\")");
        while (true) {
            send_cl("Выберите каким образом будет проводиться сортировка:\n\n1.По возрастанию\n2.По убыванию\n\nВведите нужный номер одной цифрой, без точки: ");
            send_cl(cin_const);
            type_st = recv_str();
            direction = toInt(type_st, 1, 2);
            if (direction == -1) continue;
            break;
        }
        auto i = meats.begin();
        int l = -1;
        for (i; i != meats.end(); i++) {
            l++;
            for (int j = l + 1; j < meats.size(); j++)
                if (type == 1 && compare((*i).getStrData("name"), meats[j].getStrData("name")) == direction) {
                    dop = (*i);
                    (*i) = meats[j];
                    meats[j] = dop;
                }
                else if (type == 1 && compare((*i).getStrData("name"), meats[j].getStrData("name")) == direction) {
                    dop = (*i);
                    (*i) = meats[j];
                    meats[j] = dop;
                }
                else if (type == 2 && compare((*i).getStrData("type"), meats[j].getStrData("type")) == direction) {
                    dop = (*i);
                    (*i) = meats[j];
                    meats[j] = dop;
                }
                else if (type == 2 && compare((*i).getStrData("type"), meats[j].getStrData("type")) == direction) {
                    dop = (*i);
                    (*i) = meats[j];
                    meats[j] = dop;
                }
                else if (type == 3 && compare((*i).getStrData("brand"), meats[j].getStrData("brand")) == direction) {
                    dop = (*i);
                    (*i) = meats[j];
                    meats[j] = dop;
                }
                else if (type == 3 && compare((*i).getStrData("brand"), meats[j].getStrData("brand")) == direction) {
                    dop = (*i);
                    (*i) = meats[j];
                    meats[j] = dop;
                }
                else if (type == 4 && compare((*i).getStrData("animal"), meats[j].getStrData("animal")) == direction) {
                    dop = (*i);
                    (*i) = meats[j];
                    meats[j] = dop;
                }
                else if (type == 4 && compare((*i).getStrData("animal"), meats[j].getStrData("animal")) == direction) {
                    dop = (*i);
                    (*i) = meats[j];
                    meats[j] = dop;
                }
                else if (type == 5 && compare((*i).getDoubleData("weight"), meats[j].getDoubleData("weight")) == direction) {
                    dop = (*i);
                    (*i) = meats[j];
                    meats[j] = dop;
                }
                else if (type == 5 && compare((*i).getDoubleData("weight"), meats[j].getDoubleData("weight")) == direction) {
                    dop = (*i);
                    (*i) = meats[j];
                    meats[j] = dop;
                }
                else if (type == 6 && compare((*i).getDoubleData("price"), meats[j].getDoubleData("price")) == direction) {
                    dop = (*i);
                    (*i) = meats[j];
                    meats[j] = dop;
                }
                else if (type == 6 && compare((*i).getDoubleData("price"), meats[j].getDoubleData("price")) == direction) {
                    dop = (*i);
                    (*i) = meats[j];
                    meats[j] = dop;
                }
                else if (type == 7 && compare((*i).getIntData(), meats[j].getIntData()) == direction) {
                    dop = (*i);
                    (*i) = meats[j];
                    meats[j] = dop;
                }
                else if (type == 7 && compare((*i).getIntData(), meats[j].getIntData()) == direction) {
                    dop = (*i);
                    (*i) = meats[j];
                    meats[j] = dop;
                }
        }
        send_cl("system(\"CLS\")");
        send_cl("УПОРЯДОЧЕННЫЕ ДАННЫЕ:\n\n");
        for (int i = 0; i < meats.size(); i++) {
            meats[i].getData();
        }
        send_cl("system(\"pause\")");
        send_cl("system(\"CLS\")");
    }
    void find_d() {
        double find_d;
        int find_i, type;
        string find_s, type_s;
        meat meat;
        send_cl("system(\"CLS\")");
        while (true) {
            send_cl("Выберите параметр по которому будет проводиться поиск:\n\n1.Наименование товара\n2.Тип товара\n3.Марка товара\n4.Вид мяса\n5.Вес\n6.Цена\n7.Количество продукта\n\nВведите нужный номер одной цифрой, без точки: ");
            send_cl(cin_const);
            type_s = recv_str();;
            type = toInt(type_s, 1, 7);
            if (type == -1) continue;
            break;
        }
        while (true) {
            send_cl("Введите запрос для этого параметра: ");
            send_cl(cin_const);
            find_s = recv_str();
            if (type < 5) break;
            if (type < 7) {
                find_d = toDouble(find_s, 0.001, -1);
                if (find_d == -1) continue;
                break;
            }
            find_i = toInt(find_s, 0, -1);
            if (find_i == -1) continue;
            break;
        }
        send_cl("system(\"CLS\")");
        send_cl("Результаты поиска:\n\n");
        ifstream fin("meat.txt");
        while (meat.putFile(fin)) {
            send_cl("\n\n");
            if (type == 1 && meat.getStrData("name") == find_s) meat.getData();
            else if (type == 2 && meat.getStrData("type") == find_s) meat.getData();
            else if (type == 3 && meat.getStrData("brand") == find_s) meat.getData();
            else if (type == 4 && meat.getStrData("animal") == find_s) meat.getData();
            else if (type == 5 && meat.getDoubleData("weight") == find_d) meat.getData();
            else if (type == 6 && meat.getDoubleData("price") == find_d) meat.getData();
            else if (type == 7 && meat.getIntData() == find_i) meat.getData();
        }
        send_cl("system(\"pause\")");
        send_cl("system(\"CLS\")");
    }
    void filter_d() {
        string type_s;
        int type, find_i;
        double find_d;
        meat meat;
        send_cl("system(\"CLS\")");
        while (true) {
            send_cl("Выберите параметр по которому будет проводиться фильтрация:\n\n1.Вес\n2.Цена\n3.Количество продукта\n\nВведите нужный номер одной цифрой, без точки: ");
            send_cl(cin_const);
            type_s = recv_str();
            type = toInt(type_s, 1, 3);
            if (type == -1) continue;
            break;
        }
        send_cl("system(\"CLS\")");
        while (true) {
            send_cl("Введите значение параметра больше/меньше которого будут отображаться отфильтрованные данные: ");
            send_cl(cin_const);
            type_s = recv_str();
            if (type < 3) {
                find_d = toDouble(type_s, 0.001, -1);
                if (find_d == -1) continue;
                break;
            }
            find_i = toInt(type_s, 0, -1);
            if (find_i == -1) continue;
            break;
        }
        int direction;
        send_cl("system(\"CLS\")");
        while (true) {
            send_cl("Выберите каким образом будет проводиться фильтрация:\n\n1.Больше введенного параметра\n2.Меньше введенного параметра\n\nВведите нужный номер одной цифрой, без точки: ");
            send_cl(cin_const);
            type_s = recv_str();
            direction = toInt(type_s, 1, 2);
            if (direction == -1) continue;
            break;
        }
        ifstream fin("meat.txt");
        while (meat.putFile(fin)) {
            if (type == 1 && compare(meat.getDoubleData("weight"), find_d) == direction) meat.getData();
            else if (type == 2 && compare(meat.getDoubleData("price"), find_d) == direction) meat.getData();
            else if (type == 3 && compare(meat.getIntData(), find_i) == direction) meat.getData();
        }
        send_cl("system(\"pause\")");
        send_cl("system(\"CLS\")");
    }
    void report() {
        int page = 0;
        ifstream fin("meat.txt");
        ofstream fout("C:/report.txt");
        meat meat;
        fout << "Отчет по данным";
        while (meat.putFile(fin)) {
            page++;
            fout << "\n\nПродукт №" << page << "\n\n";
            meat.getReport(fout);
        }
        fin.close();
        fout.close();
        send_cl("system(\"CLS\")");
        send_cl("Отчет сформирован в файл report.txt на диске C:\n\n");
        send_cl("system(\"pause\")");
        send_cl("system(\"CLS\")");
    }
    string log_check() {
        this->password = cypher(this->password, 1);
        string login, password;
        ifstream fin("admin.txt");
        while (fin >> login >> password) {
            if (login == this->login && password == this->password) {
                fin.close();
                this->password = cypher(this->password, -1);
                return "admin";
            }
        }
        fin.close();
        fin.open("experts.txt");
        while (fin >> login >> password) {
            if (login == this->login && password == this->password) {
                fin.close();
                this->password = cypher(this->password, -1);
                return "expert";
            }
        }
        fin.close();
        fin.open("users.txt");
        while (fin >> login >> password) {
            if (login == this->login && password == this->password) {
                fin.close();
                this->password = cypher(this->password, -1);
                return "user";
            }
        }
        fin.close();
        this->password = cypher(this->password, -1);
        return "error";
    }
    user() {
        send_cl("system(\"CLS\")");
        while (true) {
            while (true) {
                send_cl("Введите логин(использование пробелов в логине запрещено): ");
                send_cl(cin_const);
                login = recv_str();
                if (login.find(" ") != string::npos) {
                    send_cl("system(\"CLS\")");
                    send_cl("В логине запрещено использование пробелов. Повторите попытку ввода.\n\n\n");
                    continue;
                }
                break;
            }
            while (true) {
                send_cl("Введите пароль(использование пробелов в пароле запрещено): ");
                send_cl(cin_const);
                password = recv_str();
                if (password.find(" ") != string::npos) {
                    send_cl("system(\"CLS\")");
                    send_cl("В пароле запрещено использование пробелов. Повторите попытку ввода\n\n\n");
                    continue;
                }
                break;
            }
            break;
        }
    }
    user(string login, string password) {
        this->login = login;
        this->password = password;
    }
    string getData(string data) {
        if (data == "login") return login;
        else return password;
    }
};

class admin : protected user {

public:
    void menu() {
        send_cl("system(\"CLS\")");
        string trash;
        int operation;
        while (true) {
            
            send_cl("Добро пожаловать в меню администратора\n\n");
            send_cl("1. Просмотр данных\n2. Добавление записи\n3. Редактирование записи\n4. Удаление записи\n5. Поиск записи по заданному параметру\n6. Сортировка записей\n");
            send_cl("7. Фильтрация записей по некоторым параметрам\n8. Вывод отчета по данным в файл\n9. Работа с экспертами\n10. Получить копию последнего отчета по целям\n11. Оформить заказ на экспорт\n12. Оформить заказ на импорт\n13. Просмотреть историю заказов\n0. Выход из меню\n\nВведите номер выбранной операции, целым числом и без пробелов : ");
            send_cl(cin_const);
            trash = recv_str();
            operation = toInt(trash, 0, 13);
            if (operation == -1) continue;
            if (operation == 0) return;
            if (operation == 1) getTableData();
            else if (operation == 2) add_d();
            else if (operation == 3) update_d();
            else if (operation == 4) del_d();
            else if (operation == 5) find_d();
            else if (operation == 6) sort_d();
            else if (operation == 7) filter_d();
            else if (operation == 8) report();
            else if (operation == 9) expert_w();
            else if (operation == 10) copy_report();
            else if (operation == 11) order_ie(true);
            else if (operation == 12) order_ie(false);
            else if (operation == 13) order_show();
            send_cl("system(\"CLS\")");
        }
    };
    void show_ex() {
        send_cl("system(\"CLS\")");
        send_cl("Меню просмотра аккаунтов экспертов");
        string login, password;
        ifstream fin("experts.txt");
        while (fin >> login >> password) {
            send_cl("\n\nЛогин: ");
            send_cl(login.c_str());
            send_cl("\nПароль: ");
            send_cl(cypher(password, -1).c_str());
        }
        send_cl("system(\"pause\")");
        send_cl("system(\"CLS\")");
    }
    void add_ex() {
        send_cl("system(\"CLS\")");
        send_cl("Меню добавления аккаунтов экспертов\n\n");
        user reg;
        if (reg.log_check() != "error") {
            send_cl("system(\"CLS\")");
            send_cl("Ошибка! Данный аккаунт уже зарегистрирован.\n\n\n");
            send_cl("system(\"pause\")");
            send_cl("system(\"CLS\")");
            return;
        }
        ofstream fout("experts.txt", ios_base::app);
        fout << reg.getData("login") << endl << cypher(reg.getData("password"), 1) << endl;
        fout.close();
        int count_ex;
        ifstream fin("countofexperts.txt");
        fin >> count_ex;
        fin.close();
        fout.open("countofexperts.txt");
        fout << count_ex + 1;
        fout.close();
        send_cl("system(\"CLS\")");
        send_cl("Аккаунт успешно зарегистрирован\n");

        send_cl("system(\"pause\")");
        send_cl("system(\"CLS\")");

    }
    void add_d() {
        send_cl("system(\"CLS\")");
        send_cl("Меню добавления товара:\n\n");
        meat meat;
        meat.putData();
        ofstream fout("meat.txt", ios_base::app);
        meat.getFile(fout);
        fout.close();
        send_cl("Данные успешно добавлены\n");
        send_cl("system(\"pause\")");
        send_cl("system(\"CLS\")");
    }
    void del_d() {
        send_cl("system(\"CLS\")");
        ifstream fin("meat.txt");
        string type_s;
        int type;
        int page = 0;
        meat empt;
        vector<meat> meats;
        meats.push_back(empt);
        send_cl("system(\"CLS\")");
        send_cl("Меню удаления данных\n\n");
        while (meats[page].putFile(fin)) {
            page++;
            /*send_cl("    | Товар №");
            send_cl(to_string(page));
            send_cl(" |\n\n");
            meats[page-1].getData();*/
            meats.push_back(empt);
        }
        fin.close();
        while (true) {
            for (int i = 0; i < page; i++) {
                send_cl("    | Товар №");
                send_cl(to_string(i + 1));
                send_cl(" |\n\n");
                meats[i].getData();
            }
            send_cl("\n\nВведите номер товара который хотите удалить(если вы хотите вернуться в меню, введите 0): ");
            send_cl(cin_const);
            type_s = recv_str();
            type = toInt(type_s, 0, page);
            if (type == -1) continue;
            if (type == 0) {
                send_cl("system(\"CLS\")");
                return;
            }
            break;
        }
        send_cl("system(\"CLS\")");
        meats[type - 1].getData();
        send_cl("Данные удалены успешно\n");
        send_cl("system(\"pause\")");
        send_cl("system(\"CLS\")");
        fin.close();
        ofstream fout("meat.txt");
        for (int i = 0; i < page; i++) {
            if (i!=type-1) meats[i].getFile(fout);
        }
        fout.close();
    }
    void update_d() {
        send_cl("system(\"CLS\")");
        ifstream fin("meat.txt");
        string type_s;
        int type;
        int page = 0;
        meat empt;
        vector<meat> meats;
        meats.push_back(empt);
        send_cl("system(\"CLS\")");
        send_cl("Меню редактирования данных\n\n");
        while (meats[page].putFile(fin)) {
            page++;
            /*send_cl("    | Товар №");
            send_cl(to_string(page));
            send_cl(" |\n\n");
            meats[page-1].getData();*/
            meats.push_back(empt);
        }
        fin.close();
        while (true) {
            for (int i = 0; i < page; i++) {
                send_cl("    | Товар №");
                send_cl(to_string(i+1));
                send_cl(" |\n\n");
                meats[i].getData();
            }
            send_cl("\n\nВведите номер товара который хотите редактировать(если вы хотите вернуться в меню, введите 0): ");
            send_cl(cin_const);
            type_s = recv_str();
            type = toInt(type_s, 0, page);
            if (type == -1) continue;
            if (type == 0) {
                send_cl("system(\"CLS\")");
                return;
            }
            break;
        }
        send_cl("system(\"CLS\")");
        string type2_st;
        int type2;
        while (true) {
            meats[type - 1].getData();
            send_cl("Выберите параметр, который хотите редактировать:\n\n1.Наименование товара\n2.Тип товара\n3.Марка товара\n4.Вид мяса\n5.Вес\n6.Цена\n7.Количество продукта\n\nВведите нужный номер одной цифрой, без точки: ");
            send_cl(cin_const);
            type2_st = recv_str();
            type2 = toInt(type2_st, 1, 7);
            if (type2 == -1) continue;
            break;
        }
        meats[type - 1].updateData(type2);
        send_cl("system(\"CLS\")");
        meats[type - 1].getData();
        send_cl("Данные отредактированы успешно\n");
        send_cl("system(\"pause\")");
        send_cl("system(\"CLS\")");
        fin.close();
        ofstream fout("meat.txt");
        for (int i = 0; i<page; i++) {
            meats[i].getFile(fout);
        }
        fout.close();
    }
    void expert_w() {
        send_cl("system(\"CLS\")");
        string trash;
        int operation;
        while (true) {
            send_cl("system(\"CLS\")");
            send_cl("Меню работы с экспертами\n\n1. Просмотр данных об экспертах\n2. Добавить эксперта\n0. Выход в предыдущее меню\n\nВведите номер выбранной операции, одной цифрой и без пробелов: ");
            send_cl(cin_const);
            trash = recv_str();
            operation = toInt(trash, 0, 2);
            if (operation == 0) return;
            else if (operation == 1) show_ex();
            else if (operation == 2) add_ex();
        }
    }
    void order_ie(bool isExport) {
        send_cl("system(\"CLS\")");
        string trash;
        int operation;
        if (!isExport) {
            imprt ord;
            send_cl("system(\"CLS\")");
            while (true) {
                send_cl("Оформление заказа на импорт\n\n");
                send_cl("1. Оформить повторный заказ на продукт\n2. Заказать новый продукт\n0. Вернуться в предыдущее меню\n\nВведите номер выбранной операции, целым числом и без пробелов : ");
                send_cl(cin_const);
                trash = recv_str();
                operation = toInt(trash, 0, 2);
                if (operation == -1) continue;
                if (!operation) return;
                if (operation == 1) {
                    send_cl("system(\"CLS\")");
                    ifstream fin("meat.txt");
                    string type_s;
                    int type;
                    int page = 0;
                    meat empt;
                    vector<meat> meats;
                    meats.push_back(empt);
                    while (meats[page].putFile(fin)) {
                        page++;
                        /*send_cl("    | Товар №");
                        send_cl(to_string(page));
                        send_cl(" |\n\n");
                        meats[page-1].getData();*/
                        meats.push_back(empt);
                    }
                    fin.close();
                    while (true) {
                        for (int i = 0; i < page; i++) {
                            send_cl("    | Товар №");
                            send_cl(to_string(i + 1));
                            send_cl(" |\n\n");
                            meats[i].getData();
                        }
                        send_cl("\n\nВведите номер товара который хотите заказать(если вы хотите вернуться в меню, введите 0): ");
                        send_cl(cin_const);
                        type_s = recv_str();
                        type = toInt(type_s, 0, page);
                        if (type == -1) continue;
                        if (type == 0) {
                            send_cl("system(\"CLS\")");
                            return;
                        }
                        break;
                    }
                    send_cl("system(\"CLS\")");
                    ord.getMeat_o(meats[type-1]);
                }
                else if (operation == 2) {
                    send_cl("system(\"CLS\")");
                    ord.meatPutData();
                }
                send_cl("system(\"CLS\")");
                ord.putData();
                send_cl("system(\"CLS\")");
                ord.order::putData();
                break;
            }
            ofstream fout("order_history.txt", ios_base::app);
            ord.getFile(fout);
            fout.close();
        }
        else {
            exprt ord;
            while (true) {
                send_cl("system(\"CLS\")");
                ifstream fin("meat.txt");
                string type_s;
                int type;
                int page = 0;
                meat empt;
                vector<meat> meats;
                meats.push_back(empt);
                while (meats[page].putFile(fin)) {
                    page++;
                    /*send_cl("    | Товар №");
                    send_cl(to_string(page));
                    send_cl(" |\n\n");
                    meats[page-1].getData();*/
                    meats.push_back(empt);
                }
                fin.close();
                while (true) {
                    for (int i = 0; i < page; i++) {
                        send_cl("    | Товар №");
                        send_cl(to_string(i + 1));
                        send_cl(" |\n\n");
                        meats[i].getData();
                    }
                    send_cl("\n\nВведите номер товара который хотите заказать(если вы хотите вернуться в меню, введите 0): ");
                    send_cl(cin_const);
                    type_s = recv_str();
                    type = toInt(type_s, 0, page);
                    if (type == -1) continue;
                    if (type == 0) {
                        send_cl("system(\"CLS\")");
                        return;
                    }
                    break;
                }
                send_cl("system(\"CLS\")");
                ord.getMeat_o(meats[type - 1]);
                send_cl("system(\"CLS\")");
                ord.putData();
                send_cl("system(\"CLS\")");
                ord.order::putData();
                break;
            }
            ofstream fout("order_history.txt", ios_base::app);
            ord.getFile(fout);
            fout.close();
        }
        send_cl("system(\"CLS\")");
        send_cl("Заказ успешно оформлен!\n\n");
        send_cl("system(\"pause\")");
        send_cl("system(\"CLS\")");
    }
    void order_show() {
        ifstream fin("order_history.txt");
        send_cl("system(\"CLS\")");
        string type;
        while (getline(fin, type)) {
            if (type == "export") {
                exprt ord;
                if (!ord.putFile(fin)) break;
                send_cl("\n\nЗаказ на экспорт\n");
                ord.getData();
            }
            else if (type == "import") {
                imprt ord;
                if (!ord.putFile(fin)) break;
                send_cl("\n\nЗаказ на импорт\n");
                ord.getData();
            }
            else break;
        }
        send_cl("system(\"pause\")");
        send_cl("system(\"CLS\")");
    }
    //void show_cl();
    //void find_cl();
    //void filter_cl();
    //void sort_cl();
    //void add_cl();
    //void del_cl();
    //void update_cl();

    admin(string login, string password) : user(login, password) {}
};

class aim {
public:
    string description;
    double mark[100], sum;
    int count;
};

class expert : protected user {
    bool isVoted = false;
public:
    void menu() {
        send_cl("system(\"CLS\")");
        string trash;
        int operation;
        string login, password;
        ifstream fin("votedexperts.txt");
        while (fin >> login >> password) {
            if (login == this->login && password == this->password) {
                isVoted = true;
                break;
            }
        }
        fin.close();
        while (true) {
            send_cl("Добро пожаловать в меню эксперта\n\n");
            send_cl("1. Просмотр данных\n2. Поиск записи по заданному параметру\n3. Сортировка записей\n4. Фильтрация записей по некоторым параметрам\n5. Оценка целей\n6. Получить последний отчет по целям\n7. Просмотр истории заказов\n0. Выход из меню\n\nВведите номер выбранной операции, одной цифрой и без пробелов: ");
            send_cl(cin_const);
            trash = recv_str();
            operation = toInt(trash, 0, 7);
            if (operation == -1) continue;
            if (operation == 0) return;
            if (operation == 1) getTableData();
            else if (operation == 2) find_d();
            else if (operation == 3) sort_d();
            else if (operation == 4) filter_d();
            else if (operation == 5) vote();
            else if (operation == 6) copy_report();
            else if (operation == 7) order_show();
        }
    }
    void vote() {
        send_cl("system(\"CLS\")");
        if (isVoted) {
            send_cl("Вы уже голосовали...");
            send_cl("system(\"pause\")");
            return;
        }
        ifstream fin("aims.txt");
        ofstream fout("buffer.txt");
        aim aim;
        string trash;
        double mark;
        while (getline(fin, aim.description)) {
            if (aim.description == "") break;
            fin >> aim.count;
            aim.sum = 0;
            for (int i = 0; i < aim.count; i++) {
                fin >> aim.mark[i];
                aim.sum += aim.mark[i];
            }
            send_cl("system(\"CLS\")");
            while (true) {
                send_cl("Цель: ");
                send_cl(aim.description.c_str());
                send_cl("\nСредняя оценка цели: ");
                if (aim.count == 0) send_cl("-");
                else {
                    char* trash2 = NULL;
                    send_cl(to_string(aim.sum / double(aim.count)));
                }
                send_cl("\n\nВведите свою оценку от 1 до 10 данной цели(если вы хотите отменить оценивание и вернуться в меню введите один символ - 0): ");
                send_cl(cin_const);
                trash = recv_str();
                mark = toDouble(trash, 0, 10);
                if (mark == -1) continue;
                if (mark == 0) {
                    fin.close();
                    fout.close();
                    return;
                }
                break;
            }
            aim.mark[aim.count] = mark;
            fout << aim.description << "\n";
            fout << aim.count + 1 << "\n";
            for (int i = 0; i < aim.count + 1; i++)
                fout << aim.mark[i] << "\n";
            fin.ignore(1);
        }
        fin.close();
        fout.close();
        fout.open("aims.txt");
        fin.open("buffer.txt");
        while (getline(fin, aim.description)) {
            if (aim.description == "") break;
            fin >> aim.count;
            for (int i = 0; i < aim.count; i++) {
                fin >> aim.mark[i];
            }
            fout << aim.description << "\n";
            fout << aim.count << "\n";
            for (int i = 0; i < aim.count; i++)
                fout << aim.mark[i] << "\n";
            fin.ignore(1);
        }
        fin.close();
        fout.close();
        fout.open("votedexperts.txt", ios_base::app);
        fout << this->login << "\n" << this->password << "\n";
        fout.close();
        int count_ex;
        fin.open("countofexperts.txt");
        fin >> count_ex;
        fin.close();
        if (aim.count == count_ex) {
            double all_sum = 0, wght = 0;
            string mx_desc = "";
            fin.open("aims.txt");
            fout.open("aim_report.txt");
            //fout << "Отчет по целям\n\n";
            while (getline(fin, aim.description)) {
                
                if (aim.description == "") break;
                fin >> aim.count;
                for (int i = 0; i < aim.count; i++) {
                    fin >> aim.mark[i];
                    all_sum += aim.mark[i];
                }
                //fout << "Цель: " << aim.description << "\n";
                //fout << "Средняя оценка " << aim.sum / double(aim.count) << "\n" << "Проголосовало " << aim.count << " экспертов\n" << "Вес цели " << wght << "\n\n";
                fin.ignore(1);
            }
            fin.close();
            fin.open("aims.txt");
            while (getline(fin, aim.description)) {
                if (aim.description == "") break;
                fin >> aim.count;
                aim.sum = 0;
                for (int i = 0; i < aim.count; i++) {
                    fin >> aim.mark[i];
                    aim.sum += aim.mark[i];
                }
                fout << "Цель: " << aim.description << "\n";
                fout << "Средняя оценка " << aim.sum / double(aim.count) << "\n" << "Проголосовало " << aim.count << " экспертов\n" << "Вес цели " << aim.sum / all_sum << "\n\n";
                if ((aim.sum / all_sum) > wght) {
                    wght = aim.sum / all_sum;
                    mx_desc = aim.description;
                }
                fin.ignore(1);
            }
            fout << "\n\nЛучшая цель по методу эскпертного ранга - " << mx_desc << "\n\n";
            fout.close();
            fin.close();
        }
        isVoted = true;
        send_cl("system(\"CLS\")");
    }
    void order_show() {
        ifstream fin("order_history.txt");
        send_cl("system(\"CLS\")");
        string type;
        while (getline(fin, type)) {
            if (type == "export") {
                exprt ord;
                if (!ord.putFile(fin)) break;
                send_cl("\n\nЗаказ на экспорт\n");
                ord.getData();
            }
            else if (type == "import") {
                imprt ord;
                if (!ord.putFile(fin)) break;
                send_cl("\n\nЗаказ на импорт\n");
                ord.getData();
            }
            else break;
        }
        send_cl("system(\"pause\")");
        send_cl("system(\"CLS\")");
    }
    expert(string login, string password) : user(login, password) {}
};

void sign_up() {
    send_cl("system(\"CLS\")");
    send_cl("Меню регистрации пользователя:\n\n");
    user reg;
    if (reg.log_check() != "error") {
        send_cl("system(\"CLS\")");
        send_cl("Ошибка! Данный аккаунт уже зарегистрирован.\n\n\n");
        send_cl("system(\"pause\")");
        send_cl("system(\"CLS\")");
        return;
    }
    ofstream fout("users.txt", ios_base::app);
    fout << reg.getData("login") << endl << cypher(reg.getData("password"), 1) << endl;
    send_cl("system(\"CLS\")");
    send_cl("Аккаунт успешно зарегистрирован\n");
    send_cl("system(\"pause\")");
    send_cl("system(\"CLS\")");
}

void login() {
    send_cl("system(\"CLS\")");
    user log;
    send_cl("Меню входа:\n\n");
    string log_check = log.log_check();
    if (log_check == "error") {
        send_cl("system(\"CLS\")");
        send_cl("Введенных логина и пароля не существует\n\n");
        send_cl("system(\"pause\")");
        send_cl("system(\"CLS\")");
        return;
    }
    if (log_check == "admin") {
        admin acc(log.getData("login"), log.getData("password"));
        acc.menu();
    }
    else if (log_check == "expert") {
        expert acc(log.getData("login"), log.getData("password"));
        acc.menu();
    }
    else {
        user acc(log.getData("login"), log.getData("password"));
        acc.menu();
    }

}

void main_menu() {
    string trash;
    int operation;
    send_cl("system(\"CLS\")");
    while (true) {
        send_cl("ПРИВЕТСТВУЕМ ВАС В КОМПУКТЕРНОЙ ПРОГРАММЕ МЯСОКОМБИНАТА \"АЛЕШКА\" \n\n");
        send_cl("1. Вход\n2. Регистрация\n0. Выход из программы\n\nВведите номер выбранной операции, одной цифрой и без пробелов: ");
        send_cl(cin_const);
        trash = recv_str();
        operation = toInt(trash, 0, 2);
        if (operation == -1) continue;


        if (operation == 0) {
            send_cl("system(\"CLS\")");
            send_cl("РАБОТА ПРОГРАММЫ МЯСОКОМБИНАТА \"АЛЕШКА\" ЗАВЕРШЕНА\n\n");
            send_cl("endendend");
            break;
        }
        else if (operation == 1) login();
        else if (operation == 2) sign_up();

    }

}

int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    //СЕРВЕР
    //WSAStartup
    WSAData wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);
    if (WSAStartup(DLLVersion, &wsaData) != 0) {
        cout << "Ошибка соединения" << std::endl;
        exit(1);
    }
    SOCKADDR_IN addr;
    int sizeofaddr = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(1111);
    addr.sin_family = AF_INET;

    SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
    bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
    listen(sListen, SOMAXCONN);


    cout << "Сервер стартовал: " << inet_ntoa(addr.sin_addr);
    cout << ":" << addr.sin_port << "\n\n";

    while (true) {
        newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);
        char name[512];
        char ip[512];
        if (newConnection == 0) {
            cout << "Ошибка соединения #2\n";
        }
        else {
            time_t now = time(0);
            char* dt = ctime(&now);
            
            recv(newConnection, name, sizeof(name), NULL);
            cout << "Клиент " << name << " подключен! Дата и время: " << dt;
            recv(newConnection, ip, sizeof(name), NULL);
            cout << ip << ":" << addr.sin_port << "\n\n";
        }


        //Отправка сообщений send(newConnection, msg, sizeof(msg), NULL);



        //СЕРВЕР

        /*ofstream fout("aims.txt");
        fout << "Увеличение ассортимента мясной продукции\n0\nУвеличение количества заказов на экспорт\n0";
        fout.close();*/
        main_menu();
        cout << "Клиент " << name << " отключен!\n\n";
    }
}
