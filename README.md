# Trab_SD
Batalha Naval com 2-Clientes-Servidor, Utilizando INET em C
1. INTRODUÇÃO
O trabalho consiste no desenvolvimento de uma implementação utilizando conceitos apresentados em sala de aula sobre sincronização, exclusão mutua, cliente-servidor, acordo, eleição de líder, etc. A implementação pode ser feita em qualquer. Fica a critério do grupo a escolha, mas deve justificar o motivo da escolha no relatório. O objetivo do trabalho prático é propiciar ao aluno a aplicação dos conceitos estudados na disciplina e aplica-los em uma implementação prática.

2. ENTREGA
Os trabalhos deverão ser entregues no dia 26/Nov no Moodle com os códigos dos arquivos e um relatório descrevendo o código e como deve ser executado.

3. TRABALHO
- Cada grupo irá implementar um serviço de acordo com o protocolo e a linguagem escolhida.
- O relatório deverá constar pelo menos os seguintes itens abaixo:
  * Descrever de maneira sucinta a proposta do trabalho
  * Descrição dos requisitos funcionais do cliente e o servidor
  * Como é feita a comunicação entre o cliente e o servidor. Utilize um diagrama de sequência para descrever os passos dessa comunicação.
  * Diagrama de classe da implementação
  * Como o cliente e o servidor receberão as mensagens enviadas.
  * Descrição do serviço e como são executados no servidor.

4. AVALIAÇÃO
- Será avaliado a execução da implementação proposta para cada grupo.
  * Comunicação entre um cliente acessando o servidor de acordo com a aplicação proposta
para os grupos.
  * Avaliação do funcionamento da aplicação de acordo com a especificação proposta.
- Avaliação do relatório
  * Descrição dos passos de instalação, bibliotecas, configuração e execução da implementação para cada serviço, etc.
  * Descrição do serviço proposto para o grupo.

5. TEMAS/APLICAÇÃO
GRUPO 1 – Batalha Naval
- O sistema é composto por dois clientes e um servidor primário e um backup.
- Os clientes enviam as posições dos navios em um mapa 10x10 posicionando os seus navios.
- O servidor irá receber essas posições e alocar no mapa onde apenas o servidor saberá, mas cada
cliente tem as posições de seus navios com os seus ataques com sucesso ou não.
- Os clientes irão enviar coordenadas de ataque para o servidor e o servidor irá responder se o
ataque foi bem-sucedido ou não para os clientes. É necessário estabelecer um controle de
exclusão mútua nos clientes onde apenas um cliente possa acessar o servidor para enviar o
ataque na sua vez. Além disso, um cliente não pode enviar dois ataques sucessivos ao mesmo
tempo.
  * Os clientes terão uma visão dos seus ataques e o servidor informará o estado do mapa
  para cada cliente.
- o servidor primário deverá ser replicado.
  * É necessário que se implemente um mecanismo de atualização do estado para o servidor
  backup quando o servidor primário falha possa continuar a execução da aplicação.
  * É importante que na apresentação do trabalho os servidores devem está em máquinas
  diferentes. 
