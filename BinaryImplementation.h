#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <random>

class Node{
private:
	Node* parent{nullptr};
	Node* left{nullptr};
	Node* right{nullptr};
	double rate{0};
	std::pair<int,int> key{0,0};
public:
	Node(void) = default;
	Node(double r, std::pair<int,int> k){
		rate = r;
		key = k;
	}
	Node(Node* l, Node* r){
		rate = l->getRate() + r->getRate();
		l->setParent(this);
		r->setParent(this);
		left = l;
		right = r;
	}
	// Node(Node* l, Node* r){}
	std::pair<int,int> getKey(){return key;}
	double getRate(){return rate;}
	Node* getLeft(){return left;}
	Node* getRight(){return right;}
	Node* getParent(){return parent;}
	void setRate(double r){rate = r;}
	void setParent(Node* x){parent = x;}
	void setLeft(Node* x){left=x;}
	void setRight(Node* x){right=x;}
};

class BinaryTree{
private:
	double deltaT;
	double currentTime;
	Node* head;
	Node* conductor;
public: 
	BinaryTree(){
		head = conductor = NULL;
	}
	BinaryTree(std::vector< std::pair<double,std::pair<int,int> > > r){
		std::vector< Node* > q(r.size());
		for (int i = 0; i < q.size(); i++){
			q[i] = new Node(r[i].first,r[i].second);
		}
		// double desiredNum = pow(2,ceil(log2(q.size())));
		// while(q.size()!=desiredNum){
		// 	q.push_back(new Node());
		// }
		Node* rate1;
		Node* rate2;
		while (q.size()>1){
			for (int i = 0; i<q.size() ; i++){
				std::cout<<q[i]->getRate()<<" ";
			}
			std::cout<<'\n';
			rate1 = q.front(); q.erase(q.begin());
			rate2 = q.front(); q.erase(q.begin());
			Node* parent = new Node(rate1,rate2);
			q.push_back(parent);
		}
		head = conductor = q[0];
	}

	void insert(std::pair<double,std::pair<int,int> > a){
		conductor = head;
		while(!isLeaf()){
			if (conductor->getRight()->getRate() >= conductor->getLeft()->getRate())
				conductor = conductor->getLeft();
			else
				conductor = conductor->getRight();
		}
		// Node* temp = new Node(new Node(conductor->getRate(),conductor->getKey()),new Node(a.first,a.second));
		conductor->setLeft(new Node(conductor->getRate(),conductor->getKey()));
		conductor->setRight(new Node(a.first,a.second));
		double difference = conductor->getRate() - (conductor->getRight()->getRate()+conductor->getLeft()->getRate());
		update(conductor,difference);
		conductor = head;
	}
	
	void remove(int creatureNum, Node* temp){
		// conductor = head;
		if (temp == NULL)
			return;
		if(temp->getLeft()==NULL && temp->getRight()==NULL && temp->getKey().first==creatureNum){
			// double parentSum = conductor->getParent()->getRight()->getRate() + conductor->getParent()->getLeft()->getRate();
			// double difference = conductor->getRate() - parentSum;
			// conductor->getParent()->setRate(parentSum - conductor->getRate());
			temp->setRight(nullptr);
			temp->setLeft(nullptr);
			update(temp->getParent(),-(temp->getRate()));
		}
		remove(creatureNum,temp->getLeft());
		remove(creatureNum, temp->getRight());
	}

	void update(Node* updatePoint,double increment){
		updatePoint->setRate(updatePoint->getRate()+increment);
		if (updatePoint->getParent()!=NULL)
			update(updatePoint->getParent(),increment);
	}

	bool isLeaf(){return conductor->getLeft()==NULL && conductor->getRight()==NULL;}

	std::pair<int,int> find(){
		conductor = head;
		auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		std::mt19937 mt_rand;
		mt_rand.seed(seed);
		auto die = std::bind(std::uniform_real_distribution<double>(0,1), mt_rand);
	    deltaT = (-log(die()))/rSum();
        currentTime+=deltaT;
        double place = die()*rSum();
		while (place<conductor->getRate() && conductor->getRight() != NULL){
			// std::cout<<conductor->getRate()<<'\n';
			if (place>conductor->getLeft()->getRate()){
				place -= conductor->getLeft()->getRate();
				conductor = conductor->getRight();
				std::cout<<"went right" << '\n';
			}
			else{
				conductor = conductor->getLeft();
				std::cout<<"went left" << '\n';
			}
		}
		return conductor->getKey();
	}
	Node* getHead(){return head;}
	double rSum(){return head->getRate();}
};


