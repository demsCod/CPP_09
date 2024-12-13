#pragma once

/*
Chapter IV
Exercice 00: Bitcoin Exchange
Exercise : 00
Bitcoin Exchange
Turn-in directory : ex00/
Files to turn in : Makefile, main.cpp, BitcoinExchange.{cpp, hpp}
Forbidden functions : None
Vous devez créer un programme qui affiche la valeur d’une certaine quantité de bitcoins
à une certaine date.
Ce programme doit utiliser une base de données au format CSV qui représentera le
prix du bitcoin au fil du temps. Cette base de données est fournie avec le sujet.
Le programme prendra en entrée une deuxième base de données stockant les différents
prix / dates à évaluer.
Votre programme doit respecter ces règles:
• Le nom du programme est btc.
• Votre programme doit prendre un fichier en argument.
• Chaque ligne de ce fichier doit utiliser le format suivant: "date | valeur".
• Une date valide sera toujours au format "Année-Mois-Jour" (YYYY-MM-DD).
• Une valeur valide doit être soit un nombre à virgule flottante (float), ou un entier
positif, compris entre 0 et 1000.
*/
#include <map>
#include <string>
#include <fstream>
#include <iostream>
class BitcoinExchange
{

    private :
        std::map<std::string, float> database;
        void parseInput(std::fstream& fs);
        std::fstream fs;
        std::string buffer;
    public :
        BitcoinExchange(std::string input);
        void DisplayValue();

   
};