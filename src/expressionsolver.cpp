//---------------------------------------------------------------------
// Arquivo      : expressionsolver.cpp
// Conteudo     : programa que implementa a classe ExpressionSolver
// Autor        : André Luiz Alves Costa (andrelac963@gmail.com)
// Historico    : 2023-05-09 - arquivo criado
//---------------------------------------------------------------------

#include "expressionsolver.hpp"

ExpressionSolver::ExpressionSolver(string filename)
{
  this->ReadFile(filename);

  // Valida se o tipo de expressão de saída solicitado no arquivo de entrada é válido e exibe a expressão
  if (this->outputType == "INFIXA")
  {
    cout << endl
         << "Resultado" << endl;
    cout << "EXP: " << this->convertToInfix(this->postfixExpression) << endl;
  }
  else if (this->outputType == "POSFIXA")
  {
    cout << "Resultado" << endl;
    cout << "EXP: " << this->postfixExpression << endl;
  }
  else
  {
    throw InvalidType{this->outputType};
  }

  // Exibe o resultado da expressão
  cout << fixed << setprecision(6) << "VAL: " << this->solvePostfix() << endl
       << endl;
}

ExpressionSolver::~ExpressionSolver() {}

void ExpressionSolver::ReadFile(string filename)
{
  ifstream file(filename);

  // Valida se o arquivo de entrada foi aberto corretamente
  if (file.is_open())
  {
    string line[3];

    // Lê as 3 linhas do arquivo de entrada e armazena em um vetor de strings
    for (int i = 0; i < 3; i++)
    {
      getline(file, line[i]);
    }

    file.close();

    // Separa o tipo de expressão de entrada
    char inputType[8];
    char expression[1000];

    int i = 0;
    while (line[0][i] != ' ')
    {
      i++;
    }
    i++;

    int j = 0;
    while (line[0][i] != ' ')
    {
      inputType[j] = line[0][i];
      i++;
      j++;
    }
    inputType[j] = '\0';

    // Separa a expressão
    i += 2;
    int k = 0;
    while (line[0][i] != '\0')
    {
      expression[k] = line[0][i];
      i++;
      k++;
    }
    expression[k] = '\0';

    // Separa o resultado da expressão
    char answer[100];

    int a = 0;
    while (line[2][a] != ' ')
    {
      a++;
    }
    a += 3;

    int b = 0;
    while (line[2][a] != '\0')
    {
      answer[b] = line[2][a];
      a++;
      b++;
    }
    answer[b] = '\0';

    this->inputType = inputType;

    // Valida se o tipo de expressão de entrada informado no arquivo de entrada é válido
    if (this->inputType == "INFIXA")
    {
      // Valida se a expressão infixa é válida
      if (isValidInfixExpression(expression))
      {
        this->postfixExpression = convertToPostfix(expression);
      }
      else
      {
        throw InvalidExpression{expression};
      }
    }
    else if (this->inputType == "POSFIXA")
    {
      // Valida se a expressão posfixa é válida
      if (isValidPostfixExpression(expression))
      {
        this->postfixExpression = expression;
      }
      else
      {
        throw InvalidExpression{expression};
      }
    }
    else
    {
      throw InvalidType{this->inputType};
    }

    this->outputType = line[1];

    this->answer = answer;
  }
  else
  {
    throw FailedToOpenFile{filename};
  }
}

bool isValidOperatorQuantity(string expr)
{
  int numOperands = 0;
  int numOperators = 0;
  int n = expr.size();

  // percorre a string da expressão
  for (int i = 0; i < n; i++)
  {
    if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/')
    {
      numOperators++;
    }
    else if (isdigit(expr[i]))
    {
      numOperands++;

      // avança para o próximo número, se houver
      while (i < n && expr[i] != ' ')
      {
        i++;
      }

      // volta uma posição para o caso do próximo caracter ser um operador
      i--;
    }
  }

  // retorna true se a quantidade de Operators é um a menos que a quantidade de Operands
  return numOperators == numOperands - 1;
}

bool ExpressionSolver::isValidPostfixExpression(string expr)
{
  // Valida se a quantidade de operadores é um a menos que a quantidade de operandos
  if (!isValidOperatorQuantity(expr))
  {
    return false;
  }

  int n = expr.size();

  // Valida se o último caracter da expressão é um operador
  if (expr[n - 2] != '+' && expr[n - 2] != '-' && expr[n - 2] != '*' && expr[n - 2] != '/')
  {
    return false;
  }

  return true;
}

bool ExpressionSolver::isValidInfixExpression(string expr)
{
  // Valida se a quantidade de operadores é um a menos que a quantidade de operandos
  if (!isValidOperatorQuantity(expr))
  {
    return false;
  }

  int n = expr.size();
  int openParenCount = 0;

  // Valida se a quantidade de parênteses abertos é igual a quantidade de parênteses fechados
  for (int i = 0; i < n; i++)
  {
    char c = expr[i];
    if (c == '(')
    {
      openParenCount++;
    }
    else if (c == ')')
    {
      openParenCount--;
      if (openParenCount < 0)
      {
        return false;
      }
    }
  }

  return openParenCount == 0;
}

int precedencia(char op)
{
  if (op == '+' || op == '-')
  {
    return 1;
  }
  else if (op == '*' || op == '/')
  {
    return 2;
  }
  else
  {
    return 0;
  }
}

string ExpressionSolver::convertToPostfix(string expr)
{
  string postfix = "";
  int size = expr.size();

  stack<char> oper = stack<char>(size);

  for (int i = 0; i < size; i++)
  {
    char c = expr[i];

    if (isdigit(c))
    {
      // Extrai o número da expressão
      int j = i;
      while (j < size && (isdigit(expr[j]) || expr[j] == '.'))
      {
        j++;
      }
      string number = expr.substr(i, j - i);
      postfix += number + " ";
      i = j - 1; // Avança a posição i para o final do número
    }
    else if (c == '+' || c == '-' || c == '*' || c == '/')
    {
      while (!oper.isEmpty() && precedencia(oper.peek()) >= precedencia(c))
      {
        postfix += oper.peek();

        oper.pop();
      }
      oper.push(c);
    }
    else if (c == '(')
    {
      oper.push(c);
    }
    else if (c == ')')
    {
      while (!oper.isEmpty() && oper.peek() != '(')
      {
        postfix += oper.peek();
        postfix += " ";
        oper.pop();
      }
      oper.pop();
    }
  }

  while (!oper.isEmpty())
  {
    postfix += oper.peek();
    oper.pop();
  }

  return postfix;
}

string ExpressionSolver::convertToInfix(string expr)
{
  string infix = "";
  int size = expr.size();

  stack<string> oper = stack<string>(size);

  for (int i = 0; i < size; i++)
  {
    char c = expr[i];

    if (isdigit(c))
    {
      // Extrai o número da expressão
      int j = i;
      while (j < size && (isdigit(expr[j]) || expr[j] == '.'))
      {
        j++;
      }
      string number = expr.substr(i, j - i);
      oper.push(number);
      i = j - 1; // Avança a posição i para o final do número
    }
    else if (c == '+' || c == '-' || c == '*' || c == '/')
    {
      string op1 = oper.peek();
      oper.pop();
      string op2 = oper.peek();
      oper.pop();
      string operacao = "( " + op2 + " " + c + " " + op1 + " )";
      oper.push(operacao);
    }
  }

  infix = oper.peek();
  oper.pop();

  return infix;
}

double ExpressionSolver::solvePostfix()
{
  int size = this->postfixExpression.size();

  stack<double> oper = stack<double>(size);

  for (int i = 0; i < size; i++)
  {
    char c = this->postfixExpression[i];

    if (isdigit(c))
    {
      // Extrai o número da expressão
      int j = i;
      while (j < size && (isdigit(this->postfixExpression[j]) || this->postfixExpression[j] == '.'))
      {
        j++;
      }
      string number = this->postfixExpression.substr(i, j - i);
      oper.push(stod(number));
      i = j - 1; // Avança a posição i para o final do número
    }
    // Se o caractere for um operador, desempilha os dois últimos operandos e realiza a operação
    else if (c == '+' || c == '-' || c == '*' || c == '/')
    {
      double op1 = oper.peek();
      oper.pop();
      double op2 = oper.peek();
      oper.pop();
      double resultado;
      switch (c)
      {
      case '+':
        resultado = op2 + op1;
        break;
      case '-':
        resultado = op2 - op1;
        break;
      case '*':
        resultado = op2 * op1;
        break;
      case '/':
        resultado = op2 / op1;
        break;
      default:
        break;
      }
      oper.push(resultado);
    }
  }

  double result = oper.peek();

  return result;
}