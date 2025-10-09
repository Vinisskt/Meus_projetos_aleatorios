import json
import os
import time

def main():
    listadetarefas = lerArquivo("arquivo.json")
    while True:
        exibirinstrucoes()

        while True:
            opcoes = input("escolha oque deseja fazer\n")
            if (int(opcoes) > 0 and int(opcoes) < 7) or opcoes == "sair":
                break

        if opcoes == "1":
            listadetarefas.append(Tarefa())
            limparterminal()
        if opcoes == "2":
            alteracoes(listadetarefas, 2, status())
            limparterminal()
        if opcoes == "3":
            alteracoes(listadetarefas, 0, renomear())
            limparterminal()
        if opcoes == "4":
            alteracoes(listadetarefas, 1, renomeardescricao())
            limparterminal()
        if opcoes == "5":
            remover(listadetarefas)
            limparterminal()
        if opcoes == "6":
            limparterminal()
            exibirlista(listadetarefas)
        if opcoes == "sair":
            escreverarquivo("arquivo.json", listadetarefas)
            break
                        
def lerArquivo(file):
    listadetarefas = []
    with open(file, 'r') as arquivo:
        listadetarefas = json.load(arquivo)
        
    return listadetarefas

def escreverarquivo(file, listadetarefas):
    with open(file, 'w') as arquivo:
        json.dump(listadetarefas, arquivo)

# exibir todas as tarefas 
def exibirlista(listadetarefas):
    print("TAREFA | DESCRICAO DA TAREFA | STATUS")
    for tarefas in range(len(listadetarefas)):
        for _ in listadetarefas[tarefas]:
            print(_.strip(), end=", ")
        print("\n")

def limparterminal():
    os.system("clear")

# remover uma tarefa da lista
def remover(listadetarefas):
    nomeremover = input("nome a ser removido\n")
    for tarefas in range(len(listadetarefas)):
        if nomeremover in listadetarefas[tarefas][0]:
            listadetarefas.remove(listadetarefas[tarefas])

def renomear():
    novonome = input("novo nome para a tarefa\n")
    return novonome

def status():
    return "concluido"

def renomeardescricao():
    novadescricao = input("nova descricao para a tarefa\n")
    return novadescricao

# verifica o nome a alterar e altera usando uma funcao separada
def alteracoes(listadetarefas, indice, funcao):
    nometarefa = input("qual e a tarefa que deseja")
    for tarefas in range(len(listadetarefas)):
        if listadetarefas[tarefas][0] == nometarefa:
            listadetarefas[tarefas][indice] = funcao

# tarefa com nome e uma breve descriao inicia com nao concluido
def Tarefa():
    tarefa = []
    nometarefa = input("qual tarefa a ser realizada\n")
    descricao = input("breve descricao da tarefa\n")
    status = "nao concluido"
    tarefa.append(nometarefa)
    tarefa.append(descricao)
    tarefa.append(status)

    return tarefa

# instrucoes de uso
def exibirinstrucoes():
    print("1 para adicionar uma tarefa")
    print("2 para alterar o status para concluido")
    print("3 para renomear a tarefa")
    print("4 para renomear a descricao da tarefa")
    print("5 para remover uma tarefa da lista")
    print("6 para exibir a lista de tarefas")



if __name__ == "__main__":
    main()

