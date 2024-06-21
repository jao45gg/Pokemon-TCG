#ifndef _CARTAS_CPP
#define _CARTAS_CPP

#include "../include/Cartas.hpp"
#include <iostream>

using namespace std;

Cartas::Cartas()
{
    this->_hp = 0;
    this->_defesa = 0;
    this->_nome_pokemon = "";
    this->_qtnd_atks = 0;
    vector<pair<string, int>> vazio;
    vazio.clear();
    this->_ataque = vazio;
}

Cartas::Cartas(string nome, int qtnd_atks, vector<pair<string, int>> ataque, int defesa, string tipo, int hp)
{
    try
    {
        _nome_pokemon = nome;
        _qtnd_atks = qtnd_atks;
        _ataque.clear();

        for (int i = 0; i < qtnd_atks; i++)
        {
            if (ataque[i].second >= 0 && ataque[i].second <= 400)
            {
                _ataque.push_back(ataque[i]);
            }
            else if (ataque[i].second < 0)
            {
                pair<string, int> aux = ataque[i];
                aux.second = 0;
                _ataque.push_back(aux);
            }
            else if (ataque[i].second > 400)
            {
                pair<string, int> aux = ataque[i];
                aux.second = 400;
                _ataque.push_back(aux);
            }
        }

        _defesa = defesa;
        _tipo = tipo;
        _hp = hp;
    }
    catch (const std::exception &e)
    {
        cerr << "Erro ao construir carta: " << e.what() << endl;
        // Pode adicionar outras ações aqui, se necessário
    }
}

Cartas::~Cartas()
{
    _nome_pokemon = "";
    _defesa = 0;
    _tipo = "";
    _hp = 0;
    _qtnd_atks = 0;
}

string Cartas::getNome()
{
    return _nome_pokemon;
}

vector<pair<string, int>> Cartas::getAtaques()
{
    return _ataque;
}

pair<string, int> Cartas::getAtaque(int seleciona_atks)
{
    try
    {
        if (seleciona_atks >= 0 && seleciona_atks < _qtnd_atks)
        {
            return (_ataque.at(seleciona_atks));
        }
        else
        {
            throw out_of_range("Indice fora dos limites no método getAtaque");
        }
    }
    catch (const std::exception &e)
    {
        cerr << "Erro ao acessar ataque: " << e.what() << endl;
        return pair<string, int>{"vazio", 0};
    }
}

int Cartas::getDefesa()
{
    return _defesa;
}

string Cartas::getTipo()
{
    return _tipo;
}

int Cartas::getHp()
{
    return _hp;
}

void Cartas::sofrerDano(int dano)
{
    try
    {
        _hp -= dano;
        cout << "--> " << "  Vida depois do ataque: " << _hp << endl
             << endl;
    }
    catch (const std::exception &e)
    {
        cerr << "Erro ao sofrer dano: " << e.what() << endl;
    }
}

void Cartas::mostraCarta()
{
    cout << "Pokemon " << _nome_pokemon << endl;
    cout << "Ataque " << _ataque.at(0).first << " tem dano " << _ataque.at(0).second << endl;
    cout << "Defesa " << _defesa << endl;
    cout << "Tipo " << _tipo << endl;
    cout << "Vida " << _hp << endl;
}

void Cartas::destroiCarta()
{
    _hp = 0;
    _defesa = 0;
    _nome_pokemon = "";
    _qtnd_atks = 0;
    vector<pair<string, int>> vazio;
    vazio.clear();
    _ataque = vazio;
}

#endif
