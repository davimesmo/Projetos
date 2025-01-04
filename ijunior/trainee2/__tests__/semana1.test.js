const exercises = require('../semana1'); // Importe o módulo que contém as funções

describe('Testes para os exercícios desafiadores', () => {
    test('Teste para a função dobrarNumeros', () => {
        expect(exercises.dobrarNumeros([1, 2, 3])).toEqual([2, 4, 6]);
    });

    test('Teste para a função criarPessoa', () => {
        expect(exercises.criarPessoa('Alice', 25)).toEqual({ nome: 'Alice', idade: 25 });
    });

    test('Teste para a função calcularDobro', () => {
        expect(exercises.calcularDobro([4, 6, 8])).toEqual([8, 12, 16]);
    });

    test('Teste para a função listarPropriedades', () => {
        expect(exercises.listarPropriedades({ a: 1, b: 2, c: 3 })).toEqual(['a', 'b', 'c']);
    });

    test('Teste para a função listarValores', () => {
        expect(exercises.listarValores({ a: 1, b: 2, c: 3 })).toEqual([1, 2, 3]);
    });

    test('Teste para a função mostrarElementos', () => {
        const consoleLog = jest.spyOn(console, 'log');
        exercises.mostrarElementos([10, 20, 30]);
        expect(consoleLog).toHaveBeenNthCalledWith(1, 10);
        expect(consoleLog).toHaveBeenNthCalledWith(2, 20);
        expect(consoleLog).toHaveBeenNthCalledWith(3, 30);
        consoleLog.mockRestore(); // Restaura a função original após o teste
    });

    test('Teste para a função calcularPotencia', () => {
        expect(exercises.calcularPotencia(2, 3)).toBe(8);
    });

    test('Teste para a função encontrarMaiores', () => {
        expect(exercises.encontrarMaiores([5, 15, 2, 12, 8])).toEqual([15, 12]);
    });

    test('Teste para a função calcularVolumeRetangulo', () => {
        expect(exercises.calcularVolumeRetangulo(2, 3, 4)).toEqual(24);
    });

    test('Teste para a função calcularSoma', () => {
        expect(exercises.calcularSoma([1, 2, 3, 4, 5])).toBe(15);
    });
});
