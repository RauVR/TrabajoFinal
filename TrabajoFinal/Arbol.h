#ifndef __ARBOLBB_HPP__
#define __ARBOLBB_HPP__

#include <functional>
using namespace std;

template <class T>
class Nodo2 {
public:
	T elemento;
	Nodo2* izq;
	Nodo2* der;
};

template <class T>
class Arbol {
	typedef function<int(T, T)> Comp; //Lambda

	Nodo2<T>* raiz;
	void(*procesar)(T); //Puntero a funcion

	Comp comparar; // lambda de criterio de comparaci�n

public:
	//Arbol(void(*otroPunteroAFuncion)(T)) {
	//	this->procesar = otroPunteroAFuncion;
	//	this->comparar = [](T a, T b)->int {return a - b; };
	//	raiz = nullptr;
	//}
	Arbol() { raiz = nullptr; }


	bool insertar(T e) {
		return _insertar(raiz, e);
	}
	void enOrden() {
		_enOrden(raiz);
	}
	void preOrden() {
		_preOrden(raiz);
	}
	void postOrden() {
		_postOrden(raiz);
	}
	int cantidad() {
		return _cantidad(raiz);
	}
	int altura() {
		return _altura(raiz);
	}
	bool Buscar(T e) {
		return _buscar(raiz, e);
	}
	int Minimo() {
		return _minimo(raiz);
	}
	int Maximo() {
		return _maximo(raiz);
	}
	bool Eliminar(T e) {
		return _eliminar(raiz, e);
	}
	void Predecesor(T e) {
		return _predecesor(raiz, e);
	}
	void Sucesores(T e) {
		return _sucesores(raiz, e);
	}

private:
	bool _buscar(Nodo2<T>* nodo, T e) {
		if (nodo == nullptr) return false;
		else {
			int r = comparar(nodo->elemento, e);
			if (r == 0) return true;
			else if (r < 0) {
				return _buscar(nodo->der, e);
			}
			else {
				return _buscar(nodo->izq, e);
			}
		}
	}
	Nodo2<T>* _obtener(Nodo2<T>* nodo, T e) {
		if (nodo == nullptr) return nullptr;
		else {
			int r = comparar(nodo->elemento, e);
			if (r == 0) return nodo;
			else if (r < 0) {
				return _buscar(nodo->der, e);
			}
			else {
				return _buscar(nodo->izq, e);
			}
		}
	}
	bool _insertar(Nodo2<T>*& nodo, T e) {
		if (nodo == nullptr) {
			nodo = new Nodo2<T>();
			nodo->elemento = e;
			return true;
		}
		else {
			int r = comparar(nodo->elemento, e);
			if (r == 0) return false;
			else if (r < 0) {
				return _insertar(nodo->der, e);
			}
			else {
				return _insertar(nodo->izq, e);
			}
		}
	}
	void _enOrden(Nodo2<T>* nodo) {
		if (nodo == nullptr) return;
		_enOrden(nodo->izq);
		procesar(nodo->elemento);
		_enOrden(nodo->der);
	}

	void _preOrden(Nodo2<T>* nodo) {
		if (nodo == nullptr) return;
		procesar(nodo->elemento);
		_preOrden(nodo->izq);
		_preOrden(nodo->der);
	}

	void _postOrden(Nodo2<T>* nodo) {
		if (nodo == nullptr) return;
		_postOrden(nodo->izq);
		_postOrden(nodo->der);
		procesar(nodo->elemento);
	}
	bool _vacio() {
		return raiz == nullptr;
	}
	int _cantidad(Nodo2<T>* nodo) {
		//La cantidad de nodos del �rbol es:
		//	0 si es vac�o
		//	1 + la cantidad de nodos por la izquierda + la cantidad de nodos por la derecha

		if (nodo == nullptr)
			return 0;
		else
		{
			int ci, cd;
			ci = _cantidad(nodo->izq);
			cd = _cantidad(nodo->der);
			return 1 + ci + cd;
		}

	}
	int _altura(Nodo2<T>* nodo) {
		//La altura del �rbol es:
		//	0 si es vac�o
		//	la mayor de las alturas por la izquierda y por la derecha, las cu�les son 0 si son vac�as � 1 + la altura por la izq(o der) en caso contrario

		if (nodo == nullptr)
			return 0;
		else
		{
			int ai, ad;
			ai = 1 + _altura(nodo->izq);
			ad = 1 + _altura(nodo->der);
			return ai > ad ? ai : ad;
		}
	}

	int _minimo(Nodo2<T>* nodo) {
		if (nodo->izq == nullptr) return nodo->elemento;
		else
			return _minimo(nodo->izq);
	}
	int _maximo(Nodo2<T>* nodo) {
		if (nodo->der == nullptr) return nodo->elemento;
		else
			return _maximo(nodo->der);
	}
	bool _eliminar(Nodo2<T>*& nodo, T e) {
		if (nodo == nullptr) return false;
		else {
			int r = comparar(nodo->elemento, e);

			if (r < 0) {
				return _eliminar(nodo->der, e); //Aqui no pasa nada solo itera
			}
			else if (r > 0) {
				return _eliminar(nodo->izq, e); //Aqui no pasa nada solo itera
			}

			//Aqui empiezan con la eliminacion de nodos segun el caso

			else { // r==0 es porque se encontr� el elemento e en el arbol
				if (nodo->der == nullptr && nodo->izq == nullptr) {//caso 1
					nodo = nullptr;
					delete nodo;		// Aqui es donde hace la eliminacion
					return true;
				}
				else if (nodo->izq == nullptr) { //caso 2
					nodo = nodo->der;
					return true;
				}
				else if (nodo->der == nullptr) { //caso 3
					nodo = nodo->izq;
					return true;
				}
				else { //caso 4
					Nodo2<T>* aux = nodo->der; //Se establece buscar el menor elemento por la derecha
					while (aux->izq != nullptr)
					{
						aux = aux->izq; //Se obtiene la hoja menor
					}
					nodo->elemento = aux->elemento; //Se actualiza el elemento en el nodo raiz y
					return _eliminar(nodo->der, aux->elemento); //se env�a a eliminar el elemento en el arbol por la derecha
				}
			}
		}
	}


	void _sucesores(Nodo2<T>*& nodo, T e) {
		if (nodo == nullptr) return;
		else {
			int r = comparar(nodo->elemento, e);
			if (r == 0) {
				cout << nodo->izq->elemento << endl;
				cout << nodo->der->elemento << endl;
			}
			else if (r < 0) {
				return _sucesores(nodo->der, e);
			}
			else {
				return _sucesores(nodo->izq, e);
			}
		}
	}
	void _predecesor(Nodo2<T>*& nodo, T e) {
		if (nodo == nullptr) return;
		else {
			Nodo2<T>* actual = nodo;
			while (actual->izq != nullptr && actual->der != nullptr) {
				if (actual->izq->elemento == e) {
					cout << actual->elemento << " ";
					break;
				}
				if (actual->der->elemento == e) {
					cout << actual->elemento << " ";
					break;
				}
			}

		}
	}
};

#endif

