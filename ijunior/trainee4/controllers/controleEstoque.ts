import { Data } from "../models/interfaceData";
import {estoqueService} from "../services/serviceEstoque";
const service = new estoqueService();
export async function adicionarProduto(data:Data){
    try{
        await service.criar(data);
    }catch(error){
        console.log(error);
    }
}