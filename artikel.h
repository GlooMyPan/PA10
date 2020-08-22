#include <iostream>
#include <string>

using namespace std ;


// Lese gesamte Textdatei in einen String und gib ihn zur?ck.
// Dabei werden Worttrennzeichen '-' ignoriert und Leerzeilen zu
// Zeilentrennern '\n'. Kann die Datei nicht ge?ffnet werden,
// wird ein leerer String zur?ck gegeben.
string leseArtikel ( char const dateiName[] ) ;

// Schreibe ganzen Artikel auf cout mit breite Zeichen, nSpalten Spalten
// und zwRaum Leerzeichen zwischen den Spalten.
// Anmerkung: artikel soll hier kopiert werden, deshalb nicht "const&"!
void schreibeArtikel ( string artikel, size_t breite, size_t nSpalten, size_t zwRaum ) ;
