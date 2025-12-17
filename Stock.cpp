#include "Stock.h"


Stock::Stock(){
    _cantidad = 0;
    _idProducto = 0;
}

int Stock::getCantidad(){
    return _cantidad;
}

int Stock::getIdProducto(){
    return _idProducto;
}

void Stock::setCantidad(int cant){
    _cantidad = cant;
}

void Stock::setIdProducto(int id){
    _idProducto = id;
}
