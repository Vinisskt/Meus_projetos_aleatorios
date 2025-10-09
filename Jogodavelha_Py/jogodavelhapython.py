import libraryjogodavelha

def main():
  
  # tabuleiro visual e casas
  posicoes = [1,2,3,4,5,6,7,8,9]
  tabuleiro = [" "] * len(posicoes)
  
  # pontos dos jogadores
  ponto_x = [0,0,0]
  ponto_o = [0,0,0]
  
  print("bem vindo ao jogo da velha")
  
  libraryjogodavelha.exibirTabuleiroPosicoes()
  
  while True:
    
    # jogador X

    libraryjogodavelha.jogada("X",tabuleiro,posicoes)
    
    libraryjogodavelha.exibirTabuleiro(tabuleiro)
    
    ponto_x[0] = libraryjogodavelha.verificarLinha(tabuleiro,"X")
    ponto_x[1] = libraryjogodavelha.verificarColuna(tabuleiro, "X")
    ponto_x[2] = libraryjogodavelha.verificarDiagonais(tabuleiro, "X")
    
    # limpar terminal.
    libraryjogodavelha.limparTerminal()
    # exibir posicoes
    libraryjogodavelha.exibirTabuleiroPosicoes()
    
    # verificacao ponto X
    if 1 in ponto_x:
      print("parabens X")
      libraryjogodavelha.exibirTabuleiro(tabuleiro)
      break
    
    if " " not in tabuleiro:
      print("empate")
      break
      
    
    # jogador O
    libraryjogodavelha.jogada("O", tabuleiro, posicoes)
    libraryjogodavelha.exibirTabuleiro(tabuleiro)
    ponto_o[0] = libraryjogodavelha.verificarLinha(tabuleiro, "O")
    ponto_o[1] = libraryjogodavelha.verificarColuna(tabuleiro, "O")
    ponto_o[2] = libraryjogodavelha.verificarDiagonais(tabuleiro, "O")
    
    # limpar terminal
    libraryjogodavelha.limparTerminal()
    # exibir posicoes
    libraryjogodavelha.exibirTabuleiroPosicoes()
    
    # verificacao ponto O
    if 1 in ponto_o:
      print("parabens O")
      libraryjogodavelha.exibirTabuleiro(tabuleiro)
      break
    
    if " " not in tabuleiro:
      print("empate")
      break


if __name__ == "__main__":
  main()

  
  
