/*
QMM (beta) - Q3 MultiMod
Copyright 2004-2024
https://github.com/thecybermind/qmm/
3-clause BSD license: https://opensource.org/license/bsd-3-clause

Created By:
    Kevin Masterson < cybermind@gmail.com >

*/

#ifndef __CLINKLIST_H__
#define __CLINKLIST_H__

template <typename T>
class CLinkNode {
	public:
		CLinkNode();
		~CLinkNode();

		T* data;
		CLinkNode<T>* prev;
		CLinkNode<T>* next;
};

//--------------

template <typename T>
class CLinkList {
	public:
		CLinkList();
		~CLinkList();

		CLinkNode<T>* add(T*);
		void del(CLinkNode<T>*);
		void del(T* ndata);

		CLinkNode<T>* get_first();
	private:
		CLinkNode<T>* first;
};

//==============

template <typename T>
CLinkNode<T>::CLinkNode() {
	this->data = NULL;
	this->prev = NULL;
	this->next = NULL;
}

template <typename T>
CLinkNode<T>::~CLinkNode() {
	if (this->data)
		delete (this->data);
	this->prev = NULL;
	this->next = NULL;
}

//--------------

template <typename T>
CLinkList<T>::CLinkList() {
	this->first = NULL;
}

template <typename T>
CLinkList<T>::~CLinkList() {
	CLinkNode<T>* p = this->first;
	CLinkNode<T>* q = NULL;
	while (p) {
		q = p;		//store current
		p = p->next;	//move to next
		delete q;	//delete stored
	}

	this->first = NULL;
}

template <typename T>
CLinkNode<T>* CLinkList<T>::add(T* data) {
	CLinkNode<T>* p = this->first;
	CLinkNode<T>* q = NULL;
	while (p) {
		q = p;		//store current
		p = p->next;	//move to next
	}
	p = new CLinkNode<T>;
	p->prev = q;
	if (q)
		q->next = p;
	else
		this->first = p;
	p->next = NULL;
	p->data = data;

	return p;
}

template <typename T>
void CLinkList<T>::del(T* ndata) {
	CLinkNode<T>* node = this->first;
	while (node) {
		if (node->data == ndata) {
			CLinkNode<T>* p = node->prev;
			CLinkNode<T>* n = node->next;

			//remove node from sequence
			//set previous' next to node's next
			if (p) p->next = n;
			//set next's previous to node's previous
			if (n) n->prev = p;

			//if the node is the first in this list, set to next node
			if (node == this->first)
				this->first = n;

			delete node;
			return;
		}
		node = node->next;
	}
}

template <typename T>
void CLinkList<T>::del(CLinkNode<T>* node) {
	CLinkNode<T>* p = node->prev;
	CLinkNode<T>* n = node->next;

	//remove node from sequence
	//set previous' next to node's next
	if (p) p->next = n;
	//set next's previous to node's previous
	if (n) n->prev = p;

	//if the node is the first in this list, set to next node
	if (node == this->first)
		this->first = n;

	delete node;
}

template <typename T>
CLinkNode<T>* CLinkList<T>::get_first() {
	return this->first;
}

#endif //__CLINKLIST_H__
