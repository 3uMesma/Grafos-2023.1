import numpy as np
import math
COR_BRANCO = 0
COR_CINZA = 1
COR_PRETO = 2
DIRECOES = {(0,1):'B',(1,0):'D',(0,-1):'C',(-1,0):'E'} ## Baixo, Direita, Cima, Esquerda
idx = lambda cmp,lista: lista.index(cmp) if cmp in lista else -1 ##Função de busca de um vértice em uma lista por id,[x,y]
class Vertice():
    def __init__(self,pos,id):
        self.vizinhos = [] #lista de inteiros
        self.cor=COR_BRANCO
        self.pos=np.array(pos)
        self.id=id
        self.status = {"achado":-1,"processado":-1,"antecessor":-1}
        self.distancia = -1
    def __eq__(self, other): ##Overloading de ==
        ##Uso: compara vértice==(int) id, vértice==vértice e vértice==(x,y)
        if type(other)==Vertice:
            return self.id==other.id
        elif type(other)==int:
            return self.id==other
        elif type(other)==tuple or type(other)==np.ndarray or type(other)==list:
            return (self.pos==np.array(other)).all()
        return False
    def __str__(self):
        return str("id:{0} {5} ({1},{2},{3}) --> {4}".format(self.id,self.status["achado"],self.status["processado"],self.status["antecessor"],self.vizinhos,self.pos))
    def __add__(self, other): ##Overloading de +
        ##Uso: Vértice + id ou vértice --> adiciona esse vértice como um vizinho
        if idx(other,self.vizinhos)==-1:##Garante que só vai 
            if type(other)==Vertice:
                self.vizinhos.append(other.id)
            if type(other)==int:
                self.vizinhos.append(other)
        return self
    def __floordiv__(self, other): ##Overloading de // 
        ##Uso: Vértice // vértice
        if type(other)==Vertice:
            self + other
            other + self
    def __rshift__(self, other):#Retorna a posição que está mudando de um pra outro
        if type(other)==Vertice:
            diff = self.pos-other.pos
        elif type(other)==tuple or type(other)==np.ndarray or type(other)==list:
            diff = np.array(other)-self.pos
        if tuple(diff) in list(DIRECOES.keys()):
            return DIRECOES[tuple(diff)]
        else:
            return '_'
    def __lshift__(self, other):#Mesma coisa, só que muda o lado
        return other >> self



class Grafo():
    def __init__(self):
        self.vertices = []
    def __add__(self, other): ##Adiciona um vértice no grafo
        ## Uso: Grafo + vértice ou (x,y) --> cria o vértice (x,y) se precisar e adiciona ele no grafo
        if type(other)==Vertice:
            if idx(self.vertices,other)==-1:
                self.vertices.append(other)
        elif type(other)==tuple or type(other)==np.ndarray or type(other)==list:
            if idx(self.vertices,other)==-1:
                self.vertices.append(Vertice(np.array(other),len(self.vertices)))
        return self
    def __floordiv__(self, other): ##Adiciona um vértice no grafo fazendo as conexões
        ## Uso: Grafo + vértice ou (x,y)  --> inclui ovértice (x,y) no grafo conectado a todas as outras direções
        if type(other)==Vertice or type(other)==tuple or type(other)==np.ndarray or type(other)==list:
            self + other #adiciona o novo vértice no grafo
            for dir in list(DIRECOES.keys()):
                #Retorna a posição do vértice na lista 'vertices' ao mudar a posição em +-1 para cada direção
                vet_i = idx(tuple(self.vertices[-1].pos + np.array(dir)),self.vertices)
                if vet_i!=-1:
                    #Se ele existir, ele se conecta com o atual
                    self.vertices[vet_i] // self.vertices[-1]
    def __str__(self):
        string = ""
        for vet in self.vertices:
            string += str(vet)+"\n"
        return string


# lista = [Vertice((0,i),i) for i in range(10)]
# print(idx((0,3),lista))
# a = Vertice((0,0),1)
# print(a >> (-1,0))

def grafo_create(mat,wall=-1):
    #Cria o grafo a partir da matriz
    grafo = Grafo()
    for y in range(len(mat[0])):
        for x in range(len(mat)):
            if x>=0 and x<len(mat) and y>=0 and y<len(mat[0]):
                if mat[x][y]!=wall:
                    grafo // (x,y) #Cria o nó (x,y) e conecta ele no grafo
    print("Grafo: \n",grafo)

mat = np.arange(5*5).reshape((5,5))
print("mat: \n",mat)

G = grafo_create(mat)