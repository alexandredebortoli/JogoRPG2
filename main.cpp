#include <iostream>
#include <ctime>
#include <vector>

using namespace std;

struct Arma
{
    int minDano, maxDano;
};
struct Jogador
{
    int vida;
    Arma arma;
    int pos_largura;
    int pos_altura;
};
struct Inimigo
{
    string nome;
    int vida;
    Arma arma;
};
struct Bloco
{
    bool caminho_pedra;
    bool caminho_inimigo;
    Inimigo* inimigo_bloco;
};
struct Mapa
{
    int altura;
    int largura;
    Bloco** matriz_mapa;
};
struct Fase
{
    string nome;
    Mapa mapa_fase;
    int num_inimigos;
    Inimigo* inimigos;
};


Jogador jogador()
{
    Jogador novoJogador;

    novoJogador.vida = 300;
    novoJogador.arma.minDano = 1;
    novoJogador.arma.maxDano = 20;
    novoJogador.pos_largura = 0;
    novoJogador.pos_altura = 0;

    return novoJogador;
}
void declararInimigos(Inimigo &inimigo, string nome, int vida, int minDano, int maxDano)
{
    inimigo.nome = nome;
    inimigo.vida = vida;
    inimigo.arma.minDano = minDano;
    inimigo.arma.maxDano = maxDano;
}

Inimigo* CriarInimigos()
{
    Inimigo *inimigos = new Inimigo[5];
    declararInimigos(inimigos[0], "Mandarim", 10, 2, 10);
    declararInimigos(inimigos[1], "Caveira Vermelha", 20, 2, 20);
    declararInimigos(inimigos[2], "Killmonger", 30, 2, 30);
    declararInimigos(inimigos[3], "Loki", 40, 2, 40);
    declararInimigos(inimigos[4], "Thanos", 50, 2, 50);

    return inimigos;
}

Mapa CriarMapa(int altura, int largura) {
    Mapa novo_mapa;
    novo_mapa.altura = altura;
    novo_mapa.largura = largura;
    novo_mapa.matriz_mapa = new Bloco *[novo_mapa.largura];
    for(int i = 0; i < novo_mapa.largura; i++) {
        novo_mapa.matriz_mapa[i] = new Bloco[novo_mapa.altura];
    }

    int rand_caminho;

    for(int i = 0; i < largura; i++) {
        for(int j = 0; j < altura; j++) {
            rand_caminho = rand() % 100 + 1;
            if(rand_caminho > 20) {
                novo_mapa.matriz_mapa[i][j].caminho_pedra = false;
            } else {
                if(i != 0 and j != 0)
                    novo_mapa.matriz_mapa[i][j].caminho_pedra = true;
            }
            novo_mapa.matriz_mapa[i][j].caminho_inimigo = false;
        }
    }
    return novo_mapa;
}

Fase CriarFase(int num_inimigos, Inimigo* inimigos, int altura_mapa, int largura_mapa) {
    Fase nova_fase;
    nova_fase.nome = "Avengers";
    nova_fase.mapa_fase = CriarMapa(altura_mapa, largura_mapa);
    nova_fase.num_inimigos = num_inimigos;
    nova_fase.inimigos = new Inimigo[nova_fase.num_inimigos];
    nova_fase.inimigos = inimigos;

    int rand_altura;
    int rand_largura;

    for(int i = nova_fase.num_inimigos; i > 0; i--) {
        do {
            rand_altura = rand() % nova_fase.mapa_fase.altura;
            rand_largura = rand() % nova_fase.mapa_fase.largura;
        } while (nova_fase.mapa_fase.matriz_mapa[rand_largura][rand_altura].caminho_inimigo and nova_fase.mapa_fase.matriz_mapa[rand_largura][rand_altura].caminho_pedra);

        nova_fase.mapa_fase.matriz_mapa[rand_largura][rand_altura].caminho_inimigo = true;
        nova_fase.mapa_fase.matriz_mapa[rand_largura][rand_altura].inimigo_bloco = &nova_fase.inimigos[i - 1];
    }

    return nova_fase;
}

void Movimentar(Jogador &jogador, Mapa mapa) {
    char escolha;
    cout<< "Posicao atual do jogador: x = " << jogador.pos_largura << " y = " << jogador.pos_altura << endl;
    cout<< "Mapa: x = " << mapa.largura << " y = " << mapa.altura << endl;
    cout << "W -> cima\nS -> baixo\nA -> esquerda\nD -> direita\n Escolha: ";
    cin >> escolha;
    escolha = tolower(escolha);

    switch (escolha) {
        case 'w':
            if(jogador.pos_altura !=0 && !mapa.matriz_mapa[jogador.pos_largura][jogador.pos_altura - 1].caminho_pedra){
                jogador.pos_altura--;
            }
            else{
                if(jogador.pos_altura == 0){
                    cout<< "Voce está na borda do mapa!!" << endl;
                }
                if(mapa.matriz_mapa[jogador.pos_largura][jogador.pos_altura - 1].caminho_pedra){
                    cout<< "Voce encontrou uma pedra no mapa!!" << endl;
                }
            }
            break;
        case 's':
            if(jogador.pos_altura != (mapa.altura - 1) && !mapa.matriz_mapa[jogador.pos_largura][jogador.pos_altura + 1].caminho_pedra){
                jogador.pos_altura++;
            }
            else {
                if (jogador.pos_altura == (mapa.altura - 1)) {
                    cout << "Voce está na borda do mapa!!" << endl;
                }
                if (mapa.matriz_mapa[jogador.pos_largura][jogador.pos_altura + 1].caminho_pedra) {
                    cout << "Voce encontrou uma pedra no mapa!!" << endl;
                }
            }
            break;
        case 'a':
            if(jogador.pos_largura !=0 && !mapa.matriz_mapa[jogador.pos_largura - 1][jogador.pos_altura].caminho_pedra){
                jogador.pos_largura--;
            }
            else {
                if (jogador.pos_largura == 0) {
                    cout << "Voce está na borda do mapa!!" << endl;
                }
                if (mapa.matriz_mapa[jogador.pos_largura - 1][jogador.pos_altura].caminho_pedra) {
                    cout << "Voce encontrou uma pedra no mapa!!" << endl;
                }
            }
            break;
        case 'd':
            if(jogador.pos_largura != (mapa.largura - 1) && !mapa.matriz_mapa[jogador.pos_largura + 1][jogador.pos_altura].caminho_pedra){
                jogador.pos_largura++;
            }
            else {
                if (jogador.pos_largura == (mapa.largura - 1)) {
                    cout << "Voce está na borda do mapa!!" << endl;
                }
                if (mapa.matriz_mapa[jogador.pos_largura + 1][jogador.pos_altura].caminho_pedra) {
                    cout << "Voce encontrou uma pedra no mapa!!" << endl;
                }
            }
            break;
    }
}


template<typename Tipo>
bool morreu(Tipo personagem)
{
    if(personagem.vida <= 0) {
        return true;
    }
    else {
        return false;
    }
}

template<typename Atacante, typename Vitima>
Vitima ataque(Atacante atacante, Vitima vitima)
{
    vitima.vida -= rand() % (atacante.arma.maxDano - atacante.arma.minDano) + atacante.arma.minDano;

    return vitima;
}

bool batalhar(Jogador &jogador, Fase &fase, Inimigo inimigo)
{
    cout << "\nEntrando em " << fase.nome << "...\n" << endl;
    cout << "- Jogador -\nVida: " << jogador.vida << "\nDano: " << jogador.arma.minDano << " - " << jogador.arma.maxDano << endl;
    cout << "----------------\n" << endl;
    cout << "Inimigo: " << inimigo.nome << endl;
    cout << "Vida: " << inimigo.vida << endl;
    cout << "Dano: " << inimigo.arma.minDano << " - " << inimigo.arma.maxDano<< "\n" << endl;
    while(!morreu(inimigo)) {
        jogador = ataque(inimigo, jogador);
        inimigo = ataque(jogador, inimigo);

        cout << "O jogador atacou " << inimigo.nome << " e ele ficou com " << inimigo.vida << " de vida" << endl;
        cout << "O " << inimigo.nome << " atacou ao mesmo tempo e o jogador ficou com " << jogador.vida << " de vida" << endl;

        if(morreu(inimigo))
            cout << inimigo.nome << " foi morto!\n" << endl;
        if(morreu(jogador)) {
            return true;
        }
    }
    return false;
}

int main()
{
    srand(time(NULL));
    Jogador novoJogador;
    novoJogador = jogador();
    Fase novaFase = CriarFase(5, CriarInimigos(), 5, 10);
    bool jogadorPerdeu = false;
    while(!jogadorPerdeu){
        if(novaFase.mapa_fase.matriz_mapa[novoJogador.pos_largura][novoJogador.pos_altura].caminho_inimigo) {
            jogadorPerdeu = batalhar(novoJogador, novaFase, *novaFase.mapa_fase.matriz_mapa[novoJogador.pos_largura][novoJogador.pos_altura].inimigo_bloco);
        }
        Movimentar(novoJogador, novaFase.mapa_fase);
    }
}