//---------------------------------------------------------------------
// Arquivo      : expressionsolver.hpp
// Conteudo     : cabeçalho da classe ExpressionSolver
// Autor        : André Luiz Alves Costa (andrelac963@gmail.com)
// Historico    : 2023-05-09 - arquivo criado
//---------------------------------------------------------------------

#ifndef EXPRESSIONSOLVER_H
#define EXPRESSIONSOLVER_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;

// Exceção para erros de abertura de arquivo
struct FailedToOpenFile
{
  string filename;
};

// Exceção para erros de tipo de expressão
struct InvalidType
{
  string type;
};

// Exceção para erros de expressão inválida
struct InvalidExpression
{
  string expression;
};

class ExpressionSolver
{
public:
  // Construtor e destrutor
  ExpressionSolver(string filename);
  ~ExpressionSolver();

  // Lê um arquivo de entrada
  void ReadFile(string filename);

  // Valida se uma expressão posfixa é válida
  bool isValidPostfixExpression(string expr);

  // Valida se uma expressão infixa é válida
  bool isValidInfixExpression(string expr);

  // Converte uma expressão infixa para posfixa
  string convertToPostfix(string expr);

  // Converte uma expressão posfixa para infixa
  string convertToInfix(string expr);

  // Resolve uma expressão posfixa
  double solvePostfix();

private:
  string inputType;
  string outputType;
  string postfixExpression;
  string answer;
};

// Implementação da classe Stack

// Tamanho padrão da pilha
#define SIZE 10

template <class X>
class stack
{
  X *arr;
  int top;
  int capacity;

public:
  // Construtor
  stack(int size = SIZE)
  {
    arr = new X[size];
    capacity = size;
    top = -1;
  };

  // Insere um elemento na pilha
  void push(X x)
  {
    if (isFull())
    {
      exit(EXIT_FAILURE);
    }

    arr[++top] = x;
  };

  // Remove um elemento da pilha
  X pop()
  {
    if (isEmpty())
    {
      exit(EXIT_FAILURE);
    }

    return arr[top--];
  };

  // Retorna o elemento do topo da pilha
  X peek()
  {
    if (!isEmpty())
    {
      return arr[top];
    }
    else
    {
      exit(EXIT_FAILURE);
    }
  };

  // Retorna o tamanho da pilha
  int size()
  {
    return top + 1;
  };

  // Retorna se a pilha está vazia
  bool isEmpty()
  {
    return top == -1;
  };

  // Retorna se a pilha está cheia
  bool isFull()
  {
    return top == capacity - 1;
  };

  // Destrutor
  ~stack()
  {
    delete[] arr;
  };
};

#endif