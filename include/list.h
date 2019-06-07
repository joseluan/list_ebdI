/*! @file list.h
    @brief estrutura de dado list.
*/
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
				/**
                * @brief Contruttor sem argumentos, current = nullptr
                */
				iterator(): current(nullptr){}
				
				/**
                * @brief Contruttor sem argumentos, data = nullptr
                * @param p é seu current
                */
				iterator(Node * p) : current(p){};
				
				/**
                * @brief retorna o seu Node
                * @return Node 
                */
				Node& operator* ( ){
					return *current;
				}

				/**
                * @brief pega o proximo Node // ++it
                * @return iterator
                */
				iterator & operator++(){ 
					current = current->next;
					return *this;
				}
				
				/**
                * @brief pega o proximo Node // it++
                * @return iterator
                */
				iterator & operator++(int){ 
					iterator * temp = this; 
					current = current->next;
					return *temp;
				} 

				/**
                * @brief pega o Node anterior // --it
                * @return iterator
                */
				iterator & operator--(){ 
					current = current->prev;
					return *this;
				}

				/**
                * @brief pega o Node anterior // it++
                * @return iterator
                */				
				iterator & operator--(int){ //t--
					Node * temp = current;
					current = current->prev;
					return temp;
				} 

				/**
                * @brief verifica se dois iterators são iguais
                * @return booleano
                */
				bool operator==(iterator rhs){
					return current->data == (rhs.current)->data;
				}

				/**
                * @brief verifica se dois iterators são diferentes
                * @return booleano
                */
				bool operator!=(iterator rhs){
					return current->data != (rhs.current)->data;
				}


			protected:	
				Node * current;
		};

		class const_iterator{
			public:
				/**
                * @brief Contruttor sem argumentos, current = nullptr
                */
				const_iterator(): current(nullptr){}
				/**
                * @brief Contruttor sem argumentos, data = nullptr
                * @param p é seu current
                */
				const_iterator(Node * p) : current(p){};
				
				/**
                * @brief retorna o seu const Node
                * @return const Node 
                */
				const Node& operator* ( ) const{
					return *current;
				}

				/**
                * @brief pega o proximo Node // ++it
                * @return const iterator
                */
				const_iterator & operator++(){ 
					current = current->next;
					return *this;
				} 
				
				/**
                * @brief pega o proximo Node // it++
                * @return const iterator
                */
				const_iterator & operator++(int){
					const_iterator * temp = this; 
					current = current->next;
					return *temp;
				}

				/**
                * @brief pega o Node anterior // --it
                * @return const iterator
                */
				const_iterator & operator--(){ 
					current = current->prev;
					return *this;
				} 
				
				/**
                * @brief pega o Node anterior // it--
                * @return const iterator
                */
				const_iterator & operator--(int){ //t--
					const_iterator * temp = this; 
					current = current->prev;
					return *temp;
				}

				/**
                * @brief verifica se dois const iterators são iguais
                * @return booleano
                */
				bool operator==(const const_iterator rhs) const{
					return current->data == (rhs.current)->data;
				}

				/**
                * @brief verifica se dois const iterators são diferentes
                * @return booleano
                */
				bool operator!=(const const_iterator rhs) const{
					return current->data != (rhs.current)->data;
				}

			protected:	
				Node * current;
		};

		// [II] Iterators
		/**
        * @brief iterator do começo do list
        * @return um iterator para o começo do list
        */
		iterator begin(){
			iterator ci(m_head);
			return ci;
		}

		/**
        * @brief const iterator do começo do list
        * @return um const iterator para o começo do list
        */
		const_iterator cbegin() const{
			const_iterator ci(m_head);
			return ci;
		}

		/**
        * @brief iterator do fim do list
        * @return um iterator para o final do list
        */
		iterator end(){
			iterator ci(m_field);
			return ci;
		}

		/**
        * @brief const iterator do fim do list
        * @return um const iterator para o final do list
        */
		const_iterator cend() const{
			const_iterator ci(m_field);
			return ci;
		}
		// fim [II]
		
		// [III] Capacity
		/**
        * @brief tamanho do list
        * @return quantidade de Node do list
        */
		int size() const{
			return m_size;
		}

		/**
        * @brief verifica se o list possui elementos
        * @return true caso o list estaja vazio, e false caso contrario
        */
		bool empty() const{
			return m_size == 0;
		}	
		// fim [III]
		
		// [IV] Modifiers
		/**
        * @brief remove todos os Node do list
        */
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
		
		/**
        * @brief primeiro valor do list
        * @return uma referencia para o primeiro valor do list
        */
		T & front(){
			if(m_head != nullptr)
				return m_head->data;
		}

		/**
        * @brief ultimo valor do list
        * @return uma referencia para o ultimo valor do list
        */
		T & back(){
			if(m_field != nullptr)
				return m_field->data;
		}

		/**
        * @brief adiociona um Node do final do list
        * @param value valor do Node a ser inserido
        */
		void push_back(const T & value){
			//Node * temp = new Node(value, m_field);
			Node * temp = m_field;

			if(m_head == nullptr){
				m_field = new Node(value, temp);
				m_head = new Node(value, nullptr, m_field);
			}else{
				//Node * temp2 = m_field;
				//m_field = new Node{};
				//temp2->next = m_field;
			}

			m_size++;
		}

		/**
        * @brief adiociona um Node do começo do list
        * @param value valor do Node a ser inserido
        */
		void push_front(const T & value){
			Node * temp = new Node(value, nullptr, m_head);
			m_head->prev = temp;
			m_head = temp;
 			if(m_field == nullptr)
				m_field = temp;
			m_size++;
		}

		/**
        * @brief remove um Node do começo do list
        */
		void pop_front(){
			if(m_head == nullptr) return;
			Node * temp = m_head->next;
			delete m_head; 
			m_head = temp;
			m_size--;
		}

		/**
        * @brief remove um Node do final do list
        */
		void pop_back(){
			if(m_head == nullptr) return;
			Node * temp = m_field->prev;
			delete m_field; 
			m_field = temp;
			m_size--;
		}
		

		// fim [IV]
	
		// [V] modificadores com iterators
		/** @brief recria o list apartir de dois Iterator
		* @param first começo da lista a ser copiada
		* @param last sucessor do fim da lista a ser copiada
        */	
		void assign(iterator first, iterator last){
			clear();
			while(first != last){
				first = ++first;
				push_back((*first).data);
			}
		}

		/** @brief recria o list para seus dados serem iguais a uma lista fornecida
		* @param list lista a ser igual a os dados do vector
        */
		void assign( std::initializer_list<T> ilist ){
			//clear();
			list<T> lista{};
			for (T it : ilist){
				lista.push_back(it);
			}

			*this = lista;
		}

		/** @brief recria o list para ter somente size Nodes com o valor de value
		* @param size quantidade de vezes qie value será copiado
		* @param value valor do Node
        */
		void assign(int size, const T& value){
			clear();
			
			/*while(size > 0){
				push_back(value);
				size--;
			}*/
			for (int i = 0; i < size; ++i){
				push_back(value);
			}
		}
		
		/**
        * @brief apaga um Node do list
        * @param it iterator a ser apagado
        * @return um iterator para o local onde o dado foi removido
        */
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

		/**
        * @brief remove uma de dados, apartir de dois iterators
        * @param first começo da sequencia de dados
        * @param last o posterior ao fim da sequencia de dados
        * @return um iterator para o local onde o dado foi removido
        */
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

		/** @brief proucura um Node apartir de um valor
		* @param value valor do Node
		* @return um const iterator do Node encontrado
        */
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
		/**
        * @brief construtor iniciando com 0 Nodes 
        */
		list(): m_size(0), m_head(nullptr), m_field(nullptr){}
		
		/**
        * @brief desconstrutor destroi os dados do list (deveria funcionar) 
        */
		~list(){
			clear();
		}

		/**
        * @brief construtor iniciando com os mesmos valores de outro list
        * @param source list a ser copiado
        */
		list(const list & source): m_size(source.m_size){
			clear();
			Node * it = source.m_head; 
			while(it->next != nullptr){
				push_back(it->data);
				it= it->next;
			}
			m_field = it;
		};

		/**
        * @brief copia um list para outro list
        * @param source list a ser copiado
        * @return uma referencia para list
        */
		list & operator=(const list & source){
			clear();
			Node * it = source.m_head; 
			while(it->next != nullptr){
				push_back(it->data);
				it= it->next;
			}
			m_field = it;
			return *this;
		}
		// fim [I]

	private: 
		int m_size; //!< quantidade de Node
		Node * m_head; //!< ponteiro de Node para o primeiro Node
		Node * m_field; //!< ponteiro de Node para o ultimo Node
};
}