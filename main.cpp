#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <bits/stdc++.h>

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


//Tässä demossa määritellään sattumanvaraiset pisteet jokaiselle kokelaalle i kokeeseen j. 
//Tähän voitaisiin myös koodata input-funktio, mutta käytetään mieluummin sattumanvaraisia tuloksia, sillä oikeaa raakaa dataa ei kuitenkaan saada
int main()
{
    srand(time(0));                       //Siemen random funktiolle
    vector<vector<int>> x;                //Koematriisi IxJ (int)
    vector<vector<double>> x_converted;   //Koematriisi IxJ (double)
    vector<double> sd;                    //Keskihajontavektori J
    vector<double> mean;                  //Keskiarvovektori J
    vector<double> z_average;             //SYK-pistevektori
    vector<double> syk_arvosanarajat;     //Rajavektori, joka määrää syk-arosanan 
    vector<int> syk_i_rajat;              //
    vector<double> rajat{1, 0.95, 0.8, 0.6, 0.4, 0.2, 0.05, 0};
    vector<char> arvosanalista{'L', 'E', 'M', 'C', 'B', 'A', 'I'};
    vector<char> syk_arvosanat;
    int I, J;
    cin >> I >> J;                        //Määritellään I (kokelaiden määrä) ja J (kokeiden määrä)
  
    for(int i = 0; i < I; i++){           //Iteroidaan sattumanvaraiset arvot koematriisille IxJ
        vector<int> v1;                    
        for(int j = 0; j < J; j++){
            v1.push_back(rand() % 121);
        }
        x.push_back(v1);
    }
  
    for(int j = 0; j < J; j++){           //Määritetään keskiarvovektori sekä keskihajontavektori
        mean.push_back(x_mean(j, I, x));
        sd.push_back(s(j, I, x));
    }
    
    for(int i = 0; i < I; i++){           //Muunnetaan koematriisi (int) IxJ --> koematriisi (double) IxJ
        vector<double> v1(x[i].begin(), x[i].end());
        x_converted.push_back(v1);
    }
  
    vector<vector<double>> z = z_norm(x_converted, sd, mean, I, J);     //Normitetaan koepistematriisi IxJ
  
    for(int i = 0; i < I; i++){                                         //Muodostetaan SYK-pistevektori
        z_average.push_back(z_averages(i, J, z, x));
    }
  
    vector<double> z_jarjestetty = z_average;           //SYK-pisterajoja varten modostetaan väliaikainen vektori, joka järjestetään SYK-pisteiden mukaan
  
    sort(z_jarjestetty.begin(), z_jarjestetty.end());   //Järjestetään väliaikainen vektori (pienemmästä suurimpaan)
  
    for(int n = 7; n >= 0; n--){                        //Määritetään kokelaat, jotka ovat arvosanojen rajapinnoilla
        syk_i_rajat.push_back(round(rajat[n] * I));
    }
  
    syk_arvosanarajat.push_back(z_jarjestetty[I-1]);    //Määritetään suurin SYK-pistemäärä
  
    for(int n = 6; n >= 0; n--){                        //Määritetään varsinaiset SYK-rajat
        syk_arvosanarajat.push_back(z_jarjestetty[syk_i_rajat[n]]);
    }
    
    for(int i = 0; i < I; i++){                         //Määritetään kokelaille SYK-arvosanat
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
  
    for(int i = 0; i < I; i++){
        cout << i << " " << z_average[i] << " " << syk_arvosanat[i] << "\n";
    }
  
    return 0;
}
