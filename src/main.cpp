#include "../include/Partida.hpp"
#include "../include/Usuario.hpp"
#include "../include/Cartas.hpp"
#include "../include/Baralho.hpp"
#include "../third_party/color.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <exception>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

struct ScoreEntry
{
    std::string name;
    int score;
};

vector<ScoreEntry> readScores(const string &filename)
{
    vector<ScoreEntry> scores;
    ifstream inFile(filename);

    if (!inFile)
    {
        cerr << "Erro ao abrir o arquivo: " << filename << endl;
        return scores;
    }

    string line;
    while (getline(inFile, line))
    {
        if (line.empty())
            continue;

        size_t lastSpacePos = line.find_last_of(" \t");

        if (lastSpacePos == string::npos)
        {
            cerr << "Formato inválido da linha no arquivo: " << filename << endl;
            continue;
        }

        string name = line.substr(0, lastSpacePos);
        string scoreStr = line.substr(lastSpacePos + 1);

        int score;
        try
        {
            score = stoi(scoreStr);
        }
        catch (const std::invalid_argument &e)
        {
            cerr << "Erro ao converter pontuação para inteiro para o jogador: " << name << endl;
            continue;
        }
        catch (const std::out_of_range &e)
        {
            cerr << "Pontuação do jogador está fora do intervalo suportado: " << name << endl;
            continue;
        }

        scores.push_back({name, score});
    }

    inFile.close();

    // Sort scores in descending order
    sort(scores.begin(), scores.end(), [](const ScoreEntry &a, const ScoreEntry &b)
         { return a.score > b.score; });

    return scores;
}

void writeScores(const vector<ScoreEntry> &scores, const string &filename)
{
    ofstream outFile(filename);

    if (!outFile)
    {
        cerr << "Erro ao abrir o arquivo para escrita: " << filename << endl;
        return;
    }

    for (const auto &entry : scores)
    {
        outFile << entry.name << " " << entry.score << endl;
    }

    outFile.close();
}

void updateScores(vector<ScoreEntry> &scores, const string &playerName)
{
    bool playerExists = false;

    // Check if player is already in the list
    for (auto &entry : scores)
    {
        if (entry.name == playerName)
        {
            entry.score += 1; // Increment the score by 1
            playerExists = true;
            break;
        }
    }

    // If player is not in the list, add them with score 1
    if (!playerExists)
    {
        scores.push_back({playerName, 1});
    }

    // Sort scores in descending order
    sort(scores.begin(), scores.end(), [](const ScoreEntry &a, const ScoreEntry &b)
         {
             return a.score > b.score; // Sort in descending order by score
         });
}

int main()
{

    std::string systemClear = "";

#ifdef _WIN32
    systemClear = "cls";
#else
    systemClear = "clear";
#endif

    const char *clearCommand = systemClear.c_str();

    cout << dye::yellow_on_black(" _____     _                        _____ _____ _____ ") << endl;
    cout << dye::yellow_on_black("|  _  |___| |_ ___ _____ ___ ___   |_   _|     |   __|") << endl;
    cout << dye::yellow_on_black("|   __| . | '_| -_|     | . |   |    | | |   --|  |  |") << endl;
    cout << dye::yellow_on_black("|__|  |___|_,_|___|_|_|_|___|_|_|    |_| |_____|_____|") << endl;
    cout << endl;

    string filename = "./src/scores.txt";

    vector<ScoreEntry> scores = readScores(filename);

    if (!scores.empty())
    {
        cout << "----------------------------------------------------------" << endl
             << endl;
        cout << "Top Scores:" << endl
             << endl;

        for (const auto &entry : scores)
        {
            cout << entry.name << " " << entry.score << endl
                 << endl;
        }

        cout << "----------------------------------------------------------" << endl
             << endl;
    }
    else
    {
        cout << "----------------------------------------------------------" << endl
             << endl;
        std::cout << "Ainda não temos um top 3, seja o primeiro na lista !" << std::endl
                  << endl;
        cout << "----------------------------------------------------------" << endl
             << endl;
    }

    int comando;
    int comandoAux;
    string nomePersonagem;

    do
    {
        cout << dye::white_on_green("Menu") << endl
             << endl;
        cout << "Digite '1' para Iniciar um Jogo" << endl;
        cout << "Digite '2' para Ver os Creditos" << endl;
        cout << "Digite '3' para Fechar o Jogo" << endl;
        cout << endl;

        while (true)
        {
            try
            {
                cin >> comando;

                if (comando != 1 && comando != 2 && comando != 3)
                {
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw runtime_error("Opção inválida. Digite '1', '2' ou '3' para realizar uma ação!");
                }

                std::cout << std::endl;

                break;
            }
            catch (const std::exception &e)
            {
                std::cerr << endl
                          << e.what() << std::endl
                          << endl;
            }
        }

        if (comando == 1)
        {
            system(clearCommand);

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Digite o nome do seu personagem:" << endl;
            cout
                << endl;

            getline(cin, nomePersonagem);

            cout
                << endl;
            Usuario jogador = Usuario(nomePersonagem);
            Usuario Bot = Usuario("Bot");

            string nomeBaralhoJogador;
            nomeBaralhoJogador = jogador.getNomeBaralho(0);

            Partida Jogo = Partida(jogador, Bot, nomeBaralhoJogador, "Baralho do Bot");

            cout << endl;
            cout << "Sorteio Cara ou Coroa" << endl;

            int moeda;
            int jogadorInicia = 0;
            int vezDoJogador = 0;

            while (true)
            {
                try
                {
                    cout
                        << "Digite '1' para escolher Cara ou '2' para escolher Coroa : " << endl
                        << endl;
                    cin >> moeda;
                    cout << endl;

                    if (moeda == 1 || moeda == 2)
                    {
                        unsigned seed = time(0);
                        srand(seed);
                        int sorteio = rand() % 2;
                        sorteio++;
                        if (sorteio == 1)
                        {
                            cout << "Cara!" << endl;
                        }
                        else if (sorteio == 2)
                        {
                            cout << "Coroa!" << endl;
                        }

                        if (sorteio == moeda)
                        {
                            jogadorInicia = 1;
                            break;
                        }
                        else if (sorteio != moeda)
                        {
                            jogadorInicia = 0;
                            break;
                        }
                    }
                    else
                    {
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        throw runtime_error("Opção inválida. Digite '1' ou '2' para realizar uma ação!");
                    }

                    std::cout << std::endl;

                    break;
                }
                catch (const std::exception &e)
                {
                    std::cerr << endl
                              << e.what() << std::endl
                              << endl;
                }
            }

            system(clearCommand);

            if (jogadorInicia)
            {
                cout << endl;
                cout << nomePersonagem << dye::green_on_black(" comeca jogando!") << endl
                     << endl;
            }
            else
            {
                cout << endl;
                cout << dye::red_on_black("Bot comeca jogando!") << endl
                     << endl;
            }

            vezDoJogador = jogadorInicia;
            int primeiraRodadaJogador = 1;
            int primeiraRodadaBot = 1;
            int contagemRodadas = 1;
            int contagemPlayer = 0, contagemBot = 0;

            while (((Jogo.numPremio(nomePersonagem)) > 0) && ((Jogo.numPremio("Bot")) > 0))
            {
                cout << dye::yellow_on_black("RODADA ") << contagemRodadas << endl;
                cout << endl;

                if (vezDoJogador == 1)
                {
                    cout << "Vez de " << nomePersonagem << endl;
                    int numCarta;

                    if (Jogo.estaSemCarta(nomePersonagem))
                    {
                        if (primeiraRodadaJogador == 0)
                        {
                            cout << endl;
                            Jogo.comprarCarta(nomePersonagem);
                            cout << dye::red_on_black("Sua carta em batalha morreu, digite o numero de uma outra carta de substituicao") << endl;
                        }
                        if (primeiraRodadaJogador == 1)
                        {
                            cout << endl;
                            cout << "Digite o numero da carta que deseja enviar para batalha : " << endl;
                        }
                        cout << endl;
                        vector<Cartas> MaoJogador = Jogo.getMaoJogador(nomePersonagem);
                        for (int i = 0, ie = MaoJogador.size(); i < ie; i++)
                        {
                            cout << "   [" << i << "] " << MaoJogador.at(i).getNome();
                            cout << endl;
                        }

                        cout << endl;

                        while (true)
                        {
                            try
                            {
                                if (!(std::cin >> numCarta))
                                {
                                    std::cin.clear();
                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                    throw std::runtime_error("Numero de carta invalido, tente novamente");
                                }

                                std::cout << std::endl;

                                if (numCarta >= 0 && numCarta < (int)(MaoJogador.size()))
                                {
                                    Jogo.setCartaEmBatalha(numCarta, nomePersonagem);
                                    break;
                                }
                                else
                                {
                                    throw std::runtime_error("Numero de carta invalido, tente novamente");
                                }
                            }
                            catch (const std::exception &e)
                            {
                                std::cerr << endl
                                          << e.what() << std::endl
                                          << endl;
                            }
                        }
                    }
                    else if (Jogo.estaSemCarta("Bot"))
                    {
                        // break;
                    }
                    else if (!(Jogo.estaSemCarta("Bot")) && !(Jogo.estaSemCarta(nomePersonagem)))
                    {
                        if (primeiraRodadaBot == 1 || primeiraRodadaJogador == 1)
                        {
                            cout << "Primeira rodada, nao ha movimentos" << endl
                                 << endl;
                        }
                        else if (primeiraRodadaJogador == 0 && primeiraRodadaBot == 0)
                        {
                            Jogo.comprarCarta(nomePersonagem);

                            if (Jogo.estaSemCarta(nomePersonagem))
                            {
                                cout << "o ponteiro da carta em batalha ficou nulo o" << endl;
                            }

                            Jogo.Ataque(nomePersonagem, "Bot");
                            if (Jogo.cartaMorta("Bot"))
                            {
                                Jogo.matarCarta("Bot");
                                cout << nomePersonagem << " derrotou o Pokemon em batalha do Bot" << endl;
                                Jogo.ganharPremio(nomePersonagem);
                            }
                        }
                    }
                    vezDoJogador = 0;
                    primeiraRodadaJogador = 0;
                    contagemPlayer = 1;
                }
                else if (vezDoJogador == 0)
                {
                    cout << "Vez do Bot" << endl;
                    cout << endl;

                    if (Jogo.estaSemCarta("Bot"))
                    {
                        cout << endl;
                        vector<Cartas> MaoBot = Jogo.getMaoJogador("Bot");
                        unsigned seed = time(0);
                        srand(seed);
                        Jogo.comprarCarta("Bot");
                        int cartaEscolhidaBot = rand() % MaoBot.size();
                        Jogo.setCartaEmBatalha(cartaEscolhidaBot, "Bot");
                        if (!primeiraRodadaBot)
                        {
                            Jogo.Ataque("Bot", nomePersonagem);
                            if (Jogo.cartaMorta(nomePersonagem))
                            {
                                Jogo.matarCarta(nomePersonagem);
                                cout << "Bot derrotou o Pokemon em batalha de " << nomePersonagem << endl;
                                Jogo.ganharPremio("Bot");
                            }
                        }
                    }
                    else if (!(Jogo.estaSemCarta("Bot")) && !(Jogo.estaSemCarta(nomePersonagem)))
                    {
                        if (primeiraRodadaBot == 1 || primeiraRodadaJogador == 1)
                        {
                            cout << "Primeira rodada, Bot nao realizou movimentos" << endl;
                        }
                        else if (primeiraRodadaJogador == 0 && primeiraRodadaBot == 0)
                        {
                            Jogo.comprarCarta("Bot");
                        }

                        Jogo.Ataque("Bot", nomePersonagem);
                        if (Jogo.cartaMorta(nomePersonagem))
                        {
                            Jogo.matarCarta(nomePersonagem);
                            cout << "Bot derrotou o Pokemon em batalha de " << nomePersonagem << endl;
                            Jogo.ganharPremio("Bot");
                        }
                    }
                    vezDoJogador = 1;
                    primeiraRodadaBot = 0;
                    contagemBot = 1;
                }
                if (primeiraRodadaBot == 0 && primeiraRodadaJogador == 0 && contagemPlayer == 1 && contagemBot == 1)
                {
                    contagemRodadas++;
                    contagemBot = 0;
                    contagemPlayer = 0;
                }
            }

            if (((Jogo.numPremio(nomePersonagem)) == 0) && ((Jogo.numPremio("Bot")) > 0))
            {
                updateScores(scores, nomePersonagem);
                writeScores(scores, "./src/scores.txt");

                cout << endl;
                cout << nomePersonagem << " VENCEU !!!!" << endl
                     << endl;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            if (((Jogo.numPremio("Bot")) == 0) && ((Jogo.numPremio(nomePersonagem)) > 0))
            {
                cout << endl;
                cout << "Bot VENCEU !!!!" << endl
                     << endl;
            }

            string buffer;
            cout << endl
                 << endl
                 << endl
                 << endl
                 << dye::yellow_on_black("Insira qualquer botao para continuar:") << endl;
            cin >> buffer;

            system(clearCommand);

            while (true)
            {
                try
                {
                    cout << endl;
                    cout << "Digite '1' se deseja voltar ao menu inicial" << endl;
                    cout << "Digite '2' se deseja fechar o jogo" << endl;
                    cout << endl;

                    if (!(std::cin >> comandoAux))
                    {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        throw std::runtime_error("Numero invalido, tente novamente");
                    }

                    std::cout << std::endl;

                    if (comandoAux == 1)
                    {
                        cout << "Voltando ao Menu..." << endl
                             << endl;
                        comando = 0;
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        break;
                    }
                    else if (comandoAux == 2)
                    {
                        cout << "Fechando o jogo..." << endl
                             << endl;
                        return 0;
                    }
                    else
                    {
                        throw std::runtime_error("Numero invalido, tente novamente");
                    }
                }
                catch (const std::exception &e)
                {
                    std::cerr << endl
                              << e.what() << std::endl
                              << endl;
                }
            }
        }
        else if (comando == 2)
        {
            cout << "Trabalho feito pelos alunos:" << endl
                 << endl;
            cout << "Matheus Henrique Martins Matozinho" << endl;
            cout << "Paulo Henrique Cardoso" << endl;
            cout << "Joao Pedro Souza Braga" << endl;
            cout << endl;

            while (true)
            {
                try
                {
                    cout << endl;
                    cout << "Digite '1' se deseja voltar ao menu inicial" << endl;
                    cout << "Digite '2' se deseja fechar o jogo" << endl;
                    cout << endl;

                    if (!(std::cin >> comandoAux))
                    {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        throw std::runtime_error("Numero invalido, tente novamente");
                    }

                    std::cout << std::endl;

                    if (comandoAux == 1)
                    {
                        cout << "Voltando ao Menu..." << endl
                             << endl;
                        comando = 0;
                        break;
                    }
                    else if (comandoAux == 2)
                    {
                        cout << "Fechando o jogo..." << endl
                             << endl;
                        return 0;
                    }
                    else
                    {
                        throw std::runtime_error("Numero invalido, tente novamente");
                    }
                }
                catch (const std::exception &e)
                {
                    std::cerr << endl
                              << e.what() << std::endl
                              << endl;
                }
            }
        }
        else if (comando == 3)
        {
            cout << "Fechando o jogo...";
            return 0;
        }
        else if ((comando != 1) && (comando != 2) && (comando != 3))
        {
            cout << "Comando invalido, tente novamente" << endl;
        }

    } while (comando != 3 || comandoAux != 2);

    return 0;
}
