//Seja bem vindo ao ao seu primeiro desafio! :D
//Aqui você vai aplicar os conceitos que aprendeu no módulo até agora, para fixar o seu conhecimento.
//Para isso, criamos uma série de exercícios que falam sobre os tópicos vistos.

// 1. Variáveis
// Crie uma função chamada "nome" que recebe um parâmetro "texto" e retorna esse texto.
// Você deve simplesmente retornar o parâmetro recebido pela função. Note que esse exercicio já foi resolvido, para você ter um exemplo.
function nome(texto) {
    return texto;
}

// 2. Operadores Aritméticos
// A função deve calcular e retornar a soma, subtração, multiplicação, divisão e resto da divisão de "a" por "b".
// Dentro desta função, você deve calcular cada uma das operações aritméticas mencionadas e atribuir os resultados a variáveis correspondentes.
// Ao final, você deve retornar um array contendo os resultados das operações. Note que esse exercicio já foi resolvido, para você ter um exemplo.
function operadoresAritmeticos(a, b) {
    var soma = a + b;
    var subtracao = a-b;
    var multiplicacao = a*b;
    var divisao = a/b;
    var restoDivisao = a%b;

    return [soma, subtracao, multiplicacao, divisao, restoDivisao];
}
// 3. Operadores Lógicos e de Comparação
// A função deve verificar se o número é par ou ímpar e retornar uma string indicando essa informação.
//Outputs esperados: par, ímpar.

function parOuImpar(numero) {
    // Dentro desta função, você deve usar o operador de resto (%) para verificar se o número é divisível por 2.
    // Se for divisível por 2, é par; caso contrário, é ímpar.
    // Retorne a string "par" ou "ímpar" com base nessa verificação.
    var resultado; /*seu código*/
    if(numero%2 == 0){
        resultado = "par";
    }else{
        resultado = "ímpar";
    }
    return resultado;
}

// 4. Estruturas Condicionais
// A função deve verificar se a pessoa pode dirigir com base na idade e retornar uma string correspondente.
// Outputs esperados: "Pode dirigir", "Não pode dirigir".
function podeDirigir(idade) {
    // Dentro desta função, você deve usar uma estrutura condicional (if/else) para verificar se a idade é maior ou igual a 18.
    var resultado; /*seu código*/
    if(idade < 18){
        resultado = "Não pode dirigir";

    }else{
        resultado = "Pode dirigir";
    }
    return resultado;
}

// 5. Estruturas de Repetição
function imprimirNumeros() {
    // Crie um loop for que itere de 1 a 5 e imprima cada número no console.
    // Ou seja, o resultado esperado é a impressão dos números de 1 a 5 no console.
    // Dica: use o console.log para imprimir os números.
    for(var itera = 0; itera < 5; itera++){
        console.log(itera);
    }
}

// 6. Operadores Ternários
// A função deve determinar se o número é positivo, negativo ou zero e retornar uma string correspondente.
// Use o operador ternário para verificar se o número é positivo, negativo ou zero.
// Outputs esperados: "positivo", "negativo", "zero".
function verificarNumero(numero) {
    var resultado = numero < 0 ? "negativo" : numero == 0 ? "zero" : "positivo";
    return resultado;
}

// 7. Variáveis e Operadores Aritméticos
// A função deve calcular e retornar a média aritmética dos três números.
function calcularMedia(a, b, c) {
    // Faça a soma dos três números e divida pelo número de elementos para calcular a média.
    var media = (a + b + c)/3;

    return media;
}

// 8. Operadores Lógicos e de Comparação
// A função deve verificar se a pessoa é maior de idade (idade maior ou igual a 18) e retornar true ou false.
function maiorDeIdade(idade) {
    // Use um operador de comparação para verificar se a idade é maior ou igual a 18.
    // Retorne true se for, e false caso contrário.
    var resultado = idade < 18 ? false : true;

    return resultado;
}

// 9. Estruturas Condicionais e Operadores Lógicos
// Crie uma função chamada "podeVotar" que recebe dois parâmetros: "idade" e "temTituloEleitoral". (tem título eleitoral é uma variável booleana)
// A função deve verificar se a pessoa pode votar, considerando que para votar é necessário ter 16 anos completos e possuir título de eleitor.
// Retorne true se a pessoa pode votar, e false caso contrário.
function podeVotar(idade, temTituloEleitoral) {
    // Use uma estrutura condicional para verificar as condições necessárias para votar.
    // Considere operadores lógicos para combinar as condições.
    var resultado = idade >= 16 && temTituloEleitoral ? true : false;

    return resultado;
}

// 10. Estruturas de Repetição e Operadores Aritméticos
// A função deve calcular e retornar a soma de todos os números de 1 até "n".
function somarNumerosAteN(n) {
    // Use um loop for para iterar de 1 até "n" e acumule a soma dos números.
    var soma = 0; 
    for(var i =0;  i <= n; i++){
        soma = soma + i;
    }

    return soma;
}

// 11. Operadores Ternários e Operadores de Comparação
// A função deve determinar qual dos dois números é maior e retornar esse número (nesse cenário, ainda não vamos tratar números iguais).
function maiorNumero(a, b) {
    // Use um operador ternário para determinar qual número é maior.
    var maior = a < b ? b : a;

    return maior;
}

// 12. Estruturas Condicionais e Operadores Lógicos
// Crie uma função chamada "verificarTriangulo" que recebe três parâmetros "a", "b" e "c", que representam os lados de um triângulo.
// A função deve verificar e retornar o tipo de triângulo: equilátero, isósceles ou escaleno.
function verificarTriangulo(a, b, c) {
    // Use uma estrutura condicional para verificar as condições para cada tipo de triângulo.
    // Utilize operadores lógicos para combinar as condições.
    var tipo; 
    if(a == b && b == c){
        tipo = "equilátero";
    }else if(a != b && b != c && a != c){
        tipo = "escaleno"
    }else{
        tipo = "isóceles"
    }

    return tipo;
}

// 13. Operadores Aritméticos e Operadores Lógicos
// A função deve verificar se o ano é bissexto e retornar true ou false.
function verificarAnoBissexto(ano) {
    // Um ano é bissexto se for divisível por 4 e não for divisível por 100, ou se for divisível por 400.
    var resultado = ano % 4 != 0 ? false : ano % 100 != 0 ? true : ano % 400 !=0 ? false : true;

    return resultado;
}

// 14. Variáveis e Operadores de Comparação
// Crie uma função chamada "compararStrings" que recebe dois parâmetros "str1" e "str2", que são strings.
// A função deve comparar as duas strings e retornar true se forem iguais e false caso contrário.
function compararStrings(str1, str2) {
    // Use o operador de comparação para verificar se as strings são iguais.
    var resultado = str1 == str2 ? true : false;

    return resultado;
}

// 15. Operadores Ternários e Operadores de Comparação
// Crie uma função chamada "maiorTresNumeros" que recebe três parâmetros "a", "b" e "c".
// A função deve determinar qual dos três números é o maior e retornar esse número.
function maiorTresNumeros(a, b, c) {
    // Use operadores ternários para comparar os números e determinar o maior.
    var maior = a > b && a > c ? a : b > a && b > c ? b : c;

    return maior;
}


//Parabéns! Você concluiu o desafio da semana 1!
//Para testar o seu código, rode o comando "npx jest" no terminal.



//NÃO ALTERAR ESSA LINHA
module.exports = {
    nome: nome,
    operadoresAritmeticos: operadoresAritmeticos,
    parOuImpar: parOuImpar,
    podeDirigir: podeDirigir,
    imprimirNumeros: imprimirNumeros,
    verificarNumero: verificarNumero,
    calcularMedia: calcularMedia,
    maiorDeIdade: maiorDeIdade,
    podeVotar: podeVotar,
    somarNumerosAteN: somarNumerosAteN,
    maiorNumero: maiorNumero,
    verificarTriangulo: verificarTriangulo,
    verificarAnoBissexto: verificarAnoBissexto,
    compararStrings: compararStrings,
    maiorTresNumeros: maiorTresNumeros
};
