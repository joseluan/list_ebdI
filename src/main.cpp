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
			~Node(){
				delete &data;
				delete prev;
				delete next;
			}
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
					return iterator(current);
				} //++it
				
				iterator & operator++(int){ 
					current = current->next;
					return iterator(current->prev);
				} //it++

				iterator & operator--(){ return current->prev; } //--it
				
				iterator & operator--(int){ //t--
					Node * temp = current;
					current = current->prev;
					return temp;
				} //it++

				bool operator==(iterator & rhs){
					return this->data == rhs->data;
				}

				bool operator!=(iterator & rhs){
					return this->data != rhs->data;
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
					return const_iterator(current);
				} //++it
				
				const_iterator & operator++(int){ 
					current = current->next;
					return const_iterator(current->prev);
				} //it++

				const_iterator & operator--(){ return current->prev; } //--it
				
				const_iterator & operator--(int){ //t--
					Node * temp = current;
					current = current->prev;
					return temp;
				} //it++

				bool operator==(const const_iterator & rhs) const{
					return this->data == rhs->data;
				}

				bool operator!=(const const_iterator & rhs) const{
					return this->data != rhs->data;
				}


			protected:	
				Node * current;
		};

		// [I] membros especiais
		list(): m_size(0), m_head(nullptr), m_field(nullptr){}
		~list(){
			
		}

		list(const list<T> & lista): m_size(lista.m_size){
			Node * temp = m_head;
			Node * temp2 = m_field;
			/*
			while(m_head != m_field){
				delete m_head;
				delete m_field;

				m_head = temp;
				m_field = temp2;

				temp = m_head->next;
				temp2 = m_field->prev;
			}

			delete m_field;

			m_head = lista.m_head;
			m_field = lista.m_field;
			*/
		};

		list & operator=(const list& lista){
			m_head = lista.m_head;
			m_field = lista.m_field;
			m_size = lista.m_size;
			return *this;
		}

		// fim [I]
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
			//delete m_head; //por forças do além o delete não estar funcionando
			m_head = temp;
		}

		void pop_back(){
			if(m_head == nullptr) return;
			Node * temp = m_field->prev;
			//delete m_field; //por forças do além o delete não estar funcionando
			m_field = temp;
		}
		

		// fim [IV]
		// [V] modificadores com iterators
		
		/*void assign(iterator first, iterator last){
			clear();
			m_head = first.current;
			m_field = last.current;
			int size = 1;
			while(first != last){
				first++;
				size++;
			}
			m_size = size;
		}*/

		void assign( std::initializer_list<T> ilist ){
			//clear();
			list<T> lista{};
			for (T it : ilist){
				lista.push_back(it);
			}

			*this = lista;
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
	lista.assign({1, 2, 3});
	lista.find(2);
	cout << (*(lista.find(3))).data << endl; 
	
	return 0;
}