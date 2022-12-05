#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <bits/stdc++.h>
#include <string>

using namespace std;

//Aktivointifunktio
int H(int x)
{
    if(x >= 0){
        return 1;
    }
    return 0;
}

//Kokeen j osallistujamäärä
int d(int j, int I, vector<vector<int>> x)
{
    int result = 0;
    for(int i = 0; i < I; i++){
        result += H(x[i][j]);
    }
    return result;
}

//Kokeen j keskiarvo
double x_mean(int j, int I, vector<vector<int>> x)
{
    double result = 0;
    int osallistujat = d(j, I, x);
    for(int i = 0; i < I; i++){
        result += x[i][j] * H(x[i][j]);
    }
    return result/osallistujat;
}

//Kokeen J keskihajonta
double s(int j, int I, vector<vector<int>> x)
{
    double result = 0;
    int osallistujat = d(j, I, x);
    double mean = x_mean(j, I, x);
    for(int i = 0; i < I; i++){
        result += H(x[i][j]) * (x[i][j]-mean) * (x[i][j]-mean);
    }
    result = sqrt(result/osallistujat);
    return result;
}

//Kokelaan i koemäärä
int e (int i, int J, vector<vector<int>> x)
{
    int result = 0;
    for(int j = 0; j < J; j++){
        result += H(x[i][j]);
    }
    return result;
}

//Todellisten arvojen muuttaminen normitetuiksi arvoiksi
vector<vector<double>> z_norm(vector<vector<double>> x, vector<double> sd, vector<double> mean, int I, int J)
{
    vector<vector<double>> result;
    for(int i = 0; i < I; i++){
        result.push_back(x[i]);
    }
    for(int i = 0; i < I; i++){
        for(int j = 0; j < J; j++){
            result[i][j] = H(result[i][j])*(result[i][j]-mean[j])/sd[j];
        }
    }
    return result;
}

//Kokelaan i SYK-pisteet
double z_averages(int i, int J, vector<vector<double>> z, vector<vector<int>> x)
{
    double result = 0;
    for(int j = 0; j < J; j++){
        result += z[i][j];
    }
    return result/e(i, J, x);
}

//Arvosanan määrittävä funktio

char arvosanasi(int i, int j, vector<vector<int>> x, vector<vector<double>> pisterajat){
    vector<char> arvosanalista{'L', 'E', 'M', 'C', 'B', 'A', 'I'};
    for(int n = 0; n < 7; n++){
        if(x[i][j] >= pisterajat[j][n]){
            return arvosanalista[n];
        }
    }
}
void kokelaan_tulokset(vector<vector<int>> x, vector<vector<char>> arvosana, int I, int J, vector<vector<double>> pisterajat);
void tietyn_kokelaan_tulos(vector<vector<int>> x, vector<vector<char>> arvosana, int I, int J, vector<vector<double>> pisterajat);
void tuloslista(vector<vector<int>> x, vector<vector<char>> arvosana, int I, int J, vector<vector<double>> pisterajat);
void pisterajat_n(vector<vector<int>> x, vector<vector<char>> arvosana, int I, int J, vector<vector<double>> pisterajat);

void menu(vector<vector<int>> x, vector<vector<char>> arvosana, int I, int J, vector<vector<double>> pisterajat){
    string key;
    system("CLS");
    cout << "Exit (0)\nHae tietyn kokelaan tulokset (1)\nPisterajat(2)\n";
    cin >> key;
    string tmp;
    getline(cin, tmp);
    if(key == "1"){
        kokelaan_tulokset(x, arvosana, I, J, pisterajat);
    }
    if(key == "2"){
        pisterajat_n(x, arvosana, I, J, pisterajat);
    }
    if(key == "0"){
        exit;
    }
    if(key != "1" && key != "2" && key != "0"){
    menu(x, arvosana, I, J, pisterajat);
    }
}

void pisterajat_n(vector<vector<int>> x, vector<vector<char>> arvosana, int I, int J, vector<vector<double>> pisterajat){
    system("CLS");
    for(int j = 0; j < J; j++){
        for(int n = 0; n < 7; n++){
            cout << pisterajat[j][n] << " ";
        }
        cout << "\n";
    }
    system("pause");
    menu(x, arvosana, I, J, pisterajat);
}

void kokelaan_tulokset(vector<vector<int>> x, vector<vector<char>> arvosana, int I, int J, vector<vector<double>> pisterajat){
    system("CLS");
    string key;
    cout << "Takaisin (0)\nTietyn kokelaan tulos (1)\nKaikki tulokset(2)\n";
    cin >> key;
    if(key == "1"){
        tietyn_kokelaan_tulos(x, arvosana, I, J, pisterajat);
    }
    if(key == "2"){
        tuloslista(x, arvosana, I, J, pisterajat);
    }
    if(key == "0"){
        menu(x, arvosana, I, J, pisterajat);
    }
    if(key != "1" && key != "2"){
    kokelaan_tulokset(x, arvosana, I, J, pisterajat);
    }
}

void tuloslista(vector<vector<int>> x, vector<vector<char>> arvosana, int I, int J, vector<vector<double>> pisterajat){
    string tulos;
    for(int i = 0; i < I; i++){
        tulos += "Kokelas ";
        tulos += std::to_string(i);
        tulos += "; ";
        for(int j = 0; j < J; j++){
            if(x[i][j] != -1){
                tulos += "Koe ";
                tulos += std::to_string(j);
                tulos += ": ";
                tulos += std::to_string(x[i][j]);
                tulos += "--";
                tulos += arvosana[i][j];
                tulos += ". ";
            }
        }
        tulos += "\n";

    }
    system("CLS");
    cout << tulos;
    system("pause");
    kokelaan_tulokset(x, arvosana, I, J, pisterajat);
}

void tietyn_kokelaan_tulos(vector<vector<int>> x, vector<vector<char>> arvosana, int I, int J, vector<vector<double>> pisterajat){
    system("CLS");
    int i;
    cout << "Kokelaan numero: ";
    cin >> i;
    for(int j = 0; j < x[i].size(); j++){
        if(x[i][j] != -1){
            cout << "Koe " << j << ". Tulos "<< x[i][j] << "--" << arvosana[i][j] << ".\n";
        }
    }
    system("pause");
    kokelaan_tulokset(x, arvosana, I, J, pisterajat);
}

//Tässä demossa määritellään sattumanvaraiset pisteet jokaiselle kokelaalle i kokeeseen j.
//Tähän voitaisiin myös koodata input-funktio, mutta käytetään mieluummin sattumanvaraisia tuloksia, sillä oikeaa raakaa dataa ei kuitenkaan saada
int main()
{
    srand(time(0));                       //Siemen random funktiolle
    vector<vector<int>> x;                //Koematriisi IxJ (int)
    vector<vector<char>> arvosana;        //Arvosanamatriisi IxJ
    vector<vector<double>> x_converted;   //Koematriisi IxJ (double)
    vector<double> sd;                    //Keskihajontavektori J
    vector<double> mean;                  //Keskiarvovektori J
    vector<double> z_average;             //SYK-pistevektori
    vector<double> syk_arvosanarajat;     //Rajavektori, joka määrää syk-arosanan
    vector<vector<double>> pisterajat;               //Kokeen j pisterajat muodossa {L, E, M, C, B, A, I}
    vector<int> syk_i_rajat;              //
    vector<double> rajat{1, 0.95, 0.8, 0.6, 0.4, 0.2, 0.05, 0};
    vector<char> arvosanalista{'L', 'E', 'M', 'C', 'B', 'A', 'I'};
    vector<char> syk_arvosanat;
    int I, J;
    cout << "Syötä kokelaiden ja kokeiden määrä muodossa \"i [väli] j [enter]\"";
    cin >> I >> J;                        //Määritellään I (kokelaiden määrä) ja J (kokeiden määrä)

    //Täytetään koematriisi arvoilla -1
    for(int i = 0; i < I; i++){
        vector<int> v1;
        for(int j = 0; j < J; j++){
            v1.push_back(-1);
        }
        x.push_back(v1);
    }

    //Iteroidaan sattumanvaraiset arvot koematriisille IxJ
    for(int i = 0; i < I; i++){
        vector<int> v1;
        for(int j = 0; j < J; j++){
            x[i][j] = rand() % 121;
            if((rand() % J) > J/3){
                x[i][j] = -1;
            }
        }
        int temp = 0;
        for(int j = 0; j < J; j++){
                temp += x[i][j];
        }
        if(temp == -J){
                x[i][rand() % J] = rand() % 121;
        }
    }

    //Määritetään keskiarvovektori sekä keskihajontavektori
    for(int j = 0; j < J; j++){
        mean.push_back(x_mean(j, I, x));
        sd.push_back(s(j, I, x));
    }

    //Muunnetaan koematriisi (int) IxJ --> koematriisi (double) IxJ
    for(int i = 0; i < I; i++){
        vector<double> v1(x[i].begin(), x[i].end());
        x_converted.push_back(v1);
    }

    //Normitetaan koepistematriisi IxJ
    vector<vector<double>> z = z_norm(x_converted, sd, mean, I, J);

    //Muodostetaan SYK-pistevektori
    for(int i = 0; i < I; i++){
        z_average.push_back(z_averages(i, J, z, x));
    }

    //SYK-pisterajoja varten modostetaan väliaikainen vektori, joka järjestetään SYK-pisteiden mukaan
    vector<double> z_jarjestetty = z_average;

    //Järjestetään väliaikainen vektori (pienemmästä suurimpaan)
    sort(z_jarjestetty.begin(), z_jarjestetty.end());

    //Määritetään kokelaat, jotka ovat arvosanojen rajapinnoilla
    for(int n = 7; n >= 0; n--){
        syk_i_rajat.push_back(round(rajat[n] * I));
    }

    //Määritetään suurin SYK-pistemäärä
    syk_arvosanarajat.push_back(z_jarjestetty[I-1]);

    //Määritetään varsinaiset SYK-rajat
    for(int n = 6; n >= 0; n--){
        syk_arvosanarajat.push_back(z_jarjestetty[syk_i_rajat[n]]);
    }

    //Määritetään kokelaille SYK-arvosanat
    for(int i = 0; i < I; i++){
        for(int n = 0; n < 7; n++){
            if(z_average[i] == syk_arvosanarajat[0]){
                syk_arvosanat.push_back(arvosanalista[0]);
                break;
            }
            if(z_average[i] < syk_arvosanarajat[n] && z_average[i] >= syk_arvosanarajat[n+1]){
                syk_arvosanat.push_back(arvosanalista[n]);
                break;
            }
        }
    }

    //Määritetään pisterajat
    for(int j = 0; j < J; j++){
        vector<double> v1;
        vector<double> v2;
        double temp;
        vector<double> suhteelliset_kertoimet;
        for(int i = 0; i < I; i++){
            if(x[i][j] != -1){
                v1.push_back(x[i][j]);
            }
        }
        suhteelliset_kertoimet.push_back(0);
        for(int n = 0; n < 6; n++){
            double amount_of_grade = 0;
            for(int i = 0; i < I; i++){
                if(x[i][j] != -1 && syk_arvosanat[i] == arvosanalista[n]){
                    amount_of_grade++;
                }
            }
            temp = d(j, I, x);
            suhteelliset_kertoimet.push_back(amount_of_grade/temp+suhteelliset_kertoimet[n]);
        }
        sort(v1.begin(), v1.end());
        for(int n = 6; n >= 0; n--){
            v2.push_back(v1[temp*suhteelliset_kertoimet[n]]);
        }
        pisterajat.push_back(v2);
    }

    //Muodostetaan arvosanamatriisi
    for(int i = 0; i < I; i++){
        vector<char> v1;
        for(int j = 0; j < J; j++){
            if(x[i][j] == -1){
                v1.push_back('-');
            }else{
                v1.push_back(arvosanasi(i, j, x, pisterajat));
            }
        }
        arvosana.push_back(v1);
    }
    menu(x, arvosana, I, J, pisterajat);

    return 0;
}
