#include <iostream>
#include <limits>

using namespace std;

struct Pizza {
    string nombrePizza;
    float precio;
    int porciones;
}menuPizzas[5];

struct NodoPizza{
    Pizza pizza;
    NodoPizza *siguiente;
};

struct Orden{
    NodoPizza *nodoPizza;
    float total;
    string nombreCliente;
};

struct NodoOrden{
    Orden orden;
    NodoOrden *siguiente;
};

struct ColaOrden{
    NodoOrden *frenteCola;
    NodoOrden *finalCola;
}colaOrden;


void NuevaOrden();
void EnconlarOrden(Orden nuevaOrden);
void TerminarOrdenes();
void DeleteOrden();
Orden PopOrden();

void NuevaPizza(int opcion, NodoPizza *&);
void StackPizza(Pizza nuevaPizza, NodoPizza *&);
void ImprimirStack(NodoPizza *nodoPizza);

void ImprimirMenu();

bool OrdenColaVacia();

void MenuMain();

int main(){
    menuPizzas[0]={"Hawaiana",5.50,8};
    menuPizzas[1]={"Peperoni",6.50,8};
    menuPizzas[2]={"Suprema",7.50,8};
    menuPizzas[3]={"Carne",8.50,8};
    menuPizzas[4]={"Jamon",9.50,8};

    MenuMain();

    return 0;
}

void MenuMain(){
    int opcion;

    while(true){
        cout<<"Bienvenido al sistema de Pizzas Lola, que accion desea realizar?"<<"\n"
        <<"1- Ingresar nueva orden"<<"\n"
        <<"2- Mostar el menu de pizzas"<<"\n"
        <<"3- Terminar las ordenes"<<"\n"
        <<"4- Cerrar Sesion"<<"\n";
        cin>>opcion;
        switch (opcion) {
            case 1:
                NuevaOrden();
                break;
            case 2:
                ImprimirMenu();
                break;
            case 3:
                TerminarOrdenes();
                break;
            case 4:
                return;
            default:
                return;
        }
    }
}

void NuevaOrden(){
    Orden nuevaOrden;
    int opcion = 0;

    cout<<"Ingrese nombre del cliente : ";
    if (!(cin >> nuevaOrden.nombreCliente)) {
        cerr << "Error: Invalid input for the client's name." << endl;
        // Clear the error state and consume any remaining input
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    nuevaOrden.nodoPizza = nullptr;
    do {
        cout << "Que opcion desea ordenar?" << "\n"
             << "1- Hawaiana $5.50" << "\n"
             << "2- Peperoni $6.50" << "\n"
             << "3- Suprema $7.50" << "\n"
             << "4- Carne $8.50" << "\n"
             << "5- Jamon $9.50" << "\n"
             << "6- Salir" << "\n";
        cin >> opcion;
        if (opcion >= 1 && opcion <= 5){
            NuevaPizza(opcion, nuevaOrden.nodoPizza);
        }
    }while (opcion != 6);

    NodoPizza *temp = nuevaOrden.nodoPizza;
    nuevaOrden.total = 0;

    while (temp != nullptr){
        nuevaOrden.total += temp->pizza.precio;
        temp = temp->siguiente;
    }
    EnconlarOrden(nuevaOrden);
}

void EnconlarOrden(Orden nuevaOrden){
    NodoOrden *nuevoNodo = new NodoOrden;

    nuevoNodo->orden = nuevaOrden;
    nuevoNodo->siguiente = nullptr;

    if(OrdenColaVacia()){
        colaOrden.frenteCola = nuevoNodo;
    } else {
        colaOrden.finalCola->siguiente = nuevoNodo;
    }
    colaOrden.finalCola = nuevoNodo;
}

void TerminarOrdenes(){
    while (!OrdenColaVacia()){
        Orden orden = PopOrden();
        cout<<"Nombre del cliente :"<<orden.nombreCliente<<"\n";
        ImprimirStack(orden.nodoPizza);
        cout<<"Precio Final $"<<orden.total<<"\n";
    }
}

Orden PopOrden(){
    Orden orden = colaOrden.frenteCola->orden;
    DeleteOrden();
    return orden;
}

void DeleteOrden(){
    if(!OrdenColaVacia()){
        NodoOrden *temp = colaOrden.frenteCola;
        colaOrden.frenteCola = colaOrden.frenteCola->siguiente;

        if(temp == colaOrden.finalCola){
            colaOrden.finalCola = nullptr;
        }

        delete temp;
    }

}

void NuevaPizza(int opcion, NodoPizza *&pizzaStack){
    Pizza nuevaPizza = menuPizzas[opcion-1];
    StackPizza(nuevaPizza, pizzaStack);
}

void StackPizza(Pizza nuevaPizza, NodoPizza *&pizzaStack){
    auto *nuevoNodo = new NodoPizza;
    nuevoNodo->pizza = nuevaPizza;
    nuevoNodo->siguiente = pizzaStack;
    pizzaStack = nuevoNodo;
}

void ImprimirStack(NodoPizza *nodoPizza){
    NodoPizza *temp = nodoPizza;
    while (temp != nullptr){
        cout<<"**** "<<temp->pizza.nombrePizza<<" ***"<<"\n";
        cout<<"**** $"<<temp->pizza.precio<<" ***"<<"\n";
        temp = temp->siguiente;
    }
}

void ImprimirMenu(){
    for(Pizza menuPizza : menuPizzas){
        cout<<"Nombre :"<<menuPizza.nombrePizza<<"\n";
        cout<<"Precio : $"<<menuPizza.precio<<"\n";
        cout<<"Porciones :"<<menuPizza.porciones<<"\n";
    }
}


bool OrdenColaVacia(){
    return colaOrden.frenteCola == nullptr;
}