import {readCSV} from "../models/readCSV";
import {writeCSV} from "../models/writeCSV";
import { Data } from '../models/interfaceData';
import fs from "fs";

const filePath = "./models/estoque.csv"

export class estoqueService{
    async criar(data:Data){
        if(typeof data.nome != "string"){
            throw new Error("ERROU!");
        }else{
            await writeCSV(filePath, [data]);
        }
    }
}

