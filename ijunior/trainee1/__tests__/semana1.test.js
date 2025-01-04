const semana1 = require ('../semana1.js');

describe('Desafio da Semana 1', () => {
    test('Função nome', () => {
        expect(semana1.nome('iJunior')).toBe('iJunior');
    });

    test('Função operadoresAritmeticos', () => {
        expect(semana1.operadoresAritmeticos(10, 5)).toEqual([15, 5, 50, 2, 0]);
    });

    test('Função parOuImpar', () => {
        expect(semana1.parOuImpar(7)).toBe('ímpar');
    });

    test('Função podeDirigir', () => {
        expect(semana1.podeDirigir(20)).toBe('Pode dirigir');
    });

    test('Função verificarNumero', () => {
        expect(semana1.verificarNumero(-3)).toBe('negativo');
    });

    test('Função calcularMedia', () => {
        expect(semana1.calcularMedia(5, 10, 15)).toBe(10);
    });

    test('Função maiorDeIdade', () => {
        expect(semana1.maiorDeIdade(22)).toBe(true);
    });

    test('Função podeVotar', () => {
        expect(semana1.podeVotar(17, true)).toBe(true);
    });

    test('Função somarNumerosAteN', () => {
        expect(semana1.somarNumerosAteN(5)).toBe(15);
    });

    test('Função maiorNumero', () => {
        expect(semana1.maiorNumero(7, 3)).toBe(7);
    });

    test('Função verificarTriangulo', () => {
        expect(semana1.verificarTriangulo(4, 4, 4)).toBe('equilátero');
    });

    test('Função verificarAnoBissexto', () => {
        expect(semana1.verificarAnoBissexto(2024)).toBe(true);
    });

    test('Função compararStrings', () => {
        expect(semana1.compararStrings('hello', 'hello')).toBe(true);
    });

    test('Função maiorTresNumeros', () => {
        expect(semana1.maiorTresNumeros(8, 12, 5)).toBe(12);
    });
});