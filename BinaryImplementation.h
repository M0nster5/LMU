#include <vector>
#include <algorithm>
#include <iostream>

//This only works if the set of rates given is 2^i


class Node{
private:
	Node* left;
	Node* right;
	double rate;
	double key;
public:
	Node(){
		left = NULL;
		right = NULL;
		rate = 0;
		key = 0;
	}
	Node(double r, double k){
		left = NULL;
		right = NULL;
		rate = r;
		key = k;
	}
	Node(Node* l, Node* r){
		rate = l->getRate() + r->getRate(); 
		key = 0;
		left = l;
		right = r;
	}
	double getKey(){return key;}
	double getRate(){return rate;}
	Node* getLeft(){return left;}
	Node* getRight(){return right;}
	void setLeft(Node* x){left=x;}
	void setRight(Node* x){right=x;}
};

class BinaryTree{
private:
	Node* head;
	Node* conductor;
public: 
	BinaryTree(){
		head = conductor = NULL;
	}
	BinaryTree(std::vector< std::vector< double > > r){
		std::vector< Node* > q(r.size());
		for (int i = 0; i < q.size(); i++){
			q[i] = new Node(r[i][1],r[i][0]);
		}
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
	double find(double place){
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
};



