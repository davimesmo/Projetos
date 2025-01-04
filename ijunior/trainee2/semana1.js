//Se você chegou até aqui, parabéns!
//Aqui teremos alguns exercícios um pouco mais desafiadores.
//Se você não conseguiu resolver algum deles, não se preocupe, é normal, eu mesmo não dei conta de alguns na minha época (já fazem 84 anos).
//Com toda a bondade do meu coração, eu deixei o gabarito de cada exercício no final da página de exercícios no Notion.
//MASSSSSSSSSSSSSS antes de olhar o gabarito, faça o dev feliz e tente resolver os exercícios sozinho(a) primeiro, ok?
//Quando chegar ao final, você terá aprendido o básico de JavaScript e poderá dar o próximo passo.


// 1. Arrays e Loops
// Crie uma função chamada "dobrarNumeros" que recebe um array de números como parâmetro e retorna um novo array onde cada número é dobrado.
// Dica: use um loop for para percorrer o array e o método push para adicionar elementos ao array resultante.
function dobrarNumeros(nums) {
    var numerosDobrados = [];
    for (var index = 0; index < nums.length; index++) {
        numerosDobrados.push(nums[index]*2);        
    }
    return numerosDobrados;
}

// 2. Objetos
// Crie uma função chamada "criarPessoa" que recebe dois parâmetros: "nome" e "idade".
// A função deve retornar um objeto com as propriedades "nome" e "idade" de acordo com os parâmetros fornecidos.
function criarPessoa(nome, idade) {
    var pessoa = {
        nome: nome,
        idade: idade

    };
    return pessoa;
}

// 3. Arrow Functions
// Converta a função "dobrarNumeros" do exercício 1 em uma arrow function.
// Dica: use o método map para percorrer o array e dobrar cada elemento.
// No final do arquivo, o gabarito deste exercício está comentado.
const dobrarNumeros2 = nums => nums.map(num => num*2);

// 4. Map
// Crie uma função chamada "calcularDobro" que recebe um array de números como parâmetro e retorna um novo array onde cada número é dobrado, usando o método map.
// Dica, é o mesmo da questão 3, porém com uma função nomeada.

function calcularDobro(nums) {

    return nums.map(num => num*2);
}

// 5. Objeto - Chaves e Valores
// Crie uma função chamada "listarPropriedades" que recebe um objeto como parâmetro e retorna um array com as chaves desse objeto.
// Dica: use o método keys para obter as chaves do objeto.
function listarPropriedades(obj) {

    return Object.keys(obj);
}

// 6. Objeto - Valores
// Crie uma função chamada "listarValores" que recebe um objeto como parâmetro e retorna um array com os valores desse objeto.
// Dica: use o método values para obter os valores do objeto.
function listarValores(obj) {
    return Object.values(obj);
}

// 7. forEach
// Crie uma função chamada "mostrarElementos" que recebe um array como parâmetro e imprime cada elemento do array usando o método forEach.
// Dica: use o método forEach para percorrer o array e o método console.log para imprimir cada elemento.
function mostrarElementos(arr) {
    arr.forEach(element => {
        console.log(element);
    });
}


// 8. Arrow Functions e Operadores Aritméticos
// Crie uma função chamada "calcularPotencia" que recebe dois parâmetros: "base" e "expoente". UTILIZANDO ARROW FUNCTION
// A função deve retornar o resultado da base elevada ao expoente, usando o operador de exponenciação (**).
const calcularPotencia = (base, expoente) => 
    base**expoente;

// 9. Arrays e Métodos de Array
// Crie uma função chamada "encontrarMaiores" que recebe um array de números como parâmetro.
// A função deve retornar um novo array contendo apenas os números maiores do que 10.
// Dica: use o método filter para percorrer o array e filtrar os números maiores do que 10, easy peasy.
function encontrarMaiores(nums) {
    return nums.filter(num => num > 10);
}

// 10. Objeto - Método
// A função deve retornar o volume do retângulo.
function calcularVolumeRetangulo(comprimento, largura, profundidade) {
    return comprimento * largura * profundidade;
};
//antes de subir o exercício percebi um erro profano no exercício 10, mas quis deixá-lo aqui.
//Caso você encontre o erro, mande uma mensagem no telegram informando qual foi e ganhe um brinde surpresa.
//(limitado a 3 brindes, senão o financeiro fica bravo)
//válido somente para os trainees de 2023/2.


// 11. Arrays e Reduce
// Crie uma função chamada "calcularSoma" que recebe um array de números como parâmetro.
// A função deve retornar a soma de todos os números no array, usando o método reduce.
function calcularSoma(nums) {
    return nums.reduce((acumulador, num) => acumulador + num, 0);
}

//NÃO ALTERE NADA ABAIXO DESTA LINHA
module.exports = {
    dobrarNumeros: dobrarNumeros,
    criarPessoa: criarPessoa,
    calcularDobro: calcularDobro,
    listarPropriedades: listarPropriedades,
    listarValores: listarValores,
    mostrarElementos: mostrarElementos,
    calcularPotencia: calcularPotencia,
    encontrarMaiores: encontrarMaiores,
    calcularVolumeRetangulo: calcularVolumeRetangulo,
    calcularSoma: calcularSoma
    
};
