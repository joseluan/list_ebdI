#include <iostream>
#include <stdlib.h>

using namespace std;

namespace sc{

template<typename T>
class list {
	private:
		struct Node {
			T data; //<! compo de dados
			Node *prev; //<! ponteiro para o anterior node na lista
			Node *next; //<! ponteiro para o próximo node na lista
			
			//<! Contrutor basico
			Node(const T & d = T(), Node * p = nullptr, Node * n = nullptr)
				: data(d), prev(p), next(n) {}
		};

	public:
		class iterator{
			public:
				iterator(): current(nullptr){}
				
				iterator(Node * p) : current(p){};
				
				Node& operator* ( ){
					return *current;
				}

				iterator & operator++(){ 
					current = current->next;
					return *this;
				} //++it
				
				iterator & operator++(int){ 
					iterator * temp = this; 
					current = current->next;
					return *temp;
				} //it++

				iterator & operator--(){ 
					current = current->prev;
					return *this;
				} //--it
				
				iterator & operator--(int){ //t--
					Node * temp = current;
					current = current->prev;
					return temp;
				} //it++

				bool operator==(iterator rhs){
					return current->data == (rhs.current)->data;
				}

				bool operator!=(iterator rhs){
					return current->data != (rhs.current)->data;
				}


			protected:	
				Node * current;
		};

		class const_iterator{
			public:
				const_iterator(): current(nullptr){}
				const_iterator(Node * p) : current(p){};
							
				const Node& operator* ( ) const{
					return *current;
				}

				const_iterator & operator++(){ 
					current = current->next;
					return *this;
				} //++it
				
				const_iterator & operator++(int){
					const_iterator * temp = this; 
					current = current->next;
					return *temp;
				} //it++

				const_iterator & operator--(){ 
					current = current->prev;
					return *this;
				} //--it
				
				const_iterator & operator--(int){ //t--
					const_iterator * temp = this; 
					current = current->prev;
					return *temp;
				} //it++

				bool operator==(const const_iterator rhs) const{
					return current->data == (rhs.current)->data;
				}

				bool operator!=(const const_iterator rhs) const{
					return current->data != (rhs.current)->data;
				}

			protected:	
				Node * current;
		};

		// [II] Iterators
		iterator begin(){
			iterator ci(m_head);
			return ci;
		}

		const_iterator cbegin() const{
			const_iterator ci(m_head);
			return ci;
		}

		iterator end(){
			iterator ci(m_field);
			return ci;
		}

		const_iterator cend() const{
			const_iterator ci(m_field);
			return ci;
		}

		// fim [II]
		// [III] Capacity
		int size() const{
			return m_size;
		}

		bool empty() const{
			return m_size == 0;
		}
		// fim [III]
		// [IV] Modifiers
		void clear(){
			if(m_head == nullptr) return;
			Node * temp = m_head;
			while(temp != m_field){
				delete temp;
				temp = m_head->next;
			}

			m_head = nullptr;
			m_field = nullptr;
			m_size = 0;
		}
		
		T & front(){
			if(m_head != nullptr)
				return m_head->data;
		}

		T & back(){
			if(m_field != nullptr)
				return m_field->data;
		}

		void push_back(const T & value){
			Node * temp = new Node(value, m_field);
			m_field = temp;
			if(m_head == nullptr)
				m_head = temp;
			m_size++;
		}

		void push_front(const T & value){
			Node * temp = new Node(value, nullptr, m_head);
			m_head->prev = temp;
			m_head = temp;
 			if(m_field == nullptr)
				m_field = temp;
			m_size++;
		}

		void pop_front(){
			if(m_head == nullptr) return;
			Node * temp = m_head->next;
			delete m_head; 
			m_head = temp;
			m_size--;
		}

		void pop_back(){
			if(m_head == nullptr) return;
			Node * temp = m_field->prev;
			delete m_field; 
			m_field = temp;
			m_size--;
		}
		

		// fim [IV]
		// [V] modificadores com iterators
		
		void assign(iterator first, iterator last){
			clear();
			while(first != last){
				first = ++first;
				push_back((*first).data);
			}
		}

		void assign( std::initializer_list<T> ilist ){
			//clear();
			list<T> lista{};
			for (T it : ilist){
				lista.push_back(it);
			}

			*this = lista;
		}

		void assign(const T& value){
			clear();
			push_back(value);
		}
		
		iterator erase(iterator itr){
			if(itr == begin()){
				pop_front();
				return begin();
			}else if(itr == end()){
				pop_back();
				return end();
			}

			iterator temp = itr;
			iterator temp_n = ++itr;
			iterator temp_p = --itr;

			delete &(*temp);

			(*temp_p).next = &(*temp_n);
			(*temp_n).prev = &(*temp_p);
			return temp_p;
		}

		iterator erase(iterator first, iterator last){
			if(first == begin() && last == end()){
				clear();
				return first;
			}

			iterator temp = first;
			iterator temp_n = ++first;
			iterator temp_p = --first;
			//apagando os iterators
			while(temp_n != last){
				delete &(*temp);
				temp = temp_n;
				temp_n = temp_n++;
			}

			(*temp_p).next = &(*temp_n);
			(*temp_n).prev = &(*temp_p);
			return temp_p;
		}

		const_iterator find(const T & value) const{
			if(m_head->data == value) return const_iterator(m_head);
			Node * temp = m_head->next;
			while(temp != nullptr){
				if(temp->data == value) return const_iterator(temp);
				temp = temp->next;
			}
			return nullptr;
		}

		// fim [V]

		// [I] membros especiais
		list(): m_size(0), m_head(nullptr), m_field(nullptr){}
		~list(){
			//clear(); // quando rodei o programa ficou num loop infinito
		}

		list(const list & lista): m_size(lista.m_size){
			clear();
			Node * it = lista.m_head; 
			while(it->next != nullptr){
				push_back(it->data);
				it= it->next;
			}
			m_field = it;
		};

		list & operator=(const list & lista){
			clear();
			Node * it = lista.m_head; 
			while(it->next != nullptr){
				push_back(it->data);
				it= it->next;
			}
			m_field = it;
			return *this;
		}

		// fim [I]
	private: 
		int m_size;
		Node * m_head;
		Node * m_field;
};
}

int main(int argc, char const *argv[]){
	
	sc::list<int> lista{};
	lista.push_back(56);
	lista.push_front(132);
	
	sc::list<int> lista2{};
	
	

	lista.erase(lista.begin(), lista.end());

	cout <<  " = " << lista.back() << endl; 
	
	return 0;
}