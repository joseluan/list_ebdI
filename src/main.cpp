#include <iostream>

using namespace std;

namespace ls{

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
				//friend class List<Object> lista;
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
			
			return *this;
		}

		// fim [I]
		// [II] Iterators
		const_iterator cbegin() const{
			const_iterator ci(m_head);
			return ci;
		}

		const_iterator cend() const{
			const_iterator ci(m_head);
			int cont = 0;

			while(cont <= m_size-1){
				ci++;
				cont++;
			}

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
			if(m_head == nullptr) return 0;
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

		void push_front(const T & value){
			Node * n;
			Node * temp = m_head;
			n->data = value;
			n->next = temp;
			n->prev = nullptr;
			m_head = n;
			//cout << (temp->next) << endl;
		}

		void push_back(const T & value){
			Node * n;
			n->data = value;
			//n->next = nullptr;
			//n->prev = m_field;
			//m_field->next = n;
			//m_field = n;
			//m_size += 1;
		}
		
		void pop_front(){
			Node * n = m_head;
			m_head = n->next;
			//delete n; //estar dando erro (falha de segmentação)
			m_size -= 1;
		}

		void pop_back(){
			Node * n = m_field;
			m_field = n->prev;
			//delete n; //estar dando erro (falha de segmentação)
			m_size -= 1;
		}

		// fim [IV]

	private: 
		int m_size;
		Node * m_head;
		Node * m_field;
};
}

int main(int argc, char const *argv[]){
	
	ls::list<int> lista = ls::list<int>();
	//ls::list<int> lista2(lista);
	
	lista.push_front(56);
	//lista.push_back(78);
	//lista.push_front(14);

	//lista.pop_back();

	//cout << lista.back() << endl;
	cout << lista.front() << endl;
	
	return 0;
}