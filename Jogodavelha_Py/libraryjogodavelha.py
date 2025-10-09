import os

def jogada(char, tabuleiro, posicoes):
  while True:
    try:
      jogador = int(input("escolha uma casa de 1 a 9 jogador " + char + " : -> "))
      print("\n")
    except ValueError:
      print("apenas numero de 1 a 9")
      continue
      
      
    if tabuleiro[jogador - 1] != " ":
      print("casa preenchida")
      continue
      
    for casa in range(len(tabuleiro)):
      if jogador == posicoes[casa]:
          tabuleiro[casa] = char
    
    break
      
def exibirTabuleiro(tabuleiro):
  
  for i in range(0,len(tabuleiro), 3):
    print(" | ".join(tabuleiro[i:i+3]))

def exibirTabuleiroPosicoes():
  posicoes = ["1","2","3","4","5","6","7","8","9"]
  
  print("\n")
  
  for i in range(0 ,len(posicoes), 3):
    print(" | ".join(posicoes[i:i+3]))
    
  print("\n")
  
def verificarLinha(tabuleiro, char):
  ponto = 0
  for i in [0,3,6]:
    if tabuleiro[i:i+3]:
      if tabuleiro[i] == char and tabuleiro[i + 1] == char and tabuleiro[i + 2] == char:
        ponto += 1
  return ponto
      
def verificarColuna(tabuleiro, char):
  ponto = 0
  for i in range(3):
    if tabuleiro[i] == char and tabuleiro[i+ 3] == char and tabuleiro[i+6] == char:
      ponto += 1
  return ponto

def verificarDiagonais(tabuleiro, char):
  ponto = 0
  for diagonais in [0,2]:
    if diagonais == 0:
      if tabuleiro[diagonais] == char and tabuleiro[diagonais+4] == char and tabuleiro[diagonais+8] == char:
        ponto += 1
    
    if diagonais == 2:
      if tabuleiro[diagonais] == char and tabuleiro[diagonais+2] == char and tabuleiro[diagonais+4] == char:
        ponto += 1
        
  return ponto
  
def limparTerminal():
  input("\n\npressione enter para continuar")
  os.system("clear")
