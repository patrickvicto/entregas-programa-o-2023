// importação de blibliotecas

#include <iostream>
using namespace std;

// definição da classe Cliente
class Cliente {
  // atributos privados
private:
  long long imei;
  std::string login;
  // atributos publicos
public:
  Cliente();
  Cliente(long long imei, std::string login);
  // função para recuperar o Login
  string getLogin() const;
  // função para recuperar o Imei
  long long getImei() const;
};

// Implementação de construtor vazio, caso não receba nada
Cliente::Cliente() {
  this->imei = -1;
  this->login = "";
};
// implementação do contrutor, mas recebendo parametros
Cliente::Cliente(long long imei, std::string login) {
  this->imei = imei;
  this->login = login;
} // função para pegar o login do cliente
string Cliente::getLogin() const {
  return login;
} // função para pegar imei do bleinte
long long Cliente::getImei() const { return imei; }

// definiição da classe Hash
class Hash {
  // atributos publicos
public:
  // função cria tabela hash com (x) espaços
  Hash(int max_itens = 100);
  ~Hash();
  bool verificarLotacao() const;
  int recuperarTamanho() const;
  // definição na classe de uma função para recuperar um cliente da tabela
  void recuperarItem(Cliente &cliente, bool &encontrado);
  // definição na classe de uma função inserir um cliente da tabela
  void inserirItem(Cliente cliente);
  // definição na classe de uma função deletar um cliente da tabela
  void deletarItem(Cliente cliente);
  void print();
  // atributos privados
private:
  int getHash(Cliente cliente);
  int max_itens;
  int tamanho;
  Cliente *estrutura;
};
// definição de um construtor para a classe Hash que confirma de o numero de
// itens na tabela hash e iqual ao max permitido
Hash::Hash(int max) {
  tamanho = 0;
  max_itens = max;
  estrutura = new Cliente[max_itens];
}

// deleta um pedaço da tabela hash
Hash::~Hash() { delete[] estrutura; }
// verifica se  a tabela ta lotada
bool Hash::verificarLotacao() const { return (tamanho == max_itens); }
// verivica o temanho da tabela hash
int Hash::recuperarTamanho() const { return tamanho; }

// função para encontrar um cliente na tabela, considerando colisões
void Hash::recuperarItem(Cliente &cliente, bool &encontrado) {
  int localizacao_inicial = getHash(cliente);
  bool mais_a_procurar = true;
  int localizacao = localizacao_inicial;
  do {
    if (estrutura[localizacao].getImei() == cliente.getImei() ||
        estrutura[localizacao].getImei() == -1)
      mais_a_procurar = false;
    else
      localizacao = (localizacao + 1) % max_itens;
  } while (localizacao != localizacao_inicial && mais_a_procurar);
  int found = (estrutura[localizacao].getImei() == cliente.getImei());
  if (found) {
    cliente = estrutura[localizacao];
  }
}
// função para iserir um cliente na tabeça, considerando colissões
void Hash::inserirItem(Cliente cliente) {
  int localizacao = getHash(cliente);
  //
  while (estrutura[localizacao].getImei() > 0)
    localizacao = (localizacao + 1) % max_itens;
  estrutura[localizacao] = cliente;
  tamanho++;
}
// função para deletar cliente na tabela, considerando colissões
void Hash::deletarItem(Cliente cliente) {
  int localizacao_inicial = getHash(cliente);
  bool mais_a_procurar = true;
  int localizacao = localizacao_inicial;
  do {
    if (estrutura[localizacao].getImei() == cliente.getImei() ||
        estrutura[localizacao].getImei() == -1)
      mais_a_procurar = false;
    else
      localizacao = (localizacao + 1) % max_itens;
  } while (localizacao != localizacao_inicial && mais_a_procurar);

  if (estrutura[localizacao].getImei() == cliente.getImei()) {
    estrutura[localizacao] = Cliente(-2, "");
    tamanho--;
  }
}
// função para printar tabela hash
void Hash::print() {
  for (int i = 0; i < max_itens; i++) {
    cout << i << ":" << estrutura[i].getImei() << ", "
         << estrutura[i].getLogin() << endl;
  }
}

// descobre o hash de um cliente a partir do que foi fornecido
int Hash::getHash(Cliente cliente) { return cliente.getImei() % max_itens; }

// função main, que ira rodar o codigo
// obs : Os codigos devem rodar todos juntos
int main() {
  // Caso de teste numero 1
  cout << "inicio do caso de teste 1" << endl;
  cout << "objetivo: criar uma tabela hash com numero de espaços desejados"
       << endl;
  Hash clientesHash(11);
  // Imei a serem salvos
  long long ras[5] = {929001100012704, 899002300031233, 1200000011012330,
                      73200722042112, 987380010052204};
  // login a serem salvos
  string login[5] = {"pedroag@gmail.com", "pablo95@gmail.com",
                     "Joãopaulista@gmail.com", "Carlos63artes@gmail.com",
                     "Lucasaugusto300@gmail.com"};

  for (int i = 0; i < 5; i++) {
    Cliente cliente = Cliente(ras[i], login[i]);
    clientesHash.inserirItem(cliente);
  }
  clientesHash.print();
  // cout << "------------------------------" <<  endl;
  //  cout << "Os úsuarios adcioandos acima devem estar presentes na tabela" <<
  //  endl;
  cout << "Fim do caso de teste 1" << endl;

  cout << "------------------------------" << endl;
  /////fim do caso de teste numero 1

  // inicio do caso de teste de numero  2
  cout << "inicio do caso de teste 2" << endl;
  cout << "objetivo: deletar um usuário da tabela hash, salvo em sua devida "
          "posição"
       << endl;
  Cliente cliente_deletar(1200000011012330, "");
  clientesHash.deletarItem(cliente_deletar);
  clientesHash.print();
  cout << "fim do caso de teste de numero 2" << endl;
  cout << "------------------------------" << endl;
  // fim do caso de teste de numero  2

  // inicio do caso de teste de numero 3
  cout << "inicio do caso de teste 3" << endl;
  cout << "objetivo: obter as informações de um usuário da tabela hash, salvo "
          "em sua devida posição"
       << endl
       << endl;
  Cliente cliente(929001100012704, "");
  bool encontrado = false;
  clientesHash.recuperarItem(cliente, encontrado);
  cout << cliente.getLogin() << "->"
       << "este e o login referente ao Imei passado" << endl
       << endl;
  cout << "fim do caso de teste de numero 3" << endl;
  cout << "------------------------------" << endl;
  // fim do caso de teste de numero  3

  // inicio do caso de teste de numero  4
  cout << "inicio do caso de teste 4" << endl;
  cout << "objetivo: adicionar um novo usuário a tabela hash, tratando a "
          "colisão e o adicionando no proximo espaço disponivel"
       << endl;
  Cliente cliente_adicionar(929001100012748, "paulocarioca@gmail.com");
  clientesHash.inserirItem(cliente_adicionar);
  clientesHash.print();
  cout << "Fim do caso de teste 2" << endl;
  cout << "------------------------------" << endl;
  // fim do caso de teste numero 4

  // inicio do caso de teste de numero  5
  cout << "inicio do caso de teste 5" << endl;
  cout << "objetivo: pegar informações de um usuário que foi registrado em "
          "outra posição na tabela, devido ao tratamento de colisão."
       << endl
       << endl;
  Cliente cliente_recuperar(929001100012748, "");
  bool encontrado_recuperar = false;
  clientesHash.recuperarItem(cliente_recuperar, encontrado);
  cout << cliente_recuperar.getLogin() << "->"
       << "este e o login referente ao Imei passado" << endl
       << endl;
  cout << "fim do caso de teste de numero 5" << endl;
  cout << "------------------------------" << endl;
  // fim do caso de teste numero 5

  // inicio do caso de teste de numero  6
  cout << "inicio do caso de teste 6" << endl;
  cout << "objetivo: deletar um usuário que foi registrado em outra posição na "
          "tabela, devido ao tratamento de colisão"
       << endl;
  Cliente cliente_deletar_colisao(929001100012748, "");
  clientesHash.deletarItem(cliente_deletar_colisao);
  clientesHash.print();
  cout << "fim do caso de teste de numero 6" << endl;
  cout << "------------------------------" << endl;
  // fim do caso de teste numero 6
}
