//
// Created by Xuantong Pan on 2020/8/22.
// Matrikelnummer: 905896
//

#include "artikel.h"
#include <fstream>
#include <cmath> // for ceil()
#include <iomanip> // for setw()

string leseArtikel(char const dateiName[])
{
    ifstream ifs;
    ifs.open(dateiName);
    if (!ifs)
        return "";
    string rohArtikel = "", zeile;
    while (getline(ifs, zeile))
    {
        if (zeile.empty())
        {
            rohArtikel.erase(rohArtikel.find_last_not_of(' ') + 1);
            zeile = "\n\n";
        } else if (zeile.back() == '-')
            zeile.pop_back();
        else
            zeile += ' ';
        rohArtikel += zeile;
    } //end while
    ifs.close();
    return rohArtikel;
}

void schreibeArtikel(string artikel, size_t breite, size_t nSpalten, size_t zwRaum)
{
    size_t spaltenBreite = (breite - (nSpalten - 1) * zwRaum) / nSpalten;
    if (spaltenBreite < 3)
    {
        cerr << "Die Spaltenbreite ist zu klein!";
        return;
    }
    for (size_t e = spaltenBreite; e < artikel.size(); e += spaltenBreite)
    {
        size_t a = e - spaltenBreite;
        size_t i = artikel.find('\n', a);
        if (i == e)
            artikel.erase(i, 1);
        else if (i < e)
            artikel.replace(i, 1, e - i, ' ');
        else if (artikel[e] == ' ')
            artikel.erase(e, 1);
        else
        {
            i = artikel.rfind(' ', e);
            if (i >= a)
                artikel.replace(i, 1, e - i, ' ');
            else
                artikel.insert(e - 1, "-");
        }

    } // endfor

    size_t gZeilen = ceil(artikel.size() / double(spaltenBreite));
    if (artikel.size() % spaltenBreite == 0)
        ++gZeilen;
    size_t nZeilen = gZeilen / nSpalten;
    if (nZeilen % nSpalten != 0 && artikel.size() % spaltenBreite != 0)
        ++nZeilen;
    int m = 0, n = max(gZeilen, max(spaltenBreite, nZeilen));
    while (n > 0)
    {
        n /= 10;
        ++m;
    }

    cout << endl;
    cout << "Breite der Spalten = " << setw(m) << spaltenBreite << endl;
    cout << "Gesamzahl Zeilen   = " << setw(m) << gZeilen << endl;
    cout << "Laenge der Spalten = " << setw(m) << nZeilen << endl;
    cout << endl;

    for (size_t i = 0; i < nZeilen; ++i)
    {
        for (size_t j = i; j < gZeilen; j += nZeilen)
        {
            if (j > i)
                cout << string(zwRaum, ' ');
//            cout << artikel.substr(j * spaltenBreite, spaltenBreite);
            string subStr = artikel.substr(j * spaltenBreite, spaltenBreite); // subString mit Leerzeichen
            size_t nOfSubStrWithNoSpaceAtEnd = subStr.find_last_not_of(' ') + 1, nextSpace = 0;
            string subStr2 = subStr.substr(0, nOfSubStrWithNoSpaceAtEnd); // subString ohne Leerzeichen
            for (int k = 0; k < subStr.size() - nOfSubStrWithNoSpaceAtEnd; ++k)
            {
                nextSpace = subStr2.find(' ', nextSpace); // finde, wo die naechste Leerzeichen ist
                if (nextSpace == string::npos)
                    subStr2.find(' ') == string::npos ? nextSpace = 0 : nextSpace = subStr2.find(' ');
                subStr2.insert(nextSpace, " ");
                nextSpace += 2;
            }
            cout << subStr2;
        }
        cout << endl;
    }
}