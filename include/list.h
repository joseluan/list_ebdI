
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
				delete data;
				delete prev;
				delete next;
			}
		};

	public:
		class const_iterator{
			public:
				const_iterator(): current(nullptr){}
				
				const Node& operator* ( ) const{
					return *current;
				}

				const_iterator & operator++(){ return current->next;} //++it
				const_iterator & operator++(int){
					Node * temp = current;
					current = current->next;
					return temp;
				} //it++
				const_iterator & operator--(){ return current->prev; } //++it
				const_iterator & operator--(int){
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
				//const_iterator(Node * p) : current(p){};
				//friend class List<Object> lista;
		};

		list(): m_size(0), m_head(nullptr), m_field(nullptr){}
		~list(){
			Node * temp = m_head->next;
			while(m_head != m_field){
				delete m_head;
				m_head = temp;
				temp = m_head->next;
			}
			delete m_field;
		}

		list(const list & lista): m_size(lista.size()), m_head {}
	private: 
		int m_size;
		Node * m_head;
		Node * m_field;
};
}