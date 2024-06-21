#ifndef _BARALHO_CPP
#define _BARALHO_CPP

#include "../include/baralho.hpp"
#include "../include/Cartas.hpp"
#include <vector>
#include <iostream>

using namespace std;

Baralho::Baralho()
{
    this->_nome = "";
    (this->_cartas).clear();
}

Baralho::Baralho(string nomeP, vector<Cartas> &cartasExistentes)
{
    this->_nome = nomeP;

    try
    {
        while (((this->_cartas).size()) <= 60)
        {
            string nomeCarta;
            cin >> nomeCarta;
            int numCartasRep = 0;
            bool existeCarta = false;
            bool adicionouCarta = false;
            bool estourouLimite = false;

            for (int j = 0, je = (cartasExistentes.size()); j < je; j++)
            {
                string procuraNome = ((cartasExistentes.at(j)).getNome());
                if (nomeCarta == procuraNome)
                {
                    for (int k = 0, ke = ((this->_cartas).size()); k < ke; k++)
                    {
                        string nomeDessaCarta = _cartas.at(k).getNome();
                        if (nomeCarta == nomeDessaCarta)
                        {
                            numCartasRep++;
                        }
                    }

                    if (numCartasRep < 4)
                    {
                        (this->_cartas).push_back(cartasExistentes.at(j));
                        existeCarta = true;
                        adicionouCarta = true;
                        break;
                    }
                    else if (numCartasRep >= 4)
                    {
                        cout << "Essa carta atingiu o limite máximo de repetições por baralho" << endl;
                        estourouLimite = true;
                        break;
                    }
                }

                if (adicionouCarta || estourouLimite)
                {
                    break;
                }
            }

            if (!existeCarta)
            {
                cout << "Não existe carta que pode ser adicionada com esse nome" << endl;
            }
        }
    }
    catch (const std::exception &e)
    {
        cerr << "Erro ao adicionar carta ao baralho: " << e.what() << endl;
    }
}

Baralho::~Baralho()
{
    (this->_cartas).clear();
    this->_nome = "";
}

string Baralho::getNome()
{
    return this->_nome;
}

vector<Cartas> Baralho::getCartasBaralho()
{
    return (this->_cartas);
}

void Baralho::setNome(string nomeP)
{
    this->_nome = nomeP;
}

Cartas Baralho::getCarta(int num)
{
    try
    {
        if (num < 0 || num >= _cartas.size())
        {
            throw out_of_range("Índice fora dos limites no método getCarta");
        }
        return (_cartas.at(num));
    }
    catch (const std::exception &e)
    {
        cerr << "Erro ao acessar carta no baralho: " << e.what() << endl;
        return Cartas(); // Retorna uma carta padrão em caso de erro
    }
}

void Baralho::removeCarta(string nome)
{
    try
    {
        bool encontrou = false;
        for (auto i = _cartas.begin(); i != _cartas.end(); ++i)
        {
            if (i->getNome() == nome)
            {
                _cartas.erase(i);
                encontrou = true;
                break;
            }
        }

        if (!encontrou)
        {
            throw invalid_argument("Carta não encontrada no baralho");
        }
    }
    catch (const std::exception &e)
    {
        cerr << "Erro ao remover carta do baralho: " << e.what() << endl;
    }
}

int Baralho::getSize()
{
    return _cartas.size();
}

void Baralho::setCartas(vector<Cartas> cartasP)
{
    this->_cartas = cartasP;
}

void Baralho::mostraBaralho()
{
    for (int i = 0; i < this->getSize(); i++)
    {
        (this->_cartas).at(i).mostraCarta();
    }
}

void Baralho::mostraNomesCartas()
{
    for (int i = 0; i < this->getSize(); i++)
    {
        cout << "   [" << i << "] " << (this->_cartas).at(i).getNome() << endl;
    }
}

#endif
