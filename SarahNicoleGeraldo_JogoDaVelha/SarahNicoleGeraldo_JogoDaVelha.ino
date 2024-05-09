// variáveis globais
int velha = 1;
int linha;
int coluna;
bool haVencedor = false;
int tabuleiro[3][3] = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } };
String jogador1 = "Jogador 1";
String jogador2 = "Jogador 2";
int JogadorDaVez = 1;
String jogada = "";

// validar as jogadas
bool validaJogada(int linha, int coluna) {
  if (linha == 0 || linha == 1 || linha == 2) {
    if (coluna == 0 || coluna == 1 || coluna == 2) {
      return true;
    }
  }
  return false;
}

// validar as posições
bool validaPosicao(int tabuleiro[3][3], int linha, int coluna) {
  if (tabuleiro[linha][coluna] == 0) {
    return true;
  } else {
    return false;
  }
}

void setup() {
  Serial.begin(9600);

// limpar o tabuleiro
  for (int linha = 0; linha <= 2; linha++) {
    for (int coluna = 0; coluna <= 2; coluna++) {
      tabuleiro[linha][coluna] = 0;
    }
  }

  for (int linha = 0; linha <= 2; linha++) {
    if (linha == 1 || linha == 2) {
      Serial.println("");
    }
    for (int coluna = 0; coluna <= 2; coluna++) {
      Serial.print(tabuleiro[linha][coluna]);
    }
  }

  Serial.println("");
  Serial.print("Digite sua jogada jogador");
  Serial.print(JogadorDaVez);
  Serial.println("");
}

// reiniciar o jogo
void reiniciar(int tabuleiro[3][3], int JogadorDaVez, int velha, bool haVencedor) {
  
  JogadorDaVez= 1;
  velha= 1;
  haVencedor= false;
  for (int linha = 0; linha <= 2; linha++) {
    for (int coluna = 0; coluna <= 2; coluna++) {
      tabuleiro[linha][coluna] = 0;
    }
  }
}

// limpar o tabuleiro para um novo jogo
void imprimir (int tabuleiro [3][3]) {

  for (int linha = 0; linha <= 2; linha++) {
    if (linha == 1 || linha == 2) {
      Serial.println("");
    }
    for (int coluna = 0; coluna <= 2; coluna++) {
      Serial.print(tabuleiro[linha][coluna]);
    }
  }

  Serial.println("");
  Serial.print("Digite sua jogada jogador");
  Serial.print(JogadorDaVez);
  Serial.println("");
}

void loop() {
    
    do{
      
      // ler as jogadas
      while(!Serial.available());
      
      // passar as strings para valores inteiros
      jogada = Serial.readString();
    linha = jogada.substring(0, 1).toInt();
    coluna = jogada.substring(2, 3).toInt();


    if (validaJogada(linha, coluna)) {
      if (validaPosicao(tabuleiro, linha, coluna)) {
       
        // verificar se há vencedor na linha, coluna ou diagonal
        if((tabuleiro[0][0]==JogadorDaVez && tabuleiro[0][1]==JogadorDaVez && tabuleiro[0][2]==JogadorDaVez) ||
(tabuleiro[1][0]==JogadorDaVez && tabuleiro[1][1]==JogadorDaVez && tabuleiro[1][2]==JogadorDaVez) ||
(tabuleiro[2][0]==JogadorDaVez && tabuleiro[2][1]==JogadorDaVez && tabuleiro[2][2]==JogadorDaVez)){
	haVencedor = true;
}else if((tabuleiro[0][0]==JogadorDaVez && tabuleiro[1][0]==JogadorDaVez && tabuleiro[2][0]==JogadorDaVez) ||
(tabuleiro[0][1]==JogadorDaVez && tabuleiro[1][1]==JogadorDaVez && tabuleiro[2][1]==JogadorDaVez) ||
(tabuleiro[0][2]==JogadorDaVez && tabuleiro[1][2]==JogadorDaVez && tabuleiro[2][2]==JogadorDaVez)){
	haVencedor = true;
}else if((tabuleiro[0][0]==JogadorDaVez && tabuleiro[1][1]==JogadorDaVez && tabuleiro[1][2]==JogadorDaVez) ||
(tabuleiro[0][2]==JogadorDaVez && tabuleiro[1][1]==JogadorDaVez && tabuleiro[2][0]==JogadorDaVez)){
	haVencedor = true;
}else{
	 tabuleiro[linha][coluna] = JogadorDaVez;

          // mudar os jogadores ao final de cada jogada
        if (JogadorDaVez == 1) {
          JogadorDaVez = 2;
        } else {
          JogadorDaVez = 1;
        }


          // mostrar as jogadas
        for (int linha = 0; linha <= 2; linha++) {
          if (linha == 1 || linha == 2) {
            Serial.println("");
          }
          for (int coluna = 0; coluna <= 2; coluna++) {
            Serial.print(tabuleiro[linha][coluna]);
          }
        }
		
          // pedir a jogada ao jogador da vez
        velha = velha + 1;
        Serial.println("");
        Serial.print("Digite sua jogada jogador");
        Serial.println(JogadorDaVez);
}
        
        
        // ler posições inválidas
      } else {
        Serial.println("Posicao invalida.");
        Serial.println("");
        Serial.print("Digite sua jogada novamente jogador");
        Serial.println(JogadorDaVez);
      }


    // ler jogadas inválidas
    } else {
      Serial.println("Jogada invalida.");
      Serial.println("");
      Serial.print("Digite sua jogada novamente jogador");
      Serial.println(JogadorDaVez);
    }
    
    }while( !haVencedor && velha <= 9 );
    
  // se houver vencedor ou empate reiniciar o jogo e o tabuleiro
  if(haVencedor){
    Serial.print("Parabens pela vitoria, jogador");
    reiniciar(tabuleiro, JogadorDaVez, velha, haVencedor);
    imprimir(tabuleiro);
    Serial.println(JogadorDaVez);
  }else{
  	Serial.println("Deu velha!!!");
    reiniciar(tabuleiro, JogadorDaVez, velha, haVencedor);
    imprimir(tabuleiro);
  }
}