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
	std::pair<int,int> getKey(){return key;}
	double getRate(){return rate;}
	Node* getLeft(){return left;}
	Node* getRight(){return right;}
	Node* getParent(){return parent;}
	void setRate(double r){rate = r;}
	void setParent(Node* x){parent = x;}
	void setLeft(Node* x){left=x;}
	void setRight(Node* x){right=x;}
	void setKey(std::pair<int,int> a){key = a;}
};

class BinaryTree{
private:
	Node* head;
	Node* conductor;
public: 
	//create an empty binary tree.
	BinaryTree(){
		head = conductor = nullptr;
	}
	//construct special tree for Gillespie such that leaves are rates and parents are sums
	BinaryTree(std::vector< std::pair<double,std::pair<int,int> > > r){
		head = conductor = new Node(r[0].first,r[0].second);
		for (int i = 1; i<r.size();i++)
			insert(r[i]);
	}


	//special insert method given a tree like:
//			       5
//			     /  \   
//			    3    2    

	//that is supposed to insert new element 6 it will try to balance the tree by puttin it on the side that has less
//			      11
//			     /  \   
//			    3    8    
//				    / \
//			       2   6  		

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
		conductor->getLeft()->setParent(conductor);
		conductor->setRight(new Node(a.first,a.second));
		conductor->getRight()->setParent(conductor);
		double difference = conductor->getRate() - (conductor->getRight()->getRate()+conductor->getLeft()->getRate());
		conductor->setKey({0,0});
		update(conductor,-difference);
		conductor = head;
	}
	
//special remove func that given a binary tree such as
//			      11
//			     /  \   
//			    3    8    
//				    / \
//			       2   6  	
//with the purpose of removing 6
//will remove it like so
//			       5
//			     /  \   
//			    3    2
//	and if it need to remove 2 it would change to this		    
//			       3
//			     /  \   
//			  null   null  		       		
	void remove(int creatureNum, Node* temp){
		// conductor = head;
		//std::cout<<"\n\n";
		int id = 0;
		//prettyPrint(head,id);
		if (temp == nullptr)
			return;
		if(temp->getLeft()==NULL && temp->getRight()==NULL && temp->getKey().first==creatureNum){
			//std::cout<<"found: "<<temp->getRate()<<" "<<temp->getKey().first<<" "<<temp->getKey().second<<"\n";
			if (temp->getParent()==nullptr) {
				head = conductor = nullptr;
				return;
			}
			//else std::cout<<"ok"<<std::flush;
			if (equals(temp, temp->getParent()->getLeft())){
				//std::cout<<"switching right to parent";
				Node* parentR = temp->getParent()->getRight();
				parentR->setParent(temp->getParent()->getParent());
				if (parentR->getParent()==nullptr){
					head = conductor = parentR;
					return;
				}
				if (equals(temp->getParent(), temp->getParent()->getParent()->getLeft()))
					parentR->getParent()->setLeft(parentR);
				else
					parentR->getParent()->setRight(parentR);

				update(parentR->getParent(),-temp->getRate());
			}
			else{
				//std::cout<<"switching left to parent\n";
				Node* parentL = temp->getParent()->getLeft();
				//std::cout<<"parentL: "<< parentL->getRate()<<" "<<parentL->getKey().first<<"\n";
				parentL->setParent(temp->getParent()->getParent());
				if (parentL->getParent()==nullptr){
					head = conductor = parentL;
					return;
				}
				if (equals(temp->getParent(), temp->getParent()->getParent()->getLeft()))
					parentL->getParent()->setLeft(parentL);
				else
					parentL->getParent()->setRight(parentL);

				update(parentL->getParent(),-temp->getRate());
			}
		}
		remove(creatureNum,temp->getLeft());
		remove(creatureNum, temp->getRight());
	}

//checks to see if two nodes rates and keys are equal
	bool equals(Node* a, Node* b){
		return a->getRate() == b->getRate() && a->getKey() == b->getKey();
	}
//will update all parent nodes by adding the increment to their rate val
	void update(Node* updatePoint,double increment){
		if (updatePoint == nullptr) return;
		updatePoint->setRate(updatePoint->getRate()+increment);
		if (updatePoint->getParent()!=NULL)
			update(updatePoint->getParent(),increment);
	}

//checks to see if the conductor is a leaf
	bool isLeaf(){return conductor->getLeft()==NULL && conductor->getRight()==NULL;}

//Gillespie step
	std::pair<double,std::pair<int,int> > find(double place){
		conductor = head;
		while (place<conductor->getRate() && conductor->getRight() != NULL){
			// std::cout<<conductor->getRate()<<'\n';
			if (place>conductor->getLeft()->getRate()){
				place -= conductor->getLeft()->getRate();
				conductor = conductor->getRight();
				//std::cout<<"went right" << '\n';
			}
			else{
				conductor = conductor->getLeft();
				//std::cout<<"went left" << '\n';
			}
		}
		return {conductor->getRate(),conductor->getKey()};
	}

//prints all nodes in the tree
	void prettyPrint(Node* x, int & id){
		if (!x) return;
		prettyPrint(x->getLeft(),id);
		id++;
		std::cout<<id<<" "<< x ->getRate()<<" "<<x->getKey().first<<std::endl;
		prettyPrint(x->getRight(),id);

	}


	Node* getHead(){return head;}
	double rSum(){return head->getRate();}
};



