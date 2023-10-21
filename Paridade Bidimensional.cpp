#include <iostream>

using namespace std;

string retorna_linha(int inicio, int fim, string bit_inicial){
    string bit_linha;
    int contador = 0;
    
    for (int i = inicio; i < fim; i++){
        bit_linha = bit_linha + bit_inicial[i];
        
        if (bit_inicial[i] == '1') contador++;
    }
    
    if (contador % 2 == 0) bit_linha = bit_linha + "0";
    else bit_linha = bit_linha + "1";
    
    return bit_linha;
}

string retorna_ultima_linha(string bit_linha1, string bit_linha2, string bit_linha3, string bit_linha4, string bit_linha5){
    int contador = 0;
    
    if (bit_linha1[4] == '1') contador++;
    if (bit_linha2[4] == '1') contador++;
    if (bit_linha3[4] == '1') contador++;
    if (bit_linha4[4] == '1') contador++;
    
    for (int i = 0; i < 4; i++){
        if (bit_linha5[i] == '1') contador++;
    }
    
    if (contador % 2 == 0) bit_linha5 = bit_linha5 + "0";
    else bit_linha5 = bit_linha5 + "1";
    
    return bit_linha5;
}

string bit_datagrama(string bit_inicial){
    string bit_linha1;
    string bit_linha2;
    string bit_linha3;
    string bit_linha4;
    string bit_linha5;
    string datagrama;
    int contador;
    
    bit_linha1 = retorna_linha(0, 4, bit_inicial);
    bit_linha2 = retorna_linha(4, 8, bit_inicial);
    bit_linha3 = retorna_linha(8, 12, bit_inicial);
    bit_linha4 = retorna_linha(12, 16, bit_inicial);
    
    for (int i = 0; i < 4; i++){
        contador = 0;
        
        if (bit_linha1[i] == '1') contador++;
        if (bit_linha2[i] == '1') contador++;
        if (bit_linha3[i] == '1') contador++;
        if (bit_linha4[i] == '1') contador++;
        
        if (contador % 2 == 0) bit_linha5 = bit_linha5 + "0";
        else bit_linha5 = bit_linha5 + "1";
    }
    
    bit_linha5 = retorna_ultima_linha(bit_linha1, bit_linha2, bit_linha3, bit_linha4, bit_linha5);
    datagrama = bit_linha1 + bit_linha2 + bit_linha3 + bit_linha4 + bit_linha5;
    
    return datagrama;
}

string recupera_linha_paridade(string datagrama_inicial, int inicio, int fim){
    string linha_paridade = "";
    
    for (int i = inicio; i < fim; i++){
        linha_paridade = linha_paridade + datagrama_inicial[i];
    }
    
    return linha_paridade;
}

string verifica_paridade_bidimensional(string datagrama_inicial){
    string verifica_bit;
    string linha5;
    int contador;
    
    string bit_linha1 = recupera_linha_paridade(datagrama_inicial, 0, 5);
    string bit_linha2 = recupera_linha_paridade(datagrama_inicial, 5, 10);
    string bit_linha3 = recupera_linha_paridade(datagrama_inicial, 10, 15);
    string bit_linha4 = recupera_linha_paridade(datagrama_inicial, 15, 20);
    string bit_linha5 = recupera_linha_paridade(datagrama_inicial, 20, 25);
    
    verifica_bit = retorna_linha(0, 4, bit_linha1);
    if (verifica_bit != bit_linha1) return "Essa Paridade Bidimensional esta INCORRETA!";
    
    verifica_bit = retorna_linha(0, 4, bit_linha2);
    if (verifica_bit != bit_linha2) return "Essa Paridade Bidimensional esta INCORRETA!";
    
    verifica_bit = retorna_linha(0, 4, bit_linha3);
    if (verifica_bit != bit_linha3) return "Essa Paridade Bidimensional esta INCORRETA!";
    
    verifica_bit = retorna_linha(0, 4, bit_linha4);
    if (verifica_bit != bit_linha4) return "Essa Paridade Bidimensional esta INCORRETA!";
    
    for (int i = 0; i < 4; i++){
        contador = 0;
        
        if (bit_linha1[i] == '1') contador++;
        if (bit_linha2[i] == '1') contador++;
        if (bit_linha3[i] == '1') contador++;
        if (bit_linha4[i] == '1') contador++;
        
        if (contador % 2 == 0) linha5 = linha5 + "0";
        else linha5 = linha5 + "1";
    }
    
    verifica_bit = retorna_ultima_linha(bit_linha1, bit_linha2, bit_linha3, bit_linha4, linha5);
    if (verifica_bit != bit_linha5) return "Essa Paridade Bidimensional esta INCORRETA!";
    
    return "Essa Paridade Bidimensional esta CORRETA!";
}

bool verifica_string(string sequencia_bits, int tipo){
    int bits = sequencia_bits.length();
    
    if (tipo == 1 && bits != 16) {
        cout << endl << "Quantidade de bits insuficiente!";
        return true;
    } else 
    if (tipo == 2 && bits != 25) {
        cout << endl << "Quantidade de bits insuficiente!";
        return true;
    }
    
    for (int i = 0; i < bits; i++){
        if (sequencia_bits[i] != '0' && sequencia_bits[i] != '1') {
            cout << endl << "A sequência digitada não é uma sequência binária!";
            return true;
        }
    }
    
    return false;
}

int main() {
    string bit_inicial;
    string datagrama;
    string datagrama_inicial;
    int opcao1;
    int opcao2;
    int opcao3;
    bool sair;
    
    do {
        system("clear");
        
        cout << "1 - Gerar Paridade Bidimensional"     << endl
             << "2 - Verificar Paridade Bidimensional" << endl
             << "3 - Sair"                             << endl << endl
             << "Escolha uma das opções acima: ";
        cin >> opcao1;
        
        if (opcao1 == 1 || opcao1 == 2){
            if (opcao1 == 1) {
                system("clear");
                
                cout << "Informe um valor binário de 16 bits: ";
                cin >> bit_inicial;
                
                if (!verifica_string(bit_inicial, 1)){
                    datagrama = bit_datagrama(bit_inicial);
                
                    cout << endl << "O Datagrama é: " << datagrama;
                }
            } else
            if (opcao1 == 2){
                system("clear");
                
                cout << "Deseja informar uma nova Paridade Bidimensional ou carregar a gerada (caso tenha gerado)? 1 - Carregar / 2 - Novo" << endl;
                cin >> opcao3;
                
                system("clear");
                
                if (opcao3 == 1 && datagrama != "") {
                    datagrama_inicial = datagrama;
                } else
                if (opcao3 == 1 && datagrama == "") {
                    cout << "Não foi gerado nenhuma Paridade Bidimensional!" << endl << endl;
                }
                
                if (opcao3 != 1 || (opcao3 == 1 && datagrama == "")) {
                    cout << "Informe uma Paridade Bidimensional de 25 bits: ";
                    cin >> datagrama_inicial;
                    cout << endl;
                }
                
                if (!verifica_string(datagrama_inicial, 2)){
                    cout << verifica_paridade_bidimensional(datagrama_inicial);
                }
            }
            
            cout << endl << endl << "Deseja escolher outra opção? 1 - Sim / 2 - Não" << endl;
            cin >> opcao2;
            
            if (opcao2 == 2) sair = true;
        } 
        
        else sair = true;
        
    } while (!sair);
    
    return 0;
}