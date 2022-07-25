#pragma once
#include "Node.h"
#include "vector"

using std::vector;
using std::exception;

class Notework_manager
{
	
	
	/*
	 *Менеджер 
		будет знать обовсех нодах
		будет иметь 2 массива  с основными нодами и с свежими
		будет самостоятельно запускать ивенты всех нод
			сам рандомно будет вызывать ивенты
	 */
private:

	std::vector<Node*> NodeArr;
	std::vector<Node*> NewNodeArr;

	int callEvet, subscribeOnNode, unSubscribe, creatandSub, inaction;

	int start_size;

public:
	
	Notework_manager() {};
	
	void StartSimulator()
	{
		std::cout << "=== Construction managet notework ===" << std::endl;
		std::cout << "* Enter started number of nodes" << std::endl;

		std::cin >> start_size;

		if (start_size <= 1)
		{
			std::cout << "Number of nodes must be greater 1 !" << std::endl;
			exit(0);
		}
		// Distribute - распределить, between - между 
		std::cout << "* Distribute 100 percent between five events" << std::endl;
		std::cout << "  it is important that the sum of the distributed interest is equal to 100" << std::endl;

		std::cout << "\t * Call Event - ";
		std::cin >> callEvet;

		//std::cout << std::endl;
		std::cout << "\t * Subscription on node - ";
		std::cin >> subscribeOnNode;

		//std::cout << std::endl;
		std::cout << "\t * Un subscription on node - ";
		std::cin >> unSubscribe;

		//std::cout << std::endl;
		std::cout << "\t * Create and subscription in node - ";
		std::cin >> creatandSub;

		//std::cout << std::endl;
		std::cout << "\t * Skip stage - ";
		std::cin >> inaction;

		std::cout << std::endl;

		if (100 == callEvet + subscribeOnNode + unSubscribe + creatandSub + inaction)
		{
			std::cout << "Great, you coped\n" << std::endl;
		}
		else
		{
			std::cout << "Bad, you dont coped" << std::endl;
			//throw exception("Bad, you dont coped");
			exit(0);
		}


		Node* temptr = new Node();

		NodeArr.push_back(temptr);

		for (int i = 1; i < start_size; ++i)
		{

			Node* temp = new Node();

			NodeArr.push_back(temp);

			// Блок подписки предыдущего элемента на нынешний

			pair<bool, function<void(int, Node*)>> RandoFu = NodeArr[i - 1]->RandomEvern();

			temp->Subscribe(NodeArr[i - 1], RandoFu.second);

			NodeArr[i - 1]->MySubscription.emplace(temp, std::make_pair(RandoFu.first, 0));
		}
	}

	void StartSimulator(int size_val)
	{
		Node* temptr = new Node();

		NodeArr.push_back(temptr);

		for (int i = 1; i < size_val; ++i)
		{

			Node* temp = new Node();

			NodeArr.push_back(temp);

			// Блок подписки предыдущего элемента на нынешний

			pair<bool, function<void(int, Node*)>> RandoFu = NodeArr[i - 1]->RandomEvern();

			temp->Subscribe(NodeArr[i - 1], RandoFu.second);

			NodeArr[i - 1]->MySubscription.emplace(temp, std::make_pair(RandoFu.first, 0));
		}
	}

	
	void Tick()
	{
		/*
			Сперва пробежимяс по всем элиментам и проверим их на наличие подписок

			После пробежимся по массиву NodeArr и отработаем у каждого элемента ивент

			в конце массив свеже созданных элементов переместим в основной
		 */
		
		std::cout << "\n--Finding elements don't have sub--" << std::endl;
		
		for (int i = NodeArr.size() - 1; i > -1; --i)
		{
			if(NodeArr[i]->IsAlone())
			{
				
				std::cout << "\tFound and killed element dont had sub - " << NodeArr[i] << std::endl;
				NodeArr.erase(NodeArr.begin() + i);
			}
		}

		// Stage - этап
		std::cout << "--Stage calling events--" << std::endl;
		
		for (int i = 0; i < NodeArr.size(); ++i)
		{
			// сделай метод чтоб рандомно выбрать евент

			int RandIndex = rand() % 5;

			switch (RandIndex)
			{
				case 0:
				{
					std::cout << "\tNode - " << NodeArr[i] << " Call all events" << std::endl;
					NodeArr[i]->CallEvent();
					break;
				}
				case 1:
				{
					std::cout << "\tNode - " << NodeArr[i] << " Subscribe on random node" << std::endl;
					NodeArr[i]->SubscribeOnNode();
					break;
				}
				case 2:
				{
					std::cout << "\tNode - " << NodeArr[i] << " Un subscribe on node" << std::endl;
					NodeArr[i]->UnSubscribe();
					break;
				}
				case 3:
				{
					std::cout << "\tNode - " << NodeArr[i] << " Create and subscribe on new node" << std::endl;
					NewNodeArr.push_back(NodeArr[i]->CreateAndSubscribeNewNode());
					break;
				}
				case 4:
				{
					std::cout << "\tNode - " << NodeArr[i] << " Inaction this stage" << std::endl;
					NodeArr[i]->Inaction();
					break;
				}
				default :
				{
					throw exception("Ты что дурак ?\nКак так вышло что в менаджере индекс эвента привысил 4 ???");
					return;
				}
			}
		}

		for (int i = 0; i < NewNodeArr.size(); ++i)
		{
			NodeArr.push_back(NewNodeArr[i]);
		}
		NewNodeArr.clear();
	}
};