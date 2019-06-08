# EDBI
Implementação de uma lista encadeada dupla feito c++

#verificando
abra a pasta e executeo comando make, para criar o executável, após digite ./list para executar
o código principal onde pode ser testado estar na pasta src, e o arquivo é o main.cpp

#notas
O projeto não está com os google test, pois não sei como rodar isso.

possiveis erros:
	Métodos estranhos:
		- push_back
		- push_front
		nesses dois casos tentei de varias maneiras para que funcionasse, ex.: criando uma variavel temporaria pra guardar um m_head ou até criar um node e igualar a m_head
		sem a varaivel temporaria
		- o assign(iterator, iterator)
		- erase(iterator, iterator)
		pode dar falha de segmentação

