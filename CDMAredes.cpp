#include <fstream>
#include <iostream>

using namespace std;

int chave1[8] = {1,1,1,-1,1,-1,-1,-1};
int chave2[8] = {1,-1,1,1,1,-1,1,1};

string validaInformacao(string informacao){
    int tamanho = informacao.length();

    for (int i = 0; i < tamanho; i++){
        if (informacao[i] != '0' && informacao[i] != '1') {
            informacao = "Os dados informados nao sao numeros binarios!";
            break;
        }
    }

    return informacao;
}

string leArquivoTxt(string programa, int tipo){
    ifstream arq;
    string informacao;
	
    programa = programa + ".txt";

	arq.open(programa);
	
	if (arq.is_open()){
		getline(arq,informacao);
		
		arq.close();
	} 
	else informacao = "Nao foi possivel ler o arquivo " + programa;

    if (tipo == 1) informacao = validaInformacao(informacao);

    return informacao;
}

void geraArquivoTxt(string informacao_saida){
    ofstream arq;

	arq.open("Sinal_Gerado.txt");
	if(arq.is_open()){
		arq << informacao_saida;
		
		arq.close();
	}
	else cout << "Erro ao gerar o arquivo!";
}

string corrigeInformacao(string informacao, int tamanho){
    int quantidade = informacao.length();
    string complemento;

    for (int i = quantidade; i <= tamanho; i++){
        complemento = complemento + "2"; 
    }

    return informacao + complemento;
}

string cdma(string informacao1, string informacao2){
    int tamanho1 = informacao1.length() * 8;
    int tamanho2 = informacao2.length() * 8;
    int tamanho_maior;
    int quantidade;
    int bit1;
    int bit2; 
    int contador = 0;
    string informacao_saida;

    if (tamanho1 >= tamanho2) {
        tamanho_maior = tamanho1;
        quantidade = informacao1.length();
        informacao2 = corrigeInformacao(informacao2,tamanho_maior);
    }
    else {
        tamanho_maior = tamanho2;
        quantidade = informacao2.length();
        informacao1 = corrigeInformacao(informacao1,tamanho_maior);
    }

    int dados[tamanho_maior];
    
    for (int i = 0; i < quantidade; i++){
        if      (informacao1[i] == '1') bit1 = 1;
        else if (informacao1[i] == '0') bit1 = -1;
        else bit1 = 0;
        
        if      (informacao2[i] == '1') bit2 = 1;
        else if (informacao2[i] == '0') bit2 = -1;
        else bit2 = 0;
        
        for (int j = 0; j < 8; j++){
            dados[contador] = (bit1 * chave1[j]) + (bit2 * chave2[j]);
            contador++;
        }
    }
    
    for (int i = 0; i < tamanho_maior; i++){
        informacao_saida = informacao_saida + to_string(dados[i]);
    }
    
    return informacao_saida;
}

string converteSinal(string informarcao, int tamanho, int tipo){
    string bits;
    string bits_saida;
    string inf;
    bool negativo = false;
    int operacao = 0;
    int bit;
    int aux = 0;
    float div = 0;

    for (int i = 0; i < informarcao.length(); i++){
        if (negativo){
                 if (informarcao[i] == '1') bits = bits + '3';
            else if (informarcao[i] == '2') bits = bits + '4';

            negativo = false;
        }
        else {
                 if (informarcao[i] == '0') bits = bits + '0';
            else if (informarcao[i] == '1') bits = bits + '1';
            else if (informarcao[i] == '2') bits = bits + '2';
        }
        
        if (informarcao[i] == '-') negativo = true;
    }

    if (tipo == 999) return bits;

    for (int i = 0; i < tamanho; i++){
        switch (bits[i]){
            case '0': bit = 0;
                      break;
            
            case '1': bit = 1;
                      break;

            case '2': bit = 2;
                      break;

            case '3': bit = -1;
                      break;

            case '4': bit = -2;
                      break;
        }
        
        operacao = operacao + (bit * (tipo==1?chave1[aux]:(tipo==2?chave2[aux]:0)));
        aux++;

        if (aux == 8){
            if (operacao == 0) inf = '0';
            else {
                if (operacao % 8 == 0) inf = to_string(operacao / 8);
                else {
                    div = operacao / 8;
                    inf = to_string(div);
                }
            }

            if (inf == "-1") inf = '0';

            bits_saida = bits_saida + inf;
            operacao   = 0;
            aux        = 0;
        }
    }

    return bits_saida;
}

void decodificaSinal(string informacao_saida, string informacao1, string informacao2){
    int tamanho1 = informacao1.length() * 8;
    int tamanho2 = informacao2.length() * 8;
    int tamanho_comparacao;
    string inf1  = converteSinal(informacao_saida,tamanho1,1);
    string inf2  = converteSinal(informacao_saida,tamanho2,2);
    
    cout << endl;

    if      (tamanho1 >= tamanho2) tamanho_comparacao = tamanho1;
    else if (tamanho1 < tamanho2)  tamanho_comparacao = tamanho2;

    if (converteSinal(informacao_saida,tamanho_comparacao,999).length() != tamanho_comparacao){
        cout << "O sinal gerado NAO CONDIZ com os sinais de entrada!" << endl;
        return;
    }

    if (informacao1 == inf1 && informacao2 == inf2) cout << "O sinal gerado CONDIZ com os sinais de entrada!" << endl;
    else cout << "O sinal gerado NAO CONDIZ com os sinais de entrada!" << endl;
}

int main(){
	string informacao1 = leArquivoTxt("info1",1);
    string informacao2 = leArquivoTxt("info2",1);
    int opcao;
    int finaliza;

    if (validaInformacao(informacao1) == "Os dados informados nao sao numeros binarios!" ||
        validaInformacao(informacao2) == "Os dados informados nao sao numeros binarios!"){
        cout << "Nao foi possivel transmitir as informacoes, pois algum dos dois pacotes nao possuem numeros binarios!";
    }
	else {
        while (true){
            cout << endl;
            cout << "1 - Gera o Sinal de Saida;"       << endl;
            cout << "2 - Decodifica o Sinal de Saida;" << endl;
            cout << "3 - Sair."                        << endl;
            cout << "Escolha alguma das opcoes acima: ";
            cin >> opcao;

            switch (opcao){
                case 1: geraArquivoTxt(cdma(informacao1,informacao2));
                        break;
                
                case 2: decodificaSinal(leArquivoTxt("Sinal_Gerado",2),informacao1,informacao2);
                        break;

                default: return 0;
                         break;
            }

            cout << endl << "Deseja escolher alguma outra opcao? 1 - Sim | 2 - Nao" << endl;
            cin >> finaliza;

            if (finaliza != 1) return 0;
        }
    }
    
    return 0;
}
