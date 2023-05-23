//---------------------------------------------------------------------
// Arquivo      : main.cpp
// Conteudo     : programa principal que chama a classe ExpressionSolver
// Autor        : André Luiz Alves Costa (andrelac963@gmail.com)
// Historico    : 2023-05-09 - arquivo criado
//---------------------------------------------------------------------

#include <iostream>
#include "expressionsolver.hpp"

using namespace std;

int main(int argc, char *argv[])
{
  try
  {
    ExpressionSolver *expressionSolver = new ExpressionSolver(argv[1]);

    delete expressionSolver;
  }
  catch (FailedToOpenFile e)
  {
    cout << "Erro ao abrir o arquivo " << e.filename << endl
         << endl;
  }
  catch (InvalidType e)
  {
    cout << "Tipo de expressão inválido: " << e.type << endl
         << endl;
  }
  catch (InvalidExpression e)
  {
    cout << "Expressão inválida: " << e.expression << endl
         << endl;
  }
  return 0;
}